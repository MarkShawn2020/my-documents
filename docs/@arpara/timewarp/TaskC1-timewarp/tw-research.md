# TIMEWARP RESEARCH

- [Timewarp Guide](#timewarp-guide)
- [Source Code Research](#source-code-research)
  - [decide the target code](#decide-the-target-code)
- [SDK Logic Backward-track](#sdk-logic-backward-track)
- [SDK Logic Forward-implementation](#sdk-logic-forward-implementation)
  - [step 1. `vertexShader` and `fragmentShader`](#step-1-vertexshader-and-fragmentshader)
    - [1.1. definition of `vertexShader` and `fragmentShader`](#11-definition-of-vertexshader-and-fragmentshader)
    - [1.2. usage of `vertexShader` and `fragmentShader`](#12-usage-of-vertexshader-and-fragmentshader)
    - [2.3 `Pose`（姿态）](#23-pose姿态)
    - [2.4. PASS: `[CG]PU_PROFILE_(BEGIN|END)`](#24-pass-cgpu_profile_beginend)
  - [2.5. 初始化 `Pose`](#25-初始化-pose)
  - [2.6 获取 `Pose`](#26-获取-pose)
- [SDK custom](#sdk-custom)
  - [implementation](#implementation)
  - [FIXME: `glUniformMatrix4fv is depreciated`](#fixme-gluniformmatrix4fv-is-depreciated)
  - [TODO: 获取的姿态不等于我们对 buffer 要做的操作](#todo-获取的姿态不等于我们对buffer要做的操作)
  - [FIXED: how to init C++ class](#fixed-how-to-init-c-class)
  - [FIXED: how to "import" `GLint`](#fixed-how-to-import-glint)
- [Framework Logic](#framework-logic)
  - [intro: `ProgramCache.cpp`](#intro-programcachecpp)
  - [filter out `uniform` Logic](#filter-out-uniform-logic)
  - [add `vertexShader` and `fragmentShader`](#add-vertexshader-and-fragmentshader)
- [Timewarp Forecast](#timewarp-forecast)
  - [documentation](#documentation)
  - [workflow](#workflow)
- [Timewarp Algo](#timewarp-algo)
- [mark::update@2022-02-25: timewarp framework test](#markupdate2022-02-25-timewarp-framework-test)
  - [打印 timewarp matrix](#打印-timewarp-matrix)
- [can we change log level?](#can-we-change-log-level)
- [can we debug shader?](#can-we-debug-shader)

## Timewarp Guide

- 核心参考资料（Oculus 的 ATW 介绍） [Asynchronous TimeWarp (ATW) | Oculus Developers](https://developer.oculus.com/documentation/native/android/mobile-timewarp-overview/)

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645101339108-d0a8d4e45f1bc1d7eff11beeef983a052fc7a0ed679f8f4e3d2a808b9cb91c51.png)

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645101347871-f23d6d77ae06bd2e7f4f6aa23516d5ecc330afe6f0ead6c8789919f9d0041740.png)

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645101359009-fde308c67c9e8d1207019e6f09568ef4507fd3f7eed53ce6d3a870ce4d5e6261.png)

In this article: [Android N VR 代码简析 - 简书](https://www.jianshu.com/p/027916e345bc), it said:

> 单独分离出一个 SDK，除了方便应用开发者之外，主要的目的是用来把 VR 的一些核心算法隐藏起来，比如用来减少延迟的 ATW 异步时间扭曲算法就是被封装在这里，是闭源不公开的。众所周知，在手机上面运行 VR 的时候一个最大的挑战就是延迟，当一副画面的延迟超过 20MS，人就会感觉不舒服恶心，严重影响用户体验，一个好的 VR 产品都会尽量避免延迟。

## Source Code Research

### decide the target code

According to the grep search and vimdiff, we can locate the target codes are in `./src/lib/cpp/Distortion/BarrelDistortion1ShaderProgramGL.cpp`.

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645079933188-0fb7311936ddbe6e17d5fafb7ebcd6b384693c39f649f1ccd6884440cece9917.png)

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645079885554-ded3bb730484c368a2695e269ba47fc7ad3e772bc3bad3bdf98171ab8f43cef6.png)

## SDK Logic Backward-track

sdk 关于 `timewarp` 的逻辑，尤其是 `Shader` 部分主要集中在 `vrsdk-20210813/src/lib/cpp/Distortion/BarrelDistortion1ShaderProgramGL.cpp` 文件中，并基于 `opengl` 的版本决定 `VertexShader` 和 `FragmentShader` 的初始化，其对应的版本也不同。

~~我们直接使用 `opengl3.3` 的版本就可以（也就是 `opengl-core` 对应的逻辑）部分。~~

mark::update@2022-02-19: 根据志刚反馈，车机使用的是`opengl 3.0`，因此我们只能使用 本 SDK 中`opengl 1.0` 的写法了。

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645107339477-4177bf852550cf415b931baf25f375fc201469290c17c62f91b0b37befbadbff.png)

其中 `BarrelDistortionShaderProgramPerApi` 函数是在 `cpp/Distortion/BarrelDistortionShaderProgram.h` （注意，不是 1 了）中定义的，它接收三个 Shader 参数，前面两个分别是 `VertexShader` 和 `FragmentShader`，最后一个是叫 `geomShader`，初始化为空。它们会调用 `ShaderBase` 函数。

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645112317306-8e8d26282dffba206bd8c9c1e1cc4cd0e9fc00b4dd55ab97b5bcfbd868532515.png)

注意，这个 `ShaderBase` 函数其实是一个泛型，在我们的调用栈中，它实际是 `cpp/Distortion/BarrelDistortion1ShaderProgramGL.h` 中的 `ShaderProgramGL`。

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645112700190-9449f0e393c7dc9fb7bde2cd41c9d5f319b1965e2af6cf78ff62bed9f60d4845.png)

也就是说，实际初始化时，调用的具体函数是 `ShaderProgramGL(vertexShader, fragmentShader, null)`。

它是在 `cpp/Renderer/gl/ShaderProgramGL.h` 中定义的：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645113409867-689ac83f3397660a54f44a0c1ee31bcaf12b2fabdd9a0f0f6397d6f83e891c3e.png)

查看实现，其实底层就是调的`cpp/Renderer/gl/ShaderProgramGL.cpp`（TO-CONFIRM: 应该是官方`opengl`） 的 `ShaderProgram`。

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645113514126-ff2bc90994310fe39fdc65705750bc6bf855e61d899132ccde263efcd6f99e0b.png)

注意到这里也有 `IVR_GRAPHICS_API_GLES2` 和 `IVR_GRAPHICS_API_GLCORE` 的定义，~~可以看出来，其实两个文件结构是差不多的~~。mark::update@2022-02-18: 对比了下具体的文件，还是差挺多的，只有很少的一部分（比如 `compile`接口）有保留，其他的基本都改了，应该来说，结构差不多，但内容差了很多，深度定制了。

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645159048380-534d6cff90d4a85b84c2195517db44ba1776758331ce98584e525ea3249f3044.png)

最后追到 `cpp/Renderer/ShaderProgram.cpp` 里 `ShaderProgram` 的实现，可以看到就是一个初始化的过程。

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645159373569-9bbc79c606ee2827a604a6cf730e01debbc81f7dc2a0eb098d3c97791d1314d1.png)

## SDK Logic Forward-implementation

基于 [sdk logic backward-track](#sdk-logic-backward-track) 的梳理，我们可以前向整理出整套 sdk 逻辑了。

### step 1. `vertexShader` and `fragmentShader`

#### 1.1. definition of `vertexShader` and `fragmentShader`

原 SDK 中，基于 `opengl` 版本进行判断，选择是否使用 `opengl#version 100` 或者 `opengl#version 330`。

但是经过查询 android 官方 opengl 部分： [OpenGL ES  |  Android 开发者  |  Android Developers](https://developer.android.com/guide/topics/graphics/opengl?hl=zh-cn)，发现可能只支持`opengl 3.1`：

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645161819210-94b0b24bb07812169e7b14d2584066f11d105bb65ebf2824cbeafd7adbeb1b00.png)

理论上应该不至于，因为 `opengl 3.3` : [OpenGL - Wikipedia](https://en.wikipedia.org/wiki/OpenGL#OpenGL_3.3) 早在 2010 年就发布了：

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645161870835-8a0ab9ae3a92f44e4bc95b9422a7a930f1607c95bc5aed983adbc06aa3e7eb36.png)

!!! warning DEPRECIATED

    FIXED: 所以这一点还要确认一下。

    因此，目前的保守做法，就还是沿用老SDK的处理方式，根据opengl的不同版本，写两套处理程序（为精简，都去除了和旋转有关的内容），一套为了兼容（`opengl 1.0`），一套为了性能（`opengl 3.3`）：

    see: [define_shader.h](./define_shader.h)

mark::update@2022-02-19: 已确认，车机只能使用 `opengl 3.9`。

这样我们就有了两个变量：

1. `s_barrelDistortion1VertexShader`
2. `s_barrelDistortion1FragmentShader`

#### 1.2. usage of `vertexShader` and `fragmentShader`

根据调用栈：

cpp++ BarrelDistortion1ShaderProgramGL::BarrelDistortion1ShaderProgramGL() --> BarrelDistortionShaderProgramPerApi(s*barrelDistortion1VertexShader, s_barrelDistortion1FragmentShader) --> ShaderBase(vertShader, fragShader, geomShader /\_null*/) --> ShaderProgramGL(vertShader, fragShader, geomShader /_null_/) --> ShaderProgram(vertShader, fragShader, geomShader /_null_/) --> \_vertShaderSource(vertShader), \_fragShaderSource(fragShader), \_geomShaderSource(geomShader)

```

所以，其实就是单纯赋值一直往上就可以了，最终在 `BarrelDistortion1ShaderProgramGL` 或者说 `ShaderProgram` 里有个 `_vertShaderSource`被初始化为 `s_barrelDistortion1VertexShader`，有个 `_fragShaderSource` 被初始化为 `s_barrelDistortion1FragmentShader`。

#### 1.3. dependencies of `vertexShader` and `fragmentShader`

其实怎么使用功能 `vertexShader` 和 `fragmentShader` 理论上不是我们需要思考的事，因为在 android 框架里，使用部分貌似是已经封装好的，我们只需初始化这两个shader并启用就好。

而这一步，在后面的 [framework logic](#framework-logic) 里会继续深入，此处不是我们关心的问题。

而且我们确实有现在需要关心的问题，那就是两个Shader里还有一些变量需要我们手动提供。

如下图，`a_texcoord` 应该只是内部属性，不需要自己实现（TODO: 确认这一点）；而真正需要自己定义、实现与操作的是 `u_timewarp_mat` 和 `u_enable_timewarp` 变量。

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645164420291-f604b847b85aa1119ed4df29ba330be9a59fa936cf6cf8d08751497a591116f1.png)

### step 2. `setWrapMatrix`

#### 2.1 call/set `u_enable_time_warp` and `u_timewarp_mat`

!!! note

    ~~我们可以先从 `u_enable_time_warp` 变量入手，因为它只是一个 bool 类型变量，在理解了它的“前世今生”之后，可以更快地理解 `u_timewarp_mat`。~~

    mark::update@2022-02-18: 后续分析发现，其实 `u_enable_time_warp` 是在 `setWarpMatrix` 函数中和 `u_timewarp_mat` 一起设置的，所以也没有分开研究的必要。

在 `src/lib/cpp/Distortion/BarrelDistortion1ShaderProgramGL.cpp` 中可以看到关于 `u_enable_time_warp` 相关的 set 操作（已修正原SDK误把 `_uniformTimewarpEnable` 写成 `_uniformRotationEnable` 的问题 ）。

但其实，对照 `setScreenParameters` 中对 `_uniformRotationEnable` 的使用，可以发现，我们的 `_uniformTimeWarpEnable` 方法只有 set 1 的动作，而没有set 0.

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645166936719-016396f18b4c4fb274fca9e8d18c38eec123a448ceb4cca13576d9ec03fd5186.png)

我们尝试添加 set 0 的操作，以支持 timewarp 的动态开关。

一个比较简单的方法，是保留现在的接口，但允许传入参数 `warpMatrix` 为空，然后当它为空时，我们设置 set `_uniformTimeWarpEnable` 为 0。

修改如下：

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645169682121-d34078661d59776fc5a02d68bd3735513940c76597c20312afafce6fde96a052.png)

现在还得知道 `setWarpMatrix` 的逻辑。

#### 2.2 `setWrapMatrix`

首先搜索所有 `setWarpMatrix` 相关的调用信息：

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645172215721-7704936bd0e08b03339a88bc9574e8ce98f82695d8d268b1935f76f470e13a2e.png)

其中第一个就是我们刚刚修改（加入disable timewarp选项）的那个，然后其他都是初始化相关的，最终调用的就两个地方，也就是 `src/lib/cpp/Distortion/BarrelDistortion1RenderPass.cpp` 内的 `composeSingleEye` 和 `composeDoubleEye`。

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645176448825-5c255c6cb2f880756d3450bc84e1d8edabd27160f015aac4dcaf65aaaee228f6.png)

询问了晓研哥，回复是“曾经提过一个让不支持3D分辨率的设备只输出2D画面的需求”，具体也不懂，也不是很重要，我们直接看 `composeDoubleEye` 就好。

TODO: `composeDoubleEye` 函数中与 `ShaderProgram` 有关的有四个方法调用：

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645176614228-c65b03d91721b6c8b0e0e78652d166fb734369fd553701b3a02f7b07ea961a9f.png)

首先分析和 `timewarp` 相关的那个，使用了`getWarpMatrix`方法，容易知道，这个方法是在 `Renderer` 里面定义的：

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645176839422-557fb596ea4a85211e087787e3f4276200a8fef3d576c4475184b106b96ec52f.png)

进来发现，它其实只是使用了数组 `_warpMatrix`，因此我们需要知道这个数组的意思。

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645176922723-209f658563875ceb5dda8763af1b8aa10ca18203130d20dfe4efafc951c533f8.png)

结果发现，还是在这个文件里，有一个传参赋值动作：

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645177011817-3b1a21df7eb71b72cf95aa6b991c8c33fa8a00090be02841890c71a61453d40c.png)

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645176997898-3f44ebfceeab8796f1532c084c9774d24c06b6abe5e7c8fbb0cb2f119f44b11e.png)

因此我们又得知道 `setWarpMatrix` 的赋值调用。

此时如果直接搜索 `*1*GL*`，则发现回到了我们的起点……闭环了……

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645177307017-9d8e3573c6d9b9927588d391e1c0637c9abca7d1c05d3b42b02dca356b94269f.png)

说明，实际 `setWarpMatrix` 的动作还在外面，我们需要知道 `setWarpMatrix` 真正是由谁调用的。

其实仔细看底层的 `setWarpMatrix` 会发现它有两个参数，第一个参数是眼睛。

因此直接在根目录搜索，会发现是在 `Composer`里调用的。

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645177654553-d99cb22999a5773485f4308fc1a95dc69dc138d1d0fecc97392d971665be1838.png)

至此，关于 `warpMatrix` 的逻辑栈就通了：

cpp++
// get
BarrelDistortion1RenderPass::composeDoubleEye()
--> _shaderProgram->setWarpMatrix(getWarpMatrix(eye)) // _warpMatrix[eye]

// set
VrComposerInproc::_distortionPass->setWarpMatrix(eye, warpMatrix)
--> BarrelDistortion1ShaderProgramGL::setWarpMatrix(warpMatrix)
--> _warpMatrix[eye] = warpMatrix
```

#### 2.3 `Pose`（姿态）

姿态相关的是在 `Composer/VrComposerInProc.cpp` 中，主要函数是 `void VrComposerInProc::present(uint32_t renderOptions, const Pose &renderPose)`：

![picture 30](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645178554972-fec9c4518c220189bd6e73d9217bbe316a4352918935a90dde18a8c3f480f3dd.png)

其中 `renderOptions` 参数可以几乎不用管，用来判断逻辑的， 我们只需要 enable 它就可以。

核心处理是这部分，首先获取最新的姿态（接下来由 `hmdClient` 提供），然后算出一个矩阵，再设置给左右眼：

![picture 31](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645180693642-ba78a1153e62a645caa0eb51f8e312bc3a470eb32cb2d03658e367be3648daad.png)

追到 `calculateWarpMatrices` ，发现就是个逆矩阵计算。(不过还需要通过 `computeViewMatrix` 函数得到每个矩阵。)

![picture 32](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645180840261-1f96d52e8a8f5ab7de37476437c68138beea0d5258ee82d0431ba2709f324eea.png)

再看 `computeViewMatrix` 函数，就是基于 `Pose` 的姿态属性，进行 `glm` 相关的计算（可以照抄）。

![picture 33](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645181125920-5e12bb82603d93570f87eb62d4de9e101cb44b6aa0c305e2fc793f1fde41728a.png)

而 `Pose` 的定义是在 `./Tracker/TrackerClient.h` 中（这里虽然写的是 `PoseState`， 但实际上对比之前那个函数，会发现，应该就是 `Pose`）：

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645181208590-b8bded1e4d065bd5b3a3352ca4357243e50ce23183fb88e16dc6df1d73f13d0c.png)

#### 2.4. PASS: `[CG]PU_PROFILE_(BEGIN|END)`

> 根据晓研哥指示，这部分适用于测试性能的，所以也不用看。

在 `VrComposerInProc::present` 函数中，有个关于 `[CG]PU` 的调用值得注意：

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645184570907-28e87ba2defce8077e7dbae6c3c8cbc595706541fe4c32e407f7dd52f0f66a13.png)

在 `src/common/CpuProfile.h` 中可以找到关于 `CPU_PROFILE_(BEGIN|END)` 的定义。

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645187583404-eb0431553855fcd14b0a91540d36b37feb4e42b0c603b9ebcfbc1c948c3be3cc.png)

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645187328248-c763c95de009709aa4c968ff99362b5a7bdb97185b3c8429eef11cdc039d471d.png)

在 `src/common/CpuProfile.cpp` 中可查到实现如下：

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645187986029-c539c3894bb662726b8eb13e1510e92a32721402592378cc8b068a89ed477bfe.png)

### 2.5. 初始化 `Pose`

在 `TrackClient.h` 中定义了 `PoseState` 的数组，但是并没有什么 set 的操作。

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645199303457-e03440c58786c29055b67a07093a24247f4f7c1657cd5e01b0d604e1619df674.png)

查看 `_historyBuffer` 相关的信息，发现主要还是集中在 `onSensorUpdate` 函数上。

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645199369594-b182d7ef99e58bee5137c6cf06301ff5cf57ae55b4e6aba6a446ee64f8c83ede.png)

![picture 43](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645199414532-3ab5efdaea105fe7159f4017aeb91c2e0b41f75a5a10ed33fa9002a95e743a62.png)

但其实这个函数里对 `_historyBuffer` 的 set 操作，也是基于其“本身”的，所以很奇怪：

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645199492073-08c539ad900b2182fe0f0dda16b554f050fd455356f022f79482bbf01f1a0d5f.png)

### 2.6 获取 `Pose`

在 `TrackerPalHmdService.cpp` 的 `readSensor` 接口里获取 `hmdService` 的姿态数据，然后将姿态数据再基于自己的 `onSensorUpdate` 函数进行更新维护，并触发预测。

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645200260860-4f7adc57d66017e1968db4db783322d948ae662ee883c6bac12cd824151d125c.png)

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645200296274-3019781fc5146b961ac9f708f0a726c1b6e44dd7f744826c910811f0ab2c8368.png)

## SDK custom

### implementation

一开始 `vertexShader` 中阉割旋转部分把 `gl_Position` 也阉割了，导致最后没有图形，补上来之后就有图形（三角形）了（但是是黑色）。

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645473167572-7e9de9e0b54294f1a028c055f03e04feef939ac6fc999ef3858a697c3a246e8d.png)

黑色一般是着色没着成，检查了一下 `fragmentShader`，再对照官网 case，果然，没有一个输出，加上后就有白色的三角形了。

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645473249075-64aa9719db7a5c5d6dc546d43da3ec1d331419343e26627893db4d846645ef9f.png)

!!!tip 结果后来发现，这个 `gl_FragColor` 是 1.0 版本产物，现在也不行……

    ![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645475488760-5af09bfacb12d4acff18135c3bc7a7e9b88507f59a99b01802c5a055be5e9c4c.png)

    最后确定是用 `gl_FragColor` 但是不要加 `out`，并且我换成 `FragColor`也是不对的。

    ![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645475598339-b17bd92138afbcf1e6b702deb6bb8343b6b8dc25c1d9d2837ab8226be565d743.png)

接着发现 `timewarp` 没效果，以为是 `a_texcoord` 没生效，于是测试添加一个明显的、固定的 `a_texcoord`，测了几个，结果还是不行。

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645473308231-3f3e5430ae706d1d1b9db9146256cb625fbb9180cb269ec277d23cd3cf9a5590.png)

后来研究这部分函数`gl_FragColor = texture2D(eye_texture, t);`发现 `timewarp` 其实就是重新设置了贴纸的中心坐标（所以并没有什么神奇的），既然是这样，再联系我们之前的三角形问题，由于我们三角形的颜色是单一的白色，自然，就没有任何变化了（因为中心坐标无论在哪，周围都是白色）。

FIXME: 基于此，我突然想到，要是我们设置一个超出范围（0-1）的坐标，基于官网裁切、重复那部分章节，或许至少能有不一样的效果。

但是很遗憾，还是没有，如下，我设置成了 (1.2, 1.3) 都不行。

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645473483639-3d66cd01ea124abea037b2b3c5e968f708b97a80631a0cd1e11cd95eca6e446d.png)

!!!tip 原来还有一个错误，这么设置固定的数组是不行的……

    ![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645475387056-cbd35f7a3eb856a7013f6071f26fa976417fac0efb9c3b1a76cd029e44d7d7fc.png)

但这也不是不可以接受，因为和教程中那个场景还是有可能不一样的，不过这个不是重点，这条路暂时不行，也不用深究，还有一个更加稳妥的办法，那就是换贴纸。

参照官网换贴纸的案例：[LearnOpenGL/textures.cpp at master · JoeyDeVries/LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/4.1.textures/textures.cpp)：

---

终于，有图片了，但是好奇怪，是非常扭曲的那种，即便我取消了一切 shader 操作也不行……

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645475869127-92d956fbb5f8ec89162b9032d4ace551539a665d142b13c25715148ad598074d.png)

经过不懈尝试，使用 3.3+版本的 `glad` 结合官网的 `shader` [LearnOpenGL/src/1.getting_started/4.1.textures at master · JoeyDeVries/LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/1.getting_started/4.1.textures) 完成了初步的正常显示，如下：

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645476671858-7f13ef4d3a1a5cbe5bc94e56ee958a99f5ce6d7c858e30112913ba3f0050b168.png)

### FIXME: `glUniformMatrix4fv is depreciated`

We can find the definition of `glUniformMatrix4gv` at here [glUniform](https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glUniform.xml):

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645260666205-78d660fb4698d0633c567e4e45c8b3993ee93fc59ec4b14b6a288edec9a82250.png)

### TODO: 获取的姿态不等于我们对 buffer 要做的操作

### FIXED: how to init C++ class

As mentioned in [c++ - Creating an instance of class - Stack Overflow](https://stackoverflow.com/questions/12248703/creating-an-instance-of-class), we can use: `Foo* foo1 = new Foo ();` or `Foo foo2` to declare an instance of a class.

### FIXED: how to "import" `GLint`

Just to add `#include <OpenGL/gl.h>`, then we can use `GLint`, since Mac has opengl supported built-in.

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645259030449-7aa80cf0fc080c767693b49aff0c655c3cd67a046ec9aff8ad397c0deb38ebf1.png)

It's inspired from [Drawing to a Window or View](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_drawing/opengl_drawing.html#//apple_ref/doc/uid/TP40001987-CH404-SW8):

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645259097457-7a57f4b719c630bcef342108e3d18ecb4da10e4bab214bbebd05766279ad500d.png)

More detailed configuration (on Windows) can be learned from [How To Set Up OpenGL (and freeglut) on MinGW w/ CLion + Run Demo Programs | Game/3D programming - YouTube](https://www.youtube.com/watch?v=AUFZnA3lW_Q).

## Framework Logic

### intro: `ProgramCache.cpp`

晓研哥说 Shader 的逻辑是在 `frameworks/native/libs/renderengine/gl/ProgramCache.cpp`，一开始我还表示十分怀疑，因为是一个带`Cache`名的文件。

但进去之后一看，不得了，都在这里。

比如 `VertexShader`:

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645104307789-42761414203cb15cd5ed1663583d311b7d7dc3e75d04dc36d32c3822d1785d60.png)

还有 `FragmentShader`:

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645104326249-7ac30af4022c1d56c473a522421cb052cf98c951e92f575dd4a745f13503c34e.png)

这两个 Shader 都是生成函数，并且还都集中定义在一个函数 `generateProgram` 下：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645104352170-2c953257331770aa542ec425632168b87c0c07ce33d86abc3a43d8a049febc54.png)

而 `generateProgram` 又是在 `useProgram` 函数下调用的（还有一些其他地方也在调用 `generateProgram`，但是主逻辑应该是在 `useProgram`这里 ）。

`useProgram` 中接收 `EGLContext` 和 `Description`，其中 `Description` 用于生成 `needs`。

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645102966351-cfa524c9390dfd2c1452687d26c92607379ca8b37cf039d0711e9601c3583c9d.png)

