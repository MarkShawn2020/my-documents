---
tags: [开发笔记, Linux]
---

# 编程 | Linux 笔记

> 很久以前，自打我刚开始学计算机，就有一个认知：精通 linux 的人都是大神。
>
> 但，我是不需要学的。
>
> 很长一段时间，我都是这么认为的。
>
> 直到这两年，我选择了 Mac 作为自己的主力开发工具，两年的摸爬滚打，尤其是始于对`iTerm + zsh + oh-my-zsh`颜值的惊艳，到现在能够在 mac、ubuntu、centos、windows 等各大操作系统之间自如切换，并逐渐意识到命令行系统对于现代操作系统的重要性，命令行熟练度对于提升工作效率的重要性，我知道，我已经走向了一条与计算机越来越近的不归路。
>
> 而这一切中间的桥梁，正是 linux，于我而言，不认识不掌握 linux，不可谓入了程序的真正世界。
>
> 因此，本系列第一篇，献给 linux，一方面是致敬我心中曾经那触不可及的信仰，另一方面也是为了能重新认识它，对它说一句它可能真正想听的："hello linux, I'm mark"。
>
> 因为每一个 linux 的学习者最后都会发现，linux 并不神秘，而 linux 真正启迪人的，是它的设计哲学，与对你工作流的重塑。
>
> 在此，我斗胆把 python 之禅搬于此，因为在我心中，它于 linux，是心有灵犀，同样适用：
>
> ![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_core-notes-of-linux-1643723806431-00b5b858aa9372ebc4b9dfc37178554d0d0d4eb62c854edb6cd2385e15333e07.png)

## 首先，linux 是什么

作为南川的核心开发笔记（从实际工作经验中提炼出来的笔记），我无意过多展开一些基本的背景介绍，因此也不会花时间去讲述 linux 和 unix 和 mac 之间的关系，这些读者们都可以很方便地在互联网找到答案。

我只简单地如下描述，目前用于个人使用的电脑系统，主要分为 windows 和 mac。

windows 的最大优点，是价格相对平民，生态丰富，交互习惯最符合人类直觉。

mac 的最大优点，是审美一流，做工一流，触控板和屏幕天花板的存在，然后于我而言最大的优点，是其 unix 系统，可以允许我像 linux 一样方便地使用命令行。

所以，我在使用了五年的 windows 后，毅然投入了 mac 的怀抱，而其中的目的之一，就是为了更好地掌握 linux。

（当然，纯粹使用 linux 我是不会接受的，我还是觉得追求审美也是生活中很重要的一部分，于是乎，~~我现在已经极其极其不想看到任何 windows 的界面~~）

说了这么多，还是没说 linux 是什么。

没错，就应该这样，这篇是核心开发笔记，非核心的，可以出门右转某乎，比如：

- [(19 封私信 / 67 条消息) 作为开发者，你更喜欢用 macOS、Linux 还是 Windows 操作系统？为什么？ - 知乎](https://www.zhihu.com/question/434914458/answer/1664277013)
- [(19 封私信 / 67 条消息) Linux 各大发行版有什么特色？ - 知乎](https://www.zhihu.com/question/24261540/answer/80418621)

PS: 以上链接，我都没有看过，只是随手一搜。:smile:

## 其次，如何拥有一台 linux

有很多种方法。

如果你是 windows 10+用户，最方便的方法，是基于内置的`wsl`系统，不知道是什么？出门右转。

至于内置的`wsl`会不会有什么限制和性能损耗？这个我也不知道，我不用，如果你知道，欢迎留言，我还挺想知道的，只要你愿意留我就愿意听，并且可能会影响我接下来的认知。

但我不会因为这个出门右转，我已经为了给大家示范如何出门右转，已经出门一次了，寒冬腊月，怪冷的。

这是其一。

其二，装一个双系统。

我一直想装个双系统，并且尝试到了最后一步，因为工作需要。当时我给我的 mac 装 ubuntu 的双系统，结果到了安装界面，鼠标和键盘没有响应，查了查好像我的版本 mac 2020 pro 的鼠标和键盘不走 usb，而是总线？

不清楚，后续我可能会继续尝试装个双系统，目前我用的是虚拟机。

PS：友情提示，小白不要轻易尝试双系统，容易留下不学无术后悔的泪。

其三，装一个虚拟机，比如`vmware`或者`virtual box`。两个都尝试下来，个人比较喜欢`vmware`。

至于怎么装，怎么配置，出门右转，或者等我后续系列，会有虚拟机/双系统专刊的，应该（如果不懒的话）。

我目前的虚拟机（内部运行的 ubuntu，可以同时运行多个操作系统）界面如下：

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_core-notes-of-linux-1643725375163-c76c9d50a6632d532665d3bbbffb45379f7a72060170528ffbba377ad4a0d461.png)

其四，阿里云/腾讯云/华为云/亚马逊云……租一个 linux 服务器或者操作系统等。这是业界搭建后端必备。我之前一直用的阿里云/腾讯云，因为以前做全栈多一些。

目前市面上，服务端应该用 centos 比较多，客户端应该用 ubuntu 比较多，主要原因可能是 centos 默认没有界面，程序较为稳定；ubuntu 的界面很好看，比较适合个人鼓捣。

我目前使用的 ubuntu 界面如下：

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_core-notes-of-linux-1643725414611-b8cc4126f345748e9f692843738ed6d80aa61c82103b1321308468c70443c356.png)

这里值得注意的是，有一些企业可能购置了类似于 windows server 之类的服务端，这种本质上还是 windows 系统，不是 linux 系统，只不过一直跑在公司网络上。

所以当我们谈到服务器的时候，可能并不一定是 linux 系统，这是值得注意的。

我为啥知道这玩意呢，因为之前碰到一个项目是这样的，我本来写好的 linux 的后端，想着直接移到目标公司网上，结果一看，windows server，把我给整不会了。

## 接着，如何登录 linux

理论上，登录这个动作，不应该是个问题，但那仅限于是登录自己的本地的每天都用的电脑。

linux 一般都是在服务端的，一般涉及到远程访问，所以通用做法是用`ssh`。

基本的 ssh 用法出门右转即可，本文只记录如何免密登录 ssh。

因为 ssh 默认每次都会输入密码，很不畅快。更严重的是，如果涉及到写批运行脚本，则密码输入会成为脚本杀手，至少会让脚本更难理解，出错概率更高。

很简单，第一步，先`ssh USERNAME@SERVER`，其中`USERNAME`和`SERVER`是目标服务器的用户名和 IP 地址（或者域名，如果有的话）。

