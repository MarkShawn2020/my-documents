我已经让 claude code 给我写了一款独立的 python 程序，它可以监听剪切板实现粘贴时自动转换成文本。

```shell
python clipboard_monitor.py
🚀 Claude Code 剪切板监听器已启动
📁 临时文件目录: /Users/mark/projects/claude-code-clipboard-monitor/.tmp
📋 监听剪切板图片中...
🛑 按 Ctrl+C 停止
✅ 图片已保存: .tmp/clipboard_20250711_174708.png

```

我甚至还研究了 claude code 的`--add-dir`指令，让脚本安装时自动把 `~/.neurora/claude-code`文件夹加入工作区，然后让我们的监控程序把图片输出到`~/.neurora/claude-code/screenshots`下。

```shell
jq .permissions.additionalDirectories ~/.claude/settings.json
[
  "~/.claude",
  "~/.neurora/claude-code"
]
```

这样所有的 claude code 程序都可以始终读取到我们的最新图片。

但有个**致命问题**，转换的动作是在复制的时候实现，而非在粘贴的时候。

这就导致，在复制完图片后，无论在哪个软件内粘贴，都会粘贴成一行文字：`@.tmp/xxx.png`，这显然副作用太大了。

并且还让 claude code 在 plan mode 下给我出优化方案：

```
╭──────────────────────────────────────────────────────────────────────────────────────────────────────────╮
│ Ready to code?                                                                                           │
│                                                                                                          │
│ Here is Claude's plan:                                                                                   │
│ ╭──────────────────────────────────────────────────────────────────────────────────────────────────────╮ │
│ │ Optimized Clipboard Monitoring Solutions                                                             │ │
│ │                                                                                                      │ │
│ │ Option 1: Smart Clipboard Buffer (Recommended)                                                       │ │
│ │                                                                                                      │ │
│ │ - Create a clipboard buffer that stores original image data                                          │ │
│ │ - Only replace clipboard when Claude Code window is active AND paste is detected                     │ │
│ │ - Immediately restore original image after successful paste                                          │ │
│ │ - Use proper platform-specific clipboard APIs for reliable image restoration                         │ │
│ │                                                                                                      │ │
│ │ Option 2: Drag-and-Drop Simulation                                                                   │ │
│ │                                                                                                      │ │
│ │ - Save images to temp directory without modifying clipboard                                          │ │
│ │ - Automatically simulate drag-and-drop into Claude Code when detected                                │ │
│ │ - Preserve original clipboard completely                                                             │ │
│ │                                                                                                      │ │
│ │ Option 3: System Notification + Quick Copy                                                           │ │
│ │                                                                                                      │ │
│ │ - Save images silently without clipboard modification                                                │ │
│ │ - Show system notification with file path                                                            │ │
│ │ - Provide quick-copy button in notification for easy @filepath copying                               │ │
│ │                                                                                                      │ │
│ │ Option 4: Virtual Clipboard Overlay                                                                  │ │
│ │                                                                                                      │ │
│ │ - Create a virtual clipboard layer that intercepts only Claude Code paste operations                 │ │
│ │ - Route image pastes through file system while preserving text/other content                         │ │
│ │ - Transparent to other applications                                                                  │ │
│ │                                                                                                      │ │
│ │ Implementation Priority:                                                                             │ │
│ │                                                                                                      │ │
│ │ 1. Fix smart_monitor.py image restoration logic                                                      │ │
│ │ 2. Add proper platform-specific clipboard APIs                                                       │ │
│ │ 3. Implement drag-and-drop simulation as fallback                                                    │ │
│ │ 4. Add notification system for manual workflow                                                       │ │
│ │                                                                                                      │ │
│ │ Benefits:                                                                                            │ │
│ │                                                                                                      │ │
│ │ - Zero impact on other applications                                                                  │ │
│ │ - Seamless Claude Code integration                                                                   │ │
│ │ - Reliable cross-platform operation                                                                  │ │
│ │ - Fallback options for different scenarios                                                           │ │
│ ╰──────────────────────────────────────────────────────────────────────────────────────────────────────╯ │
│                                                                                                          │
│ Would you like to proceed?                                                                               │
│                                                                                                          │
│   1. Yes                                                                                                 │
│ ❯ 2. No, keep planning                                                                                   │
│                                                                                                          │
╰──────────────────────────────────────────────────────────────────────────────────────────────────────────╯

```

但说实话我觉得它的这些方案**都不是很靠谱**。

