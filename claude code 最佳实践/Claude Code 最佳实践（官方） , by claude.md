---

## title: Claude Code 最佳实践：代理式编程的工程化指南 subtitle: 来自 Anthropic 工程团队的一线实践经验 date: 2025-08-26 source: https://www.anthropic.com/engineering/claude-code-best-practices original_date: 2025-04-18
---


# Claude Code 最佳实践：代理式编程的工程化指南

今年 4 月，Anthropic 正式发布了 **Claude Code** —— 一个专为代理式编程（agentic coding）设计的命令行工具。作为 Anthropic 内部研究项目的成果，Claude Code 为工程师和研究人员提供了一种更原生的方式，将 Claude 集成到日常编程工作流中。这篇来自 Anthropic 工程团队的技术文档，系统总结了内外部工程师在各种代码库、编程语言和开发环境中使用 Claude Code 的有效模式。

<!-- 评注建议：这里可以评论 Claude Code 发布时机的战略意义，以及它与 Cursor、GitHub Copilot 等工具的差异化定位 -->

## 核心发现摘要

- **设计理念**：Claude Code 采用了"刻意低级、不强加观点"的设计哲学，提供接近原始模型的访问能力，不强制特定工作流
- **六大实践领域**：自定义设置、工具扩展、工作流模式、性能优化、自动化部署、多实例协作
- **关键创新**：`CLAUDE.md` 配置系统、MCP 集成、无头模式、多 Claude 实例并行工作流
- **实战价值**：Anthropic 内部工程师已将其作为核心代码审查、新人入职培训和 Git 交互的主要工具

## 一、自定义设置：构建专属的 AI 编程环境

### 创建 `CLAUDE.md` 文件

`CLAUDE.md` 是 Claude Code 的核心配置机制。当启动会话时，Claude 会自动将这个特殊文件拉入上下文。Anthropic 建议在其中记录：

- 常用 bash 命令
- 核心文件和工具函数
- 代码风格指南
- 测试指令
- 仓库规范（如分支命名、merge vs. rebase 等）
- 开发环境配置（如 pyenv use、编译器选择）
- 项目特有的异常行为或警告
- 其他希望 Claude 记住的信息

```ad-tip

CLAUDE.md 没有固定格式要求，但 Anthropic 建议保持简洁和人类可读。文件可以放置在多个位置：仓库根目录（最常见）、任何父目录（适合 monorepo）、子目录、或用户主目录（~/.claude/CLAUDE.md）。通过 `/init` 命令可以自动生成初始配置。
```

以下是一个典型的 `CLAUDE.md` 示例：

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

### 调优 `CLAUDE.md` 文件

由于 `CLAUDE.md` 成为 Claude 提示词的一部分，应该像优化频繁使用的提示词一样对其进行迭代。Anthropic 工程师会定期通过 prompt improver 运行 `CLAUDE.md`，并调整指令（如添加 "IMPORTANT" 或 "YOU MUST" 等强调词）来提高遵循度。

<!-- 评注建议：这里可以深入分析 CLAUDE.md 本质上是一种"持久化的系统提示词"设计，评论这种设计模式对 AI 工程的启发意义 -->

### 管理允许的工具列表

Claude Code 在设计上采取了保守的安全策略：任何可能修改系统的操作（文件写入、bash 命令、MCP 工具等）都需要请求权限。用户可以通过四种方式管理工具权限：

1. 在会话中选择"始终允许"
2. 使用 `/permissions` 命令添加或移除工具
3. 手动编辑 `.claude/settings.json` 或 `~/.claude.json`
4. 使用 `--allowedTools` CLI 标志设置会话特定权限

### GitHub 集成优化

如果使用 GitHub，安装 `gh` CLI 可以让 Claude 执行创建 issue、开启 PR、读取评论等操作。即使没有安装 `gh`，Claude 仍可通过 GitHub API 或 MCP 服务器工作。

## 二、扩展工具集：构建 Claude 的能力矩阵

### Bash 工具集成

Claude Code 继承用户的 bash 环境，可以访问所有工具。虽然 Claude 了解常见的 Unix 工具和 `gh`，但对于自定义 bash 工具需要：

1. 告知 Claude 工具名称和使用示例
2. 让 Claude 运行 `--help` 查看文档
3. 在 `CLAUDE.md` 中记录常用工具

### MCP（Model Context Protocol）集成

Claude Code 既是 MCP 服务器也是客户端。作为客户端，它可以通过三种方式连接 MCP 服务器：

