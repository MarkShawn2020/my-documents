---
date: 2025-08-26 
source: https://www.anthropic.com/engineering/claude-code-best-practices
original_publication: 2025-04-18 
author: 手工川编译
---


Anthropic 在今年4月发布了 Claude Code——一个专为智能体编程（agentic coding）设计的命令行工具。这篇来自 Anthropic 工程团队的实践总结，详细阐述了在各种代码库、编程语言和开发环境中使用 Claude Code 的有效方法和技巧。作为一个研究项目的产物，Claude Code 为工程师和研究人员提供了将 Claude 更原生地集成到编码工作流中的新途径。



- 原文：https://www.anthropic.com/engineering/claude-code-best-practices
- 编译：手工川

### Key Insights

- **设计理念**：Claude Code 采用低层级、无偏见的设计，提供近乎原始的模型访问，不强制特定工作流
- **灵活性优先**：工具设计强调灵活、可定制、可脚本化和安全，形成强大的生产力工具
- **学习曲线存在**：这种灵活性为初次接触智能体编程工具的工程师带来了学习曲线
- **实践驱动**：本文总结了 Anthropic 内部团队和外部工程师在实际使用中验证有效的模式
- **非教条主义**：所有建议都是起点而非定律，鼓励实验和个性化

<!-- 评注建议：此处可以对比分析 Claude Code 与 GitHub Copilot、Cursor 等其他 AI 编程工具的设计哲学差异，探讨"低层级无偏见"设计在实际开发中的利弊权衡 -->

## 自定义你的设置

Claude Code 作为智能体编程助手，会自动将上下文拉入提示词中。这种上下文收集会消耗时间和令牌（tokens），但你可以通过环境调优来优化它。

### a. 创建 `CLAUDE.md` 文件

`CLAUDE.md` 是一个特殊文件，Claude 在启动对话时会自动将其拉入上下文。这使它成为记录以下内容的理想场所：

- 常用 bash 命令
- 核心文件和实用函数
- 代码风格指南
- 测试说明
- 仓库礼仪（例如，分支命名、合并 vs 变基等）
- 开发者环境设置（例如，pyenv 使用、哪些编译器可用）
- 项目特有的任何意外行为或警告
- 其他你希望 Claude 记住的信息

`CLAUDE.md` 文件没有必需的格式要求。我们建议保持简洁和人类可读。例如：

```
# Bash commands
- npm run build: Build the project
- npm run typecheck: Run the typechecker

# Code style
- Use ES modules (import/export) syntax, not CommonJS (require)
- Destructure imports when possible (eg. import { foo } from 'bar')

# Workflow
- Be sure to typecheck when you're done making a series of code changes
- Prefer running single tests, and not the whole test suite, for performance
```

你可以在多个位置放置 `CLAUDE.md` 文件：

- **仓库根目录**，或你运行 `claude` 的任何位置（最常见的用法）。将其命名为 `CLAUDE.md` 并提交到 git，以便在会话间和团队成员间共享（推荐），或命名为 `CLAUDE.local.md` 并添加到 `.gitignore`
- **运行 `claude` 的目录的任何父级**。这对单体仓库最有用，你可能从 `root/foo` 运行 `claude`，并在 `root/CLAUDE.md` 和 `root/foo/CLAUDE.md` 都有 `CLAUDE.md` 文件。这两个文件都会自动被拉入上下文
- **运行 `claude` 的目录的任何子级**。这是上述的反向操作，在这种情况下，当你处理子目录中的文件时，Claude 会按需拉入 `CLAUDE.md` 文件
- **你的主目录**（`~/.claude/CLAUDE.md`），这会将其应用于你所有的 Claude 会话

当你运行 `/init` 命令时，Claude 会自动为你生成一个 `CLAUDE.md`。

<!-- 评注建议：这里可以分享一些实际项目中 CLAUDE.md 的最佳实践案例，比如不同技术栈（前端、后端、AI）的模板示例 -->

