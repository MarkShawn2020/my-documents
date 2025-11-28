最近在创作时，经常有把两张图片放在一起对比的需求，调研了一圈，比如 native 的解决方案是使用无边记（英文名：Freeform）这个 app，它是一个平凡的画布软件，可以放任意多张图片，任意摆放，在一键或者拖选复制，复制后会默认有个空白的背景色，方便我们在其他平台粘贴。

比如这就是我们在调研产品 Monica、Sider 时使用无边记的效果：

![](http://cdn.cs-magic.cn/picgo/20251128160542163.png)

无边记确实好用，也提供了`cmd+N`的快捷键，但只支持在无边记处于前台时才可以调用，而我希望它能在任意时刻通过快捷键打开。

### 跟着 AI 鼓捣

问了一下 claude，说可以使用 alfred 的工作流功能。

![](http://cdn.cs-magic.cn/picgo/20251128160912698.png)

alfred 我是用的，所以我确实希望尝试一下，否则的话我可能得考虑自己开发一个更方便的无边记了：）

![](http://cdn.cs-magic.cn/picgo/20251128160924789.png)

接下来我就跟着 claude 的指引，尝试在我们的 alfred 里搭建这样的 workflow。

首先先打开 alfred:

![](http://cdn.cs-magic.cn/picgo/20251128160958485.png)

接着点击 create a new workflow，会提示我们输入一些信息，我先试着填了一些我暂时能填的：

![](http://cdn.cs-magic.cn/picgo/20251128161148240.png)

接着跟着教程 右键-triggers-hotkey：

![](http://cdn.cs-magic.cn/picgo/20251128161239197.png)

然后就让我们填要绑定什么键。

由于无边记的英文是 Freeform，首字母是 F，但 F 一般和 Find 绑定，而且 Find 是一个超高频操作，所以不太合适。

考虑到它是创建新的窗口，又是画布形式，我就给了 `cmd+shift+alt+N`：

![](http://cdn.cs-magic.cn/picgo/20251128161554133.png)

接着要右键创建一个新的脚本：

![](http://cdn.cs-magic.cn/picgo/20251128161630586.png)

再粘贴脚本：

```applescript
tell application "Freeform"
    activate
    delay 0.1
    tell application "System Events"
        keystroke "n" using {command down}
    end tell
end tell
```

记得勾选`/usr/bin/osascript (AppleScript)`，这个是 mac 官方的脚本器，会比其他的优先级更高一些：

![](http://cdn.cs-magic.cn/picgo/20251128161740333.png)

最后再连接一下两者，就成功了：

![](http://cdn.cs-magic.cn/picgo/20251128161855553.png)

### 看看效果。

执行快捷键，显示：

![](http://cdn.cs-magic.cn/picgo/20251128161944658.png)

确认后，后续就好了。

### 复盘

这次 claude 给的指引里面，有一定的幻觉。

比如它给的原程序是：

```applescript
keystroke "n" using {command down, shift down}
```

也就是说 alfred 打开无边记后，调用 `cmd+shift+N`，但事实上，无边记默认打开新窗口的快捷键是 `cmd+N`，而 `cmd+shift+N`打开的是主窗口。

![](http://cdn.cs-magic.cn/picgo/20251128162404699.png)

![](http://cdn.cs-magic.cn/picgo/20251128162510357.png)

所以我们要简单修改一下。

---

以上就是本期我们研究的一点小小心得啦，如果你想持续学习此类小技巧，欢迎关注我们，感谢~
