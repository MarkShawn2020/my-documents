## prepare

```sh
# ubuntu 18.0.4
sudo apt-get install git-core gnupg flex bison build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 libncurses5 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev libgl1-mesa-dev libxml2-utils xsltproc unzip fontconfig
```

ref:

- [搭建构建环境  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/build/initializing#installing-required-packages-ubuntu-1804)

## fetch aosp source codes

### 成功拉取的完美表现

网速、镜像好的话（没有什么网络波动、墙之类的问题），应该会很干净。

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643041083062-7ef2fb44364ee4d19b85ca10c9d584fab92b00dcba15786931ecad664299a1dc.png)

然后最后一部分也会很干净，否则会有`repo sync -j1 --fail-fast`的提示。

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643041021703-2441a7b9be700a6cd4a915d77cf889a1b04040a47f073b724c303ca3466faa8d.png)

选择 combo 的时候也会很干净。

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643041231454-e0370288b3958ecc7a66decdbe289feb7d6970955048b4b9ae7effd4c525884c.png)

### aosp 镜像的大小

aosp 7 size: about 168GB

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643018168314-a1741be86e4033659829ff6bd84b890047f972a9214375e4e698248f4960246c.png)

### 什么环节最吃 cpu：checkout 的时候

checkout 的时候最卡，因为 cpu 都用满了（无堵塞的那种），单单是`repo sync`这种其实还还好，毕竟网络延迟要比本地磁盘要高，占用 cpu 的能力也就相对较弱了。

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643040592979-1255c3834cbd8fcc7fbd22a4a2763ea68a4be298da9bafe7099e335a16e4fd4f.png)

### aosp 编译成功的表现

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643052800738-5972707bfd1a8d66b6af4a41d552c44762e2be2238914a4c6dc05d9ec990f911.png)

## repo steps

### repo detailed steps

#### Step 1. config repo

1. download repo

```sh
# - [源代码控制工具  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/develop#installing-repo)
sudo apt install repo
```

2. change python version

There are a lot of methods to let repo using python3, but the easiest way I learned is to modify the first line of `repo` script file: change `python` to `python3`

```sh
vim $(which repo)
```

#### Step 2. set git

```sh
# set user, necessary
git config --global user.email shawninjuly@gmail.com
git config --global user.name markshawn2020
```

#### Step 3. set mirror

> 1. 如果是在公司，则直接用公司的网络即可
> 2. 如果是个人，则**即使有 vpn，也要用镜像，因为流量太大了！**。因此接下来说说镜像操作