```ad-tip 

手工川注：

1. `/init` 不仅可以用于项目的初始化，也可以用于后续的 checkpoints，它会自动基于最近的项目改动，更新 CLAUDE.md
   
2. CLAUDE.md 和 README.md 两个文件的作用接近，但目标对象不同，一个是给AI看的，一个是给用户看的，我们后续会写一篇文章讲一讲这两个文件的最佳实践，敬请期待。
```

### b. 调优你的 `CLAUDE.md` 文件

你的 `CLAUDE.md` 文件会成为 Claude 提示词的一部分，因此它们应该像任何经常使用的提示词一样被精炼。一个常见的错误是添加大量内容而不迭代其有效性。花时间实验并确定什么能产生模型最好的指令遵循效果。

你可以手动向 `CLAUDE.md` 添加内容，或按 `#` 键给 Claude 一个指令，它会自动将其纳入相关的 `CLAUDE.md`。许多工程师在编码时频繁使用 `#` 来记录命令、文件和风格指南，然后在提交中包含 `CLAUDE.md` 的更改，以便团队成员也能受益。

在 Anthropic，我们偶尔会通过[提示词改进器](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/prompt-improver)运行 `CLAUDE.md` 文件，并经常调整指令（例如，用"IMPORTANT"或"YOU MUST"添加强调）以改善遵守程度。

![Claude Code 工具允许列表](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6961243cc6409e41ba93895faded4f4bc1772366-1600x1231.png&w=3840&q=75)

### c. 策划 Claude 的允许工具列表

默认情况下，Claude Code 会为任何可能修改你系统的操作请求权限：文件写入、许多 bash 命令、MCP 工具等。我们设计 Claude Code 时采用了这种故意保守的方法来优先考虑安全性。你可以自定义允许列表以允许你知道安全的额外工具，或允许容易撤销的潜在不安全工具（例如，文件编辑、`git commit`）。

有四种方式管理允许的工具：

- **在会话期间提示时选择"始终允许"**
- **启动 Claude Code 后使用 `/permissions` 命令**添加或删除允许列表中的工具。例如，你可以添加 `Edit` 以始终允许文件编辑，`Bash(git commit:*)` 以允许 git 提交，或 `mcp__puppeteer__puppeteer_navigate` 以允许使用 Puppeteer MCP 服务器进行导航
- **手动编辑**你的 `.claude/settings.json` 或 `~/.claude.json`（我们建议将前者提交到源代码控制以与团队共享）
- **使用 `--allowedTools` CLI 标志**进行特定会话的权限设置

### d. 如果使用 GitHub，安装 gh CLI

Claude 知道如何使用 `gh` CLI 与 GitHub 交互，用于创建问题、打开拉取请求、阅读评论等。如果没有安装 `gh`，Claude 仍然可以使用 GitHub API 或 MCP 服务器（如果你安装了的话）。

<!-- 评注建议：此处可以讨论权限管理的安全性考虑，以及在企业环境中的最佳实践配置 -->

```ad-tip

手工川注：gh 非常有用，可以脱离 GUI 直接操纵、维护我们的 Github 仓库，强烈建议配置，不过要注意 token 的权限。
```

## 给 Claude 更多工具

Claude 可以访问你的 shell 环境，你可以在其中为它构建便利脚本和函数集，就像你为自己做的一样。它还可以通过 MCP 和 REST API 利用更复杂的工具。

### a. 使用 Claude 与 bash 工具

Claude Code 继承你的 bash 环境，使其能够访问你所有的工具。虽然 Claude 知道常见的实用工具如 unix 工具和 `gh`，但如果没有说明，它不会知道你的自定义 bash 工具：

1. 告诉 Claude 工具名称和使用示例
2. 告诉 Claude 运行 `--help` 查看工具文档
3. 在 `CLAUDE.md` 中记录经常使用的工具

### b. 使用 Claude 与 MCP

