# 深度解析 Claude Agent Skills：基于提示词的元工具架构设计

Anthropic 于今年推出的 Agent Skills 系统，代表了一种独特的 LLM 能力扩展范式。与传统的函数调用或代码执行不同，Skills 通过 **提示词扩展（Prompt Expansion）** 和 **上下文修改（Context Modification）** 来改变 Claude 处理后续请求的方式——而非编写可执行代码。

本文基于 Hanchung Lee 的深度技术分析，从第一性原理出发，完整拆解 Claude Agent Skills 系统的架构设计。我们将以 `skill-creator` 和 `internal-comms` 技能为案例，逐层剖析从文件解析到 API 请求结构，再到 Claude 决策过程的完整生命周期。

<!-- 评注建议：可在此处评论 Anthropic 选择"提示词注入"而非"代码执行"作为能力扩展机制的深层战略意图——这与其一贯的 AI 安全理念高度一致 -->

## 核心发现摘要

在深入技术细节之前，先提炼本文的核心要点：

- **Skills 的本质是提示词模板**，而非可执行代码。它们存储在 `SKILL.md` 文件中，通过 YAML frontmatter 配置元数据
- **Skill 工具（大写 S）是一个元工具**，负责管理所有 skills（小写 s）。它作为独立工具出现在 Claude 的 `tools` 数组中
- **技能选择完全依赖 LLM 推理**，没有算法路由、嵌入匹配或意图分类——决策完全发生在 Claude 的 transformer 前向传播中
- **双重上下文修改机制**：Skills 通过注入指令提示修改 **对话上下文**，同时通过改变工具权限和模型选择修改 **执行上下文**
- **渐进式信息披露（Progressive Disclosure）** 是核心设计原则：先展示最少必要信息让 Claude 做出选择，再在需要时加载完整指令

```ad-tip

本文涉及的关键术语区分：
- **Skill 工具（大写 S）**：位于 Claude tools 数组中的元工具，负责分发和管理所有技能
- **skills（小写 s）**：具体的技能模板，如 `pdf`、`skill-creator`、`internal-comms` 等
- **上下文注入**：通过 `isMeta: true` 标记的隐藏消息向 Claude 注入指令
- **执行上下文修改**：动态改变工具权限、模型选择等运行时参数
```

## Claude Agent Skills 概览

Claude 使用 Skills 来提升执行特定任务的能力。Skills 被定义为包含指令、脚本和资源的文件夹，Claude 可以在需要时加载这些内容。这套系统采用 **声明式、基于提示词** 的方式进行技能发现和调用——AI 模型（Claude）根据系统提示中呈现的文本描述来决定是否调用某个技能。

这里需要特别强调的是：**在代码层面不存在算法化的技能选择或 AI 驱动的意图检测**。决策完全发生在 Claude 的推理过程中，基于系统提供的技能描述。

