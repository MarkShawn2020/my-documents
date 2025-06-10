比较好的教程： [系统要求 - ComfyUI](https://docs.comfy.org/zh-CN/installation/system_requirements#comfyui)。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e90fbbf22255d9650d9695dbf29773d2.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---

## 安装与启动

直接官网 [Download ComfyUI for Windows/Mac](https://www.comfy.org/download) 下载。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/87c634e995f877b0d53cabb035d9c91e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

安装后打开。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9da75471a633b5484f063c5bc994e019.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

按照提示一步步往下，**确保要有 15G 存储空间**。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/38c5f75cf41490d8833855c7561bfc81.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


启动后，就会看到已经有一些模板。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/fb1069c28298dd45f28281f730791678.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

```ad-tip
之后每次启动都会先进入一个服务器启动环节。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1699a2206216b7cdca8fdf01ff94193e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

以及注意里面的网址，是需要魔法的。
```

系统配置界面。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/489dc6d2b80d9f87467c30f199ead035.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


## 复现

```ad-tip

100% 有效快速入门一个领域的办法，就是 **自己动手复现**。

```

本次我想实现的是一个艺术字生成，经过我们的层层搜索定位到了一个 B 站视频：[Comfyui清明春天艺术字工作流，超细致30分钟0基础内容，直播剪辑版，controlnet的使用方法，lora堆的使用方法_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1qM4m1X7GP/?vd_source=9cb028fe6c978c6816626901d9249eb1)

接着顶楼给出了工作流的地址：[V1.0 AI艺术字工作流基础版——设计师学Ai-工作流-设计师学Ai-LiblibAI](https://www.liblib.art/modelinfo/51a2dbc70a354fa3a1e90a28e672855f?from=personal_page&versionUuid=0b750af4de4746e5b22ed83f3a11f414)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7ccfa650fbf1e19ec265a09a0ac06114.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

我们点击”下载“按钮，是一个 json 文件。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/13f6abb3ab63484e4eb6dad8fc2b1fe5.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

根据经验，这是一个 workflow 文件，直接在 comfyui 里导入即可。

提示有节点缺失：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/cc59f78edb438281dd91af49e815d9cf.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


一个个点击安装即可。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ee9dd07eaa1710fd5c7f28a6404331b8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



---

## 错误的尝试

浏览模板，发现比较匹配我们需求的是”混合 ControlNets”。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9ad1e2b5dc149ded75087a8c8249d4b2.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


打开发现需要下载模型。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/432a9514b39676e29b6a2fd8237cfef3.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

点击下载即可。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/622bab130be25574583ac5020fd6f9bb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


上传两张图片，点击运行。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/aa08e5f4efc576a1b6f239166ad953a6.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

也不知道到底是不是在运行🤔

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/fc89d4eb7777ec5d62b61de5cfe02b09.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

似乎是看这个顶部的进度，不过有点慢。

看来 Apple 芯片还是不大行的。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a1ae4cdcbf8c648169959fde2d2092ab.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

hmmm，为什么有一只猫🤔

但似乎还在跑🤔


## FAQ

### 模型没下载好，导致报错，重新下载即可。


出 bug 了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2141d92c9497ca18155f06ad87df0ff7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


点击“显示报告”。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/0881d272c6d310b380f47bb76b647b9f.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



**直接无脑复制发给 claude。**

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/da4f0d807c8df4223b4e32c6a50b6d61.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


claude 提示我们去 civitai 重新下载模型。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a50a5770d132c6d359786fe7ab4958a8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

听话下载模型。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9383e7957b252a0eb6f7c48e3f59e0f1.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

下载完之后对比一看，果然是之前没下载好的问题。

覆盖即可。

## 参考文档

- [系统要求 - ComfyUI](https://docs.comfy.org/zh-CN/installation/system_requirements#comfyui)
- [‌﻿⁡‌⁤⁣‬﻿​‬⁤⁡‬​​‌‌​⁤⁡⁤‍​​​⁣​⁤‌﻿‬​​⁤⁢⁣​‌‌​⁤⁤⁢​‬⁢⁡​​⁣安装说明 - Feishu Docs](https://tffyvtlai4.feishu.cn/wiki/T6KswU6jmiDMOUkgovhcK0XHncd)
- 