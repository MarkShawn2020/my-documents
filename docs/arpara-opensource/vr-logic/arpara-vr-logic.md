# arpara vr logic

## anti-distortion: implementation

我们需要生成一个 $(100+1)^2*2$ 的 mesh 网，这由我司内部生成，文件分别为 `HmdTypeXXXDistortionMesh.*` ，目前 `XXX=8`。

生成算法与 `opengl` 三角型绘制原理有关，并且需要综合眼镜焦距、分辨率等进行调整，此处不展开。

核心问题是`mesh`的初始化位置与实现。

<img alt="picture 50" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/arpara-vr-logic-1645799660292-b30748482118e3c0214c2f314d65d241d5dc18a6ed7ba08a488601511d77b73d.png" />

检索可知，`AOSP` 内部只在`GLESRenderEngine.cpp`的三个函数内部初始化了`mesh` ,分别是 `fillRegionWithColor | drawLayers | handleShadow` ，这三者在业务上并非选择关系，我们只需要处理 `drawLayers`即可。

在 `drawLayers` 函数中，`Mesh` 的构建参数与我们的不同，最主要的差异是体现在顶点的个数上，AOSP 只需要处理 4 个顶点，但我们的反畸变在效果上则需要越多越好，因此不可共用同一个 mesh。我们第一版修改如下：

<img alt="picture 51" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/arpara-vr-logic-1645799848783-1be7214a86835bb5d9aa49d083caacc2363ed48546d1366a3bd356919c45bdd3.png" />

但该设计存在问题，按照现在的需求，我们只应在检测到 Arpara 的 app 在运行时才需要启用，更准确地说，是在检测到某个 layer 是在渲染 arpara 的 app 时才要启用反畸变，以排除系统弹窗这种不能启用反畸变的场景，否则将造成分裂（智委）。

因此我们的反畸变控制逻辑需要进一步精细到每个 layer 层面。

这时，如果我们直接把 mesh 初始化下移，预期会大幅降低性能，因为每次绘图时，遍历 layer，然后分别初始化每个 mesh。理论上，AOSP 可以直接把 mesh 写成静态变量，但他们没有，而是写在了函数的内部，这也许是出于后续还要进行裁剪等处理或防止泄露等原因。

考虑到我们的 mesh 的顶点、尺寸`3840*1920` 等都是固定的，理论上我们可以静态写死反畸变 mesh 的一切属性，但由于条件限制我的开发环境是`1920*1080`亦或`1280*720` ，因此比较合适的是，至少尺寸这块还是基于 layer 的实际大小来重新设定。

也就是，最合适的办法，静态初始化一个反畸变 mesh，然后在遍历 layer 时，需要该 layer 正在渲染 arpara 的 app，则基于这个 layer 重新调整尺寸，并采用我们的 mesh 进行渲染。

---

但这里有个问题：在 `drawLayers` 中遍历的 `layer` 并非 `class Layer` 而是 `class LayerSettings*` ，在 `LayerSettings`中默认是没有`activity name`的相关信息的。

因此我们需要定制。

---

```mermaid
flowchart TD;

subgraph logics
direction TB

    Layer::isArparaVrEnv["logic of Layer::isArparaVrEnv:\nThe activity name of layer\nincludes one of the following:\n1. 'com.XR.LeadingIdeal' for release\n2.'com.arpara.vr.sample' for debug"]

    -->
    isTimewarpEnabled["logic of ProgramCache::isArparaTimewarpEnabled:\n\`(mKey & ARPARA_MASK) == ARPARA_ON\`"]
end

subgraph initLayer[Layer::Layer]
    initArparaVrEnv[const mArparaVrEnv = Layer::isArparaVrEnv]
end

subgraph prepareFrame[Layer::preparePerFrameCompositionState]
forceClient[compositionState->forceClientComposition = mArparaVrEnv]
end

subgraph prepareClientComposition[Layer::prepareClientComposition]
settingLayer[layerSettings.mArparaVrEnv = mArparaVrEnv]
end

subgraph drawLayers[GLESRenderEngine::drawLayers]
direction TB
    subgraph traverseLayers
    direction TB
        layerSettings.mArparaVrEnv -- YES --> arparaVr
    end
end

subgraph arparaVr[ARPARA VR SYSTEM]
direction TB
    antiDistortion & timewarp
end

subgraph antiDistortion[ARPARA AntiDistortion]
direction TB
    buildArparaMesh
    --> initArparaPosition
    --> initArparaTexCoords
    --> drawMesh
end


subgraph timewarp[ARPARA Timewarp]
direction TB

    subgraph inputPoses[generate poses]
        hmdService[["hmdService\n(stable only)"]] & mockQuaternion["mockQuaternion\n(\`persist.mock.arpara.timewarp\`)"]
        --> poses[renderPose + presentPose]
    end


    poses
    --> setTimewarpMatrix["mState.arparaTimewarpMatrix =\n calculateTimewarpMatrix\n(renderPose, presentPose)"]
    --> setUniform["Program::setUniforms(mState.arparaTimewarpMatrix)"]
    --> generateVertexShader["ProgramCache::generateVertexShader(ARPARA_SHADER)"]

    enableTimewarp["mState.arparaTimewarpEnable \n= mArparaVrEnv"]
    --> calculateNeeds["ProgramCache::computeKey\n(mState.arparaTimewarpEnable)"]
    -- Key::ARPARA_ON --> setUniform
end

subgraph Layer
    initLayer
    -- decide forceClient --> prepareFrame
    -- carry ARPARA info --> prepareClientComposition
end

Layer --> drawLayers
```

## data

### package names

- release: `com.XR.LeadingIdeal`
- debug: `com.arpara.vr.sample`
- debug: `com.arpara.arparahome`

## info

- version: 0.0.1
- date: 2022-02-25
- author: 南川