不得不转变思路。

---

最后我想到，既然拖动是一个非常友好的交互方式，但我们又无法 hook claude code 的拖动，那要不我们做一个剪切板管理器，它可以列出剪切历史，并且支持常驻拖动，或者一键复制图片为文件。

```ad-tip

claude code 支持几种输入图片的方式：
1. 手动@工作区内的图片文件
2. 拖动一个图片文件到claude code界面，这个文件往往在iFinder中，但实测在我的截图软件里也是可以拖的
3. 在iFinder中复制一张图片文件，然后在claude code中粘贴

值得注意的是，我们提的一直是图片文件，而非图片本身，比如你在浏览器里复制一张图片，那会以二进制形式存储在剪切板里，是无法直接在claude code里粘贴的。
```

于是，又大概肝了 2 小时，期间同时让 claude code 维护自己的主线产品，所以也没算耽误事。

但后面用剪映剪视频，很耽误事。等我忙完这段时间，就 vibe coding 一个 mini 剪映，目前积累了不少 know how。

最后直接看视频吧，完成度还是很高的。

【视频】

除了视频里提到的点之外，这个产品的整体思路设计是：

1. 要有一个GUI，但不要驻入docker，也就是Tray模式运行，通过快捷键或者状态栏唤起
2. 支持历史记录，并且支持像alfred那样对文本、图像、文件不同周期的历史记录
3. 支持双列查看，左边列表，右边预览
4. 支持拖动图片为文件（这是核心差异点与动机，我已经为此苦恼了好几周）
5. 支持多套模板的分享图（类似xx卡片）
6. 支持用户系统以充当AI产品的一部分数据来源（另一个合作伙伴想要的点）
7. ……

这产品也没那么复杂，我直接放一下prompt历史，大家感受一下这个产品是怎么开发出来的。