参考：- [AOSP | 镜像站使用帮助 | 清华大学开源软件镜像站 | Tsinghua Open Source Mirror](https://mirrors.tuna.tsinghua.edu.cn/help/AOSP/) 可以通过以下方法快速更换镜像地址：

method 1:

```sh
# ~/.bashrc
# ref: https://blog.csdn.net/zy13608089849/article/details/84767864
export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/'
```

method 2:

```sh
# set mirror, faster
git config --global url.https://mirrors.tuna.tsinghua.edu.cn/git/AOSP/.insteadof https://android.googlesource.com
```

这条命令，其实会修改 git 的全局 url 属性，具体效果如下：

```sh
mark@ubuntu:/var/lib/dpkg/updates$ cat ~/.gitconfig
[user]
	name = XXX
	email = XXX@gmail.com
[url "https://mirrors.tuna.tsinghua.edu.cn/git/AOSP/"]
	insteadof = https://android.googlesource.com
```

#### Step 4. `repo init`

> ref: AOSP | 镜像站使用帮助 | 清华大学开源软件镜像站 | Tsinghua Open Source Mirror, https://mirrors.tuna.tsinghua.edu.cn/help/AOSP/

At here we can get diversified versions of aosp [代号、标记和 Build 号  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/start/build-numbers#source-code-tags-and-builds), and we can know that the version is composed of: `android-{VERSION_NUMBER}_r{NUMBER}`.

So since I wanna to install the android 11, I can specify the version as `android-11.0.0_r1`.

And then download it via:

```sh
cd {ANDROID}
# e.g. VERSION=android-10.0.0_r1

# ensure `REPO_URL` set is better

# solution 1:
repo init -u https://android.googlesource.com/platform/manifest -b $VERSION

# solution 2:
repo init -u https://mirrors.tuna.tsinghua.edu.cn/git/AOSP/platform/manifest -b $VERSION
```

ref:

- [下载源代码  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/build/downloading#initializing-a-repo-client)

#### Step 5. `repo sync`

Since `repo sync` needs a lot of time, 1-10 hours or so, depending on the internet speed.

```sh
repo sync -j88
```

So:

1. the internet connection, especially vpn setup is necessary!
2. the terminal time is recommended to set for time review.

#### Step 6. build (make)

看样子，其实还是 CPU 用的狠一点。

不过当我使用`m -j32`时，程序会提示，最少要 24G 内存（恰好我服务器正好）。~~但现在来看，可能有点夸张了。~~

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642413954133-6ab9f4f668db9ab420f0428e5c9f9dcdc7fe1a4cf8974861b2b5b0cce7c2b26d.png" /> P

Emm... 貌似。。不夸张！用满了！

### repo howto

#### how to get the revision(tag / version number) of repo

```sh
grep revision .repo/manifests/default.xml
```

#### how to download/sync specific part of aosp

ref:

recommended:

- [git - Repo Sync a particular folder - Stack Overflow](https://stackoverflow.com/questions/2130283/repo-sync-a-particular-folder)

not recommended:

- [(23 条消息) 如何使用 repo 下载部分 Android 源码并保持项目结构\_西涛 offbye-移动全栈技术博客-CSDN 博客](https://blog.csdn.net/offbye/article/details/53002219)

full/official download:

- [下载源代码  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/build/downloading)

### repo bugfix

#### :white_check_mark: `error: Unable to fully sync the tree. error: Downloading network changes failed.`

```sh
repo sync -j1 --fail-fast
```

ref:

- [Mac11.5 编译 Android 源代码报错汇集 - 简书](https://www.jianshu.com/p/7971444b5359)

#### FIXME: TEST `A TLS packet with unexpected length was received.`

We can see the problem of it from the following image:

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642512998973-7a429cb3e3152b874f699178c53352a5c456aa8f530010ca0df58b16b9ddcecb.png)

~~It's quite likely that the tls packet size exceeds the default capacity of git.~~

If so, the solution becomes clear, that is to increase the limitation.

```sh
git config --global http.postBuffer 1048576000
```

Update: however, it's not.

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642515812043-f1207f2431e7ca6e7a9fbb48e75924fbf6a68c31f83a697b642425fdf9e2cee6.png)

Maybe, we need other solutions.

A possible one maybe to disable ssl verification:

```sh
git config --global http.sslVerify false
```

#### FIXME: `The remote end hung up unexpectedly`

ref:

```sh
设置git最低速度
$ git config --global http.lowSpeedLimit 0
$ git config --global http.lowSpeedTime 999999
设置http缓存
$ git config --global http.postBuffer 1048576000
```

- [ubuntu 中 git clone 安卓内核时报 fatal: The remote end hung up unexpectedly 错误的处理 - CodeAntenna](https://codeantenna.com/a/H67hswkvrF)

- [github - Git, fatal: The remote end hung up unexpectedly - Stack Overflow](https://stackoverflow.com/questions/15240815/git-fatal-the-remote-end-hung-up-unexpectedly)

- [Git：解决报错：fatal: The remote end hung up unexpectedly_JiangDong 的博客-CSDN 博客](https://blog.csdn.net/u013250071/article/details/81203900)

### :white_check_mark: `prior sync failed; rebase still in progress`

resolution:

```sh
git rebase --abort
```

ref:

- [如何解决报错“prior sync failed; rebase still in progress” | IChrisKing](https://ichrisking.github.io/2017/12/04/how-to-fix-rebase-still-in-progress/)

## discussion

### why not support macos

ref:

- [自 2021 年 6 月 22 日开始，新版 Android 将不再支持在 MacOS 或 Windows 上构建 - V2EX](https://www.v2ex.com/t/778988)
