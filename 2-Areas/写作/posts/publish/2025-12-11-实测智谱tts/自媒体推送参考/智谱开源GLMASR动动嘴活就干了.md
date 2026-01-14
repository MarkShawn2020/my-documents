---
title: 智谱开源GLMASR动动嘴活就干了
slug: glmasr-1765422433589
source: https://mp.weixin.qq.com/s/ZNibelqb_mkIWWAUU8rNXg
datetime: 2025-12-11T03:07:13.589Z
---

# 智谱开源GLM-ASR：动动嘴，活就干了

[魔搭ModelScope社区](javascript:void\(0\);)

*2025年12月10日 20:38* *浙江*

在小说阅读器中沉浸阅读

  

![图片](https://mmbiz.qpic.cn/mmbiz_png/UBWAWibiaa4jeNZXo8lmagjDJVYCHsr5VibY1tgdecEBV4K1eeOaedNjOOnc9VtFmnDp6OUKhBEXgueU2bGSRpCCQ/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1#imgIndex=0)

  

智谱正式发布并开源了**GLM-ASR系列语音识别模型**，并推出基于该系列模型打造的桌面端**智谱AI输入法**。

  

本次发布模型与产品包括：

-   GLM-ASR-2512：全球领先的云端语音识别模型；
    
-   GLM-ASR-Nano-2512：参数量仅**1.5B**的开源SOTA端侧语音模型；
    
-   智谱AI输入法：将语音识别与大模型深度融合的桌面端效率工具。
    

**实现让用户真正做到“动动嘴，活就干了”，从“把话变成字”走向“直接用语音完成任务”。**

  

### GLM-ASR系列模型开源

GLM-ASR-2512是智谱新一代语音识别模型，支持将语音实时转换为文字。在多场景、多语种、多口音的真实复杂环境测试中，保持行业领先的识别表现，字符错误率（CER）仅为0.0717。

  

在此基础上，研究团队开源了GLM-ASR-Nano-2512。这是一个**1.5B参数**的端侧模型，却取得了当前开源语音识别方向的SOTA表现，并在部分测试中优于若干闭源模型。它将识别能力压缩到本地运行，在保证高精度的同时，实现更强的隐私保护与更低的交互延迟。

  

![Image](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)

  

基于上述模型能力，智谱AI输入法正式上线，让用户在PC端用语音丝滑交互。用户不但可以实现精准的语音转文字，还可以实现翻译、改写等智能操作，真正实现“指尖即模型，语音即指令”。

  

智谱AI输入法：在输入中直接调起模型能力

  

智谱AI输入法基于GLM-ASR系列模型打造，让用户在电脑端用语音丝滑交互。用户不仅可以实现精准的语音转文字，还可以在输入法中直接调用大模型能力，完成翻译、改写、情绪转化等操作，实现“指尖即模型，语音即指令”。

  

-   所选即所改，从听写到改写的一体化：传统输入法只负责打字，而智谱AI输入法直接调用底层GLM模型帮助用户翻译、扩写、精简屏幕上的任意一段文字，同时完成智能润色，让输出更加自然、通顺。整个过程在输入框内完成，实现“理解-执行-替换”一体化，无需在多个应用间反复切换。  
      
    
-   千人千面人设切换：支持设置不同“人设”风格，实现同一句话在不同场景下的不同表达。例如，在工作场景中，选择“面对老板”，口语化的碎碎念瞬间转化为逻辑严谨、条理清晰的工作汇报；在生活场景中，切换至“面对伴侣”，文字则变得温柔俏皮，贴近日常聊天语境。
    

  

-   Vibe Coding（语感编程）搭子：针对开发者，特别推出了Vibe Coding体验，并与智谱Coding Plan账号打通。结合多语言支持与代码理解能力，开发者可以通过语音快速输入代码逻辑和注释、查找遗忘的Linux指令、用自然语言指挥AI完成复杂数学计算或脚本编写。同样，设计师也可以从传统的“用手抠图”过渡到“用嘴做设计”。
    

  

-   耳语捕捉与高效热词：针对开放式办公室、图书馆等公共场景，优化了对微弱声音的捕捉能力，并区分环境噪声。只需轻声说话，即可精准转为文字，解决公共场合“不好意思用语音输入”的痛点。同时，支持用户一键导入专属词汇、项目代号（如AutoGLM）及生僻人名、地名等。只需在设置中添加一次。
    

  

### 体验与下载

现在，你可以在智谱开放平台bigmodel.cn调用最新GLM-ASR-2512模型。同时，为开源社区提供了1.5B的端侧模型GLM-ASR-Nano-2512，权重及推理代码均已发布。

  

即日起，智谱AI输入法面向所有用户开放，并免费提供2000积分，相当于28天使用时长。欢迎体验！

  

-   GLM-ASR-2512
    

-   使用指南：  
    https://docs.bigmodel.cn/cn/guide/models/sound-and-video/glm-asr-2512
    
-   体验中心：
    
    https://bigmodel.cn/trialcenter/modeltrial/voice
    
-   接口文档：
    
    https://docs.bigmodel.cn/api-reference/模型-api/语音转文本
    

-   GLM-ASR-Nano-2512
    
    https://www.modelscope.cn/models/ZhipuAI/GLM-ASR-Nano-2512
    
-   智谱AI输入法：
    

-   Mac/Win访问下载：https://autoglm.zhipuai.cn/autotyper/
    

  

  

点击阅读原文，直达模型~

  

  

* * *

  

👇点击关注ModelScope公众号获取

更多技术信息~