（导出工具是我前几天开发的 [claude-code-manager](https://github.com/MarkShawn2020/claude-code-manager)，大家可以多多支持一下，我把它做的更牛逼更好用~）。

```shell
➜  /Users/mark/projects/n-clip git:(main) ccm stat --current --full-message
────────────────────────────────────────────────────────────────────────────────
Project 01: /Users/mark/projects/n-clip
  TOTAL SIZE: 4.47 MB
  History Details (35 entries):

  1. 请开发一个跨平台剪切板管理软件，UI大致像Alfred剪切板一样，支持快捷键唤出  [Image #1]
  2. [Pasted text #1 +92 lines]
  3. [Pasted text #1 +9 lines]  这些报错怎么解决呢
  4. 好地，现在我们把目前项目（模板）改造成我们的 n-clip （neurora的剪切板管理软件）  它有类似alfred一样的UIUX：[Image #1]
  5. #你不要自动build，这会花很多时间
  6. 我现在dev启动了，UI很漂亮，目前你支持劫持文字，但是不支持劫持图片、文件
  7. 很棒，请支持拖拽移动窗口，并且支持记忆，记忆可以用jotai
  8. 不是，我们是electron程序，我记得天生就支持拖拽？为什么你这个要在视图区域内额外加个三个点……太离谱了
  9. 我发现你这个app没有跑马灯，所以拖不了。。。 （但我也确实不想要跑马灯）
  10. <div class="App"><div class="clipboard-manager"><div class="drag-area"></div><div class="header"><div class="search-container"><div class="search-icon">🔍</div><input type="text" placeholder="All Snippets" class="search-input" value=""></div></div><div class="items-container"></div><div class="no-results">No items found</div></div></div>  你现在只有clipboard-manager是可以拖的，而我是要整个App可以拖，明白吗？
  11. /compact
  12. 点击某一项的时候会触发复制，这个是合理的，但是我们应该保证剪切历史里没有重复的
  13. 为什么我打开程序后，再cmd+shift+V打开alfred剪切板窗口，然后我们的程序就消失了，并且无法再切换显示出来？
  14. 很好，点击不同项之后，高亮应该切换过去
  15. 很好，然后我们要采用双列布局，左边列显示每条复制的条目，右边列是预览区域，显示全部的文本、图片等
  16. 最小宽度可以设置地更小一些； 最小高度有问题，高度很小的时候，内部内容溢出了
  17.  height: 100vh; 导致外窗相对于内窗都没有padding了，不好看
  18. 单列转双列的breakpoint可以再小点
  19. app中底部应该由我们n-clip branding标识
  20. 应该是NClip，斜一点，酷一点，以及不要解释，而是用一句slogan 以及当失去焦点时应该自动hide
  21. 好地，现在请不要让程序出现在cmd+tab列表里，我们完全通过快捷键或者状态栏呼唤它
  22. 很好，现在请支持拖拽图片到其他程序（以文件形式粘贴）
  23. 没用，iFinder里拖拽图片到别人程序可以，但我们的程序拖拽图片就不行。。。
  24. 还是不行！ Please UltraThink ！
  25. 可以！ 但我发现： 1. 只有左侧列的图片可以拖，右侧的预览区不可以拖 2. 左侧列拖动的时候文字被选中了，这不应该发生
  26. 要支持删除，以及生成精美的分享卡片
  27. 图片的话应该支持点击全屏预览
  28. 很好，最后请支持这些数据的持久化，目前重启后就都没了，也许我们应该用个sqlite存储？
  29. 我希望存储目录在 ~/.neurora/n-clip/
  30. 点击文转图按钮没有效果了
  31. 文字很长的话，溢出屏幕了，分享卡片应该可以选各种模板和比例，默认3:4
  32. 不对，当我们点击生成卡片的时候，应该弹窗，方便我们在各种模板与比例里调试，最后我们再有一个复制按钮  然后即便是纯图片，也是可以点击那个生成卡片按钮的，因为都是模板，可以是wrapper（只不过文字更丰富也更难一些）
  33. 新的弹窗要独立，这样可以获得更自由的显示空间
  34. Failed to open share card window: TypeError: Cannot read properties of null (reading 'once')     at createShareCardWindow (file:///Users/mark/projects/n-clip/dist-electron/main/index.js:318:19)     at async file:///Users/mark/projects/n-clip/dist-electron/main/index.js:709:5     at async WebContents.<anonymous> (node:electron/js2c/browser_init:2:87023)
  35. [Pasted text #1 +49 lines]  点击后没有展示出独立窗口，第二次点击报错了


```

以上就是我全部开发的过程，有一点技术名词，但不多。

另外，我是先clone了一份模板，然后开发的，以下是我最近比较喜欢用的模板/框架：
- SaaS网页：[Jonghakseo/chrome-extension-boilerplate-react-vite: Chrome Extension Boilerplate with React + Vite + Typescript](https://github.com/Jonghakseo/chrome-extension-boilerplate-react-vite)
- 桌面软件：[electron-vite/electron-vite-react: :electron: Electron + Vite + React + Sass boilerplate.](https://github.com/electron-vite/electron-vite-react)
- Chrome插件：[Jonghakseo/chrome-extension-boilerplate-react-vite: Chrome Extension Boilerplate with React + Vite + Typescript](https://github.com/Jonghakseo/chrome-extension-boilerplate-react-vite)
- 小程序：一直用React友好的Taro，因为实在不想碰Vue生态；不过这种选型的执拗在vibe coding时代可能有更好的解决方案，也许我可以重新用uniapp了，毕竟我不需要写vue，我只要看得懂就行，那还是没啥压力的

以及，这是本期涉及到的几个项目的地址：
- [MarkShawn2020/n-clip: 一个现代化的剪切板管理器，基于 Electron + React + TypeScript 构建。](https://github.com/MarkShawn2020/n-clip)
- [MarkShawn2020/claude-code-clipboard-monitor: 智能监听剪切板图片，自动拖拽到 Claude Code 窗口或保存到本地，专为 Claude Code 优化的剪切板增强工具。](https://github.com/MarkShawn2020/claude-code-clipboard-monitor)
- [MarkShawn2020/claude-code-manager: A powerful CLI tool for managing Claude Code workflows with automatic execution tracking and analytics.](https://github.com/MarkShawn2020/claude-code-manager)
- 

以上，关注我，Vibe Coding 不迷路~

---



目前我同时在维护三个技术大群，感兴趣的技术朋友欢迎加入，包括：
- 与WayToAGI、Stain、Xlu一起维护的Vibe Coding大类交流群，目前200+人
- 与Stain一起维护的Claude Code交流群，目前200+人
- 与Xlu一起维护的Gemini Code交流群，目前200人左右

以及两个AI大类群，都500满人了， 现在准备开启第三个，主要面向创业者、投资人、产品经理、工程师、设计师、运营、增长等，保持对AI创投的敏感度，如果你感兴趣也欢迎加入，但我精力实在有限，所以提高一下门槛，299一年，交个朋友为主。