- **项目配置**：在特定目录运行时可用
- **全局配置**：所有项目可用
- **签入的 `.mcp.json` 文件**：仓库中所有工程师可用

使用 `--mcp-debug` 标志可以帮助识别配置问题。

### 自定义斜杠命令

对于重复的工作流（调试循环、日志分析等），可以在 `.claude/commands` 文件夹中存储提示模板。这些命令通过输入 `/` 触发。

示例：自动修复 GitHub issue 的命令模板：

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

将上述内容保存到 `.claude/commands/fix-github-issue.md` 后，就可以使用 `/project:fix-github-issue 1234` 来修复 issue #1234。

## 三、常见工作流模式

### 探索、规划、编码、提交

这个通用工作流适合多数问题：

1. **让 Claude 阅读相关文件、图像或 URL**，明确告诉它暂时不要编写代码
2. **要求 Claude 制定解决问题的计划**。使用"think"触发扩展思考模式，给 Claude 额外的计算时间
3. **让 Claude 实现解决方案**
4. **要求 Claude 提交结果并创建 PR**

<!-- 评注建议：这里可以评论"思考链"（Chain of Thought）在实际工程中的应用，以及不同思考强度级别的实用性 -->

```ad-tip

Anthropic 映射了特定短语到不同的思考预算级别：
- "think" < "think hard" < "think harder" < "ultrathink"
每个级别都会为 Claude 分配递进式增加的思考预算。
```

### 测试驱动开发（TDD）工作流

1. **让 Claude 基于预期输入/输出编写测试**
2. **运行测试并确认失败**
3. **提交测试**
4. **让 Claude 编写通过测试的代码**
5. **提交代码**

### 视觉驱动迭代

1. **给 Claude 截图能力**（如 Puppeteer MCP 服务器）
2. **提供视觉模型**
3. **让 Claude 实现设计并迭代**
4. **满意后提交**

### 安全 YOLO 模式

使用 `claude --dangerously-skip-permissions` 跳过所有权限检查，让 Claude 不间断工作。建议在无网络访问的容器中使用，以最小化风险。

### 代码库问答

将 Claude Code 用于学习和探索新代码库。可以问 Claude 类似结对编程时会问其他工程师的问题：

- 日志系统是如何工作的？
- 如何创建新的 API 端点？
- `CustomerOnboardingFlowImpl` 处理了哪些边缘情况？
- 为什么在第 333 行调用 `foo()` 而不是 `bar()`？

在 Anthropic，这已成为核心入职工作流，显著提升了新人上手速度。

### Git 交互自动化

Anthropic 工程师使用 Claude 处理 90%+ 的 git 交互：

- **搜索 git 历史**回答"v1.2.3 包含了哪些改动？"
- **编写提交信息**
- **处理复杂 git 操作**如回滚文件、解决 rebase 冲突

### GitHub 工作流集成

- **创建 PR**：Claude 理解"pr"简写
- **实现代码审查意见的一次性解决**
- **修复失败的构建**或 linter 警告
- **分类和分流开放的 issue**

### Jupyter Notebook 协作

研究人员和数据科学家使用 Claude Code 读写 Jupyter notebook。Claude 可以解释输出（包括图像），提供快速的数据探索和交互方式。

## 四、工作流优化策略

### 具体化指令

Claude Code 的成功率随着指令的具体性显著提升。清晰的指示减少了后续纠正的需要。

|糟糕的指令|优秀的指令|
|---|---|
|为 foo.py 添加测试|为 foo.py 编写新测试用例，覆盖用户未登录的边缘情况。避免使用 mock|
|为什么 ExecutionFactory 有这么奇怪的 API？|查看 ExecutionFactory 的 git 历史，总结其 API 是如何演变的|

### 利用图像输入

Claude 擅长处理图像和图表：

- **粘贴截图**（macOS: cmd+ctrl+shift+4 截图到剪贴板，ctrl+v 粘贴）
- **拖放图像**直接到提示输入
- **提供文件路径**

### 文件引用优化

使用 tab 补全快速引用仓库中的文件或文件夹，帮助 Claude 找到正确的资源。

### URL 集成

粘贴特定 URL 让 Claude 获取和阅读。使用 `/permissions` 将域名添加到允许列表以避免重复权限提示。

### 早期和频繁的纠正

虽然自动接受模式（shift+tab 切换）让 Claude 自主工作，但作为积极的协作者引导 Claude 的方法通常能获得更好的结果。四个纠正工具：

