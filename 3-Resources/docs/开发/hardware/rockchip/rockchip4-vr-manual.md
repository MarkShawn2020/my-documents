# rockchip4 vr manual

1. [test diy and compile surfaceflinger](#test-diy-and-compile-surfaceflinger)
   1. [1. :white_check_mark: 虚拟机找不到 adb 设备](#1-white_check_mark-虚拟机找不到adb设备)
   2. [2. :white_check_mark: 启用投屏](#2-white_check_mark-启用投屏)
   3. [3. :white_check_mark: 修改源码，尝试在`surfaceflinger`部分加入几句 log](#3-white_check_mark-修改源码尝试在surfaceflinger部分加入几句log)
   4. [4. :white_check_mark: 推入系统](#4-white_check_mark-推入系统)
   5. [5. :white_check_mark: 测试是否编译通过成功](#5-white_check_mark-测试是否编译通过成功)
2. [compile and run the first vr mode](#compile-and-run-the-first-vr-mode)
   1. [error of null pointer](#error-of-null-pointer)
3. [output 4k](#output-4k)
   1. [分辨率输出逻辑](#分辨率输出逻辑)
   2. [TODO: check supported resolutions](#todo-check-supported-resolutions)
   3. [TODO: 自定义分辨率输出参数](#todo-自定义分辨率输出参数)
   4. [change hdmi output resolution](#change-hdmi-output-resolution)
      1. [resolution 1. set `framebuffer` and `resolution`](#resolution-1-set-framebuffer-and-resolution)
      2. [resolution 2. change dts](#resolution-2-change-dts)
      3. [PASSED: change `RkConfig`](#passed-change-rkconfig)
   5. [主板支持 4k60hz 输出修改](#主板支持4k60hz输出修改)
   6. [测试 edid 修改结果](#测试edid修改结果)
4. [HDMI 相关介绍](#hdmi-相关介绍)
   1. [EDID](#edid)
   2. [HDMI 比例](#hdmi比例)
   3. [:sparkles::sparkles: VOP(`vopb` | `vopl`)](#sparklessparkles-vopvopb--vopl)
      1. [启用`vopb`](#启用vopb)
      2. [绑定`pll`](#绑定pll)
      3. [VOP 调试（hdmi 图层显示）](#vop调试hdmi-图层显示)
   4. [:sparkles::sparkles: 主副屏](#sparklessparkles-主副屏)
      1. [启用 HDMI 为副屏](#启用hdmi为副屏)
      2. [查看主副屏输出接口](#查看主副屏输出接口)
   5. [HDMI 引脚](#hdmi引脚)
   6. [显示桥接芯片](#显示桥接芯片)

## test diy and compile surfaceflinger

### 1. :white_check_mark: 虚拟机找不到 adb 设备

目前 rc 通过 usb 默认连接到了主机上，导致虚拟机里的 ubuntu 找不到 adb，根据 [In VMWare Player, I can't get adb devices to see my phone - Spiceworks](https://community.spiceworks.com/topic/2303147-in-vmware-player-i-can-t-get-adb-devices-to-see-my-phone)

可以在这里修改：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644291505272-a4660a930c8165733e3be82a551ea7e9e93b1e4b7cb1dc9d22c9c8cb8f4410d2.png)

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644291490776-a17326a3c58a579e8eb0500b03f35d227798b68c05143f45dc160e54686a0eba.png)

但是刚刚发现还是不行，还是检测不到，后来意识到应该是板子里的系统已经（类似）休眠了，因为蓝灯已经不闪了。所以重新插拔供电线，强制重启板子系统，**十几秒后就跳出 usb 连接哪个主机的弹窗**，在选择连接到 linux 之后，ubuntu 内就出现了 adb 设备。

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644291859846-df250a16abde64924d64c73c66369636d179e8ea760efd1ba1ff4b0f7dc6183b.png)

尽管目前已经解决了问题，但是有弹窗也意味着刚刚的配置是失效的，所以检查了一下，果然又变成“ask what to do”了，为了测试是否能够直接连到 vmware，我又加强了一下设置：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644291965505-85fc02a5056db7b8499280c7dbaa9d03053895e7430c1038c797e6822001617e.png)

然后**重新登录**之后，发现是可行的，设备还在：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644292015229-94eb3717c5014f721507b40bbf5900a9747a0da9b920e6d139d2df0e1abf658a.png)

但这不够，我们再加测**板子重新插拔电后是否能够直接连到虚拟机**。

测试结果很顺利，没有弹窗，虚拟机里的 adb 继续连上了。

并且`watch adb devices`可以发现，断电后设备消失，接电开机后设备自动显示。一切符合预期。

### 2. :white_check_mark: 启用投屏

1. 更改虚拟机的 vpn

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644292303819-535bf4b5161fe9a7835113252cf96809456a599eef593a12d4ecdecde5ef484d.png)

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644292319861-51e3b642065e81eff1efc0c1e6f81a14f161e891a0be68fe835e23b86529c785.png)

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644292355761-6b49a051496a88321ad542b062670b7d15c689560a05d624e4d0864775603fec.png)

2. 安装`scrcpy`

首先尝试`sudo apt install scrcpy`发现不行，好在`snap`里有，用`snap install scrcpy`装上了。

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644292426121-edc7fc3b7060801ff7336e8696b30718cc63b25b1e18edd10e5a4ea6a954198f.png)

目前一切顺利

### 3. :white_check_mark: 修改源码，尝试在`surfaceflinger`部分加入几句 log

**加 log 要在函数里加，不能直接加在文件级别**，这是 C++和 python 之类语言的一个比较明显的区别，否则会报函数找不到错误：

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644297427881-4965e9b5200916e5524700d061d8e622ba667a76db3f7becf8360bb498c8bc44.png)

所以我最后是这么加的：

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644297486127-01a0286a7798e5b1af0ebf954c4af043993cadb69ff848afd1f10f04e63f7b8f.png)

编译成功：

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644297376178-f3130420824d0b978095a5e477efb6615b17045bde2225334d3286ebc7df1818.png)

### 4. :white_check_mark: 推入系统

1. `read-only system` ![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644297365734-9aba960db2fae4365663aebfbad05efc10fa2cdf320954dbf2b7f9680a19c07d.png)

step 1. `disable-verity`

```sh
echo "rooting"; adb root;
echo "waiting to disable verity"; sleep 10; adb disable-verity;
echo "waiting to remount"; adb remount;
```

step 2. `adb push`

```sh
BUILD_SYSTEM=out/target/product/rk3399_Android10/system
ADB_SYSTEM=/system
MODULE=surfaceflinger
LIB_MODULE=lib$MODULE.so
adb push $BUILD_SYSTEM/bin/$MODULE /system/bin/$MODULE
adb push $BUILD_SYSTEM/lib/$LIB_MODULE /system/lib/$LIB_MODULE
adb push $BUILD_SYSTEM/lib64/$LIB_MODULE /system/lib64/$LIB_MODULE
```

### 5. :white_check_mark: 测试是否编译通过成功

确认已经有了我们修改的信息：

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/diary-public-1644299092756-8c4e6436e39052c591eef37c23a08975d665aa3141e0b1fc13c869981f670638.png)

测试通过！

## compile and run the first vr mode

### error of null pointer

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644322885417-1a0cfd0afbe3b026ac4eccdf3309404fed3c342a037d4712a8ce2245c8d76fe5.png)

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644323010078-bc993677892afa7108f54e21d796f58d348454602b6e311a1b81aa967731347c.png)

## output 4k

### 分辨率输出逻辑

> SDK 默认的分辨率是读取电视的 edid，然后选择最大输出的
>
> 需要在修改内核和配合 Setting 才可以

所谓，内核，也就是 rk3399 已经定义的一些分辨率输出的参数，每种都有自己的时序设置。4k 目前支持的是 3920x2160，如果我们想要 3920x1080，得自己定制。

设置的话，按照题主的摸索，如下：

> 谢谢，修改内核代码搞定了 kernel\drivers\video\rockchip\hdmi\rockchip-hdmi.h #define HDMI_VIDEO_DEFAULT_MODE HDMI_1280X720P_60HZ 修改为 HDMI_1920x1080P_60HZ

所以要去`kernel/drivers/video/rockchip/hdmi/`下找到`rockchip-hdmi/h`文件，修改器`HDMI_VIDEO_DEFAULT_MODE`，但实际上我拉的版本里目录已经完全不对了。

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644777515302-76380b70651884e8a52a800ec2f9d1af43781e5a10e465050c69ef24b084e869.png)

ref:

- [3399 的板子，HDMI 默认输出分辨率在哪里修改 - Firefly-RK3399 - Firefly 开源社区 3399 的板子，HDMI 默认输出分辨率在哪里修改](https://dev.t-firefly.com/thread-12261-1-1.html)

### TODO: check supported resolutions

```sh
sudo tvservice --status
sudo tvservice --modes=CEA
sudo tvservice --modes=RGB
```

ref:

- [graphics - Linux Framebuffer set resolution correctly - Stack Overflow](https://stackoverflow.com/questions/34904763/linux-framebuffer-set-resolution-correctly)

### TODO: 自定义分辨率输出参数

- [(1 条消息) rk3399 的 android7.1 平台新增 HDMI 特殊分辨率输出修改补丁\_androidRK3299 显示全屏-其它文档类资源-CSDN 文库](https://download.csdn.net/download/com6339663/14926373?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164477580616781685380768%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fdownload.%2522%257D&request_id=164477580616781685380768&biz_id=1&utm_medium=distribute.pc_search_result.none-task-download-2~download~first_rank_ecpm_v1~rank_v31_ecpm-1-14926373.pc_v2_rank_dl_default&utm_term=rk3399+hdmi+&spm=1018.2226.3001.4451.1)

### change hdmi output resolution

#### resolution 1. set `framebuffer` and `resolution`

ref:

- 重点看这个：:sparkles:[RK3399 开发板香橙派 4 开发板连接 HDMI 显示屏如何输出 4K 分辨率\_嵌入式系统与 MCU-面包板社区](https://mbb.eet-china.com/forum/topic/83050_1_1.html)
- 跟上面差不多：[firefly-rk3399 关于设置 4K 输出答疑 - 开发板使用 - 深圳风火轮科技 - Powered by Discuz!](http://arm-cn.com/thread-5422-1-1.html)

##### approach 1. define in device and burn

```yaml
# suggested: device/rockchip/rk3399/rk3399_mid/system.prop
# verified by mark: device/rockchip/common/system.prop
persist.sys.framebuffer.main = 2160x3840 persist.sys.resolution.main = 3840x2160@60
```

TODO: 不知道副显的 `framebuffer` 可不可以设置……（以及有没有必要设置）

![picture 53](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644787815780-89404bbb0699a969ab087996915c2a8c6fed47921f9a3ba4eeaeb478b8972036.png)

##### approach 2. use adb

```sh
adb shell setprop persist.sys.framebuffer.main 2160x3840
adb shell setprop sys.display.timeline 1

adb shell setprop persist.sys.resolution.main = 3840x2160@60
adb shell setprop sys.display.timeline 1
```

#### resolution 2. change dts

参考由 [4k HDMI output - Rockchip 3399 - armbian forum](https://forum.armbian.com/topic/14167-4k-hdmi-output/) 指引到的 [Comparing next-20200501...next-20200501-drm-rockchip · Kwiboo/linux-rockchip](https://github.com/Kwiboo/linux-rockchip/compare/next-20200501...next-20200501-drm-rockchip)，这是一份 patch，不过需要自己改。

不过实际上，我发现很多内容在我的开发板上都已经有了。

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644747572967-ef3850722867f96a735d3ec6002834319cde80524b2d06dbdf11ea2a25115997.png)

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644747585299-7255b0e7a32198d00bd2bf6bce5a9f26cec5ea0768e64792bbfcae4cccc58af3.png)

---

但后续发现，还是有些问题，对照国内朋友修改 dts 的记录，较为详细：[[RK3399] HDMI 正常输出 4K\_但行前路 无问西东-程序员宝宝 - 程序员宝宝](https://www.cxybb.com/article/m0_38022615/109221525)

核心思路：编译 kernel 时，碰到错误会给出报错行，用 vim 去查看该行，看看是啥问题，对应的删改即可，:sparkles::sparkles:。

这个问题主要是因为帖子中的`connect = <&vopb_out_hdmi>;` 已经不适用了，导致报错。

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644773468648-9619c41de0933010588837778104f0ca070b4fc7ef8d376b8371a74fd427ff2d.png)

考虑到这个只是用于开机 logo 的，所以无视，删掉重新编！

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644773568142-3d1f1dbf9d8c1b7072589b7002570e689909da3f65e1ceb221a901d5ea6efcd2.png)

---

新的问题是由于写错了：

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644773709386-68055eeb44e3e9c18e2509fb299f1207e7007c4cdfdc3284f984b93307c81889.png)

ref:

- sparkles: :sparkles: :sparkles: 修改 dts 的 patch [Comparing next-20200501...next-20200501-drm-rockchip · Kwiboo/linux-rockchip](https://github.com/Kwiboo/linux-rockchip/compare/next-20200501...next-20200501-drm-rockchip)

- [[RK3399] HDMI 正常输出 4K\_但行前路 无问西东-程序员宝宝 - 程序员宝宝](https://www.cxybb.com/article/m0_38022615/109221525)

- 修改 dts 的 patch 的来源与讨论： [4k HDMI output - Rockchip 3399 - armbian forum](https://forum.armbian.com/topic/14167-4k-hdmi-output/)

- 写到了部分`edid`相关的：[(1 条消息) [RK3399] HDMI 正常输出 4K30 帧 无法输出 60 帧以及设置分辨率的流程分析\_但行前路 无问西东-CSDN 博客\_hdmi 输出分辨率设置](https://blog.csdn.net/m0_38022615/article/details/109378391)

#### PASSED: change `RkConfig`

看起来对，也改起来很简单，但是我并没有找到对应的配置。

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644759185068-465f770f9da3ec1ba5b5eb8349cfcce5ab6bd64b7faad713b4fc076f0e8ac481.png)

以下是我们的配置：

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644759280740-26f86c67effb30bd3ad77e1b652eaf4061be62cfc031c9509bdddb8b47a5c11a.png)

ref:

- [[v3,5/5] video: rockchip: Support 4K resolution for rk3399, HDMI - Patchwork](https://patchwork.ozlabs.org/project/uboot/patch/20200402114125.2501-6-jagan@amarulasolutions.com/)

### 主板支持 4k60hz 输出修改

基于 rockchip 开发大佬的文章 [(1 条消息) [RK3399][Android7.1] HDMI 显示屏(副屏)调试记录小结\_Kris Fei's blog-CSDN 博客\_hdmi 调试](https://blog.csdn.net/kris_fei/article/details/88875516?spm=1001.2014.3001.5502) ，可以知道修改主板 hdmi 输出主要改以下这几文件：

1. drm_edid.c： edid 相关
2. dw-hdmi.c： HDMI 驱动，包括内部 I2C 接口实现
3. d_hdmi-rockchip.c: drm 框架部分

修改如下：

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644784592881-bc178a2b8c0e656491b1d9d391ce824d505de6d59b27d6e597771aafdb56f7cc.png)

此外根据官方文档，还要确认一下白名单：

![picture 54](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644788099106-e45cfb1288e41b2fcb8fc492775d1c1caafadaffe853db7c11b598d323dd485f.png)

好在都是有的：

![picture 55](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644788109475-28fb54c3d9cf1c8ad4b5c8a86960175d53cb47c9baac61453e3a3f262390d367.png)

### 测试 edid 修改结果

```sh
/sys/class/drm/card0-HDMI-A-1/edid
```

![picture 43](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644784205395-77d07db4f846454f863e84b9907056d36fa1f4833db96a92cf163f5e8feb2d6f.png)

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644784231104-4eba6721ee143c9eae3ec7cd3225c0bb3544977654ededb257be306bce6db5ea.png)

ref:

- [(1 条消息) [RK3399][Android7.1] HDMI 显示屏(副屏)调试记录小结\_Kris Fei's blog-CSDN 博客\_hdmi 调试](https://blog.csdn.net/kris_fei/article/details/88875516?spm=1001.2014.3001.5502)

## HDMI 相关介绍

### EDID

- [EDID - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/EDID)

### HDMI 比例

在 [hdmi.h - include/linux/hdmi.h - Linux source code (v5.16.9) - Bootlin](https://elixir.bootlin.com/linux/latest/source/include/linux/hdmi.h#L176) 可以找到 HDMI 比例的定义：

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644783773364-f0284efe7c70b41b399d446a83c40fd85a6f43556b632266c1d4f832b02a4c0b.png)

### :sparkles::sparkles: VOP(`vopb` | `vopl`)

ref:

- [如何选择显示桥接芯片（MIPI、LVDS、HDMI、eDP、RGB 转换） - 知乎](https://zhuanlan.zhihu.com/p/398362901)

#### 启用`vopb`

官方文档指示，想使用哪种 VOP，只要关闭另一种就可以了：

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644785638794-720b5551c0e5804c25206a1916857db85a96629eec8f7d0ef2e4d4c18641c9fc.png)

在`kernel`仓库寻找我们的关键字，找到`rk3399`和`rockpi-4b`相关的文件：

![picture 47](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644785664838-59156bd86378861e4fd2a7d130470dad45a93c7d60fdf8b737fc58269091829a.png)

确认内部的信息，是把`vopl`关闭的，也就是开启了`vopb`，也就是默认打开了 4k 输出：

![picture 48](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644785690918-b5e757b3f43908a931342bdca52d4ec781e36bd7838bdd0e51017f8240e8c043.png)

#### 绑定`pll`

官方文档指示，需要将目标 vop 挂载到`vpll`，另一个挂载到`cpll`：

![picture 49](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644785899708-1add03724419fab2616149e0a237faf8a18ee8d6a4e2537f764955ff5da436b7.png)

还是同一个文件，检查确认，是默认的：

![picture 50](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644785982133-0ed8b67309f7dae406937160b2ce5cbe82583ebb151e44174960c02c32f5cd29.png)

ref:

- [(1 条消息) [RK3399][Android7.1] Display 中的 VOP 模块介绍\_Kris Fei's blog-CSDN 博客\_vopb vopl](https://blog.csdn.net/kris_fei/article/details/79030144)

#### VOP 调试（hdmi 图层显示）

```sh
cat /d/dri/0/summary
```

主要查看`Connector`是不是`HDMI-A`，以及`Display mode`:

![picture 56](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644788466119-b7e85d12c1120867bdbb4c9877224ca049ee785b65de7a97b8f5cd61bd30bba7.png)

每个图层的大小变化(`src`(source) --> `dst`(destination))也是很重要的信息：

![picture 57](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644788502156-951c67303be8ae6c04062b187385c28a903365d2b727afc9099529370d5f4efe.png)

### :sparkles::sparkles: 主副屏

#### 启用 HDMI 为副屏

```sh
# device/rockchip/rk3368/rk3368_mid/system.prop
sys.hwc.device.extend=HDMI-A
```

![picture 51](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644787563143-77fd26d8d6af22ae3851bcd8f1c9e7d5a2f854107b754174f81a41a8f4e983c1.png)

#### 查看主副屏输出接口

```sh
sys.hwc.device.main # 主显输出接口
sys.hwc.device.aux  # 副显输出接口
```

![picture 52](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/rockchip4-vr-manual-1644787683624-44c6d3d1db10e0ceac3059d96db4b4cbf30af518670379a33d4ae58619a17e11.png)

### HDMI 引脚

- [HDMI 介绍与流程 - TaigaComplex - 博客园](https://www.cnblogs.com/TaigaCon/p/3840653.html)

### 显示桥接芯片

看不懂……所以瑞芯微文档里各种组合是啥意思：

2.4.1 EDP(vopb) + HDMI(vopl) 2.4.2 LVDS(vopl) + HDMI(vopb) 2.4.3 MIPI(vopb) + HDMI(vopl) 2.4.4 HDMI(vopb) + DP(vopl)

- [如何选择显示桥接芯片（MIPI、LVDS、HDMI、eDP、RGB 转换） - 知乎](https://zhuanlan.zhihu.com/p/398362901)
