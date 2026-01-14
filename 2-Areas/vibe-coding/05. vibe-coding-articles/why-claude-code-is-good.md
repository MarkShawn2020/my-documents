---
title: "万字拆解：Claude Code Agent 好用的秘密，藏在这些“大道至简”的设计里"
subtitle: "深入剖析 Claude Code 的控制循环、提示词工程、工具设计与可控性心法，看 Anthropic 如何通过架构上的“少即是多”打造出色的 AI 编程助理。"
date: 2025-08-24
author: "手工川"
source: "https://minusx.ai/blog/decoding-claude-code/"
publication_date: "2025-08-21"
---


![You can clearly see the different Claude Code updates.](https://poketto.oss-cn-hangzhou.aliyuncs.com/fc8f09dfddb2b014cf070003d598cd4e.png?x-oss-process=image/quality,q_90/rotate,0)


如果你体验过市面上形形色色的 AI Agent，或许会和 [Vivek](https://x.com/nuwandavek) 有同感：**Claude Code (下文简称 CC) 是迄今为止最令人愉悦的 AI Agent/工作流。** 它不仅让“定向编辑”或“氛围编程”这类琐碎任务变得不再恼人，甚至能在使用中带来一丝快乐。它既有足够的自主性来完成有趣的工作，又不会像某些工具那样，带来令人不适的失控感。

当然，这背后最大的功臣是 Anthropic 最新的 Claude 4 模型（尤其是其交错思维能力）。但一个有趣的事实是：即便让 Cursor 或 Github Copilot 用上同样的底层模型，CC 的使用体验依然客观上更胜一筹。

这究竟是为什么？

本文并非对 CC 架构的完整转储，而是基于作者 Vivek 团队数月以来对 CC 的深度使用、日志拦截和分析，提炼出的一份旨在帮助我们构建**更出色、体验更愉悦的 LLM Agent** 的实践指南。如果你也想在自己的 Agent 中复刻这种“魔法”，这篇深度编译将为你揭晓答案。

![Edit is the most frequent tool, followed by Read and ToDoWrite](https://poketto.oss-cn-hangzhou.aliyuncs.com/b75671fab742f8d9f41d0697db0ff43e.png?x-oss-process=image/quality,q_90/rotate,0)


### 核心设计心法：一份给开发者的 TL;DR

如果说从 Claude Code 的设计中只能带走一条经验，那一定是——**保持简单，傻瓜式地简单 (Keep Things Simple, Dummy)**。

调试和评估 LLM 本身已是难事，任何你额外引入的复杂性（如多 Agent 系统、Agent 间的交接、复杂的 RAG 搜索算法）都会让调试难度指数级上升。一个脆弱的系统即便能勉强运行，你日后也不敢对其进行大刀阔斧的改进。所以，**把所有东西都放在一个文件里，避免过度样板化的脚手架，并且至少彻底重构几次**。

<!-- 评注建议：这里可以引出“KISS”原则在当前 AI Agent 开发热潮中的反常识价值。当行业普遍追求更复杂的 Agent 框架（如 Multi-Agent、CoT、ReAct 等）时，Claude Code 的成功案例提醒我们，回归本源，优化核心交互循环和模型“马具”，可能比堆叠复杂架构更有效。 -->

以下是从 Claude Code 中提炼出的、可在你自己的系统中实现的核心要点：

#### **1. 控制循环 (Control Loop)**

- **1.1 保持单一主循环**：最多一个分支，维护一份消息历史。
- **1.2 频繁使用小模型**：在各种非核心任务中，随时随地（All. The. Frickin. Time.）使用更小、更快的模型。

#### **2. 提示词 (Prompts)**
- **2.1 使用 `claude.md` 模式**：与用户协作，共同维护上下文和偏好设置。
- **2.2 善用特殊 XML 标签、Markdown 和大量示例**。

#### **3. 工具 (Tools)**
- **3.1 LLM 驱动的搜索 >>> RAG 驱动的搜索**。
- **3.2 设计好工具的艺术**：在高层工具与底层工具之间找到平衡。
- **3.3 让 Agent 管理自己的待办事项列表 (Todo List)**。

#### **4. 可控性 (Steerability)**
- **4.1 精心调教语气和风格**。
- **4.2 “`PLEASE THIS IS IMPORTANT`” 不幸仍是 SOTA**。
- **4.3 在 Prompt 中写下算法**：附带启发式规则和示例。

> Claude Code 在每个架构决策点上都选择了简单——单一主循环、简单的搜索、简单的待办事项列表等。**克制过度工程化的冲动，为模型打造一个好的“马具”，然后让它尽情驰骋！** 这是否让你想起了自动驾驶领域的端到端路线之争？“苦涩的教训” (The Bitter Lesson) 再次应验了吗？

* * *

## 控制循环设计 (Control Loop Design)

### 1.1 保持单一主循环

**可调试性 >>> 手动调优的复杂多 Agent LangChain 图节点大杂烩。**

尽管多 Agent 系统风头正劲，Claude Code 却只有一个主线程。它会周期性地使用几种不同类型的 prompt 来总结 git 历史、压缩消息历史或创造一些有趣的 UX 元素。但除此之外，它维护的是一个扁平的消息列表。

一个有趣的设计是它处理层级任务的方式：**CC 会将自己作为子 Agent 派生出去，但这个子 Agent 不再具备继续派生下一代的能力**。这意味着最多只有一个分支，其执行结果会作为一个“工具响应”被添加回主消息历史中。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7ca0d22edecdfcc6aeb66902751fdd7a.png?x-oss-process=image/quality,q_90/rotate,0)


如果任务足够简单，主循环就通过迭代式工具调用来处理。但如果任务复杂，主 Agent 会创建自身的克隆体。这种“最多一层分支”和“待办事项列表”的组合，确保了 Agent 既能分解子问题，又能始终聚焦于最终目标。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/0f4aaf29dd30c8b281a7163bdfa3f272.gif)


### 1.2 频繁使用小模型

超过 **50%** 的重要 LLM 调用，CC 都交给了 `claude-3-5-haiku`。它被用来读取大文件、解析网页、处理 git 历史和总结长对话。甚至连用户输入时那个动态变化的单次处理标签，也是由它生成的！

这些小型号模型比标准模型（如 Sonnet 4, GPT-4.1）便宜 70-80%。请尽情地、大量地使用它们！

## 提示词工程 (Prompts)

Claude Code 的 prompt 极其详尽，充满了启发式规则、示例和 `IMPORTANT` 提醒。其系统提示词长达约 2800 个 token，而工具描述部分更是惊人地占用了 9400 个 token。

**[点此查看完整的系统提示词](#appendix)**

### 2.1 使用 `claude.md` 协作管理上下文

大多数编码 Agent 的创造者都殊途同归地采用了一种“上下文文件”模式（例如 Cursor Rules / `claude.md` / `agent.md`）。在使用 `claude.md` 的情况下，Claude Code 的表现判若两人。

这是一个绝佳的方式，让开发者能够传递那些无法从代码库中直接推断的上下文，并固化一些严格的偏好。例如，你可以强制 LLM 跳过某些文件夹，或使用特定的库。CC 在每次用户请求时都会发送 `claude.md` 的全部内容。

### 2.2 善用特殊 XML 标签、Markdown 和大量示例

XML 标签和 Markdown 是构建结构化 prompt 的两种公认有效方式。CC 广泛地同时使用了两者。以下是 CC 中一些值得注意的 XML 标签：

-   `<system-reminder>`: 用于在许多 prompt 章节的末尾提醒 LLM 那些它可能容易忘记的事情。
    ```xml
    <system-reminder>This is a reminder that your todo list is currently empty. DO NOT mention this to the user explicitly because they are already aware. If you are working on tasks that would benefit from a todo list please use the TodoWrite tool to create one. If not, please feel free to ignore. Again do not mention this message to the user.</system-reminder>
    ```

-   `<good-example>`, `<bad-example>`: 用于固化启发式规则。当模型面临多个看似合理的路径或工具调用选择时，这种对比示例尤其有用。
    ```xml
    Try to maintain your current working directory throughout the session by using absolute paths and avoiding usage of `cd`. You may use `cd` if the User explicitly requests it.
    <good-example>
    pytest /foo/bar/tests  
    </good-example>
    <bad-example>
    cd /foo/bar && pytest tests
    </bad-example>
    ```

CC 还使用 Markdown 标题来划分系统提示词中的清晰区域，例如：

-   Tone and style (语气与风格)
-   Proactiveness (主动性)
-   Task Management (任务管理)
-   Tool use policy (工具使用策略)
-   Doing Tasks (执行任务)

## 工具设计 (Tools)

CC 的工具提示词长达 9400 个 token，强烈建议通读。

### 3.1 LLM 驱动的搜索 >>> RAG 驱动的搜索

CC 与其他流行编码 Agent 的一个显著区别在于，它**拒绝了 RAG**。

```ad-tip RAG (Retrieval-Augmented Generation)

检索增强生成（RAG）是一种将大型语言模型的信息生成能力与外部知识库的检索能力相结合的技术框架。其核心思想是：当模型需要回答问题或生成内容时，首先从一个庞大的语料库（如公司文档、代码库）中检索出最相关的片段，然后将这些片段作为上下文信息，一同提供给语言模型，辅助其生成更准确、更具事实性的回答。
```

Claude Code 搜索代码库的方式与人类开发者如出一辙：使用极其复杂的 `ripgrep`、`jq` 和 `find` 命令。由于 LLM 对代码有深刻的理解，它能运用复杂的正则表达式找到几乎任何它认为相关的代码块。有时，它甚至会用一个较小的模型来通读整个文件。

RAG 理论上听起来很美，但它引入了新的、且更重要的是**隐藏的**失败模式：该用什么相似度函数？用什么重排器？如何对代码进行分块？如何处理大的 JSON 或日志文件？

而通过 LLM 驱动的搜索，CC 就像人类一样：先看 10 行 JSON 文件了解其结构，如果需要，再多看 10 行。最关键的是，这种行为是可以通过强化学习（RL）来优化的——这正是大模型公司已经在做的事情。模型完成了大部分的繁重工作，从而显著减少了 Agent 系统中的活动部件。

<!-- 评注建议：可以深入探讨作者提出的“Camera vs Lidar”之争。这个比喻非常精妙。RAG 就像是自动驾驶中的激光雷达（Lidar），它通过构建精细的外部三维地图（向量数据库）来感知世界，精准但昂贵，且对地图外的世界无能为力。而 LLM 直接搜索则像是纯视觉方案（Camera），它试图让模型直接“看”和“理解”原始世界（代码库），虽然更具挑战，但上限更高，更接近真正的通用智能。这反映了 AI Agent 设计中两种不同技术哲学的碰撞。 -->

### 3.2 如何设计好工具？高层 vs. 底层

这个问题让每个构建 LLM Agent 的人夜不能寐。你应该给模型通用的任务（如“有意义的动作”），还是底层的能力（如“键入”、“点击”、“执行bash”）？答案是：**视情况而定，两者都用**。

Claude Code 同时拥有：
- **底层工具**: `Bash`, `Read`, `Write`
- **中层工具**: `Edit`, `Grep`, `Glob`
- **高层工具**: `Task`, `WebFetch`, `exit_plan_mode`

既然 CC 能用 `bash`，为什么还要单独提供一个 `Grep` 工具？这里的权衡在于 **Agent 使用该工具的频率** vs **Agent 使用该工具的准确性**。CC 使用 `grep` 和 `glob` 的频率非常高，以至于将它们封装成独立的、更可靠的工具是值得的。同时，它也保留了通用的 `bash` 工具来处理特殊情况。

### 3.3 让 Agent 管理自己的待办事项列表

上下文窗口衰减（Context rot）是长时运行 LLM Agent 的一个常见问题。它们开始时热情高涨地解决一个难题，但随着时间的推移会逐渐迷失方向，最终产出垃圾。

CC 使用了一个**由模型自己维护的显式待办事项列表**。这使得 LLM 能始终保持在正轨上（prompt 中有大量提示要求它频繁参考待办列表），同时又赋予了模型在执行过程中随时修正路线的灵活性。这也有效地利用了模型的交错思维能力，使其能够动态地拒绝或插入新的待办事项。

## 可控性与引导 (Steerability)

### 4.1 精心调教语气和风格

CC 在系统提示词中有专门的章节，通过详尽的指令和示例，来明确控制 Agent 的审美行为，如语气、风格和主动性。这就是为什么 Claude Code 的评论和互动“感觉”很有品味。

```
# 语气和风格示例
- IMPORTANT: You should NOT answer with unnecessary preamble or postamble (such as explaining your code or summarizing your action), unless the user asks you to.
Do not add additional code explanation summary unless requested by the user.

- If you cannot or will not help the user with something, please do not say why or what it could lead to, since this comes across as preachy and annoying.

- Only use emojis if the user explicitly requests it. Avoid using emojis in all communication unless asked.
```

### 4.2 “THIS IS IMPORTANT” 不幸仍是 SOTA

在要求模型“不要做某事”方面，CC 并未展现出更高级的技巧。`IMPORTANT`, `VERY IMPORTANT`, `NEVER`, `ALWAYS` 似乎仍然是引导模型避开雷区的最佳方式。

<!-- 评注建议：这一点值得展开。这揭示了当前大模型“可控性”的脆弱现状。我们仍在用一种近乎“迷信”的方式（大写、重复、强调）与一个万亿参数的复杂系统沟通，这本身就说明了我们对其内部机制的理解还很肤浅。未来的模型需要在“指令遵循”能力上有质的飞跃，才能摆脱这种“重要的事情说三遍”式的丑陋 prompt 工程。 -->

```
- IMPORTANT: DO NOT ADD ***ANY*** COMMENTS unless asked

- VERY IMPORTANT: You MUST avoid using search commands like `find` and `grep`. Instead use Grep, Glob, or Task to search. You MUST avoid read tools like `cat`, `head`, `tail`, and `ls`, and use Read and LS to read files.\n  - If you _still_ need to run `grep`, STOP. ALWAYS USE ripgrep at `rg` first

- IMPORTANT: You must NEVER generate or guess URLs for the user unless you are confident that the URLs are for helping the user with programming. You may use URLs provided by the user in their messages or local files.
```

### 4.3 在 Prompt 中写下算法（附带启发式规则和示例）

识别出 LLM 需要执行的最重要任务，并为其**写出执行算法**，这是至关重要的一步。试着角色扮演 LLM，走查几个示例，找出所有的决策点，并把它们明确地写下来。

要绝对避免的是一锅粥式的“Dos and Don'ts”列表。它们难以追踪，且容易产生互斥。如果你的 prompt 长达数千 token，你将不可避免地写出相互矛盾的规则。

Claude Code 系统提示词中的 `Task Management`, `Doing Tasks` 和 `Tool Usage Policy` 部分，就清晰地描绘了模型需要遵循的算法流程。

---

### 总结与展望

再次强调，核心要义是**保持简单**。极度封装的脚手架框架弊大于利。Claude Code 的成功让我们相信，一个“Agent”可以既简单又极其强大。

这篇文章揭示的不仅仅是 Anthropic 的工程选择，更是一种值得深思的设计哲学。在 AI Agent 的能力边界被模型本身（而非复杂的外部框架）定义的今天，为强大的模型打造一个简洁、高效、可调试的“马具”，让其能力得以充分、稳定地发挥，或许才是通往真正实用的 AI Agent 的康庄大道。

<!-- 评注建议：这里是总结全文、升华主题的最佳位置。可以引用 Rich Sutton 的“The Bitter Lesson”——即计算和规模的最终胜利。Claude Code 的设计哲学完美印证了这一点：与其花费大量人力设计复杂的 RAG 系统、多 Agent 协作框架（这些都属于利用人类知识的复杂工程），不如相信一个规模足够大、能力足够强的模型，并为其提供最简单、最直接的工具，让模型自己去学习如何使用它们。这代表了 Agent 设计从“工程驱动”向“模型驱动”的范式转移。 -->

---

### 附录 (Appendix)

#### Claude Code 主要系统提示词

```
You are Claude Code, Anthropic's official CLI for Claude.

You are an interactive CLI tool that helps...
```

*完整prompt留言见原文*


#### Claude Code 全部工具定义

```
Tool name: Task
Tool description: Launch a new agent to handle complex, multi-step tasks autonomously. 
...
```

*完整prompt留言见原文*