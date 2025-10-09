---
date: 2025-08-26 
source: https://www.anthropic.com/engineering/claude-code-best-practices
original_publication: 2025-04-18 
author: 手工川编译
---


Anthropic 在今年4月发布了 Claude Code——一个专为智能体编程（agentic coding）设计的命令行工具。这篇来自 Anthropic 工程团队的实践总结，详细阐述了在各种代码库、编程语言和开发环境中使用 Claude Code 的有效方法和技巧。作为一个研究项目的产物，Claude Code 为工程师和研究人员提供了将 Claude 更原生地集成到编码工作流中的新途径。



- 原文：https://www.anthropic.com/engineering/claude-code-best-practices
- 编译：手工川


### Overview

- **设计理念**：Claude Code 采用低层级、无偏见的设计，提供近乎原始的模型访问，不强制特定工作流
- **环境定制为王 (`CLAUDE.md`)**：通过创建和优化 `CLAUDE.md` 文件，为Claude提供项目特定的上下文、指令和约束，这是提升其表现的基石。
- **工具赋能，扩展能力边界**：将Claude无缝接入你的Shell环境、自定义脚本、MCP（模型上下文协议）工具集和REST API，让它能调用的“武器”越多，能力越强。
- **拥抱结构化工作流**：官方推荐了多种行之有效的协作模式，如“探索-规划-编码-提交”四步法、测试驱动开发（TDD）、以及基于视觉反馈的迭代循环。
- **精准指令，高效纠偏**：强调指令的明确性，并善用打断、历史编辑、撤销等工具进行早期、频繁的过程干预，将人与AI的协作效率最大化。
- **无头模式 (Headless Mode) 驱动自动化**：利用 `-p` 参数在CI/CD、预提交钩子等非交互式场景中运行Claude，实现代码审查、问题分类等基础设施自动化。
- **多智能体协作，战斗力翻倍**：通过并行运行多个Claude实例（如代码生成 vs. 代码审查），或利用 `git worktrees` 进行多任务处理，实现更复杂、更高效的开发流程。

---

## 定制你的专属开发环境

Claude Code 是一个能够自动将上下文拉取到提示中的智能体编码助手。这个上下文收集过程会消耗时间和Token，但你可以通过环境调优来优化它。

```ad-tip 智能体编码 (Agentic Coding)

Agentic Coding 指的是一种编程范式，其中开发者与一个或多个具备自主性、规划能力和工具使用能力的AI智能体（Agent）协作完成软件开发任务。与传统的代码补全或问答式AI助手不同，编程智能体可以更主动地理解任务、分解问题、执行命令、读写文件、与外部服务交互，并根据反馈进行迭代，从而在更高层次上辅助甚至自动化开发流程。
```

### a. 创建 `CLAUDE.md` 文件

`CLAUDE.md` 是一个特殊文件，当启动对话时，Claude会自动将其内容拉入上下文。这使其成为记录以下信息的理想场所：

-   常用的bash命令
-   核心文件和工具函数
-   代码风格指南
-   测试说明
-   代码仓库的规范（例如，分支命名、使用merge还是rebase等）
-   开发者环境设置（例如，pyenv的使用、哪些编译器可用）
-   项目中任何特殊的预期行为或警告
-   任何你希望Claude记住的其他信息

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

你可以将 `CLAUDE.md` 文件放置在多个位置：

-   **仓库根目录**，或你运行 `claude` 的任何位置（最常见用法）。将其命名为 `CLAUDE.md` 并提交到git，以便在不同会话和团队成员间共享（推荐），或者命名为 `CLAUDE.local.md` 并将其加入 `.gitignore`。
-   **运行 `claude` 目录的任何父目录**。这对于monorepo项目最有用，你可能在 `root/foo` 目录下运行 `claude`，而在 `root/CLAUDE.md` 和 `root/foo/CLAUDE.md` 中都有 `CLAUDE.md` 文件。这两者都会被自动拉入上下文。
-   **运行 `claude` 目录的任何子目录**。这是上述情况的反向操作，在这种情况下，当你处理子目录中的文件时，Claude会按需拉取 `CLAUDE.md` 文件。
-   **你的主文件夹** (`~/.claude/CLAUDE.md`)，它将应用于你所有的 *claude* 会话。

