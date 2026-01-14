---
title: "像水一样编程：我的 Vibe Coding 进化史与实战心法"
subtitle: "蚂蚁集团战投部蚂上创业营分享实录"
date: 2024-11-27
author: "手工川"
tags: ["Vibe Coding", "AI编程", "Claude Code", "Context Management", "Prompt Engineering"]
config:
  layout: dagre
  theme: base
  look: handDrawn
---

11月27日，在蚂蚁集团战投部“蚂上创业营”的分享中，我复盘了个人 Vibe Coding 的成长史与一些心得。

我的核心观点很简单：**Vibe Coding Like Water**。在 AI 时代，编程不再是搬砖，而应像水一样流动。

![手工川分享《Vibe Coding Essential》](http://cdn.cs-magic.cn/picgo/24796a3e90836ad3d956d688a94dabbb.jpg)


以下是我分享的笔记回顾。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.001.jpeg)

## 个人背景：从开源到创业

我个人比较喜欢的几个 Tag，也代表了我技术生涯的不同侧面：

*   **Github 开源贡献者**：不仅是代码的堆砌，更是与全球开发者对话的方式。
    ![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.002.jpeg)

*   **骨灰级 Vibe Coder**：作为 CCM 作者，我致力于探索人机协作的极限。
    ![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.003.jpeg)

*   **Lovpen Founder**：将技术理念转化为产品落地。
    ![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.004.jpeg)

## Claude Code 彻底重塑了我

如果非要给我的编程生涯划一条分界线，那一定是 **Claude Code** 的出现。我把自己的编程之旅分成 **BC (Before Claude Code)** 和 **AC (After Claude Code)** 两个阶段。

目前，我正处于 **1 AC**。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.005.jpeg)

在这个阶段，我经历了从“抗拒”到“臣服”再到“驾驭”的过程。Ego（自我）的消失，往往是进化的开始。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.006.jpeg)

<!-- 评注建议：此处可以简短补充一句关于“放弃旧经验”的痛感与快感，强化个人IP的真实性。 -->

## System Prompt：压缩即智能

在 Vibe Coding 体系中，System Prompt（系统提示词）不是越长越好。**少写代码、写好代码、写对代码**，是我对 AI 的核心约束。

### 核心提示词策略

我要求 AI 扮演 Linus Torvalds，并强制植入软件工程的黄金法则。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.007.jpeg)

> You are Linus Torvalds, KISS, YAGNI, DRY & SOLID, and use ask-question tool if you are not clear...
>
> *完整prompt见：https://thepromptbase.com/p/linus-torvalds-system-prompt*

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.008.jpeg)

```ad-tip SOLID 原则与极简主义

在 AI 编程中，严格的工程原则比以往更重要：
*   **KISS (Keep It Simple, Stupid)**：保持愚蠢式的简单，防止 AI 过度设计。
*   **YAGNI (You Ain't Gonna Need It)**：不要去写那些“未来可能用到”的功能，只专注当下。
*   **DRY (Don't Repeat Yourself)**：AI 容易像拉肚子一样生成大量重复代码，必须显式禁止。
*   **SOLID**：面向对象设计的五大原则（单一职责、开闭原则等），这是保证代码质量的基石。
```

### 个人化强约束 (Personal Principles)

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.009.jpeg)

为了防止 AI“自作聪明”，我制定了更具体的“三不原则”：
1.  **如无必要，禁止自动写文档**。
2.  **如无必要，禁止自动写测试**。
3.  **如无必要，禁止自动启动开发服务器**（本地环境往往已就绪）。
4.  **技术栈锁定**：CSS 优先使用 Tailwind。

**为什么是 Tailwind？**
在 Q&A 环节我提到，GPT-5 发布时的演示代码全是紫色的，因为它们大量训练了 Tailwind 的代码库。Tailwind 的原子化 CSS 类名（Utility-first）不仅实现了高内聚，而且让 HTML 文件包含了结构与样式，Context 密度极高。这种“所见即所得”的代码形态，天然契合 AI 的理解模式。

## 上下文管理的艺术 (The Art of Context Management)

这是 Vibe Coding 的核心心法。模型能力是常量，**上下文（Context）质量是唯一的变量**。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.010.jpeg)

### 优先级金字塔

我总结了一套 **AVAP** 上下文管理法则。为了更清晰地展示这一逻辑，我将其整理为下方的决策树：