`computeKey` 函数中对 `description` 进行处理，将目标属性一一加在 `needs` 上。

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645103160792-1d33d27b31cabfd26ead64960e7b7f74cfb1d284cfd84f8e4350cc5e66c2082c.png)

`Description` 是在 `renderengine/private/Description.h` 中定义的。

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645103200832-a0e4bdaed9541deb5e4c5cc852e8a196dfc2beab98b053144a6c07826ab3afab.png)

具体位置是在 `frameworks/native/libs/renderengine/include/renderengine/private/Description.h`

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645103893037-f67f0b8dc2b57a71d1414a286fbb2088113b8c530e13595c44c42e79b482f1f9.png)

可以看到，还是比较复杂的，定义了很多属性，估计是全局的。

我们可能要基于这些属性，去操纵我们的目标。

### filter out `uniform` Logic

We have seen some `uniform` variables defined in `Shader` language, such as `displayMaxLuminance`.

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645399159611-f4cf7fe64b23e2a05dae5e1dae7420059fcc67839b0f2e46b0757dc2d3f04c2e.png)

搜索发现，其实就是在 `Prime.cpp` 中进行赋值的。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645399323930-5c12eb631d6bbfb2fbfdc6d840c3ce1f72a177dde7a775f981f3c31cfeffe496.png)

