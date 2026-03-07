---
title: Claude 聊天记录获取完全指南（2026 最新）
date: 2026-03-07
status: draft
tags: [Claude, AI, 聊天记录, 教程, 抓包]
---
## 你喂给 AI 的每句话，都值得被保存

你有没有想过一个问题：**你和 AI 的聊天记录，可能比你写过的任何文档都更能代表你的真实水平。**

之前我写过一篇文章叫《[你喂给 AI 的每一句 prompt，本质上都是你专业能力的外化](https://mp.weixin.qq.com/s/u3l3jn7dB0n0b2FVV5R3fA)》，核心观点是：**prompt 的质量 = 你对问题的理解深度**。你怎么提问、怎么追问、怎么纠正 AI 的方向——这些对话痕迹，就是你思维模式的镜像。

所以，聊天记录不只是"历史记录"，它是你的**思维资产**。

但问题来了——你试过导出 Claude 的聊天记录吗？

如果你试过，你就知道：**Claude 官方没有提供任何导出功能。** 虽然 ChatGPT 在设置深处藏了个"Export data"（会把全量数据发到邮箱），但大多数 AI 产品——包括 Claude——只提供了分享链接功能，想要结构化地导出自己的对话数据？不存在的。

![](http://cdn.cs-magic.cn/picgo/20260307174326265.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


这篇文章就是来解决这个问题的。我会按场景分类，把我们摸索出来的所有方案都讲清楚——从最简单的到最硬核的。

---

## 先搞清楚：你用的是哪个 Claude？

这是第一个关键区分。Claude 目前有两大使用环境，聊天记录的存储方式完全不同：

| 环境 | 说明 | 记录存储位置 |
|------|------|------------|
| **Claude Code**（终端/CLI） | 命令行工具，用于编程 | **本地电脑** |
| **Claude App**（网页/桌面/移动端） | 日常对话界面 | **云端服务器** |

Claude App 里又分三个功能模块：

- **Chat**：常规对话（三端同步）
- **Cowork**：协作模式（目前仅 App 内）
- **Code**：App 内的编程模式（目前仅 App 内）

存储位置不同，获取方式就完全不同。下面逐个讲。

---

## 场景一：Claude Code 本地聊天记录

> 难度：⭐ | 数据位置：你的电脑本地

这是最简单的场景。Claude Code 的所有对话都以 JSONL 格式存在你电脑上，不需要任何抓包或黑科技。

### 记录存储位置

```
~/.claude/projects/
```

这个目录下按项目路径组织，每个项目都有对应的 session 日志文件。具体结构：

```
~/.claude/
├── projects/
│   ├── -Users-你的用户名-项目A/
│   │   ├── .session.jsonl          # 当前会话
│   │   ├── sessions/
│   │   │   ├── abc123.jsonl        # 历史会话
│   │   │   └── def456.jsonl
│   │   └── memory/
│   │       └── MEMORY.md           # 项目记忆
│   └── -Users-你的用户名-项目B/
│       └── ...
```

### 如何定位 session 文件

Claude Code 按**项目路径**来组织对话记录，路径中的 `/` 会被替换为 `-`。比如你的项目在 `/Users/mark/projects/my-app`，对应的记录目录就是：

```
~/.claude/projects/-Users-mark-projects-my-app/
```

找到当前项目最新 session 的通用命令：

```bash
# 自动根据当前目录定位最新 session 文件
PROJECT_KEY=$(pwd | sed 's|/|-|g')
ls -t ~/.claude/projects/"$PROJECT_KEY"/*.jsonl | head -1
```

也可以手动浏览所有项目：

```bash
# 列出所有项目
ls ~/.claude/projects/

# 列出某个项目的所有 session（按时间排序）
ls -lt ~/.claude/projects/-Users-mark-projects-my-app/*.jsonl
```

文件名就是 session ID，例如 `21413e22-33b7-4d1b-b9bc-59af2ecf31ea.jsonl`。

想快速预览最近的对话内容？一行搞定：

我们写了一个小工具 [claude-chat-preview](https://www.npmjs.com/package/claude-chat-preview)，一行命令快速预览最近的对话，包括工具调用：

```bash
# 直接运行，无需安装
npx claude-chat-preview

# 指定显示条数
npx claude-chat-preview 20
```

输出效果：

```
Session: 21413e22-33b7-4d1b-b9bc-59af2ecf31ea

U: 帮我重构这个组件

A: [Edit] /src/components/Header.tsx
   [Bash] npm run build

A: 重构完成，把 Header 拆分成了三个子组件 ...

U: 测试一下能不能跑

A: [Bash] npm test
   所有测试通过
```

### 方法一：直接读取 JSONL 文件

最原始但最可靠的方式。每个 `.jsonl` 文件里，每一行都是一个 JSON 对象，记录了完整的对话消息。

```bash
# 查看某个 session 的内容（jq 美化输出）
SESSION=$(ls -t ~/.claude/projects/"$(pwd | sed 's|/|-|g')"/*.jsonl | head -1)
cat "$SESSION" | jq .

# 提取所有用户消息
cat session.jsonl | jq 'select(.type == "user") | .message.content'

# 提取所有 assistant 回复
cat session.jsonl | jq 'select(.type == "assistant") | .message.content'
```

如果你想把对话导出成可读的 Markdown：

```bash
cat session.jsonl | jq -r '
  if .type == "user" then "## User\n\n" + (.message.content | tostring) + "\n"
  elif .type == "assistant" then "## Claude\n\n" + (.message.content | tostring) + "\n"
  else empty end
' > conversation.md
```

### 方法二：在 lovcode 中查看

如果你使用我们的 [lovcode](https://github.com/MarkShawn2020/lovcode) 开发环境，它内置了对 Claude Code 会话记录的浏览和分析功能，可以直接在界面中回顾历史对话，无需手动解析 JSONL。

![Lovcode 支持项目、session、聊天条目等三级索引](http://cdn.cs-magic.cn/picgo/20260307184500402.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


### 小结

Claude Code 的本地记录获取非常简单，因为数据就在你手边。真正的挑战在下一个场景。

---

## 场景二：Claude App (Chat) 聊天记录

> 难度：⭐⭐⭐⭐ | 数据位置：云端

这是大多数人的核心需求——你在 claude.ai 或 Claude 桌面端里的日常对话。这些数据存在 Anthropic 的服务器上，没有导出按钮，也没有公开 API。

获取方式只有一条路：**抓包。**

但 claude.ai 的抓包不像普通网站那么简单，我们在实践中踩了好几个坑，下面完整记录。

### 第一步：配置 Charles 代理抓包

工具选择：[Charles Proxy](https://www.charlesproxy.com/)（macOS 最主流的抓包工具）。

![](http://cdn.cs-magic.cn/picgo/20260307185121497.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

#### 0. 搭配 VPN/代理工具使用（如 Clash Verge）

如果你日常使用 Clash Verge 等代理工具科学上网，需要让 Charles 和它协同工作。方案是把 Clash 设为 Charles 的**上游代理**：

1. Charles → Proxy → **External Proxy Settings**
2. 勾选 **Use external proxy servers**
3. 填写 Clash 的代理地址：
   - HTTP Proxy: `127.0.0.1:7890`
   - HTTPS Proxy: `127.0.0.1:7890`（端口以你的 Clash 配置为准）
4. 确保 Clash Verge 的"系统代理"关闭（避免和 Charles 的系统代理冲突）

这样流量路径就是：**浏览器 → Charles（抓包） → Clash（翻墙） → 目标网站**，两者各司其职。

#### 1. 安装 SSL 证书

抓 HTTPS 必须配证书，否则看到的全是加密数据。

1. 打开 Charles → Help → SSL Proxying → **Install Charles Root Certificate**
2. 系统会自动打开"钥匙串访问"
3. 找到 "Charles Proxy CA" 证书，双击
4. 展开"信任" → "使用此证书时"改为 **始终信任**
5. 关闭窗口，输入密码确认

![安装成功后会显示登录、系统都完全信任](http://cdn.cs-magic.cn/picgo/20260307185337026.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


#### 2. 开启 SSL Proxying

1. Proxy → SSL Proxying Settings
2. 勾选 **Enable SSL Proxying**
3. 在 Include 列表中添加：
   - Host: `claude.ai`
   - Port: `443`
   - （或者偷懒填 `*:443` 全局解密）

![](http://cdn.cs-magic.cn/picgo/20260307185308550.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

![ChatGPT app 对网络的监控比 claude 要更严格](http://cdn.cs-magic.cn/picgo/20260307185634014.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


#### 3. 打开 claude.ai 正常使用

现在你在 Charles 中应该能看到 claude.ai 的请求了。大部分请求都能正常解密显示——但有一个问题。

### 第二步：解决 zstd 编码乱码

当你在 Charles 中查看 claude.ai 的响应时，你会发现：**response body 全是乱码！**

其他网站都正常，唯独 claude.ai 乱码。这不是证书问题，而是——

**claude.ai 的响应使用了 Zstandard (zstd) 压缩编码。**

查看响应头，你会看到：

```
content-encoding: zstd
```

而 Charles（截至 2026 年初）**不支持 zstd 解压**。它只能处理 gzip、deflate、brotli，遇到 zstd 就直接显示原始压缩字节流。

#### 解决方案：Rewrite 请求头

用 Charles 的 Rewrite 功能，在请求发出前把 `Accept-Encoding` 头里的 zstd 去掉，强制服务器返回 Charles 能识别的压缩格式。

1. Tools → **Rewrite** → 勾选 **Enable Rewrite**
2. 点 **Add** 新建一条规则集
3. **Location** 添加 `claude.ai`
4. 点 **Add** 添加一条 Rewrite Rule：
   - Type: **Modify Header**
   - Where: **Request**
   - Match - Name: `Accept-Encoding`
   - Match - Value: `(.*)zstd,?\s*(.*)` （勾选 Regex）
   - Replace - Name: `Accept-Encoding`
   - Replace - Value: `$1$2`

或者更简单粗暴：

- Type: **Modify Header**
- Where: **Request**
- Match - Name: `Accept-Encoding`
- Replace - Value: `gzip, deflate, br`（直接覆盖整个值）

![确保charles抓包得到的数据都是可解析的压缩格式](http://cdn.cs-magic.cn/picgo/20260307185426301.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


保存后刷新 claude.ai 页面，**response body 变成可读的 JSON 了！**


### 第三步：找到聊天记录的 API

现在你能看到所有请求了。关键的几个 API 端点：

```
# 获取对话列表
GET https://claude.ai/api/organizations/{org_id}/chat_conversations

# 获取单个对话详情（包含所有消息）
GET https://claude.ai/api/organizations/{org_id}/chat_conversations/{conversation_id}

# 发送消息（SSE 流式响应）
POST https://claude.ai/api/organizations/{org_id}/chat_conversations/{conversation_id}/completion
```

如果你实在不知道什么数据对应什么请求，问题也不大，在打开目标网页之后，复制一个较有标识的词语，然后在charles里按 `shift + cmd + F` 全局搜索，就可以看到匹配的结果：

![](http://cdn.cs-magic.cn/picgo/20260307190021234.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

接着双击就可以跳转到带有导航结构的文件位置了：

![](http://cdn.cs-magic.cn/picgo/20260307190150771.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

接着右键repeat测试请求是否稳定（有些反爬比较厉害的网站会基于时间戳刷新请求参数，导致无法复用链接）：

![](http://cdn.cs-magic.cn/picgo/20260307190311556.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

实测claude的请求是稳定的：

![](http://cdn.cs-magic.cn/picgo/20260307190332505.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


所以可以直接右键 → **Copy cURL Request**，你就得到了一个带完整 Cookie 和 Header 的 curl 命令。

![](http://cdn.cs-magic.cn/picgo/20260307190349525.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

它的结构大致如下：

```shell
    
curl -H "Host: claude.ai" -H "Cookie: anthropic-device-id=dfd5d……
```

### 第四步：解决 curl 命令行执行问题

你兴冲冲地把 curl 命令粘贴到终端执行——结果返回了一堆 HTML：

```html
<!DOCTYPE html>
<html>
<head><title>Just a moment...</title>
```

**Cloudflare 的 Bot 检测拦截了你。**

为什么 Charles 里 Repeat 请求可以，curl 不行？三个原因：

1. **TLS 指纹不同**：Cloudflare 检测 TLS Client Hello 的指纹（JA3/JA4），curl 的 TLS 握手特征和 Chrome 完全不一样
2. **`cf_clearance` cookie 有绑定**：这个 cookie 跟浏览器的 TLS 指纹绑定，复制到 curl 里指纹不匹配会被拒
3. **Challenge 状态不可转移**：浏览器通过的 Cloudflare 验证状态不能被 curl 继承

#### 解决方案：curl-impersonate

[curl-impersonate](https://github.com/lwthiker/curl-impersonate) 是一个能模拟真实浏览器 TLS 指纹的 curl 分支。它魔改了 curl 的 TLS 库，让握手过程看起来和 Chrome/Firefox 一模一样。

**macOS 安装：**

```bash
brew tap shakacode/brew
brew install curl-impersonate
```

> ⚠️ **踩坑提醒**：brew 安装可能遇到 CMake 版本兼容问题。如果报 `Compatibility with CMake < 3.5 has been removed` 错误，需要编辑 formula：
>
> ```bash
> # 找到 formula 路径
> brew formula shakacode/brew/curl-impersonate
> # 编辑这个文件，在 def install 开头加一行：
> ENV["CMAKE_POLICY_VERSION_MINIMUM"] = "3.5"
> ```
>
> 如果还有网络问题（SSL_ERROR_SYSCALL），在 formula 中加：
> ```ruby
> ENV["http_proxy"] = "http://127.0.0.1:7890"
> ENV["https_proxy"] = "http://127.0.0.1:7890"
> ```

安装后可用的命令：

```bash
# 通用入口
curl-impersonate-chrome

# 指定浏览器版本
curl_chrome110
curl_chrome107
# ...更多版本见 curl-impersonate --help
```

**使用方式：**

把 Charles 复制出来的 curl 命令中的 `curl` 替换为 `curl-impersonate-chrome`，其余不变：

![](http://cdn.cs-magic.cn/picgo/20260307190609830.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


这次你应该能拿到正常的 JSON 响应了。

![](http://cdn.cs-magic.cn/picgo/20260307190722604.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


### 第五步：批量导出聊天记录

有了能用的 curl 命令，批量导出就是体力活了。思路：

```bash
# 1. 获取所有对话列表
curl-impersonate-chrome 'https://claude.ai/api/organizations/{org_id}/chat_conversations' \
  -H 'Cookie: ...' > conversations.json

# 2. 提取每个对话的 ID
cat conversations.json | jq -r '.[].uuid' > conversation_ids.txt

# 3. 逐个获取对话详情
while read id; do
  curl_chrome110 "https://claude.ai/api/organizations/{org_id}/chat_conversations/$id" \
    -H 'Cookie: ...' > "conversation_$id.json"
  sleep 2  # 别太快，避免触发限流
done < conversation_ids.txt
```

> **注意**：Cookie 有有效期，过期后需要重新从 Charles 中获取。建议一次性跑完。

### 完整流程图

```
Charles 配置 SSL 证书
        ↓
开启 SSL Proxying (claude.ai:443)
        ↓
Rewrite 规则去除 zstd 编码
        ↓
抓包获取 API 端点和 Cookie
        ↓
Copy cURL Request
        ↓
替换 curl 为 curl_chrome110
        ↓
批量获取对话记录 JSON
        ↓
解析/转换为可读格式
```

---

## 场景三：Claude App (Cowork / Code) 记录

> 难度：⭐⭐⭐ | 方案：开发者工具

好消息是，Claude 桌面 App 内置了**开发者模式**。在菜单中启用后，你可以直接打开 DevTools，像在浏览器里一样查看 Network 面板、复制请求——这意味着 Chat、Cowork、Code 三个功能的网络请求都可以被捕获。

![claude app 支持开发者模式](http://cdn.cs-magic.cn/picgo/20260307190833755.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


获取方式和场景二基本一致：在 DevTools 的 Network 面板中找到对应的 API 请求，复制为 cURL，再用 curl-impersonate 执行即可。

由于claude采用了electron架构，所以直接使用 `shift + cmd + I` 即可打开开发者模式：

![](http://cdn.cs-magic.cn/picgo/20260307190930289.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


具体的 API 端点和数据格式，我们会在后续文章中展开。如果你有新发现，欢迎留言交流。

---

## 获取记录后，你可以做什么？

拿到原始 JSON 数据后，真正有价值的事情才刚开始：

1. **建立个人知识库**：把和 AI 的高质量对话整理成可检索的知识文档
2. **复盘思维过程**：回顾自己是怎么提问的，哪些追问有效，哪些跑偏了
3. **提炼 Prompt 模板**：从历史对话中提取好用的提问模式，形成自己的 prompt 库
4. **统计使用模式**：分析自己最常在什么场景下使用 AI，哪些领域依赖最深
5. **训练/微调**：如果你做 AI 研发，高质量的人机对话本身就是宝贵的训练数据

**我们之前还系统分析过各大开源框架（包括openclaw）的记忆机制，如果你感兴趣的话，欢迎留言或者转发本文以提高我们发布研究成果的积极性，理论上对大家理解/更好地驾驭 agent 的记忆机制或者自行基于 cc/claw 架构构建自己的 agent 会有一定帮助。**

---

## 总结

| 场景 | 方案 | 难度 | 现状 |
|------|------|------|------|
| Claude Code | 直接读本地 JSONL | ⭐ | 完全可用 |
| Claude App Chat | Charles 抓包 + curl-impersonate | ⭐⭐⭐⭐ | 完全可用 |
| Claude App Cowork/Code | App 开发者工具 + curl-impersonate | ⭐⭐⭐ | 可用 |

核心踩坑点：

- **zstd 编码**：Charles 不支持 zstd 解压，需要 Rewrite 请求头
- **Cloudflare 检测**：普通 curl 的 TLS 指纹会被拦截，需要 curl-impersonate
- **brew 安装坑**：curl-impersonate 的 Homebrew formula 有 CMake 兼容性问题

这些问题我们都是用 AI 辅助排查和解决的——遇到技术问题先抓关键信息（响应头、错误日志），再让 AI 分析原因，效率非常高。

---

**你的 AI 聊天记录，值得被认真对待。**

如果这篇文章对你有帮助，欢迎转发给同样在用 Claude 的朋友。如果你有更好的获取方案，或者对 Cowork/Code 的抓包有思路，评论区见。

---

## 最后：我们想办一场 OpenClaw 线下峰会

聊天记录只是起点。我们还系统分析过各大开源框架（包括 OpenClaw）的记忆机制，也在探索龙虾的自主进化、最佳实践等方向。

我们正在筹备一场 **OpenClaw 线下峰会**，想先听听大家的想法——**请花 10 秒在评论区投票**：

**1. 你的身份是？**
A. 开发者/程序员
B. 产品经理/设计师
C. 创业者/独立开发者
D. 投资人
E. AI 爱好者/其他

**2. 你最想深入讨论的议题？（可多选）**
A. 记忆机制：龙虾如何越用越懂你
B. 自主进化：龙虾如何越用越聪明
C. 最佳实践：高效养龙虾的工作流
D. 创投生态：龙虾赛道的投资逻辑

**3. 你希望在哪个城市举办？**
A. 北京
B. 上海
C. 深圳/广州
D. 其他（评论区留言）

**4. 你愿意为一场全天的高质量沙龙付费吗？**
A. 免费才来
B. 199 以内可以接受
C. 399 以内可以接受
D. 只要内容好，价格不是问题

**投票方式：在评论区回复数字组合即可，例如「C-AB-A-B」表示你是创业者，想聊记忆机制和自主进化，希望在北京办，199以内可接受。**

你的每一票都会影响最终的活动形式和内容。期待见面。
