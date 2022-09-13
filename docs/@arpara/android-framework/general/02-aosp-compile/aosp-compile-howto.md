# aosp compile

- [make commands](#make-commands)
- [target product: `eng/userdebug/user`](#target-product-enguserdebuguser)
- [BEST-PRACTICE: install preparations if in need](#best-practice-install-preparations-if-in-need)
- [BEST-PRACTICE: auto make: `make || make -j3`](#best-practice-auto-make-make--make--j3)
- [how to check detailed log in file (when building)](#how-to-check-detailed-log-in-file-when-building)
- [why ninja start so slow?](#why-ninja-start-so-slow)
- [A totally failed attempt to compile rk codes/patch onto AOSP](#a-totally-failed-attempt-to-compile-rk-codespatch-onto-aosp)
  - [conflicts of meson python version requirements](#conflicts-of-meson-python-version-requirements)
  - [compile `librga`](#compile-librga)
  - [realization of impossibility](#realization-of-impossibility)
- [run aosp in avd](#run-aosp-in-avd)
  - [resolution 1. use build version of `full-eng`](#resolution-1-use-build-version-of-full-eng)
  - [resolution 2. use avd](#resolution-2-use-avd)
  - [resolution 3. run arm on qemu](#resolution-3-run-arm-on-qemu)
  - [how to increase partition size](#how-to-increase-partition-size)

## make commands

- :sparkles: a good instruction :sparkles:: [(23 条消息) Android 高版本 P/Q/R 源码编译指南\_IT 先森-CSDN 博客\_android 源码编译](https://blog.csdn.net/tkwxty/article/details/111684291), include: 动态分区刷机的方法, 解决 Android 高版本编译 ssd 固态硬盘空间不够的问题

```yaml
make update-api: 更新API文件，在framework API改动之后，需要首先执行该命令来更新API，公开的API记录在frameworks/base/api目录下
make: Android默认系统编译指令，会编译出整个系统的所有镜像(其实质最终执行的是make droid)

make sdk: 编译出Android的SDK开发套件
make clean-sdk: 清理SDK的编译产物

make clean: deletes all of the output and intermediate files for this configuration. This is the same as `rm -rf out/<configuration>/`,通常删除的是整个Android源码工程的out/*目录
make installclean: 当我们在执行切换编译目标时可以执行make installclean，用以清除之前编译生成的文件，但是又不会将整个out目录清空，这样可以加快编译目标的构建速度

make framework: 编译所有Javaframework内容(做Android framework开发的小伙们对这条命令应该是再熟悉不过的了)。
make services: 编译系统服务和相关内容

make bootimage: 编译生成boot.img
make systemimage: 编译生成system.img
make vendorimage: 编译生成vendor.img
make superimage: 编译生成superi.img
```

## target product: `eng/userdebug/user`

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-compile-howto-1644770866675-f652b37aaa6b2ebd8848d90e1aaaa77d7203e8f625ce778fa1ba4ff3364f0e51.png)

ref:

- [Android 编译选项 eng、user、userdebug 的区别 - petercao - 博客园](https://www.cnblogs.com/bluestorm/p/11125055.html)

## BEST-PRACTICE: install preparations if in need

```sh
sudo apt-get install git-core gnupg flex bison build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 libncurses5 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev libgl1-mesa-dev libxml2-utils xsltproc unzip fontconfig
```

ref:

- [搭建构建环境  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/build/initializing#installing-required-packages-ubuntu-1804)

## BEST-PRACTICE: auto make: `make || make -j3`

> :warning: Since there are different making speed for different partition of aosp build, so we can use the first `make` to automatically build as a faster speed and then decrease to a lower when stuck.

```sh
(make || make -j3) && echo "finished"
```

## how to check detailed log in file (when building)

```sh
gzip -cd out/verbose.log.gz | less -R
```

ref:

- [build - AOSP make verbose - Stack Overflow](https://stackoverflow.com/questions/42925014/aosp-make-verbose)

## why ninja start so slow?

直接给出结论：大部分情况下，ninja 在启动阶段很慢的原因，都与整编依赖有关。

例如，这一次，我把博文的 `hmdservice | hmdclient_ndk` 放到了 `AOSP/vendor/arpara/` 下，并且在 `renderengine` 的 `Android.bp` 的 share 库里包含了 `libhmdclient_ndk`。 由于 `hmdservice` 里带了 `gml` 和 `cv`， 所以导致初始动作巨慢。

![picture 52](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-compile-howto-1645852992297-0a6962dcb37b031975a46b7f23a651842f3a37a903e13aca782b5cb8b19e10fd.png)

我不知道这一步 ninja 具体在干嘛，但估计和“打包”之类的动作应该差不多。

好在下一次编译就会快很多了。

!!! warning 但是注意，如果使用 `mm` 的话，是会重新编译整个依赖的，所以又会很慢，因此尽量用 `m XXX` 即可。

## A totally failed attempt to compile rk codes/patch onto AOSP

### conflicts of meson python version requirements

meson requires python version > 3.7 (ref: [FFY00/mesonpy: Meson PEP 517 Python build backend](https://github.com/FFY00/mesonpy)), however my default version is 3.6.9.

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643087935681-cae1ef23e1bb4f426ee84613734b1971b8f67b6b41b399ec7912b131087475f8.png)

### compile `librga`

搞了半天，莫名其妙已经有了`librga`，也许把这个拷到`/usr/bin`下就可以了。

![picture 30](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643091737140-cb7e48d73979942cf47885f781656a7c06d7e2d31809a57cd3fecb7abe34768e.png)

但是，这时我正好在看`https://github.com/rockchip-linux/linux-rga`，发现直接给了 AOSP 的编译方法……

我这下才发现，被另一篇文章坑的有多惨……

对比一下：

这是`linux-rga`指定的编译方法：

![picture 31](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643091854481-b44f540f1b11955ace900a589c5c2d11d28cbffebbf76000045e8647eead2ed0.png)

而这是这个人的帖子：

![picture 32](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643091877616-fecbb622e8971a218cdbcba0148062e30f2d0f952041b8ffd79d94d9b8d80746.png)

我一路被坑爆掉了，各种依赖缺失，一个个找……吐了啊……

### realization of impossibility

![picture 33](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643093693014-df3c8f45ac4e76c7c03d83046c602f4fd59e6006dd92241a632936ed442b4e18.png)

## run aosp in avd

### resolution 1. use build version of `full-eng`

1. common build: `m aosp_arm64-eng`

2. recommended by emulator for my machine: `m aosp_x86_64-eng`

3. recommended online in order to run emulator, which is inner 'arm64': `m full-eng`

compile success of `m full-eng`:

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-compile-howto-1643502046060-43128f1f27ac933f2857ec703eba13559887ac32eb3301231943aa5cf5916c9b.png)

### resolution 2. use avd

```sh
m sdk-phone-arm64
```

ref:

- [使用 Android 模拟器虚拟设备  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/setup/create/avd)

### resolution 3. run arm on qemu

```sh
qemu-system-aarch64
```

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-compile-howto-1643514178964-e8d97c7c99dad22b38e9df3fee5f98208fd0b373318e2420e2b95b90bcd07812.png)

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-compile-howto-1643514114839-8d612b6d498344fa330f5ca01bc99ee72c77de12e7f76324434191c59336441e.png)

ref:

- [Arm System emulator — QEMU documentation](https://www.qemu.org/docs/master/system/target-arm.html#:~:text=QEMU%20can%20emulate%20both%2032,a%2064%2Dbit%20Arm%20machine.)

- [can arm run on qemu - Google Search](https://www.google.com.hk/search?q=can+arm+run+on+qemu&newwindow=1&sxsrf=APq-WBvFNnymRMqLigJ9HjE9BLc77SU3pw%3A1643513796283&ei=xAf2YazdEIaVseMPnd6a0AY&ved=0ahUKEwisz4qAxtj1AhWGSmwGHR2vBmoQ4dUDCA4&uact=5&oq=can+arm+run+on+qemu&gs_lcp=Cgdnd3Mtd2l6EAM6BwgAEEcQsANKBAhBGABKBAhGGABQ7AtY0g5gthFoAnACeACAAawBiAHLA5IBAzAuM5gBAKABAcgBCMABAQ&sclient=gws-wiz)

### how to increase partition size

> :warning:
>
> 1. first converting the system.img to a raw image may be need
> 2. You will not be able to use a system.img partition larger than the one defined in BoardConfig at `device/generic/x86_64/BoardConfig.mk`

```sh
PLATFORM=generic_x86_64
IMG_NAME=userdata-qemu
SIZE_TO_ADD=3092

croot
cd out/target/product/$PLATFORM
dd if=/dev/zero bs=1M count=$SIZE_TO_ADD >> $IMG_NAME.img
e2fsck -f $IMG_NAME.img && resize2fs $IMG_NAME.img
```

ref:

- [android - How to increase system.img partition size - Stack Overflow](https://stackoverflow.com/questions/34560562/how-to-increase-system-img-partition-size)