```ad-tip

MCP 是 Anthropic 开发的模型上下文协议，允许 AI 模型与外部工具和服务进行标准化交互。通过 MCP，Claude 可以连接到数据库、API、开发工具等各种服务，实现更复杂的自动化任务。
```

Claude Code 既可以作为 MCP 服务器也可以作为客户端。作为客户端，它可以通过三种方式连接到任意数量的 MCP 服务器来访问它们的工具：

- **在项目配置中**（在该目录中运行 Claude Code 时可用）
- **在全局配置中**（在所有项目中可用）
- **在已提交的 `.mcp.json` 文件中**（对在你的代码库中工作的任何人可用）。例如，你可以将 Puppeteer 和 Sentry 服务器添加到你的 `.mcp.json`，这样在你的仓库上工作的每个工程师都可以开箱即用地使用这些工具

在使用 MCP 时，使用 `--mcp-debug` 标志启动 Claude 也有助于识别配置问题。

```ad-tip

手工川注：在吴恩达 Claude Code 教程里，官方推荐使用的两个 mcp 是 Playwright 和 Figma。
```

### c. 使用自定义斜杠命令

对于重复的工作流程——调试循环、日志分析等——将提示模板存储在 `.claude/commands` 文件夹内的 Markdown 文件中。当你输入 `/` 时，这些命令会通过斜杠命令菜单变得可用。你可以将这些命令提交到 git，使它们对团队的其他成员可用。

自定义斜杠命令可以包含特殊关键字 `$ARGUMENTS` 来从命令调用传递参数。

例如，这是一个你可以用来自动拉取和修复 GitHub 问题的斜杠命令：

```
Please analyze and fix the GitHub issue: $ARGUMENTS.

Follow these steps:

1. Use `gh issue view` to get the issue details
2. Understand the problem described in the issue
3. Search the codebase for relevant files
4. Implement the necessary changes to fix the issue
5. Write and run tests to verify the fix
6. Ensure code passes linting and type checking
7. Create a descriptive commit message
8. Push and create a PR

Remember to use the GitHub CLI (`gh`) for all GitHub-related tasks.
```

将上述内容放入 `.claude/commands/fix-github-issue.md` 使其在 Claude Code 中作为 `/project:fix-github-issue` 命令可用。然后你可以使用例如 `/project:fix-github-issue 1234` 让 Claude 修复问题 #1234。同样，你可以将你自己的个人命令添加到 `~/.claude/commands` 文件夹，用于你希望在所有会话中可用的命令。

```ad-tip

手工川注：手工川自研了元命令与深度思考命令集，并在日常开发中大量使用，也推荐给各位，具体留言领取或者阅读往期文章。
```

## 尝试常见工作流

Claude Code 不强制特定的工作流，给你使用它的灵活性。在这种灵活性所提供的空间内，我们的用户社区中出现了几种有效使用 Claude Code 的成功模式：

### a. 探索、规划、编码、提交

这个多功能的工作流适合许多问题：

1. **要求 Claude 读取相关文件、图片或 URL**，提供一般指针（"读取处理日志的文件"）或特定文件名（"读取 logging.py"），但明确告诉它暂时不要编写任何代码。
    
    - 这是工作流中你应该考虑大量使用子代理的部分，特别是对于复杂问题。告诉 Claude 使用子代理来验证细节或调查它可能有的特定问题，特别是在对话或任务的早期，往往能保留上下文可用性，而在效率损失方面没有太多缺点。
2. **要求 Claude 制定如何处理特定问题的计划**。我们建议使用"think"这个词来触发扩展思考模式，这给 Claude 额外的计算时间来更彻底地评估替代方案。这些特定短语直接映射到系统中不断增加的思考预算级别："think" < "think hard" < "think harder" < "ultrathink"。每个级别都为 Claude 分配逐步更多的思考预算来使用。
    
    - 如果这一步的结果看起来合理，你可以让 Claude 创建一个文档或 GitHub 问题，包含它的计划，这样如果实施（第3步）不是你想要的，你可以重置到这个点。
