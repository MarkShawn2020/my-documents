# 趣立编译笔记

> For better reading experience, refer to [blog: 趣立编译笔记](https://markshawn.com/docs/@arpara/android-framework/quli/compile).

- [basic info](#basic-info)
- [pre-compile](#pre-compile)
  - [install dependencies (necessary)](#install-dependencies-necessary)
  - [increase swap area (necessary in low memory machine)](#increase-swap-area-necessary-in-low-memory-machine)
  - [config environment variables (recommended private usage)](#config-environment-variables-recommended-private-usage)
- [compile](#compile)
  - [auto build script](#auto-build-script)
  - [how to speed up compilation](#how-to-speed-up-compilation)
- [compile efficiency](#compile-efficiency)
- [bugfix](#bugfix)
  - [FIXED: `cd is not defined` when `source ./build/envsetup.sh`](#fixed-cd-is-not-defined-when-source-buildenvsetupsh)
  - [PASS: `Could not create symlink` when `source ./build/envsetup.sh`](#pass-could-not-create-symlink-when-source-buildenvsetupsh)
  - [PASS: `Disallowed Path Tools` when compiling](#pass-disallowed-path-tools-when-compiling)

## basic info

```yaml
# premise
AF_SOURCE: ~/work@arpara/AF1020
AF_OEM: $AF_SOURCE/forluci/oem

# const
AF_ROOT: $AF_OEM/sxr2130_apps/LINUX/android
```

## pre-compile

### install dependencies (necessary)

> ref: [搭建构建环境  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/docs/setup/build/initializing#installing-required-packages-ubuntu-1804)

:::caution
必须要按照趣立的依赖进行安装，按照谷歌的会报错，因为趣立的依赖里包含谷歌未给出的，例如`openssl`
:::

```sh
# [X] AOSP dependencies given officially by google for Ubuntu 18
sudo apt-get install git-core gnupg flex bison build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 libncurses5 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev libgl1-mesa-dev libxml2-utils xsltproc unzip fontconfig

# [Y] dependencies given by quli
sudo apt-get install -y libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-dev g++-multilib git flex bison gperf build-essential libncurses5-dev:i386 tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386 dpkg-dev libsdl1.2-dev git-core gnupg flex bison gperf build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev libgl1-mesa-dev libxml2-utils xsltproc unzip m4 lib32z-dev ccache libssl-dev libxml-simple-perl bc rsync
```

### increase swap area (necessary in low memory machine)

see: [external: increase-swap-area-recommended](../general/AndroidFramework/02-aosp-compile/index.md#3-increase-swap-area-recommended)

### config environment variables (recommended private usage)

```sh
AF_SOURCE="~/work@arpara/AF1020"

export AF_OEM="$AF_SOURCE/forluci/oem"
alias af-oem="cd $AF_OEM"

export AF_ROOT="$AF_OEM/sxr2130_apps/LINUX/android"
alias af-root="cd $AF_ROOT"
```

## compile
 
> - Android官方: https://source.android.com/docs/setup/build/building
> - arpara编译: https://arpara2021.feishu.cn/wiki/wikcn1lWQsHDluKB5WHwm83WlJd?appStyle=UI4&domain=www.feishu.cn&locale=en-US&tabName=space&theme=light&userId=7085189359086878748

:::caution
使用`m`编译无法通过，要基于`build.sh`
:::

### auto build script

```sh
# at path: xx/oem

cd sxr2130_apps/LINUX/android

source ./build/envsetup.sh

choosecombo debug kona eng V02A

./build.sh dist -j8 | tee "build_$(date +"%m-%dT%H:%M").log"

# 回到 /oem 目录下   注:依赖/pgk,将pkg放置于系统根目录/pgk
cd ../../..
./bld_prj.sh V02A                           //编译oem   
./make_usf.sh dir                           //打包   生成usf刷机包
```

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/compile-1661847002308-9c3f8bc0082f05543f409ced04d7163670e86eda431dde7ad70e109af49f7780.png)  

### how to speed up compilation

see: [external: how-to-speed-up-aosp-building](../general/AndroidFramework/02-aosp-compile/index.md#how-to-speed-up-aosp-building)

## compile efficiency

:::tip
`ln out` implementation not yet passed, we caught one `-j1` log at: `$AF_LOGS/build_09-04T00:33.log`, with its last lines as:

```txt
[  3% 1557/47140] Export includes file: out/soong/.intermediates/system/libhidl/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/android/hidl/manager/1.0/IServiceManager.h -- out/target/product/kona/obj/SHARED_LIBRARIES/vendor.qti.hardware.audiohalext@1.0.vendor_intermediates/export_includes
[  3% 1558/47140] target Generated: audio_kernel_headers_32 <= vendor/qcom/opensource/audio-kernel/include/uapi/linux/avtimer.h
FAILED: out/target/product/kona/obj/vendor/qcom/opensource/audio-kernel/include/linux/avtimer.h
/bin/bash -c "\$(cd out/target/product/kona/obj/KERNEL_OBJ; ../../../../../../../kernel/msm-4.19/scripts/headers_install.sh ../../../../../../../out/target/product/kona/obj/vendor/qcom/opensource/audio-kernel/include/linux/ ../../../../../../../vendor/qcom/opensource/audio-kernel/include/uapi/linux/ avtimer.h)"
/bin/bash: ../../../../../../../kernel/msm-4.19/scripts/headers_install.sh: No such file or directory
ninja: build stopped: subcommand failed.
07:31:19 ninja failed with: exit status 1

^[[0;31m#### failed to build some targets (15:06 (mm:ss)) ####^[[00m

============================================
[build.sh]: FAILED: make dist -j1 ENABLE_AB=true BOARD_DYNAMIC_PARTITION_ENABLE=true SHIPPING_API_LEVEL=29
============================================
```
:::

| sDate       | eDate       | minutes | env                                     | note |
| ----------- | ----------- | ------- | --------------------------------------- | ---- |
| 09-06T03:27 | 09-06T04:10 | 43      | /aospPool/mark2, j88, ccache-2, inplace |      |
| 09-06T00:29 | 09-06T03:26 | 177     | /aospPool/mark2, j88, ccache-1, inplace |      |
| 09-03T06:02 | 09-03T06:49 | 47      | af-root, j88, ccache-2, inplace         |      |
| 09-03T05:12 | 09-03T06:00 | 48      | af-root, j88, ccache-2, inplace         |      |
| 09-03T03:02 | 09-03T05:10 | 128     | af-root, j88, ccache-1, inplace         |      |
| 09-02T18:34 | 09-02T20:38 | 124     | af-root, j88, ccache-0, inplace         |      |

## bugfix

### FIXED: `cd is not defined` when `source ./build/envsetup.sh`

这是由于我在 `~/.bash_profile` 中配置了 `alias .="cd ."` 这样的东西，可能超前使用了`cd`，去掉这些之后就可以了。

另外，最好用 `bash`，而非`zsh`（google官方推荐）。

### PASS: `Could not create symlink` when `source ./build/envsetup.sh`

problem:

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/compile-1661508344387-b9c65a4391c7df529dd1e7b4070077a26ceb38d5f144a7eeb4e056f330b2e7ea.png)  

solution: 咨询趣立的结果是：“不影响”：

  ![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/compile-1661508944461-cb7c443d0fbfbcfddad80f59927e4fd7ba8155015c37f0d2221fa8895398ce4d.png)  

### PASS: `Disallowed Path Tools` when compiling

1. 咨询趣立的结论是这个可以忽视。

2. 具体参考google的变动：

  - [Build System Changes for Android.mk Writers](https://android.googlesource.com/platform/build/+/master/Changes.md#PATH_Tools)

  以及（如果明确副作用的话）可以将工具写入配置文件中，参考：https://forum.xda-developers.com/t/guide-complete-android-rom-development-from-source-to-end.2814763/post-80923041

