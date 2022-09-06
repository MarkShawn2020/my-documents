# 趣立编译笔记

> For better reading experience, refer to [blog: 趣立编译笔记](https://markshawn.com/docs/@arpara/android-framework/quli/compile).

- [basic info](#basic-info)
  - [path variables](#path-variables)
  - [project structure of OEM](#project-structure-of-oem)
  - [project structure of Android](#project-structure-of-android)
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

### path variables

```yaml
# premise
AF_SOURCE: ~/work@arpara/AF1020
AF_OEM: $AF_SOURCE/forluci/oem

# const
AF_ROOT: $AF_OEM/sxr2130_apps/LINUX/android
```

### project structure of OEM

```txt
➜  oem tree -L 2
.
├── A11B
│   ├── BATTERY.PROVISION.A11B
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.e11
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   └── logo1.bmp
├── NORMAL
│   ├── BATTERY.PROVISION
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   ├── logo1.bmp
│   ├── pm_config_pam.c
│   ├── pm_config_target.c
│   ├── por.py
│   ├── railway_config.c
│   └── slpi
├── V02A
│   ├── BATTERY.PROVISION.V02A
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.e11
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   ├── logo1.bmp
│   ├── pm_config_pam.c
│   ├── pm_config_target.c
│   ├── pm_sbl_boot_oem.c
│   ├── por.py
│   ├── railway_config.c
│   └── slpi
├── about.html          // 基线信息都在这（趣立）
├── bld_adsp.sh
├── bld_aop.sh
├── bld_boot.sh
├── bld_cdsp.sh
├── bld_common.sh
├── bld_prj.sh
├── bld_slpi.sh
├── bld_tz.sh
├── common
│   ├── Core
│   ├── build
│   ├── config
│   ├── core_qupv3fw
│   └── sectools
├── contents.xml
├── cpota.sh
├── dir
│   ├── dir.zip
│   └── ufs
├── make_usf.sh
├── ota.py
├── sxr2130_adsp
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.adsp.prodQ.json
│   └── adsp_proc
├── sxr2130_aop
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_AAAAANAZO.json
│   └── aop_proc
├── sxr2130_apps
│   └── LINUX
├── sxr2130_boot
│   ├── BuildProducts.txt
│   └── boot_images
├── sxr2130_btfm
│   └── btfm_proc
├── sxr2130_btfm_hsp
│   └── btfm_proc
├── sxr2130_cdsp
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.cdsp.prodQ.json
│   └── cdsp_proc
├── sxr2130_cvp
│   ├── cvp_proc
│   └── manifest.xml
├── sxr2130_npu
│   └── npu_proc
├── sxr2130_slpi
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.slpi.prodQ.json
│   └── slpi_proc
├── sxr2130_spss
│   └── spss_proc
├── sxr2130_tz
│   ├── BuildProducts.txt
│   └── trustzone_images
├── sxr2130_tzapps
│   └── qtee_tas
├── sxr2130_video
│   ├── manifest.xml
│   └── venus_proc
├── sxr2130_wigig
│   ├── BuildProducts.txt
│   └── wigig_proc
├── sxr2130_wlan_hsp
│   └── wlan_proc
└── sxr2130_wlan_hst
    └── wlan_proc

47 directories, 71 files
```

### project structure of Android

```log
➜  android git:(master) ✗ ll
total 32K
lrwxrwxrwx 1 mark mark   19 Sep  5 16:34 Android.bp -> build/soong/root.bp
-r--r--r-- 1 mark mark   92 Aug 25 17:25 Makefile
drwxrwxr-x 1 mark mark  692 Aug 25 17:25 art
-rwxrwxr-x 1 mark mark  199 Sep  5 16:33 auto-build.sh
drwxrwxr-x 1 mark mark  360 Aug 25 17:26 bionic
drwxrwxr-x 1 mark mark   36 Aug 25 17:23 bootable
lrwxrwxrwx 1 mark mark   26 Sep  5 16:34 bootstrap.bash -> build/soong/bootstrap.bash
drwxrwxr-x 1 mark mark  160 Sep  5 16:34 build
lrwxrwxrwx 1 mark mark   48 Sep  5 16:34 build.sh -> vendor/qcom/opensource/core-utils/build/build.sh
drwxrwxr-x 1 mark mark  384 Aug 25 17:25 cts
drwxrwxr-x 1 mark mark  212 Aug 25 17:26 dalvik
drwxrwxr-x 1 mark mark   34 Aug 25 17:24 developers
drwxrwxr-x 1 mark mark  222 Aug 25 17:23 development
drwxrwxr-x 1 mark mark  104 Aug 25 17:26 device
drwxrwxr-x 1 mark mark   20 Sep  5 16:34 disregard
drwxrwxr-x 1 mark mark 5.1K Aug 25 17:25 external
drwxrwxr-x 1 mark mark  134 Aug 25 17:23 frameworks
drwxrwxr-x 1 mark mark  138 Aug 25 17:24 hardware
drwxrwxr-x 1 mark mark   86 Sep  5 16:34 kernel
drwxrwxr-x 1 mark mark  814 Aug 25 17:26 libcore
drwxrwxr-x 1 mark mark  422 Aug 25 17:26 libnativehelper
drwxrwxr-x 1 mark mark  846 Sep  6 06:34 logs
drwxrwxr-x 1 mark mark    8 Sep  3 10:24 logs.bak
drwxrwxr-x 1 mark mark 1.8K Sep  5 16:34 out
drwxrwxr-x 1 mark mark  124 Aug 25 17:26 packages
drwxrwxr-x 1 mark mark   38 Aug 25 17:26 pdk
drwxrwxr-x 1 mark mark  112 Aug 25 17:25 platform_testing
drwxrwxr-x 1 mark mark  400 Aug 25 17:25 prebuilts
-rw-rw-r-- 1 mark mark  101 Sep  2 11:33 readme.md
drwxrwxr-x 1 mark mark  500 Aug 25 17:24 sdk
drwxrwxr-x 1 mark mark  110 Aug 25 17:24 shortcut-fe
-rwxrwxr-x 1 mark mark 4.5K Aug 25 17:24 sync.sh
drwxrwxr-x 1 mark mark  566 Aug 25 17:23 system
drwxrwxr-x 1 mark mark   94 Aug 25 17:26 test
drwxrwxr-x 1 mark mark   42 Aug 25 17:26 toolchain
drwxrwxr-x 1 mark mark  288 Aug 25 17:24 tools
drwxrwxr-x 1 mark mark   50 Aug 25 17:26 vendor
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
TODO: `ln out` implementation not yet passed, however we caught one `-j1` log at: `$AF_LOGS/build_09-04T00:33.log`, with its last lines as:

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