当你运行 `/init` 命令时，Claude会自动为你生成一个 `CLAUDE.md` 文件。

<!-- 评注建议：`CLAUDE.md` 的设计哲学非常值得关注。它本质上是将针对AI智能体的“系统级提示”或“元指令”显式化、版本化，并与代码库绑定。这标志着我们正在从与AI的“临时对话”转向“长期协作”，AI的配置本身也成为了项目工程资产的一部分。这或许是未来AI原生开发环境的一个标准实践。 -->

### b. 调优你的 `CLAUDE.md` 文件

你的 `CLAUDE.md` 文件会成为Claude提示的一部分，因此应该像对待任何频繁使用的提示一样对其进行优化。一个常见的错误是添加大量内容却不迭代其有效性。花时间进行实验，确定哪些内容能让模型产生最佳的指令遵循效果。

你可以手动向 `CLAUDE.md` 添加内容，或者按 `#` 键给Claude一个指令，它会自动将该指令整合到相关的 `CLAUDE.md` 中。许多工程师在编码时频繁使用 `#` 来记录命令、文件和风格指南，然后将 `CLAUDE.md` 的变更包含在提交中，以便团队成员也能受益。

在Anthropic，我们偶尔会用 [prompt improver](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/prompt-improver) 来优化 `CLAUDE.md` 文件，并经常调整指令（例如，用 "IMPORTANT" 或 "YOU MUST" 来强调）以提高遵循度。

![Claude Code tool allowlist](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6961243cc6409e41ba93895faded4f4bc1772366-1600x1231.png&w=3840&q=75)

### c. 管理Claude的工具白名单

默认情况下，Claude Code对任何可能修改你系统的操作都会请求许可：文件写入、许多bash命令、MCP工具等。我们设计Claude Code时采取了这种刻意保守的方法，以优先保障安全。你可以自定义白名单，允许你知道是安全的额外工具，或者允许那些易于撤销的潜在不安全工具（例如，文件编辑、`git commit`）。

有四种方式来管理允许的工具：

-   在会话中被提示时**选择 "Always allow"**。
-   启动Claude Code后**使用 `/permissions` 命令**来添加或移除工具白名单。例如，你可以添加 `Edit` 来始终允许文件编辑，`Bash(git commit:*)` 来允许git提交，或者 `mcp__puppeteer__puppeteer_navigate` 来允许使用Puppeteer MCP服务器进行导航。
-   **手动编辑**你的 `.claude/settings.json` 或 `~/.claude.json`（我们建议将前者检入源代码控制以与团队共享）。
-   **使用 `--allowedTools` CLI标志**进行会话特定的权限设置。

### d. 如果使用GitHub，请安装gh CLI

Claude知道如何使用 `gh` CLI与GitHub交互，用于创建issue、开启pull request、读取评论等。如果没有安装 `gh`，Claude仍然可以使用GitHub API或MCP服务器（如果你已安装）。

## 赋予Claude更多工具

Claude可以访问你的shell环境，你可以在其中为它构建一系列便利的脚本和函数，就像为自己构建一样。它还可以通过MCP和REST API利用更复杂的工具。

### a. 结合使用bash工具

Claude Code继承了你的bash环境，使其可以访问你所有的工具。虽然Claude了解像unix工具和 `gh` 这样的常用工具，但如果没有指令，它不会知道你的自定义bash工具：

1.  告诉Claude工具名称和使用示例。
2.  告诉Claude运行 `--help` 来查看工具文档。
3.  在 `CLAUDE.md` 中记录常用工具。

### b. 结合使用MCP

```ad-tip MCP (Model Context Protocol)

模型上下文协议（MCP）是一种开放标准，旨在让语言模型能够安全、可靠地与外部工具和服务进行交互。它定义了一套标准的接口和数据格式，使得开发者可以轻松地将现有的API、数据库或自定义功能“封装”成模型可以理解和调用的工具。Claude Code既可以作为MCP客户端连接其他服务，也可以作为MCP服务器向外提供能力。
```

