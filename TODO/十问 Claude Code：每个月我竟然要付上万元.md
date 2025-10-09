- 定义
  - cc：Claude Code
- 时间线
  - 5 月 25 日，我们几个 AI 创业者朋友一起创建了 cc 的交流群
  - 6 月 24 日，我第一次正式使用 cc，当天消耗 0.6 刀
  - 7 月 25 日，我的 cc 累计消耗 1292.25 刀
- ……

![使用 cc 开发的 cc 费用可视化，reference: https://github.com/MarkShawn2020/claude-code-manager](https://poketto.oss-cn-hangzhou.aliyuncs.com/a6729acdd646756a4f78b95720c68bb0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

从 2025 年中旬起，如果你身边有一位程序员，他没有每个月为某款 AI 产品名义上付费一万元以上人民币（实际一千多），那么不用怀疑，他一定不够卷。

cc 正在以某种完全全新的方式影响着世界的生产力、生产关系，以及消费行为、消费认知与消费习惯。

基于我们在最近两个月接近 10 个 AI 群的深度交流与数十个项目的实战探索，特在两周月之际汇总一些我们使用 cc 的实际感受、经验与教训。

## 什么是 Claude Code


这是我电脑的日常工作界面，这里面每一列都有一个Claude Code。

---

> 参考 Claude Code 官网： https://www.anthropic.com/claude-code

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/54c419953c07b85ba181a7f5768d43bb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2beed1bcf164459d121001a040cfd32a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


简单来说，Claude Code 是一个专为开发者设计的 **AI 编程协作伙伴**。它将 Anthropic 最强大的AI模型直接集成到您的**终端（Terminal）** 中，让您无需离开命令行界面即可完成复杂的编程任务。

它的核心理念是成为开发者的“新合作者”，在您熟悉的工作流和工具中，以思想的速度推动代码库的演进。

### **核心特性**

#### 1. **深度代码感知 (Deep Codebase Awareness)**

与许多只分析孤立代码片段的工具不同，Claude Code 具备对**整个代码库**的深入理解能力。

- 它使用“代理搜索”（agentic search）来自动分析项目结构、依赖关系和编码模式。
    
- 能够跨越多个文件进行协调一致的修改，而不仅仅是修改单个文件。
    

#### 2. **终端原生体验 (Works Where You Work)**

Claude Code 直接在您的终端中运行，旨在最大限度地减少上下文切换，提高工作效率。

- **无需切换窗口**：所有交互都在您最常用的命令行中进行。
    
- **IDE 集成**：可与 VS Code 和 JetBrains 等主流集成开发环境（IDE）协同工作。
    
- **利用现有工具**：能够调用您已有的测试套件、构建系统和版本控制工具（如 Git）。
    

#### 3. **强大的执行与自动化能力**

它不仅仅是代码生成器，更是一个能够执行任务的代理。

- **从概念到提交**：能够处理从阅读一个功能需求（Issue）到编写代码、创建测试、修复错误，最终提交合并请求（Pull Request）的完整流程。
    
- **文件操作与命令执行**：可以直接在您的工作环境中创建、编辑文件和运行命令。
    

#### 4. **开发者完全掌控 (You’re in Control)**

安全性和可控性是其设计的关键部分。

- **明确授权**：在没有得到您的明确批准之前，Claude Code **绝不会**修改您的任何文件或执行任何命令。
    
- **适应您的风格**：它会学习并适应您项目的编码标准和模式。
    
- **可配置与扩展**：提供SDK，您可以基于它进行构建或在 GitHub Actions 等CI/CD流程中运行。
    

### **主要应用场景**

- **新项目上手 (Code Onboarding)**
    
    > 对于刚加入项目的开发者，Claude Code 可以在数秒内扫描并解释整个代码库的架构、主要组件和功能，极大地缩短了学习和适应时间。
    
- **自动化开发流程 (Turning Issues into PRs)**
    
    > 您可以将一个在 GitHub 或 GitLab 上的 issue 交给 Claude Code，它会自动分析需求、编写实现代码、增加必要的测试，并将整个过程打包成一个 Pull Request，让您从繁琐的流程中解放出来。
    
- **复杂的代码重构 (Powerful Edits)**
    
    > 凭借对整个代码库的理解，它可以执行复杂的重构任务，例如升级框架、替换库或在多个文件中统一实现新的设计模式。
    

### **如何开始使用？**

您可以通过以下两种方式之一来使用 Claude Code：

1. 拥有 **Claude Pro 或 Max** 订阅计划。
    
2. 拥有一个 **Anthropic Console**（开发者控制台）账户。
    

总而言之，Claude Code 旨在通过将一个具备深度代码理解和执行能力的AI助手无缝集成到开发者的核心工作流中，从而彻底改变软件开发的效率和体验。


## 我为什么要用 Claude Code

回答这个问题，并没有那么显然。

在 Claude Code 出现之际，我正在使用 cursor、windsurf 等 AI IDE（现在更火的是 augment），与此同时，我也大量地尝试 chatgpt、gemini、claude 等 AI App，以及 void、cline 等开源编码工具，以及 same.new、heyboss、bolt、v0 等 AI 网页生成产品。

基于人月神话的理论，我个人觉得 GUI（Graphics User Interface，图形化用户界面）相较于 Claude Code这样的 TUI（Terminal User Interface，命令行用户界面）始终拥有相对较大的优势。

![人月神话p157](https://poketto.oss-cn-hangzhou.aliyuncs.com/29c69be5e399a224fe7858f6e98bd045.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


在 Claude Code 之前，我只在类似 htop、ANSI-art 等命令行工具上感受过 TUI 的震撼。

![htop 实时界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/28ddf513cd5b495367bd32ef7c33f969.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![source: https://github.com/EtoDemerzel0427/ANSI-art](https://poketto.oss-cn-hangzhou.aliyuncs.com/5cbc3ec91d6be8b404d72fd77929443c.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


但它们的交互体验始终是有限的。

而且当年乔布斯正是看了一眼施乐的图形界面，这才让头发蓬乱、留着浓密大胡子、也喜欢尝试各种迷幻药的神经科学博士天才比尔·阿特金森在六个月内着手实现：**打造一款属于大众的机器，让人人都能拥有外观悦目、造价亲民（就像埃奇勒建造的房屋一样）、使用方便（像时尚厨房用具一样）的电脑**，后世经久流传的那句“**伟大的艺术家窃取灵感**”正源于此。

![source: https://worldscience.cn/c/2023-03-28/641603.shtml](https://poketto.oss-cn-hangzhou.aliyuncs.com/6c629852fa49a655dd37d69364577f4f.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


即便很多资深程序员会坚持使用vim等IDE，但对大众来说，以DOS为代表的TUI走向以Mac、Windows、iPhone、Android为代表的GUI，这样的趋势，在过去几十年可能从未倒退过。

而在我最早开始接触计算机的时候，那时候我们还是用 Visual Studio / Dev-C++ 这样的上古 IDE，再后来我才同时使用 Jetbrains、VSCode，然后才是最近一年的 Cursor、Winsurf等。

![各类典型IDE，你用过多少？](https://poketto.oss-cn-hangzhou.aliyuncs.com/956f21690ee2dee620b5c98fba56bfa9.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

尤其是过去几个月深度使用 cursor、windsurf 等 IDE 的时候， 我经常会使用选中某几行代码然后发送到聊天窗这样的功能，以及也有在网页开发预览时鼠标选中某个元素以发给聊天窗的需求。

但总体来看，我觉得一款 AI IDE （GUI）的优势如下：

1. 更强大与灵活的上下文组织能力：我可以选中某几行，或者 at 某个文件甚至某个组件，甚至通过在预览页选中某个元素，就能轻松地组合成我想要的上下文
2. 完整的、熟悉的开发环境：我可以拥有更好的代码阅读体验，以及基于插件市场安装我所熟悉的插件
3. 等等

在 Claude Code 出现之前，一切都是那么地自然，仿佛 AI IDE 就应该长这样。

但我们完全忽视了最核心的一个问题。

在 AI 时代，在 Vibe 时代（**人们只关心目标是什么，不那么关心怎么实现**，而这个 B AI 还真地给装到了），我们最关心的是，当我们提出一个需求目标的时候，AI 是否能够帮我们实现目标，并且效果尽可能地好。

而最诡谲的一点是，**开发出了人类历史上最强大的编程模型 sonnet-3.5、sonner-4 的 Anthropic 公司又开发出了最强的编程Agent，它能够比其他的AI公司在理解上下文、给出修改建议等场景做地更好，并且工程质量、用户体验、迭代速度也是顶尖的**。

然后你会发现：**当一个模型和Agent能力足够的强之后，其他一切的UIUX优化都成为了无穷小量，回答质量是唯一的用户体验**。

除此之外，由于不需要API中转，以及基于文件的纯后端交互，Claude Code的响应速度也显著优于套壳厂商。

![手工川图解为什么Claude Code速度可以更快](https://poketto.oss-cn-hangzhou.aliyuncs.com/882733fd0ae44d507a63cbbb6cc1b698.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



![延伸交流：为什么不同AI IDE的效果有差异](https://poketto.oss-cn-hangzhou.aliyuncs.com/134b2739692cbfb65c5c03de1cddbf89.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

最后，额外的一些感受，**当我们被迫强制在一个命令行里去串行地查看所有的文件改动历史的时候，由于缺少了多窗口的干扰，我们反而看代码更认真了：）**



## 我用 Claude Code 做了什么
## Claude Code 到底牛在哪里

## 别人是怎么用 Claude Code 的
## 我是怎么用 Claude Code 的

ok，基于以上的分析，大家已经很明白我们为什么选用Claude Code，主要就是效果好（**这世界目前只有两种Code Agent：Anthropic 的 Claude Code，以及其他**（也许Augment 也可以一战，待评测）），以及速度快。

但对于我来说，还有更显著的其他优势，一方面是我本来就喜欢使用命令行，另一方面，是我更加喜欢并行开发。

Claude Code 给了我这样沉浸式并行开发多个项目的可能性。

以下是 gamma 为我做的一份关于我 Vibe Coding 部分总结的 PPT。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/65965c4cf05c53d8bb4eefd1ccc7ede8.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e92814d66f2427d11856fa6aebf61d02.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9d2e3445a2a75a033bf43761c850bc3f.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/896f63deb9097a8a21eca906437efa74.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/f4cdba200249acb2d4c2fb9f6c63c0d8.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/4fabd009aebeabe9b3905a61ba63a82a.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9167f772121beeadd5ae312cbccaa4e5.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1e5f28e1ee4baef62065289fbdb93cd6.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


不过本篇文章，我最想提的是我让Claude Code写的手工川think指令集，我自己超级深度使用（超50%的prompt），也在很多群里推广过（尽管尚未有空写一篇仔细的文章）。

但有很多人不解，我简单理了一下，大概有以下这几种问题：
1. 不明白为什么需要使用think模式（基于DS的教育，使用cc的群体里这类人基本上不存在）
2. 不明白为什么需要用指令去声明think模式（这类人目测很多，他们对“函数”是没有太大概念的）
3. 不明白为什么think模式需要分级（首先分级不是我分的，是Anthropic自己分的，其次我认同）
4. 不明白think模式之间的分级差异（我们这张图的差异显示就非常的细致）
5. ultra党：觉得既然ultrathink有用，那就无脑ultrathink好了（他们走向了另一个反面）
6. ……


### 1. think.md

```markdown
---
allowed-tools: [Read, Grep, Glob, LS, Task, WebFetch, WebSearch]
description: "Trigger extended thinking mode for deeper analysis and planning"
version: "1.0.0"
author: markshawn2020
created: "2025-07-14"
updated: "2025-07-14"
changelog:
  - version: "1.0.0"
    date: "2025-07-14"
    changes: ["Initial version - basic thinking mode activation"]
---

Please think about the following problem or question: $ARGUMENTS

Use extended thinking to:
- Analyze the problem from multiple angles
- Consider alternative approaches
- Evaluate potential solutions thoroughly
- Think through edge cases and implications
- Provide a well-reasoned response

Take your time to think through this systematically before responding.
```

### 2. think-hard.md

```markdown
---
allowed-tools: [Read, Grep, Glob, LS, Task, WebFetch, WebSearch]
description: "Trigger enhanced thinking mode for complex problem solving"
version: "1.0.0"
author: markshawn2020
created: "2025-07-14"
updated: "2025-07-14"
changelog:
  - version: "1.0.0"
    date: "2025-07-14"
    changes: ["Initial version - enhanced thinking mode activation"]
---

Please think hard about the following problem or question: $ARGUMENTS

Use enhanced thinking to:
- Deeply analyze the problem from multiple perspectives
- Systematically explore all possible approaches
- Rigorously evaluate each potential solution
- Consider complex interactions and dependencies
- Identify potential risks and mitigation strategies
- Think through implementation details and challenges
- Provide a comprehensive, well-reasoned response

Take additional time to think through this problem with increased depth and rigor.
```

### 3. think-harder.md

```markdown
---
allowed-tools: [Read, Grep, Glob, LS, Task, WebFetch, WebSearch]
description: "Trigger intensive thinking mode for highly complex analysis"
version: "1.0.0"
author: markshawn2020
created: "2025-07-14"
updated: "2025-07-14"
changelog:
  - version: "1.0.0"
    date: "2025-07-14"
    changes: ["Initial version - intensive thinking mode activation"]
---

Please think harder about the following problem or question: $ARGUMENTS

Use intensive thinking to:
- Conduct exhaustive analysis from all conceivable angles
- Systematically decompose the problem into sub-components
- Explore intricate relationships between different elements
- Perform detailed risk-benefit analysis for each approach
- Consider long-term implications and second-order effects
- Analyze potential failure modes and recovery strategies
- Evaluate alternative frameworks and methodologies
- Synthesize insights from multiple domains of knowledge
- Provide a thorough, nuanced, and comprehensive response

Apply maximum cognitive effort to thoroughly understand and address this complex problem.
```


### 4. think-ultra.md

```markdown
---
allowed-tools: [Read, Grep, Glob, LS, Task, WebFetch, WebSearch]
description: "Trigger maximum thinking mode for the most complex problems"
version: "1.0.0"
author: markshawn2020
created: "2025-07-14"
updated: "2025-07-14"
changelog:
  - version: "1.0.0"
    date: "2025-07-14"
    changes: ["Initial version - maximum thinking mode activation"]
---

Please ultrathink about the following problem or question: $ARGUMENTS

Use maximum thinking capacity to:
- Conduct comprehensive multi-dimensional analysis
- Explore every conceivable angle, perspective, and approach
- Perform deep philosophical and theoretical examination
- Consider historical precedents and future implications
- Analyze complex systemic interactions and emergent properties
- Evaluate meta-level considerations and paradigm shifts
- Synthesize insights across multiple disciplines and domains
- Consider ethical, social, and broader contextual implications
- Perform exhaustive scenario planning and contingency analysis
- Challenge fundamental assumptions and explore alternative frameworks
- Provide the most thorough, nuanced, and sophisticated response possible

Deploy maximum cognitive resources to provide the deepest possible analysis and most comprehensive solution.
```

### 怎么用

**需要深度思考的时候用上，有效预防降智！**

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ee258487ad906161a599efec3b8e1b85.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

社区伙伴反馈：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ac80513880d11e7ee7fde209acd73d75.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)




### Claude Code 有哪些境界



## Claude Code 还有哪些玩法

## Claude Code 对我有什么启示

		

