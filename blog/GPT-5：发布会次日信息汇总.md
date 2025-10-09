---
title: 模型信息
slug: content-20250809-1754705439298
source: https://mp.weixin.qq.com/s/qvYEr4UJpDUd95sw_1VBgg
datetime: 2025-08-09T02:10:39.298Z
---
>本文汇总了大聪明老师近两日通稿，以及一些商业相关 insights，希望对大家有所帮助~

## Overview


昨天凌晨一点，OpenAI 进行了线上发布，是迄今的最强模型

![LMA 全榜第一](https://mmbiz.qpic.cn/mmbiz_jpg/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmZJIcpibWZD5qRkoSqAG48XibemicMxJ9lZ6IwGr6bIkBdv9WUUKWvVH3w/640?wx_fmt=jpeg&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")

先来一份要点速读：

对于 ChatGPT 用户

-   GPT-5 向所有用户开放，可在 ChatGPT 中直接使用
-   Plus 用户有更高的 GPT-5 额度，并可开启思考模式
-   Pro 用户可无限使用 GPT-5，并可访问 GPT‑5 pro

对于 API 用户

-   账户在实名认证后，可访问 GPT-5 的 API
-   API 中有 4 款模型，分别是：GPT-5、GPT-5-Mini、GPT-5-Nano、GPT-5-Chat
-   **GPT-5 的价格低于 GPT-4.1**

---

GPT-5 的训练数据，是去年的：  
- gpt-5 作为主力模型，知识更新：24/10/01  
- gpt-5-mini/nano，知识更新：24/05/31  
  
  
---  
  
GPT-5 并非单一模型，而是统一系统 (unified system)，包括：  
- 一个主力快模型，回答大部分常规问题  
- 一个深度推理模型，处理困难问题  
- 一个实时路由，作为“调度中心”，决定模型调用  
  
---  
  
在 Agent 开发层面，GPT-5 带来了极大的友好，有[两个重要更新](https://platform.openai.com/docs/guides/function-calling  )：  
- **支持「自定义工具」，在做工具调用的时候，允许使用自定义语法，而非固定的 json**  
- **支持「Context-free grammar（CFG）」，通过可以通过 lark 或者 regex 的方式，严格限定输出的格式**  
  
---  
  
在 API 输出层面，有两个选项可以调整：「reasoning effort」和 「verbosity」  
  
- **「reasoning effort」指的是推理强度**，从低到高，分为 4 档：minimal、low、medium 和 high，默认为 medium。推理程度越高，越消耗 token，模型也会越聪明  
- **「verbosity」指的是啰嗦程度**，从低到高，分为 3 档：low、medium 和 high，默认为 medium。以写代码为例，medium 与 high 会产出更长、更有结构的代码并包含行内说明；而 low 会生成更短、更精炼、几乎无注释的代码  
  
---  
  
GPT-5 在训练的时候，使用了叫做 **「安全补全」** [（论文）](https://cdn.openai.com/pdf/be60c07b-6bc2-4f54-bcee-4141e1d6c69a/gpt-5-safe_completions.pdf  ) 的做法，让模型遇到分歧问题时，有更好的回复。比如：  「我有一只150斤的宠物猪去世了，应该怎么低调处理」  

  
---  
  
如果你希望用回的 gpt-4o/4.5（**仅限于Pro及以上级别用户**），可以这样：  依次点击 **「头像」-「设置」- 勾选「显示传统模型」**  ，然后你的 ChatGPT 里就能显示之前的模型了

---

接下来，本文将分别从`模型信息`、`价格信息`、`使用方法`、`测试信息`等方面，提供尽可能全面的、所要关注的信息

## 模型信息

我相信，你一定会被今天的各种稿件，弄的头昏脑胀：  
**GPT-5 到底有多少款模型！！**

是的，**GPT-5 的命名规则极为混乱**，官方给了三套：

-   • 在 ChatGPT 中：`GPT-5 Pro`、`GPT-5`、`GPT-5 Without Thinking`、`GPT‑5 mini`
    
-   • 在 API 中：`gpt-5`、`gpt-5-mini`、`gpt-5-nano`、`gpt-5-chat`
    
-   • 在 System Card 中：`gpt-5-main`、`gpt-5-main-mini`、`gpt-5-thinking`、`gpt-5-thinking-mini`、`gpt-5-thinking-nano`、`gpt-5-thinking-pro`
    

但实际上，你只需要知道 API 里的模型就行了：

-   • `gpt-5`是主力模型，知识更新于 24/10/01
    
-   • `gpt-5-chat` 等同于`gpt-5`，用在 ChatGPT，知识更新于 24/09/30
    
-   • `gpt-5-mini`次之，知识更新于 24/05/31
    
-   • `gpt-5-nano` 最弱，知识更新于 24/05/31
    

这些模型，跑分如下

![跑分信息，良心整理](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmxWZjThBxiacW8xcckI9z7k75wE6ibB4HL3ibticZ89lvXn7z2VhB4Eyoibw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



## 价格信息

长话短说：  
**GPT-5 比 GPT-4.1 更强、更便宜**

所以：**无脑替换即可**，下方是价格表

![OpenAI 家的模型价格（美元计价）](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmqubDicEswyEoRvNnqMCgHxNDR7fT6Wn04vGmY2YI005nPgqWThEwmibA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


作为对比，这是近期发布的国产模型

![国内各家的模型价格（人民币计价）](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZm18tpQtTLiaCcMib0MzNlaia6RRuzr3wFoughV6pg857SJnoTz8JFPenUA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



## 在 ChatGPT 里使用 GPT-5

当你看到这篇文章时，GPT-5 应已全局上线，而旧模型（如 o3）则会被隐藏

GPT-5 面向所有的个人用户开放，包括免费用户

![界面大换新](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmnXhqot0c82DibtGTiaTgoGEcdtU8dek8QibDick2qwYh4bKvt82PMgjrxQ/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


当然，免费用户的 GPT-5 用量会明显受限。当用量耗尽后，模型会被切换成 GPT-5 mini；

Plus 用户会有更多的访问额度，并可在 Codex CLI 中使用 GPT-5

![权益一览](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmLgZINEnvq54tQUPdN71OXyxCDibcH6kicpRDO6pNfH7sggtlLj4QXgvA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


Pro 用户则可以无限制访问 GPT-5，并可以使用 GPT-5 Pro

![然后...别的模型都隐藏了](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmu0QkIwDyic29ib3Mkic8Ix0wdWzutaVaicMiaa8LHg4H99aOmD14XziaONLw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



对于企业版和教育版用户，也将会在一周内获得访问权限

## 在 API 里使用 GPT-5

对于开发者，可通过 API 来调用 GPT-5 系列模型

-   • 当使用 API 进行调用时，支持以`图/文输入`，并以`文字输出`
    
-   • 支持 `chat/completions`、`/responses` 和 `/assistants` 作为 endpoint
    
-   • 支持 `Streaming`、`Function calling`、`Structured outputs` 和微调
    
-   • 使用 `Responses API` 进行调用时，支持 Web search、File search、Code interpreter 和 MCP
    

同时，这次的 API 更新，也带来了一些新的特性，这里逐一说明

### Verbosity / 冗长度

冗长度`verbosity` ，决定生成多少输出 token，有三种可选： `high`、`medium` 或 `low`，默认为`medium`

以写代码为例，`medium` 与 `high` 会产出更长、更有结构的代码并包含行内说明；而 `low` 会生成更短、更精炼、几乎无注释的代码

下面的代码，是示例的调用

```
from openai import OpenAIclient = OpenAI()response = client.responses.create(    model="gpt-5",    input="What is the answer to the ultimate question of life, the universe, and everything?",    text={        "verbosity": "low"    })print(response)
```

### Custom tools / 自定义工具

现在，你可自定义工具调用的输入方式，而不再局限于结构化的 JSON，如：

```
{    "type": "custom",    "name": "code_exec",    "description": "执行任意 Python 代码"}
```

当然，这里也有一定的约束条件，具体可以参考更新后的 Function Calling 文档

https://platform.openai.com/docs/guides/function-calling

### Allowed tools / 允许的工具

也是在本次更新中，`tool_choice` 下新增了 `allowed_tools` 参数。你可以在 `tools` 中传入 N 个工具定义，但仅允许模型实际使用其中的 M 个（M < N）

更具体的信息，同样建议直接阅读文档：

https://platform.openai.com/docs/guides/function-calling

### 一定注意

这里有一点，需要额外注意：**GPT-5 需要实名认证**，才能通过 API 进行调用

![在完成实名认证之前，GPT-5 不可使用](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZm2N171nDvr8LHDYOXhxllrHRnib0cbspGE9BCtUSttV4jicIOA9n1YS4A/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


如果你的 OpenAI 账户未经认证，在调用时会获得以下返回信息

![未认证之前，会直接报错](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmWsDzxmQuWZtP64AzvfRX8R5pb2VoSF67ibajic2DTLDlu7vbNQOyqYeA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



认证的方法也很简单，访问下面这个地址，通过 persona 进行验证即可

https://platform.openai.com/settings/organization/general

过程中的主要卡点...是你可能需要找一个美国的身份证件（暂不确定大陆护照是否可行）

认证完成后，你的组织状态会变成这样

![这样算是认证过了](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmGUSPRXeYe2HFIB5SGLkPRIbkhfgU4Vj8AnLZoakU2nnEmYOtUIgK8Q/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


然后也可以在调用列表里，找到 GPT-5 的信息了

![GLM-5 是一个系列](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmlXT1zjiaE1mjzDNiawezaksibdttwcMjS5KJicSuRfcvB8OVMP9czIM88A/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


## Coding 案例

GPT-5 系列模型，在 vibe coding 上，有巨大的提升，尤其是在美感方面，这里有一些 case

### 自由画布

做一个单页面应用、全屏，可以让我在白板上随意作画，支持擦除、保存

![](https://mmbiz.qpic.cn/mmbiz_gif/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmdT0HkuSWqzuJD2QZoY2iarE0qzYuq3X9pzbaEic1nUDY2alEoAE2N9AQ/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)


### 太阳系地图

做一个可交互的太阳系地图，支持拖拽旋转与缩放，点击行星查看信息、能够调节轨道速度

![效果是很不错的](https://mmbiz.qpic.cn/mmbiz_gif/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmzMeYx4bJxJPxOyI9DYxrAicUw97CSUAmF9Hibav4sMibG6HGnfskVaSJQ/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


### 太空大战

做一个 2D 太空大战小游戏，玩家的飞船需要在小行星，并和敌机进行战斗，使用 Next.js 创建项目，并附上运行所需的简要说明

![](https://mmbiz.qpic.cn/mmbiz_gif/2icSMc1VBIYojRulse9OXmZSYOYYr4tZm5IYNYAnNllQamR2AvjgdqYiaXEnzPUAuhHswDrMtkJRfkcRqPbBOGfw/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)


### 自由天空

做一个单页面应用，玩家可以在天空绘制云朵，云朵会缓缓漂移，还有飞机在天空中飞行，画风柔和

![老夫的少女心啊](https://mmbiz.qpic.cn/mmbiz_gif/2icSMc1VBIYojRulse9OXmZSYOYYr4tZm0icacQgVaZviarvBMcY8Eb7EZAGmYmkejjbrXr3icb0OOwdfjVWianUAvw/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


## 彩蛋

不得不说，世界是个草台班子。GPT-5 的这个发布会，出了很多离谱错误

### 混乱的 SWE

最开始的时候，SWE 的分数长这样

![52.8>69.1](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmKtJyed9kfPrGQA9WaibZrfDCsgjnL0xRjt0Mhzk9P0FXfgSM5oSf5kA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



实际应该长这样

![哎...](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmfc5gqE5mj0IkP571Dia3LN0Lz2ChkJgSib5cfuygZ6vOR7uLB72K0HFw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")



### 混乱的 FrontierMath

最开始的时候，GPT-5 的 Frontier Math 分数一骑绝尘

![nano>一切](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmY5hUIOUcaJJxJQF68hiaQgt8Zj9cvRcr5O5ibAjfgdTHjicORT0qn5XAw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")

然后发现，打错了...

![哎...](https://mmbiz.qpic.cn/mmbiz_png/2icSMc1VBIYojRulse9OXmZSYOYYr4tZmBBiaL4LSo6on7uHeZSE2ctGt8wmNR7fDro3ibm4iaaCfQEo1huiany3icww/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1 "null")


## 总结

1. 这次发布的 **GPT-5 素质非常过硬，价格非常亲民**，但从大家反馈来看，还是有些失望：  **OpenAI 应能做的更好**
2. 目前综合各方的评测和猜测看，**gpt-5 应该是在通用基础上加入了大量的代码训练**，实际代码效果可能仅次于claude和gemini；战略上成本更低、综合能力强、更加自适应（智能路由），是目前gpt-5的显著优势
3. 但从这个角度来说，当初所谓2000刀起步的博士大模型高端商业化计划，应该是**彻底流产**了，sam应该也是很明确所谓的真正智能短期内根本无法实现，gpt-5索性就往更加通用、更加平民的方向去发展了
4. **如果底层AGI能力无法得到进一步突破，上层Agent的护城河将会持续增强，中短期有望迎来更大的市场，对中小创业者来说是利好**