Claude Code同时充当MCP服务器和客户端。作为客户端，它可以通过三种方式连接到任意数量的MCP服务器以访问它们的工具：

-   **在项目配置中**（在那个目录运行Claude Code时可用）。
-   **在全局配置中**（在所有项目中可用）。
-   **在一个已检入的 `.mcp.json` 文件中**（对任何在你的代码库中工作的人都可用）。例如，你可以将Puppeteer和Sentry服务器添加到你的 `.mcp.json` 中，这样每个在你仓库上工作的工程师都可以开箱即用地使用它们。

使用MCP时，用 `--mcp-debug` 标志启动Claude也很有帮助，可以帮助识别配置问题。

### c. 使用自定义斜杠命令

对于重复的工作流——调试循环、日志分析等——可以将提示模板存储在 `.claude/commands` 文件夹中的Markdown文件中。当你输入 `/` 时，这些模板就会通过斜杠命令菜单变得可用。你可以将这些命令检入git，使其对团队其他成员可用。

自定义斜杠命令可以包含特殊关键字 `$ARGUMENTS`，以从命令调用中传递参数。

例如，这是一个可以用来自动拉取和修复GitHub issue的斜杠命令：

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

将以上内容放入 `.claude/commands/fix-github-issue.md` 文件中，就可以在Claude Code中作为 `/project:fix-github-issue` 命令使用。然后你就可以用 `/project:fix-github-issue 1234` 来让Claude修复issue #1234。同样，你可以将自己的个人命令添加到 `~/.claude/commands` 文件夹中，以便在所有会话中使用。

## 尝试常见的工作流

Claude Code不强加特定的工作流，让你有灵活性按自己想要的方式使用它。在这种灵活性所提供的空间内，我们的用户社区中涌现出了几种成功有效使用Claude Code的模式：

### a. 探索、规划、编码、提交

这个通用的工作流适用于许多问题：

1.  **让Claude阅读相关文件、图片或URL**，可以提供一般性指引（“阅读处理日志的文件”）或具体文件名（“阅读logging.py”），但明确告诉它暂时不要编写任何代码。
    1.  这是工作流中应该考虑大力使用子智能体的部分，特别是对于复杂问题。告诉Claude使用子智能体来验证细节或调查它可能有的特定问题，尤其是在对话或任务的早期，往往可以在不损失太多效率的情况下保留上下文的可用性。
2.  **让Claude制定一个解决特定问题的计划**。我们建议使用“think”这个词来触发扩展思考模式，这会给Claude额外的计算时间来更彻底地评估备选方案。这些特定的短语直接映射到系统中不断增加的思考预算：“think” < “think hard” < “think harder” < “ultrathink”。每个级别都会为Claude分配递增的思考预算。
    1.  如果这一步的结果看起来合理，你可以让Claude用它的计划创建一个文档或一个GitHub issue，这样如果实现（第3步）不符合你的期望，你可以重置到这个点。
3.  **让Claude用代码实现其解决方案**。这也是一个好时机，要求它在实现方案的各个部分时明确验证其解决方案的合理性。
4.  **让Claude提交结果并创建一个pull request**。如果相关，这也是让Claude更新任何README或changelog，解释它刚刚做了什么的好时机。

步骤 #1-#2 至关重要——没有它们，Claude往往会直接跳到编码解决方案。虽然有时这正是你想要的，但对于需要更深入前期思考的问题，先让Claude研究和规划会显著提高性能。

### b. 编写测试，提交；编码，迭代，提交

这是Anthropic内部最喜欢的一种工作流，适用于可以通过单元、集成或端到端测试轻松验证的变更。测试驱动开发（TDD）在智能体编码的加持下变得更加强大：

1.  **让Claude根据预期的输入/输出对编写测试**。明确指出你正在进行测试驱动开发，这样它就会避免创建模拟实现，即使对于代码库中尚不存在的功能也是如此。
2.  **告诉Claude运行测试并确认它们失败**。明确告诉它在这个阶段不要编写任何实现代码通常很有帮助。
3.  **当你对测试满意时，让Claude提交测试**。
4.  **让Claude编写通过测试的代码**，并指示它不要修改测试。告诉Claude继续前进，直到所有测试都通过。它通常需要几次迭代来编写代码、运行测试、调整代码，然后再次运行测试。
    1.  在这个阶段，要求它用独立的子智能体来验证实现没有对测试过拟合会很有帮助。
