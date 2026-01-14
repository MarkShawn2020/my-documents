---
date: 2025-08-26 
source: https://www.anthropic.com/engineering/claude-code-best-practices
original_publication: 2025-04-18 
author: 手工川编译
---

今年 4 月，Anthropic 正式发布了 **Claude Code** —— 一个专为代理式编程（agentic coding）设计的命令行工具。

作为 Anthropic 内部研究项目的成果，Claude Code 为工程师和研究人员提供了一种更原生的方式，将 Claude 集成到日常编程工作流中。

这篇来自 [Anthropic 工程团队的技术文档](https://www.anthropic.com/engineering/claude-code-best-practices) 推荐给对大家，它系统总结了内外部工程师在各种代码库、编程语言和开发环境中使用 Claude Code 的有效模式。



<!-- 评注建议：这里可以评论 Claude Code 发布时机的战略意义，以及它与 Cursor、GitHub Copilot 等工具的差异化定位 -->


- 编译：手工川

### key insights

- **设计理念**：Claude Code 采用了"刻意低级、不强加观点"的设计哲学，提供接近原始模型的访问能力，不强制特定工作流
- **六大实践领域**：自定义设置、工具扩展、工作流模式、性能优化、自动化部署、多实例协作
- **关键创新**：`CLAUDE.md` 配置系统、MCP 集成、无头模式、多 Claude 实例并行工作流
- **实战价值**：Anthropic 内部工程师已将其作为核心代码审查、新人入职培训和 Git 交互的主要工具




---

我们最近[发布了 Claude Code](https://www.anthropic.com/news/claude-3-7-sonnet)，这是一款专为 Agentic Coding 设计的命令行工具。作为一个研究项目，Claude Code 为 Anthropic 的工程师和研究人员提供了一种更原生的方式，将 Claude 集成到他们的编码工作流中。

Claude Code 故意设计得底层且无固定模式（low-level and unopinionated），提供近乎原始的模型访问能力，而不强迫用户遵循特定的工作流。这种设计哲学创造了一个灵活、可定制、可脚本化且安全的强大工具。然而，尽管功能强大，这种灵活性对于刚接触 Agentic Coding 工具的工程师来说存在一个学习曲线——至少在他们形成自己的最佳实践之前是这样。

本文概述了已被证明行之有效的通用模式，这些模式不仅适用于 Anthropic 的内部团队，也适用于在各种代码库、语言和环境中使用的外部工程师。列表中的任何内容都不是一成不变或普遍适用的；请将这些建议视为起点。我们鼓励你进行实验，找到最适合自己的方法！

*想了解更详细的信息？我们位于 [claude.ai/code](https://claude.ai/redirect/website.v1.4691dd80-a6f1-4a83-9607-1b9d8abebf13/code) 的综合文档涵盖了本文提到的所有功能，并提供了额外的示例、实现细节和高级技术。*

```ad-tip Agentic Coding (智能体编码)

Agentic Coding 是一种编程范式，其中开发者与一个或多个自主的 AI 智能体（Agent）协作完成软件开发任务。这些智能体能够理解高级指令，自主规划步骤、编写代码、执行命令、调试错误并与外部工具（如版本控制、API）交互。与传统的 Copilot 式代码补全不同，Agentic Coding 强调的是 AI 在整个工作流中的自主性和端到端的问题解决能力。
```

## 自定义你的设置

Claude Code 是一个 Agentic Coding 助手，它会自动将上下文拉取到提示中。这个上下文收集过程会消耗时间和 token，但你可以通过环境调优来优化它。

### a. 创建 `CLAUDE.md` 文件

`CLAUDE.md` 是一个特殊文件，Claude 在开始对话时会自动将其内容拉入上下文。这使得它成为记录以下内容的理想场所：

-   常用的 bash 命令
-   核心文件和工具函数
-   代码风格指南
-   测试说明
-   代码仓库的规范（例如，分支命名、merge vs. rebase 等）
-   开发者环境设置（例如，pyenv 的使用，哪些编译器可用）
-   项目中特有的任何意外行为或警告
-   任何你希望 Claude 记住的其他信息

`CLAUDE.md` 文件没有固定的格式要求。我们建议保持其简洁和人类可读。例如：

```
# Bash commands
- npm run build: Build the project
- npm run typecheck: Run the typechecker

# Code style
- Use ES modules (import/export) syntax, not CommonJS (require)
- Destructure imports when possible (eg. import { foo } from 'bar')

# Workflow
- Be sure to typecheck when you’re done making a series of code changes
- Prefer running single tests, and not the whole test suite, for performance
```

<!-- 评注建议：`CLAUDE.md` 的设计哲学值得深思。它本质上是为 AI Agent 定义了一个项目级的“系统提示”或“操作手册”。这是一种新颖的人机协作“契约”，将原本存在于开发者大脑中的隐性知识（项目规范、常用命令）显性化、结构化，从而极大地提升了 AI Agent 的工作效率和准确性。这可能预示着未来项目文档的一种新形态。 -->

你可以将 `CLAUDE.md` 文件放置在几个位置：

-   **仓库根目录**，或者你运行 `claude` 的任何地方（最常见的用法）。将其命名为 `CLAUDE.md` 并提交到 git，以便在不同会话和团队成员之间共享（推荐），或者命名为 `CLAUDE.local.md` 并将其加入 `.gitignore`。
-   **运行 `claude` 目录的任何父目录**。这对于 monorepo 最为有用，你可能在 `root/foo` 中运行 `claude`，而在 `root/CLAUDE.md` 和 `root/foo/CLAUDE.md` 中都有 `CLAUDE.md` 文件。这两者都会被自动拉入上下文。
-   **运行 `claude` 目录的任何子目录**。这与上述情况相反，在这种情况下，当你处理子目录中的文件时，Claude 会按需拉取 `CLAUDE.md` 文件。
-   **你的 home 目录** (`~/.claude/CLAUDE.md`)，它将应用于你所有的 *claude* 会话。

当你运行 `/init` 命令时，Claude 会自动为你生成一个 `CLAUDE.md`。

### b. 调优你的 `CLAUDE.md` 文件

你的 `CLAUDE.md` 文件会成为 Claude 提示的一部分，因此应该像任何频繁使用的提示一样进行优化。一个常见的错误是添加大量内容而没有迭代其有效性。花时间进行实验，确定什么能从模型中产生最佳的指令遵循效果。

你可以手动向 `CLAUDE.md` 添加内容，或者按 `#` 键给 Claude 一个指令，它会自动将其合并到相关的 `CLAUDE.md` 中。许多工程师在编码时频繁使用 `#` 来记录命令、文件和风格指南，然后在提交中包含 `CLAUDE.md` 的更改，以便团队成员也能受益。

在 Anthropic，我们偶尔会用 [prompt improver](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/prompt-improver) 来优化 `CLAUDE.md` 文件，并经常调整指令（例如，用 "IMPORTANT" 或 "YOU MUST" 来强调）以提高遵循度。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6961243cc6409e41ba93895faded4f4bc1772366-1600x1231.png&w=3840&q=75)



### c. 管理 Claude 的工具白名单

默认情况下，Claude Code 对任何可能修改你系统的操作都会请求许可：文件写入、许多 bash 命令、MCP 工具等。我们设计 Claude Code 时采用了这种刻意保守的方法，以优先考虑安全性。你可以自定义白名单，以允许你知道是安全的其他工具，或者允许那些易于撤销的潜在不安全工具（例如，文件编辑、`git commit`）。

有四种方式来管理允许的工具：

-   在会话中被提示时**选择 "Always allow"**。
-   启动 Claude Code 后**使用 `/permissions` 命令**来添加或移除工具白名单。例如，你可以添加 `Edit` 来始终允许文件编辑，`Bash(git commit:*)` 来允许 git 提交，或者 `mcp__puppeteer__puppeteer_navigate` 来允许使用 Puppeteer MCP 服务器进行导航。
-   **手动编辑**你的 `.claude/settings.json` 或 `~/.claude.json`（我们建议将前者检入源代码控制以与团队共享）。
-   **使用 `--allowedTools` CLI 标志**进行会话特定的权限设置。

### d. 如果使用 GitHub，请安装 gh CLI

Claude 知道如何使用 `gh` CLI 与 GitHub 交互，以创建 issue、开启 pull request、读取评论等。如果没有安装 `gh`，Claude 仍然可以使用 GitHub API 或 MCP 服务器（如果你已安装）。

## 赋予 Claude 更多工具

Claude 可以访问你的 shell 环境，你可以在其中为它构建一套便利的脚本和函数，就像为自己构建一样。它还可以通过 MCP 和 REST API 利用更复杂的工具。

```ad-tip MCP (Model Context Protocol)

模型上下文协议（MCP）是一种开放标准，旨在让语言模型能够安全、可靠地与外部工具和服务进行交互。它定义了一套规范，使得像 Claude Code 这样的 AI 客户端可以发现并调用在 MCP 服务器上注册的工具（例如，数据库查询、网页浏览、API 调用）。这极大地扩展了 AI Agent 的能力边界，使其能够执行超越文本生成的复杂任务。
```

### a. 结合使用 Claude 与 bash 工具

Claude Code 继承了你的 bash 环境，使其可以访问你所有的工具。虽然 Claude 知道像 unix 工具和 `gh` 这样的常用工具，但如果没有指令，它不会知道你的自定义 bash 工具：

1.  告诉 Claude 工具名称和使用示例。
2.  告诉 Claude 运行 `--help` 来查看工具文档。
3.  在 `CLAUDE.md` 中记录常用工具。

### b. 结合使用 Claude 与 MCP

Claude Code 同时作为 MCP 服务器和客户端。作为客户端，它可以通过三种方式连接到任意数量的 MCP 服务器以访问其工具：

-   **在项目配置中**（在项目目录中运行 Claude Code 时可用）。
-   **在全局配置中**（在所有项目中可用）。
-   **在检入的 `.mcp.json` 文件中**（对任何在你的代码库中工作的人都可用）。例如，你可以将 Puppeteer 和 Sentry 服务器添加到你的 `.mcp.json` 中，这样每个在你仓库上工作的工程师都可以开箱即用地使用它们。

使用 MCP 时，启动 Claude 时加上 `--mcp-debug` 标志可以帮助识别配置问题。

### c. 使用自定义斜杠命令

对于重复的工作流——如调试循环、日志分析等——可以将提示模板存储在 `.claude/commands` 文件夹中的 Markdown 文件里。当你输入 `/` 时，这些命令就会出现在斜杠命令菜单中。你可以将这些命令检入 git，使其对团队其他成员可用。

自定义斜杠命令可以包含特殊关键字 `$ARGUMENTS`，以从命令调用中传递参数。

例如，这是一个可以用来自动拉取和修复 Github issue 的斜杠命令：

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

将以上内容放入 `.claude/commands/fix-github-issue.md` 文件中，就可以在 Claude Code 中作为 `/project:fix-github-issue` 命令使用。然后你就可以用 `/project:fix-github-issue 1234` 来让 Claude 修复 issue #1234。同样，你可以将自己的个人命令添加到 `~/.claude/commands` 文件夹中，以便在所有会话中使用。

## 尝试通用工作流

Claude Code 不强加特定的工作流，让你有灵活性按自己喜欢的方式使用它。在这种灵活性提供的空间内，我们的用户社区中涌现出了几种成功有效使用 Claude Code 的模式：

### a. 探索、规划、编码、提交

这个通用的工作流适用于许多问题：

1.  **让 Claude 阅读相关文件、图片或 URL**，可以提供一般性指引（“阅读处理日志的文件”）或具体文件名（“阅读 logging.py”），但明确告诉它暂时不要编写任何代码。
    1.  这是工作流中应考虑大力使用子智能体的部分，特别是对于复杂问题。告诉 Claude 使用子智能体来验证细节或调查它可能有的特定问题，尤其是在对话或任务的早期，往往可以在不损失太多效率的情况下保留上下文的可用性。
2.  **让 Claude 制定一个解决特定问题的计划**。我们建议使用 "think" 这个词来触发扩展思考模式，这会给 Claude 额外的计算时间来更彻底地评估备选方案。这些特定的短语直接映射到系统中不断增加的思考预算级别："think" < "think hard" < "think harder" < "ultrathink"。每个级别都会为 Claude 分配递增的思考预算。
    1.  如果这一步的结果看起来合理，你可以让 Claude 创建一个文档或 GitHub issue 来记录它的计划，这样如果实现（第3步）不符合你的期望，你可以重置到这个点。
3.  **让 Claude 用代码实现其解决方案**。这也是一个好时机，要求它在实现方案的各个部分时明确验证其解决方案的合理性。
4.  **让 Claude 提交结果并创建一个 pull request**。如果相关，这也是让 Claude 更新任何 README 或 changelog，解释它刚刚做了什么的好时机。

步骤 #1-#2 至关重要——没有它们，Claude 倾向于直接跳到编码解决方案。虽然有时这正是你想要的，但对于需要更深入前期思考的问题，先让 Claude 研究和规划会显著提高性能。

### b. 编写测试、提交；编码、迭代、提交

这是 Anthropic 内部最喜欢的工作流之一，适用于可以通过单元、集成或端到端测试轻松验证的更改。测试驱动开发（TDD）在 Agentic Coding 的加持下变得更加强大：

1.  **让 Claude 基于预期的输入/输出对编写测试**。明确指出你正在进行测试驱动开发，这样它就会避免创建模拟实现，即使是对于代码库中尚不存在的功能。
2.  **告诉 Claude 运行测试并确认它们失败**。明确告诉它在这个阶段不要编写任何实现代码通常很有帮助。
3.  **当你对测试满意时，让 Claude 提交测试**。
4.  **让 Claude 编写能通过测试的代码**，并指示它不要修改测试。告诉 Claude 继续工作，直到所有测试都通过。通常需要几次迭代，Claude 才能编写代码、运行测试、调整代码，然后再次运行测试。
    1.  在这个阶段，要求它用独立的子智能体来验证实现是否对测试过度拟合会很有帮助。
5.  **一旦你对更改满意，让 Claude 提交代码**。

<!-- 评注建议：TDD 与 Agentic Coding 的结合是一个完美的范例。AI Agent 最擅长的就是在一个有明确、可量化目标的闭环中进行迭代。测试用例为 AI 提供了这样一个完美的“目标函数”。这个工作流不仅保证了代码质量，还极大地发挥了 AI 的优势，是人机协作从“辅助”走向“自主”的关键一步。 -->

当 Claude 有一个清晰的迭代目标时——一个视觉模型、一个测试用例或其他类型的输出——它的表现最好。通过提供像测试这样的预期输出，Claude 可以进行更改、评估结果，并逐步改进直到成功。

### c. 编写代码、截图结果、迭代

与测试工作流类似，你可以为 Claude 提供视觉目标：

1.  **给 Claude 一种截取浏览器屏幕截图的方法**（例如，使用 [Puppeteer MCP server](https://github.com/modelcontextprotocol/servers/tree/c19925b8f0f2815ad72b08d2368f0007c86eb8e6/src/puppeteer)、一个 [iOS simulator MCP server](https://github.com/joshuayoes/ios-simulator-mcp)，或者手动复制/粘贴截图给 Claude）。
2.  **通过复制/粘贴或拖放图片，或者提供图片文件路径，给 Claude 一个视觉模型**。
3.  **让 Claude 用代码实现设计**，截取结果的屏幕截图，并迭代直到其结果与模型匹配。
4.  **当你满意时，让 Claude 提交**。

像人类一样，Claude 的输出通过迭代往往会显著改善。虽然第一个版本可能不错，但经过2-3次迭代后，它通常会看起来好得多。给 Claude 工具来看它的输出，以获得最佳结果。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6ea59a36fe82c2b300bceaf3b880a4b4852c552d-1600x1143.png&w=3840&q=75)

### d. 安全的 YOLO 模式

你可以使用 `claude --dangerously-skip-permissions` 来绕过所有权限检查，让 Claude 不间断地工作直到完成，而不是监督它。这对于修复 lint 错误或生成样板代码等工作流非常有效。

<!-- 评注建议：“Safe YOLO mode”这个提法非常有趣，它触及了 Agentic Coding 的核心矛盾：效率与安全。在完全隔离的环境（如 Docker Dev Container）中赋予 AI 完全的自主权，是一种务实的工程妥协。这暗示了未来 AI Agent 的运行环境可能会像今天的 CI/CD 一样，成为一种标准化的、受控的沙箱环境。 -->

让 Claude 运行任意命令是有风险的，可能导致数据丢失、系统损坏，甚至数据泄露（例如，通过提示注入攻击）。为了最小化这些风险，请在没有互联网访问的容器中使用 `--dangerously-skip-permissions`。你可以参考这个使用 Docker Dev Containers 的[参考实现](https://github.com/anthropics/claude-code/tree/main/.devcontainer)。

### e. 代码库问答

在熟悉一个新的代码库时，使用 Claude Code 进行学习和探索。你可以向 Claude 提出与你在结对编程时会问项目中其他工程师的同类问题。Claude 可以智能地搜索代码库来回答一般性问题，例如：

-   日志系统是如何工作的？
-   我如何创建一个新的 API 端点？
-   `foo.rs` 文件第 134 行的 `async move { ... }` 是做什么的？
-   `CustomerOnboardingFlowImpl` 处理了哪些边界情况？
-   为什么我们在第 333 行调用 `foo()` 而不是 `bar()`？
-   `baz.py` 文件第 334 行在 Java 中对应的实现是什么？

在 Anthropic，以这种方式使用 Claude Code 已成为我们的核心入职工作流，显著缩短了新员工的上手时间，并减轻了其他工程师的负担。无需特殊的提示！只需提问，Claude 就会探索代码以找到答案。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fa08ea13c2359aac0eceacebf2e15f81e8e8ec8d2-1600x1278.png&w=3840&q=75)

### f. 使用 Claude 与 git 交互

Claude 可以有效地处理许多 git 操作。许多 Anthropic 工程师将 90% 以上的 *git* 交互交给 Claude：

-   **搜索 *git* 历史**来回答诸如“v1.2.3 版本包含了哪些更改？”、“谁是这个特定功能的所有者？”或“为什么这个 API 是这样设计的？”等问题。明确提示 Claude 查阅 git 历史来回答这类问题会很有帮助。
-   **编写提交信息**。Claude 会自动查看你的更改和最近的历史记录，以撰写一条考虑了所有相关上下文的信息。
-   **处理复杂的 git 操作**，如恢复文件、解决 rebase 冲突以及比较和嫁接补丁。

### g. 使用 Claude 与 GitHub 交互

Claude Code 可以管理许多 GitHub 交互：

-   **创建 pull requests**：Claude 理解 "pr" 这个简写，并会根据 diff 和周围的上下文生成合适的提交信息。
-   **对简单的代码审查评论进行一键式解决**：只需告诉它修复你 PR 上的评论（可选地，给它更具体的指示），并在完成后推送回 PR 分支。
-   **修复失败的构建**或 linter 警告。
-   **通过让 Claude 遍历开放的 GitHub issues 来分类和分流**。

这消除了记住 `gh` 命令行语法的需要，同时自动化了日常任务。

### h. 使用 Claude 处理 Jupyter notebooks

Anthropic 的研究人员和数据科学家使用 Claude Code 来读写 Jupyter notebooks。Claude 可以解释输出，包括图像，为探索和与数据交互提供了一种快速的方式。没有必需的提示或工作流，但我们推荐的一个工作流是在 VS Code 中并排打开 Claude Code 和一个 `.ipynb` 文件。

你也可以要求 Claude 在向同事展示之前清理或美化你的 Jupyter notebook。明确告诉它让 notebook 或其数据可视化“美观”往往有助于提醒它正在为人类的观看体验进行优化。

## 优化你的工作流

以下建议适用于所有工作流：

### a. 指令要具体

Claude Code 的成功率随着指令的更具体而显著提高，尤其是在初次尝试时。预先给出明确的方向可以减少后续的路线修正。

例如：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/44bd6a1578f3a413c3cc1ef1a5fb179e.png?x-oss-process=image/quality,q_90/rotate,0)


Claude 可以推断意图，但它不会读心术。具体性带来与期望更好的对齐。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F75e1b57a0b696e7aafeca1ed5fa6ba7c601a5953-1360x1126.png&w=3840&q=75)

