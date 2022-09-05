# surfaceflinger patch research

- [gerrit codes](#gerrit-codes)
  - [search the target gerrit](#search-the-target-gerrit)
- [patch 1 & 2 analysis](#patch-1--2-analysis)
  - [definition](#definition)
  - [classification](#classification)
  - [EASY: suppress `#error` problem of imported `gls2.h`](#easy-suppress-error-problem-of-imported-gls2h)
  - [EASY: `services/surfaceflinger/Android.mk`](#easy-servicessurfaceflingerandroidmk)
  - [PASS: `libs/gui/GLConsumer.cpp`](#pass-libsguiglconsumercpp)
    - [variable initialization](#variable-initialization)
  - [`services/surfaceflinger/SurfaceFlinger.cpp`](#servicessurfaceflingersurfaceflingercpp)
    - [part 1. initFB](#part-1-initfb)
    - [part 2. function of `initFB`](#part-2-function-of-initfb)
    - [HARD: part 3. `doComposeSurfaces`](#hard-part-3-docomposesurfaces)
    - [drawing flow](#drawing-flow)
    - [doComposeSurfaces code flow](#docomposesurfaces-code-flow)
    - [rendering client layers](#rendering-client-layers)
- [编译](#编译)
  - [目前策略](#目前策略)
  - [目前策略更新@2022-01-27 15:16:38](#目前策略更新2022-01-27-151638)
  - [:white_check_mark: `error: use of undeclared identifier 'dirty'`](#white_check_mark-error-use-of-undeclared-identifier-dirty)
  - [:white_check_mark: `error: use of undeclared identifier 'displayTransform'`](#white_check_mark-error-use-of-undeclared-identifier-displaytransform)
  - [:white_check_mark: `error: unknown type name 'Transform'`](#white_check_mark-error-unknown-type-name-transform)
  - [:white_check_mark: `error: no member named 'draw' in 'android::Layer'`](#white_check_mark-error-no-member-named-draw-in-androidlayer)
  - [:white_check_mark: `error: use of undeclared identifier 'mRenderEngine'; did you mean 'renderEngine'?`](#white_check_mark-error-use-of-undeclared-identifier-mrenderengine-did-you-mean-renderengine)
  - [:white_check_mark: `error: too few arguments to function call, expected 5, have 3 (RenderEngine->setupLayerBlending)`](#white_check_mark-error-too-few-arguments-to-function-call-expected-5-have-3-renderengine-setuplayerblending)
  - [:white_check_mark: `error: use of undeclared identifier 'renderArea'`](#white_check_mark-error-use-of-undeclared-identifier-renderarea)
  - [终于成功了！2022-01-27 23:37:03](#终于成功了2022-01-27-233703)
- [年前主要工作目标](#年前主要工作目标)
  - [pre-check list](#pre-check-list)
  - [core 1 list](#core-1-list)
  - [core 2 list](#core-2-list)
  - [core 3 list](#core-3-list)
- [年前主要困难分析](#年前主要困难分析)
  - [`Layer.cpp`中关于`win`和`position`](#layercpp中关于win和position)
    - [可疑 1. `Layer::prepareClientComposition()`](#可疑1-layerprepareclientcomposition)
    - [可疑 2. `InputWindowInfo Layer::fillInputInfo()`](#可疑2-inputwindowinfo-layerfillinputinfo)
    - [position 似乎没有被调用的困惑](#position似乎没有被调用的困惑)
  - [`surfaceflinger.cpp`中关于 `doComposeSurfaces`](#surfaceflingercpp中关于-docomposesurfaces)

## gerrit codes

### search the target gerrit

search: `status:merged project:oneos/platform/frameworks/native branch:project-dev`

url: http://192.168.0.241:8080/#/q/status:merged+project:oneos/platform/frameworks/native+branch:project-dev

## patch 1 & 2 analysis

### definition

`p1` 指 patch 1，即 `merge from rk3399`

`p2` 指 patch 2，即 `feature vr 2d mode`

p2 基于 p1，中间还有其他一个 commit，不过貌似和 p2 无关，不构成依赖关系。

目前基于`combinediff`将`p1`与`p2`合并也是没有问题，不报错的。

p1 改动涉及到 60 个左右的文件，主要作用是 aosp 向 rk 的适配（大致作用肯定是这个，具体场景等不清楚），而 p2 改动涉及 9 个，使支持了 vr 模式的功能。

p1 和 p2 之间有几个文件是重合的，也就是先后改动的，因此要想直接打 patch 2，需要对 patch 1 中相关的文件进行分析，理出专属于 p2 的改动的极小集。

### classification

```text
Both in p1, p2:

- [ ] libs/gui/GLConsumer.cpp
- [ ] services/surfaceflinger/Android.mk
- [ ] services/surfaceflinger/Layer.cpp
- [ ] services/surfaceflinger/Layer.h
- [ ] services/surfaceflinger/SurfaceFlinger.cpp
- [ ] services/surfaceflinger/SurfaceFlinger.h

Added in p2:

- [ ] libs/gui/include/gui/ISurfaceComposerClient.h
- [ ] services/surfaceflinger/HmdType6DistortionMesh.cpp
- [ ] services/surfaceflinger/HmdType6DistortionMesh.h
```

这些文件大概可以分成以下几组，并分批分析完成。

1. 编译部分：`Android.mk`，很简单，p1 不用考虑，直接考虑在 p2 中加一个 cpp 即可。
2. 不用考虑但两部分都有的文件：`GLConsumer.cpp`，这个文件经过分析，没有必要动。
3. 不用动脑的核心文件:`ISurfaceComposerClient.h`，这个文件主要是定义了一个 vr 变量，供`surfaceflinger`使用，所以很简单。
4. 不用修改的两个核心文件：`HmdType6DistortionMesh.cpp|h`，这两个文件基本可以写死，而且是基于算法自动生成的，所以也不需要手改。
5. 需要看但不难的两个核心文件：`Layer.cpp|h`，这两个文件要看一下。
6. 需要看最难的两个核心文件：`surfaceflinger.cpp|h`，重点分析！
7. 其它只在 p1 中动的文件，我们可以暂时先不看，如果接下来编译有用到的，再加！

### EASY: suppress `#error` problem of imported `gls2.h`

> :warning: 不注释这个就编不过去，luci 用的旧版依赖，或者单纯地不该把它们导入到 `surfaceflinger.cpp / Layer.cpp`内

```sh
sed  -E "s|(#error.*gl2)|//\1|p" services/surfaceflinger/Layer.cpp
sed  -E "s|(#error.*gl2)|//\1|p" services/surfaceflinger/SurfaceFlinger.cpp
```

### EASY: `services/surfaceflinger/Android.mk`

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643106263791-f437ddb26e9cb79f654853b88a29b64f8d9f9de30885faa31bb710648a3556f0.png)

p1 关于 mk 部分，最大的篇幅是`rockchip support`，我们也可以直接跳过，看了也没用，目标是高通的。（如果后期实在要对这部分，那就认了吧）

除此之外，就是加了`rk`专用的`librga`依赖，这个高通也用不着。

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643106525915-0556ab703bde3abacaa1c349aaae854f0ca887e0fe95340acee86a82caa20a8c.png)

p1 就是这么些改动，所以实际上对项目没有任何帮助。

p2 则加了一个`HmdType6DistortionMesh.cpp`的依赖，就是我们自己的那个。

![picture 43](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643106603903-23b4912d18a8053a444b0b247f94e5c560891a0ee252b35e2bb87f5352874967.png)

在原生 8 的`Android.mk`中，它其实就是加在`LOCAL_SRC_FILES`里的。

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643109587318-b2da803315284f3547262e9706ab1bb73a568cc72e647c18d114e3a065da522f.png)

尽管 8 已经有`Android.bp`了，但其实还没正式开始用（TODO: 具体区别待查）。

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643116633259-574c82039d43cc89a3a7a9a9f2a1266bacc4274b22a481e9d3e0dde6e44f5474.png)

所以要把加 cpp 的动作改到 11 的`bp`中去。

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643109875995-7539232556a1fa87e9ffb6910c80c63c2a7b31833dd97cc814efcd6816b7cbe6.png)

根据检索，实际上就是要加在`filegroup.srcs`下（和`Layer.cpp | FrameTracker.cpp`一起）。

命令可如下：

```sh
# mac sed -> gsed
# :warning: alias need to work in next commands
if [[ $(uname) == Darwin ]]; then alias sed=gsed; fi;
```

```sh
# 在surfaceflinger/Android.bp内加入私有实现
SRC="HmdType6DistortionMesh.cpp"
T='"'$SRC'", // mark added at '$(date +%Y-%m-%d\ %H:%M:%S)
F="services/surfaceflinger/Android.bp"
P='"Layer.cpp",'
if grep $SRC $F;
then echo "found";
else echo "not found";
echo $T | sed 's|^.*$|s_^(.*?)('$P'.*)$_\\1\\2\\n\\1\0_|' | sed -i.bak -E -f- $F
fi;
```

### PASS: `libs/gui/GLConsumer.cpp`

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643103121263-7460c1d919e7a11e5e65830708304f8a20cc09bd6175822271cd62deeef3c31f.png)

在`GLConsumer.cpp`中，p1 主要是加了一个**对齐函数**：

cpp++ bufferWidth = (cropRect.width() + 31) & (~31);

```

具体可以看我和chen姐的请教记录：

![picture 35](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104031704-cdeb8648205dc69ec4352cbda34fa9718f611cdf5b5e08c046e0d3ed1927bad0.png)

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104038721-0c2f2634d5070f0493f786e6a96626cf5d376545c8703d566149d21bc1d78dcc.png)

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104043233-a06964a558bbe6829684e3032f2f2a5b2efc439c70004fccb88b6a3a2e8c021a.png)

所以，实际上 p1只是一个小小的性能优化，对于业务来说，应该影响不大，不过确实是值得关注的一个改动，得去11上看看。

然而11看的结果就是，完全没有这回事！

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104398250-911dad0fe36ae180059835431f11e15d4e6150e50ab7806f75daea4506b345b8.png)

所以，我们也不用管这个函数了！

接着是p2中的改动，坦白说，我没懂他改动的意义。

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643032866621-9dd0251e560a24ddc5d1b91d91d8bbb013d2da3597a4887bca852187fcf2a09b.png)

在原来的逻辑中，有一个静态变量`sReleasedTexImageBuffer`初始化为空，然后接收buffer数据。

这是一个初始化设计，注意注释：`// The first time, create the debug texture in case the application continues to use it.`

但后来的逻辑中，却把这个初始化判断给去掉了，于是乎每次都会新生成一个buffer（显然，这个效率会大大降低）。

在另一个官方diff：[Diff - 9870c9b^! - platform/frameworks/native - Git at Google](https://android.googlesource.com/platform/frameworks/native/+/9870c9b%5E!/) 中（不知道是哪个版本对哪个版本），很清晰地将原先的获得`mReleasedTexImageBuffer`改成了获得`getDebugTexImageBuffer()`。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643033403953-02c9e6213fd5519490cd23b29c05719ee9531b24ed9e97bf2ad9435991334eea.png)

基于此，有理由判定，这里的改动只是一个`debug/release`或初始化相关的区别，对目前的vr集成目标可能没有什么影响，只不过令人困惑的是，它的改动似乎与官方的改动有些相近，却又不完全一样，不知到底是版本升级的问题还是啥（比如说使用debug的版本是8，而源代码版本是7，于是为了将7的部分升级成8，就用了这种改动办法，仅仅是一种猜测，很有可能不对）

具体见我和晓研哥的讨论：

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104628305-66437969f15d8a23eb8f491d7e2d8c0e8839c24a0c7238396fe1df0317abcbf1.png)

check了一下11中的代码，也是没变的：

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643104552627-777845363dfb2d005d2c5e6aa9b3869987fcc1fec7a8e7880b5ac6ec54090c86.png)

所以p2的改动也忽视！

ref:

- 完整的实现：[libs/gui/GLConsumer.cpp - platform/frameworks/native - Git at Google](https://android.googlesource.com/platform/frameworks/native/+/master/libs/gui/GLConsumer.cpp)

### EASY: `services/surfaceflinger/Layer.h`

> :sparkles: 见识到`对比浏览分析(line in side)`的强大了吧！

![picture 51](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643132425592-dc09daee4b9581cabb5142d14c3cee28a9714568f336451ac657a3609793a513.png)

可以看到，在 `Layer.h` 中，p1里基本都是定义的和 rk 相关的变量和函数，虽然有一个 `RK_VR` 的变量和逻辑处理很吸引注意力，但是询问了晓研得到的回复都是明确的不用看。

![picture 52](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643132607551-8c8e22178f1d4f0ad220e613f209239047cef5fea7b0c5f6ec0b4217acda5427.png)

而 p2 很简单，就是加入了vr的变量标识，并提供了`get | set`的方法。

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643041501426-002bd50f36a307ff05a627d558984c31d8ce0877b03b6bb2b21fcc2264c88963.png)

### `services/surfaceflinger/Layer.cpp`

#### HARD: `win.right = hw->getWidth();`

![picture 53](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643133906128-eaaf0240b6d8e31bda6fcaf21527e860a64303c889e1a90f8966e45f0e5de36e.png)

不出意外，p1中有大量和RK相关的定义与实现，篇幅很长，目测主要实现了`RK_VR`和`RK_STEREO`两个模式，但根据晓研指示，都不用看，这样的话，就实际上等于p1没改啥了。

唯一改的影响到p2的应该是这个`win`，它把原先的`ComputeBounds`改成了`FloatRectBounds`，估计是为了更精确的实现旋转、VR等变换的意思吧。但对p2的接口却是可以不变的，目测来看。也就是以下代码几乎可以照抄。

cpp++
    if(mIsVr) {
        win.right = hw->getWidth();
    }

```

而它的下方就是

cpp++ float left = float(win.left) / float(s.active.w); float top = float(win.top) / float(s.active.h); float right = float(win.right) / float(s.active.w);

````

~~可以基于这个写sed脚本。~~

然而，这个想法失败了，8到11变得太大了，已经搜不到 ` float left   = float(win.left)   / float(s.active.w);` 这个了。

![picture 54](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643134635239-1d6f9de87874186699deb6ed33071fb79b0389f60e8dab41332727b8da9010e8.png)

所以得定位到出处。

![picture 55](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643137004483-5b3b4140ab77de72ef4a5b848121194f6d2102e27c2fe23e84823f184ad2f7b8.png)

在 `drawWithOpenGL` 函数中，它接收的第一个参数是`hw`，类型是`DisplayDevice`，紧接着开始创建`Rect`类型的`win`变量。

改动就是在这里进行的，一旦检测到是vr模式，就让这个`win`变量的宽度修改为`hw`的宽度：`win.right = hw->getWidth()`。

这里我们得知道这个`computeBounds()`构造函数是咋回事。

![picture 56](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643137518943-d8297585f5c0fa99e05666d3eaeb3a8e87e544c55deb73dd390d224ab758b3c9.png)

还好，8和11在这里的区别不是很大，只不过`computeBounds`名字改成了`getBounds`，内部实现也相应地更简洁了一些，核心思想就是窗口区域减去透明区域，得到的就是所谓`Rect`，也就是实际区域吧。~~至于结构体是啥，四个坐标吗，还是啥，应该倒也不是那么重要。~~

不过这样，回到前面那个函数：`win.right = hw->getWidth`就有点怪了，`hw`和`getBounds()`之间又是什么关系呢。

TODO: 我这里其实主要困惑的在于，如果`win`是指那个活动窗口，比如说某个浮动窗口，那在vr模式下单独改其`right`为`hw`的宽度，而不把`left`改成0，这是否会有问题呢？至少看起来不是那么对称，所以这里在原理上来说，是一个非常大的困惑。

还是，先看看如何在11中实现这个修改吧。

##### 可疑1. `Layer::prepareClientComposition()`

![picture 58](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643138949603-bd8010805a1b2d7274c9adf4c6c21c43c549711742aadeb94d21c388e1468ca7.png)

在这块里，最大的可疑原因是正好与左边8的版本对齐，并且函数名就是在画图：

![picture 59](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139039422-45fe81e61a85a9a61de7d2d34b40023143d959a149be023b1f89ef875e73a6eb.png)

另外也有一个关键赋值语句：`layerSettings.geometry.boundaries = bounds;`，我们若在赋值之前，修改`bounds.right`为`hw.getWidth()`，或许就和8对齐了。

只不过最大的问题是，这个函数不接收`hw`的参数……，所以，很可能，不是我们相要的。

但我又找了一下`hw`的类`DeviceDisplay`，发现这个文件里很少用：

![picture 60](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139341595-57becab0aa04cd092d41f5176b3f5afd575609567c75524f460af9e009e9996e.png)

并且 `hw->`的调用也是一个都没。

##### 可疑2. `InputWindowInfo Layer::fillInputInfo()`

![picture 57](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643138409793-047823adc1fbf5db5d36fc05a824d31ff9e81110a4ce1a4ef69833d217f0c026.png)

我基于`getBounds`函数追到这块（可疑1也有`getBounds`），发现代码结构就比较像目标代码。尤其是`x|ySurfaceInset`的构造与使用，可以看到`xSurfaceInset`也用到了`layerBounds.getWidth()`函数，并且后续还有一句`layerBounds.inset(xSurfaceInset, ySurfaceInset, xSurfaceInset, ySurfaceInset);`看起来仿佛在构造两个眼镜的某些参数一样。

#### MID: `position`

![picture 61](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139564016-37973fb37dbac73e4fa89c3e2d7fb127e1415c0699dc370f39de3ffd47749d10.png)

分析了`win`后，下面的一个问题就是关于`position`的，然而光从这段来看的话，似乎没有起到任何作用，仅仅是一个赋值，所以不太懂这个设计。如果这是个全局变量，我还比较明白，说明`position[2]`可能是左眼右边点，而`position[3]`是右眼左边点。

### EASY: `libs/gui/include/gui/ISurfaceComposerClient.h`

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643033846337-6802e52cc14b9224fef4725b5669c87755209b419956bd021bf4d9964743f521.png)

该文件中，只增加了一个`eVrWindow`的变量。

而它其实只是在`surfaceflinger.cpp`中用于判断是否是`vr`模式，这个比较简单直白。

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643034044680-f14735982c660c54119d8c30ba2c493318c839a4dcc947981240d04b555f4b70.png)

#### MID: `services/surfaceflinger/HmdType6DistortionMesh.h`

这个文件也是新增的，和 [[3/9, MID] `services/surfaceflinger/HmdType6DistortionMesh.cpp`](#39-mid-servicessurfaceflingerHmdType6DistortionMeshcpp) 配套，是其头文件定义，需要仔细分析一下。

其中'DistortionCorrection tool' 可以生成mesh矩阵，目前这个sdk后续需要的话还要再找晓研看看。

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643040148049-06f4be1b8f9329cbd382b432af2ed50f60d1f2570370536de4095854cbd4c8f0.png)

大致理解了一下：

1. ~~`#define HMD_TYPE6_DM_VERTCOUNT 10201` 应该就是宽度像素`1020`乘以10再加一，也就是每个像素点有10个`vert`，应该是指`vertex`顶点的意思~~
2. `HMD_TYPE6_DM_WIDTH/HEIGHT`代表一个mesh的宽与高，长度都是100，也就是有101个顶点，所以一个mesh就有`HMD_TYPE6_DM_VERTCOUNT = 101 * 101 = 10201`个顶点
3. `#define HMD_TYPE6_DM_IDXCOUNT  (HMD_TYPE6_DM_WIDTH * HMD_TYPE6_DM_HEIGHT * 3 * 2)` ：两个三角形，每个三角形三个顶点，`IDXCOUNT`就是总索引数的意思
4. `#define HMD_TYPE6_DM_ELEMCOUNT (HMD_TYPE6_DM_VERTCOUNT * 4)` 每个`vert`应该有4个维度的数据，`x y u v` 或者 `a b c d`，可以看做是结构体内最小单元的总个数
5. `#define HMD_TYPE6_DM_SIZE (HMD_TYPE6_DM_ELEMCOUNT * sizeof(float))` 所有顶点的存储空间大小
6. `#define HMD_TYPE6_DM_K0~5` 六个参数

#### EASY: `services/surfaceflinger/HmdType6DistortionMesh.cpp`

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643036038107-6f5bfa4f08a73c080083d6658e6c99c07bda32e73215ff0da0cc550426c67150.png)

该文件属于新增，内容是基于程序自动生成的，不过生成脚本也是老SDK了。

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643036091354-24e7e13ad10eeb2616e356fc5fb3c324683ec92e9c6fc0347b611ebe179a5fbb.png)

### MID: `services/surfaceflinger/SurfaceFlinger.h`

![picture 62](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643141116414-687d66c090a80e5605ccb2195b6f58e78cb17670744a61c5488e8aae8e1f495c.png)

p1里面全是和RK相关的，没啥好看的，直接看p2。

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643042375823-7b1c802f21be285ac5167118355b488311204fe26cfb06c306d771a612851110.png)

p2里主要是定义了8个变量和1个初始化函数。

其中4个变量都是mesh，两个（`mLeftEyeMesh | mRightEyeMesh`）是vr模式下的左右眼mesh，两个（`mLMesh | mRMesh`）应该是正常情况下的左右眼mesh。

`mDistortionEnabled`控制是否启用反畸变。

`mFrameBuffer | mTextureName | mTexture` 应该都是为 `initFB` 函数服务的。

现在，我们要追踪一下，这几个包的导入问题，因为API变动很大。

首先是`Mesh.h`和`Texture.h`，原先在8中是在`surfaceflinger/RenderEngine`下，11则换了地方：

```sh
➜  native git:(b8293fd0e0) ✗ find . -name "Mesh.h"
./libs/renderengine/include/renderengine/Mesh.h

➜  native git:(b8293fd0e0) ✗ find . -name "Texture.h"
./libs/renderengine/include/renderengine/Texture.h
````

追过去。

![picture 63](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643141519785-f873abee7c470d96e142c3aa5364827a8a82bb4123ea6c6eaa34c801dc63c45d.png)

可以看到，在 8 的`surfaceflinger.cpp`中需要的两个函数`getPositionArray()`和`getTexCoordArray()`都在，这说明 api 接口没变，只是位置变了，那就比较好说。基于此，`Texture.h`的调用部分暂时就不看了，应该比较稳妥。

update at 2022-01-27: NO! 编译到 10 后发现有各种问题，主要是语法层面的，后来发现，接口还是有一些变化。

![picture 89](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643256750858-a6fc4675727af6e51e1500700eaec2cd7d3be2feaae48ba2dac19424d599e11c.png)

首先，如上，命名空间有变化，原来是`android::Mesh`，现在变成`android::renderengine::Mesh`了。

`gl2.h`和`gl2ext.h`的位置不太一样，在另一个模块下：

```sh
➜  native git:(b8293fd0e0) ✗ find . -name "gl2.h"
./opengl/include/GLES2/gl2.h

➜  native git:(b8293fd0e0) ✗ find . -name "gl2ext.h"
./opengl/include/GLES2/gl2ext.h
```

但本质还是一样的，所以这部分代码应该就比较好写了。具体来说，就是把`RenderEngine`改成`renderengine`其它照抄。前缀应该不用加了，因为`include`下应该会有环境变量，自动能搜索到。

#### variable initialization

![picture 74](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643184157839-37d1c335d7b499ec969a1e6772e7ca1b23cdab2daabb0f64366f3ee2c80a56af.png)

![picture 75](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643184227668-9c72ba2d4ab05453921ad65bca9735089fc63a0966706c0883373601e8476b1b.png)

对比来看，确定把初始化变量写在位置 5 即可。

### `services/surfaceflinger/SurfaceFlinger.cpp`

![picture 64](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643142332055-4ad345818863122d35aca8a353f315178b086666c831a3fefd0e32257b294f1d.png)

`surfaceflinger.cpp`的 p1 里对旋转做了较多的考虑，并且还包括一点非 RK 属性的修改，好在我们目前也不用旋转，所以 p1 对于我们来说依旧可以忽视。

接下来重点看 p2。

#### part 1. initFB

> :warning: 编译顺序有问题。思路，对标 8 里面的一些初始化变量，在 11 中找对应的新的构造方式。

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643042777978-417faf89b357d77feae1fa777d737459a5d70a6214656aba3790a419963e4898.png)

初始化过程中，可以看到，`mLeftEyeMesh/mRightEyeMesh`和`mLMesh/mRMesh`的初始化参数是不一样的，为啥这么初始化，目前还没有形象认识。

:warning: 这段中写了一些比较关键的系统参数，是我们需要去验证核实的，值得引起注意：

```yaml
## /system/build.prop
persist.sys.framebuffer.main=1920x1080

# HDMI display:
sys.hwc.device.primary=HDMI-A
# VRG:
sys.hwc.device.primary=DP
```

而他说`uint32_t width = 1920; // half of display size`，说明宽度都是按照 3840 来算的。

然后就是对标 10 版本。

![picture 76](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643185687929-684a3a046f2ee223d226408e6c157616274f8c54702ac4feb37374240d8818de.png)

10 里面虽然加了`Factory`的初始化方式，但其实只是其中一个属性，注意看`mFactory`的前缀`m`与其他的`mXXX`是等价的，而我们要加的变量正是`mXXX`类型，所以就可以不用管`mFactory`里面是什么，因为是同级的。

#### part 2. function of `initFB`

:warning: 目测 `initFB` 函数绝大部分都不需要改，不过有一个系统属性 `vr.luci.distortion.enable` 值得注意，会基于这个决定是否启用反畸变。

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643045333549-7ac057aaa61ddf8c4e60350e3789827e11e3bee1b3a21781326ec0399fcec2a5.png)

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/research-diff-1643045571855-3c6ce4abe57b1c9aef7c01beffec3e8f4422b45c0e980bd444f28dfcafd8099b.png)

#### HARD: part 3. `doComposeSurfaces`

![picture 65](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643144378837-b02055303c54561f2c6769b85e61e9213186d752c210af0d1d507899a61f690a.png)

很惨啊，8 里面的接口直接被剥了。

![picture 66](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643144504135-08af60009b0a7f5dfecaf1b01b1d718be6b7aefaed131e72e18aa2a3a0e33496.png)

![picture 67](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643144692166-10a3bf592b15344ddcc3939b5f372ccde6f8ca9d275aaee1f53c1a12e2e47478.png)

太惨了！正好是 10->11 接口被剥了！

![picture 68](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643145769167-82f36a6b3eb301404a04d6cbdb6ece0c9751161413fa7882fad10c07da2661ce.png)

#### drawing flow

ref: https://waynewolf.github.io/2014/06/22/surfaceflinger-and-client/

```text
handleMessageRefresh
     |—> preComposition
     |—> rebuildLayerStacks
     |—> setUpHWComposer
          |—> HWComposer::createWorkList <== hwc="" structures="" are="" allocated="" |—=""> Layer::setGeometry()
          |—  set per frame data
          |—  HWComposer::prepare
               |—> hwc prepare
     |—> doComposition
          |---- skip composition on external display if condition meets
          |—> doDisplayComposition
          |    |—> doComposeSurfaces
          |     |—> DisplayDevice::swapBuffers
          |          |—> eglSwapBuffers
          |          |—> FramebufferSurface::advanceFrame
          |—> DisplayDevice::flip(…)     <== just="" update="" statistics="" count="" |--=""> Call DisplayDevice::compositionComplete(), notify each display
               |--> DisplaySurface::compositionComplete()
                    |--> FramebufferSurface::compositionComplete()
                         |--> HWComposer::fbCompositionComplete()
                              |--> NoOP if HWC >= 1.1
                              |--> used only in framebuffer device case.
          |—> postFrameBuffer
               |—> HWComposer::commit
                    |—> hwc set
                    |—> update retireFenceFd of hwc_display_contents_1
               |—> DisplayDevice::onSwapBuffersCompleted
                    |—> FramebufferSurface::onFrameComitted
               |—> Layer::onLayerDisplayed
               |—   update some statistics
     |—> postComposition
```

ref: https://zhuanlan.zhihu.com/p/127324424

![picture 69](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643146727064-cfab15ef79d008d64d5c5c29bb93680cfbfe470563fb4a9b1fac82a572690c18.png)

#### doComposeSurfaces code flow

```text
handleMessageRefresh -> doComposition -> doDisplayComposition -> doComposeSurfaces
```

- Preparation work:
  - If GLES and hwc compositing, clear frame buffer target first
  - If GLES only, drawWarmHole first
- Render layers to framebuffer
  - For all layers if using hwc
    - do nothing if HWC_OVERLAY layer, display hardware will blend the layer
    - render with opengl if HWC_FRAMEBUFFER layer, call layer->draw()
    - set the layer’s acquireFence
  - For all layers if no hwc
    - just render with OpenGL, call layer->draw()
- Now all the GLES layers are drawn on frame buffer target, waiting to swapBuffers

#### rendering client layers

![picture 70](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643150328404-b6176d87255273165579bfd2a35670f914000f9426a8818582fe30c9af7a333b.png)

## 编译

在把第二个 patch 的所有内容都打进 AOSP 10 后进行编译，发现了新的错误，有些变量没有，这说明某些是在 p1 里定义的。

![picture 90](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643259309065-400df4bbf3122953663fc51c354aedddc86e1c4e6c9bfedcc83b70fd1108c903.png)

这就麻烦了……

又是漫长的找变量过程。

### 目前策略

将在 ubuntu 机上所有的 commit 保存成新的 patch，打回主机 n10 环境，再与 n8 进行对比

### 目前策略更新@2022-01-27 15:16:38

考虑到有很多版本问题一一要修复，所以采用 git 方式单独对 surfaceflinger 进行控制管理，但是之前由于把西瓜的 `hmdservice` 加进来在`native`级别一下`add`了，导致 git 脏了。

所以现在，拷贝了一份当前的 `surfaceflinger`（无 git 版本），然后重新拉一份`surfaceflinger`，接着`git init`，再把原来的 `surfaceflinger`拷贝回来，再用`git commit`进行更新，这样就有`git history`了，可以用于生成纯净的 patch。

### :white_check_mark: `error: use of undeclared identifier 'dirty'`

problem:

![picture 94](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643270250699-1c9b572414150473871cc166d63ffc1f9db000bc70832683ff679bc566a8e739.png)

analysis:

虽然位置对了。

![picture 91](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643260910516-4abaab424f67566d72adcc7e9abbb2b307cb061d87d4a36d150f189c45242253.png)

但其实 10 里面换名字了……

![picture 92](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643260957409-fa660a0b04134b6438e205e23cd65c20fb141bd3165cb11f1609294f2c26fee5.png)

resolution:

change `dirty.in` to be `debugRegion.in`, then fixed.

![picture 95](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643270380057-954041c435c5766e2a9246e7117a4a459a521f5a79a7a79f2303fd5285f851fd.png)

### :white_check_mark: `error: use of undeclared identifier 'displayTransform'`

![picture 93](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643261575586-cfca4d2780992850c4e04abea21bf5408be3b635015dce9579b570189ec50702.png)

### :white_check_mark: `error: unknown type name 'Transform'`

reason:

when added `displayTransform` line, then introduces `Transform` which is not imported.

![picture 96](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643270733917-88cfbcc1133a098b2826d05c30e3b39d6d8ee14d7cb0b5a8f0638d9d17e8aa81.png)

analysis:

the `Transform` is defined at: `ui/`:

![picture 98](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643270989945-25cc87f8ab8ed0edcbb29ff230e4bae7ceac528caedc5e2d5f6c6a3a58ad77d6.png)

and the raw 10 used a `ui` prefix both in `.h` and in `.cpp`

![picture 99](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643271063371-bfa7569154cf91f89dc21bd4e5721d8c3147664285e4452d12f86b057ed18eee.png)

~~so we need manually add a `ui` namespace or add `ui` prefix when we use `Transform` variable.~~

So it's not wise to add a `ui` namespace in case of introducing conflict or affecting efficiency.

It's better for us to manually add `ui` prefix when we use the `Transform` variable.

resolution:

![picture 100](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643271284098-f4a1b2cdf2424fa314a06bbed114872856c668e162db1bb0e1c45e39c6f9b599.png)

ok:

![picture 101](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643271321290-c49b3cbb94321e9e2238ea90e0f40f39820261a82ae79eedafb2333871fb9508.png)

### :white_check_mark: `error: no member named 'draw' in 'android::Layer'`

analysis:

simulate what AOSP 10 is doing when 8 is `draw`ing.

![picture 103](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279221765-a1e4058d1e04f5d37f0a516a93209ef3d1b3ddba7f55fc4f7900eee0d1918d3a.png)

It can be seen that the `draw` becomes a more sophisticated `prepare-xxx`, just copy it now!

resolution:

![picture 106](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279430687-975f38e5baea3c7fb28b39f497903ea1adff155bd30ee69226c9fed65ff8bb3a.png)

ok:

![picture 102](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279186528-7be5d583cf681cd2e1ea09285900e3a16d75fa3d886125fbe68bc8922e2a823f.png)

### :white_check_mark: `error: use of undeclared identifier 'mRenderEngine'; did you mean 'renderEngine'?`

problem:

![picture 105](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279394094-1e450fe68afcb37d5e44a2828b89e1c3990fc7ab9377dc988e62fa8ff5b2c0e7.png)

reason:

not initialized (even not defined in `.h` ?):

![picture 107](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279496721-63842bc08930f43fc784d44b88fce06f6d98587154b89a735c93b057c5c253d2.png)

do not exist exactly in `.h` !

![picture 108](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279565516-6244202abc3f4d78c323b4c8f1020c9e4cbe196f7d4834eee0b32fbb9fa30657.png)

resolution:

just add it !

![picture 109](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279898807-928c19aec2a62ffc35659af4183e664b9a33be7d8e4aa0e9ffcf9f0e17aa227e.png)

ok:

![picture 111](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643279913238-cf52cc95e317162963545b1a547daa9dbf7b4890f7555e5f532fd24026886d8f.png)

### :white_check_mark: `error: too few arguments to function call, expected 5, have 3 (RenderEngine->setupLayerBlending)`

reason: the api changes.

`setupLayerBlending` 的新接口里取消掉了 `alpha` （这个倒觉得无所谓），但是新增了 `disableTexture`, `color`, `cornerRadius`

![picture 117](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643292858686-1f7a4757e6e3e83dde525b484a6bd5db04a64037f9a973c164f047b8d1a367b4.png)

analysis:

We can learn from this:

![picture 118](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643292958805-09c2701d0625b1dfbd79c9f850e2f4d6283d58523ae82b34c0a383d463b708d2.png)

And the `color` and `radius` is derived from `layer`

![picture 119](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643292986311-2e4418c71630b84636051ef3671cf04d57ba17dd3b2b4b1c5db9faf3c56e468d.png)

![picture 120](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643293004105-7710cb8c71467925ad086b641ab0924796c179471cc9f608852d6088b67e7b8d.png)

Except the `mTexture` is alone:

![picture 121](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643293026912-63f585a4bc133f40b0e1a2135a6e8934a605ac2e788817a3d18f245329baf253.png)

ok:

![picture 122](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643293040926-f04cffcb41fe54e5f505f75826d5e60a17ceeb3226514f031e379afb4e1272d0.png)

### :white_check_mark: `error: use of undeclared identifier 'renderArea'`

reason:

It's caused by my change the `draw` to be `prepareLayer` in where there is no layers.

resolution:

Now we just commented them, since it's possible that they are not that important and annoying to simulate a `draw` function using `setupLayerBlending`.

![picture 123](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643293414679-afb2a4aa3891330597ff734e28f65e82963a1ec415b50c0fa7e64dce8b9f4fca.png)

ok / bonjour:

![picture 124](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643297485831-621052ab16b1695fa050b8d0c4ebd6c8b18fcf3ca52cb65ffadc0c730dec3379.png)

### 终于成功了！2022-01-27 23:37:03

![picture 125](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643297534048-7dc15ff720dd39a7cf6577f3c9cc7e09e479b79e480b590062851a4ff29952b0.png)

## 年前主要工作目标

### pre-check list

- [x] ++ Check props in `/system/build.prop`; note: 这个暂时先不用管了，找智伟找了一下，都没找到

### core 1 list

- [x] +++ Add files of `HmdType6DistortionMesh`
- [x] +++ Add `HmdType6DistortionMesh` into `Android.mk`

### core 2 list

- [x] +++ suppress `#error` of `gls2.h`
- [x] ++ Add variable `eVrWindow` into `ISurfaceComposerClient.h`
- [x] +++ Add variables definition into `surfaceflinger.h`
- [x] +++ Add `initFB` into `surfaceflinger.cpp`
- [?] +++ Add `doComposeSurfaces` into `surfaceflinger.cpp`

### core 3 list

- [x] ++ Add `vr` variable and `get|set` into `Layer.h` (but implemented in `surfaceflinger.cpp`)
- [?] + Add `win.right` and `position` into `Layer.cpp`

## 年前主要困难分析

### `Layer.cpp`中关于`win`和`position`

这是 patch 截图：

![picture 71](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-problems-1643166975497-f3269e96a60010bb3b024829d8d884748f7870a6c070e92c708da11c0516b0a4.png)

这是 AOSP 8 和 11 中这部分代码位置：

![picture 72](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-problems-1643167134668-81d592f0345aba1a0e67f670a66b9ea7772884ab0a2dbe340e772325a65170f8.png)

8 中 patch 修改的部分是在`drawWithOpenGL`函数内，但是 11 中同文件没有这块内容，11 中 OpenGL 整体都移出去了。这是第一个问题。

第二个问题就是，这个`win.right = hw->getWidth()`我没有太理解。`win`是基于`bounds(computeBounds())`得到的，是减去透明区域后的区域，它的构造如下：

![picture 56](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643137518943-d8297585f5c0fa99e05666d3eaeb3a8e87e544c55deb73dd390d224ab758b3c9.png)

8 和 11 在这里的区别不是很大，只不过`computeBounds`名字改成了`getBounds`，内部实现也相应地更简洁了一些，核心思想就是窗口区域减去透明区域，得到的就是所谓`Rect`，也就是实际区域吧。~~至于结构体是啥，四个坐标吗，还是啥，应该倒也不是那么重要。~~

我这里其实主要困惑的在于，如果`win`是指那个活动窗口，比如说某个浮动窗口，那在 vr 模式下单独改其`right`为`hw`的宽度，而不把`left`改成 0，这是否会有问题呢？至少看起来不是那么对称，所以这里在原理上来说，是一个非常大的困惑。

还是，先看看如何在 11 中实现这个修改吧。

#### 可疑 1. `Layer::prepareClientComposition()`

![picture 58](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643138949603-bd8010805a1b2d7274c9adf4c6c21c43c549711742aadeb94d21c388e1468ca7.png)

在这块里，最大的可疑原因是正好与左边 8 的版本对齐，并且函数名就是在画图：

![picture 59](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139039422-45fe81e61a85a9a61de7d2d34b40023143d959a149be023b1f89ef875e73a6eb.png)

另外也有一个关键赋值语句：`layerSettings.geometry.boundaries = bounds;`，我们若在赋值之前，修改`bounds.right`为`hw.getWidth()`，或许就和 8 对齐了。

只不过最大的问题是，这个函数不接收`hw`的参数……，所以，很可能，不是我们相要的。

但我又找了一下`hw`的类`DeviceDisplay`，发现这个文件里很少用：

![picture 60](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139341595-57becab0aa04cd092d41f5176b3f5afd575609567c75524f460af9e009e9996e.png)

并且 `hw->`的调用也是一个都没。

#### 可疑 2. `InputWindowInfo Layer::fillInputInfo()`

![picture 57](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643138409793-047823adc1fbf5db5d36fc05a824d31ff9e81110a4ce1a4ef69833d217f0c026.png)

我基于`getBounds`函数追到这块（可疑 1 也有`getBounds`），发现代码结构就比较像目标代码。尤其是`x|ySurfaceInset`的构造与使用，可以看到`xSurfaceInset`也用到了`layerBounds.getWidth()`函数，并且后续还有一句`layerBounds.inset(xSurfaceInset, ySurfaceInset, xSurfaceInset, ySurfaceInset);`看起来仿佛在构造两个眼镜的某些参数一样。

#### position 似乎没有被调用的困惑

![picture 61](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643139564016-37973fb37dbac73e4fa89c3e2d7fb127e1415c0699dc370f39de3ffd47749d10.png)

分析了`win`后，下面的一个问题就是关于`position`的，然而光从这段来看的话，似乎没有起到任何作用，仅仅是一个赋值，所以不太懂这个设计。如果这是个全局变量，我还比较明白，说明`position[2]`可能是左眼右边点，而`position[3]`是右眼左边点。

### `surfaceflinger.cpp`中关于 `doComposeSurfaces`

![picture 73](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-problems-1643167933698-db055f067f102fdb102f9439b13842250003015447719c5459a4593af867b2b9.png)

![picture 65](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/surfaceflinger-patch-research-1643144378837-b02055303c54561f2c6769b85e61e9213186d752c210af0d1d507899a61f690a.png)

很惨，8 里面的接口直接被剥了，经过对比，实际上 10 还是有的，所以是 11 时删的。

而 `doComposeSurfaces` 函数正好还比较复杂：

```text
handleMessageRefresh
     |—> preComposition
     |—> rebuildLayerStacks
     |—> setUpHWComposer
          |—> HWComposer::createWorkList <== hwc="" structures="" are="" allocated="" |—=""> Layer::setGeometry()
          |—  set per frame data
          |—  HWComposer::prepare
               |—> hwc prepare
     |—> doComposition
          |---- skip composition on external display if condition meets
          |—> doDisplayComposition
          |    |—> doComposeSurfaces
          |     |—> DisplayDevice::swapBuffers
          |          |—> eglSwapBuffers
          |          |—> FramebufferSurface::advanceFrame
          |—> DisplayDevice::flip(…)     <== just="" update="" statistics="" count="" |--=""> Call DisplayDevice::compositionComplete(), notify each display
               |--> DisplaySurface::compositionComplete()
                    |--> FramebufferSurface::compositionComplete()
                         |--> HWComposer::fbCompositionComplete()
                              |--> NoOP if HWC >= 1.1
                              |--> used only in framebuffer device case.
          |—> postFrameBuffer
               |—> HWComposer::commit
                    |—> hwc set
                    |—> update retireFenceFd of hwc_display_contents_1
               |—> DisplayDevice::onSwapBuffersCompleted
                    |—> FramebufferSurface::onFrameComitted
               |—> Layer::onLayerDisplayed
               |—   update some statistics
     |—> postComposition
```

目前已知的，关于 opengl 的实现路径变动：

```text
## Mesh.h, Texture.h 都在该目录下
RenderEngine --> ./libs/renderengine/include/renderengine

## gls2.h, gls2ext.h 都在该目录下
GLES2 --> ./opengl/include/GLES2
```

但是关键是 `doComposeSurfaces` 中的函数体非常大，结果到 11 全被割出去了。
