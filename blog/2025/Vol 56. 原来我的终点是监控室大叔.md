

今天早上写了一套 think 提示词，我非常非常喜欢，社区的朋友立即也用了，验证确实有效。

但我说实话，已经没有太多想科普的心情。

因为市场上的认知太割裂太参差不齐了。

很多人连怎么用上 cc 都不知道，他们也没有渠道购买到好的方案，从梯子到海外信用卡到厂商到渠道商到自己手上的电脑、命令行……

已经卡死了90%的人。

我犹记得两年前去Top2一所大学和计算机系朋友交流，他还在用共享的ChatGPT账号，时不时被中断。

那种感觉，真地有一种。

anyway，不太说的上来。

好了，先不扯这个。

先分享一下prompt，干货要紧。

一共四个。

老规矩，复制粘贴到 `~/.claude/commands/` 文件夹下就好，都是用于全局的。

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

## 怎么用

**需要深度思考的时候用上，有效预防降智！**

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ee258487ad906161a599efec3b8e1b85.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

社区伙伴反馈：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ac80513880d11e7ee7fde209acd73d75.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 最后

三个AI给我肝活三个项目，我成监控室大叔了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/4dc7448be3ce970022c3f3b5740029c0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)