### b. 给 Claude 图片

Claude 通过多种方式出色地处理图像和图表：

-   **粘贴截图**（专业提示：在 macOS 中按 *cmd+ctrl+shift+4* 截图到剪贴板，然后按 *ctrl+v* 粘贴。注意这不是像在 mac 上通常使用的 cmd+v，并且在远程环境下无效。）
-   **直接拖放**图片到提示输入框。
-   **提供图片的文件路径**。

这在处理 UI 开发的设计模型以及用于分析和调试的可视化图表时特别有用。如果你没有向上下文中添加视觉元素，明确告诉 Claude 结果在视觉上具有吸引力的重要性仍然很有帮助。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F7372868757dd17b6f2d3fef98d499d7991d89800-1450x1164.png&w=3840&q=75)

### c. 提及你希望 Claude 查看或处理的文件

使用 tab 键补全功能快速引用仓库中任何地方的文件或文件夹，帮助 Claude 找到或更新正确的资源。

![](https://www.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fe071de707f209bbaa7f16b593cc7ed0739875dae-1306x1088.png&w=3840&q=75)

### d. 给 Claude URL

将特定的 URL 粘贴到你的提示旁边，让 Claude 获取和阅读。为避免对相同域名（例如，docs.foo.com）的权限提示，使用 `/permissions` 将域名添加到你的白名单中。

### e. 尽早并频繁地纠正路线

虽然自动接受模式（按 shift+tab 切换）让 Claude 自主工作，但通常通过成为一个积极的合作者并指导 Claude 的方法，你会得到更好的结果。在开始时向 Claude 彻底解释任务可以获得最佳结果，但你也可以随时纠正 Claude。

这四个工具有助于路线修正：

-   在编码前**让 Claude 制定一个计划**。明确告诉它在你确认其计划可行之前不要编码。
-   在任何阶段（思考、工具调用、文件编辑）**按 Escape 键中断** Claude，保留上下文，以便你可以重定向或扩展指令。
-   **双击 Escape 键跳回历史记录**，编辑之前的提示，并探索一个不同的方向。你可以编辑提示并重复，直到得到你想要的结果。
-   **让 Claude 撤销更改**，通常与选项 #2 结合使用，以采取不同的方法。

尽管 Claude Code 偶尔能在第一次尝试中完美解决问题，但使用这些修正工具通常能更快地产生更好的解决方案。

### f. 使用 `/clear` 保持上下文专注

在长时间的会话中，Claude 的上下文窗口可能会被不相关的对话、文件内容和命令填满。这会降低性能，有时会分散 Claude 的注意力。在任务之间频繁使用 `/clear` 命令来重置上下文窗口。

### g. 对复杂工作流使用清单和草稿板

对于包含多个步骤或需要详尽解决方案的大型任务——如代码迁移、修复大量 lint 错误或运行复杂的构建脚本——通过让 Claude 使用 Markdown 文件（甚至 GitHub issue！）作为清单和工作草稿板来提高性能：

例如，要修复大量的 lint 问题，你可以这样做：

1.  **告诉 Claude 运行 lint 命令**并将所有结果错误（包括文件名和行号）写入一个 Markdown 清单。
2.  **指示 Claude 逐个解决每个问题**，在修复和验证后勾选掉，然后继续下一个。

### h. 向 Claude 传递数据

有几种方法可以向 Claude 提供数据：

-   **直接复制粘贴**到你的提示中（最常见的方法）。
-   **通过管道输入到 Claude Code**（例如，`cat foo.txt | claude`），特别适用于日志、CSV 和大数据。
-   **告诉 Claude 通过 bash 命令、MCP 工具或自定义斜杠命令拉取数据**。
-   **让 Claude 读取文件**或获取 URL（对图像也有效）。

大多数会话都涉及这些方法的组合。例如，你可以通过管道输入一个日志文件，然后告诉 Claude 使用一个工具来拉取额外的上下文来调试日志。

## 使用无头模式自动化你的基础设施

Claude Code 包含[无头模式](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#automate-ci-and-infra-workflows)，用于非交互式环境，如 CI、pre-commit hooks、构建脚本和自动化。使用 `-p` 标志和一个提示来启用无头模式，并使用 `--output-format stream-json` 来获取流式 JSON 输出。

请注意，无头模式在会话之间不持久。你必须在每个会话中触发它。

### a. 使用 Claude 进行 issue 分流

无头模式可以驱动由 GitHub 事件触发的自动化，例如当你的仓库中创建了一个新的 issue 时。例如，公共的 [Claude Code 仓库](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-issue-triage-action/action.yml) 使用 Claude 来检查新进入的 issues 并分配适当的标签。

### b. 使用 Claude 作为 linter

Claude Code 可以提供[主观的代码审查](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-code-action/action.yml)，超越传统 linting 工具所能检测的范围，识别诸如拼写错误、过时的注释、误导性的函数或变量名等问题。

## 通过多 Claude 工作流提升水平

除了独立使用，一些最强大的应用涉及并行运行多个 Claude 实例：

<!-- 评注建议：这是整篇文章中最具前瞻性的部分。多 Agent 协作（无论是通过代码审查、测试驱动，还是利用 git worktree 并行处理任务）预示了软件开发的未来。这不再是“人与AI”的结对，而是“人指挥下的AI小队”协同作战。这种模式对开发者的技能要求也发生了变化，从纯粹的编码者转变为任务分解、流程设计和 AI 协调的“架构师”。 -->

### a. 一个 Claude 写代码；另一个 Claude 来验证

一个简单但有效的方法是让一个 Claude 写代码，而另一个来审查或测试它。类似于与多位工程师合作，有时拥有独立的上下文是有益的：

1.  使用 Claude 写代码。
2.  运行 `/clear` 或在另一个终端中启动第二个 Claude。
3.  让第二个 Claude 审查第一个 Claude 的工作。
4.  启动另一个 Claude（或再次 `/clear`）来阅读代码和审查反馈。
5.  让这个 Claude 根据反馈编辑代码。

你可以对测试做类似的事情：让一个 Claude 写测试，然后让另一个 Claude 写代码来使测试通过。你甚至可以通过给它们独立的工作草稿板，并告诉它们哪个写入哪个读取，来让你的 Claude 实例相互通信。

这种分离通常比让单个 Claude 处理所有事情产生更好的结果。

### b. 拥有多个代码库的 checkout

许多 Anthropic 的工程师不是等待 Claude 完成每一步，而是这样做：

1.  在不同的文件夹中**创建 3-4 个 git checkout**。
2.  在不同的终端标签页中**打开每个文件夹**。
3.  在每个文件夹中**用不同的任务启动 Claude**。
4.  **循环切换**以检查进度并批准/拒绝权限请求。

### c. 使用 git worktrees

这种方法在处理多个独立任务时表现出色，提供了一种比多个 checkout 更轻量级的替代方案。Git worktrees 允许你将同一仓库的多个分支检出到不同的目录中。每个 worktree 都有自己独立的工作目录和文件，同时共享相同的 Git 历史和 reflog。

使用 git worktrees 使你能够在项目的不同部分同时运行多个 Claude 会话，每个会话专注于其独立的任务。例如，你可能让一个 Claude 重构你的认证系统，而另一个构建一个完全不相关的数据可视化组件。由于任务不重叠，每个 Claude 都可以全速工作，而无需等待对方的更改或处理合并冲突：

1.  **创建 worktrees**：`git worktree add ../project-feature-a feature-a`
2.  **在每个 worktree 中启动 Claude**：`cd ../project-feature-a && claude`
3.  **根据需要创建额外的 worktrees**（在新的终端标签页中重复步骤1-2）。

一些技巧：

-   使用一致的命名约定。
-   每个 worktree 保持一个终端标签页。
-   如果你在 Mac 上使用 iTerm2，[设置通知](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#notification-setup)以便在 Claude 需要注意时得到提醒。
-   为不同的 worktrees 使用独立的 IDE 窗口。
-   完成后清理：`git worktree remove ../project-feature-a`

### d. 结合自定义工具链使用无头模式

`claude -p`（无头模式）将 Claude Code 以编程方式集成到更大的工作流中，同时利用其内置的工具和系统提示。使用无头模式主要有两种模式：

1.  **扇出（Fanning out）** 处理大规模迁移或分析（例如，分析数百个日志中的情绪或分析数千个 CSV）：
    1.  让 Claude 写一个脚本来生成任务列表。例如，生成一个需要从框架 A 迁移到框架 B 的 2000 个文件的列表。
    2.  循环遍历任务，为每个任务以编程方式调用 Claude，并给它一个任务和一组它可以使用的工具。例如：`claude -p “migrate foo.py from React to Vue. When you are done, you MUST return the string OK if you succeeded, or FAIL if the task failed.” --allowedTools Edit Bash(git commit:*)`
    3.  多次运行脚本并优化你的提示以获得期望的结果。

2.  **管道化（Pipelining）** 将 Claude 集成到现有的数据/处理管道中：
    1.  调用 `claude -p “<your prompt>” --json | your_command`，其中 `your_command` 是你处理管道的下一步。
    2.  就是这样！JSON 输出（可选）可以帮助提供结构，以便于自动化处理。

对于这两种用例，使用 `--verbose` 标志进行调试 Claude 调用会很有帮助。我们通常建议在生产环境中关闭详细模式以获得更清晰的输出。

你有什么使用 Claude Code 的技巧和最佳实践吗？标记 @AnthropicAI，让我们看看你在构建什么！

---

### 总结与展望

Claude Code 代表了 AI 辅助编程向"代理式编程"范式的重要转变。与传统的代码补全工具不同，Claude Code 通过提供接近原始模型访问能力、灵活的工具集成和多实例协作模式，为工程师提供了一个真正的 AI 编程伙伴。

从 Anthropic 内部的实践来看，Claude Code 已经深度改变了软件开发的多个环节——从新人入职、代码审查到日常的 Git 操作。特别值得注意的是，这种"不强加观点"的设计哲学，让每个团队都能根据自己的需求定制工作流，这可能是 AI 工程工具未来发展的重要方向。

<!-- 评注建议：这里可以展望代理式编程的未来，比如多模态输入、更智能的上下文管理、以及 AI 编程助手之间的标准化协议等 -->

随着越来越多的工程师采用这种工作模式，我们正在见证软件开发范式的根本性转变：从"人类编写代码、AI 辅助"到"人类定义意图、AI 实现细节"的新时代。Claude Code 的最佳实践不仅是工具使用指南，更是这个新时代的工程方法论雏形。

---

_致谢：本文基于 Anthropic 工程师 Boris Cherny 的原文编译，感谢 Claude Code 用户社区的创新方法和工作流贡献，特别感谢 Daisy Hollman、Ashwin Bhat、Cat Wu、Sid Bidasaria、Cal Rueb、Nodir Turakulov、Barry Zhang、Drew Hodun 等 Anthropic 工程师的宝贵见解。_