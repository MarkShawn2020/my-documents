# surfaceflinger display research

1. [核心文章](#核心文章)
   1. [谷歌官方](#谷歌官方)
   2. [推荐系列一：Android 图形系统 - YuLong 的专栏 - 掘金](#推荐系列一android图形系统---yulong的专栏---掘金)
   3. [推荐系列二](#推荐系列二)
   4. [推荐系列三](#推荐系列三)
   5. [其他阅读](#其他阅读)
2. [core logic](#core-logic)
   1. [`createDisplay | destroyDisplay`](#createdisplay--destroydisplay)
   2. [`getPhysicalDisplayIds | getPhysicalDisplayToken`](#getphysicaldisplayids--getphysicaldisplaytoken)
   3. [`getHwComposer | getRenderEngine | getCompositionEngine`](#gethwcomposer--getrenderengine--getcompositionengine)
   4. [`mVrFlingerRequestDisplay`](#mvrflingerrequestdisplay)
   5. [`initializeDisplays`](#initializedisplays)
   6. [`SurfaceFlinger::SurfaceFlinger`](#surfaceflingersurfaceflinger)
   7. [`doComposition`](#docomposition)
   8. [`SurfaceFlinger::doDisplayComposition`](#surfaceflingerdodisplaycomposition)
   9. [`SurfaceFlinger::handleMessageRefresh`](#surfaceflingerhandlemessagerefresh)
   10. [接收到新应用切换信息，开始准备新的图层的绘制](#接收到新应用切换信息开始准备新的图层的绘制)
       1. [FIXME: (一分钟后?) 开始创建新应用的图层](#fixme-一分钟后-开始创建新应用的图层)
       2. [应用交替，完成后后将持续绘制新应用，不再有旧应用信息](#应用交替完成后后将持续绘制新应用不再有旧应用信息)
       3. [完成新的应用/图层绘制后，应用如无更新，图层将不再绘制](#完成新的应用图层绘制后应用如无更新图层将不再绘制)
       4. [IMPORTANT: 关于 display 下 layer 的绘制分析结论](#important-关于display下layer的绘制分析结论)
   11. [修改逻辑](#修改逻辑)
       1. [TODO: 什么是 `handleRoundedCorners`，我目前不管它，直接渲染了](#todo-什么是-handleroundedcorners我目前不管它直接渲染了)
       2. [FIXED: 如果走原先系统渲染的分支，导致画面不正常 (No! It's all because of Scrcpy!)](#fixed-如果走原先系统渲染的分支导致画面不正常-no-its-all-because-of-scrcpy)
       3. [加入我们的屏幕逻辑](#加入我们的屏幕逻辑)
3. [屏幕基本信息](#屏幕基本信息)
   1. [`DisplayId`](#displayid)
   2. [`Display | DisplayDevice::getDebugName`](#display--displaydevicegetdebugname)
   3. [`Mesh | Mesh::Builder`](#mesh--meshbuilder)
4. [属性](#属性)
   1. [关于属性的官方参考](#关于属性的官方参考)
   2. [`property_get | property_set`](#property_get--property_set)
5. [投屏 (`scrcpy`)](#投屏-scrcpy)
   1. [`adb server version (41) doesn't match this client (40) #527`](#adb-server-version-41-doesnt-match-this-client-40-527)
   2. [多窗口支持（虚拟副屏）](#多窗口支持虚拟副屏)
      1. [在 Android 模拟器上启动双屏异显](#在android模拟器上启动双屏异显)
      2. [BEST-PRACTICE: disable `simulate secondary display`](#best-practice-disable-simulate-secondary-display)

## 核心文章

### 谷歌官方

- [图形架构  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/architecture?hl=zh-cn)

- [BufferQueue 和 Gralloc  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/arch-bq-gralloc?hl=zh-cn)

- [Surface 和 SurfaceHolder  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/arch-sh?hl=zh-cn)

- [SurfaceFlinger 和 WindowManager  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/surfaceflinger-windowmanager?hl=zh-cn)

- [硬件混合渲染器 HAL  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/hwc?hl=zh-cn)

- [层和屏幕  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/layers-displays?hl=zh-cn)

- [VSYNC  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/implement-vsync?hl=zh-cn)

- [Frame Pacing 库概览  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/frame-pacing?hl=zh-cn)

- [EGLSurface 和 OpenGL ES  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/arch-egl-opengl?hl=zh-cn)

- [Vulkan  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/arch-vulkan?hl=zh-cn)

- [同步框架  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/sync?hl=zh-cn)

- [实现测试  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/devices/graphics/implement?hl=zh-cn)

![picture 58](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-howto-1644813248011-1b74af291c18328e8beb97146675c9747e0b71c81bb9270e5e24103eaa39c9e1.png)

### 推荐系列一：[Android 图形系统 - YuLong 的专栏 - 掘金](https://juejin.cn/column/7021525822439686174)

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644767185263-319f6789b39c13e5a6b86a0a949f42e6ad2f41664ceb6e16e85f3d05e52faaf9.png)

- [[Android 禅修之路] Android 图形系统开篇 - 掘金](https://juejin.cn/post/7026351143714308132)

- [[Android 禅修之路] SurfaceFlinger 的启动过程 - 掘金](https://juejin.cn/post/7026352122941669413)

- [[Android 禅修之路] SurfaceFlinger 合成总览 - 掘金](https://juejin.cn/post/7027848653511327751)

- [[Android 禅修之路] SurfaceFlinger 合成前的预处理 - 掘金](https://juejin.cn/post/7028950385251319815)

- [[Android 禅修之路] SurfaceFlinger 中的一些对象 - 掘金](https://juejin.cn/post/7028951141710823432)

- [[Android 禅修之路] SurfaceFlinger 合成中的工作 - 掘金](https://juejin.cn/post/7030402577875337230)

- [[Android 禅修之路] 解读 SurfaceFlinger 中的 BufferQueue - 掘金](https://juejin.cn/post/7033402333128032286)

- [[Android 禅修之路] 解读 Vsync(一) - 掘金](https://juejin.cn/post/7045996528942448648)

- [[Android 禅修之路] 解读 Vsync(二) - 掘金](https://juejin.cn/post/7045996703219974157)

### 推荐系列二

- 这篇写的非常不错，很清晰详细，包括很多类图也是独有的：[Android P 图形显示系统（一）硬件合成 HWC2 - 简书](https://www.jianshu.com/p/824a9ddf68b9)

- 这篇继承上篇，讲到了 layer 相关的：[Android SurfaceFlinger 和 HWC2 概述 | sunwengang blog](https://wizzie.top/Blog/2019/12/22/2019/191222_android_HWC2/)

### 推荐系列三

- [Android 图形系统系统篇之 HWC - 掘金](https://juejin.cn/post/6844903955709837326)

### 其他阅读

- [Oculus VR SDK 實現 -主要結構體及 Api 接口設計 - 台部落](https://www.twblogs.net/a/5e4ed7f0bd9eee101e83b715)

- [Native 層-OpenGL ES-雙緩衝離屏渲染 - 台部落](https://www.twblogs.net/a/5ef3a16b26bc8c4a8eb3f242)

## core logic

### `createDisplay | destroyDisplay`

`createDisplay` 函数里面没有什么特别的地方，就是把名字和安全性信息保存了下来，并且返回了一个新生成的 token

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644396165436-95dab24e23025dd4ff192453d15e3a3163f253153f9d51040684201037c8d9a0.png)

### `getPhysicalDisplayIds | getPhysicalDisplayToken`

FIXME: `getPhysicalDisplayIds` 这个函数也没啥东西，就是把`mPhysicalDisplayTokens`中不是内置屏（`internalDisplayId`）的都记为物理屏（不太理解，非内置，也就是外置，外置就等于物理屏了吗？所以虚拟屏属于内置屏？但虚拟屏的 id 也不等于`internalDisplayId`吧）

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644396656636-7978143298f058bdfc673509bd1c643a73300b7d17a45240d5ceb46d8b29f815.png)

### `getHwComposer | getRenderEngine | getCompositionEngine`

这几个函数都是基于 `mCompositionEngine`的。

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644396948455-34c7feeb8f30cd7df711e413a3e9c5dbd925f21979bd2331070735df2c646d31.png)

### `mVrFlingerRequestDisplay`

FIXME: 也许 `getHwComposer().getComposer()->isRemote()` 可以判断是否是有外接屏？还是啥？

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644398131632-f7c5ca93c1500c823a52d6b8bafc1f61c5160830c11af2e9cfb479f2342a8807.png)

这一段应该就是 google 目前处理`vrFlinger`的逻辑，主要是`HwComposer`处理的。（和我们用`OpenGL`的方案不同）

![picture 30](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644398536604-9ae51ad41ef0e8d08c1713c867287544b1f7a5ac70c43b775ad24e009b9ef034.png)

### `initializeDisplays`

在 `init` 函数中，判断完 `vrFlinger` 之后就开始初始化 displays 了。

![picture 31](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644398712378-18ac3844d81a3332d3b5e6de49bfeb0dbed36e0f8b9a94e9d77a9f8f25423ecb.png)

不过 `initializeDisplays` 中也没有做什么特别神奇的事，就是初始化了一个 `Vector<DisplayState> displays` 向量，然后装进了一个初始化几乎为 0 的 `displayState`。

![picture 32](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644399394079-f2aa7b40d5aed66ad5b55c6e0c0ad7e2b1717f96d84d1d0f33ab886596ca9562.png)

也就是说，`displays` 是 `displayState` 的一个集合。

### `SurfaceFlinger::SurfaceFlinger`

总体看下来，基本都是一些值的初始化，看起来也主要是三种类型：`debug | ro | sys`，猜测 `ro` 是 `rockchip` 的意思，也就是 rockchip 自己定义的变量，sys 是系统属性。

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644400920798-067e47132aee75aff619a393935b42c56c96686c9754cc7237bbe2d8659b2430.png)

FIXME: 比较耐人寻味的是 `debug` 的含义，到底是单纯的 debug 呢？还是既用作 debug，又用作变量。

比如如下中那句注释 `debugging stuff...`，好像表明这些变量似乎就是用来 debug 的，而没有其他作用（即：打开与否不影响系统运行）……：

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644400566554-c3ec11a248e4378729955f0e1372a3412fe046db59e096bb3d92e1ce0fe32285.png)

### `doComposition`

```cpp
auto display = displayDevice->getCompositionDisplay(); const auto& displayState = display->getState();
````

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644402161945-7aad65da4ea112adac978d23aff3e6408a252f7da25e6bfcab95b767a9a76d06.png)

`DisplayState` 是定义在 `native/libs/gui/include/gui/LayerState.h` 中的。

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644402585796-305163d611c8eed7ededc4794881c87adf57cb8667f5dd7574955a590385d56f.png)

其中，并无我想要的 `displayName`，2333。

### `SurfaceFlinger::doDisplayComposition`

FIXME: display从readyFence中取出buffer，我们也不用管这个函数吗？

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644404173728-11ba658674b9747f87dff9d0c53283db5829e13e0d7a0bcfa9e3b5bdf290a66a.png)

### `SurfaceFlinger::handleMessageRefresh`

这里面首先遍历了`mDisplay`，这是一个`Map<token: DisplayDevice>`的结构，所以我们用`displayDevice`的`getDebugName`函数直接打印具体信息。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644458370072-00d1d3e326503541b125f3eb38cb5ba8e779fbadaf46313d384db6926df284e4.png)

试着打印了一下，捕捉系统重启的动作，但结果很诡异（关于`scrcpy`部分），竟然直接跳过了我前面几个语句的打印，直接就`doCompositionFinished`了，感觉是错过了一些log：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644462417643-8764cab02fd0d69f26b68af7260ab81ded0e571845cf540f08976dc8f1515ca1.png)

但我的log应该是完整的啊，因为第一行就是`beginning of system`。

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644462478626-319d98178fddb294f2a0b3ae55e81695efd4513578088c153a256b9ebc803248.png)

也可能是`scrcpy`和`adb logcat`的时机不对？

我再试一遍，先logcat，再scrcpy看看。

找到了！确实（很可能）是`adb` 和 `scrcpy`之间的顺序问题，现在使用以下命令收集日志，就完整了！

```sh
# 需要重启手机，以重置log
adb reboot && (adb logcat > logcat.log & sc)

# sc是
export sc() {
    while [[ -z $(adb devices | grep -E "device$") ]]; do echo "waiting..."; sleep 2; done;
    ADB=$(which adb) scrcpy;
}
````

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644462951227-efd3217d6d170ae1329108103654678bc4d0d6e6ac56d48ef01b65510c47d8c0.png)

从这个 log 来看，`scrcpy`最后一步 `doComposition` 的回路明显要比 `internalDisplay` 和 `Overlay #1` 要长很多（可能是无限循环渲染的原因），具体也不清楚啊，理论上，scrcpy 只要把主屏投过去就可以了啊（基于一个完整的屏），结果不是，看这 log，scrcpy 是又创建了一个虚拟屏啊……

我们在主屏上，基于开发者模式模拟了副屏，默认的副屏会捕捉主屏，于是出现了直播软件的无限套屏现象；然后我们还用用 scrcpy 又创了一块虚拟屏……

我已经傻傻分不清了……

不过目测应该暂时问题不大。

另外一点，就是我发现，如果**主屏和副屏都是桌面致使无限套屏**的话，log 会疯狂输出；直到我们在副屏启动了一个新的应用（比如：设置），log 才会稳定下来，这大概就是套屏与不套屏的最大区别，值得警惕。

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644463441714-3fb634b55447d3ec520a44ac0d06d2a39f76295bfb5b07b9c89e58ae3ee180b3.png)

好在我们只需要调试主副屏异显的场景，目前来看，也是相对来说更好调试的。

接下来，我们就发现，不同屏幕的渲染逻辑与顺序了。

可以看到，是 `Overlap #1` -> `scrcpy` -> `internalDisplay` 的顺序，并且 `scrcpy` 和 `internalDisplay` 渲染的图层信息是一样的，而 `Overlap #1`没有渲染层的日志信息，因为它只是打开了一个设置应用

FIXED: 但为啥这个应用就没有 layer 层的 log 信息呢？

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644463723806-9e313bce2dd541de5985515ab226e4056c78a893064e00c7fa9a2d4fe2bec63b.png)

因为每次打开应用，屏幕会有多次刷新，只在最初几（可能从 1 到 n-k）次会有 `Overlap #1` display 里的层渲染。

比如，我用 `adb shell am start -n com.android.settings/.Settings --display 1` 与 `adb shell am start -n com.android.gallery3d/.app.GalleryActivity --display 1` 在副屏上交换打开 设置 与 图库应用，打开之后的初步就会有反应。

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644464633264-c6a869a8e63e758abfad9eda6bbaf95aea94ae15d948ad9df7157f2ffdb48a2b.png)

### 接收到新应用切换信息，开始准备新的图层的绘制

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644466090539-148e02f3ff1f322fb01ec520ad07e85969620b6b10ff3f4a1784f7ae520d0919.png)

#### FIXME: (一分钟后?) 开始创建新应用的图层

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644466013667-658bfd9c15c01e0f07194c42fd8aab25409ed95128920c5f633c6fed079a45fe.png)

#### 应用交替，完成后后将持续绘制新应用，不再有旧应用信息

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644465915980-05885c5806f2286d4f01f97f42ea3044d2ac6eb76e7f1fe49862dccef3eed53f.png)

#### 完成新的应用/图层绘制后，应用如无更新，图层将不再绘制

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644465763962-ca34e30c5d98f5e86a80997ba0b0af79988ce8c7a153bf5e18949f11aada4067.png)

#### IMPORTANT: 关于 display 下 layer 的绘制分析结论

在准备新的图层时，确实是将所有 layer 一一绘制然后叠加到目标 display 上。

也就是说，`SurfaceFlinger`在渲染时，首先遍历所有 display（按照一定的优先顺序），这是外层循环。然后内层，会对所有 layer 再进行遍历绘制。如果没有新的 layer，则不绘制（没有 `doComposition` 的动作，大概如一些文章所说的，那就会直接从 `BufferQueue` 中取了。

而外层循环函数就是 `SurfaceFlinger::handleMessageRefresh`。

所以我们可以在外层循环中，对每个 display 进行区分，传入是否启用 vr 的参数，以实现**主屏不反畸变，副屏畸变**的效果。

相关 log 调试已保存在 [logcat_settings-gallery3d.log](logcat_settings-gallery3d.log)

### 修改逻辑

`doDebugFlashRegions` 函数内部有部分关于重新绘制整个屏幕的函数 `doComposeSurface`。

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644466983284-f1545ac87774b0fd57fe39d2cc3d6f249944a057703aa32be40f64cf1dd2fbb1.png)

~~FIXED: 但是奇怪的是，我们好像确实没有操作这边（log 里没有我在 `doDisplayComposition` 函数中的断点，所以可能正如晓研哥所说：我们没有操纵 `FrameBuffer`。）~~

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644467241837-e0831761d7ec0cfd2eefa8d35cc17ec8de97b0881658464bc3a5f0406ba3f4fe.png)

No，这是因为我们……用的是`ALOGV`，所以才默认没有打印……

#### TODO: 什么是 `handleRoundedCorners`，我目前不管它，直接渲染了

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644468422163-ed20507e28f83af75cb98b5c777071508a85cf7caf10307fb2b354907e7a0a84.png)

#### FIXED: 如果走原先系统渲染的分支，导致画面不正常 (No! It's all because of Scrcpy!)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644469165742-7d1256b230e0674fbb7a003cd95a57d06063e15f2864a88a47b3b4fade3ea8c1.png)

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644469069781-15fb45e551e02364e8258fee829d9888421ab7966644c8f2ae6fd8474b7a7cac.png)

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644471022048-a14a4f38d5b1a9b57b6c6331287bce1c17e08d0eb2052c50995cdcb3b7841603.png)

如果强制走 ARPARA 的逻辑，也不正常了：

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644471286167-c6fdbcbecf700f881652c481297545741a5b299edd10a5fdfdc1065c982e1883.png)

好恐怖，得把之前的逻辑改回来。。。

经过不断地“回退”后，发现没能解决这个问题，由于我实质上只改动过 `$sf/SurfaceFlinger.cpp` 和 `$gl/GLESRenderEngine.cpp`，因此最终确定，一定不是程序的问题。

后来意识到了！

是 `scrcpy --max-size 360` 的问题！

这个参数会提前限制屏幕的大小，导致渲染异常！

所以正确的做法，应该是 `resize` 而非 `max-size`！

这是两个不同的操作！

回退后就出现目前暂时想要的预期效果了：

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644474394720-8198a5744f9ee9749121c8f56ad986f08e693dcf1c4e53a1e4077e891b718c4b.png)

#### 加入我们的屏幕逻辑

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644474507400-bce3205434fb4b88750554a56097b99f5e49da10b6713cf5b22cd50b4fb9b70c.png)

检测 `DisplayDevice.getDebugName()` 中的信息，比如是不是 `Overlap XX`(模拟测试)，或是有什么 id

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644476692368-e43a6b98641a6f298e3776f1942c52e4e5506f04e78d6ab6682cb46d0e8e94ed.png)

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644476259875-d13018feaa960c2ac8f0398bd61d5a623e8be4b9fab4e39b49babad9309deec8.png)

当 内置屏不做反畸变，然后误把 scrcpy 反畸变后，实际上等同于把内置屏做了反畸变：

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644481108953-5a1302167ca99f49cdb411a75095b1e46b82c2caf1c6fd88efd4f986f73917b0.png)

【修改好语法】（花了接近两小时）后，终于实现了。

这是清理代码后的结果：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644493134518-5344037de67107f2679304c562532591400da7f72702ceb447e97c1bcf1052f6.png)

## 屏幕基本信息

### `DisplayId`

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644478810088-0cfccc9ea75c9b0cddc108c95e5478363f2a6a57a4b088ed9c30292239b54f76.png)

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644480089749-5cc880adbf88b6073f67964cb2926af288cdc7c1e3ad772b8d588122d75a9c53.png)

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644478376848-124329d51189ef791f124d7bf594a3bc68eb7f930a1bc075e8c0e51789ea2e05.png)

### `Display | DisplayDevice::getDebugName`

可以使用 `DisplayDevice::getDebugName` 方便获取屏幕信息，如果直接用 `getId` 的话，有可能为空，信息也不是很够。

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644404592849-c88a4470d37f5e2c1773096e99b464ad2a394ce5b4ec8d64b23ad00784d09be2.png)

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644405345360-4b5d7b81a0f4fc99acc31206a1458d64b0200ebaf7d640cf16da9bc06bec5e30.png)

### `Mesh | Mesh::Builder`

`Mesh::Builder` 如下：

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-howto-1644999320206-07ea6d50b136d13f95e7634d861d8c84e8e9d22cb5d8fb3b71e2f08389b6c97a.png)

## 属性

### 关于属性的官方参考

- [添加系统属性  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/devices/architecture/configuration/add-system-properties)

### `property_get | property_set`

`property_get` 用于获取一个属性，存储到（一般是临时的）`value`变量中，然后再基于`atoi`转换存储到对应变量。

![picture 33](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644400482897-e556a2c0c12b9364bcfbfd78951955fc97f631bda5f8b7834627d2e84b33c9ba.png)

例如：

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644400566554-c3ec11a248e4378729955f0e1372a3412fe046db59e096bb3d92e1ce0fe32285.png)

而 `property_set` 则是用于修改属性值，并且一般都是字符串。

![picture 35](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644400615270-f540e1d2e892b333e3a4aabd6b6ef58cc957d2a029008e45799ca1b342bd72e3.png)

## 投屏 (`scrcpy`)

### `adb server version (41) doesn't match this client (40) #527`

```sh
# force scrcpy to use specific adb
ADB=specified-adb scrcpy
```

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-displays-research-1644415248041-ce024be52e9fcd0c82716539849b9c571bf79addb73f7c55301e43c575cb8df4.png)

> ref

- :sparkles::sparkles: solution: [adb server version (41) doesn't match this client (40) · Issue #527 · Genymobile/scrcpy](https://github.com/Genymobile/scrcpy/issues/527)

- [adb-server version mismatch + device offline error · Issue #2856 · Genymobile/scrcpy](https://github.com/Genymobile/scrcpy/issues/2856)

- [How To Resolve This ADB Server Version Doesn't Match This Client Error In Android? | The Dark Source](https://thedarksource.com/how-to-solve-this-adb-server-version-doesnt-match-this-client-error-in-android/)

- [android - Install specific adb version on Linux - Stack Overflow](https://stackoverflow.com/questions/55634367/install-specific-adb-version-on-linux/55724130)

### 多窗口支持（虚拟副屏）

- [多窗口支持  |  Android 开发者  |  Android Developers](https://developer.android.com/guide/topics/large-screens/multi-window-support)

#### 在 Android 模拟器上启动双屏异显

模拟器中打开"设置-开发者选项"界面，在列表中找到"Simulate secondary displays"条目。

点击后，在弹出的对话框中选择副屏的分辨率。

比如我们选中 720p，模拟器屏幕的左上角上会立即呈现出副屏的窗口，其显示内容默认为与主屏显示一致：

> see

- [(1 条消息) 安卓系统双屏异显\_Android10 模拟器上调试双屏异显\_wlj509 的博客-CSDN 博客](https://blog.csdn.net/weixin_33612966/article/details/112932641)

#### BEST-PRACTICE: disable `simulate secondary display`

```sh
adb shell settings put global overlay_display_devices 1920x1080/320
```

> ref

- [Developer Settings simulate secondary screen : tasker](https://www.reddit.com/r/tasker/comments/akwso9/developer_settings_simulate_secondary_screen/)

- [android - adb change developer settings options programmatically - Stack Overflow](https://stackoverflow.com/questions/46810503/adb-change-developer-settings-options-programmatically)

- [cyanogenmod - Added simulated external display in Developer Settings and can't boot now - Android Enthusiasts Stack Exchange](https://android.stackexchange.com/questions/61454/added-simulated-external-display-in-developer-settings-and-cant-boot-now)