一般，默认的`USERNAME`是`root`，密码也是`root`，虽然这很不推荐，不安全，但对于新手却是很友好。

尽管我的密码更简单，简单到你会拍案惊奇。

当你第一次`ssh`之后，会在本机的当前用户文件夹下（mac 和 linux 都是`~`文件夹，windows 是`C:\\Users\\XXX`）生成一个`.ssh/id_rsa.pub`，这是公钥。

这个文件的内容，涉及到了 rsa 算法等密码学相关内容，不展开。而你要做的，就是把里面的文本复制，粘贴到目标服务器的`~/.ssh/authorization_keys`文件内（如果文件不存在，则新建；如果文件已有内容，则另起一行，补在后面即可）。

以下给出一键脚本：

```sh
USERNAME="xxx"
SERVER="xxxxx"
file="id_rsa.pub"

scp ~/.ssh/$file $USERNAME@$SERVER:
ssh $USERNAME@$SERVER
cat $file >> .ssh/authorized_keys
rm $file
```

这个脚本里的`scp`是在本地与服务器之间交换文件的意思，最后一个冒号表示当前文件夹，而`$USERNAME@SERVER`即目标服务器的用户文件夹，这就对上了。

`cat`是读取所有文本内容到输出流，`>>`是把输出流内容添加到目标文件的末尾。

`rm`是删除，这里代表传送的`file`是一个中转文件的意思，为啥要中转，你猜。

最后，为了防止`ssh`超时断开，可以在本地（客户端）的`ssh`配置文件中补一下以下配置，这样每分钟发送一次消息给服务端，服务端就不会主动清理客户端了。相信我，如果不解决这个问题，后续你会很头疼的。

```yaml
# /etc/ssh/ssh_config
HOST: *
	ServerAliveInterval 60
```

## 最后，如何掌控 Linux，以下给出一部分经验笔记

## -------------------------------------

## BEST-PRACTICE: ubuntu initialization

### step 0. install

