
## office

### list LAN devices with name

#### motivation

to get zhifeiji IP for pulling `pkg.zip` in the terminal

#### solution

1. research

In [linux - How can I list all IPs in the connected network, through Terminal preferably? - Super User](https://superuser.com/questions/261818/how-can-i-list-all-ips-in-the-connected-network-through-terminal-preferably), `arp-scan` not works, but `fing` is OK.

2. implementation

download `fing` via `brew install fing --cask`, and run in APP mode (no command of `fing` now), and login using account (e.g. via google):

![picture 1](.imgs/S01_manage-1662690835516-88191fdc3a252ace479e9d1993974050ad3b0e509527cfb04786c4bfb47f489b.png)  

3. result

we can get to know that ip of zhifeiji is `192.168.1.236`, and the ip of `UBUNTU18AOSP0` (`$ARPARA_AOSP_SERVER`) is `192.168.1.242`.

### how to mount/unmount LAN drivers

#### how to list drivers on Mac

```sh
l /Volumes
```

#### how to unmount drivers on Mac

ref: - [Mount & Unmount Drives from the Command Line in Mac OS X](https://osxdaily.com/2013/05/13/mount-unmount-drives-from-the-command-line-in-mac-os-x/)

```sh
diskutil unmount /Volumes/XXX
```

#### how to mount LAN-drivers on Mac

In [network - mount_smbfs: server rejected the connection: Authentication error on Mac OS High Sierra 10.13.6 - Ask Different](https://apple.stackexchange.com/questions/341631/mount-smbfs-server-rejected-the-connection-authentication-error-on-mac-os-high), it recommends using:

```sh
mount -t smbfs '//share;user@server.domain/share' /Volumes/share
```

```