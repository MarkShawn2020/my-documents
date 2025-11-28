---
title: Alfred Workflow：把重复操作变成一键自动化
description: Mac 提效神器，任何重复操作都能一键触发
---

Mac 上总有些操作让你觉得"要是能一键搞定就好了"——比如每次想对比两张图，都要先打开某个 app、再新建画布、再开始操作。

今天介绍一个我常用的提效神器：**Alfred Workflow**。它本质上是一个自动化引擎，能把任何"重复操作序列"变成"一键触发"。

### Alfred Workflow 能做什么

简单说，它是 **触发器 + 脚本 + 串联** 的组合：

- **触发方式**：快捷键、关键词、文件拖拽、剪贴板内容...
- **执行能力**：AppleScript、Shell、Python、调用 API...
- **串联能力**：多个动作可以像流水线一样串起来

今天用一个实战案例来演示：**一键新建无边记画布**。

### 背景：为什么是无边记

最近创作时经常需要对比图片，调研了一圈发现 macOS 自带的「无边记」（Freeform）挺好用——无限画布，随意摆放，选中后复制自带白底，方便粘贴到其他地方。

比如这是我对比 Monica 和 Sider 产品时的效果：

![](http://cdn.cs-magic.cn/picgo/20251128160542163.png)

无边记自带 `Cmd+N` 新建窗口，但只能在 app 前台时用。我想要的是：**在任意场景下，按一个快捷键就能直接弹出新画布**。

这正是 Alfred Workflow 擅长的事。

### 实战：5 分钟搭建 Workflow

问了一下 Claude，确认 Alfred Workflow 可以实现：

![](http://cdn.cs-magic.cn/picgo/20251128160912698.png)

跟着搞起来。

**第一步：创建 Workflow**

打开 Alfred Preferences，点击 Workflows，创建一个新的：

![](http://cdn.cs-magic.cn/picgo/20251128160958485.png)

填写基本信息：

![](http://cdn.cs-magic.cn/picgo/20251128161148240.png)

**第二步：设置触发器**

右键 → Triggers → Hotkey：

![](http://cdn.cs-magic.cn/picgo/20251128161239197.png)

我选了 `Cmd+Shift+Option+N`（N for New canvas）：

![](http://cdn.cs-magic.cn/picgo/20251128161554133.png)

**第三步：添加执行脚本**

右键 → Actions → Run Script：

![](http://cdn.cs-magic.cn/picgo/20251128161630586.png)

粘贴这段 AppleScript：

```applescript
tell application "Freeform"
    activate
    delay 0.1  -- 等待 app 完全激活
    tell application "System Events"
        keystroke "n" using {command down}
    end tell
end tell
```

语言选择 `/usr/bin/osascript (AppleScript)`：

![](http://cdn.cs-magic.cn/picgo/20251128161740333.png)

**第四步：连接触发器和脚本**

把两个节点连起来，完成：

![](http://cdn.cs-magic.cn/picgo/20251128161855553.png)

### 效果

按下快捷键，首次会请求权限：

![](http://cdn.cs-magic.cn/picgo/20251128161944658.png)

确认后，以后随时随地一键新建画布。

### 举一反三

这个模式可以套用到很多场景：

```applescript
-- 通用模板
tell application "你的App"
    activate
    delay 0.1
    tell application "System Events"
        keystroke "快捷键" using {command down}
    end tell
end tell
```

比如：
- 一键新建 Notion 页面
- 一键打开 VSCode 最近项目
- 一键启动某个终端脚本

甚至不限于快捷键——你可以让 Workflow 执行任意 Shell 命令、调用 API、操作文件...

### AI 协作复盘

这次 Claude 给了正确的方向，但脚本细节有幻觉。

它原本给的是：

```applescript
keystroke "n" using {command down, shift down}
```

但实际上无边记的"新建窗口"是 `Cmd+N`，而 `Cmd+Shift+N` 是"显示主窗口"：

![](http://cdn.cs-magic.cn/picgo/20251128162404699.png)

![](http://cdn.cs-magic.cn/picgo/20251128162510357.png)

所以 AI 给的方案要验证，尤其是涉及具体 app 的快捷键这种细节。

---

Alfred Workflow 的玩法远不止这些，后续可以再聊聊更高级的用法。

> 注：Alfred 的 Workflow 功能需要 Powerpack（付费买断）。我把本文的 Workflow 打包好了，公众号回复「Alfred」即可获取，省去配置时间。

如果你有什么重复操作想自动化，欢迎评论区交流~