![](http://cdn.cs-magic.cn/picgo/20251126235802494.png)


那么 Skills 到底是什么？

Skills **不是**可执行代码。它们不运行 Python 或 JavaScript，背后没有 HTTP 服务器或函数调用。它们也没有被硬编码进 Claude 的系统提示词中——Skills 存在于 API 请求结构的独立部分。

Skills **是**专门的提示词模板，用于向对话上下文注入领域特定的指令。当一个 skill 被调用时，它会同时修改对话上下文（通过注入指令提示）和执行上下文（通过改变工具权限，可能还会切换模型）。每个 skill 作为动态添加项出现在 Claude 可见的工具模式中，而非直接执行操作。

<!-- 评注建议：这里可以深入评论"提示词即程序"（Prompt as Program）的范式转换意义——Skills 本质上是用自然语言编写的"子程序" -->

当用户发送请求时，Claude 会收到三样东西：用户消息、可用工具（Read、Write、Bash 等）以及 Skill 工具。Skill 工具的描述包含一个格式化列表，汇总了所有可用技能的 `name`、`description` 等字段。Claude 读取这个列表，使用其原生的语言理解能力将用户意图与技能描述进行匹配。

例如，当你说"帮我创建一个日志技能"时，Claude 看到 `internal-comms` 技能的描述（"当用户想使用公司格式编写内部通信时"），识别出匹配，然后调用 Skill 工具并传入 `command: "internal-comms"`。

技能选择机制在代码层面 **没有任何算法路由或意图分类**。Claude Code 不使用嵌入、分类器或模式匹配来决定调用哪个技能。相反，系统将所有可用技能格式化为文本描述，嵌入到 Skill 工具的提示词中，让 Claude 的语言模型做出决定。

这是纯粹的 LLM 推理——没有正则表达式、没有关键词匹配、没有基于机器学习的意图检测。决策发生在 Claude 通过 transformer 的前向传播中，而非应用代码中。

### Tools 与 Skills 的核心区别

以下表格帮助理解传统工具与 Skills 的本质差异：

|维度|传统工具|Skills|
|---|---|---|
|**执行模型**|同步、直接执行|提示词扩展|
|**目的**|执行特定操作|引导复杂工作流|
|**返回值**|即时结果|对话上下文 + 执行上下文变更|
|**示例**|`Read`、`Write`、`Bash`|`internal-comms`、`skill-creator`|
|**并发安全**|通常安全|非并发安全|
|**类型**|多种|始终为 `"prompt"`|

## 构建 Agent Skills

现在让我们以 Anthropic 技能仓库中的 [`skill-creator` 技能](https://github.com/anthropics/skills/tree/main/skill-creator) 为案例，深入探讨如何构建 Skills。

```ad-tip

**Skill = 提示词模板 + 对话上下文注入 + 执行上下文修改 + 可选的数据文件和脚本**
```

每个 Skill 都定义在一个名为 `SKILL.md`（不区分大小写）的 Markdown 文件中，可以附带存储在 `/scripts`、`/references` 和 `/assets` 目录下的资源文件。这些资源可以是 Python 脚本、Shell 脚本、字体定义、模板等。

![](http://cdn.cs-magic.cn/picgo/20251126235927015.png)

Skills 从多个来源被发现和加载：Claude Code 会扫描用户设置（`~/.config/claude/skills/`）、项目设置（`.claude/skills/`）、插件提供的技能以及内置技能来构建可用技能列表。

构建 Skills 最重要的概念是 **渐进式披露（Progressive Disclosure）**——只展示足够的信息帮助智能体决定下一步做什么，然后在需要时揭示更多细节：

1. **披露 Frontmatter**：最小化信息（name、description、license）
2. **如果选择了某个 skill**：加载 SKILL.md 的完整内容
3. **执行过程中**：按需加载辅助的 assets、references 和 scripts

### 编写 SKILL.md

`SKILL.md` 是技能提示词的核心，它是一个遵循两部分结构的 Markdown 文件——frontmatter 和正文内容。Frontmatter 配置技能 **如何** 运行（权限、模型、元数据），而 Markdown 正文告诉 Claude **做什么**。

```
┌─────────────────────────────────────┐
│ 1. YAML Frontmatter (Metadata)      │ ← 配置
│    ---                              │
│    name: skill-name                 │
│    description: Brief overview      │
│    allowed-tools: "Bash, Read"      │
│    version: 1.0.0                   │
│    ---                              │
├─────────────────────────────────────┤
│ 2. Markdown Content (Instructions)  │ ← Claude 的提示词
│                                     │
│    Purpose explanation              │
│    Detailed instructions            │
│    Examples and guidelines          │
│    Step-by-step procedures          │
└─────────────────────────────────────┘
```

### Frontmatter 字段详解

以 `skill-creator` 为例，其 frontmatter 如下：

```yaml
---
name: skill-creator
description: Guide for creating effective skills. This skill should be used when users want to create a new skill (or update an existing skill) that extends Claude's capabilities with specialized knowledge, workflows, or tool integrations.
license: Complete terms in LICENSE.txt
---
```

![](http://cdn.cs-magic.cn/picgo/20251126235911199.png)

**`name`（必需）**：技能名称，用作 Skill 工具中的 `command` 参数。

**`description`（必需）**：技能功能的简要摘要。这是 Claude 用来决定何时调用技能的主要信号。示例中的描述明确指出"当用户想创建新技能时应使用此技能"——这种清晰的、面向行动的语言有助于 Claude 将用户意图与技能能力进行匹配。系统会自动在描述后附加来源信息（如 `"(plugin:skills)"`），以区分来自不同来源的技能。

**`allowed-tools`（可选）**：定义技能可以无需用户批准即可使用的工具，以逗号分隔的字符串形式解析为工具名称数组。可以使用通配符限定权限范围，如 `Bash(git:*)` 只允许 git 子命令，而 `Bash(npm:*)` 允许所有 npm 操作。

```yaml
# ✅ 特定 git 命令
allowed-tools: "Bash(git status:*),Bash(git diff:*),Bash(git log:*),Read,Grep"

# ✅ 仅文件操作
allowed-tools: "Read,Write,Edit,Glob,Grep"

# ❌ 不必要的攻击面
allowed-tools: "Bash,Read,Write,Edit,Glob,Grep,WebSearch,Task,Agent"
```

**`model`（可选）**：定义技能使用的模型，默认继承用户会话中的当前模型。对于代码审查等复杂任务，技能可以请求更强大的模型如 Claude Opus。

```yaml
model: "claude-opus-4-20250514"  # 使用特定模型
model: "inherit"                 # 使用会话当前模型（默认）
```

**`when_to_use`（未文档化）**：此字段在代码库中广泛出现，但 **未在任何官方 Anthropic 文档中记录**。可能是已弃用、实验性或计划中的功能。建议依赖详细的 `description` 字段，避免在生产技能中使用。

**`disable-model-invocation`（可选）**：布尔值，当设为 true 时，阻止 Claude 通过 Skill 工具自动调用该技能。技能将被排除在展示给 Claude 的列表之外，只能由用户通过 `/skill-name` 手动调用——适用于危险操作、配置命令或需要显式用户控制的交互式工作流。

**`mode`（可选）**：布尔值，将技能标记为修改 Claude 行为或上下文的"模式命令"。设为 true 时，技能会出现在技能列表顶部的特殊"Mode Commands"部分——适用于 debug-mode、expert-mode 或 review-mode 等建立特定操作上下文的技能。

### 提示词正文内容

Frontmatter 之后是 Markdown 正文——当技能被调用时 Claude 收到的实际提示词。这里定义技能的行为、指令和工作流。编写有效技能提示词的关键是 **保持聚焦** 并 **使用渐进式披露**：在 SKILL.md 中提供核心指令，为详细内容引用外部文件。

推荐的内容结构：

```markdown
---
# Frontmatter
---

# [简要目的陈述 - 1-2 句]

## Overview
[技能功能、使用场景、提供的能力]

## Prerequisites
[所需工具、文件或上下文]

## Instructions

### Step 1: [第一个操作]
[祈使句指令]
[必要时的示例]

### Step 2: [下一个操作]
[祈使句指令]

## Output Format
[如何组织结果]

## Error Handling
[失败时的处理方式]

## Resources
[引用 scripts/、references/、assets/ 中的资源]
```

编写提示词正文的最佳实践：

- 保持在 5,000 词（约 800 行）以内，避免上下文过载
- 使用祈使句（"分析代码..."）而非第二人称（"你应该分析..."）
- 为详细内容引用外部文件，而非嵌入所有内容
- 使用 `{baseDir}` 作为路径，**永远不要硬编码绝对路径**

```
❌ Read /home/user/project/config.json
✅ Read {baseDir}/config.json
```

### 资源捆绑

Skills 的强大之处在于可以在 SKILL.md 旁边捆绑支持资源。标准结构使用三个目录：

```
my-skill/
├── SKILL.md              # 核心提示词和指令
├── scripts/              # 可执行的 Python/Bash 脚本
├── references/           # 加载到上下文的文档
└── assets/               # 模板和二进制文件
```

**`scripts/` 目录**：包含 Claude 通过 Bash 工具运行的可执行代码——自动化脚本、数据处理器、验证器或代码生成器。

**`references/` 目录**：存储 Claude 在被引用时读入上下文的文档。这是文本内容——Markdown 文件、JSON 模式、配置模板等。

**`assets/` 目录**：包含 Claude 通过路径引用但不加载到上下文的模板和二进制文件。HTML 模板、CSS 文件、图像、配置样板或字体等。

`references/` 和 `assets/` 的关键区别：

- **references/**：通过 Read 工具加载到 Claude 上下文的文本内容，消耗上下文 token
- **assets/**：仅通过路径引用，不加载到上下文

<!-- 评注建议：这里可以评论"上下文窗口经济学"——references 和 assets 的区分体现了对有限上下文资源的精细化管理思想 -->

### 常见技能模式

理解常见模式有助于设计有效的技能。

**模式 1：脚本自动化**

用于需要多个命令或确定性逻辑的复杂操作。将计算任务卸载到 `scripts/` 目录中的 Python 或 Bash 脚本。

![Claude Skill Script Automation](https://claude.ai/assets/img/2025-10-26/09-script-automation.png)

```yaml
allowed-tools: "Bash(python {baseDir}/scripts/*:*), Read, Write"
```

**模式 2：读取-处理-写入**

最简单的模式——读取输入、按指令转换、写入输出。适用于格式转换、数据清理或报告生成。

![Claude Skill Read Process Write](https://claude.ai/assets/img/2025-10-26/10-read-process-write.png)

**模式 3：搜索-分析-报告**

用于代码库分析和模式检测。使用 Grep 搜索模式，读取匹配文件获取上下文，分析发现，生成结构化报告。

![Claude Skill Search Analyze Report](https://claude.ai/assets/img/2025-10-26/06-search-analyze-report.png)

**模式 4：命令链执行**

用于有依赖关系的多步骤操作。执行一系列命令，每个步骤都依赖前一步的成功。常见于类 CI/CD 工作流。

![Claude Skill Command Chain Execution](https://claude.ai/assets/img/2025-10-26/05-command-chain-execution.png)

### 高级模式

**向导式多步骤工作流**：将复杂任务分解为离散步骤，每个阶段之间需要显式用户确认。适用于设置向导、配置工具或引导式流程。

**基于模板的生成**：加载模板、填充占位符、写入结果。常用于报告生成、样板代码创建或文档。

**迭代细化**：先进行广泛分析，然后对识别出的问题进行逐步深入。适用于代码审查、安全审计或质量分析。

**上下文聚合**：从多个来源收集信息，综合成连贯的整体画面。适用于项目摘要、依赖分析或影响评估。

## Agent Skills 内部架构

了解了概览和构建过程后，现在来深入研究 Skills 在底层是如何工作的。Skills 系统通过元工具架构运作，其中名为 `Skill` 的工具作为所有单独技能的容器和调度器。这一设计从根本上将技能与传统工具在实现和目的上区分开来。

```ad-tip

Skill 工具是管理所有技能的元工具。它不直接执行操作，而是注入指令并修改执行环境。
```

### Skills 对象设计

传统工具如 `Read`、`Bash` 或 `Write` 执行离散操作并返回即时结果。Skills 的运作方式根本不同——它们不是直接执行操作，而是将全面的指令集注入对话历史，并动态修改 Claude 的执行环境。

![Claude Skill Execution Flow](https://claude.ai/assets/img/2025-10-26/08-claude-skill-execution-flow.png)

|特性|普通工具|Skill 工具|
|---|---|---|
|**本质**|直接动作执行器|提示词注入 + 上下文修改器|
|**消息角色**|assistant → tool_use<br>user → tool_result|assistant → tool_use Skill<br>user → tool_result<br>user → skill prompt ← 注入！|
|**复杂度**|简单（3-4 条消息）|复杂（5-10+ 条消息）|
|**上下文**|静态|动态（每轮修改）|
|**持久性**|仅工具交互|工具交互 + 技能提示词|
|**Token 开销**|最小（约 100 tokens）|显著（每轮 1,500+ tokens）|

复杂度是显著的。普通工具生成简单的消息交换——一个 assistant 工具调用后跟一个 user 结果。Skills 注入多条消息，在动态修改的上下文中运作，并承担显著的 token 开销来提供引导 Claude 行为的专门指令。

### Skill 元工具的结构

```javascript
Pd = {
  name: "Skill",  // 工具名称常量

  inputSchema: {
    command: string  // 例如 "pdf", "skill-creator"
  },

  outputSchema: {
    success: boolean,
    commandName: string
  },

  // 🔑 关键字段：动态生成技能列表
  prompt: async () => fN2(),

  // 验证和执行
  validateInput: async (input, context) => { /* 5 种错误码 */ },
  checkPermissions: async (input, context) => { /* allow/deny/ask */ },
  call: async *(input, context) => { /* yields messages + context modifier */ }
}
```

`prompt` 字段将 Skill 工具与 `Read` 或 `Bash` 等其他工具区分开来——后者有静态描述。Skill 工具使用动态提示词生成器，在运行时通过聚合所有可用技能的名称和描述来构建其描述。这实现了 **渐进式披露**——系统只将最少的元数据（frontmatter 中的技能名称和描述）加载到 Claude 的初始上下文，提供足够的信息让模型决定哪个技能匹配用户意图。完整的技能提示词只在 Claude 做出选择后才加载，防止上下文膨胀的同时保持可发现性。

<!-- 评注建议：动态 prompt 生成器的设计非常精妙——可以评论这种"懒加载"思想在 LLM 应用架构中的普适价值 -->

与 ChatGPT 等某些助手将工具放在系统提示词中不同，Claude **agent skills 不在系统提示词中**。它们作为 Skill 工具描述的一部分存在于 `tools` 数组中。单独技能的名称作为 Skill 元工具输入模式的 `command` 字段呈现。

以下是实际的 API 请求结构：

```json
{
  "model": "claude-sonnet-4-5-20250929",
  "system": "You are Claude Code, Anthropic's official CLI...",
  "messages": [
    {"role": "user", "content": "Help me create a new skill"}
  ],
  "tools": [
    {
      "name": "Skill",
      "description": "Execute a skill...\n\n<skills_instructions>...\n\n<available_skills>\n...",
      "input_schema": {
        "type": "object",
        "properties": {
          "command": {
            "type": "string",
            "description": "The skill name (no arguments)"
          }
        }
      }
    },
    {
      "name": "Bash",
      "description": "Execute bash commands..."
    },
    {
      "name": "Read"
    }
  ]
}
```

`<available_skills>` 部分存在于 Skill 工具的描述中，并为每个 API 请求重新生成。系统通过聚合当前加载的技能（来自用户和项目配置、插件提供的技能以及内置技能）动态构建此列表，受默认 15,000 字符的 token 预算限制。这一预算约束迫使技能作者编写简洁的描述，并确保工具描述不会压垮模型的上下文窗口。

### 对话和执行上下文注入设计

大多数 LLM API 支持可以理论上承载系统提示词的 `role: "system"` 消息。事实上，OpenAI 的 ChatGPT 在其系统提示词中承载了默认工具，包括用于记忆的 `bio`、用于任务调度的 `automations`、用于控制画布的 `canmore`、用于图像生成的 `img_gen`、`file_search`、`python` 和用于互联网搜索的 `web`。最终，工具提示词占据了其系统提示词中约 90% 的 token 数量。如果有大量工具和/或技能需要加载到上下文中，这种方式效率很低。

然而，系统消息有不同的语义，使其不适合用于技能。系统消息设置在整个对话中持久存在的全局上下文，以比用户指令更高的权威影响所有后续轮次。

Skills 需要 **临时的、有范围的行为**。`skill-creator` 技能应该只影响与技能创建相关的任务，而不是将 Claude 永久转变为整个会话期间的 PDF 专家。使用带有 `isMeta: true` 的 `role: "user"` 使技能提示词作为用户输入呈现给 Claude，保持其临时性和局限于当前交互。技能完成后，对话返回正常的对话上下文和执行上下文，没有残留的行为修改。

### 双消息架构：isMeta 标志的精妙设计

普通工具如 `Read`、`Write` 或 `Bash` 有简单的通信模式。但 Skills 的运作方式根本不同——它们不是执行离散操作并返回结果，而是注入全面的指令集来修改 Claude 推理和处理任务的方式。这带来了普通工具从未面临的设计挑战：用户需要了解哪些技能正在运行以及它们在做什么，同时 Claude 需要详细的、可能冗长的指令来正确执行技能。

解决方案是将这两个通信渠道分离为具有不同可见性规则的独立消息。

Skills 系统在每条消息上使用 `isMeta` 标志来控制它是否出现在用户界面中：

- 当 `isMeta: false`（或省略时默认为 false）：消息在用户看到的对话记录中渲染
- 当 `isMeta: true`：消息作为 Claude 对话上下文的一部分发送到 Anthropic API，但从不出现在 UI 中

当技能执行时，系统向对话历史注入 **两条独立的用户消息**：

**消息 1（元数据，可见）**：

```xml
<command-message>The "pdf" skill is loading</command-message>
<command-name>pdf</command-name>
<command-args>report.pdf</command-args>
```

这条消息保持故意简洁——通常 50 到 200 个字符。XML 标签使前端能够以特殊格式渲染它。

**消息 2（技能提示词，隐藏）**：

```markdown
You are a PDF processing specialist.

Your task is to extract text from PDF documents using the pdftotext tool.

## Process

1. Validate the PDF file exists
2. Run pdftotext command to extract text
3. Read the output file
4. Present the extracted text to the user

## Tools Available

You have access to:
- Bash(pdftotext:*) - For running pdftotext command
- Read - For reading extracted text
- Write - For saving results if needed

Base directory: /path/to/skill
User arguments: report.pdf
```

典型的技能提示词运行 500 到 5,000 词，提供全面的指导来转变 Claude 的行为。通过 `isMeta: true`，整个提示词被发送到 API，但从不杂乱用户的对话记录。

|方面|元数据消息|技能提示词消息|
|---|---|---|
|**受众**|人类用户|Claude（AI）|
|**目的**|状态/透明度|指令/引导|
|**长度**|约 50-200 字符|约 500-5,000 词|
|**格式**|结构化 XML|自然语言 Markdown|
|**可见性**|应该可见|应该隐藏|
|**内容**|"正在发生什么？"|"如何做？"|

<!-- 评注建议：双消息架构是一个值得深入评论的工程设计——它优雅地解决了"透明度"与"简洁性"的矛盾，体现了对用户体验的深思熟虑 -->

## 案例研究：执行生命周期

现在让我们通过一个假设的 `pdf` 技能作为案例，逐步分析当用户说"从 report.pdf 提取文本"时发生的完整执行流程。

![Claude Skill Execution Flow](https://claude.ai/assets/img/2025-10-26/07-claude-skill-sequence-diagram.png)

### 阶段 1：发现与加载（启动时）

当 Claude Code 启动时，它会扫描技能：

```javascript
async function getAllCommands() {
  // 并行从所有来源加载
  let [userCommands, skillsAndPlugins, pluginCommands, builtins] =
    await Promise.all([
      loadUserCommands(),      // ~/.claude/commands/
      loadSkills(),            // .claude/skills/ + plugins
      loadPluginCommands(),    // 插件定义的命令
      getBuiltinCommands()     // 硬编码命令
    ]);

  return [...userCommands, ...skillsAndPlugins, ...pluginCommands, ...builtins]
    .filter(cmd => cmd.isEnabled());
}
```

对于 pdf 技能，这会产生：

```javascript
{
  type: "prompt",
  name: "pdf",
  description: "Extract text from PDF documents (plugin:document-tools)",
  whenToUse: "When user wants to extract or process text from PDF files",
  allowedTools: ["Bash(pdftotext:*)", "Read", "Write"],
  model: undefined,  // 使用会话模型
  isSkill: true,
  disableModelInvocation: false,
  promptContent: "You are a PDF processing specialist..."
}
```

### 阶段 2：用户请求与技能选择

用户发送请求："从 report.pdf 提取文本"。Claude 收到此消息以及 tools 数组中的 Skill 工具。

技能必须在 frontmatter 中有 `description` **或** `when_to_use`，否则会被过滤掉。每个技能被格式化到 `<available_skills>` 部分：

```
"pdf": Extract text from PDF documents - When user wants to extract or process text from PDF files
```

Claude 的决策过程（假设的内部推理）：

```
内部推理：
- 用户想"从 report.pdf 提取文本"
- 这是一个 PDF 处理任务
- 查看可用技能...
- "pdf": Extract text from PDF documents - When user wants to extract or process text from PDF files
- 匹配！用户想从 PDF 提取文本
- 决定：调用 Skill 工具，command="pdf"
```

这里 **没有算法匹配**。没有词法匹配。没有语义匹配。没有搜索。这是纯粹的 LLM 推理，基于技能描述做出决策。完成后，Claude 返回工具使用：

```json
{
  "type": "tool_use",
  "id": "toolu_123abc",
  "name": "Skill",
  "input": {
    "command": "pdf"
  }
}
```

### 阶段 3：Skill 工具执行

Skill 工具现在执行。它进行验证（5 种错误码检查）、权限检查（deny/allow/ask）、文件加载，并准备执行上下文修改。

核心执行逻辑：

```javascript
async *call({ command }, context) {
  const skillName = command.trim().replace(/^\//, "");
  const skill = getSkill(skillName, allSkills);

  // 加载技能提示词
  const promptContent = await skill.getPromptForCommand("", context);

  // 生成元数据标签
  const metadata = [
    `<command-message>The "${skill.userFacingName()}" skill is loading</command-message>`,
    `<command-name>${skill.userFacingName()}</command-name>`
  ].join('\n');

  // 创建消息
  const messages = [
    { type: "user", content: metadata },  // 对用户可见
    { type: "user", content: promptContent, isMeta: true }  // 对用户隐藏，对 Claude 可见
  ];

  // 提取配置
  const allowedTools = skill.allowedTools || [];
  const modelOverride = skill.model;

  // 返回结果和执行上下文修改器
  yield {
    type: "result",
    data: { success: true, commandName: skillName },
    newMessages: messages,

    // 🔑 执行上下文修改函数
    contextModifier(context) {
      // 注入允许的工具
      // 覆盖模型（如果指定）
      return modified;
    }
  };
}
```

### 阶段 4：发送到 API（Turn 1 完成）

系统构建完整的消息数组发送到 Anthropic API：

```javascript
{
  model: "claude-sonnet-4-5-20250929",
  messages: [
    {
      role: "user",
      content: "Extract text from report.pdf"
    },
    {
      role: "assistant",
      content: [
        {
          type: "tool_use",
          id: "toolu_123abc",
          name: "Skill",
          input: { command: "pdf" }
        }
      ]
    },
    {
      role: "user",
      content: "<command-message>The \"pdf\" skill is loading</command-message>\n<command-name>pdf</command-name>"
      // isMeta: false (default) - 在 UI 中可见
    },
    {
      role: "user",
      content: "You are a PDF processing specialist...\n\n## Process\n1. Validate PDF exists\n2. Run pdftotext...",
      isMeta: true  // 对 UI 隐藏，发送到 API
    },
    {
      role: "user",
      content: {
        type: "command_permissions",
        allowedTools: ["Bash(pdftotext:*)", "Read", "Write"],
        model: undefined
      }
    }
  ]
}
```

![Turn 1 Completion](https://claude.ai/assets/img/2025-10-26/11-turn-1-completion.png)

执行上下文修改器被应用，预先批准 `Bash(pdftotext:*)`、`Read` 和 `Write` 用于后续工具调用。请求发送到 Anthropic API。这完成了技能执行。如果是普通工具，我们就完成了。然而，技能不同——agent skill 只是注入了对话上下文和执行上下文。这意味着我们仍然需要用所有这些注入的上下文调用 Claude agent 来完成用户的请求！

### 阶段 5：Bash 工具执行（带有 Skill 上下文的工具使用！）

Claude 收到带有注入对话上下文的 API 响应。技能提示词已转变了 Claude 的行为，为其提供了：

- 专门的 PDF 处理指令（对话上下文）
- 预先批准访问 `Bash(pdftotext:*)`、`Read` 和 `Write` 工具（执行上下文）
- 清晰的工作流程（对话上下文）

Claude 处理上下文并遵循 pdf 技能的工作流：

```
I'll extract text from report.pdf. Let me process the file.

[Following pdf skill's instructions]
1. Validate that report.pdf exists
2. Run pdftotext command to extract text
3. Read the output file
4. Present the extracted text to you
```

Claude 使用 Bash 工具（预先批准，不需要用户提示）：

```json
{
  "type": "tool_use",
  "id": "toolu_456def",
  "name": "Bash",
  "input": {
    "command": "pdftotext report.pdf output.txt",
    "description": "Extract text from PDF using pdftotext"
  }
}
```

Bash 工具成功执行，返回结果。Claude 然后使用 Read 工具读取输出文件，并将提取的文本呈现给用户。技能通过注入指令到对话上下文并修改执行上下文中的工具权限，成功引导 Claude 完成了专门的 PDF 提取工作流。

## 总结与展望

Claude Code 中的 Skills 是 **基于提示词的对话和执行上下文修改器**，通过元工具架构工作。

### 核心要点回顾

1. Skills 是 `SKILL.md` 文件中的 **提示词模板**，而非可执行代码
2. **Skill 工具**（大写 S）是 tools 数组中的元工具，管理单独的技能，不在系统提示词中
3. Skills 通过注入指令提示 **修改对话上下文**（通过 `isMeta: true` 消息）
4. Skills 通过改变工具权限和模型选择 **修改执行上下文**
5. 选择通过 **LLM 推理** 发生，而非算法匹配
6. 工具权限通过执行上下文修改 **限定在技能执行范围内**
7. 每次调用注入 **两条用户消息**——一条用于用户可见的元数据，一条用于发送到 API 的隐藏指令

### 设计的优雅之处

通过将专门知识视为 _修改对话上下文的提示词_ 和 _修改执行上下文的权限_，而非 _执行的代码_，Claude Code 实现了传统函数调用难以达到的灵活性、安全性和可组合性。

<!-- 评注建议：这里是全文的黄金评注位置。可以从三个维度展开：1）这种架构对 AI 安全的深远意义——通过提示词而非代码扩展能力，本质上限制了潜在的攻击面；2）对开发者生态的影响——降低了创建"AI 原生插件"的门槛；3）对 LLM 应用架构设计的启示——"提示词即接口"的范式值得更广泛地探索 -->

这套设计体现了 Anthropic 在 AI 系统工程上的深思熟虑——在赋予模型更强能力的同时，通过精细的上下文控制和权限管理来保持安全边界。对于正在构建 LLM 应用的开发者而言，Skills 架构提供了一个值得深入学习的参考范式。

## 参考资料

- [Introducing Agent Skills](https://www.anthropic.com/news/skills)
- [Equipping Agents for the Real World with Agent Skills](https://www.anthropic.com/engineering/equipping-agents-for-the-real-world-with-agent-skills)
- [Claude Code Documentation](https://docs.claude.com/en/docs/claude-code/overview)
- [Anthropic API Reference](https://docs.anthropic.com/en/api/messages)
- [Official Documented Frontmatter Fields](https://docs.claude.com/en/docs/agents-and-tools/agent-skills/overview#skill-structure)
- [Internal Comms Skill](https://github.com/anthropics/skills/tree/main/internal-comms)
- [Skill Creator Skill](https://github.com/anthropics/skills/tree/main/skill-creator)

```bibtex
@article{
    leehanchung_claude_skills,
    author = {Lee, Hanchung},
    title = {Claude Agent Skills: A First Principles Deep Dive},
    year = {2025},
    month = {10},
    day = {26},
    howpublished = {\url{https://leehanchung.github.io}},
    url = {https://leehanchung.github.io/blogs/2025/10/26/claude-skills-deep-dive/}
}
```