3. **要求 Claude 在代码中实施其解决方案**。这也是一个好地方，要求它在实施解决方案的各个部分时明确验证其解决方案的合理性。
    
4. **要求 Claude 提交结果并创建拉取请求**。如果相关，这也是让 Claude 更新任何 README 或更改日志的好时机，解释它刚刚做了什么。
    

第 1-2 步至关重要——没有它们，Claude 倾向于直接跳到编码解决方案。虽然有时这就是你想要的，但要求 Claude 首先研究和规划对于需要前期深入思考的问题显著提高了性能。

### b. 编写测试，提交；编码，迭代，提交

这是 Anthropic 最喜欢的工作流，用于可以通过单元、集成或端到端测试轻松验证的更改。测试驱动开发（TDD）在智能体编程中变得更加强大：

1. **要求 Claude 基于预期输入/输出对编写测试**。明确说明你正在进行测试驱动开发，以便它避免创建模拟实现，即使对于代码库中尚不存在的功能也是如此。
    
2. **告诉 Claude 运行测试并确认它们失败**。在这个阶段明确告诉它不要编写任何实现代码通常很有帮助。
    
3. **当你对测试满意时，要求 Claude 提交测试**。
    
4. **要求 Claude 编写通过测试的代码**，指示它不要修改测试。告诉 Claude 继续直到所有测试通过。Claude 编写代码、运行测试、调整代码并再次运行测试通常需要几次迭代。
    
    - 在这个阶段，要求它通过独立的子代理验证实现没有过度拟合测试可能会有所帮助
5. **一旦你对更改满意，要求 Claude 提交代码**。
    

Claude 在有明确的迭代目标时表现最好——视觉模型、测试用例或另一种输出。通过提供像测试这样的预期输出，Claude 可以进行更改、评估结果并逐步改进直到成功。

### c. 编写代码，截图结果，迭代

类似于测试工作流，你可以为 Claude 提供视觉目标：

