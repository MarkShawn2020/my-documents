---
title: GLMTTS开源3秒复刻情绪万变
slug: glmtts-3-1765431949095
source: https://mp.weixin.qq.com/s/UNILGo-FFXUwCbviZGxOJQ
datetime: 2025-12-11T05:45:49.095Z
---

# GLM‑TTS开源：3秒复刻，情绪万变

[智谱](javascript:void\(0\);)

*2025年12月11日 09:07* *北京*

在小说阅读器中沉浸阅读

![图片](https://mmbiz.qpic.cn/mmbiz_png/UBWAWibiaa4jfjOtX2L9c6tOmL4R31Bv92CCgm0fYn88YJuhd9oPol6ibV64LPgKLybKX5mXOZjsc0k3YfROu7kvQ/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=0)

  

今天，我们正式上线并开源 GLM‑TTS 工业级语音合成系统。

  

只需 3 秒语音样本，GLM‑TTS 即可学习说话人的音色和说话习惯。在通用朗读、情感配音、教育评测、电子书、有声客服等场景中，实现自然流畅、贴近真人的语音。

  

已关注

关注

重播 分享 赞

关闭

**观看更多**

更多

*退出全屏*

[](javascript:;)

*切换到竖屏全屏**退出全屏*

智谱已关注

[](javascript:;)

分享视频

，时长01:53

0/0

00:00/01:53

切换到横屏模式

继续播放

进度条，百分之0

[播放](javascript:;)

00:00

/

01:53

01:53

[倍速](javascript:;)

*全屏*

倍速播放中

[0.5倍](javascript:;) [0.75倍](javascript:;) [1.0倍](javascript:;) [1.5倍](javascript:;) [2.0倍](javascript:;)

[超清](javascript:;) [流畅](javascript:;)

您的浏览器不支持 video 标签

继续观看

GLM‑TTS开源：3秒复刻，情绪万变

观看更多

转载

,

GLM‑TTS开源：3秒复刻，情绪万变

智谱已关注

分享点赞在看

已同步到看一看[写下你的评论](javascript:;)

[视频详情](javascript:;)

  

我们希望，AI 不只是「会说话」，而是能在合适的场景下，说出既像真人、又符合情绪的声音。

  

为实现这一能力，GLM‑TTS 在架构上采用两阶段生成，并在训练中引入基于 GRPO 的强化学习方案，在公开评测的「字错误率」和「情感表达」上取得开源 SOTA 表现。

  

值得一提的是，GLM-TTS 仅使用 10w 小时训练数据，远低于行业主流商用模型。同时，GLM-TTS 也兼顾了训练成本和效果，预训练仅需要单机 4 天即可得到开源 SOTA“发音准确度”与超高“音色还原度”，精品音色 LORA 和强化学习也仅需要单机 1 天即可完成训练，远低于行业平均水平。

  

另外，GLM‑TTS 还以更低的价格获得了行业领先的 MOS 分数（平均主观意见分）。

  

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/UBWAWibiaa4jfjOtX2L9c6tOmL4R31Bv92giaKSicJWUNPIKTvI8WI6b75z4L6lzibibsc75KNutKicxtd4SI5FibhV4QQ/640?wx_fmt=jpeg&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=1)

  

## 典型场景：从 Demo 走向生产

GLM‑TTS 的目标，不是做出一个个「好听的 Demo」，而是长期支撑行业级语音生产。目前，我们重点验证了以下场景：

  

-   在教育场景中，适配多学科场景下的多音字和生僻字、生僻符号，讲解语气自然、有耐心；
-   在电子书与有声内容中，不同角色可呈现不同情绪风格；
-   在客服场景中，语气克制专业，避免夸张表演感。

  

1.教育场景

  

在教育与考试评测场景中，GLM‑TTS 适配多音字和生僻字、公式符号，为教材和题库批量生成标准发音示范音频，并在口语评测、听力训练等任务中保持大规模合成的一致性和准确度。例如：

  

-   高中数学教材示范，适配课堂教学示范场景：计算157! / 83! + √924 - 58³。  
    

  

  

-   生僻古诗词、多音词：君不见自从禹鼎沉泗水（sì shuǐ），魑魅魍魉（chī mèi wǎng liǎng）盈九州。城阙（què）辅三秦，风烟望五津，同是宦（huàn）游人。只恐双溪舴艋（zé měng）舟，载不动许多愁。  
    

  

  

2.电子书场景

  

在电子书与有声内容场景中，GLM‑TTS 既可以用单一音色完成整本书的朗读，也可以为不同角色配置专属音色，适配长篇小说、纪实、社科等不同文体的节奏与情绪，并以较低推理成本支撑大体量内容库的自动化生产。例如：

  

-   <开心情绪文本> 今天在路上看到了一只小狗，和主人玩的特别开心，他摇尾巴的样子让人看了心都融化啦！<悲伤情绪文本> 我真的不懂，为什么一切变得这么复杂，为什么我们无法回到从前？<愤怒情绪文本> 你怎么就那么不会说人话呢？  
    

  

  

3.智能客服

  

在智能客服与语音助手场景中，GLM‑TTS 能为机器人客服打造温和但克制的声音形象，降低机械感，在通话脚本中自然插入变量信息而不打乱整体韵律，并与上游 NLU/NLG 模块协同，支持从理解到回应的端到端语音交互。例如：

  