1. **要求 Claude 先制定计划**
2. **按 Escape 中断** Claude 的任何阶段
3. **双击 Escape 跳回历史**，编辑之前的提示
4. **要求 Claude 撤销更改**

### 使用 `/clear` 保持上下文聚焦

在长会话期间，使用 `/clear` 命令在任务之间重置上下文窗口。

### 复杂工作流的清单和草稿板

对于包含多个步骤的大型任务，让 Claude 使用 Markdown 文件作为清单和工作草稿板可以提升性能。

### 数据传递方法

- **复制粘贴**直接到提示（最常见）
- **管道输入** Claude Code（如 `cat foo.txt | claude`）
- **让 Claude 拉取数据**通过 bash 命令、MCP 工具或自定义斜杠命令
- **让 Claude 读取文件**或获取 URL

## 五、无头模式：基础设施自动化

Claude Code 包含无头模式，用于 CI、pre-commit hooks、构建脚本等非交互式上下文。使用 `-p` 标志加提示启用无头模式，`--output-format stream-json` 用于流式 JSON 输出。

### Issue 分类自动化

无头模式可以驱动由 GitHub 事件触发的自动化。例如，Claude Code 公共仓库使用 Claude 检查新 issue 并分配适当的标签。

### Claude 作为 Linter

Claude Code 可以提供超越传统 linting 工具的主观代码审查，识别拼写错误、过期注释、误导性函数或变量名等问题。

<!-- 评注建议：这里可以探讨"主观性 linting"的概念，以及 AI 在代码质量保证中的独特价值 -->

## 六、多 Claude 工作流：并行协作模式

### 编写-验证分离模式

一个简单但有效的方法是让一个 Claude 编写代码，另一个审查或测试：

1. 使用 Claude 编写代码
2. 运行 `/clear` 或在另一个终端启动第二个 Claude
3. 让第二个 Claude 审查第一个的工作
4. 启动另一个 Claude 读取代码和审查反馈
5. 让这个 Claude 基于反馈编辑代码

### 多仓库检出并行工作

Anthropic 工程师的常见做法：

1. **创建 3-4 个 git 检出**在不同文件夹
2. **在不同终端标签页打开每个文件夹**
3. **在每个文件夹启动 Claude**执行不同任务
4. **循环检查**进度并批准/拒绝权限请求

### Git Worktrees 优化

Git worktrees 允许从同一仓库检出多个分支到不同目录。每个 worktree 有自己的工作目录和独立文件，同时共享相同的 Git 历史和 reflog。

```
git worktree add ../project-feature-a feature-a
cd ../project-feature-a && claude
```

技巧：

- 使用一致的命名约定
- 每个 worktree 保持一个终端标签页
- macOS iTerm2 用户可设置通知
- 为不同 worktree 使用单独的 IDE 窗口
- 完成后清理：`git worktree remove ../project-feature-a`

### 无头模式与自定义框架

`claude -p`（无头模式）将 Claude Code 程序化集成到更大的工作流中。两种主要模式：

1. **扇出模式**：处理大型迁移或分析
2. **管道模式**：集成到现有数据处理管道

## 总结与展望

Claude Code 代表了 AI 辅助编程向"代理式编程"范式的重要转变。与传统的代码补全工具不同，Claude Code 通过提供接近原始模型访问能力、灵活的工具集成和多实例协作模式，为工程师提供了一个真正的 AI 编程伙伴。

从 Anthropic 内部的实践来看，Claude Code 已经深度改变了软件开发的多个环节——从新人入职、代码审查到日常的 Git 操作。特别值得注意的是，这种"不强加观点"的设计哲学，让每个团队都能根据自己的需求定制工作流，这可能是 AI 工程工具未来发展的重要方向。

<!-- 评注建议：这里可以展望代理式编程的未来，比如多模态输入、更智能的上下文管理、以及 AI 编程助手之间的标准化协议等 -->

随着越来越多的工程师采用这种工作模式，我们正在见证软件开发范式的根本性转变：从"人类编写代码、AI 辅助"到"人类定义意图、AI 实现细节"的新时代。Claude Code 的最佳实践不仅是工具使用指南，更是这个新时代的工程方法论雏形。

---

_致谢：本文基于 Anthropic 工程师 Boris Cherny 的原文编译，感谢 Claude Code 用户社区的创新方法和工作流贡献，特别感谢 Daisy Hollman、Ashwin Bhat、Cat Wu、Sid Bidasaria、Cal Rueb、Nodir Turakulov、Barry Zhang、Drew Hodun 等 Anthropic 工程师的宝贵见解。_