可以看到，就是用 `glGetUniformLocation` 函数获得地址，接着用`glUniform1f` 基于 `Description & desc` 进行赋值。

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645399412540-12c6a9d96c1adf88ed88f8e70b8f5b863e170e627f04eb1a436bda3be3c4d18c.png)

不过这里有个疑惑，这个 `Program::Program` 的初始化，`vertex` 和 `fragment` 都是 `const char *`，和我们之前看到的不断的加文本不太一样，所以得看一下是怎么初始化的。

### add `vertexShader` and `fragmentShader`

## Timewarp Forecast

### documentation

:sparkles::sparkles: 这是关于姿态的非常好的介绍资料

- [姿态的数学表示方法 | Crazepony 开源四轴飞行器](http://www.crazepony.com/book/wiki/attitude-math.html)

:sparkles::sparkles: 这是一篇非常好的，手把手的基于 MA 和动量的时间序列预测教程：

- [Chapter 2: Linear, Trend, and Momentum Forecasting — Time Series Analysis Handbook](https://phdinds-aim.github.io/time_series_handbook/02_LinearForecastingTrendandMomentumForecasting/02_LinearTrendandMomentumForecasting.html#momentum-strategies)

:sparkles::sparkles: 理解卡尔曼滤波

- [(19 封私信 / 68 条消息) 如何通俗并尽可能详细地解释卡尔曼滤波？ - 知乎](https://www.zhihu.com/question/23971601)

:sparkles::sparkles: 理解传感器融合

- [Understanding Sensor Fusion and Tracking, Part 1: What Is Sensor Fusion? - YouTube](https://www.youtube.com/watch?v=6qV3YjFppuc&t=59s)

### workflow

```mermaid
flowchart TD

IMU_glasses -- We Are Here --> data1

CV -- And Here --> data2

AlgoFix[[AlgoAdjust<statistics> ?]]

data1 --> AlgoFix

AlgoFix --> data2

data2 --> AlgoFilter[[AlgoCombine<Calman Filter> ?]]

data1 -->  AlgoFilter --> data3

IMU_car -- And Here --> data4

data4 --> AlgoAntiCar[[AlgoAntiCar ?]]

data2 --> AlgoAntiCar

data3 --> AlgoAntiCar

AlgoAntiCar --> data

VOICE/etc --> AlgoPredict[[AlgoPredict<Polynomial/GARCH/SVM> ?]]

data --> AlgoPredict

AlgoPredict -- What's the day ? --> predict

```

## Timewarp Algo

```cpp
/**
 * see: glm of "./ext/matrix_transform.inl" 153L, 4728B
 * @param m
 * @param v
 * @return
 */
mat4 translate(mat4 m, vec3 v) {
    mat4 result(m);
    result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    return result;
}
```

## mark::update@2022-02-25: timewarp framework test

- [ ] timewarp 的 matrix 没有打印出来（可能是添加位置错误，那个地方是初始化用的）
- [ ] timewarp shader 效果异常（可能是 TexCoords 问题，因为输入是 vec4, 我们需要 vec2

### 打印 timewarp matrix

发现根本没有走我们的逻辑！

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645781575138-e73b62170a17742737c2602a69f32ae9125c07680404a719796eed62c4f8cc68.png)

所以这个时候需要 ide 进行调试了。

定位到我们打印 matrix 的部分，是在 `Program::setUniform` 里，后来我们加了断点，结果发现，逻辑是走的，但是我们的变量没有触发：

![picture 43](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645786799310-6446b04b1c59393fdaaa5387a859e0aba47f9bfbb52e83a357024fefa06a77aa.png)

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645786832556-355194cfe1b92f8cc10676469801ca61e9f799f6886e5377ae2ffde2e68cbad3.png)

---

修改后发现，还剩一个 `mArparaTimewarpEnableLoc` 没绑定上。

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645787489410-6d0f8a7e51c55e30ca01dd0a09cbe83a81e62b446261a3095d4325f8afa4e3d1.png)

知道原因了，原来是被优化了。

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645787592305-c48c145796b8014da362311f9e7b50ef6b29e138d7a766cd9b29cf112d5d6321.png)

## can we change log level?

```sh
adb shell setprop log.tag.XXX V
```

ref: - [logging - How do I enable/disable log levels in Android? - Stack Overflow](https://stackoverflow.com/questions/2018263/how-do-i-enable-disable-log-levels-in-android)

## can we debug shader?

see at [Is it possible to debug shaders in Android OpenGL ES 2? - Stack Overflow](https://stackoverflow.com/questions/41161346/is-it-possible-to-debug-shaders-in-android-opengl-es-2), it's impossible:

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-research-1645781153080-6f7d1ae10fe226550c62e358e8ef6c070e4f3699e15b1ef40d3af976c6f6c055.png)
