
## linux init manual

see: [centos init manual](centos-init-manual.md)

## linux connection (`ssh`)

### ssh without password

```sh
# ref: https://superuser.com/a/400720/1365851
cat ~/.ssh/id_ed25519.pub | ssh root@47.113.227.53 -T "cat >> ~/.ssh/authorized_keys"
```

### ssh keep connection alive

the simplest way is to force the client to keep sending [a null] message(packet) to the server, in case that the server closed the connection beyond the time limitation, and what you need to do is just to modify 2 lines in your `/etc/ssh/ssh_config` file.

```sh
sudo vim /etc/ssh/ssh_config
```

change into these:

```yaml
HOST: *
	ServerAliveInterval 60
```

finally, maybe you should restart your client. If you use the mac, you can:

```sh
# restart-ssh, reference: https://gist.github.com/influx6/46c39709a67f09908cc7542ca444fca2
sudo launchctl stop com.openssh.sshd
sudo launchctl start com.openssh.sshd
```

### DEPRECIATED: scp no secret/password

It's easy that if only you generate a `id_rsa.pub` and ` ` to your `~/.ssh/authorization_keys` then things all done.

```sh
# username="xxx"
# server="xxxxx"
# file="id_rsa.pub"

# scp ~/.ssh/$file $username@$server:
# ssh $username@$server
# cat $file >> ~/.ssh/authorized_keys
# rm $file
```

ref:

