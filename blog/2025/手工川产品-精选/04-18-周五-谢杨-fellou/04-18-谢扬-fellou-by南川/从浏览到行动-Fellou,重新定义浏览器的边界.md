
_在浏览器诞生三十年后，一个新类别正在崛起：行动型浏览器。_

```insta-toc
---
title:
  name: 本文目录：
  level: 1
  center: false
exclude: ""
style:
  listType: dash
omit: []
levels:
  min: 1
  max: 6
---

# 本文目录：

- 01. 引言：浏览器的三十年未变
- 02. 什么是"行动型浏览器"？
- 03. Fellou：Browser、Agent与Workflow的融合
- 04. 四大核心能力深度解析
    - 1. 深度行动（Deep Action）
    - 2. 混合影子空间（Hybrid Shadow Workspace）
    - 3. 主动智能（Proactive Intelligence）
    - 4. 智能体网络（Agent Store）与混合反馈经验学习框架（Hybird Feedback Experience Learning）
- 05. 横向对比：Fellou vs Dia vs 传统AI浏览器
- 06. 谢扬：从身份云到AI浏览器的跨界探索
- 07. 行业意义：浏览器2.0时代已经开始
- 08. 未来挑战与前景展望
- 09. 结语：与其等待未来，不如创造未来
```

## 01. 引言：浏览器的三十年未变

30 年过去了，浏览器最大的变化可能只是图标。

「互联网之父」蒂姆·伯纳斯-李 1990 年设计的基本交互模式——通过超链接实现网页跳转，以及输入网址、等待加载、回到上一页等逻辑，在今天仍岿然不动。都 2025 年了，我们还在用同样的姿势，对着屏幕傻傻地等待页面加载。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418203619.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

过去十年，Arc、Opera、Chrome 等浏览器都试图革新这一领域，最近的 Dia 浏览器也被视为潜在的游戏规则改变者。然而，这些产品本质上仍是将 AI 作为辅助功能嵌入传统浏览体验，是锦上添花，而非改弦更张。

直到今天，在 AI Agent 技术逐渐成熟的浪潮中，一个全新品类的浏览器——"Agentic Browser"（行动型浏览器）终于出现了。

<!-- ![宣发视频.mp4](宣发视频.mp4) -->

## 02. 什么是"行动型浏览器"？

在探讨 Fellou 之前，我们需要理解：什么是行动型浏览器？

当前浏览器市场大致分为三种：

- **传统浏览器**：Chrome、Safari等，侧重信息浏览
- **对话式浏览器**：如Edge (Copilot)、Opera One等，加入AI助手功能
- **搜索优化型AI浏览器**：如Perplexity Comet，侧重深度信息检索和摘要

行动型浏览器代表了第四种范式：**不仅展示信息，更能根据用户高层目标自主拆解任务、跨界操作并完成端到端任务交付**。这是从"认知层"到"行动层"的跃迁，从"会思考"到"能行动"的飞跃。

