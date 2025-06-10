# 送给开发者的新年礼物 - Oh My Commit ！





在 2024 年的最后一天，我想向大家分享发布这个月基于 AI 全勤投入开发完成的项目 - Oh My Commit，它支持 Cli/VSCode 等多端环境、支持通知/面板视图、支持 DIY 插件式开发，致力于成为企业级 AI Commit 解决方案！

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231161608.png)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231161553.png)

## 从痛点说起 

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231152613.png)

说实话，如果不是有人和我提，我甚至都没能意识到自己其实是也需要一款 AI commit 工具的，可能是因为我长期独立开发，不太需要和别人合作，所以没能意识到规范自己 commit 的重要性。

> 从这个角度出发，人确实还是需要”多在企业里呆着好“，才能实打实地发现企业的痛点，也就是”真需求“，从而解决问题，从而”换取报酬”，至于是否需要打着一个”创业“的名号，除非要”融资“，否则也没那么重要，甚至也无那么必要。

但作为一个有代码洁癖的程序员，我自然也对混乱的代码提交信息深恶痛绝：

```bash
# 真实项目中的提交记录
git log --oneline
a123456 update
b234567 fix bug
c345678 修改了一下
d456789 改了改
```

每次看到这样的提交历史，总会想 - 身为程序员，写出规范、专业的提交信息难道不是基本素养吗？

然而现实是:
- 一天写了十几个提交，每次都要绞尽脑汁想措辞
- 有时想用英文写得专业点，但总觉得不够地道
- 团队有统一的提交规范，但每次都要翻文档查格式
- ……

而且就像垃圾分类推了这么多年还是分不清干湿，程序员也往往分不清 feat/fix/perf/... 啊……

我有时候为了尽可能记录足够完备的历史，commit 的频率非常高，以至于都不知道怎么 commit 才好，最后就 `git add . && git commit -m "."` …… （狗头）

```
* 2c8c412 - . (12 days ago) <markshawn2020>
* db43470 - . (12 days ago) <markshawn2020>
* 01e0a26 - . (12 days ago) <markshawn2020>
* e30cd98 - . (12 days ago) <markshawn2020>
* 10da285 - . (12 days ago) <markshawn2020>
* 83903eb - :sparkles: better tsconfig path aliaas (12 days ago) <markshawn2020>
```

> “懒”真地是人类进步的原动力（不是）。

