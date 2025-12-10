几天前，我在文章 [推荐一个 Mac 神器：重复操作一键自动化](https://mp.weixin.qq.com/s/L65ZFiQJGPUljxmAiXWZzg) 里介绍了基于 Alfred 实现快捷键打开无边记软件并创建画板的操作，顺带简单介绍了一下 Alfred 强大的工作流功能。

但这几天使用下来，发现偶尔会产生一些 bug，我们的快捷键有时候并不能顺利地实现目标。

我一开始以为是 Alfred 的执行不够可靠（尽管作为这么流行的一个软件，并不应该，事实证明也确实不是 Alfred 的锅）。

后来也以为是无边记不够可靠（尽管作为 Mac 的内置软件，并不应该，事实证明也确实不是无边记的锅）。

后来在我不断调试的过程中，终于突然意识到是什么问题了，原来是我们用于触发工作流的快捷键（`cmd+shift+alt+N`）与后续打开无边记后再创建画板的快键键（`cmd+N`）存在冲突，导致如果我们始终按住`cmd+shift+alt`不松开再按`N`会无效，且问题会累积：

![](http://cdn.cs-magic.cn/picgo/20251201055623385.png)

这是 alfred 的一个设计缺陷，它的快捷键默认会不断穿透给后续的工作流，而非一次性触发完结，最终影响了我们脚本后续的`keystroke "N" using {command down}`。

![](http://cdn.cs-magic.cn/picgo/20251201060023118.png)

我又基于 cc、gemini、chatgpt 等员工，花了好长时间，终于理出了几种可行的方案，以下一一罗列。

### 方案一、基于 GUI 操作绕开后续的快键键

既然问题是快捷键按压冲突，那么我们可以改换菜单栏点击。

![](http://cdn.cs-magic.cn/picgo/20251201060344448.png)

具体的话可以参考 gemini 给我们的脚本实现，它还贴心地考虑了中英文两种系统，智能到无以复加了，而且确实是有效的：

```applescript
	tell process "Freeform"
		try
			-- 方法：直接点击菜单栏，这会忽略你手上按着的 Alt/Shift 键
			-- 请根据你的系统语言选择下面的一行：

			-- 如果是中文系统：
			click menu item "新建看板" of menu "文件" of menu bar 1

			-- 如果是英文系统 (把上面中文的注释掉，启用下面这行)：
			-- click menu item "New Board" of menu "File" of menu bar 1

		on error
			-- 如果找不到菜单，可能是应用没完全加载或语言不对，此时可以尝试回退到模拟按键（虽然可能会失败）
			keystroke "n" using {command down}
		end try
	end tell
```

### 方案二、换个快捷键，以避免影响 cmd + N

![](http://cdn.cs-magic.cn/picgo/20251201220555938.png)

```applescript
tell application "Freeform"
    activate
    delay 0.1
    tell application "System Events"
        keystroke "n" using {command down}
    end tell
end tell
```

虽然 AI 给了这个方案，但我不愿意接受，因为我要记的快捷键实在太多了，每个快捷键的选择都是要比较慎重的。

但我后续想了一下，我觉得它这个方案是不太可行的。

因为我始终需要基于 modifier 触发，而我们的 edge case 就是按住 modifier 键不放。

所以除非我们的 modifier 键就是 cmd。

比如我们使用 `cmd + K` 去触发我们的 alfred workflow，然后松开 K 的时候，还保留着 `cmd`，最终 alfred workflow 发送 `cmd + N`，似乎完美。

经过实测，确实……

所以，勉强把这个也当做一版方案吧。

不过小心，这种办法还有个坑。

假如我们把触发键设置为 `cmd+N` 会怎样？

恭喜，你中奖了~

### 方案三、最佳实践：基于 Dispatch Key Combo

![](http://cdn.cs-magic.cn/picgo/20251201220656036.png)

这套方案，应该来说，是最符合 alfred 的开发范式的，因为它基于没有使用任何代码，而是非常清晰的基于 alfred 内置的一套封装，一步步地实现如下动作：

1. 检测用户按压某快捷键（`cmd + shift + alt + N`）
2. 打开对应 app（Freeform）
3. 等待一定时间（0.2s），用于缓冲快捷键
4. 使用 Dispatch Key Combo 触发新的按键（`cmd + N` 打开画布）

这套方案，ChatGPT 和 Gemini 都有给，但是 Gemini 给的描述是对的，ChatGPT 则是错的。

![](http://cdn.cs-magic.cn/picgo/20251201221253417.png)

因为 alfred workflow 里的 Dispatch Key Combo 功能是在 Outputs 下，而非 Actions。

![](http://cdn.cs-magic.cn/picgo/20251201221312261.png)

### 方案四、使用 hammerspoon

尽管 chatgpt 比 gemini 在事实校验上略逊一筹，但其实 cc 可能更差一些，它虽然有提及key-combo的方案，但是并没有作为标准答案，在后续与cc反复沟通都不能解决问题时，它甚至提出了另一种解决方案：hammerspoon。

![](http://cdn.cs-magic.cn/picgo/20251201221824950.png)

hammerspoon 允许我们写简单的 Lua 语言实现 MacOS 自动化。

![](http://cdn.cs-magic.cn/picgo/20251201221928871.png)

配置也比较简单（类似PicGO一样，只有几个简单的菜单项）：

![](http://cdn.cs-magic.cn/picgo/20251201222038594.png)

默认就一个 `init.lua` 脚本，不过我让cc模块化了一下，加了一个 `hotkeys.lua` 脚本，并配置了一个快捷键可以控制是否允许快捷键操作。

![](http://cdn.cs-magic.cn/picgo/20251201222141832.png)


像 PicGO 一样，它也有比较友好的log，方便调试：

![](http://cdn.cs-magic.cn/picgo/20251201221901761.png)

挺有意思的一个小软件，在没有方案三之前，我真地还是挺心动💓的（我先知道的方案四，后知道的方案三），但考虑到alfred的key-combo方案实在过于优雅，hammerspoon在我这就没有很大的吸引了。

btw，之前我们公众号读者还有推荐一个似乎比alfred更好用的软件叫 Raycast。

![](http://cdn.cs-magic.cn/picgo/20251201222526783.png)

我看了看，好像是专门做MacOS自动化的，确实有点意思，有机会可以多了解了解，现在alfred对我来说似乎够用🤔

![](http://cdn.cs-magic.cn/picgo/20251201222606662.png)

---

最后，有一说一，这几天在各种项目里穿梭时，每次我看cc与codex不相上下难舍难分之时，使用gemini（ai.studio），往往都能让一些问题迎刃而解，我还能说什么呢？

**Always Long Google.**

![](http://cdn.cs-magic.cn/picgo/20251201222859383.png)

---

今天的文章先写到这，再播报一条通知，12月5日下午2-5点上海徐汇区线下，我组织了一场Vibe Coding交流研讨会，邀请了几位在Vibe Coding领域非常有研究的好朋友，欢迎大家一起参加交流，感兴趣的可以添加我微信报名，囿于场地限制，限50人。

目前确认出席的嘉宾有：
- 某AI公司首席ai科学家，曾985高校讲师，专注于团队协作 vibe/spec、软件生命周期的管理
- 某月消耗7b token的AI Startup Founder ，胡润U25创业先锋
- 某新锐设计师、品牌主理人、UIUX 作品集导师，国内外奖项40余项
- ……

感谢某投资机构提供的超酷场地，某互联网大厂提供的精美伴手礼，各大模型公司提供的token支持等，我们周五不见不散！

![](http://cdn.cs-magic.cn/picgo/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20251130185941_79_5172.jpg)