- [Ubuntu 18.04.6 LTS (Bionic Beaver)](https://releases.ubuntu.com/18.04/)

### step 1. config apt source

#### 1. change apt source

ref:

- [【Ubuntu】Ubuntu 18.04 LTS 更换国内源——解决终端下载速度慢的问题 - 知乎](https://zhuanlan.zhihu.com/p/61228593)

##### fastest/script way: 直接修改`/etc/apt/sources.list`

~~其中，第一种方案虽然可行，但是有两个缺点，一个是侵入性高，所以一般都会先备份一下原文件，然后使用替换命令。~~

Update 2022-01-24：实际上所有方式底层都是通过修改 apt sources.list 文件配置的，所以没有什么侵入性一说，都会先做备份。

GUI 版（也就是`softwares & update` app 里会提供测试，自动修改，改完之后触发更新操作，而这些其实可以自己用脚本完成，响应也更快！

```sh
# backup source file
APT_SOURCES_LIST_FILE=/etc/apt/sources.list
cp $APT_SOURCES_LIST_FILE $APT_SOURCES_LIST_FILE.bak

# change source
APT_SOURCE="http://mirrors.yun-idc.com/ubuntu/"
sudo sed -i  "s|deb \S+|deb $APT_SOURCE|g" $APT_SOURCES_LIST_FILE

# update source
sudo apt update
```

另一个就是，只能填入自己想填的源，但很可能不是最好的源。比如我一直以为阿里云的源很好，结果这次发现，极其地慢，我确认在`update`时走的是`cn.xxx`，但依旧只有十几 k。

##### robustest/recommend-for-newbie way: 在`softwares & update`里修改 server

第二种办法就是在`softwares & update`里自动测试最好的服务器，然后选择它。我测出来是`yun-idc`最好，但是因为我没用过，所以当时没考虑它，后来被阿里云折磨的不行了，就试了它，结果飞快，十兆每秒！

##### use others way: 使用别人写好的 git 仓库进行配置

第三种办法，由于我还没配好源，所以也没 git，而此时下载 git 又会极其地慢，所以也不考虑。

#### 2. update apt

!!!tip If the following commands warn that files are locked, then wait for some minutes, or use `lsof FILE` to have a check, more refer to: - [解决 apt-get /var/lib/dpkg/lock-frontend 问题 - 知乎](https://zhuanlan.zhihu.com/p/126538251)

```sh
sudo apt get update
sudo apt get upgrade
```

### step 2. config git

```sh
sudo apt get git
git config --global user.name YOUR_NAME
git config --global user.email YOUR_EMAIL
```

### step 3. config terminal

### step 4. config language

#### resolution 1: config chinese input source via ibus

ibus 输入方式和搜狗输入法之间不是很兼容，如果出现两者都无法输入中文的情况，建议根据[Ubuntu 18.04LTS 安装中文输入法以及快捷键设置 - 简书](https://www.jianshu.com/p/c04a4b03d30f)先卸载搜狗输入法，确认 ibus 是可以用的，具体就是：`sudo apt-get remove fcitx*`

确认以下配置：

1. 设置 - 地区与语言 - 输入法，中要添加包含智能拼音：

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642268594063-def6bf87b276425161475a3ce55fbb05d8bb305b913ae5b39cc6e9708a6e32ae.png" />

2. 语言支持中，要启用 ibus 方案

   <img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642268691854-043dc8408c8326d13213bc92302c26f2d85b2be6a2892dbc58cf3d3349c9c8bc.png" />

   注销账号重新登录即可。

3. 如果注销账号还不行， 就要尝试`sudo reboot`一下。

#### FIXME: resolution 2: config chinese input source via sougou

虽然按照官网走了好几遍，但始终还是没有配成这套方案，我也不知道什么原因。

而且 ibus 方案也必须在 fcitx 卸载之后才能正常使用。

参考官网：

- [搜狗输入法 for linux](https://pinyin.sogou.com/linux/)

更新：确保：

1. 输入源中只有一个英文（不要有 ibus 的中文，否则会干扰）

<img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642273187873-a0b1b31105b8e9fdea3ea0c576bc3e81e15cd6dec9c1dfb55a43d3a64ece559d.png" />

2. 输入系统用`fcitx`

<img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642273215269-68b870e74dbe7fecdac78268144d73dc987602eddc24098c4e10763b540eb6bb.png" />

再更新：算了吧，我个人觉得搜过 ubuntu 的 bug 是真地多，一会能用一会不能用，尤其是我在调成中文版能用后又调成英文版，然后用不了了，接着再怎么调中文版都用不了了，非常蛋疼。

#### how to switch language input source

The best way is to directly install the Chinese version of ubuntu, since the Chinese feature is built-in.

However, what we download directly from the official ubuntu website, may not support chinese choice natively. So it highly depends on what distribution version of ubuntu we download.

ref:

- [(20 条消息) ubuntu 切换中文输入法\_*g_y*的博客-CSDN 博客\_ubuntu 切换中文输入法](https://blog.csdn.net/qq_31290747/article/details/94555163)

#### how to change language to english

```sh
echo export LANGUAGE=en_US.UTF-8 |  sudo tee -a ~/.bashrc
```

ref:

- [command line - How do I change the language via a terminal? - Ask Ubuntu](https://askubuntu.com/questions/133318/how-do-i-change-the-language-via-a-terminal)

### IMPROVE: a script to init ubuntu (may not work)

```sh
"
version: 0.0.3
features:
    1. disable sudo password so running commands faster
    2. disable apt password so installing packages faster
    3. enable arrow up/down to backward/forward search prefix command
    4. auto change deb(apt) source
    5. auto install zsh, config oh-my-zsh, set as the default shell, you may need to switch to bash when build android in case of errors, it's easy just to input `bash` in terminal
    6. re-login to make these changes work
"

# !IMPORTANT: config global variables
PASSWORD=" "

# --- step 1 ---
# write password variable into bash_profile
echo "export PASSWORD=$PASSWORD" >> ~/.bash_profile
source ~/.bash_profile

# disable sudo password, ref: https://askubuntu.com/a/878705
echo "$USER ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee -a /etc/sudoers.d/$USER

# --- step 1.5 ---
# enable backward/forward prefix commands search
echo '"\e[A": history-search-backward
"\e[B": history-search-forward' >> ~/.inputrc
bind -f ~/.inputrc

# --- step 1.7 ---

# change timezone, so that time display ok
echo "export TZ='Asia/Shanghai'" >> ~/.profile # need relogin

# --- step 2 ---
# update apt and install packages

# change apt source
APT_SOURCE="http://mirrors.yun-idc.com/ubuntu/"
APT_SOURCES_LIST_FILE=/etc/apt/sources.list
sudo sed -i.bak -r  "s|deb \S+|deb $APT_SOURCE|g" $APT_SOURCES_LIST_FILE

echo "Y" | sudo apt update # need confirm but skipped since configured
echo "Y" | sudo apt upgrade

INSTALLED_PACKAGES="vim git htop zsh terminator"
echo $INSTALLED_PACKAGES | xargs sudo apt install -y

# --- step 3 ---
# modify timezone (need relogin)

export "TZ=Asia/Shanghai'\n" >> ~/.profile

# --- step 4 ---
# configure zsh (installed in \$INSTALLED_PACKAGES) / oh-my-zsh

# install oh-my-zsh (built-in backward search)
wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh
yes | sh install.sh

# --- step 5 ---
# diy zsh based on 'oh-my-zsh'

# add dynamical time display
echo "setopt PROMPT_SUBST
PROMPT='%B%F{yellow}[%D{%L:%M:%S}]%f:%F{green}\${\${(%):-%~}}%f$ %b'
" >> ~/.zshrc

# set zsh as the default terminal (need relogin!)
sudo chsh -s $(which zsh) # after configed sudo, no need to input password

# enable zsh changes
exec zsh

# --- step 6 ---
# re-login
sudo pkill -u $USER
```

## BEST-PRACTICE: linux connection (`ssh`)

### ssh generate public keys

ref: https://git-scm.com/book/en/v2/Git-on-the-Server-Generating-Your-SSH-Public-Key

```sh
mkdir -p ~/.ssh
cd ~/.ssh
ssh-keygen -o
```

### ssh no secret/password

It's easy that if only you generate a `id_rsa.pub` and `scp` to your `~/.ssh/authorization_keys` then things all done.

#### Solution 1

```sh
username="xxx"
server="xxxxx"
file="~/.ssh/id_rsa.pub"

# command
cat $file | ssh $username@$server "cat - >> ~/.ssh/authorized_keys"

# sample
cat $file | ssh aosp@192.168.1.242 "cat - >> ~/.ssh/authorized_keys"
```

#### Solution 2

```sh
username="xxx"
server="xxxxx"
file="~/.ssh/id_rsa.pub"

scp $file $username@$server:
ssh $username@$server
cat $file >> .ssh/authorized_keys
rm $file
```

ref:

- [How to use the Linux ‘scp’ command without a password to make remote backups | alvinalexander.com](https://alvinalexander.com/linux-unix/how-use-scp-without-password-backups-copy/)

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

## BEST-PRACTICE: linux env management

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

## BEST-PRACTICE: linux file system management

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

### how to show absolute path of file from relative

I cannot use `brew install realpath` like their `apt install realpath`, but I can use `realpath`, which may be pre-built-in.

Plus, later I saw that maybe realpath is a submodule of mac package, which is named as `findutils`.

```sh
realpath FILE
```

ref:

- [bash - How to retrieve absolute path given relative - Stack Overflow](https://stackoverflow.com/questions/4175264/how-to-retrieve-absolute-path-given-relative)

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

## BEST-PRACTICE: linux disk management

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

## BEST-PRACTICE: linux shells management

ref:

this article is enough and recommended:

- [How To Change Shell To Bash in Linux / Unix - nixCraft](https://www.cyberciti.biz/faq/how-to-change-shell-to-bash/)

- [How to find list of available shells by command-line? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/140286/how-to-find-list-of-available-shells-by-command-line)

- [How do I find out what shell I am using on Linux/Unix? - nixCraft](https://www.cyberciti.biz/tips/how-do-i-find-out-what-shell-im-using.html)

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

### set zsh as the default terminal (need re-login)

```sh
chsh -s $(which zsh)
```

https://askubuntu.com/questions/131823/how-to-make-zsh-the-default-shell

## BEST-PRACTICE: linux terminal management

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

## BEST-PRACTICE: linux commands management

> :warning:
>
> 1. be careful to use `\`` in terminal / shell since it's would be treated as executable commands: <img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-hwoto-1641501462043-6790c46051fa5db1246b560e795c5b1737d5e508faf7a9247b1c52e1ce4abdbc.png" />  
>    see: [(20 条消息) shell 基础知识-echo 及单引号、反引号和双引号详解\_Luckiers 的博客-CSDN 博客\_echo 单引号和双引号](https://blog.csdn.net/Luckiers/article/details/103501168)

### how to auto input in command

#### auto input password for sudo commands

> sparkles: Use `sudo -S` to read input from stdin.

```sh
# sample
echo "$USER ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee -a /etc/sudoers.d/$USER
```

ref:

- [shell - sudo with password in one command line? - Super User](https://superuser.com/questions/67765/sudo-with-password-in-one-command-line)

#### auto yes for some command (`yes | `)

```sh
# usage
yes | COMMAND

# example
yes | sh ./install.sh # install oh-my-zsh
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

## BEST-PRACTICE: linux accounts management

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

## BEST-PRACTICE: linux net management

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

## BEST-PRACTICE: linux date/time management

### how to format date in terminal

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

## BEST-PRACTICE: linux system management

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

## -----------------------------------

## BEST-PRACTICE: linux common commands

### command:tar

```sh
# x: extract, f: file
tar -xf FILE

# v: verbose, logging output, careful when extracting big files, e.g. AOSP
tar -vxf FILE
```

ref:

- [How to Extract (Unzip) Tar Gz File | Linuxize](https://linuxize.com/post/how-to-extract-unzip-tar-gz-file/)

### command:perl

#### how to use perl to replace multi-lines

```sh
perl -0pe 's/search/replace/gms' file
```

1. `-0`: without the `-0` argument, Perl processes data line-by-line, which causes multiline searches to fail.
2. `-p`: loop over all the lines of a file
3. `-e`: execute the following arg as a perl script
4. `/s`: changes the behavior of the dot metacharacter `.` so that it matches any character at all. Normally it matches anything except a newline "\n", and so treats the string as a single line even if it contains newlines.
5. `/m`: modifies the caret `^` and dollar `$` metacharacters so that they match at newlines within the string, treating it as a multi-line string. Normally they will match only at the beginning and end of the string.
6. `/g`: global replace(not sure)

ref:

- explaining `-0`: [Multiline search replace with Perl - Stack Overflow](https://stackoverflow.com/questions/1030787/multiline-search-replace-with-perl)

- explaining `/m | /s`: [regex - Understanding Perl regular expression modifers /m and /s - Stack Overflow](https://stackoverflow.com/questions/22962588/understanding-perl-regular-expression-modifers-m-and-s)

special thanks to: [Not sure if you know, but sed has a great feature where you do not need to use a / as the separator.](https://unix.stackexchange.com/a/378991)

- [perl man page - perl-interpreter - General Commands](https://www.mankier.com/1/perl#Description)

- [perl - Replace multi line string with multi line string without escaping by hand - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/555948/replace-multi-line-string-with-multi-line-string-without-escaping-by-hand)

- [Perl 正则表达式 | 菜鸟教程](https://www.runoob.com/perl/perl-regular-expressions.html)

- [quoting - find and replace with sed with slash in find and replace string - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/378990/find-and-replace-with-sed-with-slash-in-find-and-replace-string)

### command:find

#### how to ignore case

```sh
find -iname
```

ref:

- [Find command: how to ignore case? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/32155/find-command-how-to-ignore-case)

#### how to specify search type

Use `-type` to specify the search type (default is `c` for `file`), here I used `d` for `directory`, ref: [find type](https://man7.org/linux/man-pages/man1/find.1.html#:~:text=true%20%20Always%20true.-,%2Dtype%20c,-File%20is%20of)

And then, when I search directory, it would search all the sub-folders with '/' concatenated, so I need to specify `-d 1` in order to only search the top current directory.

```sh
➜  Application Support find . -name '*electron*' -type d -d 1
./electron-react-boilerplate
./electron-react-typescript
➜  Application Support rm -rf electron-react-boilerplate
➜  Application Support rm -rf electron-react-typescript
```

#### how to exclude dir

TODO: in fact, I really can't catch why `-prune` is combined with `-o` (or)

```sh
# 1. use `-not -path`
find -name "*.js` -not -path "./directory/*"

# 2. use `-path xx -prune`
find . -path ./misc -prune -o -name '*.txt' -print

# 3. use multiple prune (need to add escaped bracket)
find . -type d \( -path ./dir1 -o -path ./dir2 -o -path ./dir3 \) -prune -o -name '*.txt' -print

# 4. use regex prune (-name)
find . -type d -name node_modules -prune -o -name '*.json' -print
```

ref:

- [linux - How to exclude a directory in find . command - Stack Overflow](https://stackoverflow.com/questions/4210042/how-to-exclude-a-directory-in-find-command)

#### TODO: how to find file with time used

#### tip: find efficiency comparison

Use a specified directory is the best and fastest;

If not, limit the `maxdepth` to a number small enough is also ok;

And then consider the directory prune.

Finally bared run is the worst.

```sh
➜  hjxh_express_match git:(main) time find .imgs  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find .imgs -name   0.00s user 0.00s system 52% cpu 0.005 total

➜  hjxh_express_match git:(main) time find . -maxdepth 3  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 3 -name   0.01s user 0.05s system 70% cpu 0.079 total

---

➜  hjxh_express_match git:(main) time find . -maxdepth 4  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 4 -name   0.06s user 0.69s system 87% cpu 0.854 total

➜  hjxh_express_match git:(main) time find . -maxdepth 5  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 5 -name   0.14s user 1.86s system 93% cpu 2.137 total

➜  hjxh_express_match git:(main) time find . -maxdepth 6  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 6 -name   0.26s user 3.21s system 94% cpu 3.683 total

---

➜  hjxh_express_match git:(main) time find .  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -name   0.44s user 5.85s system 51% cpu 12.172 total

➜  hjxh_express_match git:(main) time find . -path './.imgs/*'  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -path './.imgs/*' -name   0.46s user 5.93s system 51% cpu 12.299 total

➜  hjxh_express_match git:(main) time find . -path './.imgs/*'  ! -path "**/node_modules/*"  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -path './.imgs/*' ! -path "**/node_modules/*" -name   0.46s user 5.91s system 51% cpu 12.268 total

```

### command:grep

#### how to exclude dir (`--exclude-dir=dir`)

Recent versions of GNU Grep (>= 2.5.2) provide:

`--exclude-dir=dir`

which excludes directories matching the pattern dir from recursive directory searches.

So you can do:

```sh
grep -R --exclude-dir=node_modules 'some pattern' /path/to/search
```

ref:

- [linux - How can I exclude directories from grep -R? - Stack Overflow](https://stackoverflow.com/questions/6565471/how-can-i-exclude-directories-from-grep-r)

#### how to limit depth (`-maxdepth`)

```sh
 find . -maxdepth 4 -type f -exec grep "11.0.0_r1" {}  \;
```

ref:

- [How to do max-depth search in ack and grep? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/111722/how-to-do-max-depth-search-in-ack-and-grep)

#### tip: grep by lines context is MUCH FASTER than grep by words context, and even better for output

```sh
➜  erb git:(main) ✗ time (cat release/build/mac/皇家小虎快递分析系统.app/Contents/Resources/app/dist/main/main.js | tr ";" "\n" | grep --context=3 'fake-database')
# var n=this&&this.__importDefault||function(e){return e&&e.__esModule?e:{default:e}}
# Object.defineProperty(t,"__esModule",{value:!0}),t.isDbFinished=t.initDbUpdateResult=t.initDbInsertResult=t.DB_UPDATE_DECLINED=t.DB_UPDATED=t.DB_INSERT_DUPLICATED=t.DB_INSERT_SUCCESS=t.DB_UNKNOWN=t.DB_TIMEOUT=t.DB_TABLE_NOT_EXISTED=t.prisma=void 0
# const i=r(72298),a=`file:${n(r(71017)).default.join(i.app.getPath("userData"),"express_match.sqlite.db")}?connection_limit=1`
# process.env.DATABASE_URL=a,console.log({__dirname,rawDBPath:"file:dev.db?connection_limit=1",newDBPath:a}),t.prisma={erp:{create:()=>{console.log("fake-database: creating one")},findMany:()=>{console.log("fake-database: finding many")},upsert:()=>{console.log("fake-database: upserting one")}}},t.DB_TABLE_NOT_EXISTED="DB_TABLE_NOT_EXISTED",t.DB_TIMEOUT="DB_TIMEOUT",t.DB_UNKNOWN="DB_UNKNOWN",t.DB_INSERT_SUCCESS="DB_INSERT_SUCCESS",t.DB_INSERT_DUPLICATED="DB_INSERT_DUPLICATED",t.DB_UPDATED="DB_UPDATED",t.DB_UPDATE_DECLINED="DB_UPDATE_DECLINED"
# t.initDbInsertResult=()=>({nTotal:0,nInserted:0,nDuplicated:0,nTimeout:0,nUnknown:0,nTableNotExist:0})
# t.initDbUpdateResult=()=>({nTotal:0,nUpdated:0,nDropped:0,nTimeout:0,nUnknown:0,nTableNotExist:0})
# t.isDbFinished=e=>{let t=0
( cat  | tr ";" "\n" | grep --color=auto  --context=3 'fake-database'; )  0.20s user 0.01s system 121% cpu 0.169 total
```

```sh
➜  erb git:(main) ✗ time ( grep -iEo '.{255}fake-database.{255}' release/build/mac/皇家小虎快递分析系统.app/Contents/Resources/app/dist/main/main.js | tr ';' '\n' )
# =`file:${n(r(71017)).default.join(i.app.getPath("userData"),"express_match.sqlite.db")}?connection_limit=1`
# process.env.DATABASE_URL=a,console.log({__dirname,rawDBPath:"file:dev.db?connection_limit=1",newDBPath:a}),t.prisma={erp:{create:()=>{console.log("fake-database: creating one")},findMany:()=>{console.log("fake-database: finding many")},upsert:()=>{console.log("fake-database: upserting one")}}},t.DB_TABLE_NOT_EXISTED="DB_TABLE_NOT_EXISTED",t.DB_TIMEOUT="DB_TIMEOUT",t.DB_UNKNOWN="DB_UNKNOWN",t.DB_INSERT_SUCCESS="D
( grep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox} -iEo  t)  3.27s user 0.01s system 99% cpu 3.279 total

```

#### tip: grep by negative captured group needs to use `ggrep`

Examples Given the string foobarbarfoo:

```sh
bar(?=bar)     # finds the 1st bar ("bar" which has "bar" after it)
bar(?!bar)     # finds the 2nd bar ("bar" which does not have "bar" after it)
(?<=foo)bar    # finds the 1st bar ("bar" which has "foo" before it)
(?<!foo)bar    # finds the 2nd bar ("bar" which does not have "foo" before it)
```

You can also combine them:

```sh
# finds the 1st bar ("bar" with "foo" before it and "bar" after it)
(?<=foo)bar(?=bar)
```

ref:

- [lookaround - Regex lookahead, lookbehind and atomic groups - Stack Overflow](https://stackoverflow.com/questions/2973436/regex-lookahead-lookbehind-and-atomic-groups)

```sh
grep -Pio '(?<=heads\/)(.*?)(?=\n)' text.txt # P option instead of E
```

ref: https://stackoverflow.com/a/45534127/9422455

### command:tree

#### how to display chinese (`-N`)

```sh
tree -N
```

ref:

- [(23 条消息) linux 下 tree 命令中文字符乱码解决方案\_cxrsdn 的博客-CSDN 博客\_linux tree 中文](https://blog.csdn.net/cxrsdn/article/details/100006348)

#### how to exclude dir(`-I`)

```sh
# use `|` to split choices

# exclude
tree -I "XXX|YYY"   # maybe it means 'ignore'
```

ref:

- [tree command for multiple includes and excludes - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/61074/tree-command-for-multiple-includes-and-excludes)

### command:head

#### head basic usage

head 这个命令行其实没有什么要讲的，用法非常简单。

```sh
# output the first 5 lines (default)
head FILE

# output the first N lines (replace "N")
head -n "N" FILES
```

#### how to exclude the last k rows

但是今天 2022-01-26 碰到了一个问题，就是要获取前 n-1 行，然后试了 stackoverflow 上的方案好像都不对。

```sh
head -n -1 FILE
```

后来才知道，是因为 mac 的原因，要用`ghead`才行……

```sh
brew install coreutils
ghead -n -4 main.m
```

而 `ghead` 是在 `coreutils` 里面，这个名字一看我就有，所以也不用装了。

ref:

- [shell - head command to skip last few lines of file on MAC OSX - Stack Overflow](https://stackoverflow.com/questions/16206507/head-command-to-skip-last-few-lines-of-file-on-mac-osx)

#### discuss: use `head` or `sed`

今天之所以用到 head 其实是因为我想对一个流做 sed 处理，但略去最后一行。

我一开始想用 sed 里的范围标识（地址），但一直没试出来。

后来我把地址标识换成最简单的`1,4s/find/replace/`之后才意识到，我的思路是不对的。

`1,4`是一个确实被处理的范围选择，但结果就是，N 行中，前四行都被 sed 替换了，但是后面的行尽管没替换依旧会打印出来，而这正是 sed 的默认行为，它是一个流转换器。

那如果纯粹基于 sed，进行转换，并且去掉最后一行，就要用到`-o`结合好像是`/p`的 identifier，具体我也记不大清了。意思就是输出所有被匹配的行，但如果这样的话被匹配的行就会输出两遍了（两遍不必相同（NOT-SURE），一个是转换前，一个是转换后），所以另一个标识符就是阻止原内容的输出，这样就只输出匹配的行的处理结果。

所以，这个思路其实有问题，它可以对，也可以不对，它如果保证匹配 n-1 行，则对；否则就不满足需求了，我们的需求是处理前 n-1 行，并且不管匹配不匹配，都要输出，尽管实际上是都匹配的。

总之，理解到这层后，既可以用纯 sed 的方案，也可以用 head+sed 的方案，一个负责改，一个负责删即可，至于先后，结果都一样，也许 head 在前效率会更高一些。

所以，还是挺有意思的，这个。

### command:top

Today(2022-01-27) I finally understood how to use the command of `top` (though `htop` is better for display but possibly more costly).

![picture 88](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643248016619-b1ac7d3bcd2a9eb546a53a0e5da199d11d573f85a61a9317d679d002d98012fa.png)

I can switch the display format of memory usage when `top` has gone to the interactive interface.

The first option I can use is `E`, which allows to switch memory unit between `KiB | MiB | GiB | TiB`.

And the second option I can use is `m`, which switches the memory display type between pure text, columns graph and block graph.

> :warning:
>
> 1. 不可以在命令行中直接用 `top -M` （显示以`MB`为单位的内存使用量），因为`top -h`的帮助中写的很清楚，只支持部分选项。在 stackoverflow 上有 `top -M` 的建议(see: [linux - How to display meminfo in megabytes in top? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/105908/how-to-display-meminfo-in-megabytes-in-top))，但可能我的版本（Ubuntu 18）不支持。正确的做法，是先进入`top`交互界面，然后按`E`，这样就会切换单位，比如按两次切换到`GB`单位。另外，独立的，还可以按`m`去切换内存的显示样式，比如像`htop`那种竖条状！
> 2. 以上只在 ubuntu 上测试通过，在 mac 上我刚试了，不行！所以到底怎么用命令，还得根据平台自身！
> 3. 具体的，可以通过 `COMMAND -h`去看简洁版的帮助页面，或者`man COMMAND` (e.g. [Ubuntu Manpage: top - display Linux processes](https://manpages.ubuntu.com/manpages/bionic/en/man1/top.1.html)) 去看完整版的帮助页面！

### command:cat

#### how to write raw string into file using `cat`

```sh
# example
GOPATH=$HOME/my-go
cat <<EOF >> ~/.profile
export GOPATH=$GOPATH
export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
EOF
```

ref:

- [linux - How does "cat \<\< EOF" work in bash? - Stack Overflow](https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash)

#### usage: how to know what's the bash string

When using `bash` or `zsh`, we are supposed to use the function of `bindKey`.

However, the key we typed are always hard to remember, e.g. what's the `ctrl` key?

Luckily, there's a super easy (and also interactive) way for us to know it via `cat`, just to type `cat` followed by `enter` in terminal, and then the terminal would display what the character would be when we typing them.

E.g. here is what's the result when we combine `control | option | command` with arrow left and arrow right would be:

![picture 114](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643287045491-0d652ec4cf50fd00bdfe265d1bcbc4df4482ffc562e30624d26218fd2d841adf.png)

### command:Unzip

#### how to unzip to specific directory

```sh
unzip file.zip -d TARGET_DIR
```

ref:

- [bash - How to unzip into a given directory - Ask Ubuntu](https://askubuntu.com/questions/994611/how-to-unzip-into-a-given-directory)

### command:kill

```sh
 ps aux  |  grep -i  electron |  awk '{print $2}'  |  xargs sudo kill -9
```

ref:

https://stackoverflow.com/a/30486159/9422455

### command:scp

```sh
sudo chown -R USER_NAME REMOTE_FOLDER
sudo chmod 777 REMOTE_FOLDER
```

the `-R` means "recursively" since there may be file deeply in the target folder that won't allow you to write.

Hence, you can know, you can specifically claim your authority on the file or directory, since it would not automatically transfer.

Thus, a flexible approach is that just add a `-R` flag.

reference: https://unix.stackexchange.com/a/347412

### command:lsof

check status of port occupation

```sh
lsof -i:8888
```

### command:ufw

```sh
# check status
sudo ufw status

# enable
sudo ufw enable

# white list
sudo ufw allow 9000

# reload
sudo ufw reload

```

ref:

- [(20 条消息) Ubuntu 防火墙的开启，关闭，端口的打开，查看\_jiaochiwuzui 的博客-CSDN 博客\_ubuntu 查看防火墙开启的端口](https://blog.csdn.net/jiaochiwuzui/article/details/80907521)

### command:time

I can directly using `time ( COMMAND_1 | COMMAND_2 )`, so that it can calculate the final time of this pipe.

However, time calculation is a little more sophisticated than what would I have thought, refer more to: [bash - How can I time a pipe? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/364156/how-can-i-time-a-pipe/364157)

### command:tr

It's useful to split line to lines.

```sh
$ echo "111;222;333" | tr ';' '\n'
111
222
333
```

```sh
# use `nl` to add the line number
cat main.js | tr ';' '\n' | nl -ba | head -6
```

### command:cd

#### usage: a superb scene using `cd .`

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1641284537356-d66d64fc07918dc1e98e62dd2dd70454a9ff16b2b2cc6da39fe18cbc6a5b07a1.png" width="480" />

ref:

- [linux - How do I refresh directory in BASH? - Super User](https://superuser.com/questions/702402/how-do-i-refresh-directory-in-bash)

### command:sed

> ref

- [:sparkles::sparkles::sparkles: sed, a stream editor:sparkles::sparkles::sparkles:](https://www.gnu.org/software/sed/manual/sed.html)

- [Sed - An Introduction and Tutorial](https://www.grymoire.com/Unix/Sed.html)

- [sed man page - General Commands | ManKier](https://www.mankier.com/1/sed)

a good start:

- [Sed Command in Linux/Unix with examples - GeeksforGeeks](https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/)

#### how to print only matched lines

1. `-n` means "No automatically print the each line"
2. `/p` means "Print the processed line"

```sh
# print only the matched lines
sed -n "s|find|replace|p"

# don't print any line (so useless)
sed -n "s|find|replace|"

# print all the line each, with matched line again(twice, and it's the same)
sed "s|find|replace|p"

# TODO: print the processed, and apply function on it.
```

ref:

- [regex - sed: print only matching group - Stack Overflow](https://stackoverflow.com/questions/17511639/sed-print-only-matching-group)

#### :sparkles: how to increment version number

##### resolution 1: use `echo` based on `//e`

special thanks to: https://stackoverflow.com/a/14348899/9422455

##### resolution 2: answer

```sh
gsed -i -E 's|(.*)"version": "([0-9]+)\.([0-9]+)\.([0-9]+)"|echo "\1\\"version\\": \\"\2.\3.$((\4+1))\\""|e' package.json
```

> test what happened using `//pe`

```sh
➜  erb_sqlite git:(main) head -3 release/app/package.json                                                                                                                                           [7-01-22 | 4:18:17]
{
  "name": "mark.hjxh.express_match",
  "version": "0.2.2",


➜  erb_sqlite git:(main) gsed -E 's|(.*)"version": "([0-9]+)\.([0-9]+)\.([0-9]+)"|echo "\1\\"version\\": \\"\2.\3.$((\4+1))\\""|pe' release/app/package.json                                        [7-01-22 | 4:08:57]
{
  "name": "mark.hjxh.express_match",
echo "  \"version\": \"0.2.$((2+1))\"",
  "version": "0.2.3",
```

> explanation

In fact, the ` "version": "0.2.2",` is changed into `echo " \"version\": \"0.2.$((2+1))\"",`.

And then the `e` syntax indicates run this sequency string as a command, so that it finally turns into ` "version": "0.2.3",`

> attention

1. the `"` needs to be escaped, and to escape `"`, we need to use a `\`, and to let the `\` work in the `echo` function, we need to escape it again, that is to be `\\"`
2. `sed` will match all line (including the leading space), and the `e` would execute all line. So if I just replace the version number part into `echo "\\"0.2.3\\""`, then all the line would turns into ` "version": echo "\\"0.2.3\\""`, which is certainly unwanted and deserves reflection.

> core ref

[bash - How to find/replace and increment a matched number with sed/awk? - Stack Overflow](https://stackoverflow.com/questions/14348432/how-to-find-replace-and-increment-a-matched-number-with-sed-awk)

`perl | awk` alternative

- [bash - How to increment version number in a shell script? - Stack Overflow](https://stackoverflow.com/questions/8653126/how-to-increment-version-number-in-a-shell-script)

> official hack way (but I failed)

sh #!/usr/bin/sed -f

/[^0-9]/ d

# replace all trailing 9s by \_ (any other character except digits, could

# be used)

:d s/9\(_\*\)$/_\1/ td

# incr last digit only. The first line adds a most-significant

# digit of 1 if we have to add a digit.

s/^\(\_\*\)$/1\1/; tn s/8\(__\)$/9\1/; tn s/7\(\__\)$/8\1/; tn s/6\(__\)$/7\1/; tn s/5\(_\*\)$/6\1/; tn s/4\(\_\_\)$/5\1/; tn s/3\(\_\_\)$/4\1/; tn s/2\(\__\)$/3\1/; tn s/1\(\_\*\)$/2\1/; tn s/0\(\_\*\)$/1\1/; tn

:n y/\_/0/

````

- [sed, a stream editor](https://www.gnu.org/software/sed/manual/sed.html#Increment-a-number)

#### how to match digits (`[0-9]` or `:digit:`)

> ref:

thanks for the direction to sed official documentation in this post.

- [regex - Why doesn't `\d` work in regular expressions in sed? - Stack Overflow](https://stackoverflow.com/questions/14671293/why-doesnt-d-work-in-regular-expressions-in-sed)

#### how to insert text before first line of file

suppose the text is:

```text
@tailwind base;
@tailwind components;
@tailwind utilities;
````

and the file is `public/style.css`

first, export this variable for better understanding of commands:

```sh
T='@tailwind base;
@tailwind components;
@tailwind utilities;'
F='public/style.css'
```

and copy file as a backup:

```sh
cp $F ${F}_
```

then the reset command is:

```sh
cp ${F}_ $F
```

##### resolution 1: use `cat` and `;`

The `cat` approach meets our intuition, but needs a temp file.

First, we dump the `T` into `temp` file, then append `F` into temp, finally replace `F` with temp, that is:

```sh
echo $T > temp; cat $F >> temp; mv temp $F
```

Be careful about the second operator of `>>` since it means `append` otherwise the `$T` would be flushed, then `$F` keeps unchanged.

refer:

- [What are the shell's control and redirection operators? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)

##### resolution 2: use `cat` and `|`

In last solution, we used 2 ';', and there is an easy way to change it to just 1 ';'.

```sh
echo $T | cat - $F > temp; mv temp $F
```

In this solution, the `$T` echoed into second pipe, and `cat` used `-` to capture it then joined with `$F` and dumped into temp, which surely is faster.

refer:

- [linux - What does the last "-" (hyphen) mean in options of `bash`? - Super User](https://superuser.com/questions/1388584/what-does-the-last-hyphen-mean-in-options-of-bash)

- [shell - Usage of dash (-) in place of a filename - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/16357/usage-of-dash-in-place-of-a-filename)

##### resolution 3: use sed s-command

In the above 2 solutions, we both need an IO, i.e. first saving into a 'temp' file and move to override the raw file, which could be low-efficiently and not elegant.

There's a way allowing us to finish the 'join' action just in the pipe and finally leads to inplace-modify target file. That is "sed's s-command".

<img alt="picture 24" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379168300-linux-howto-90b435ef191284a35f21cb8cac698769b8548bfe2b3f90db2be5ea988a56c636.png" width="480" />

<img alt="picture 25" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379622241-linux-howto-e51b228ec26d453924d9731bc86f94185eccbc8ea4d43954698c4217845ca262.png" width="480" />

When using `s-command`, we can easily apply regex grammar to achieve what we want.

<img alt="picture 26" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379819166-linux-howto-c717ac5a605fb416fa2f472e202a74949ed8b34c3556d06ca6b70c8202d70901.png" width="480" />

Like this, we can easily insert text in front of a sequency of text based on regex of '^', which means the beginning of text.

And then, since the basic grammar of how to insert text before specific line of an input file in `sed` is `sed -i 'Ni TEXT' $F` , the problem then converts to how to join '1i' with $T. That is what we just learned can be put into practice:

<img alt="picture 27" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640380337394-linux-howto-d8bfb544ab1b2db098a1fd9138401997b9b11814af6cbf639243453526a91c02.png" width="480" />

You see, now all the commands have nothing to do with the io, and the principle behind this command chain is straightforward: join into `1i $T` then use it as `sed -i`’s parameter (via `-f-` which is the former pipe).

##### resolution 4: use sed e-command

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375147417-linux-howto-e0475887ff34e4a4a0be217c3596e054d2bdfa01f28f360f2459123e0b2175f7.png" width="480" />

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375169955-linux-howto-57609e425971259dd89c05c571047e701cb2c44dcc4deac43b0724a7295d8f44.png" width="480" />

I'd think the e-command is quite confusing, but does good job.

I made some tests on the e-command to help myself understand.

In the above introduction, it indicates that if 'without parameters, the e command executes the command that is found in space and replace the pattern space with the output'.

suppose we have `a='aaa\necho "bbb" \nccc'`, then if we runs `echo $a | gsed '2e'`, that's to say run the second line as a command and let others stay as what they are: <img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375663511-linux-howto-18fd2906bf27a739476740fbe2c713a3c42b40de5865cebd14c08e696ed0b39a.png" width="480" />

However, 'if a parameter is specified, instead, the e command interprets it as a command and sends its output to the output stream.'

I made an example which may help us to understand what's the mechanism of `gsed 'ne xxx`, in which `xxx` is the so-called 'parameter'.

<img alt="picture 19" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640376208972-linux-howto-5309698b6833082cf93b3b0f69cda3616678ad00d3e5141895bcec14b8684f57.png" width="480" />

You can see, as the following shows, since a is a three-line text and sent into the pipe as stream, so first line shows 'aaa', and second line shows 'echo "bbb"', as what we preset.

The most notable point is that since `gsed` sets a `3e` command which means 'it will execute following commands at 3rd row of stream'. Thus, the following commands `xxx\n echo "yyy"...` are executed as separate commands split by lines.

Obviously, neither `xxx` nor `zzz` is a valid command and turned into an error. Plus, since the level of error usually is a bit higher than normal output, the error of `zzz` came before `yyy` and then is `AAA`.

Finally, when all the commands were executed, the next stream in pipe came, i.e. `ccc`, and all the sequences came into end.

ref:

[sed e-command](https://www.gnu.org/software/sed/manual/sed.html#:~:text=by%20standard%20seds.-,e%20%5Bcommand%5D,-This%20command%20allows)

Still, we had other topics to talk about.

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377292421-linux-howto-27ab701a1d1cca335a1476e71b742a60b9f6817b5d08521c70c766bfae21290d.png" width="480" />

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377315692-linux-howto-ea510349e79dd47d4ca01d17200defcf7e8b8b8ebda0b0785c1833ba932c625d.png" width="480" />

We can know the classic usage of `sed` is `sed SCRIPT INPUTFILE`, and if `-e` option is used to specify a script, with all non-option parameters taken as input files.

So what would happen when we combine the `-e` and an input file.

Back to what we covered the above, we can move a step further now.

<img alt="picture 23" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377647537-linux-howto-8099c8c4212b90dd4f7fa22449dc22ef8135c485c97674a561b87769121c750b.png" width="480" />

In this example, we can see that `gsed` first read one line from `../temp` file which is `AAA`, and then paused since the `2e` flag to execute `cat -` command which shows all the input stream from `echo $a`, and finally continued to read the remaining rows of `BBB` and `CCC`.

So what about if we specify a `-i` option, which means `change in position`?

It's easy to understand, that is all the output would be sent into `../temp`, so that `../temp` changes to the output just like the result in this example shows.

Hence, we can derive from our conclusion: if we use the following command:

```sh
echo $T | gsed -i '1e cat -'  $F
```

then the goal of inserting text before first line can be achieved just on the fly~

How amazing and beautiful it is!

ref:

- [gsed overview](https://www.gnu.org/software/sed/manual/sed.html#:~:text=sed%20%C2%A0%20%5BContents%5D%5BIndex%5D-,2.1%20overview,-Normally%20sed%20is)

> conclusion

G1. To insert lines at the beginning of one file:

```sh
# 1. dump, dump, and move
echo $T > temp; cat $F >> temp; mv temp $F;

# 2. join, dump, and move
echo $T | cat - $F > temp; mv temp $F;

# 3. [sed s-command] concat-string, inplace-insert
echo $T | gsed '1s/^/1i /' | gsed -i -f- $F

# 4. [sed e-command] ... hard to conclude
echo $T | gsed -i '1e cat -' $F
```

G2. To insert lines at specific line:

```sh
# 1. if text is single line, refer: https://stackoverflow.com/a/6537587/9422455
gsed -i 'Ni $T' $F

# 2. if text is multi lines, refer:
echo $T | gsed -i 'Ne cat -' $F
```

FIXME: (failed) G3. To insert content after matched position:

```sh
# 1. [sed r-command]
echo $T | gsed -i '$P/r -' $F #  the '-' is same for '/dev/stdin'
```

G4. To insert multi lines manually:

```sh
# 1, when lines are already multiplied, just add `\` after each line, refer: https://askubuntu.com/a/702693

# 2, when lines are in one, using `\n`, refer: https://askubuntu.com/a/702690
```

G5. To insert lines after matched line with the same leading space format:

> :warning: 嵌套 sed 正则注意事项
>
> 1. 输入的文本不能与分隔符相同，否则需要转义。比如本次为了在代码中加入注释`//`，就不方便用`/`当分隔符
> 2. 嵌套正则的时候，为了能分清一级与二级，可以应用不同的分隔符，比如本次更新用了`|`作为一级，`_`作为二级

```sh
# 1. [sed s-command] leading space align with $P
# failed at 2022-01-25
# echo $T | gsed 's/^.*$/s\/(^.*?)($P.*$)\/\\1\\2\\n\0\//' | gsed -E -f- $F

# updated at 2022-01-25
echo $T | gsed 's|^.*$|s_^(.*?)('$P'.*)$_\\1\\2\\n\\1\0_|' | gsed -E -f- $F | grep --context=3 $T

# FIXME: (failed) 2. [sed s-command with named-pipe] [more straightforward]
cat <(echo -n "s/(^.*?)($P.*?$)/\1\2\\\\n\1" & echo -n $T & echo -n "/") | gsed -E -f- $F
```

<img alt="picture 29" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640385997938-linux-howto-41e634caf1122f991d08d485202adfb56ab71cdfdb7d5ad76ad4f57ca751cbaa.png" width="480" />

ref:

- [shell - How do I join two named pipes into single input stream in linux - Server Fault](https://serverfault.com/questions/171095/how-do-i-join-two-named-pipes-into-single-input-stream-in-linux)