虽然市面上已经有一些 AI Commit 工具，比如 130 star 的 [mefengl/vscode-i-dont-care-about-commit-message: Yet another AI git commit plugin, but without the need for manual confirmation.](https://github.com/mefengl/vscode-i-dont-care-about-commit-message)（下文代称 `I Dont Care`。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231154900.png)

我觉得他做的很不错，使用了 vscode 的原生通知，还是挺优雅的，但有几个缺点：
1. **UIUX**：生成的信息不支持修改，以及不支持多行友好显示 body 部分（这个是 vscode 的限制，所以我额外支持了 webview 的交互模型）。
2. **算法**：大部分ai commit 工具基本都是拿到 diff，然后调用一次大模型，基于 function call 生成符合目标格式的 commit message，但总会有一些缺陷，比如在diff 过长超出 token 限制的时候，就不得不转为手动commit。
3. **生态**：目前它只支持 vscode 插件，但我们有时候会用其他 IDE，或者在 terminal 环境里，所以光做 vscode 插件可能是不够的。
4. **产品理念**：参考 [feat(extension): add option to generate commit messages in Chinese](https://github.com/mefengl/vscode-i-dont-care-about-commit-message/pull/58) 作者提到自己开发这款插件是为了“**Don't Care**”，所以尽量不支持配置，与我 "**Do Care**" 的理念是不一致的，这种冲突就无法通过提 PR 去完善了，只能自己再造一个，尽管我确实有在它基础上改过。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231152932.png)


由于写 UIUX 这个是比较烦的，但是写 prompt 是比较简单的，所以我就想要不我来封装一个框架，定义一套 ai commit 的工作流，然后用户只需关心最核心的 prompt、data 等即可？

于是，一款产品就此诞生了。

## 实际效果演示

经过一个月的打磨，Oh My Commit 现在支持三种使用方式：

### 1. CLI 命令行

```bash
# 安装 cli
✗ npm install -g @oh-my-commit/cli

changed 118 packages in 10s

27 packages are looking for funding
  run `npm fund` for details


# 安装模型（可自行开发与发布，这样自己就可以装自己的模型了）
✗ npm install -g @oh-my-commit/provider-official

changed 46 packages in 712ms

5 packages are looking for funding
  run `npm fund` for details


# 检查模型是否注册成功
✗ ls -lah ~/.oh-my-commit/providers/official
total 9992
drwxr-xr-x@ 6 mark  staff   192B 12 31 16:24 .
drwxr-xr-x@ 3 mark  staff    96B 12 31 16:24 ..
-rw-r--r--@ 1 mark  staff   5.8K 12 31 16:24 CHANGELOG.md
-rw-r--r--@ 1 mark  staff   2.4M 12 31 16:24 index.js
-rw-r--r--@ 1 mark  staff   2.4M 12 31 16:24 index.mjs
-rw-r--r--@ 1 mark  staff   1.2K 12 31 16:24 package.json


# 查看命令行
✗ omc
   ____  _       __  __          _____                          _ _
  / __ \| |     |  \/  |        / ____|                        (_) |
 | |  | | |__   | \  / |_   _  | |     ___  _ __ ___  _ __ ___  _| |_
 | |  | | '_ \  | |\/| | | | | | |    / _ \| '_ ` _ \| '_ ` _ \| | __|
 | |__| | | | | | |  | | |_| | | |___| (_) | | | | | | | | | | | | |_
  \____/|_| |_| |_|  |_|\__, |  \_____\___/|_| |_| |_|_| |_| |_|_|\__|
                         __/ |
                        |___/
✨ AI-powered commit message generator
📦 Version 0.23.0

Usage: Oh My Commit [options] [command]

Oh My Commit - AI-powered commit message generator

Options:
  -v, -V, --version       output the version number
  -h, -H, --help          display help for command

Commands:
  init                    Initialize Oh My Commit configuration
  list-models             List all available AI Commit models
  select-model <modelId>  Set the default model to use for commit generation
  gen [options]           Generate commit message
  help [command]          display help for command


# 查看当前版本
✗ omc -v
0.23.0


# 查看支持的模型列表（注册的插件都会显示在这里）
✗ omc list-models
2024-12-31T08:23:02.749Z INFO  | [console] Listing models...
2024-12-31T08:23:05.938Z INFO  | [console] Available models:
2024-12-31T08:23:05.938Z INFO  | [console]   ✓ ohMyCommit.standard - omc-standard-claude-3.5 (default)


# 配置代理与自己的 API_KEY，基于当前的 git 环境自动生成 commit
✗ HTTP_PROXY=http://localhost:7890 ANTHROPIC_API_KEY=sk-xxx omc gen
2024-12-31T08:23:08.496Z INFO  | [console] Generating commit message...
2024-12-31T08:23:14.423Z INFO  | [console] Generated commit message:
no-op: no changes
---
There are no changes in the provided diff, so no commit message is needed.
2024-12-31T08:23:14.423Z INFO  | [console]
Use -y flag to commit automatically, or run git commit manually with the message above

```


### 2. VSCode 

您可以直接在 VSCode 插件市场搜索 `oh-my-commit` 进行安装：

> Windsurf 等软件使用 open-vsx 插件市场，我需要一点时间评估一下是否同步发布 open-vsx 版本，亦或直接基于 CICD 为大家分发 vsix 文件。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231163723.png)

安装完成后，使用 `Cmd + Shift + P` 打开快捷菜单，搜索 `omc` 即可看到我们预设的一些命令，其中 `Quick Commit` 将直接生成提交信息，`Select Model` 用于切换模型，`Focus View` 用于打开 primary sidebar 面板。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231163337.png)

在插件安装模式下，我们已经预设了一些模型（例如 `ohMyCommit.standard`，它基于 Claude-3.5、支持设置语言、生成 Convention 风格的 Commit ），您可能需要额外配置代理与 API_KEY。

> 项目顺利的话，我将考虑对接硅基流动，额外接入登录系统以减少配置复杂度，但基于开源 DIY 的理念，API_KEY 的独立配置能力将始终为大家保留。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231164558.png)

由于这款产品的目标是 AI 自动 Commit，因此在产品设计的思考上，我在视图级别上基于信息干扰层次做了一些划分。

#### 2.1 弹窗视图

这种在 commit 生成后会弹出一个独立的窗口，就像网页的 Dialog 一样，之前我已经实现了一版，但后续在学习了 VSCode 的 VCS 面板设计后，我 **放弃** 了这种过于干扰的视图。

#### 2.2 面板视图

面板会静静地栖息在您的侧边栏视图区域，主要用于展示 message 主体、一些快捷操作、最佳实践等，长期来看不会增加过多的东西，尽量保持简洁优雅。
   
个人目前更喜欢拖到 Secondary Sidebar （右侧边栏），这样左边看文件右边看 Commit（Changed File 是可以点击后打开 VSCode 默认支持的 Diff 视图的）。

Changed Files 里支持文件夹操作是一个小亮点，我也不明白为啥其他插件都没做这个，有了这个之后，就很方便文件夹级别的勾选，以生成更精准的提交，为我下一个支持多步 commit 的 MVP 做准备。

> 框选功能已实现，但暂未放开，因为还有一些交互没想明白，技术产品经理有兴趣可以就这个与我交流交流。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231165634.png)

#### 2.3. 通知视图

通知视图下的功能基本和 `I Dont Care` 差不多，区别在于我们的 `Edit` 按钮点击后会自动打开面板视图，以方便用户修改。（因为 VSCode 默认的快捷输入框是不支持多行的……）
   
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231165222.png)

#### 2.4. 状态栏视图

实际在 generate commit 的时候，状态栏始终会实时显示进度，因此是默认的，如果您不希望在 generate commit 的过程中有任何干扰，可以切换 UiMode 为 `panel`，然后把它折叠即可。

   ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231170625.png)

### 3. Jetbrains

我过去几年首选的 IDE 都是 Jetbrains，因此对它的支持，我一旦有心情、有时间、有必要就会去做。

> 当然也欢迎 pr，基于 monorepo 的代码架构，您可以非常方便地适配您期望的其他平台。


## 如何定制您自己的 AI Commit 实现？

请阅读：https://oh-my-commit.github.io/guide/provider-docs.html，核心就是基于我们预设的 Context，实现对应的接口，并参考我们 provider 的打包配置到指定目录即可。

## 文档、社区、开源、商业化与 Roadmap

项目采用 MIT + Commons Clause 协议开源，这意味着：
- ✅ 个人和团队可以免费使用
- ✅ 可以自由修改和分发
- ❌ 不能直接商业化

本项目的主要链接：
- Github: https://github.com/oh-my-commit/oh-my-commit
- 文档（囿于精力，大部分文档内容都是 AI 自动生成，如有出入请以代码和 ReadMe 为准）: https://oh-my-commit.github.io 
- VSCode 插件: [Oh My Commit](https://marketplace.visualstudio.com/items?itemName=oh-my-commit.oh-my-commit)
- NPM 包：[npm | oh-my-commit Settings: Packages](https://www.npmjs.com/settings/oh-my-commit/packages)

合作、社群与答疑：
- 遇到问题，推荐优先提 issue: https://github.com/oh-my-commit/oh-my-commit/issues
- 对产品感兴趣，可以联系加入我的 AI 技术（免费）/产品/商业交流群

目前正在开发的功能：
- [x] 基础的 AI 提交信息生成
- [x] CLI & VSCode 双平台支持  
- [x] 插件化架构
- [x] 完整的提交工作流
- [ ] Changeset 集成 (进行中)
- [ ] prompt 管理系统 (计划中)
- [ ] 提交历史分析 (计划中)

一些设想：

如果我们在 commit 这个事情上打穿，把用户散落在各个 IDE、项目里的 commit 都贯穿起来，这个工具可以进化成？

1. **程序员的编程画像**
   - 你最常改动哪些类型的文件
   - 你的代码偏好是什么
   - 你的提交习惯如何

2. **团队的协作仪表盘**
   - 团队的代码修改热力图
   - 成员间的协作网络
   - 项目的演进历史

3. **智能输入法**
```bash
# 自动根据上下文推荐提交信息
$ git commit -m "
> 推荐 1: fix(login): resolve undefined user object issue
> 推荐 2: feat(auth): add token refresh mechanism
> 推荐 3: style(ui): update login form layout
"
```

4. ……

## 特别感谢

- 送我 cursor vip 的继刚兄，他打破了我对所谓“代码洁癖”坚持的幻想，结束了我十年人工编程的生涯，加速将我从一名程序员转变为技术型产品经理
- 提供 idea 与友情支持的春宇、胡博、宋奇、震杰、承平、子弹等一众朋友们
- Anthropic、Windsurf 等杰出的 AI 公司

## 写在最后

作为 2024 年的收官之作，Oh My Commi 虽小，却承载了我对 AI 时代开发工具的诸多思考。

这一个月的开发经历让我深深体会到：**工具的价值不仅在于解决问题，更在于激发可能**。

通过跟 AI 的密切协作，我看到了未来开发方式的一种可能性： **让 AI 处理重复性的工作，让开发者专注于更有创意的部分**。

这不仅仅是一个工具的诞生，更是对未来开发方式的一次探索。如果你也对此感兴趣，欢迎一起来玩：

```bash
echo "LLM YYDS \!"
```

## 花絮

### 1. 本项目的作者有两个

1% 的部分属于我，剩余 99% 属于 AI。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231173744.png)

### 2. 起个名字真难

起初名字叫 Yet Another AI Commit，后来叫 YAAC（雅刻），最后它的名字叫 Oh My Commit。

致敬：
- [Oh My Zsh - a delightful & open source framework for Zsh](https://ohmyz.sh/)
- [gpakosz/.tmux: Oh my tmux! My self-contained, pretty & versatile tmux configuration made with 💛🩷💙🖤❤️🤍](https://github.com/gpakosz/.tmux)

### 3. 初期一点微不足道的思考

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20241231152815.png)

### 4. 最近密集使用 AI 开发的一些小东西

得益于 AI，现在一有 idea 就会去用 AI 实现一番，毕竟干活的是 AI 不是自己（实质还是自己，只不过自己的劳动被抽象了，原先可能是 labor intensive，现在是 mind intensive）。

- 2024-10-09：通宵用cursor写了一个飞机大战游戏
- 2024-10-11：完全用 cursor 实现的飞机大战 V0.1.0（两小时初版，十小时趟坑）
- 2024-10-13：完全用 cursor 实现的飞机大战第二版（对 AI 来说，最难的是数值计算系统的正确性），拥有四种子弹：火焰弹、激光、导弹、散弹，额外的三种背包：生命回复、护罩、加速，三种敌军 + boss（boss 还没加完）
- 2024-10-15：基于 cursor 做的一个羽毛球预约系统（一个通宵实现）
- 2024-11-16：基于 AI 实现的一套数据解析方案 Sentiment based PDF Parser，目标是在 444.个长篇论文里挖掘某种语义的表格数据
- 2024-11-17：基于 AI 实现的 [一种平替硬件录音的解决方案](https://www.icloud.com/shortcuts/18e7dc042d4948b796ed18ea3380873a)，可以实现自动录音，录完自动存储到本地文件，然后自动上传到我的后端服务器，然后就可以在我的前端页面上看到上传的录音了，后续只要基于大模型做一些酷炫的分析，再配一个美观的 UI 即可，计划作为未来某主产品的一部分
- 2024-11-19：基于 AI 尝试复刻 eqMac 实现调节基于 HDMI 的外接接显示器音量，遗憾地是未能成功
- 2024-11-21：基于 Cursor 两小时实现 auto-gui agent（实验性质），代码开源在 [cs-magic/auto-gui: AI Browser Assistant (experimental) 基于大语言模型的浏览器自动化助手，能够通过自然语言指令完成各种浏览器操作任务。](https://github.com/cs-magic/auto-gui )，随缘不保证更新，但会争取实现一些可用的案例，并逐步扩展到整个操作系统级别，计划作为未来某主产品的一部分
- 2024-11-21：基于 Windsurf 十分钟生成了监测网络请求列表的谷歌插件（首战大捷，自此我开始重度使用 Windsurf，并为他付费）
- 2024-11-27：基于 Windsurf 开发的颜值很高的今日图腾小程序（正在内测阶段）
- 2024-12-21：基于 Windsurf 两小时开发的统一 zsh 相对路径显示的脚本，源码：github.com/cs-magic-open/zsh-git-relative-path

### 5. 三个月依赖 AI 编程的经验汇总

先放个简单暴力好用的 prompt，它实测下来非常好用，尤其适合 Windsurf + Claude 模型，如果你（或者我）有一天忘了可以回来看看：

```
每当我提出一个问题时，请您：

  
1. 这个问题是什么意思

2. 为什么会发生这个问题

3. 你打算怎么解决这个问题，置信度多少

4. 需要我怎么帮助你，能进一步提高你解决这个问题的信心
```

其他的，关于 Windsurf VS Cursor VS Bolt VS Devin， 关于 ChatGPT VS Claude VS Qwen VS Deepseek……

太多了，晚点单开一篇吧。