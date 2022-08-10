# Manual/bugfix of compiling arpara hmdservice on AOSP 10

> 一些已知的问题，主要集中在环境配置与语法层面，实际效果还未知，usb 接口变动的事则值得注意

1. [环境要求](#环境要求)
2. [全局变量（本地示例）](#全局变量本地示例)
3. [编译总览](#编译总览)
4. [step 1. 初始化项目](#step-1-初始化项目)
   1. [fix 1. `glm` 路径修正](#fix-1-glm-路径修正)
   2. [项目拷贝](#项目拷贝)
   3. [`Android.mk` 配置](#androidmk-配置)
      1. [fix 2. `libusbhost`](#fix-2-libusbhost)
      2. [fix 3. `LOCAL_CFLAGS`](#fix-3-local_cflags)
      3. [Android.mk 事先编辑的重要性](#androidmk-事先编辑的重要性)
5. [step 2. usb 接口修复](#step-2-usb-接口修复)
   1. [修复需要新增`timeout`的三个接口`manufacture | product | serial`，单位是毫秒，目前改成了 5000](#修复需要新增timeout的三个接口manufacture--product--serial单位是毫秒目前改成了5000)
   2. [删除`*name`没有用到，接口也变了的一句代码](#删除name没有用到接口也变了的一句代码)
6. [step 3. 代码语法修复](#step-3-代码语法修复)
   1. [:white_check_mark: `fall through`](#white_check_mark-fall-through)
   2. [:white_check_mark: 删除空指针问题，转为赋值为空指针](#white_check_mark-删除空指针问题转为赋值为空指针)
   3. [:white_check_mark: 其他一些类型转换](#white_check_mark-其他一些类型转换)
7. [编译成功效果](#编译成功效果)
   1. [:sparkles: build success of `libhmdservice`](#sparkles-build-success-of-libhmdservice)
   2. [:sparkles::sparkles: build success of `hmdservice`](#sparklessparkles-build-success-of-hmdservice)
8. [引申阅读/其他分析](#引申阅读其他分析)
   1. [translate `Android.mk`](#translate-androidmk)
   2. [:white_check_mark: `Android.bp: Path is outside directory`](#white_check_mark-androidbp-path-is-outside-directory)
   3. [:white_check_mark: `error: frameworks/native/services/hmdservice/service: MODULE.TARGET.SHARED_LIBRARIES.libhmdservice already defined by frameworks/native/services/hmdservice/service.`](#white_check_mark-error-frameworksnativeserviceshmdserviceservice-moduletargetshared_librarieslibhmdservice-already-defined-by-frameworksnativeserviceshmdserviceservice)
   4. [:white_check_mark: `fatal error: 'usbhost/usbhost.h' file not found`](#white_check_mark-fatal-error-usbhostusbhosth-file-not-found)
   5. [usb cover progress](#usb-cover-progress)
      1. [:white_check_mark: `error: no matching function for call to 'usb_device_get_manufacturer_name'`](#white_check_mark-error-no-matching-function-for-call-to-usb_device_get_manufacturer_name)
      2. [:white_check_mark: `error: no matching function for call to 'usb_device_get_string'`](#white_check_mark-error-no-matching-function-for-call-to-usb_device_get_string)
   6. [:white_check_mark: `error: unknown type name 'usb_device'; did you mean 'UsbDevice'?`](#white_check_mark-error-unknown-type-name-usb_device-did-you-mean-usbdevice)
   7. [:white_check_mark: 变量没有使用的情况与手动修复过程（放弃，后来直接配 mk 了）](#white_check_mark-变量没有使用的情况与手动修复过程放弃后来直接配mk了)
   8. [:white_check_mark: `FAILED: ninja: 'frameworks/native/services/hmdservice/service/frameworks/native/services/hmdservice/service/common/IHmdServer.cpp', needed by 'out/target/product/generic_arm64/obj/SHARED_LIBRARIES/libhmdservice_intermediates/frameworks/native/services/hmdservice/service/common/IHmdServer.o', missing and no known rule to make it`](#white_check_mark-failed-ninja-frameworksnativeserviceshmdserviceserviceframeworksnativeserviceshmdserviceservicecommonihmdservercpp-needed-by-outtargetproductgeneric_arm64objshared_librarieslibhmdservice_intermediatesframeworksnativeserviceshmdserviceservicecommonihmdservero-missing-and-no-known-rule-to-make-it)

## 环境要求

- 需要有`android 10+`的整编环境。
- 需要有`arpara hmdservice`的一套代码。

## 全局变量（本地示例）

```sh
ARPARA=$HOME/work@luci/immerex/arpara-hmdservice    # change
AOSP=~/arpara/android/android-10.0.0_r1             # change
NATIVE=$AOSP/frameworks/native                      # no need to change
```

## 编译总览

1. 之前纠结了好久`mk`转`bp`的问题，也转过，也能用，后来发现没有必要，`Android 10`会自己检测有没有`mk`或者`bp`文件，然后都可以编，两个文件不能同时有（准确地说，是里面的内容不能有重合，比如两个模块名一样），否则会报`XXX has declared`错。
2. 所以这里推荐，也不用转了，直接基于目前的 `Android.mk` 改，不然后期不太好和杭州同学同步维护，主要现在 `Android.mk` 还有很大问题，可能会一直修改，没有成型，那转出来的 `bp` 也是没成型的，后期到底是改 `mk` 还是改 `bp` 这就涉及到一个同步问题。
3. 目前的共识是只要跑一个 service 即可，观察`service`目录结构，，会发现虽然有两个`Android.mk`文件，但是核心是`service/hmdservice/service/Android.mk`这个文件，里面有两个模块名，一个叫`libhmdservice`这是服务端，一个叫`hmdservice`这是客户端，客户端依赖于服务端，所以可以先编服务端，直接`m libhmdservice`即可，编好后可以再编客户端，直接`m hmdservice`接口。
4. 编完后，`externals`里面的文件与模块都会打包到`hmdservice/service`目录下，如下，可以看到原先用`..`等引用的文件目录现在都同级了。 ![picture 155](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643325369686-dbf6353e65673ccf50dc225bb0813c756654bd5e9050afeb884fd2e25ce230c2.png)

## step 1. 初始化项目

### fix 1. `glm` 路径修正

景喆发我的 sdk 里，核心是`service`与`externals`两个文件夹。

其中 `externals` 文件夹的目录结构如下：

![picture 152](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643324368419-b20be18152a2cbb0d1e959033ebf5fa4cd46036cb96a46447d6c733971ee82ab.png)

注意，`glm`作为外部库，实际起作用的是绿框部分。

但是在 `Android.mk` 文件内配置的路径却为：

![picture 153](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643324448613-5fe847f970fa6c394982b88ecb1935008e29a30603ea1d2670f09f26dfc39e07.png)

这是不对的，这样编译，会导致 `glm` 下的所有文件都找不到。

在不改变文件结构的情况下，可以直接修改 `Android.mk` 将 `glm`层级加深一级。

![picture 154](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643324597991-133228183c45f0a6d5257c2bdaeaf8bcebf5b61543b6e7c0668f2b0aac83e33a.png)

### 项目拷贝

接着将 `arpara-hmdservice` 的一套代码直接拷贝到 `native` 下，保持目录结构。

```sh
cp -r $ARPARA/* $NATIVE
```

### `Android.mk` 配置

考虑目前采用 `Android.mk` 方案，所以 `bp` 就不管了。

刚刚其实已经说了一个`Android.mk`的配置改动，关于 `glm` 的，这还是第一步。

#### fix 2. `libusbhost`

第二步，一个很大的坑，就是`hmdservice`下面没有引入静态库`libusbhost`，这会导致`#include <usbhost/usbhost.h>`失效。所以要补上。

![picture 158](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643326614099-58e2901ab04c381add6deb8145ad7be1ff18f87c1096c7e7d13d8e6476783544.png)

#### fix 3. `LOCAL_CFLAGS`

![picture 147](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643319315149-0ef8f4f36eae75de9e0544938317df9ae16c51e7e9b818e4885023b7ba13fbec.png)

基于以上认识，有必要对某些错误进行抑制，变量未使用的错误基本无关痛痒的，format 不匹配一般也不会引发程序错误，尤其是在`print`函数中或者向上转换时。

因此修改`Android.mk`如下，否则编译不过。

![picture 160](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643327867425-d299e3defc90f9470ab7645780f39e2098f6ecfdb59862c67ae2b4424235d0bb.png)

具体可参考：[:white_check_mark: 变量没有使用的情况与手动修复过程（放弃，后来直接配 mk 了）](#white_check_mark-变量没有使用的情况与手动修复过程放弃后来直接配mk了)

#### Android.mk 事先编辑的重要性

由于每次 `Android.mk` 改动后，即使是编译该文件夹下的一个小模块，也会触发全局/局部刷新，导致编译变慢，所以尽量一次性先配好 `Android.mk`，后续就不用改配置，直接改代码，编译就会很快。

## step 2. usb 接口修复

具体分析可跳转：[usb cover progress](#usb-cover-progress)

### 修复需要新增`timeout`的三个接口`manufacture | product | serial`，单位是毫秒，目前改成了 5000

```sh
cd $NATIVE/services/hmdservice/service

# add `timeout` param since api changed
sed -i "s|usb_device_get_manufacturer_name(device)|usb_device_get_manufacturer_name(device, 5000)|" HmdDeviceManager.cpp
sed -i "s|usb_device_get_product_name(device)|usb_device_get_product_name(device, 5000)|" HmdDeviceManager.cpp
sed -i "s|usb_device_get_serial(device)|usb_device_get_serial(device, 5000)|" HmdDeviceManager.cpp
```

### 删除`*name`没有用到，接口也变了的一句代码

```sh
cd $NATIVE/services/hmdservice/service

 # drop `*name` which is useless and out-of-dated
sed -i -E "76s|(.*)|//\1|" HmdDevice.cpp
```

## step 3. 代码语法修复

### :white_check_mark: `fall through`

这是一个 case 下没有 break，我浏览了一下，99%确定应该是要加 break 的。

![picture 148](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643319911393-50ae8f67ca3dde5e6da651689cb03f8317f77c4ed4ab25708007965c723629db.png)

![picture 161](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643327972429-8aae1f5b4e3e1dde1e3095a8ebebaf6c045c282fed81d168e23bffa86a6d25a8.png)

![picture 162](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643327995369-fe01fc0318a9a5f60dcbece1527c1131bfe93c6000d53111debe0fa75054ccd6.png)

### :white_check_mark: 删除空指针问题，转为赋值为空指针

有一些空指针删除问题，个人采用了赋值为空指针，抑制了报错，我也不是 C++专家，如果我的做法有误，有副作用，请指正，感觉应该是对的。

```sh
sed -i -E "s|delete (\w+)|\1 = nullptr|" HmdService.cpp HmdDevice.cpp HmdDeviceManager.cpp
```

![picture 163](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643328380750-e31f9a278f13d5e620901fafc55e47784ebd8761a4d1486a23555b2a95bb5a47.png)

![picture 164](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643328390889-062fd6f65e1bf48114fdb3b734bb96c159a8d87ad781643f1bf2e64558b3f53b.png)

### :white_check_mark: 其他一些类型转换

整型类型转换当时在处理时碰到了点 bug，有点像环，有三个函数里面的变量怎么换都不对……

考虑到类型转换对程序正确性影响不大，而且那几个主要用于打印的，不是做实际计算，所以最后我把它加入到了`LOCAL_CFLAGS`里了，就是那个`-Wno-format`。

## 编译成功效果

### :sparkles: build success of `libhmdservice`

![picture 149](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643323418539-6548090679139c81754a84cd47460ed9f75d42d34d6185df1b4a5559ce8efbb2.png)

### :sparkles::sparkles: build success of `hmdservice`

![picture 150](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643323611443-cb33ef62710df8e38b1955d02e861426351f18854017a51f7ff94c8a0298eb1b.png)

## 引申阅读/其他分析

### translate `Android.mk`

```sh
ANDROIDMK=`out/soong/host/linux-x86/bin/$ANDROID`

sudo ln -s $ANDROIDMK /usr/local/bin/androidmk

cd $NATIVE/services/hmdservice/service

androidmk Android.mk > Android.bp
```

![picture 126](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643307094247-9112acf9b4488e6cbd159319c39ffe544e8fa9d372c5066243b9459cc7f86cbd.png)

![picture 127](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643307152936-a88f99c9cdbd14f646b4db367085a8bf64390eb4e4a93ac50717d86563c2763d.png)

### :white_check_mark: `Android.bp: Path is outside directory`

problem:

![picture 128](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643307338978-a81179a15f28f671b97b7bb5f04ed4d8c527b279d3ec0042e18a3cc0b0465ceb.png)

analysis:

There are not too many refs, so we can simply move them to under `service/hmdservice/service`.

![picture 129](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643307400267-e04276fbe02a1bfe6f470716a4bd7800ac41625f0e31db7727ba9fcd2b96085c.png)

resolution:

```sh
cd services/hmdservice/service

mv ../../../externals/glm ./
sed -i "s|../../../externals/glm|glm|g" Android.bp
mv ../common .
sed -i "s|../common|common|g" Android.bp
mv ../cv .
sed -i "s|../cv|cv|g" Android.bp

m hmdservice
```

result:

![picture 130](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643308322613-edc2554631fc57cd30e3d2c86d20d0086130ddde315a935c733e0530d487fe23.png)

### :white_check_mark: `error: frameworks/native/services/hmdservice/service: MODULE.TARGET.SHARED_LIBRARIES.libhmdservice already defined by frameworks/native/services/hmdservice/service.`

analysis:

In fact, the error may owes to the duplicated definition by both `Android.mk` and `Android.bp`.

resolution:

Delete or bak the `Android.mk`.

```sh
# service/hmdservice/service/Android.mk [core]
# maybe no need, but for explicitly using `Android.bp`
mv Android.mk Android.mk.bak

# service/hmdservice/Android.mk [redundant]
mv ../Android.mk ../Android.mk.bak
```

---

The former resolution may be right, but after then I changed back to `Android.mk`, hence the errors arise again.

reason:

I'm silly since I used `cp` again to have generated an `Android.bp.bak` so that there are `Androi

### :white_check_mark: `fatal error: 'usbhost/usbhost.h' file not found`

problem:

![picture 131](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643309016631-58f9e2f7b0d674c10ed3d222c77c02e24ae12cdab12cfee7866ea0d97fd8721b.png)

resolution:

just comment/delete that line.

result:

![picture 132](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643309450092-da8e3e51f68cb408eef7097c16369628521839b0e5094e92cf63bbad6b45b34d.png)

wrong!

---

analysis:

![picture 133](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643310177554-57f83166b9b997424737e2765d2e55c9ee7772dbc86a1cece965f0150ce5ce15.png)

resolution:

don't comment it.

and then it seems ok now.

![picture 134](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643310248334-49665e1ff7c04cdf40b6e9a8d3b6b6c242b6cb2779e55f8365305153c25ecd5a.png)

wrong!

---

resolution:

compile the `usbhost` first.

![picture 136](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643311568636-edecb257058c690a14f0cca66007371acbe2bd218657e9ab407dbb1851186779.png)

wrong!

---

analysis:

The `usbhost` is not alone only from under `sys`.

![picture 137](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643311965426-5738d84bc2fdf6deab2e95a50dd0008968d8fe383c5e310dd32a4ea6b1f67071.png)

So why only `usbhost` raises error?

One reason mey be that it isn't included in the `Android.bp` while others like `String8.h` of lib `libutils` is.

Awful! That's it!

![picture 138](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643312190595-c6352cb9bbb21c1f76c47429967746ff28ffd19734cc2d910cc09682ebeda4cd.png)

And okay!

### usb cover progress

#### :white_check_mark: `error: no matching function for call to 'usb_device_get_manufacturer_name'`

analysis:

![picture 139](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643312994745-efcdee1fb2404efb3e4856530fa8af6fa13753f898b67565a92e112d60ea4d2c.png)

Obviously! It's because api change!

![picture 140](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643313212330-a3b0b516376b57536e5959d682d9d6b13cade24be0f589eb5112f4482085ccf0.png)

resolution:

```sh
sed -i "s|usb_device_get_manufacturer_name(device)|usb_device_get_manufacturer_name(device, 5000)|" HmdDeviceManager.cpp
sed -i "s|usb_device_get_product_name(device)|usb_device_get_product_name(device, 5000)|" HmdDeviceManager.cpp
sed -i "s|usb_device_get_serial(device)|usb_device_get_serial(device, 5000)|" HmdDeviceManager.cpp
```

extended reading:

- `timeout` unit is `ms`: [FTDI Knowledgebase](https://www.ftdichip.com/Support/Knowledgebase/index.html?usbtimeout.htm)

![picture 141](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643313605044-e7a4aaeff480b32897c9580e9b8b99ea4999c2d8f6c0889b3a96e33ef300e9d3.png)

- usbhost definition: [librealsense2: usbhost.h File Reference](http://docs.ros.org/en/kinetic/api/librealsense2/html/usbhost_8h.html#a4a0722741758e228eea537a8d6f78a23)

![picture 142](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643313640291-f473da436be2b06b1a35c261445783d17b2b9cd4b13b78217bbb809801f0f682.png)

#### :white_check_mark: `error: no matching function for call to 'usb_device_get_string'`

![picture 143](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643314676811-c9751f6c959f85f7984802217366367ea4412a25888e6a5038eef8c931838743.png)

resolution:

```sh
# drop *name which is useless and out-of-dated
sed -i -E "76s|(.*)|//\1|" HmdDevice.cpp
```

drop the line since useless and out-of-date.

![picture 144](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643315231955-9f573c133950bd0c1198bd98e4a1173c88671fd7195046ee76a5a1a38e8f7407.png)

![picture 145](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643315348108-f44479f0d9247cb8849c39c1be83fe2727c1628594207756bc022d621e5ef1e8.png)

### :white_check_mark: `error: unknown type name 'usb_device'; did you mean 'UsbDevice'?`

reason:

I commented the `usbhost.h`

resolution:

Add it back.

### :white_check_mark: 变量没有使用的情况与手动修复过程（放弃，后来直接配 mk 了）

problem:

![picture 135](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643310792765-8d0f4c98a3ea3dc027642153dbb7d35e1f0cc605e2f89b92276ba688a2b1c10b.png)

```sh
# comment
sed -i -E "494s|(.*)|//\1|" HmdService.cpp
sed -i -E "258s|(.*)|//\1|" HmdService.h
sed -i -E "262s|(.*)|//\1|" HmdService.h

# uncomment
sed -i -E "494s|^//||" HmdService.cpp
sed -i -E "258s|^//||" HmdService.h
sed -i -E "262s|^//||" HmdService.h
```

### :white_check_mark: `FAILED: ninja: 'frameworks/native/services/hmdservice/service/frameworks/native/services/hmdservice/service/common/IHmdServer.cpp', needed by 'out/target/product/generic_arm64/obj/SHARED_LIBRARIES/libhmdservice_intermediates/frameworks/native/services/hmdservice/service/common/IHmdServer.o', missing and no known rule to make it`

![picture 146](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/hmdservice-1643317742418-27354174370a423f3b5f3f487370d9051454bf4003bbae27de8eaefda8520e7e.png)
