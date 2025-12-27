---
title: Anthropic API 兼容和 Claude Code 配置
slug: anthropic-api-claude-code-1766481470191
source: https://developer.qiniu.com/aitokenapi/13085/claude-code-configuration-instructions
datetime: 2025-12-23T09:17:50.191Z
---

[AI 大模型推理](/aitokenapi) > 最佳实践 > Anthropic API 兼容和 Claude Code 配置🪜

# Anthropic API 兼容和 Claude Code 配置🪜

最近更新时间: 2025-12-01 10:51:44

-   [前置要求](#1)
-   [接入教程](#2)
-   [高级配置](#3)
-   [故障排除](#4)
-   [总结](#5)

`Claude Code` 是 Anthropic 推出的一款专注于 `AI Coding` 的 Agent 工具，默认由 Claude 系列大模型驱动。它能够为开发者提供以下核心功能：

-   **实时代码建议**：智能代码补全和优化建议
-   **代码解释与优化**：深度分析代码逻辑，提供性能改进方案
-   **多语言支持**：支持主流编程语言如 Python、JavaScript、Java、Go 等
-   **IDE 集成**：无缝集成 VS Code、IntelliJ IDEA 等主流开发环境
-   **自然语言交互**：通过对话方式进行代码开发和问题解决

🪜七牛云 AI 大模型推理服务API `https://api.qnaigc.com` 也兼容了 Anthropic API协议，使用户可以为 Claude Code 配置更便宜、更具性价比的其他大模型，享受Code带来的强大 AI Coding功能。

# 前置要求

-   七牛云账号
-   Node.js 环境（版本 >= 18.0）

# 接入教程

## 第一步：获取认证信息

### 1\. 获取 API Key

-   访问：[https://portal.qiniu.com/ai-inference/api-key](https://portal.qiniu.com/ai-inference/api-key)
-   登录您的七牛云账号
-   创建或复制现有的 API Key

### 2\. 服务端点（BaseURL）

拷贝

`   1.  https://api.qnaigc.com        `

**注意**：请妥善保管您的 API Key，不要在代码中硬编码或提交到版本控制系统。

## 第二步：安装 Claude Code

拷贝

`   1.  # 通过 npm 全局安装（官方推荐）      2.  npm install -g @anthropic-ai/claude-code        `

## 第三步：配置认证信息

Claude Code 支持两种配置方式：settings.json 文件配置（推荐）和环境变量配置。

### 方式一：使用 settings.json 配置（推荐）⭐

使用 `settings.json` 配置文件是 Claude Code 官方推荐的配置方式，相比环境变量更加灵活和易于管理。

#### 1\. 创建配置文件

创建全局配置文件 `~/.claude/settings.json`，适用于所有项目：

拷贝

`   1.  mkdir -p ~/.claude      2.  cat > ~/.claude/settings.json << 'EOF'      3.  {      4.    "env": {      5.      "ANTHROPIC_AUTH_TOKEN": "sk-your-api-key-here",      6.      "ANTHROPIC_BASE_URL": "https://api.qnaigc.com"      7.    },      8.    "permissions": {      9.      "deny": [      10.        "Read(./.env)",      11.        "Read(./.env.*)",      12.        "Read(./secrets/**)"      13.      ]      14.    },      15.    "companyAnnouncements": [      16.      "您正在使用七牛云 AI 大模型推理服务 🚀"      17.    ]      18.  }      19.  EOF        `

**注意**：请将 `sk-your-api-key-here` 替换为您从七牛云获取的真实 API Key。

#### 2\. 认证配置项说明

| 配置项 | 说明 | 必填 | 示例值 |
| --- | --- | --- | --- |
| `ANTHROPIC_AUTH_TOKEN` | API 认证密钥（推荐） | 是\* | `"sk-xxxxx"` |
| `ANTHROPIC_API_KEY` | API 认证密钥（备选） | 是\* | `"sk-xxxxx"` |
| `ANTHROPIC_BASE_URL` | API 服务端点 | 是 | `"https://api.qnaigc.com"` |

**注意**：`ANTHROPIC_AUTH_TOKEN` 和 `ANTHROPIC_API_KEY` 二选一配置，不可同时设置。

### 方式二：使用环境变量配置

如果您更习惯使用环境变量，可以在 shell 配置文件（如 `~/.zshrc` 或 `~/.bashrc`）中添加：

拷贝

`   1.  # 认证配置      2.  export ANTHROPIC_AUTH_TOKEN="sk-your-api-key-here"      3.  # 或使用 ANTHROPIC_API_KEY（二选一）      4.  # export ANTHROPIC_API_KEY="sk-your-api-key-here"       6.  # 服务端点配置      7.  export ANTHROPIC_BASE_URL="https://api.qnaigc.com"        `

配置完成后需要重新加载配置文件：

拷贝

`   1.  source ~/.zshrc  # 或 source ~/.bashrc        `

**注意**：请将 `sk-your-api-key-here` 替换为您从七牛云获取的真实 API Key。

## 第四步：配置模型设置（可选）

Claude Code 默认会使用 Claude 系列模型。如果您想使用七牛云提供的其他模型（如 Kimi、DeepSeek 等），可以通过以下方式配置。

### 方式一：通过 settings.json 配置

在 `~/.claude/settings.json` 的 `env` 部分添加模型配置：

拷贝

`   1.  {      2.    "env": {      3.      "ANTHROPIC_AUTH_TOKEN": "sk-your-api-key-here",      4.      "ANTHROPIC_BASE_URL": "https://api.qnaigc.com",      5.      "ANTHROPIC_MODEL": "moonshotai/kimi-k2-thinking",      6.      "ANTHROPIC_DEFAULT_SONNET_MODEL": "moonshotai/kimi-k2-thinking",      7.      "ANTHROPIC_DEFAULT_HAIKU_MODEL": "moonshotai/kimi-k2-thinking",      8.      "ANTHROPIC_SMALL_FAST_MODEL": "moonshotai/kimi-k2-thinking"      9.    }      10.  }        `

### 方式二：通过环境变量配置

在 shell 配置文件中添加：

拷贝

`   1.  # 模型配置      2.  export ANTHROPIC_MODEL="moonshotai/kimi-k2-thinking"      3.  export ANTHROPIC_DEFAULT_SONNET_MODEL="moonshotai/kimi-k2-thinking"      4.  export ANTHROPIC_DEFAULT_HAIKU_MODEL="moonshotai/kimi-k2-thinking"      5.  export ANTHROPIC_SMALL_FAST_MODEL="moonshotai/kimi-k2-thinking"        `

### 模型配置项说明

| 配置项 | 说明 | 使用场景 |
| --- | --- | --- |
| `ANTHROPIC_MODEL` | 默认主模型 | 常规任务 |
| `ANTHROPIC_DEFAULT_SONNET_MODEL` | 默认 Sonnet 模型 | 复杂推理任务 |
| `ANTHROPIC_DEFAULT_HAIKU_MODEL` | 简单任务模型（新版） | 简单快速任务 |
| `ANTHROPIC_SMALL_FAST_MODEL` | 简单任务模型（兼容旧版） | 简单快速任务 |

### 支持的模型列表

访问 [七牛云 AI 推理模型广场](https://www.qiniu.com/ai/models) 查看：

-   最新上线的模型列表
-   各模型的详细参数和定价
-   模型的能力特点和适用场景

**常用模型推荐**：

-   **Kimi 系列**：`moonshotai/kimi-k2-thinking` - 适合复杂推理和长文本处理
-   **DeepSeek 系列**：`deepseek/deepseek-chat` - 性价比高，适合日常开发
-   **Qwen 系列**：`qwen/qwen-max` - 综合能力强，中文表现优秀

## 第五步：验证配置

启动 Claude Code 并使用 `/status` 命令验证配置：

拷贝

`   1.  claude      2.  # 在 Claude Code 中输入      3.  /status        `

检查以下配置项：

-   ✅ Base URL 显示为 `https://api.qnaigc.com`
-   ✅ API Key 已正确配置（显示为已设置状态）
-   ✅ 模型配置正确（如已配置）

[![image.png](https://dn-odum9helk.qbox.me/Fs2fNJMBEfzJN2K_7uk_gcNeOLdj)](https://dn-odum9helk.qbox.me/Fs2fNJMBEfzJN2K_7uk_gcNeOLdj)

**常见问题排查**：

-   如果 Base URL 显示错误，检查配置文件或环境变量是否正确
-   如果提示认证失败，确认 API Key 是否有效
-   如果模型配置未生效，尝试重启 Claude Code

## 第六步：启动和使用

### 启动 Claude Code

拷贝

`   1.  claude "使用 HTML 实现一个数独游戏"        `

### 授权访问

首次进入可能需要为 claude code 授予`当前目录`访问权限

[![企业微信截图_fe2dec7a-27fe-487c-b901-5a74b7b2ddab.png](https://dn-odum9helk.qbox.me/FgOmvAOP_TUf2RPSTl57ACI3ZQQX)](https://dn-odum9helk.qbox.me/FgOmvAOP_TUf2RPSTl57ACI3ZQQX)

# 高级配置

## 完整的 settings.json 配置示例

拷贝

`   1.  {      2.    "env": {      3.      // ===== 认证配置 =====      4.      "ANTHROPIC_AUTH_TOKEN": "sk-your-api-key-here",      5.      "ANTHROPIC_BASE_URL": "https://api.qnaigc.com",       7.      // ===== 模型配置 =====      8.      "ANTHROPIC_MODEL": "moonshotai/kimi-k2-thinking",      9.      "ANTHROPIC_DEFAULT_SONNET_MODEL": "moonshotai/kimi-k2-thinking",      10.      "ANTHROPIC_DEFAULT_HAIKU_MODEL": "moonshotai/kimi-k2-thinking",      11.      "ANTHROPIC_SMALL_FAST_MODEL": "moonshotai/kimi-k2-thinking"      12.    },       14.    // ===== 其他配置 =====      15.    "companyAnnouncements": [      16.      "您正在使用七牛云 AI 大模型推理服务 🚀"      17.    ]      18.  }        `

## settings.json 配置项完整说明

| 配置项 | 说明 | 示例值 |
| --- | --- | --- |
| **认证配置** |  |  |
| `env.ANTHROPIC_AUTH_TOKEN` | API 认证密钥（推荐） | `"sk-xxxxx"` |
| `env.ANTHROPIC_API_KEY` | API 认证密钥（备选） | `"sk-xxxxx"` |
| `env.ANTHROPIC_BASE_URL` | API 服务端点 | `"https://api.qnaigc.com"` |
| **模型配置** |  |  |
| `env.ANTHROPIC_MODEL` | 默认主模型 | `"moonshotai/kimi-k2-thinking"` |
| `env.ANTHROPIC_DEFAULT_SONNET_MODEL` | 默认 Sonnet 模型 | `"moonshotai/kimi-k2-thinking"` |
| `env.ANTHROPIC_DEFAULT_HAIKU_MODEL` | 简单任务模型（新版） | `"moonshotai/kimi-k2-thinking"` |
| `env.ANTHROPIC_SMALL_FAST_MODEL` | 简单任务模型（兼容旧版） | `"moonshotai/kimi-k2-thinking"` |
| **其他配置** |  |  |
| `companyAnnouncements` | 启动时显示的公告 | `["欢迎信息"]` |

> [完整配置请 Claude Code 参考官网文档](https://code.claude.com/docs/en/settings)

## 权限控制详解

### 1\. 动态 API Key 生成（企业场景）

使用 `apiKeyHelper` 配置动态生成 API Key：

拷贝

`   1.  {      2.    "apiKeyHelper": "/bin/generate_temp_api_key.sh",      3.    "env": {      4.      "CLAUDE_CODE_API_KEY_HELPER_TTL_MS": "3600000"      5.    }      6.  }        `

这对于需要定期轮换 API Key 的企业场景特别有用。

## 日志查看

在运行 Claude Code 时，它会分项目产生 `*.jsonl` 日志到 `~/.claude/projects` 目录下。

使用 `claude-code-log` 可以将日志转化为更可读的 HTML 文件格式：

拷贝

`   1.  # 安装      2.  pip install claude-code-log       4.  # 运行      5.  claude-code-log        `

# 故障排除

## 常见问题

### 1\. 认证失败

**问题**：提示 “Authentication failed” 或 “Invalid API key”

**解决方案**：

-   检查 API Key 是否正确复制（没有多余空格）
-   确认 API Key 在七牛云控制台是否有效
-   验证 `ANTHROPIC_AUTH_TOKEN` 或 `ANTHROPIC_API_KEY` 只配置了一个
-   检查 Base URL 是否正确设置为 `https://api.qnaigc.com`

### 2\. 模型不可用

**问题**：提示 “Model not found” 或模型调用失败

**解决方案**：

-   访问 [七牛云模型广场](https://www.qiniu.com/ai/models) 确认模型名称正确
-   检查账号是否有该模型的使用权限
-   尝试使用默认模型测试（如 `deepseek/deepseek-chat`）
-   使用 `/status` 命令查看当前配置

### 3\. 配置未生效

**问题**：修改配置后没有变化

**解决方案**：

-   重新启动 Claude Code
-   检查配置文件 JSON 格式是否正确（使用 JSON 验证工具）
-   确认配置文件路径正确（`~/.claude/settings.json`）
-   环境变量配置需要 `source ~/.zshrc` 后重启终端

### 4\. 权限被拒绝

**问题**：Claude Code 无法读取文件或执行命令

**解决方案**：

-   检查 `permissions.deny` 是否过于严格
-   使用 `/config` 命令查看当前权限设置
-   调整 `defaultMode` 为 `"ask"` 以临时允许操作
-   在 `permissions.allow` 中明确添加需要的权限

### 5\. 网络连接问题

**问题**：无法连接到 API 服务

**解决方案**：

-   检查网络连接是否正常
-   确认防火墙没有阻止 `https://api.qnaigc.com`
-   尝试 `curl https://api.qnaigc.com` 测试连接
-   检查是否需要配置代理

## 获取帮助

如果以上方法无法解决您的问题，可以通过以下方式获取支持：

-   **七牛云工单系统**：[https://support.qiniu.com/tickets/new](https://support.qiniu.com/tickets/new)
-   **技术文档**：[https://developer.qiniu.com/ai](https://developer.qiniu.com/ai)
-   **开发者社区**：[https://forum.qiniu.com](https://forum.qiniu.com)
-   **技术支持邮箱**：ai-support@qiniu.com

# 总结

通过本教程，您已经学会了：

✅ **认证配置**：如何获取和配置 API Key  
✅ **模型设置**：如何选择和配置不同的模型  
✅ **权限控制**：如何保护敏感文件和限制危险操作  
✅ **最佳实践**：安全、性能和成本优化建议

现在您可以开始使用 Claude Code 进行高效的 AI 辅助编程了！🎉

以上内容是否对您有帮助？

文档反馈 (如有产品使用问题，请 [提交工单](https://support.qiniu.com/tickets/category))

提交