1. **给 Claude 一种截取浏览器截图的方法**（例如，使用 [Puppeteer MCP 服务器](https://github.com/modelcontextprotocol/servers/tree/c19925b8f0f2815ad72b08d2368f0007c86eb8e6/src/puppeteer)、[iOS 模拟器 MCP 服务器](https://github.com/joshuayoes/ios-simulator-mcp)，或手动复制/粘贴截图到 Claude）。
    
2. **通过复制/粘贴或拖放图像给 Claude 一个视觉模型**，或给 Claude 图像文件路径。
    
3. **要求 Claude 在代码中实现设计**，截取结果截图，并迭代直到其结果与模型匹配。
    
4. **当你满意时要求 Claude 提交**。
    

像人类一样，Claude 的输出往往会通过迭代显著改善。虽然第一个版本可能很好，但经过 2-3 次迭代后，它通常会看起来好得多。给 Claude 工具来查看其输出以获得最佳结果。

<!-- 评注建议：可以在此处加入关于 TDD 在 AI 辅助开发中的新范式讨论，探讨测试如何成为 AI 编程的"护栏" -->

### d. 安全 YOLO 模式

![安全 YOLO 模式](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6ea59a36fe82c2b300bceaf3b880a4b4852c552d-1600x1143.png&w=3840&q=75)

你可以使用 `claude --dangerously-skip-permissions` 来绕过所有权限检查，让 Claude 不间断地工作直到完成，而不是监督 Claude。这对于修复 lint 错误或生成样板代码等工作流效果很好。

让 Claude 运行任意命令是有风险的，可能导致数据丢失、系统损坏，甚至数据泄露（例如，通过提示注入攻击）。为了最小化这些风险，在没有互联网访问的容器中使用 `--dangerously-skip-permissions`。你可以使用 Docker Dev Containers 遵循这个[参考实现](https://github.com/anthropics/claude-code/tree/main/.devcontainer)。

```ad-tip

手工川注：最近 share-ai 开源了 [kode](https://github.com/shareAI-lab/Kode) 反响不错，不过它的默认权限模式是反着的，需要使用 `kode --safe` 以关闭默认的 ` --dangerously-skip-permissions`。
```

### e. 代码库问答

当熟悉新代码库时，使用 Claude Code 进行学习和探索。你可以向 Claude 提出与向项目中另一位工程师提出的相同类型的问题，就像结对编程时一样。Claude 可以智能地搜索代码库来回答一般问题，例如：

- 日志记录是如何工作的？
- 我如何创建新的 API 端点？
- `foo.rs` 第 134 行的 `async move { ... }` 做什么？
- `CustomerOnboardingFlowImpl` 处理哪些边缘情况？
- 为什么我们在第 333 行调用 `foo()` 而不是 `bar()`？
- `baz.py` 第 334 行在 Java 中的等价物是什么？

在 Anthropic，以这种方式使用 Claude Code 已成为我们的核心入职工作流，显著改善了上手时间并减少了其他工程师的负担。不需要特殊的提示！只需提问，Claude 就会探索代码以找到答案。

### f. 使用 Claude 与 git 交互

![使用 Claude 与 git 交互](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fa08ea13c2359aac0eceacebf2e15f81e8e8ec8d2-1600x1278.png&w=3840&q=75)

Claude 可以有效地处理许多 git 操作。许多 Anthropic 工程师使用 Claude 进行 90% 以上的 git 交互：

- **搜索 git 历史**来回答诸如"哪些更改进入了 v1.2.3？"、"谁拥有这个特定功能？"或"为什么这个 API 是这样设计的？"等问题。明确提示 Claude 查看 git 历史来回答这类查询会很有帮助。
- **编写提交消息**。Claude 会自动查看你的更改和最近的历史，考虑所有相关上下文来撰写消息
- **处理复杂的 git 操作**，如还原文件、解决变基冲突以及比较和嫁接补丁

### g. 使用 Claude 与 GitHub 交互

Claude Code 可以管理许多 GitHub 交互：

- **创建拉取请求**：Claude 理解简写"pr"，并会基于差异和周围上下文生成适当的提交消息。
- **为简单的代码审查评论实施一次性解决方案**：只需告诉它修复你的 PR 上的评论（可选地，给它更具体的指令），并在完成后推送回 PR 分支。
- **修复失败的构建**或 linter 警告
- **通过要求 Claude 循环遍历开放的 GitHub 问题来分类和分级开放问题**

这消除了记住 `gh` 命令行语法的需要，同时自动化了例行任务。

### h. 使用 Claude 处理 Jupyter notebooks

Anthropic 的研究人员和数据科学家使用 Claude Code 来读取和编写 Jupyter notebooks。Claude 可以解释输出，包括图像，提供了一种探索和与数据交互的快速方法。没有必需的提示或工作流，但我们推荐的工作流是在 VS Code 中并排打开 Claude Code 和 `.ipynb` 文件。

你还可以要求 Claude 在向同事展示之前清理或美化你的 Jupyter notebook。明确告诉它使 notebook 或其数据可视化"美观悦目"往往有助于提醒它正在为人类观看体验进行优化。

<!-- 评注建议：此处可以讨论 AI 如何改变数据科学工作流，特别是在探索性数据分析和可视化方面的新可能性 -->

## 优化你的工作流

以下建议适用于所有工作流：

### a. 在指令中要具体

Claude Code 的成功率随着更具体的指令显著提高，特别是在第一次尝试时。预先给出清晰的指示减少了以后需要进行航向修正的需要。

例如：

|差|好|
|---|---|
|为 foo.py 添加测试|为 foo.py 编写一个新的测试用例，涵盖用户已注销的边缘情况。避免使用模拟|
|为什么 ExecutionFactory 有如此奇怪的 API？|查看 ExecutionFactory 的 git 历史并总结其 API 是如何形成的|
|添加日历小部件|查看主页上现有小部件的实现方式，了解模式，特别是代码和接口如何分离。HotDogWidget.php 是一个很好的开始示例。然后，遵循该模式实现一个新的日历小部件，让用户选择月份并分页前进/后退以选择年份。从头开始构建，除了代码库中已经使用的库之外不要使用其他库。|

Claude 可以推断意图，但它不能读心。具体性导致与期望更好地对齐。

### b. 给 Claude 图像

![给 Claude 图像](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F75e1b57a0b696e7aafeca1ed5fa6ba7c601a5953-1360x1126.png&w=3840&q=75)

Claude 通过几种方法擅长处理图像和图表：

- **粘贴截图**（专业提示：在 macOS 中按 cmd+ctrl+shift+4 截图到剪贴板，按 ctrl+v 粘贴。注意这不是你通常在 mac 上粘贴使用的 cmd+v，并且不能远程工作。）
- **直接拖放**图像到提示输入
- **提供图像的文件路径**

这在使用设计模型作为 UI 开发参考点时特别有用，以及用于分析和调试的视觉图表。如果你没有向上下文添加视觉效果，明确告诉 Claude 结果的视觉吸引力有多重要仍然会有帮助。

### c. 提及你希望 Claude 查看或处理的文件

![提及文件](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F7372868757dd17b6f2d3fef98d499d7991d89800-1450x1164.png&w=3840&q=75)

使用 tab 补全快速引用仓库中任何地方的文件或文件夹，帮助 Claude 找到或更新正确的资源。

### d. 给 Claude URL

![给 Claude URL](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fe071de707f209bbaa7f16b593cc7ed0739875dae-1306x1088.png&w=3840&q=75)

在你的提示旁边粘贴特定的 URL 供 Claude 获取和阅读。为了避免相同域名（例如，docs.foo.com）的权限提示，使用 `/permissions` 将域名添加到你的允许列表。

### e. 尽早并经常进行航向修正

虽然自动接受模式（shift+tab 切换）让 Claude 自主工作，但通过成为积极的合作者并指导 Claude 的方法，你通常会得到更好的结果。你可以通过在开始时向 Claude 彻底解释任务来获得最佳结果，但你也可以随时修正 Claude 的航向。

这四个工具有助于航向修正：

- **在编码前要求 Claude 制定计划**。明确告诉它在你确认其计划看起来不错之前不要编码。
- **按 Escape 在任何阶段中断** Claude（思考、工具调用、文件编辑），保留上下文，以便你可以重定向或扩展指令。
- **双击 Escape 跳回历史**，编辑以前的提示，并探索不同的方向。你可以编辑提示并重复，直到得到你要找的结果。
- **要求 Claude 撤销更改**，通常与选项 #2 结合使用以采取不同的方法。

虽然 Claude Code 偶尔会在第一次尝试时完美解决问题，但使用这些修正工具通常会更快地产生更好的解决方案。

### f. 使用 `/clear` 保持上下文聚焦

在长时间会话期间，Claude 的上下文窗口可能会被不相关的对话、文件内容和命令填满。这可能会降低性能，有时会分散 Claude 的注意力。在任务之间频繁使用 `/clear` 命令来重置上下文窗口。

### g. 为复杂工作流使用清单和草稿板

对于具有多个步骤或需要详尽解决方案的大型任务——如代码迁移、修复大量 lint 错误或运行复杂的构建脚本——通过让 Claude 使用 Markdown 文件（甚至 GitHub 问题！）作为清单和工作草稿板来提高性能：

例如，要修复大量 lint 问题，你可以执行以下操作：

1. **告诉 Claude 运行 lint 命令**并将所有结果错误（带文件名和行号）写入 Markdown 清单
2. **指示 Claude 逐个解决每个问题**，在检查并移动到下一个之前进行修复和验证

### h. 将数据传递给 Claude

存在几种向 Claude 提供数据的方法：

- **直接复制和粘贴**到你的提示中（最常见的方法）
- **管道传输到 Claude Code**（例如，`cat foo.txt | claude`），特别适用于日志、CSV 和大数据
- **告诉 Claude 通过 bash 命令、MCP 工具或自定义斜杠命令拉取数据**
- **要求 Claude 读取文件**或获取 URL（也适用于图像）

大多数会话涉及这些方法的组合。例如，你可以管道输入日志文件，然后告诉 Claude 使用工具拉入额外的上下文来调试日志。

<!-- 评注建议：此处可以探讨上下文管理的理论基础，以及如何在有限的上下文窗口内最大化 AI 的效能 -->

## 使用无头模式自动化你的基础设施

Claude Code 包括用于非交互式上下文的[无头模式](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#automate-ci-and-infra-workflows)，如 CI、预提交钩子、构建脚本和自动化。使用 `-p` 标志和提示来启用无头模式，以及 `--output-format stream-json` 用于流式 JSON 输出。

注意无头模式不会在会话之间持久化。你必须每个会话触发它。

### a. 使用 Claude 进行问题分类

无头模式可以支持由 GitHub 事件触发的自动化，例如当你的仓库中创建新问题时。例如，公共 [Claude Code 仓库](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-issue-triage-action/action.yml)使用 Claude 检查新进入的问题并分配适当的标签。

### b. 使用 Claude 作为 linter

Claude Code 可以提供超出传统 linting 工具检测范围的[主观代码审查](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-code-action/action.yml)，识别诸如拼写错误、过时评论、误导性函数或变量名等问题。

## 通过多 Claude 工作流提升水平

除了独立使用之外，一些最强大的应用涉及并行运行多个 Claude 实例：

### a. 让一个 Claude 编写代码；使用另一个 Claude 验证

一个简单但有效的方法是让一个 Claude 编写代码，而另一个审查或测试它。类似于与多个工程师合作，有时拥有单独的上下文是有益的：

1. 使用 Claude 编写代码
2. 运行 `/clear` 或在另一个终端启动第二个 Claude
3. 让第二个 Claude 审查第一个 Claude 的工作
4. 启动另一个 Claude（或再次 `/clear`）来读取代码和审查反馈
5. 让这个 Claude 基于反馈编辑代码

你可以对测试做类似的事情：让一个 Claude 编写测试，然后让另一个 Claude 编写代码使测试通过。你甚至可以通过给它们单独的工作草稿板并告诉它们哪个要写入和哪个要读取，让你的 Claude 实例相互通信。

这种分离通常比让单个 Claude 处理所有事情产生更好的结果。

### b. 拥有仓库的多个检出

与其等待 Claude 完成每个步骤，Anthropic 的许多工程师所做的是：

1. **在单独的文件夹中创建 3-4 个 git 检出**
2. **在单独的终端选项卡中打开每个文件夹**
3. **在每个文件夹中启动 Claude**，执行不同的任务
4. **循环检查**进度并批准/拒绝权限请求

### c. 使用 git worktrees

这种方法对于多个独立任务来说很出色，提供了多个检出的轻量级替代方案。Git worktrees 允许你从同一个仓库将多个分支检出到单独的目录中。每个 worktree 都有自己的工作目录和隔离的文件，同时共享相同的 Git 历史和 reflog。

使用 git worktrees 使你能够在项目的不同部分同时运行多个 Claude 会话，每个都专注于自己的独立任务。例如，你可能有一个 Claude 重构你的身份验证系统，而另一个构建一个完全不相关的数据可视化组件。由于任务不重叠，每个 Claude 都可以全速工作，无需等待另一个的更改或处理合并冲突：

1. **创建 worktrees**：`git worktree add ../project-feature-a feature-a`
2. **在每个 worktree 中启动 Claude**：`cd ../project-feature-a && claude`
3. **根据需要创建额外的 worktrees**（在新的终端选项卡中重复步骤 1-2）

一些提示：

- 使用一致的命名约定
- 每个 worktree 维护一个终端选项卡
- 如果你在 Mac 上使用 iTerm2，[设置通知](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#notification-setup)以便在 Claude 需要注意时收到提醒
- 为不同的 worktrees 使用单独的 IDE 窗口
- 完成后清理：`git worktree remove ../project-feature-a`

### d. 使用带有自定义工具的无头模式

`claude -p`（无头模式）将 Claude Code 程序化地集成到更大的工作流中，同时利用其内置工具和系统提示。使用无头模式有两种主要模式：

1. **扇出**处理大型迁移或分析（例如，分析数百个日志中的情绪或分析数千个 CSV）：
    
    1. 让 Claude 编写脚本生成任务列表。例如，生成需要从框架 A 迁移到框架 B 的 2k 文件列表。
    2. 循环遍历任务，为每个任务程序化地调用 Claude，给它一个任务和一组它可以使用的工具。例如：`claude -p "migrate foo.py from React to Vue. When you are done, you MUST return the string OK if you succeeded, or FAIL if the task failed." --allowedTools Edit Bash(git commit:*)`
    3. 多次运行脚本并改进你的提示以获得期望的结果。
2. **管道化**将 Claude 集成到现有的数据/处理管道中：
    
    1. 调用 `claude -p "<your prompt>" --json | your_command`，其中 `your_command` 是你处理管道的下一步
    2. 就是这样！JSON 输出（可选）可以帮助提供结构以便于自动化处理。

对于这两种用例，使用 `--verbose` 标志调试 Claude 调用可能会有帮助。我们通常建议在生产中关闭详细模式以获得更清洁的输出。

你在使用 Claude Code 时有什么技巧和最佳实践？标记 @AnthropicAI，让我们看看你在构建什么！

<!-- 评注建议：这里可以讨论多智能体协作的未来趋势，以及它对软件开发团队组织形式的潜在影响 -->

---


### 总结与展望

Claude Code 的发布标志着 AI 辅助编程进入了一个新阶段——从简单的代码补全和生成，演进到真正的智能体编程。通过其故意低层级和无偏见的设计，Claude Code 为开发者提供了前所未有的灵活性和控制力，同时保持了安全性和可预测性。

从技术演进的角度看，Claude Code 代表了几个重要趋势的交汇：

1. **工具生态的标准化**：MCP 协议的引入预示着 AI 工具集成的标准化时代，这将极大降低 AI 系统与外部工具交互的复杂性。
    
2. **上下文管理的精细化**：通过 CLAUDE.md 文件和各种上下文管理策略，我们看到了 AI 系统如何通过更好的上下文理解来提升效能。
    
3. **多智能体协作的实用化**：多个 Claude 实例的并行使用展示了多智能体系统在实际开发中的可行性，这可能预示着未来软件开发团队组织形式的根本变革。
    
4. **测试驱动的 AI 开发**：TDD 与智能体编程的结合创造了一种新的开发范式，其中测试不仅是质量保证工具，更是 AI 编程的"护栏"和迭代目标。
    

展望未来，随着模型能力的持续提升和工具生态的不断完善，智能体编程将从辅助工具逐步演变为开发流程的核心组成部分。开发者的角色也将从编写代码转向更高层次的系统设计、需求定义和质量把控。这不是人类程序员的替代，而是人机协作新纪元的开启。

<!-- 评注建议：文章结尾可以进一步探讨中国开发者如何利用这些工具和理念，结合本土化需求创造独特的开发实践 -->

### 鸣谢

作者 Boris Cherny。这项工作汲取了更广泛的 Claude Code 用户社区的最佳实践，他们的创造性方法和工作流程继续激励着我们。特别感谢 Daisy Hollman、Ashwin Bhat、Cat Wu、Sid Bidasaria、Cal Rueb、Nodir Turakulov、Barry Zhang、Drew Hodun 和许多其他 Anthropic 工程师，他们使用 Claude Code 的宝贵见解和实践经验帮助塑造了这些建议。