![四种浏览器.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/%E5%9B%9B%E7%A7%8D%E6%B5%8F%E8%A7%88%E5%99%A8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 03. Fellou：Browser、Agent与Workflow的融合

由 Authing 身份云创始人谢扬领导开发的 Fellou，将自己定位为"世界首个 Agentic Browser"。这一产品不是简单地将 AI 集成到浏览器，而是重新构想了浏览器的核心功能——从被动展示到主动行动。

Fellou 将三个关键组件整合为一体：

1. **Browser（浏览器）**：负责最广泛的Web内容访问与渲染
2. **Agent（智能体）**：负责"思考"和"决策"，基于LLM理解上下文、规划行动
3. **Workflow Automation（工作流自动化）**：负责"执行"和"工具化"，能调用不同API、插件、脚本

![5d842b3ff7d341c02037f1bbf1a02159.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/5d842b3ff7d341c02037f1bbf1a02159.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

这种架构使得Fellou从传统的信息展示工具转变为真正"帮你工作"的智能生产力平台。

## 04. 四大核心能力深度解析

### 1. 深度行动（Deep Action）

我在实测中最先注意到的是Fellou的Deep Action能力。这里分为两类行动：Research（研究）和Manipulation（操作）。

**Research模式**下，Fellou不仅能搜索公开网页，还能访问需登录的网站（如LinkedIn、Twitter）并进行深度信息采集。实测一个"调研日本招聘市场"的任务，Fellou用时约8分钟生成了一份包含市场规模、主要公司、行业趋势和进入机会的详尽报告。相比之下，Manus花费接近20分钟，而且内容深度不及。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418204033.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,90)

（预览地址：Report - Japan Recruitment Market Analysis, https://chat.Fellou.ai/report/share/japan-recruitment-market-analysis-SEW9XOga ）

更令人印象深刻的是**Manipulation模式**。我测试了"打开LinkedIn，写一篇关于DeepSeek的文章并发布"这一任务，Fellou完成了从登录、撰写内容到最终发布的全流程，无需我手动介入。这是我在其他AI浏览器上从未见过的能力。

<!-- ![](深度行动.mp4) -->

类似功能还包括：

- 在Gmail中自动发送会议邀请邮件
- 在Amazon上搜索并添加商品到购物车
- 自动将Product Hunt网站的热门产品信息整理到Notion

Fellou能够实现这些功能，关键在于它的浏览器使用框架Eko，它比常见的Browseruse框架执行速度快2.83倍，并具有生产级可干预特性。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418203930.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

在几天之前，我与两位朋友一起做了一份 Deep Research 调研：[Deep Research 横评 | 谁才是天命打工人？](https://mp.weixin.qq.com/s/O5suCvE7N3ccSPcIBZ8f3Q)，在这份调研里，除了秘塔搜索能在三分钟左右完成调研之外，其余产品全都需要近 20 分钟，这个结论与 Fellou 的官方测试结果一致。

但值得注意的是，秘塔之所以能达到这么快的速度，主要是因为它们是完全基于纯后端的 API 请求，而非像 manus 或者 Fellou 一样能够实现浏览器主动式浏览，众所周知很多网站必须经过 js 渲染才能拿到有效的内容，纯 API 是不行的。

而现在，Fellou 通过优化自研浏览器底层，实现了并行化浏览的能力，这样在信息获取的速度和质量上都达到了目前理论上的 SOTA ，非常值得肯定！据 Fellou/authing 创始人谢扬透露，未来这一块的性能还能大幅优化可能接近十倍，质量也会不断提高（authing 是领先的身份云系统，据透露贡献了部分 Fellou 驾驭隐私数据的能力）。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418210545.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418210718.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,90)

（预览地址：在小红书上找小米 SU7 的好评，报告用中文英文双语, https://chat.Fellou.ai/report/f01fcf27-09e1-45b2-ae87-8e4315f5bc63 ）


### 2. 混合影子空间（Hybrid Shadow Workspace）

Fellou解决了AI Agent执行任务时"抢占"用户电脑的痛点。通过构建"影子空间"，Fellou可以在后台并行执行多个任务，而不干扰用户的正常操作。

<!-- ![](混合影子空间.mp4) -->

在实测中，我让Fellou搜索并整理数据时，依然可以正常使用电脑处理其他工作。系统通过虚拟化环境同时操作多个网页，确保任务执行不互相干扰，同时还能共享会话信息以实现免登录访问。

这一机制解决了以往AI工具的核心痛点——要么占用主界面，要么需要单独开窗口操作。Fellou的影子空间让AI真正成为后台助手，而非前台干扰者。

### 3. 主动智能（Proactive Intelligence）

区别于传统被动响应的AI，Fellou能预判用户需求并主动提供帮助。例如，当我浏览某旅游攻略时，Fellou主动提示是否需要汇总相关信息或预订服务。

Fellou会实时捕捉用户在各网页的操作轨迹，积累行为数据并构建个人知识库，从而实现更精准的主动服务。这种"数字记忆"使Fellou不仅能执行明确指令，还能理解隐晦的需求信号。

<!-- ![](主动智能.mp4) -->

### 4. 智能体网络（Agent Store）与混合反馈经验学习框架（Hybird Feedback Experience Learning）

或许最具长期价值的是Fellou的Agent Store生态。用户可以将自身经验沉淀为独立的垂直Agent，这些Agent不仅服务自己，还能在社区共享。

例如，一位HR专家可以封装其招聘流程为工作流Agent，供其他用户直接调用；一位研究人员可以分享其文献检索与分析流程。这创造了一个以"智能体"为媒介的知识共享生态。

对于开发者，Fellou提供了Eko Framework——一套通过自然语言设计和部署Agentic Workflow的开发框架。这是开源框架Browseruse的生产级进阶版本，支持开发者创建复杂的自动化工作流。

除此之外，生产级的智能体一个关键挑战在于：**如何让智能体不仅依赖环境交互来持续优化行为，还能从结构化的失败反馈中获得改进**。

几天前，Google DeepMind 强化学习副总裁 David Silver 参与了一场播客访谈节目，探讨了如何从依赖人类数据的时代迈向自主学习的时代。

![Image](https://mmbiz.qpic.cn/sz_mmbiz_png/KmXPKA19gW9I2ibzpMAlKCOwe2zDbrut7bibB1LTRI3TWSiaiboMbwict4ZBcXN8TYkbuaiaC3wzaVLHuYNCQOQIKicHw/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

与此同时，David Silver 和他的老师、[2024 年图灵奖](https://mp.weixin.qq.com/s?__biz=MzA3MzI4MjgzMw==&mid=2650958043&idx=1&sn=dc02ed349a811c96abf0270968621120&scene=21#wechat_redirect)得主 Richard Sutton 合作撰写的论文《Welcome to the Era of Experience》称人们正站在人工智能新时代的门槛上，并有望达到前所未有的水平；同时展望了新一代智能体，认为它们将主要通过经验来学习，获得超越人类的能力。他们还探讨了定义这个即将到来的新时代的关键特征。（未来，这篇论文将成为 MIT Press 出版的书籍《智能设计》（Designing an Intelligence）中的一个章节。）

![Image](https://mmbiz.qpic.cn/sz_mmbiz_png/KmXPKA19gW9I2ibzpMAlKCOwe2zDbrut7mRLhniaWT2YN2YTLTElLoXeuaSBS9ibJn7XkrPQuWicT8HBAurxlIhU3w/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

（论文地址：https://storage.googleapis.com/deepmind-media/Era-of-Experience%20/The%20Era%20of%20Experience%20Paper.pdf ）

Fellou 基于此提出了一种**混合反馈经验学习（Hybird Feedback Experience Learning）框架**：当基于浏览器的智能体在执行任务过程中失败——无论是由于查询模糊、工具使用错误，还是规划错误——都会触发一个次级分析机制。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418225531.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


_混合反馈的经验学习架构_

在这一阶段，人类监督者或大型语言模型（LLM）将对失败的执行轨迹进行回顾性分析，从中提取出可操作的经验洞察，例如误解、次优决策点或被忽视的交互机会。

这些提炼出的经验随后被**注入至结构化的经验库**中，形成一个不断扩展的“**失败感知型示范语料库**”。当智能体未来再次遇到类似查询或情境时，基于检索的泛化机制使其能够主动调用此前的纠正策略，从而降低重复失败的概率，加速任务掌握过程。

这一混合机制整合了检索增强生成（RAG）与人类参与监督的优势，使智能体的经验库不仅是自我生成的，更是经过反思性丰富的。它标志着迈向具备**自我纠错能力**的智能体的关键一步，这种能力建立在真实世界交互与元认知分析的双重基础之上。

## 05. 横向对比：Fellou vs Dia vs 传统AI浏览器

我们不妨将Fellou与最近备受关注的Dia浏览器做个对比：

|功能维度|Fellou|Dia|传统AI浏览器|
|---|---|---|---|
|**核心定位**|行动型浏览器|对话增强型浏览器|信息浏览器|
|**任务执行**|自主执行跨平台任务|提供建议和辅助，用户执行|仅提供信息|
|**任务复杂度**|支持多步骤、跨平台工作流|支持单页面内辅助|基本浏览与搜索|
|**隐私访问**|可安全访问需登录网站|有限的辅助登录功能|无或有限|
|**执行环境**|影子空间（不干扰用户）|单一浏览器窗口|单一浏览器窗口|
|**执行速度**|多任务并行（如研究任务平均3.7分钟）|串行执行（依赖用户交互）|不支持自动执行|
|**生态拓展**|开放Agent Store与开发框架|提供基础扩展|插件生态|

Dia确实在UI设计和浏览体验上有其创新，但从功能维度看，Fellou与Dia的区别类似于"自动驾驶"与"驾驶辅助"的差别——前者实现端到端的任务完成，后者提供决策支持但仍需人工操作。

## 06. 谢扬：从身份云到AI浏览器的跨界探索

Fellou的创新与其创始人谢扬的背景密不可分。作为2021年福布斯亚洲30Under30入选者、北京科技新星，他在身份云领域已建立了相当的专业声誉。


![图片](https://mmbiz.qpic.cn/mmbiz_png/ocahOIMgOia7kIv1MxJrAXxbc7WBzic59xbsaf9PJgtq3xE1neMtaICc8pRQicLVaOhpdg3uoEU7EOKBY5MT1HAHA/640?wx_fmt=png&from=appmsg&tp=wxpic&wxfrom=5&wx_lazy=1&wx_co=1)

谢扬25创办Authing身份云，为企业和开发者提供事件驱动的认证服务。截至2024年，Authing已服务700+客户和数亿用户，平台拥有数万开发者，每月千万级认证次数。

从身份云到AI浏览器看似跨度很大，但实际上存在清晰的技术演进逻辑：

1. **身份认证**：Authing解决"谁能访问系统"的问题
2. **AI身份**：为AI Agent提供可信身份和访问控制
3. **行动浏览器**：为Agent提供执行环境和能力

这一演进路径反映了从"管理人类身份"到"赋能AI身份"的自然延伸，也代表了谢扬对未来人机协作方式的深刻理解。

>  仔细体味一下，**Authing 致力于解决 Who Am I，Fellou 致力于解决 What I Can Do**，这是一场大棋啊！

值得注意的是，Authing在美国的最大竞争对手Okta在2024年投资了一家名为Browserbase的云浏览器基础设施公司，这也表明浏览器相关技术在全球范围内受到高度关注。

## 07. 行业意义：浏览器2.0时代已经开始

Fellou 的出现不仅代表了一款新产品，更预示着浏览器行业可能的范式转变。

传统浏览器设计初衷是围绕文档展开的，即便现代浏览器功能丰富，其底层逻辑至今未变。而AI的狂飙突进为浏览器体验的重塑提供了契机。

在云端计算与本地设备的交互中，浏览器日益成为"中间层"，具备天然的优势：

1. 它能访问几乎所有网络服务和应用
2. 它是用户最熟悉的交互界面
3. 它既可支持复杂的文本交互又可展示丰富的可视化内容

Fellou所代表的行动型浏览器，标志着从"被动响应到执行理念的转变"，这与OpenAI的Operator、Anthropic 的 Computer Use 、智谱的"沉思"Agent 等的发展趋势不谋而合。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418214133.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


正如Fellou官网所说："**AI不会以应用程序的形式存在，也不会是一个按钮。我们相信它将是一个全新的环境——建立在Web浏览器之上。**"

## 08. 未来挑战与前景展望

尽管前景诱人，Fellou和行动型浏览器依然面临诸多挑战：

1. **安全与隐私**：Agent代表用户执行操作带来的安全风险需要严格控制
2. **操作一致性**：网页界面的不断变化可能影响自动化操作的稳定性
3. **用户适应**：从"动手操作"到"描述需求"的思维转变需要时间

长期来看，浏览器极可能成为AI Agent的主要载体——它既可通过网页接口访问遗留系统，又能通过API连接新一代服务。这种"双栖"能力使其成为理想的Agent执行环境。

同时，基于MCP和更高级协议的发展，Agent与网站之间的交互有望从模拟人类操作发展为直接数据交换，进一步提升效率和可靠性。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418213215.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250418213626.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



## 09. 结语：与其等待未来，不如创造未来

每一次技术变革都始于对现状的不满和对可能性的探索。从个人计算机到智能手机，再到今天的AI Agent，技术不断重塑我们与信息世界的交互方式。

Fellou作为"行动型浏览器"的先行者，代表了一种全新的思考方式——浏览器不再只是信息的窗口，而是行动的平台。它让我们看到，浏览器这个诞生30年的工具，仍有巨大的创新空间。

在这个AI技术日新月异的时代，我们不仅需要更聪明的AI，还需要更适合AI发挥能力的环境。Fellou的出现，让我们得以一窥未来人与AI协作的可能形态。

正如乔布斯所说："**The people who are crazy enough to think they can change the world are the ones who do.**"（那些疯狂到认为自己能改变世界的人，正是那些真正改变世界的人。）

Fellou正以实际行动重新定义浏览器的边界，将"浏览"转变为"行动"，这也许正是浏览器发展的下一个三十年的开始。

---

*（南川注：本文基于对Fellou的实测体验以及与团队的深入交流撰写。Fellou目前已开启全球内测，提供 Mac 版下载，预计2025年下半年开放Windows版和移动版。感兴趣的读者可访问 https://fellou.ai 了解更多，以及 **留言申领邀请码**。）*