5.  **一旦你对变更满意，让Claude提交代码**。

当Claude有一个明确的迭代目标时——一个视觉模型、一个测试用例或其他类型的输出——它的表现最好。通过提供像测试这样的预期输出，Claude可以进行更改、评估结果，并逐步改进直到成功。

<!-- 评注建议：TDD工作流完美诠释了AI编程智能体的一个核心价值：它们不是要颠覆软件工程的最佳实践，而是要成为这些实践的“放大器”。对于人类来说，严格执行TDD可能很枯燥，但对于AI来说，这是一个完美的、可验证的、闭环的迭代过程。这预示着未来AI将帮助我们更轻松地落地那些“知易行难”的工程原则。 -->

### c. 编写代码，截图结果，迭代

与测试工作流类似，你可以为Claude提供视觉目标：

1.  **给Claude一种截取浏览器屏幕截图的方法**（例如，使用 [Puppeteer MCP server](https://github.com/modelcontextprotocol/servers/tree/c19925b8f0f2815ad72b08d2368f0007c86eb8e6/src/puppeteer)、一个 [iOS simulator MCP server](https://github.com/joshuayoes/ios-simulator-mcp)，或者手动复制/粘贴截图给Claude）。
2.  **通过复制/粘贴或拖放图片，或者给Claude图片文件路径，来给它一个视觉模型**。
3.  **让Claude用代码实现设计**，截取结果的屏幕截图，并迭代直到其结果与模型匹配。
4.  **当你满意时，让Claude提交**。

像人类一样，Claude的输出在迭代后往往会显著改善。虽然第一个版本可能不错，但经过2-3次迭代后，它通常会看起来好得多。给Claude工具来看它的输出，以获得最佳结果。

![Safe yolo mode](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F6ea59a36fe82c2b300bceaf3b880a4b4852c552d-1600x1143.png&w=3840&q=75)

### d. 安全的“YOLO”模式

你可以使用 `claude --dangerously-skip-permissions` 来绕过所有权限检查，让Claude不间断地工作直到完成，而不是监督它。这对于像修复lint错误或生成样板代码这样的工作流非常有效。

让Claude运行任意命令是有风险的，可能导致数据丢失、系统损坏，甚至数据泄露（例如，通过提示注入攻击）。为了最小化这些风险，请在一个没有互联网访问的容器中使用 `--dangerously-skip-permissions`。你可以遵循这个使用Docker Dev Containers的[参考实现](https://github.com/anthropics/claude-code/tree/main/.devcontainer)。

<!-- 评注建议：“YOLO模式”这个命名非常传神。它直接触及了AI智能体领域的核心矛盾：自主性与安全性之间的权衡。Anthropic在这里给出的方案——在隔离容器中运行——是目前业界公认的、最务实的解决方案。这提醒我们，在追求AI能力的同时，构建强大的安全沙箱和可控环境将是同等重要的技术命题。 -->

### e. 代码库问答

在熟悉一个新的代码库时，使用Claude Code进行学习和探索。你可以向Claude提出与你在结对编程时会问项目中另一位工程师相同类型的问题。Claude可以智能体式地搜索代码库来回答一般性问题，例如：

-   日志系统是如何工作的？
-   我如何创建一个新的API端点？
-   `foo.rs` 文件第134行的 `async move { ... }` 是做什么的？
-   `CustomerOnboardingFlowImpl` 处理了哪些边缘情况？
-   为什么我们在第333行调用 `foo()` 而不是 `bar()`？
-   `baz.py` 文件第334行在Java中的等价实现是什么？

在Anthropic，以这种方式使用Claude Code已经成为我们的核心入职工作流，显著缩短了新员工的上手时间，并减轻了其他工程师的负担。无需特殊的提示！只需提问，Claude就会探索代码以找到答案。

![Use Claude to interact with git](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fa08ea13c2359aac0eceacebf2e15f81e8e8ec8d2-1600x1278.png&w=3840&q=75)

### f. 使用Claude与git交互

Claude可以有效地处理许多git操作。许多Anthropic工程师将90%以上的 *git* 交互交给Claude处理：

-   **搜索 *git* 历史**来回答诸如“v1.2.3版本包含了哪些变更？”、“谁是这个特定功能的所有者？”或“为什么这个API是这样设计的？”等问题。明确提示Claude查看git历史来回答这类查询会很有帮助。
-   **编写提交信息**。Claude会自动查看你的变更和最近的历史记录，以撰写一条考虑了所有相关上下文的信息。
-   **处理复杂的git操作**，如恢复文件、解决rebase冲突以及比较和嫁接补丁。

### g. 使用Claude与GitHub交互

Claude Code可以管理许多GitHub交互：

-   **创建pull requests**：Claude理解“pr”这个简写，并会根据diff和周围的上下文生成适当的提交信息。
-   **对简单的代码审查评论实现一键式解决**：只需告诉它修复你PR上的评论（可选地，给它更具体的指令），并在完成后推送回PR分支。
-   **修复失败的构建**或linter警告。
-   **通过让Claude遍历开放的GitHub issue来分类和分流**。

这消除了记住 `gh` 命令行语法的需要，同时自动化了日常任务。

### h. 使用Claude处理Jupyter notebooks

Anthropic的研究人员和数据科学家使用Claude Code来读写Jupyter notebooks。Claude可以解释输出，包括图片，为探索和与数据交互提供了一种快速的方式。没有必需的提示或工作流，但我们推荐的一个工作流是在VS Code中并排打开Claude Code和一个 `.ipynb` 文件。

你也可以让Claude在你向同事展示Jupyter notebook之前清理或美化它。明确告诉它让notebook或其数据可视化“美观”往往有助于提醒它正在为人类的观看体验进行优化。

## 优化你的工作流

以下建议适用于所有工作流：

### a. 指令要具体

Claude Code的成功率随着指令的更具体而显著提高，尤其是在初次尝试时。预先给出明确的方向可以减少后续纠正的需要。

例如：

| 差的指令 | 好的指令 |
| --- | --- |
| 为foo.py添加测试 | 为foo.py编写一个新的测试用例，覆盖用户未登录的边缘情况。避免使用mock。 |
| 为什么ExecutionFactory的api这么奇怪？ | 查看ExecutionFactory的git历史，并总结其api是如何演变至今的。 |
| 添加一个日历小部件 | 查看主页上现有小部件的实现方式以理解其模式，特别是代码和接口是如何分离的。HotDogWidget.php是一个很好的起点。然后，遵循该模式实现一个新的日历小部件，让用户可以选择月份并向前/向后翻页选择年份。从头开始构建，除了代码库中已使用的库外，不要使用其他库。 |

Claude可以推断意图，但它不会读心术。具体性带来与期望更好的对齐。

![Give Claude images](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F75e1b57a0b696e7aafeca1ed5fa6ba7c601a5953-1360x1126.png&w=3840&q=75)

### b. 给Claude图片

Claude通过多种方法在处理图片和图表方面表现出色：

-   **粘贴截图**（专业提示：在macOS中按 *cmd+ctrl+shift+4* 截屏到剪贴板，然后按 *ctrl+v* 粘贴。注意，这不像你在mac上通常使用的cmd+v，并且在远程操作时无效。）
-   **拖放**图片直接到提示输入框。
-   **提供图片的文件路径**。

这在处理UI开发的设计稿参考点，以及用于分析和调试的可视化图表时特别有用。如果你没有向上下文中添加视觉元素，向Claude明确指出结果在视觉上吸引人的重要性仍然很有帮助。

![Mention files you want Claude to look at or work on](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2F7372868757dd17b6f2d3fef98d499d7991d89800-1450x1164.png&w=3840&q=75)

### c. 提及你希望Claude查看或处理的文件

使用tab补全快速引用仓库中任何地方的文件或文件夹，帮助Claude找到或更新正确的资源。

![Give Claude URLs](https://www-cdn.anthropic.com/_next/image?url=https%3A%2F%2Fwww-cdn.anthropic.com%2Fimages%2F4zrzovbb%2Fwebsite%2Fe071de707f209bbaa7f16b593cc7ed0739875dae-1306x1088.png&w=3840&q=75)

### d. 给Claude URL

将特定的URL与你的提示一起粘贴，让Claude获取和阅读。为避免对相同域名（例如，docs.foo.com）的权限提示，使用 `/permissions` 将域名添加到你的白名单中。

### e. 尽早并频繁地纠正路线

虽然自动接受模式（按shift+tab切换）让Claude自主工作，但通过成为一个积极的合作者并引导Claude的方法，你通常会得到更好的结果。你可以在开始时向Claude彻底解释任务以获得最佳结果，但你也可以随时纠正Claude。

这四个工具有助于路线纠正：

-   在编码前**让Claude制定一个计划**。明确告诉它在你确认其计划看起来不错之前不要编码。
-   在任何阶段（思考、工具调用、文件编辑）**按Escape键打断**Claude，保留上下文，以便你可以重定向或扩展指令。
-   **双击Escape键跳回历史记录**，编辑之前的提示，并探索一个不同的方向。你可以编辑提示并重复，直到得到你想要的结果。
-   **让Claude撤销更改**，通常与选项#2结合使用以采取不同的方法。

尽管Claude Code偶尔会在第一次尝试时完美解决问题，但使用这些纠正工具通常能更快地产生更好的解决方案。

### f. 使用 `/clear` 保持上下文专注

在长时间的会话中，Claude的上下文窗口可能会被不相关的对话、文件内容和命令填满。这会降低性能，有时会分散Claude的注意力。在任务之间频繁使用 `/clear` 命令来重置上下文窗口。

### g. 对复杂工作流使用清单和草稿板

对于具有多个步骤或需要详尽解决方案的大型任务——如代码迁移、修复大量lint错误或运行复杂的构建脚本——通过让Claude使用Markdown文件（甚至GitHub issue！）作为清单和工作草稿板来提高性能：

例如，要修复大量的lint问题，你可以这样做：

1.  **告诉Claude运行lint命令**并将所有结果错误（包括文件名和行号）写入一个Markdown清单。
2.  **指示Claude逐一解决每个问题**，在勾选并移至下一个问题之前修复和验证。

### h. 向Claude传递数据

有几种方法可以向Claude提供数据：

-   **直接复制粘贴**到你的提示中（最常见的方法）。
-   **通过管道输入到Claude Code**（例如，`cat foo.txt | claude`），特别适用于日志、CSV和大数据。
-   **告诉Claude通过bash命令、MCP工具或自定义斜杠命令拉取数据**。
-   **让Claude读取文件**或获取URL（对图片也有效）。

大多数会话都涉及这些方法的组合。例如，你可以通过管道输入一个日志文件，然后告诉Claude使用一个工具来拉取额外的上下文来调试日志。

## 使用无头模式自动化你的基础设施

Claude Code包含[无头模式](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#automate-ci-and-infra-workflows)，用于CI、预提交钩子、构建脚本和自动化等非交互式上下文。使用 `-p` 标志和一个提示来启用无头模式，并使用 `--output-format stream-json` 来获取流式JSON输出。

请注意，无头模式在会话之间不持久。你必须在每个会话中触发它。

### a. 使用Claude进行问题分类

无头模式可以驱动由GitHub事件触发的自动化，例如当你的仓库中创建了一个新issue时。例如，公共的[Claude Code仓库](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-issue-triage-action/action.yml)使用Claude来检查新进的issue并分配适当的标签。

### b. 使用Claude作为linter

Claude Code可以提供[主观代码审查](https://github.com/anthropics/claude-code/blob/main/.github/actions/claude-code-action/action.yml)，超越传统linting工具所能检测的范围，识别诸如拼写错误、过时的注释、误导性的函数或变量名等问题。

## 通过多Claude工作流提升水平

除了独立使用外，一些最强大的应用涉及并行运行多个Claude实例：

### a. 让一个Claude写代码；用另一个Claude来验证

一个简单但有效的方法是让一个Claude写代码，而另一个来审查或测试它。类似于与多位工程师合作，有时拥有独立的上下文是有益的：

1.  使用Claude写代码。
2.  运行 `/clear` 或在另一个终端中启动第二个Claude。
3.  让第二个Claude审查第一个Claude的工作。
4.  启动另一个Claude（或再次 `/clear`）来阅读代码和审查反馈。
5.  让这个Claude根据反馈编辑代码。

你可以对测试做类似的事情：让一个Claude写测试，然后让另一个Claude写代码来使测试通过。你甚至可以让你的Claude实例通过给它们独立的工作草稿板并告诉它们哪个写入哪个读取来相互通信。

这种分离通常比让单个Claude处理所有事情产生更好的结果。

<!-- 评注建议：多智能体工作流是本文最具前瞻性的部分。无论是“生成-审查”模式，还是利用git worktrees进行并行开发，都揭示了未来软件开发可能演变为一种“人-AI混合团队”的协作模式。开发者将从代码的直接编写者，转变为AI智能体团队的“架构师”和“指挥官”。这对于我们思考未来的开发者工具和团队组织形式极具启发。 -->

### b. 拥有你的仓库的多个检出副本

许多Anthropic的工程师不是等待Claude完成每一步，而是这样做：

1.  在不同的文件夹中**创建3-4个git检出副本**。
2.  在不同的终端标签页中**打开每个文件夹**。
3.  在每个文件夹中**用不同的任务启动Claude**。
4.  **循环切换**来检查进度并批准/拒绝权限请求。

### c. 使用git worktrees

这种方法在处理多个独立任务时大放异彩，提供了一种比多个检出副本更轻量级的替代方案。Git worktrees允许你将同一仓库的多个分支检出到不同的目录中。每个worktree都有自己独立的工作目录和文件，同时共享相同的Git历史和reflog。

使用git worktrees使你可以在项目的不同部分同时运行多个Claude会话，每个会话都专注于其独立的任务。例如，你可能有一个Claude在重构你的认证系统，而另一个在构建一个完全不相关的数据可视化组件。由于任务不重叠，每个Claude都可以全速工作，而无需等待对方的更改或处理合并冲突：

1.  **创建worktrees**：`git worktree add ../project-feature-a feature-a`
2.  **在每个worktree中启动Claude**：`cd ../project-feature-a && claude`
3.  **根据需要创建额外的worktrees**（在新的终端标签页中重复步骤1-2）。

一些技巧：

-   使用一致的命名约定。
-   每个worktree保持一个终端标签页。
-   如果你在Mac上使用iTerm2，为Claude需要注意时[设置通知](https://docs.anthropic.com/en/docs/agents-and-tools/claude-code/overview#notification-setup)。
-   为不同的worktrees使用独立的IDE窗口。
-   完成后清理：`git worktree remove ../project-feature-a`

### d. 结合自定义工具链使用无头模式

`claude -p`（无头模式）将Claude Code以编程方式集成到更大的工作流中，同时利用其内置的工具和系统提示。使用无头模式主要有两种模式：

1\. **扇出 (Fanning out)** 处理大规模迁移或分析（例如，分析数百个日志中的情绪或分析数千个CSV）：

1.  让Claude编写一个脚本来生成任务列表。例如，生成一个需要从框架A迁移到框架B的2000个文件的列表。
2.  循环遍历任务，为每个任务以编程方式调用Claude，并给它一个任务和一组它可以使用的工具。例如：`claude -p “migrate foo.py from React to Vue. When you are done, you MUST return the string OK if you succeeded, or FAIL if the task failed.” --allowedTools Edit Bash(git commit:*)`
3.  多次运行脚本并优化你的提示以获得期望的结果。

2\. **管道化 (Pipelining)** 将Claude集成到现有的数据/处理管道中：

1.  调用 `claude -p “<your prompt>” --json | your_command`，其中 `your_command` 是你处理管道的下一步。
2.  就这样！JSON输出（可选）可以帮助提供结构，以便于自动化处理。

对于这两种用例，使用 `--verbose` 标志进行调试Claude调用会很有帮助。我们通常建议在生产中关闭详细模式以获得更清晰的输出。

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