-   抱歉给您带来不便！您遇到的问题我们已快速响应，专属客服 \[工号\]9527会在 10 分钟内联系您详细沟通解决方案。
    

  

  

-   您好，我已理解您想查询 您的物流进度，当前包裹正发往北京，预计明日送达，有疑问可随时告诉我～
    

  

  

  

## 强化学习：让「会说话」更像「会表达」

要让语音从「可用」走向「好用」，强化学习（RL）是关键一环。

  

然而，在 TTS 领域，奖励设计难、训练不稳定等问题长期存在，业界多停留在 SFT 阶段。GLM‑TTS 基于 GRPO 框架，引入多维度奖励和稳定训练机制，在可控前提下提升模型的表达力和鲁棒性。

  

![Image](https://mmbiz.qpic.cn/mmbiz_png/UBWAWibiaa4jfjOtX2L9c6tOmL4R31Bv92ia2sP9K7m9PiacdB1G0BjQfIEWDia9Sm8vg75ZwE39rGBFYa83RXEYzlA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=2)

  

强化学习采用了训练数据与合成数据相结合的数据构造模式，实现了几乎零成本的数据生成。通过与训练算法的优化协同，有效避免了奖励欺骗（reward hacking），从而保证了模型性能的真实性和泛化能力，在未见过的测试集上同样取得了理想效果。

  

1.seed‑tts‑eval：降低错误率、提升相似度

  

![Image](https://mmbiz.qpic.cn/mmbiz_jpg/UBWAWibiaa4jfjOtX2L9c6tOmL4R31Bv92TyJghYO0zibwS2eCMLOIfS3iaVLR7xqJb27miaGbB3W7EhygU4rh94AqA/640?wx_fmt=jpeg&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=3)

  

在 seed‑tts‑eval 中文测试集上：

  

-   CER（字符错误率）：GLM‑TTS 的 CER 为 1.03%，处于开源模型第一梯队；引入 RL 后，GLM‑TTS\_RL 的 CER 降至 0.89%，达到开源 SOTA。
-   Sim（音色相似度）：GLM‑TTS 的相似度约 76.1，GLM‑TTS\_RL 提升至 76.4，在低 CER 前提下保持较高音色相似度，兼顾「发音准确」与「音色还原」。

  

2.CV3‑eval‑emotion：情感与准确度双领先

  

![Image](https://mmbiz.qpic.cn/mmbiz_jpg/UBWAWibiaa4jfjOtX2L9c6tOmL4R31Bv923ib16zVpIFlnmyrQXEyLW203NYWBl1ic6An66RosF6uDcholZ56wrbuA/640?wx_fmt=jpeg&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=4)

  

在 CV3‑eval‑emotion text\_related 数据集上（文本自带情绪标签）：

  

-   情感维度 SOTA：GLM‑TTS ‑ 精品音色\_RL 在 Happy（0.72）、Sad（0.52）、Angry（0.28）三类情绪上均取得 SOTA，平均情感得分（avg\_emo）为 0.51。目前其余商用模型多集中在 Happy 维度，在 Sad、Angry 等负向情绪上几乎无有效输出。  
    
-   兼顾发音准确度：在情感表现领先的同时，GLM‑TTS 的 CER 仍保持较低水平：

-   GLM‑TTS ‑ 精品音色 CER ≈ 1.33%
-   GLM‑TTS ‑ 精品音色\_RL CER ≈ 1.68%

  

整体优于其他商用模型，实现「情感表达 + 字错误率」双重领先。

  

## 开源&体验

为方便开发者、研究者和企业评估与集成 GLM‑TTS，我们同步开放模型权重、推理代码和在线调用接口。

  

#### 1.开源遵循 Apache License

  

我们将在主流开源社区同步开源 GLM‑TTS 相关资源（模型权重、推理脚本、示例项目等）：

  

-   GitHub：https://github.com/zai-org/GLM-TTS
    
-   Hugging Face：https://huggingface.co/zai-org/GLM-TTS
    
-   魔搭社区：https://modelscope.cn/models/ZhipuAI/GLM-TTS
    

  

开发者可以基于主流推理框架，在 GPU 环境中快速部署 GLM‑TTS，并按需做二次开发。

  

#### 2.开放平台与 API

  

如希望直接接入线上业务，可以通过开放平台调用 GLM‑TTS 能力：  

  

-   开放平台入口：
    
    https://docs.bigmodel.cn/cn/guide/models/sound-and-video/glm-tts
    
-   API 接口文档：
    
    https://docs.bigmodel.cn/api-reference/模型-api/文本转语音
    
    https://docs.bigmodel.cn/api-reference/模型-api/音色复刻

  

平台支持多种计费和 QPS 配置，覆盖从 Demo 试用到生产级大规模调用。

  

#### 3.在线体验

  

你也可以通过以下入口快速体验 GLM‑TTS 的合成效果：

  

-   audio.z.ai：上传文本或短语音 Prompt，生成专属声音；
-   智谱清言 APP / 网页版：在对话中体验多风格朗读与音色克隆。

  

更多技术细节详见「公众号次条」GLM-TTS 中文技术报告。

  

  

  

![图片](https://mmbiz.qpic.cn/mmbiz_png/UBWAWibiaa4jdVFS3g16cX4FSN12Juiaugj2TVlvFiciaBZdxQX3AEFoB236vQLXRNlfiahSre6ZhWibRKnvZ0vlIO5kw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=5)