## Full Guide: how to sync clipboard over ssh + tmux + vim

## 1. enable `xclip` on remote ubuntu via ssh

to fix `Error: Can't open display: (null)` when using `echo "xx" | xclip` on remote ubuntu, I found we should config `ForwardX11 yes` in both local and remote ssh config, see: https://askubuntu.com/a/305681/1629991

### 1. config

```conf
## -- local ---
# /etc/ssh/ssh_config
Host *
    ForwardX11 yes

## -- remote ---
# /etc/ssh/sshd_config
X11Forwarding yes
```

### 2. connect on client

```sh
# the `-X` is to enable the `X11-forward` feature
ssh -X mark$ARPARA_AOSP_SERVER
```

### 3. test on remote

```sh
➜  ~ echo 'clip on air' | xclip
➜  ~ xclip -o
clip on air
➜  ~ xclip -selection clipboard -o
zzz2
➜  ~ echo 'clip on clipboard' | xclip -selection clipboard
➜  ~ xclip -o
clip on air
➜  ~ xclip -selection clipboard -o
clip on clipboard
➜  ~ xclip -sel clipboard -o
clip on clipboard
➜  ~ xclip -sel clip -o
clip on clipboard
```

## enable access to clipboard on remote ubuntu at local (part 1: basic)

首先可以看一下这篇[Forward your clipboard via SSH reverse tunnels](https://gist.github.com/dergachev/8259104)，它给出了最简单的基于无限循环监听端口(`nc -l`)并复制(`pbcopy`)的方案。

### 1. enable listen on one shell

```sh
while (true); do nc -l 5556 | pbcopy; done
```

### 2. connect using reverse tunnelling

#### solution 1

```sh
ssh mark@$ARPARA_AOSP_SERVER -R 5556:localhost:5556
```

#### solution 2

1. config on local

```conf
# ~/.ssh/config
RemoteForward 5556 localhost:5556
```

2. (possibly necessary) reload ssh

```sh
sudo launchctl unload /System/Library/LaunchDaemons/ssh.plist
sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist
```

3. connect without `-R`

```sh
ssh mark@$ARPARA_AOSP_SERVER
```

### 3. test on remote

```sh
echo "test 1" | nc -q0 localhost 5556
```

then we can access the `test 1` in the local clipboard.

## enable access to clipboard on remote ubuntu at local (part 2: socket)

ref: https://medium.com/hackernoon/tmux-in-practice-copy-text-from-remote-session-using-ssh-remote-tunnel-and-systemd-service-dd3c51bca1fa

### 1. config plist

```sh
PLIST_PBCOPY_SSH=`~/.pbcopy_ssh.plist`
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>pbcopy-ssh</string>

    <key>UserName</key>
    <string>mark</string>

    <key>Program</key>
    <string>/usr/bin/pbcopy</string>

    <key>Sockets</key>
    <dict>
        <key>Listeners</key>
        <dict>
            <key>SockNodeName</key>
            <string>localhost</string>
            <key>SockServiceName</key>
            <string>19988</string>
        </dict>
    </dict>
    <key>inetdCompatibility</key>
    <dict>
        <key>Wait</key>
        <false/>
    </dict>
</dict>
</plist>
```

### 2. chmod (necessary)

```sh
chmod 755 $PLIST_PBCOPY_SSH
```
  
see https://developer.apple.com/forums/thread/665661?answerId=695171022#695171022, otherwise would have the following error if we `load` or `unload` the plist file:

```text
Load failed: 5: Input/output error
Try running `launchctl bootstrap` as root for richer errors.
```

### 3. start plist

```sh
launchctl load $PLIST_PBCOPY_SSH
launchctl start pbcopy-ssh
```

we can also check the running state of plist via `launchctl print gui/501/pbcopy-ssh | grep state` to only get `state = not running`, but it have worked actually.

### 4. test plist

```sh
ssh mark@$ARPARA_AOSP_SERVER -R 19988:localhost:19988

echo 'test 2' | nc -q0 localhost 19988
```

then we can access the `test 2` in the local clipboard.



ref:
- [ssh - How to use X11 forwarding to copy from vim to local machine - Stack Overflow](https://stackoverflow.com/questions/47822357/how-to-use-x11-forwarding-to-copy-fro m-vim-to-local-machine)
- [How to copy to clipboard in Vim? - Stack Overflow](https://stackoverflow.com/questions/3961859/how-to-copy-to-clipboard-in-vim#:~:text=In%20vim%20command%20mode%20press,and%20CMD%20%2B%20v%20to%20paste.)