```mermaid
graph TD
    n1["AVAP: As Vibe As Possible (最高纲领)"]
    n2["ACAP: As Clear As Possible"]
    n3["ASAP: As Short As Possible"]
    n4["AAAP: As Auto As Possible"]
    n5["ATAP: As Tool As Possible"]
    
    n1 --> n2
    n2 --> n3
    n3 --> n4
    n4 --> n5
    
    style n1 fill:#f9f,stroke:#333,stroke-width:2px
    style n4 fill:#bbf,stroke:#333,stroke-dasharray: 5 5
```

1.  **AVAP (As Vibe As Possible)**：一切为了保持“心流”。像打游戏一样，开一个 Feature，切一个 Branch，再开一个 CC 窗口，行云流水。
2.  **ACAP (As Clear As Possible)**：清晰度优先。明确告知 AI：你的现状、遇到的问题、已尝试的方案、期望的解决路径。
3.  **ASAP (As Short As Possible)**：在清晰的前提下，极致压缩上下文。Context Window 是昂贵的资源。
4.  **AAAP (As Auto As Possible)**：自动化是最后的选项。只有当置信度极高时（如 Git Commit, 简单的 Bug Fix），才允许全自动。

### 核心策略：SGB (Self-Generated is Better)

最好的上下文往往不是你“喂”给 AI 的，而是引导 AI 自己生成的。

*   **Revert >> Rectify**：如果 AI 跑偏了，**回滚 (Revert)** 永远优于在错误基础上修正 (Rectify)。一旦发现苗头不对，立刻 `/undo` 或回滚 Git，保持上下文纯净。
*   **Slash Commands (/)**：使用 `/init`, `/fix` 等指令比自然语言更高效。
*   **Thinking Control**：手动控制 AI 的思考深度。对于简单问题，不要让它过度思考；对于复杂架构，强制它开启 `thinking` 模式。

### 实战指令流

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.011.jpeg)

在我的日常开发中，这套组合拳是标配：

1.  `/init`：启动项目时的标准化初始化。
2.  **Code-Inspector**：源码分析优先。相比于截图（Image Recognition），直接读取 Source Code 的准确率更高。
3.  `/fix-until-no-error`：允许 AI 在受控环境下进行迭代式修复 (AAAP)。
4.  `/git-commit`：**原子化提交**。每一个微小的功能点完成后立即 Commit，这是保持 Context 清爽的关键。

## 模型协同：打造你的“军火库”

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.012.jpeg)

没有万能的模型，只有最适合的配置。我的协同策略如下：

### Coding 场景
*   **CC (Claude Code/Claude)**: **主力军 (90%)**。
    *   *特点*：极其犀利，有时过度自信 (Over-confident)。它常说 "You Are Absolutely Right"，但给出的代码往往是一针见血的。
*   **Codex**: **特种兵 (9%)**。
    *   *特点*：严肃、谨慎。当 CC 搞不定复杂的算法逻辑时，我会切换到 Codex。
*   **Gemini**: **冷板凳 (0%)**。目前仍在 TODO 列表中。
*   **Human (我)**: **最后防线 (1%)**。处理极端复杂的架构决策。

### Writing 场景
*   **Gemini**: **逻辑担当 (70%)**。理性、客观，适合撰写技术文档和逻辑推演。
*   **Claude**: **风格担当 (20%)**。更具“人味” (Human-friendly)。
*   **ChatGPT**: **瓶颈 (9%)**。
*   **Human**: **最后一公里 (1%)**。画龙点睛。

## 总结：Design is how you win

Vibe Coding 的终极目标不是为了写出更多代码，而是为了**不写代码**，去直接控制数据的流动。

正如 Figma CEO Dylan Field 所言：**"Design is how you win or lose."** 在 AI 能够秒生成代码的时代，**设计能力**（架构设计、交互设计、流程设计）成为了新的决胜点。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.013.jpeg)

我们要时刻警惕 **达克效应 (Dunning-Kruger Effect)**。AI 的强大容易让人产生全知全能的错觉，但只有保持敬畏，意识到 "You Don't Know What You Don't Know"，才能真正驾驭这股力量。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.014.jpeg)

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.015.jpeg)

最后，借用李小龙的名言作为 Vibe Coding 的注脚：

> **"Vibe Coding Like Water: Don't code blocks, direct the flow."**
>
> 别被代码块困住，去引导那股流动的力量。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.016.jpeg)

<!-- 评注建议：结尾处可以加一句slogan性质的总结，升华主题。 -->

欢迎大家持续关注我们对 AI 技术创业的实战经验与硬核思考。

![](http://cdn.cs-magic.cn/picgo/%E6%89%8B%E5%B7%A5%E5%B7%9D%20-%20Vibe%20Coding%20Essential.017.jpeg)

![活动合照](http://cdn.cs-magic.cn/picgo/ef71fb5a62129a2c04e4e9e384db79ec.jpg)
