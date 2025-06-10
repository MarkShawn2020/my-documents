# Rockchip-4B Android 刷机天坑指南

1. [documentation](#documentation)
2. [记一次糟糕的刷机经历](#记一次糟糕的刷机经历)
   1. [intro](#intro)
   2. [step 1. 生成 `gpt.img`](#step-1-生成-gptimg)
   3. [step 2. install `rkdeveloptool`](#step-2-install-rkdeveloptool)
   4. [step 3. 基于`rkdeveloptool`的`emmc`刷机要点](#step-3-基于rkdeveloptool的emmc刷机要点)
   5. [基于`adb`的`scrcpy`投屏](#基于adb的scrcpy投屏)
   6. [关于 sd 卡刷](#关于sd卡刷)
   7. [其他关于 rc 的吐槽](#其他关于rc的吐槽)
3. [FIXED: `No configuration exists for this target on this architecture. Stop.`](#fixed-no-configuration-exists-for-this-target-on-this-architecture-stop)
4. [FIXED: `error: 'commit_id.xml', needed by 'out/target/product/rk3399/vendor/commit_id.xml', missing and no known rule to make it`](#fixed--error-commit_idxml-needed-by-outtargetproductrk3399vendorcommit_idxml-missing-and-no-known-rule-to-make-it)
5. [FIXED: `error: prebuilts/clang/host/linux-x86/: platform/prebuilts/clang/host/linux-x86 checkout`](#fixed-error-prebuiltsclanghostlinux-x86-platformprebuiltsclanghostlinux-x86-checkout)
6. [FIXED: `awk: line 2: function strtonum never defined`](#fixed-awk-line-2-function-strtonum-never-defined)
7. [FIXED: `fatal error: openssl/bio.h: No such file or directory`](#fixed-fatal-error-opensslbioh-no-such-file-or-directory)
8. [FIXED: `"Creating Comm Object failed!"`](#fixed-creating-comm-object-failed)

## documentation

- :sparkles::sparkles::sparkles: 核心刷机资料，包含各种工具 [Rock/flash the image - Radxa Wiki](https://wiki.radxa.com/Rock/flash_the_image#Upgrade_tool_from_Rockchip)

- 升级 XX？： [Burning Firmware — Firefly Wiki](https://wiki.t-firefly.com/en/Core-3308Y/burning_firmware.html)

https://mega.nz/folder/gxVRiara#_ExDV9pfNpqabzDTtpN-UA

## 记一次糟糕的刷机经历

### intro

首先关于 rc 的刷机部分，官方参考文章主要有以下：

- [Rockpi4/rockpi-android11 - Radxa Wiki](https://wiki.radxa.com/Rockpi4/rockpi-android11)

- [Rockpi4/rockpi-android10 - Radxa Wiki](https://wiki.radxa.com/Rockpi4/rockpi-android10)

- [Rockpi4/rockpi-android7 - Radxa Wiki](https://wiki.radxa.com/Rockpi4/rockpi-android7)

理论上，刷对应版本就去翻对应的网页，但在 rc 这里不是这样的，rc 的文档写的，应该说相当随意，然后历史遗留痕迹太大， 不懂得维护。

从经验上看，rc 可能在持续更新，比如在 android 7 的时代写一篇 7 的刷机文档，10 的时代写了一篇 10 的刷机文档，里面总体来说，可能没有什么大错误，但是坑不少。

我恰巧目标平台是 10,10 的刷机文档竟然出乎意料地是最坑的。

比起 11 它没有给出一键刷机的指令，这也许可以接受，（其实无非就是把几个脚本合起来了而已）；但比起 7 它竟然少了最后一步生成`gpt.img`的步骤，而在 7、11 里都是有的……我还是在花了很长时间的搜索后才在 7 的文档里找到这一步的答案。

咋还能升级升垮了呢？这是让我觉得 rc 最不专业的一点。

!!!warning 尽管 rc 每个版本都给出了分步编译的说明，`u-boot -> kernel -> aosp -> img`等，但是考虑到中途实在有太多步，并且他们基于（提前使用）软链接的一些设置很容易造成项目紊乱，为此我又多花了一天时间，怎么刷机都刷不过。最后还是使用一键脚本编译，然后刷机一次性通过。

    所以尽管10的文档里没有给出一键刷机的说明，但是仓库里其实有的，注意项目根目录下的`build-rockpi-4b.sh`，运行仿造11的命令：`./build-rockpi-4b.sh -UACKup` 即可（不用管意思，一把梭就可以）。

### step 1. 生成 `gpt.img`

接下来是刷机第一步（拉取代码，直到生成`gpt.img`）

```sh
VERSION=10
TAG=q           # 10 -> q, 11 -> r

DIR=rockpi4-android-$VERSION
BRANCH=rockchip-android-$VERSION

mkdir $DIR && cd $DIR

repo init -u https://github.com/radxa/manifests.git -b $BRANCH \
    -m rockchip-$TAG-release.xml
repo sync -d --no-tags -j4

./build-rockpi-4b.sh -UACKup
```

如果之前已经整编过，那么运行`./build-xx.sh` 一键编译应该只需要半个小时左右，否则就是正常安卓编译+kernel 编译时间，预留四小时吧。

在`./build-xx.sh`之后，期间生成 image 的过程里会把`rockdev`文件夹链接到根目录，也就是：

```sh
rockdev -> ./RKTools/linux/Linux_Pack_Firmware/rockdev/
```

而在这个`rockdev`目录下，又有一个`Image`文件夹软链接，它指向当前文件夹下正在编译的那个`Image`（默认有多个，比如：`Image-aosp_arm`、`Image-RockPi4B`等），我们目前的一键编译会将`Image`指向`Image-RockPi4B`。

而在该`Image`目录下，有一个`gpt.img`文件，这个就是完整的刷机包。

### step 2. install `rkdeveloptool`

由于我们购买的 rc4b 已经焊死了一个`emmc`，所以我们无需额外的 sd 卡，直接基于 emmc 就可以（根据测试，官网中说的短路也是不用的）

使用`emmc`首先需要下载`rkdevleloptool`（linux 或 mac： [rockchip-linux/rkdeveloptool](https://github.com/rockchip-linux/rkdeveloptool)）或者`RkDevTool`（windows）。

具体下载与安装也可以直接使用以下：

```sh
# mac
brew install automake autoconf libusb lsusb

# linux
sudo apt-get install -y libudev-dev libusb-1.0-0-dev dh-autoreconf

# both
git clone https://github.com/rockchip-linux/rkdeve loptool
cd rkdeveloptool
autoreconf -i
./configure
make

# global
sudo cp rkdeveloptool /usr/bin/
```

参考：- [Rockpi4/dev/usb-install/zh cn - Radxa Wiki](https://wiki.radxa.com/Rockpi4/dev/usb-install/zh_cn)

### step 3. 基于`rkdeveloptool`的`emmc`刷机要点

首先是认识接口与接线顺序。

rc4b 只有一个 typeC 口是用于供电的，其它四个 usb 口其中两个是 usb2.0，两个是 usb3.0（蓝色）。

两个蓝色 usb3.0 中，上面（离主板距离更高）那个是 otg 口，口后面有个开关，**往板角方向掰是`usb device`模式**，这样连接电脑后电脑可以检测到 rc4b 里面的系统（`adb`才有用）；否则是`udb host`模式，用于其他用途。

rc4b 还有三个按键，按官方文档：[引导 Rock PI 进入 Maskrom 模式](https://wiki.radxa.com/Rockpi4/dev/usb-install/zh_cn#.E5.BC.95.E5.AF.BCRock_PI_.E8.BF.9B.E5.85.A5Maskrom.E6.A8.A1.E5.BC.8F) 描述**从 typeC 口上的那个按键往下的三个键**分别是`maskrom | recovery | reset`键，但我目前测试下来**第二个键才是`maskrom`**，这个具体哪个对哪个，可能还是要结合实际测试。

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-flash-manual-1644255141135-1364f8369dd569aa2f158b065f7b136564f59a2862be1a7b718318828dd036a9.png)

而基于 `rkdeveloptool` 是基于 `maskrom`工作的，如果设备不是处于该模式，则无法基于 `rkdeveloptool` 对设备进行操作。

1. 先将**公对公线**连上 otg 到电脑（电脑如果是 c 口，要用 usb 转 c 转接器，直接用公接 c 线到我的 mac 没反应）
2. 按住 rc4b 的`maskrom`键
3. 将 rc4b 接电（这个电口既可以插插座，也可以接电脑，无所谓，用于供电的）
4. 松开`maskrom`键

只要是先按着`maskrom`键然后接电的，开发板就是进入了`maskrom`模式，这是要点一；

只要先接上 otg，接着就能检测到`maskrom`，这是要点二。

可以用`watch rkdeveloptool ld`（需要`brew install watch`）监控`maskrom`连接情况（**接电后一秒就有反应了**）

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644249491217-d605ee29a08003b3b798e074df803f53b30f7eca194d6ab6019242930bb97d99.png)

也可以用`lsusb`（或者`lsusb 2>/dev/null`抑制内部错误信息）查看是否有`Fuzhou`的 usb 行信息：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644249641183-07215c18cee315c5e1188645b6821447bf9a938dcda40a34ceb481513c9fd1a4.png)

这样，我们确认了已经连接上。

接下来我们要下载官方的`loader`用于初始化`RAM`。我其实在仓库根目录也看到了一个 loader：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644249777798-6b964879549bb12c14a62f4a73dbdc818a1bfb9e5682c9866353c42ffe92259e.png)

用来试了一下，发现不行，所以用官方的就好： [通过 USB 烧写镜像到 eMMC 模块](https://wiki.radxa.com/Rockpi4/dev/usb-install/zh_cn#.E9.80.9A.E8.BF.87USB.E7.83.A7.E5.86.99.E9.95.9C.E5.83.8F.E5.88.B0eMMC.E6.A8.A1.E5.9D.97)：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644249820467-2e17ef75688e91833d86a228eb13d7d5c83c183c3c3be93d78807ba1b4138532.png)

!!!tip 解压那个`zero.img.gz`可以用`gunzip zero.img.gz`，以得到`zero.img`。

假设当前目录结果如下：

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644250544006-091a413a1c4c24a47b3645967fad81cc4647c21cf65e7cc59796dff9c54d5575.png)

其中 [`rk3399_loader_v1.20.119.bin`](https://dl.radxa.com/rockpi/images/loader/rk3399_loader_v1.20.119.bin) 是下载的官方 bin 文件，[`zero.img`](https://dl.radxa.com/rockpi4/images/others/zero.img.gz)也是下载的官方空镜像，而[`ROCKPI-4AB-2020-10-15-11-14-gpt.img`](https://pan.baidu.com/s/1pT2CEa12nAkjbI8xklQvAw#list/path=/public/dl.radxa.com/rockpi4/images/android/all)是官方打包好的安卓 10 镜像，`gpt-4b.img`是我们自己编译好的安卓镜像。

于是可以用以下脚本方便一键刷机/复原：

```sh
# LOADER="rk3399_loader_v1.20.119.bin"
LOADER="loader.bin"

# function
export f() {
    rkdeveloptool db $LOADER
    rkdeveloptool wl 0 $1
    rkdeveloptool rd
}

# burn image of official packed android 10 for test
f ROCKPI-4AB-2020-10-15-11-14-gpt.img

# burn image of `gpt.img`
f gpt-4b.img

# clear image
f zero.img
```

可以这么做，达到清空镜像再重新安装我们的 4b 镜像：

```sh
f zero.img
f gpt-4b.img
```

值得注意的是，这么做之后，如果你实时监控`maskrom`状态（`watch rkdeveloptool ld`）会看到在`f zero.img`之后系统依旧是`maskrom`状态，而在`f gpt-4b.img`之后系统将复原（也就是说，`zero.img`不会中断`maskrom`状态。

同时，如果你也在监控`adb`状态（`watch adb devices`）会看到，在`f gpt-4b.img`后几秒，有一个`recovery`状态的设备发现，再过几秒就没了；然后开发板重启，再过几秒后，**蓝灯闪烁**就代表已经系统已经成功在运行，此时`adb`里会有一个正常的设备出现。

而当`adb`里有设备时可以使用投屏功能。

### 基于`adb`的`scrcpy`投屏

访问：- [Genymobile/scrcpy: Display and control your Android device](https://github.com/Genymobile/scrcpy) 或者直接 `brew/apt install scrcpy`即可安装`scrcpy`。

无需任何额外配置，在`adb`有效后，使用`scrcpy`就能看到系统效果。

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644251361710-fc09612d5c43841750ad8021df3e54a536bbefd53b0212791e6e56e3294025bc.png)

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644251346572-13d0d1f1d9bac89c6ac9c89b434263ecdd74a8957a62b16ddf0d26adbf9b84de.png)

!!!tip 目前发现，自己编译的 android 系统明显比官方打包的要好，没有抖动之类的问题，据博文猜测应该是官方打包的太旧了。

### 关于 sd 卡刷

其实 sd 卡刷理论上比`emmc`要更傻瓜一些，因为有现成的`Etcher`之类的软件三步烧到卡里，然后插到板子上，就可以自动启动了。

我之前花了很长时间纠结无法开机的问题，主要是因为镜像不对，而非按键之类的操作有误。

这也是卡刷的一个缺点，出了问题也不方便调试。

而我们的 rockchip-4b-plus，已经有了一块内置焊死的`emmc`，所以也确实没必要用 sd 卡，尽管都可以。sd 卡的话就不用去安装 rockchip 官方的 `rkdeveloptool` 工具。

具体参考官方说明：

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644251579973-a838685f920678a8b08c949b7510555ba0e731a3810b0ebcdfba986df66841df.png)

### 其他关于 rc 的吐槽

> 从今天起，只要你也吐槽 rockchip 的产品、文档，那我们就能成为朋友！

在 rc 镜像生成部分，`rockdev`目录下可以看到 readme 是这么写的：

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-howto-1644251772636-88df91526be1343f5acea923600510b931c71c87e19a463dec406d9f123a83a0.png)

但实际上，我们根本就没有必要把`loader` copy 到什么地方去，可能是他们的脚本里自带了，也有可能是他们后来更新了。

再联系他们各大版本的文档的同步、准确性等问题……

总之，标准的天坑。

## FIXED: `No configuration exists for this target on this architecture. Stop.`

mark::update@2022-02-25: 在编译 kernel 时，今天一直碰到这个问题。

一开始是我在回滚了 kernel 之后出现的，后来我仔细查看了 git log，发现有一个 commit 里包含很多 `config.go` 文件，我猜想这些文件是不能丢掉的。

我原以为，是 rk 的 git 操作没到位，一些新的文件没合到 git 里。

直到后来我才意识到，~~（不确定）是在 repo sync 的时候，自动生成的，当然，这个生成的一部分文件，也就属于新增文件，不在 commit 里了。~~

因此，当我回滚了操作，甚至直接删光 kernel 文件夹再 `repo sync kernel`，也不能获得那些 config 文件。

最终导致 kernel 无法编译。

总之，要么 `make clean`，要么 指定`lunch`，要么就 `repo sync` 重新同步一下，也没有其他办法了……终归有个办法可以用的……

## FIXED: `error: 'commit_id.xml', needed by 'out/target/product/rk3399/vendor/commit_id.xml', missing and no known rule to make it`

It arises up when we build the AOSP, and the `python` is disallowed without the `commit_id.xml`, so just put it:

```sh
TEMPORARY_DISABLE_PATH_RESTRICTIONS=true
```

see: - [error: 'commit_id.xml', needed by 'out/target/product/rk3399/vendor/commit_id.xml', missing and no known rule to make it · Issue #2 · radxa/manifests](https://github.com/radxa/manifests/issues/2)

## FIXED: `error: prebuilts/clang/host/linux-x86/: platform/prebuilts/clang/host/linux-x86 checkout`

ref:

- [repo error | XDA Forums](https://forum.xda-developers.com/t/repo-error.4092681/)

## FIXED: `awk: line 2: function strtonum never defined`

```sh
sudo apt-get install gawk
```

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-flash-manual-1644846223441-63a3ec139b6d7ca29888de4d61509a71a7c3091a4789d2e8d380c1d274ba5662.png)

ref:

- [(1 条消息) 解决 awk: line 2: function strtonum never defined_liangtianmeng 的专栏-CSDN 博客](https://blog.csdn.net/liangtianmeng/article/details/86020254)

## FIXED: `fatal error: openssl/bio.h: No such file or directory`

```sh
sudo apt-get install aptitude
sudo aptitude install libssl-dev
```

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-flash-manual-1644846538496-8633106a098062b99f863824d72ffeebf4d3c082c09c67fff2e91bdda8e2f6dc.png)

ref:

- [kernel - fatal error: openssl/bio.h: No such file or directory - Stack Overflow](https://stackoverflow.com/questions/59016911/fatal-error-openssl-bio-h-no-such-file-or-directory)

## FIXED: `"Creating Comm Object failed!"`

```sh
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="2207", MODE="0666",GROUP="plugdev"' | sudo tee /etc/udev/rules.d/51-android.rules
```

ref:

- [Linux Host Installation for ROCK960 Android - 96Boards](https://www.96boards.org/documentation/consumer/rock/installation/linux-mac-rkdeveloptool-android.md.html)

- ["Creating Comm Object failed" error when use rkdeveloptool - Using ROCK Pi 4 - Radxa Forum](https://forum.radxa.com/t/creating-comm-object-failed-error-when-use-rkdeveloptool/1092)
