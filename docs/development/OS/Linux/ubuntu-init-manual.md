# ubuntu init manual

1. [step 0. install](#step-0-install)
2. [step 1. config apt source](#step-1-config-apt-source)
   1. [1. change apt source](#1-change-apt-source)
      1. [fastest/script way: 直接修改`/etc/apt/sources.list`](#fastestscript-way-直接修改etcaptsourceslist)
      2. [robustest/recommend-for-newbie way: 在`softwares & update`里修改 server](#robustestrecommend-for-newbie-way-在softwares--update里修改server)
      3. [use others way: 使用别人写好的 git 仓库进行配置](#use-others-way-使用别人写好的-git仓库进行配置)
   2. [2. update apt](#2-update-apt)
3. [step 2. config git](#step-2-config-git)
4. [step 3. config terminal](#step-3-config-terminal)
5. [step 4. config language](#step-4-config-language)
   1. [resolution 1: config chinese input source via ibus](#resolution-1-config-chinese-input-source-via-ibus)
   2. [FIXME: resolution 2: config chinese input source via sougou](#fixme-resolution-2-config-chinese-input-source-via-sougou)
   3. [how to switch language input source](#how-to-switch-language-input-source)
   4. [how to change language to english](#how-to-change-language-to-english)

## step 0. install

- [Ubuntu 18.04.6 LTS (Bionic Beaver)](https://releases.ubuntu.com/18.04/)

## step 1. config apt source

### 1. change apt source

ref:

- [【Ubuntu】Ubuntu 18.04 LTS 更换国内源——解决终端下载速度慢的问题 - 知乎](https://zhuanlan.zhihu.com/p/61228593)

#### fastest/script way: 直接修改`/etc/apt/sources.list`

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

#### robustest/recommend-for-newbie way: 在`softwares & update`里修改 server

第二种办法就是在`softwares & update`里自动测试最好的服务器，然后选择它。我测出来是`yun-idc`最好，但是因为我没用过，所以当时没考虑它，后来被阿里云折磨的不行了，就试了它，结果飞快，十兆每秒！

#### use others way: 使用别人写好的 git 仓库进行配置

第三种办法，由于我还没配好源，所以也没 git，而此时下载 git 又会极其地慢，所以也不考虑。

### 2. update apt

!!!tip If the following commands warn that files are locked, then wait for some minutes, or use `lsof FILE` to have a check, more refer to: - [解决 apt-get /var/lib/dpkg/lock-frontend 问题 - 知乎](https://zhuanlan.zhihu.com/p/126538251)

```sh
sudo apt get update
sudo apt get upgrade
```

## step 2. config git

```sh
sudo apt get git
git config --global user.name YOUR_NAME
git config --global user.email YOUR_EMAIL
```

## step 3. config terminal

## step 4. config language

### resolution 1: config chinese input source via ibus

ibus 输入方式和搜狗输入法之间不是很兼容，如果出现两者都无法输入中文的情况，建议根据[Ubuntu 18.04LTS 安装中文输入法以及快捷键设置 - 简书](https://www.jianshu.com/p/c04a4b03d30f)先卸载搜狗输入法，确认 ibus 是可以用的，具体就是：`sudo apt-get remove fcitx*`

确认以下配置：

1. 设置 - 地区与语言 - 输入法，中要添加包含智能拼音：

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642268594063-def6bf87b276425161475a3ce55fbb05d8bb305b913ae5b39cc6e9708a6e32ae.png" />

2. 语言支持中，要启用 ibus 方案

   <img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642268691854-043dc8408c8326d13213bc92302c26f2d85b2be6a2892dbc58cf3d3349c9c8bc.png" />

   注销账号重新登录即可。

3. 如果注销账号还不行， 就要尝试`sudo reboot`一下。

### FIXME: resolution 2: config chinese input source via sougou

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

### how to switch language input source

The best way is to directly install the Chinese version of ubuntu, since the Chinese feature is built-in.

However, what we download directly from the official ubuntu website, may not support chinese choice natively. So it highly depends on what distribution version of ubuntu we download.

ref:

- [(20 条消息) ubuntu 切换中文输入法\_*g_y*的博客-CSDN 博客\_ubuntu 切换中文输入法](https://blog.csdn.net/qq_31290747/article/details/94555163)

### how to change language to english

```sh
echo export LANGUAGE=en_US.UTF-8 |  sudo tee -a ~/.bashrc
```

ref:

- [command line - How do I change the language via a terminal? - Ask Ubuntu](https://askubuntu.com/questions/133318/how-do-i-change-the-language-via-a-terminal)
