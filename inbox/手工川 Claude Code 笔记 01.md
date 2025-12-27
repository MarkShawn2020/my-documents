本系列是个人使用 claude code 的经验复盘，重点厘清大家在使用 Claude Code 中的一些细节问题，预计篇幅较长，所以不定期连载，如果你有什么问题欢迎留言，会酌情收录到后续的文章中。

非新手教学，新手请看：

- 360 奇舞团前端开发工程师的[AI 时代的终端革命：Claude Code 完全指南](https://mp.weixin.qq.com/s/23-HkZOylhVA7DzkYKYL5w)，简洁明了，包含如何接入 Kimi 等实操建议，可以作为一份速查手册
- 我们手工川花费 2 周时间系统学习吴恩达与 Anthropic 在线教育主管 Elie 合作的 Claude Code 课程笔记：[吴恩达 Claude Code 笔记精华版](https://mp.weixin.qq.com/s/Of1qAQuAQDrkyWIZ0ug-dw)

此外，也强烈推荐阅读以下最佳实践/官方文档：

- [Claude Code Best Practices \ Anthropic](https://www.anthropic.com/engineering/claude-code-best-practices)，Claude Code 官网最佳实践，我多篇文章里推荐过多次，**必看**
- [Claude Code overview - Anthropic](https://docs.anthropic.com/en/docs/claude-code/overview)，Claude Code 官方文档（**官方文档永远是第二好的学习资料**）

也欢迎留言推荐好的文章、视频、教程等~

计划目录：

- 新型开发范式： 上下文工程
- Claude Code 的细节问题
	- 01\. CodeBase vs PromptBase
	- 02\. README.md vs CLAUDE.md
	- 03\. feature management (single)
	- 04\. feature management (multiple)
	- 05\. Prompt vs Command vs OutputStyle
	- 06\. SubAgent vs MCP vs Hook
	- 07\. Misc(Test，Debug，Version，CICD)
- Claude Code 场景最佳实践
	- 01\. 初始化 / 二开
	- 02\. 设计
	- 03\. feature development
	- 04\. bugfix
	- 05\. 重构
	- 06\. 部署
	- 07\. 交付
	- 08\. 维护
- Claude Code 国内主要问题
	- 01\. 国内用户怎么使用
	- 02\. 用量是不是越多越好
	- 03\. 降智到底是怎么回事
	- 04\. 如何建立观测系统
	- 05\. gpt5、gemini、kimi 等到底哪个更好
- Appendix（个人配置）
	- ~/.zshrc
	- ~/.claude/settings.json
	- ~/.claude/CLAUDE.md
	- ~/.claude/commands/better-readme.md
	- ……


## 新型开发范式： 上下文工程

**SDLC（Software Development Life Cycle，软件开发生命周期）** 是软件工程领域的一个专业术语，它定义了开发一个高质量软件所需要经历的各个阶段，从最初的构想到最终的部署和维护，包含：

- 需求分析 (Requirement Analysis)
- 规划 (Planning)
- 设计 (Design)
- 开发/编码 (Development/Coding)
- 测试 (Testing)
- 部署 (Deployment)
- 维护 (Maintenance)

![source: https://stackify.com/what-is-sdlc/](https://poketto.oss-cn-hangzhou.aliyuncs.com/641fa22653ff17198bf0bb2a4dcfb610.png?x-oss-process=image/quality,q_90/rotate,0)

由于这个过程可能相当漫长，涉及大量的协同，充满不确定性，为了给这个复杂的过程提供一个清晰、结构化的执行框架，从而确保项目不会陷入混乱，机智的工程师们就引入或者开发了各种 SDLC 模型，目前最典型的是瀑布流模型和敏捷模型，以及小团队中最常用的原型模型。

- **瀑布模型**：严格按照线性顺序执行 SDLC 的每一个阶段，一个阶段完成后才能进入下一个阶段。
- **敏捷模型**：以迭代和增量的方式来经历 SDLC 的所有阶段。项目被拆分成多个小周期（称为“迭代”或“冲刺”），每个周期都包含需求、设计、编码、测试等所有环节，并产出一个可用的软件增量。
- **原型模型**：在正式投入大量资源进行全面开发之前，先快速构建一个可运行的、简化的系统原型（Prototype），以便及早地收集用户反馈，从而澄清和完善需求。

ChatGPT 3.5 以来，SDLC 中原有的需求分析、规划、设计等重视图文理解的场景受到广泛冲击；Claude Sonnet 3.5 以后，编码能力逐步增强，Anthropic 的最新模型 opus-4.1 的 swe 分数高达 74.5，得到了越来越多工程师的信任；MCP 等工具诞生以后，大模型与外部交互的能力越来越强，甚至各大平台纷纷为大模型开设“高速公路”（例如高德 MCP），一些创业团队尝试开发基于大模型的自动测试，部分工程师已经开始使用语音与 AI 打电话写代码，并在手机上远程同步……

自此，2025 年，软件工程的几乎所有环节，都被 AI 不同程度地渗透，字节开发了 Trae，百度开发了 Comate，腾讯开发了 CodeBuddy，阿里开发了 QCoder，纷纷试图抢占 AI Coding 的高地。

![source: https://zhuanlan.zhihu.com/p/1942019561764390788](https://poketto.oss-cn-hangzhou.aliyuncs.com/6dbc0e8769f43a3d8e4a8ee763982aff.png?x-oss-process=image/quality,q_90/rotate,0)

![source: https://www.anthropic.com/news/claude-opus-4-1](https://poketto.oss-cn-hangzhou.aliyuncs.com/886f5e13828b9066e3663b2718981660.png?x-oss-process=image/quality,q_90/rotate,0)

![source: 《手工川 AI 方法论》](https://poketto.oss-cn-hangzhou.aliyuncs.com/cda63f52c7dae22fd4cdf66405ec0793.png?x-oss-process=image/quality,q_90/rotate,0)

短短一年间，我从坚持使用五年之久的 Jetbrains IDE 转向 Cursor/Windsurf，接着半年后全面转向 iTerm + Tmux + Claude Code，辅之以 VSCode。

我往往在 iTerm 里同时打开多个 projects，每个 project 都会开启一个 tmux，在这个 tmux 里会开启多个窗格，其中 1-2 个是用于 cc，另外 1-2 个是用于预览或者验证 cc 的效果，或者用于 git 执行版本控制，大致如下：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/94e3c694777b122dc5bdfc8ec656c7d9.png?x-oss-process=image/quality,q_90/rotate,0)

这样的好处是可以同时监控 AI 在每个项目的进展，有一说一，确实有点像炒股：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/4986adaa64527372ff9bf3ac512d4296.png?x-oss-process=image/quality,q_90/rotate,0)

当然，这与以前的开发范式还是有很大的不同。以前也可以同时在 IDE 里打开多个项目，但每个项目是一个独立的 window，彼此之间需要来回切换或者强制分屏，每个项目的内部一般都标配文件导航区、代码编辑区、命令行区等。

![红色区域为视觉重心，非常零散分布](https://poketto.oss-cn-hangzhou.aliyuncs.com/d4c62920454636eefcce92079d1e932a.png?x-oss-process=image/quality,q_90/rotate,0)

在 IDE 中，视觉重心往往是占 50%以上的代码编辑区，现在则转移到了右侧 30%的 AI sidebar。而在 terminal 里，无视了文件树、代码区、sidebar 后，视觉重心只剩下了：**需求与实现**。

这是 TUI 的一次伟大胜利，也是一次奇特的返古，分水岭在 AI（尤其是 Claude Code）真地能生成人类可用（甚至更高质量）的代码，也即：**当人们不用再频繁地去检查 AI 写的代码是否正确，或者即便不正确，也可以通过其他观测手段反馈给 AI 并让它修正，人们便逐渐不再需要随时随地地深入代码细节，也就不用再打开 IDE 了**。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/74200ffeecc69fa581c0f190b132e29c.png?x-oss-process=image/quality,q_90/rotate,0)

当然，一个新事物的早期，并不是所有人都买单（我就曾和一位资深工程师前辈 SQ 就 claude code 的产品形态、开发范式展开过激烈的争论）。

工程师选择 TUI，亦或 GUI，亦或 LUI，作为自己的主开发形态，区别主要是习惯与审美，对日常产出影响不是很大，**但对长期产出影响很大**。（犹记得 SQ 给我演示配置了 brave-search、puppeter 等 MCP 之后的 Claude App 展现出的智能给我的震撼，至少不属于 Manus）

类似的探讨还有 Agent 与 Workflow 到底哪个更大？是把 Agent 嵌到 Workflow 里去，还是把 Workflow 嵌到 Agent 里；以及今天张小珺与杨智麟的对话里聊到的缸中之脑（Agent 如何与外部交互）：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/69138ef3d0a2baefbfab31c7904f539e.jpg?x-oss-process=image/quality,q_90/rotate,0)

我有相当的信心预测，未来的开发范式，不是三者择其一，而是它们的融合。开发者可能会在一个 GUI 窗口中通过 LUI 描述一个应用原型，AI 自动生成初始的 TUI 项目结构和代码框架，然后开发者在 TUI 环境中进行快速的迭代和调试，并通过 GUI 工具链进行最终的可视化发布和监控。

AI 一天，人间一年，深度使用 Claude Code 参与 40+工程项目、系统学习整理完吴恩达 Claude Code 教程的我，在此与你分享我的一点 AI Coding （Vibe Coding）的个人经验，希望对你有所帮助。


话说今天我们的 ccm（https://github.com/MarkShawn2020/claude-code-manager） 支持了超酷的 statusline，欢迎大家体验使用：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/986206d21aa12a7414297e2efef5a9e4.jpg?x-oss-process=image/quality,q_90/rotate,0)

ccm 是我们接下来重点为 claude code 开发者提供的 All in One Library，支持超级好看的 dashboard，以及一堆好玩好用的功能，欢迎大家多多支持！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d78cdcd061738f57d5977b3265a5bdcd.png?x-oss-process=image/quality,q_90/rotate,0)


## Claude Code 的细节问题

过去几个月我们在 Claude Code 相关社群里做了大量交流，中间发现了不少细节问题，它们涵盖了 Claude Code 设计与功能的方方面面。

有问题是很正常的，毕竟 [Claude Code 的官方文档](https://docs.anthropic.com/en/docs/claude-code/overview) 实在是太长了，基于[context-packer（手工川开源上下文打包工具）](https://github.com/MarkShawn2020/context-packer)打包后有 8000 多行，体积 323KB（也就是大概 30 万字母）……

耐心学完 Anthropic 的所有文档（包括 prompt、claude code 等），目测至少得一个月……

![source: https://docs.anthropic.com/en/docs/claude-code/overview](https://poketto.oss-cn-hangzhou.aliyuncs.com/656c55423e5a75054c11bb2e176b2b91.png?x-oss-process=image/quality,q_90/rotate,0)

所以本文档只针对社群交流过程中的一些高频问题，以及我个人认为很有价值的问题，做一些相对深入的阐述。

### 01. CodeBase vs PromptBase

互联网公司曾经最重要的资产正在逐渐从 CodeBase 转向 PromptBase，一大批前沿科技爱好者（即便看得懂代码）也开始尝试只用 prompt 与 AI 进行交互，以提高自己的 prompt 驾驭能力。

> 注：手工川最近还注册了 thepromptbase.com 的域名，希望能赋能到大家的 prompt 开发与迭代，敬请期待！

【投票：你觉得未来代码更重要还是 prompt 更重要？】

上下文工程在 Vibe Coding 里的具象化，就是：**Model + RAG + Prompts**，其中 RAG 什么，由 Prompts 决定。

Prompts 又分 SystemPrompts 和 UserPrompts，不同的产品会有不同的 SystemPrompts 设定机制，但大致分为 BuiltinPrompts （Agent 设计内部） + ExternalFilePrompts （在 Claude Code 中就是各种 `Claude.md` 文件，在 Cursor 中就是各种`.rules`）。

因此了解 Claude Code 的 prompt 加载机制以及如何写好这些 ExternalFilePrompts 甚至修改 BuiltinPrompts 很重要。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5365de0d6e3b75bc2149cb3d253948a6.png?x-oss-process=image/quality,q_90/rotate,0)

根据社区交流反馈，大部分社区成员都会在 `~/.claude/CLAUDE.md` 里配置用户级别偏好，在项目根目录的 `./CLAUDE.md` 里配置项目级别指引。不过较少有人探讨 `CLAUDE.local.md`以及嵌套 CLAUDE.md 的问题。

尤其是嵌套 CLAUDE.md，是在我翻译吴恩达教程并结合官方文档后才明白它是按需动态导入的，这就很巧妙。

我们积累了不少优化 prompt （包括 CLAUDE.md，见后文）的手段，未来会逐渐对外分享，希望对你有所帮助。

### 02. README.md vs CLAUDE.md

如果说上述 CLAUDE.md 的加载细节讨论较少的话，README.md 和 CLAUDE.md 之间的差异细节讨论地就更少了。

大家倾向于在看似很容易理解并且不阻碍自己的地方较少花时间，于是错过很多可能很有价值的成长机会。

对于一个初期代码库，其根目录可能只有一个 `README.md` （甚至没有）；对于一个成熟的工程项目，其根目录则往往有 `README.md | DESIGN.md | PRD.md | Licence | CONTRIBUTING.md` 等等；而现在，又出现了一个 CLAUDE.md。

显然，CLAUDE.md 是给 AI 看的，而其他文件都是给不同的人看的。

那有没有想过，在 Agent 时代（尤其是 Multi-Agent）时代，不同的 Agent 可能需要不同的 CLAUDE.md 呢？当然，你也可以说，不会的，Agent 有自己的 Agent Spec，在那个里面定义独属于它的 Prompt 即可。

所以，那就是 UserClaude.md --> ProjectClaude.md --> AgentPrompt.md --> SubAgentPrompt.md --> UserPrompts.md ……

我们需要非常仔细的分层，因为 prompt 的空间比较宝贵。未来上下文空间会不会像磁盘一样廉价呢？大概率不会，它可能更像内存。

这是第一个问题。

其次，哪些适合放在 README.md 里，哪些适合放在 CLAUDE.md 里，哪些两者都可以放，如果两者都可以放，是不是得使用某种软链接方式使之能导入（CLAUDE.md 支持 @ 导入外部文件，但 README.md 不支持）？

这些问题层出不穷，你可能会在不同的设计里左右摇摆，甚至来回重构。

Fine，I am not caring, intelligence means anything.

It's your choice.

我们需要这样细致而深入的研究探讨，如果我们真地把全部身家性命、个人发展前途都系于这样珍贵的 CLAUDE.md 上的话。

### 03. feature management (single)

第三个问题，是 single feature management。

我们并不推荐在一个 session 里并行地开发多个 features，这是非常糟糕的一种尝试，上下文污染会很严重。比较好的办法是为每个 feature 开一个独立的 session。

我们有很多社区朋友知道 `/clear` 会清除上下文，但似乎没有人探讨过它清除的同时，会新建 session 吗？

比如，在某个测试项目里，目前有 4 条 sessions。
![`cc -r` 可以罗列所有sessions](https://poketto.oss-cn-hangzhou.aliyuncs.com/ec419b60b15fba306925a9f36d42f039.png?x-oss-process=image/quality,q_90/rotate,0)

现在你新开一个 session，咨询完第一个问题后使用 `/clear`，并咨询第二个问题。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9187ee64b1422c24881e2b7cd9b39208.png?x-oss-process=image/quality,q_90/rotate,0)

现在你退出，你还能回到第一个问题吗？

我们再次罗列所有 sessions，发现有 6 条了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3e9ca336e3efa33c943161e2bd2ab616.png?x-oss-process=image/quality,q_90/rotate,0)

答案：是的，`/clear` 不仅会清空当前 session 的上下文，还实质创建了一个新的 session。

也就是说，`/clear` 等价于退出当前的 cc，并在当前目录再新建一个 cc。

但是。

根据我们以前对 `~/.claude` 的结构分析，二者在物理表示上可能是不同的，尽管在逻辑表示上是一致的。

所以我们现在就可以大胆地为某个 featureA 新建一个 session，结束后使用 `/clear` 开发第二个 featureB，直到突然意识到 featureA 还有一些改进的空间，我们就可以使用 `cc -r` 定位到 featureA 的 session，并行开发。

但比起 `/clear` 到底会不会新建 session，社区朋友更迷茫的是 `/clear` 和 `/compact` 之间的差异，以及最佳实践。

有一些比较偷懒的朋友，喜欢依赖 claude code 的 自动 compact 机制，也就是当 claude code 上下文（200K）不足的时候，会自动触发一次 `/compact`，但这是非常不推荐的。

想象你正在攻克一个棘手的数学难题，在脑海里列了一大堆设想，现在朋友突然喊你打球，你不得不中断，回来后你不得不重新解题，甚至再也记不起之前快成功的思路。

软件工程里的最佳实践往往是尽可能地模块化、原子化。

把每一个 feature 当做一个 SQL 事务去执行，要么这个 feature 顺利执行结束，要么就失败回滚，保障 feature 的原子性可以大大保障工程的质量。

```ad-tip

- **事务**(Transaction): 是一系列数据库操作的集合，这些操作被视为一个单独的工作单元。
- **原子性**(Atomicity): 事务的原子性意味着事务中的所有操作要么全部成功，要么全部失败。如果操作过程中发生任何失败（如系统崩溃、错误），那么整个事务会被撤销，所有已做的更改都会被丢弃，就像从未发生过一样。
- **回滚**Rollback): 当事务中的某个操作失败，或者数据库检测到需要撤销更改时，执行回滚操作，使数据库恢复到事务开始之前的状态。
```

但假设一个 feature 的实现所需要的 token 量（尤其是输入）非常大，怎么办？

开源节流。

比如说把一个很长的 prompt 写入文件再让 claude 按需去读，或者调用一个 gemini 实现超长文本的压缩再送给 claude，这就是开源。

比如说把一个图片尽可能降低分辨率，甚至用图转文模型转成文本，或者尽可能规避用图片去交互（比如基于 `code-inspector-plugin`可以定位前端问题对应的代码位置），这就是节流。

但如果还是不行呢？我的 feature 就是很大。

分而治之、减而治之。

把一个大的 feature 拆成一个个小的 features，就是分而治之。

在实现 feature 的路上，不断地 compact 就是减而治之。

总之，办法总比困难多，我们总能尽可能地让一切任务优雅地（gracefully）结束。

实在不行，自动 compact 也不是不可以接受。

### 04. feature management (multiple)

第四个问题是多 feature 管理。

如果你不曾认真学习这块内容，或者缺少团队协作经验的话，你往往会在同一个目录开启多个 cc，然后让它们同时进行多个 features 开发，但由于多个 cc 可能会反复操作相同的文件，因此并不推荐。

最佳实践是使用 git worktree 使每个 feature 对应的 session 都处在独立、互不相扰的环境里。

如果你还没有经验，你可以阅读以下进行更深入的了解：

- [吴恩达 Claude Code 笔记 06：CC + Git Worktree = 王炸](https://mp.weixin.qq.com/s/_4oPcqy-vcQWcsAOO4DKZA)
- [Run parallel Claude Code sessions with Git worktrees - Anthropic](https://docs.anthropic.com/en/docs/claude-code/common-workflows#run-parallel-claude-code-sessions-with-git-worktrees)
- [Git - git-worktree Documentation](https://git-scm.com/docs/git-worktree)

值得注意的是，也有一些软件方便你 by git worktree 的 features 并行开发，例如：

- UIUX 非常简洁优雅：[Conductor](https://conductor.build/)
- 手工川自研 Claude Code Management All In One：[MarkShawn2020/claude-code-manager: CCM: Claude Code Management All In One.](https://github.com/MarkShawn2020/claude-code-manager)

![source: https://conductor.build/](https://poketto.oss-cn-hangzhou.aliyuncs.com/3b1969e1670eae9d373c16498c25aa9f.png?x-oss-process=image/quality,q_90/rotate,0)

但值得注意的是，git worktree 并发很爽，合并是个小小的头疼问题，尽管吴恩达教程里选择了让 cc 自行合并，但如果你是个 indie vibe coder（独立 Vibe 开发者），你绝不会喜欢这种被 block 的感觉。

所以，对于 inide vibe coder，我的建议是：建议并行开发多个项目，每个项目内使用串行开发多个 features。

于是，here you are，你就会像我一样开成为 **Vibe“股”民** 了。

> 当然，我也在考虑基于 conductor.build 的形态适配成更适合 indie vibe coder 的版本。


---

（待续）

---

## Appendix（本期所涉及相关个人配置）

### ~/.zshrc

```bash
alias cc="claude"
alias ccc="cc -c"
alias commit="cc -p '/git-add-commit'"
```

### ~/.claude/settings.json

```json
{
  "$schema": "https://json.schemastore.org/claude-code-settings.json",
  "permissions": {
    <!-- 默认使用 YOLO 模式，不推荐使用 alias 的写法 -->
    "defaultMode": "bypassPermissions",
    <!-- 你可以把你所有常用的工作区、知识库等写在里面 -->
    "additionalDirectories": [
      "~/.claude",
      "~/.gemini",
      "~/.neurora",
      "~/projects",
      "~/repos"
    ]
  },
  "model": "opus",
  "hooks": {
    "PostToolUse": [
    <!-- ccm 自动收集 tool use 的数据，供后续分析使用 -->
      {
        "matcher": "",
        "hooks": [
          {
            "type": "command",
            "command": "npx claude-code-manager track",
            "timeout": 5
          }
        ]
      }
    ]
  },
  "feedbackSurveyState": {
    "lastShownTime": 1754071238543
  },
  <!-- ccm 支持了 statusline -->
  "statusLine": {
    "type": "command",
    "command": "/Users/mark/.claude/statusline.sh",
    "padding": 0
  }
}
```

### ~/.claude/CLAUDE.md

```markdown
# 手工川高质量代码开发通用框架 V0.8.0

本框架定义了所有项目应遵循的核心准则。具体技术栈的实现应在此框架下进行。

### I. 核心原则 (Core Principles)

- **单一职责 (SRP)**: 每个单元（函数、类、模块）只负责单一、明确的职责。
- **避免重复 (DRY)**: 抽象并复用通用逻辑，禁止复制代码。
- **保持简单 (KISS)**: 优先采用最简单、清晰的方案，避免过度工程化。

### II. 通用编码规范 (General Coding Standards)

- **配置 (Configuration)**: 禁止硬编码。配置项（密钥、URL）必须来自环境变量或配置文件。
- **异常 (Exceptions)**: 精准处理，禁止静默忽略。异常必须被记录或向上层抛出。
- **异步 (Asynchronicity)**: 必须使用现代异步模式（如 `async/await`），禁止手动延时。
- **测试 (Testing)**: 必须为核心逻辑和边界情况编写有意义的、可维护的测试。
- **文档 (Documentation)**: 必须为公共 API 和复杂逻辑编写清晰的文档（如 JSDoc, Docstrings）。
- **根源解决 (Root Cause)**: 禁止使用临时方案 (Workarounds)；必须分析并解决问题的根本原因。

### III. 技术栈规范 (Technology Stack Guidelines)

#### TypeScript (TS)

- **TS | 严格模式**: `tsconfig.json` 必须启用 `strict: true`。
- **TS | 类型安全**: 严禁使用 `any`；必须优先使用 `unknown` 进行类型收窄。
- **TS | 不可变性**: 优先使用 `readonly` 关键字来创建不可变数据，以减少副作用。

#### Python (Py)

- **Py | 代码风格**: 必须使用 `black` 和 `isort` 自动格式化所有代码。
- **Py | 类型检查**: 新代码必须全面使用类型提示，并通过 `mypy` 静态检查。
- **Py | 日志**: 应用代码必须使用 `logging` 模块，严禁使用 `print()` 函数。

#### macOS 扩展 (macOS Extensions)

- **macOS | 正确的技术栈**: **必须**使用原生的 **Finder Sync Extension** 框架，严禁使用 Automator 或 Shell 脚本作为右键菜单的实现方式。
- **macOS | 极致响应**: 任何 I/O 或耗时操作**必须**在后台线程执行（如 `DispatchQueue.global().async`），确保 UI 主线程绝不被阻塞。
- **macOS | 上下文感知**: 扩展**必须**在显示前验证上下文（如文件类型、数量、位置），仅在相关时才显示菜单项。
- **macOS | 资源节制**: 扩展**必须**轻量，严格控制内存和 CPU 占用，避免影响宿主应用（如 Finder）的性能。
- **macOS | 安全沙箱**: **必须**严格遵守 App Sandboxing 规则，仅在 `Info.plist` 中请求完成功能所必需的最小权限。

### IV. 项目工作流 (Project Workflow)

- **版本控制 (VCS)**: Git 提交信息必须遵循 [Conventional Commits](https://www.conventionalcommits.org/) 规范。
- **依赖管理 (Dependencies)**: 必须使用指定的包管理器并提交锁文件（TS: `pnpm`, Py: `uv`）。
- **自动化 (Automation)**: 必须通过 Git Hooks (如 Husky) 在代码提交前自动执行代码检查、格式化和测试。
- **安全 (Security)**: 严禁在代码库中存储任何敏感信息；必须定期扫描依赖漏洞。
```

### ~/.claude/commands/better-readme.md 


```markdown

---
allowed-tools: [Read(*), Write(*), Edit(*), LS(*), Glob(*), Grep(*), Task, TodoWrite]
description: Analyzes project structure and creates/improves README files professionally
version: "1.1.0"
author: markshawn2020
created: "2025-01-16"
updated: "2025-01-16"
changelog:
  - version: "1.1.0"
    date: "2025-01-16"
    changes: ["Fixed incomplete command logic", "Added actual README writing functionality"]
  - version: "1.0.0"
    date: "2025-01-16"
    changes: ["Initial version with project analysis and README generation/optimization"]
---

# Better README Command

This command analyzes your project structure and either creates a new README.md or optimizes an existing one based on the project type and structure.

## Usage

    /better-readme

## What this command does:

1. **Project Analysis**: 
   - Determines project type (framework, library, end-user product, etc.)
   - Identifies if it's a monorepo or single project
   - Detects target audience (developers, enterprise, consumers)

2. **README Creation/Optimization**:
   - Creates a new README.md if none exists
   - Improves existing README based on best practices
   - Ensures professional, concise, and highly readable content

3. **Content Principles**:
   - **Professional**: Industry-standard formatting and structure
   - **Concise**: High readability with clear, scannable sections
   - **User-focused**: Immediately communicates project purpose and usage

## Process

Now I will analyze this project and create or improve the README:

### Step 1: Check for existing README

First, let me check if a README.md already exists in the project root.

### Step 2: Analyze project structure

I'll examine the project to understand:
- Project type and purpose
- Technology stack
- Key features and functionality
- Target audience

### Step 3: Generate README content

Based on my analysis, I'll create a professional README with:
- Clear project title and description
- Installation instructions
- Usage examples
- Features list
- Contributing guidelines (if applicable)
- License information

### Step 4: Write the README

I'll now write the README.md file with the optimized content.

---

Execute the analysis and README generation now.
```