- [How to use the Linux ‘scp’ command without a password to make remote backups | alvinalexander.com](https://alvinalexander.com/linux-unix/how-use-scp-without-password-backups-copy/)

## linux env management

### how to change apt source

ref:

- [command line - How do I change mirrors in Ubuntu Server from regional to main? - Ask Ubuntu](https://askubuntu.com/questions/104695/how-do-i-change-mirrors-in-ubuntu-server-from-regional-to-main)

#### resolution 1: manual change from the App of `Softwares & Updates`

#### resolution 2: modify the configuration manually from the terminal

> CONCLUSION

```sh
MIRROR_FROM="us.archive.ubuntu.com"
MIRROR_TO="mirrors.tuna.tsinghua.edu.cn"
APT_FILE="/etc/apt/sources.list"
sudo sed -i "s|${MIRROR_FROM}|${MIRROR_TO}|g" ${APT_FILE}
```

> DETAIL

There are a few mirror servers can be used in China:

- mirrors.tuna.tsinghua.edu.cn
- ftp.sjtu.edu.cn
- mirrors.aliyun.com
- mirrors.huaweicloud.com
- mirrors.yun-idc.com
- ...

The format of these mirrors may be as `http://${MIRROR_URL}/ubuntu/`

And the default configuration of ubuntu servers are at `/etc/apt/sources.list`, with a copy of backup at `/etc/apt/sources.list.save`.

Here is what the `save` contents are:

```yaml
// /etc/apt/sources.list.save
#deb cdrom:[Ubuntu 18.04.6 LTS _Bionic Beaver_ - Release amd64 (20210915)]/ bionic main restricted

# See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to
# newer versions of the distribution.
deb http://us.archive.ubuntu.com/ubuntu/ bionic main restricted
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic main restricted

## Major bug fix updates produced after the final release of the
## distribution.
deb http://us.archive.ubuntu.com/ubuntu/ bionic-updates main restricted
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic-updates main restricted

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team. Also, please note that software in universe WILL NOT receive any
## review or updates from the Ubuntu security team.
deb http://us.archive.ubuntu.com/ubuntu/ bionic universe
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic universe
deb http://us.archive.ubuntu.com/ubuntu/ bionic-updates universe
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic-updates universe

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team, and may not be under a free licence. Please satisfy yourself as to
## your rights to use the software. Also, please note that software in
## multiverse WILL NOT receive any review or updates from the Ubuntu
## security team.
deb http://us.archive.ubuntu.com/ubuntu/ bionic multiverse
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic multiverse
deb http://us.archive.ubuntu.com/ubuntu/ bionic-updates multiverse
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic-updates multiverse

## N.B. software from this repository may not have been tested as
## extensively as that contained in the main release, although it includes
## newer versions of some applications which may provide useful features.
## Also, please note that software in backports WILL NOT receive any review
## or updates from the Ubuntu security team.
deb http://us.archive.ubuntu.com/ubuntu/ bionic-backports main restricted universe multiverse
# deb-src http://us.archive.ubuntu.com/ubuntu/ bionic-backports main restricted universe multiverse

## Uncomment the following two lines to add software from Canonical's
## 'partner' repository.
## This software is not part of Ubuntu, but is offered by Canonical and the
## respective vendors as a service to Ubuntu users.
# deb http://archive.canonical.com/ubuntu bionic partner
# deb-src http://archive.canonical.com/ubuntu bionic partner

deb http://security.ubuntu.com/ubuntu bionic-security main restricted
# deb-src http://security.ubuntu.com/ubuntu bionic-security main restricted
deb http://security.ubuntu.com/ubuntu bionic-security universe
# deb-src http://security.ubuntu.com/ubuntu bionic-security universe
deb http://security.ubuntu.com/ubuntu bionic-security multiverse
# deb-src http://security.ubuntu.com/ubuntu bionic-security multiverse
```

### how to know what's the os platform

```sh
# mac: Darwin
uname

# if platform is mac
if [[ $(uname) == Darwin ]];
then XXX;
else YYY;
fi;
```

ref:

- [bash - How to check if running in Cygwin, Mac or Linux? - Stack Overflow](https://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux)

### how to configure python environment

1. install the python on the server, the version of which would better correspond with the one of the local in case of unexpected error caused by version difference
2. use `virtualenv` to create an env based on this python version named `venv_py` under this working directory
3. activate this env
4. use `pip` to install the `requirements.txt`
5. run!

```sh
PY_VERSION=python3.9

# install the target python version based on its version number
# if you don't use these two lines, then you would suffer from `wget blablabla...` when you checked what the hell the python repo url is
sudo apt install software-properties-common -y
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install ${PY_VERSION}

# use `virtualenv` to create and activate a new python env fast~
sudo apt install virtualenv
virtualenv -p ${PY_VERSION} venv_py
source venv_py/bin/activate

# install all the requirements
# if you need to dump all the requirements of a python project used, you can use `pip freeze > requirements.txt` so that a file named of `requirements.txt` would be generated under the current directory
pip install -r requirements.txt

# run our backend of `fastapi`
python main.py
```

### :white_check_mark: cannot use `sudo apt-get install xxx` to install packages

```sh
cd /var/lib/dpkg/updates
rm -rf ./*

sudo apt-get update

sudo apt-get disk-upgrade # it may cost a little of time
```

ref:

I changed the suggestion in this article from `rm -r` to `rm -rf`, otherwise not successful.

- [E:dpkg was interrupted, you must manually run'dpkg 配置'to correct the problem. - 码上快乐](https://www.codeprj.com/blog/a352621.html)

This discussion seems wonderful but didn't get my problem solved.

- [apt - "The package lists or status file could not be parsed or opened" - Ask Ubuntu](https://askubuntu.com/questions/410045/the-package-lists-or-status-file-could-not-be-parsed-or-opened)

## linux file system management

### mkdir if not exist

```sh
mkdir -p DIR
```

ref:

- [mkdir](https://pubs.opengroup.org/onlinepubs/009695399/utilities/mkdir.html)

### ls and delete files

```sh
ls | grep STR | xargs rm -f
```

WARNING! Since the operation pipeline is silent, [you are likely to remove files that you did not intend to remove](https://stackoverflow.com/questions/20858524/delete-a-list-of-files-with-find-and-grep#:~:text=you%20are%20likely%20to%20remove%20files%20that%20you%20did%20not%20intend%20to%20remove).

Hence, you'd better use `ls | grep STR` first to check whether all the files to remove meet your expectation.

### fastest delete file

Don't bother checking if the file exists, just try to remove it.

```sh
rm -f PATH

brew install dialog
# or
rm PATH 2> /dev/null

find . -name 'test'

if [ "$BLEG" != xxx ]; then command; fi

```

```py
print("hello")
```

```ts
interface Test {
  name: string;
}
```

ref:

- [shell script to remove a file if it already exist - Stack Overflow](https://stackoverflow.com/questions/31318068/shell-script-to-remove-a-file-if-it-already-exist/31318262)

### DEPRECIATED: how to show absolute path of file from relative

I cannot use `brew install realpath` like their `apt install realpath`, but I can use `realpath`, which may be pre-built-in.

Plus, later I saw that maybe realpath is a submodule of mac package, which is named as `findutils`.

```sh
realpath FILE
```

ref:

- [bash - How to retrieve absolute path given relative - Stack Overflow](https://stackoverflow.com/questions/4175264/how-to-retrieve-absolute-path-given-relative)

### UPDATE-2022-02-05: how to show absolute path of file from relative

```sh
brew install coreutils
realpath FILE
```

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1644071924987-9cc4405cfa1edb81803f05a7e6a842f6dba03a8cf1b35e9c187f5f1a5a5880db.png)

> ref

- [macos - Bash script absolute path with OS X - Stack Overflow](https://stackoverflow.com/questions/3572030/bash-script-absolute-path-with-os-x)

### how to copy file into clipboard

core ref: https://apple.stackexchange.com/a/15327

#### it's easy to copy a text file

```sh
# copy
pbcopy < FILE

# paste to command line
pbpaste

# paste to a new file
pbpaste > FILE2
```

But attention, the `pbpaste` would cause corruption when deals with binary file.

#### but it cannot be done for a binary file

Since the traditional `command + c | command + v` is just copy the reference of file into clipboard, instead of the content itself, we had no way to use `pbcopy` to copy a file, and then use `command + v` to paste at another place.

A solution is to use osascript.

```osascript
#!/usr/bin/osascript
on run args
  set abs_path to do shell script "/usr/local/bin/greadlink -f -- " & (first item of args)
  set the clipboard to POSIX file abs_path
end
```

ref:

- [mac - How to use terminal to copy a file to the clipboard? - Ask Different](https://apple.stackexchange.com/questions/15318/how-to-use-terminal-to-copy-a-file-to-the-clipboard)

### how to show file size

```sh
# -l show detail
# -h show 'human readable size
ls -lh FILE/DIR
```

ref:

- [How to Make ls Command to Show File Sizes in Megabytes in Ubuntu](https://www.tutorialrepublic.com/faq/how-to-make-ls-command-to-show-file-sizes-in-megabytes-in-ubuntu.php)

### how to compare between files (`diff` & `vimdiff`)

- see: [bash - unix diff side-to-side results? - Stack Overflow](https://stackoverflow.com/questions/17195308/unix-diff-side-to-side-results)

There is a few of `diff` commands for us to choose.

#### resolution 1: `diff F1 F2`

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1642517649112-cb2bf00d7a0d7d954fdc039c3862869a96a67c75fc4190101616cd5b3ad0495a.png)

#### resolution 2: `diff -y F1 F2` or `sdiff F1 F2`

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1642517708938-fd8d1056dcc311fca0ff60316445a2fea77f670b4d7353cea9d6034775beb75a.png)

#### resolution 3: `vimdiff F1 F2`

It's awesome! Isn't it?

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1642517738027-4beec462aa9bda3ff2127c563de64a20d8703edc7774603372fce03807992a96.png)

#### TODO: resolution 4: git diff

### FIXME: how to copy/move directory files correctly to soft links under target directory without affecting git?

example:

When I zipped one modified `frameworks/native` directory to be e.g. `RAW`, and then reset the `frameworks/native` to be the init.

Then I move all the files under `RAW` to `frameworks/native` with the command:

```sh
cp -r RAW/* TARGET/frameworks/native/
```

The error arose up since there are soft links under `frameworks/native`, such as `libs/ui` which is indeed `libs/ui -> XXX/ui`.

However, in my zipped file of `RAW`, the links seemingly have turned to be the real files/dirs, which introduced the problem `directory --> non-directory`.

The wanted effect is copying/moving all the files under conflicted directory to where they should be.

However, the git marked those files as `TypeChange`...

ref:

- [linux - cp: cannot overwrite directory with non-directory - Super User](https://superuser.com/questions/1395407/cp-cannot-overwrite-directory-with-non-directory/1395410)

- [cp recursively into a directory that symlinks to dirs of same name as in source - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/555985/cp-recursively-into-a-directory-that-symlinks-to-dirs-of-same-name-as-in-source)

## linux disk management

### `ncdu`, disk space tui

### `baobab`, disk space gui

ref:

- [disk usage - How do I find the amount of free space on my hard drive? - Ask Ubuntu](https://askubuntu.com/questions/73160/how-do-i-find-the-amount-of-free-space-on-my-hard-drive)

- [baobab — Homebrew Formulae](https://formulae.brew.sh/formula/baobab)

#### install problem

When installing `ncdu`, error ocurred: [No such file or directory @ rb_sysopen ruby - Stack Overflow](https://stackoverflow.com/questions/44678437/no-such-file-or-directory-rb-sysopen-ruby)

The reason is that some dependency is missing, we can first install it and then install the target.

```sh
brew install librsvg
brew install baobab
```

#### effects

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1642600987157-8df330aac5a1fedd7d6c5f6d46f98256fedfcfa18b3f4f3ba05914fc06e19ac4.png)

## linux shells management

ref:

this article is enough and recommended:

- [How To Change Shell To Bash in Linux / Unix - nixCraft](https://www.cyberciti.biz/faq/how-to-change-shell-to-bash/)

- [How to find list of available shells by command-line? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/140286/how-to-find-list-of-available-shells-by-command-line)

- [How do I find out what shell I am using on Linux/Unix? - nixCraft](https://www.cyberciti.biz/tips/how-do-i-find-out-what-shell-im-using.html)

### redirect stdin/stderr

1. [redirect stdin/err with prefix](https://unix.stackexchange.com/questions/440426/how-to-prefix-any-output-in-a-bash-script#comment796857_440426)

```sh
ECHO_PREFIX="[init]"
exec > >(
  trap "" INT TERM
  sed 's/^/'"$ECHO_PREFIX"' /'
)
exec 2> >(
  trap "" INT TERM
  sed 's/^/'"$ECHO_PREFIX"'(stderr) /' >&2
)
```

2. [reset redirecting](https://unix.stackexchange.com/questions/258799/how-do-i-turn-off-redirection-once-ive-turned-it-on)

```sh
exec > /dev/tty
exec 2> /dev/tty
```

### FIXED: `bash navigate to directory without cd`

!!!tip 一定要搜的准！否则大概率搜不到！搜这个也花了十几分钟的……

add this line to your `~/.bashrc`:

```sh
shopt -s autocd
```

ref:

- [Switch To A Directory Without Using Cd Command in Linux - OSTechNix](https://ostechnix.com/automatically-switch-directory-without-using-cd-command/#:~:text=You%20can%20now%20go%20to,any%20directory%20in%20the%20Terminal.)

- [(1 条消息) 【Linux】一步一步学 Linux——shopt 命令(214)\_嵌入式开发工程师---欢迎大家一起交流-CSDN 博客](https://blog.csdn.net/dengjin20104042056/article/details/100566309)

### shell common aliases

!!!tip `cd -` is very useful for switching back and forth

```sh
# Easier directory navigation.
alias ~="cd ~"
alias .="cd .."
alias ..="cd ../.."
alias ...="cd ../../.."
alias ....="cd ../../../.."
alias cd..="cd .." # Typo addressed.
```

ref:

- [Shell Aliases For Easy Directory Navigation #OneDevMinute - DEV Community](https://dev.to/mrahmadawais/shell-aliases-for-easy-directory-navigation-onedevminute-30nm)

### list all the shells

```sh
$ cat /etc/shells # list valid login shells
/bin/sh
/bin/bash
/bin/rbash
/bin/dash
/bin/zsh
/usr/bin/zsh
```

### background: `sh` is different with `bash`

When I write `source` in shell script, and run by `sh xx.sh`, then it failed with `no permission`.

However, when I use `bash xx.sh`, then everything runs well.

Thus, the `sh` definitely doesn't equal as `bash`, and it seems that function of `sh` is the subset of `bash`.

If so, why I still need to use `sh`? Just for short?

<img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640152196813-linux-howto-84174e9e7dbb6fcc489b015f68e1c88b23fc19874bfcba40c3171f17cc8051a1.png" width="480" />

ref: https://stackoverflow.com/a/48785960/9422455

### see what's the current Shell

```sh
[1:42:41]:~$ echo $SHELL
/usr/bin/zsh
[1:43:25]:~$ echo $0
/usr/bin/zsh
[1:43:29]:~$ ps -p $$
   PID TTY          TIME CMD
 29657 pts/2    00:00:00 zsh
```

### switch shell

You can change your default shell using the chsh (“change shell” ) command as follows.

The syntax is:

```sh
# usage
chsh
chsh -s {shell-name-here}
chsh -s {shell-name-here} {user-name-here}

# samples
chsh -s /bin/bash
chsh -s /bin/bash $USER
```

### set zsh as default shell

see: [zsh-howto](../Mac/zsh-howto.md)

### how to prefix any output in a bash script?

see: [How to prefix any output in a bash script? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/440426/how-to-prefix-any-output-in-a-bash-script#comment796857_440426)

#### resolution 1. use function: easiest but side effect

```sh
function echo() { /bin/echo $PREFIX$*; }
```

But this would affect the `echo XXX >> FILE`, since we doesn't want to change the content to write into file.

#### RECOMMENDED: resolution 2. redirect stdin/err

```sh
exec > >(trap "" INT TERM; sed 's/^/foo: /')
exec 2> >(trap "" INT TERM; sed 's/^/foo: (stderr) /' >&2)
```

This is my recommended resolution since it only affects the stdin/err.

> result

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/general-howto-1643958401451-415c243209f2d1c85e94139c6c1850c5720f364be1be5c9210c78c573eb21b1b.png)

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/general-howto-1643958220574-b93cd09053ad7978f8b6ec09fa40dfb679bd517a9af6440b2c4a3eb443e99380.png)

### :white_check_mark: the terminal cannot up down after editing

This is a problem confused me for a long time.

Today, I finally knows what's the hell at: [linux - How to scroll up and down in sliced "screen" terminal - Stack Overflow](https://stackoverflow.com/questions/18489216/how-to-scroll-up-and-down-in-sliced-screen-terminal)

Anyway, terminal is hard to learn, I just know `control + a` can help me exit the so-called copy mode.

### TODO: bind `option + arrow` to jump word in zsh on ubuntu vmware on MacOS

> ref

- :sparkles: [Useful keyboard shortcuts](https://help.ubuntu.com/stable/ubuntu-help/shell-keyboard-shortcuts.html.en)
- [zsh jump word - Google Search](https://www.google.com/search?newwindow=1&sxsrf=AOaemvJocqqP64PM0tOaO5QuVGhGgwR1kw%3A1643272448532&lei=AFnyYY_8H8G4mAWLj7C4Cg&q=zsh%20jump%20word&ved=2ahUKEwiP_MD0wtH1AhVBHKYKHYsHDKcQsKwBKAN6BAg-EAQ&biw=1629&bih=945&dpr=2.2)
- [keyboard shortcuts - ALT+arrow moving between words in zsh and iTerm2 - Super User](https://superuser.com/questions/427163/altarrow-moving-between-words-in-zsh-and-iterm2)
- [Keyboard shortcuts in Terminal on Mac - Apple Support (HK)](https://support.apple.com/en-hk/guide/terminal/trmlshtcts/mac)
- [key binding - How to bind command key in zsh? - Super User](https://superuser.com/questions/349439/how-to-bind-command-key-in-zsh)
- [Zsh — Mac OS option key for bindkey](https://gist.github.com/YumaInaura/27bb1f79881a63bed2fb9635cbaed73b)
- [what key i'm pressing - Google Search](https://www.google.com/search?q=what+key+i%27m+pressing&oq=what+key+i+am&aqs=chrome.1.69i57j0i10j0i22i30l8.6503j0j4&sourceid=chrome&ie=UTF-8)
- ["Key-Test" - keyboard test online](https://en.key-test.ru/)
- [zsh - Ctrl + left/right arrow keys issue - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/58870/ctrl-left-right-arrow-keys-issue)
- [shell - Looking for ALT+LeftArrowKey solution in zsh - Stack Overflow](https://stackoverflow.com/questions/12382499/looking-for-altleftarrowkey-solution-in-zsh)
- [keyboard shortcuts - How can I delete a word backward at the command line (bash and zsh)? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/94331/how-can-i-delete-a-word-backward-at-the-command-line-bash-and-zsh)
- [command line - How to delete words in the terminal with Ctrl-Backspace like in the rest of Ubuntu? - Ask Ubuntu](https://askubuntu.com/questions/1017287/how-to-delete-words-in-the-terminal-with-ctrl-backspace-like-in-the-rest-of-ubun)
- [12.04 - Why does ctrl + left arrow not skip words? - Ask Ubuntu](https://askubuntu.com/questions/162247/why-does-ctrl-left-arrow-not-skip-words)

### how to clear broken soft links

```sh
# TODO: [UNDERSTAND] remove all broken soft links in the current directory
find -L . -name . -o -type d -prune -o -type l -exec rm {} +
```

> result

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1643962824307-0b5ff2544be91cdb7a591f6b94322d0823537a3c5e4aec1d1258c72e2e0c886f.png)

> ref

- [bash - Delete all broken symbolic links with a line? - Stack Overflow](https://stackoverflow.com/questions/22097130/delete-all-broken-symbolic-links-with-a-line)

## linux commands management

> :warning:
>
> 1. be careful to use `\`` in terminal / shell since it's would be treated as executable commands: <img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1641501462043-6790c46051fa5db1246b560e795c5b1737d5e508faf7a9247b1c52e1ce4abdbc.png" />  
>    see: [(20 条消息) shell 基础知识-echo 及单引号、反引号和双引号详解\_Luckiers 的博客-CSDN 博客\_echo 单引号和双引号](https://blog.csdn.net/Luckiers/article/details/103501168)

### how to check file/project size

1. using `find`

```sh
function checkFileSizesOfType() {
    find . -not -path "./.history/*" -not -path "**/node_modules/*" -name "*.$1" -type f -exec ls -al {} \; | sort -k5 -rn | sed 's/ \+/\t/g' | cut -f 9
}
```

2. using `ncdu`

3. using `baobab`

### linux quotes

非常经典的文章：

- [UNIX Shell Quotes - a simple tutorial](https://www.grymoire.com/Unix/Quote.html)

逆天的五引号：

- [bash - How to escape single quotes within single quoted strings - Stack Overflow](https://stackoverflow.com/questions/1250079/how-to-escape-single-quotes-within-single-quoted-strings)

### pip uninstall multi packages

scenario:

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1656146275078-576942a994df0141296e78f05af3cc20df82aafef4960ddc02a5cacbf9defbfb.png)

requirements:

uninstall all the packages of name starting with `pyobjc`.

solution:

```sh
grep pyobj requirements.txt | gsed 's/==.*//g' | xargs pip uninstall --yes
```

ref:

- xargs: [linux - Using grep and sed to find and replace a string - Stack Overflow](https://stackoverflow.com/questions/6178498/using-grep-and-sed-to-find-and-replace-a-string)

- auto yes: [linux - How to run pip in non-interactive mode? - Super User](https://superuser.com/questions/816143/how-to-run-pip-in-non-interactive-mode)

### Ternary operator (三元运算符)、短路运算符（`a=${VAR:-DEFAULT}`）

- [syntax - Ternary operator (?:) in Bash - Stack Overflow](https://stackoverflow.com/questions/3953645/ternary-operator-in-bash)

- [(1 条消息) Shell 和 Bash 中的三元运算符，控制 log 打印时间\_kouryoushine 的博客-CSDN 博客\_shell 三元运算](https://blog.csdn.net/kouryoushine/article/details/92838138)

### `|` , `||`, `&`, `&&`, `;`

```sh
A | B   # 管道！
A & B   # 并行

A && B  # 当A成功后继续运行B
A || B  # 当A失败后继续运行B
A; B;   # 无论A是否成功，之后继续运行B
```

ref:

- [Running asynchronous shell commands inside a synchronous one, i.e. wait for result - Stack Overflow](https://stackoverflow.com/questions/33484156/running-asynchronous-shell-commands-inside-a-synchronous-one-i-e-wait-for-resu)

### `&&` and `;`

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1644302136920-9459b3ac865f4e744a50bcefb0917e40b4f68d4b2d8f0c0e28befc62c4488a62.png)

> ref

- [bash - What is the difference between "&&" and ";" when chaining commands - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/37069/what-is-the-difference-between-and-when-chaining-commands)

### `alias` vs `variable`

> `alias` is used for executable command, while variable is a variable, so if we want to use alias as a variable, we should first define a variable of the same name.

#### auto-translate

!!!warning Don't use `~` as the user dir, since it can't be auto translated as the sub variable. e.g.

    ```sh
    export a10=~/android
    export n10=$a10/xxx
    ```

    The first `ls $a10`, and enter `TAB` is ok; while the `ls $n10` and enter `TAB` not, since it would translate to be `\~/android` which has an extra `\` before.

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1644305042688-43cf62d9c0740692f1a7192cbee01384ec36b1a6477f8094f3830d2544e9d091.png)

> sample

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1644293316229-a14a79513359e9dbe269db3bc46a7fb55d13405666920f93f4b2af131c52f298.png)

see: - [bash - Alias substitution for a string to use it in a terminal command - Ask Ubuntu](https://askubuntu.com/questions/364843/alias-substitution-for-a-string-to-use-it-in-a-terminal-command)

#### bugfix: alias in script file can't use in the outer shell

!!!warning We should use `source xx.sh` rather than `sh xx.sh` in order to make variables/aliases work in the outer shell since `sh` would create a sub shell while `source` not.

see:

- [(1 条消息) Linux source 命令解决 alias not found issue_hongchangfirst-CSDN 博客](https://blog.csdn.net/hongchangfirst/article/details/78912188)

- [How to set an alias inside a bash shell script so that is it visible from the outside? - Stack Overflow](https://stackoverflow.com/questions/2197461/how-to-set-an-alias-inside-a-bash-shell-script-so-that-is-it-visible-from-the-ou)

### incremental variable

```sh
var=$((var+1))

((var=var+1))

((var+=1))

((var++))
```

```sh
var=0

while true
do echo "seconds $((++var))"
sleep 1
done
```

![picture 48](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1644421784774-8ad0810a0e1de0e8ec8d02849ba64806d7bafbad9688161804d0c2865b839452.png)

ref:

- [How to increment a variable in bash? - Ask Ubuntu](https://askubuntu.com/questions/385528/how-to-increment-a-variable-in-bash)

### conditions

see: :sparkles::sparkles::sparkles: very good article: [Bash If Statements and Scripting - Linux Cheat Sheet | A Cloud Guru](https://acloudguru.com/blog/engineering/conditions-in-bash-scripting-if-statements)

```sh
# simple executing commands:
if [ $foo -ge 3 ]; then     # resolution 1
if test $foo -ge 3; then    # resolution 2

# check file existed
if [ -f regular-file ]; then

# check file readable
if [ -r readable-file]; then


```

#### sample of testing file readable and read

```sh
if [ -r somefile ];  then
    content=$(cat somefile)
elif [ -f somefile ]; then
    echo "The file 'somefile' exists but is not readable to the script."
else
    echo "The file 'somefile' does not exist."
fi
```

#### 在条件中执行某些语句要用 `(( CONDITION ))`

### how to auto input in command

#### auto input password for sudo commands

> sparkles: Use `sudo -S` to read input from stdin.

```sh
# no password / no secret for sudo
echo "$USER ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee -a /etc/sudoers.d/$USER 
```

ref:

- [shell - sudo with password in one command line? - Super User](https://superuser.com/questions/67765/sudo-with-password-in-one-command-line)

#### auto yes for some command (`yes | `)

```sh
# usage
yes | COMMAND

# example
yes | sh ./install.sh # e.g. install oh-my-zsh
```

ref:

- [linux - How do I script a "yes" response for installing programs? - Stack Overflow](https://stackoverflow.com/questions/7642674/how-do-i-script-a-yes-response-for-installing-programs/34176780)

#### auto yes for `apt` installing packages (`-y`)

Just add a `-y` in the command.

Example:

```sh
sudo apt install -y htop
```

ref:

- [apt-get install with --assume-yes is still prompting me to install dependencies - Ask Ubuntu](https://askubuntu.com/questions/448358/apt-get-install-with-assume-yes-is-still-prompting-me-to-install-dependencies)

### how to search commands by prefix (`history-search-backward/forward`)

```yaml
# ~/.inputrc

# Respect default shortcuts.
$include /etc/inputrc

# choice 1: recommended
"\e[A": history-search-backward     # arrow up      --> backward
"\e[B": history-search-forward      # arrow down    --> forward

# choice 2: if prefer to the page up/down
"\e[5~": history-search-backward    # page up       --> backward
"\e[6~": history-search-forward     # page down     --> forward
```

> ;warning: you should **Close and re-open all terminals for the new behavior to become effective.**

ref:

- https://askubuntu.com/a/59855

- [bash - Search for a previous command with the prefix I just typed - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/231605/search-for-a-previous-command-with-the-prefix-i-just-typed)

### how to repeat command

```sh
#  only show the last result
watch -n X command # X: X seconds; command may need quotes

# show all the result history
while true; do command; sleep X; done; # command may need quotes
```

ref:

- [bash - Repeat a command every x interval of time in terminal? - Ask Ubuntu](https://askubuntu.com/questions/430382/repeat-a-command-every-x-interval-of-time-in-terminal)

### how to use variable as multi args

```sh
# when there's only one arg as a variable, it's ok to directly use it, and the following two methods are equal
PACKAGE_TO_INSTALL="vim"
PACKAGE_TO_INSTALL=vim
sudo apt install -y $PACKAGE_TO_INSTALL

# However, if there are multi args as a variable, we need to use [`echo`](https://stackoverflow.com/a/30061925/9422455) to escape the 'hidden quotes' if I didn't understand wrongly. And also, the quotes can't be omitted, or use slashes.
PACKAGES_TO_INSTALL="vim git htop zsh terminator"
PACKAGES_TO_INSTALL=vim\ git\ htop\ zsh\ terminator
sudo apt install -y $(echo $INSTALLED_PACKAGES)

# Since the `echo` is not safe, another way is to use [`xargs`](https://stackoverflow.com/a/51242645/9422455), which seems more professional
PACKAGES_TO_INSTALL="vim git htop zsh terminator"
echo $PACKAGE_TO_INSTALL | xargs sudo apt install -y
```

ref:

- [string - Shell script - remove first and last quote (") from a variable - Stack Overflow](https://stackoverflow.com/questions/9733338/shell-script-remove-first-and-last-quote-from-a-variable)

- [bash send string argument as multiple arguments - Stack Overflow](https://stackoverflow.com/questions/30061682/bash-send-string-argument-as-multiple-arguments)

- [shell - Escaping quotes inside a quoted string - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/637496/escaping-quotes-inside-a-quoted-string)

- [BashFAQ/050 - Greg's Wiki](http://mywiki.wooledge.org/BashFAQ/050)

- [Bash variables with spaces - Stack Overflow](https://stackoverflow.com/questions/5819423/bash-variables-with-spaces)

- [shell script - How to assign a string with multiple spaces to a variable in bash? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/327784/how-to-assign-a-string-with-multiple-spaces-to-a-variable-in-bash)

- [Variable containing multiple args with quotes in Bash - Stack Overflow](https://stackoverflow.com/questions/7454526/variable-containing-multiple-args-with-quotes-in-bash)

### how to set an alias

#### resolution 1: in terminal

> :warning: this solution only works upon the next command, which can work immediately when executed in shell script file

```sh
# don't add any other characters after alias in order to catch bug
alias sed=gsed
```

#### resolution 2: write into `~/.bash_aliases`

```sh
# ~/.bash_aliases
alias update='sudo yum update'
```

> :warning: this solution needs to ensure the `.bash_aliases` enabled in `.bashrc`

![picture 47](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1643117544205-afe713493b26becfe498fda953bdc5c1d098accaf07b4e4b6b5e117b4d3671a1.png)

#### :sparkles: resolution 3: use `.bash_aliases` with `zsh`

Just add one line in `~/.zshrc`:

```sh
# ~/.zshrc
source ~/.bash_aliases
```

ref:

- [How to create a permanent Bash alias on Linux/Unix - nixCraft](https://www.cyberciti.biz/faq/create-permanent-bash-alias-linux-unix/)

#### unalias

```sh
# sample
unalias logout
```

ref:

- [How to Create and Use Alias Command in Linux](https://www.tecmint.com/create-alias-in-linux/)

### how to compare between outputs from two commands

```sh
diff <(ls old) <(ls new)
```

ref:

- [How do I diff the output of two commands? - Ask Ubuntu](https://askubuntu.com/questions/229447/how-do-i-diff-the-output-of-two-commands)

### how to check if a string contains another string

see:

- [How to Check if a String Contains a Substring in Bash | Linuxize](https://linuxize.com/post/how-to-check-if-string-contains-substring-in-bash/)

- [How to check if a string contains a substring in Bash - Stack Overflow](https://stackoverflow.com/questions/229551/how-to-check-if-a-string-contains-a-substring-in-bash)

#### using `==`

```sh
# resolution 1. using "=="
[[ $a == z* ]]   # True if $a starts with a "z" (wildcard matching).
[[ $a == "z*" ]] # True if $a is equal to z* (literal matching).

# resolution 2. using "==" when has spaces
[[ $a == "z a"* ]] # True if $a starts with a "z a"
```

> ref

- [In Bash, how can I check if a string begins with some value? - Stack Overflow](https://stackoverflow.com/questions/2172352/in-bash-how-can-i-check-if-a-string-begins-with-some-value)

#### :sparkles: using `grep`

e.g. if we want to match '-gen-index' as a pattern.

The `==` resolution may be as easy as: `[ $0 == -gen-index ]`

However, in `grep`, things came a little tricky.

```sh
# resolution 1. using regex with escape
grep '\-gen-index' <<< '-gen-index-xxx'

# resolution 2. using fixed string with forcing recognizing the following string as a pattern
grep -F -e '-gen-index' <<< '-gen-index-xxx'

# if we missed the `-e`, then it would cause error, since it supposes the `-g...` is args
```

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1643980881788-43e4da7276c3547c212039e614d0b5c98d293bf0074786099aad0c9e67578706.png)

> ref

- [bash - How to match a string containing the character "$" with grep? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/387408/how-to-match-a-string-containing-the-character-with-grep)

## linux accounts management

### how to create user

```sh
# create user with a home directory
sudo useradd -m {USERNAME}
ls -la /home/{USERNAME}


# create user [under root]
sudo useradd USERNAME

# create passwd [under root]
sudo passwd USERNAME

```

### how to log out

#### resolution 1 (11.10 and above)

```sh
gnome-session-quit
```

#### resolution 2

```sh
sudo pkill -u $USER
```

ref:

- [command line - How can you log out via the terminal? - Ask Ubuntu](https://askubuntu.com/questions/15795/how-can-you-log-out-via-the-terminal)

### set a shorter password for ubuntu

```sh
sudo passwd <USER>
```

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1642479990429-35424184b62d147dc0744f2bcb9bca97f27b9efc9df47373a458c76442b30003.png)

- ref:

  - https://askubuntu.com/questions/180402/how-to-set-a-short-password-on-ubuntu

## linux net management

### how to know my public ip address

- resolution 1:

```sh
# https://apple.stackexchange.com/questions/20547/how-do-i-find-my-ip-address-from-the-command-line
curl ifconfig.me
```

- resolution 2:

```sh
# https://www.digitalocean.com/community/tutorials/how-to-configure-remote-access-for-mongodb-on-ubuntu-20-04#:~:text=curl%20%2D4%20icanhazip.com
curl -4 icanhazip.com
```

### how to monitor network traffic

```sh
sudo apt install nethogs

sudo nethogs
```

ref:

- [networking - Network usage top/htop on Linux - Stack Overflow](https://stackoverflow.com/questions/368002/network-usage-top-htop-on-linux)

### FIXME: check proxy

In [Ubuntu 18.04.6 LTS (Bionic Beaver)](https://releases.ubuntu.com/18.04/), it introduced two methods to see what/which proxies are we using:

```sh
## approach 1
echo $http_proxy

## approach 2
env | grep -i proxy
```

However, when I configured the proxies in `Manual Proxy`, I am surprised to find nothing using either commands in the above, while the ping to `google.com` does work so that I use it as the measure then.

```sh
ping google.com
```

And another wield thing is before the system was restarted, the `env | grep -i proxy` even shows duplicated results and the change in `Manual Proxy` doesn't work, which is quite confusing.

Maybe we can do more tests later.

## linux date/time management

### how to format date

> :warning:
>
> 1. the space in formatter should be using `\ ` or anything other ways
> 2. `date`是一个函数，不是变量，变量采用`$XX`或者`${XX}`的形式，但是函数要用`$(XX)`，并且不能在字符串中

```sh
# directly output date
date +%Y-%m-%d\ %H:%M:%S

# output date into variable
T='the date is '$(date +%Y-%m-%d\ %H:%M:%S)
```

ref:

- [shell script - How to concatenate a date variable and string variable in unix? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/549415/how-to-concatenate-a-date-variable-and-string-variable-in-unix)

### how to change timezone (and time)

#### resolution 1 (conclusion): directly export

```sh
echo "export TZ='Asia/Shanghai'\n" >> ~/.profile

sudo pkill -u $USER --force
```

#### resolution 2 (detail): choose following directions

```sh
# check current time, as well as timezone
date -R

# if the ending is `+0800`, then it's ok, otherwise you need to change (e.g. `-0800`)

# change timezone (just choose as directed)
tzselect
```

And finally you will get a command suggestion to write into profile file, that is [#solution-1-directly-export](#solution-1-directly-export)

## linux system management

## FIXED: `apt-get /var/lib/dpkg/lock-frontend`

solution 01:

```sh
sudo rm /var/lib/dpkg/lock-frontend
sudo rm /var/lib/dpkg/lock
sudo rm /var/cache/apt/archives/lock
```

solution 02:

```sh
sudo lsof /var/lib/dpkg/lock-frontend
kill -9 XXX
```

ref:

- [解决 apt-get /var/lib/dpkg/lock-frontend 问题 - 知乎](https://zhuanlan.zhihu.com/p/126538251)

### :white_check_mark: `A stop job is running for Session c2 of user ... (1min 30s)`

> resolution

1. restart system
2. `journalctl -p5`
3. search `timed out. Killing`
4. analyze the target process of `Killing process 1234 (jack_thru) with signal SIGKILL.`

> :warning: 注意，也有其他几种解决方案，比如装`watchdog`和缩短`timeout`时间的，这些都侵入性太高了，并且不是治本之策，所以还是得从 log 来分析原因找对应政策。尤其是装`watchdog`的方案，我简单看了一下，大致是每分钟检查一下系统的情况，但问题是，为什么很久以前系统就没有这种问题呢？那个时候也没装 `watchdog` 啊，所以对于这个问题，我们不能偷懒!

.

> result

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-bugfix-1643550947015-7ed703f287400ec8593914f35740044149d43c47e7b97df89135a6ffff3681a5.png)

It tells me the last one is because of `adb`, since I do open the `adb` and not responding then.

And I also checked the last few times when `timed out`, but to find they are different.

So I confirmed the timeout error is temporary, since now I am not going to run any `adb`.

I tried to restart again, and the system does well which identified what I think.

> ref

- [systemd - A stop job is running for Session c2 of user - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/273876/a-stop-job-is-running-for-session-c2-of-user/297318)

- [用户的会话 c2 正在运行停止作业](https://qastack.cn/unix/273876/a-stop-job-is-running-for-session-c2-of-user)

- [systemd stop job for Session 2 on shutdown / Newbie Corner / Arch Linux Forums](https://bbs.archlinux.org/viewtopic.php?id=264233)

## Linux commands

see [linux-commands](linux-commands.md)

## Linux Is Awesome

### awesome discussions

- [How do I parse command line arguments in Bash? - Stack Overflow](https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash/14203146#14203146)

### awesome design philosophy

1. `cd .`, when directory re-created
2. `perl/sed sX..X..X`, arbitrary splitter, easy to handle especially multi-lines problem
