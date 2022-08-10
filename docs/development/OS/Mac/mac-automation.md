# mac 自动化

## applescript

### 与 shellscript 的互相调用

1. 在 applescript 中调用 shellscript：`do shell script "MY SCRIPT"`（注意要用双引号，单引号不行，因此内部的双引号要转义）, ref: - [Mac Automation Scripting Guide: Calling Command-Line Tools](https://developer.apple.com/library/archive/documentation/LanguagesUtilities/Conceptual/MacAutomationScriptingGuide/CallCommandLineUtilities.html)
2. 在 shellscript 中调用 applescript: `osascript -e "MY SCRIPT"`（如果有多行，比如 `tell xxx; do something; end tell;`这种，可以每行分别用一个`-e`，ref: https://stackoverflow.com/a/49079025/9422455）

### 注释

单行：`--` 或者写成 `-->`

多行：`(*` + `*)`, ref: - [Comments | Basics of AppleScript](http://downloads.techbarrack.com/books/programming/AppleScript/website/basics/comments.html)

### 快捷键

如果想给自动化程序绑定快捷键，就要使用 service（比如 quick action），见：- [How do I assign a keyboard shortcut to an AppleScript I wrote? - Ask Different](https://apple.stackexchange.com/questions/175215/how-do-i-assign-a-keyboard-shortcut-to-an-applescript-i-wrote)

### 输出产品

1. workflow 和 app 是不同的，workflow 里的元素很少，但 app 有自己的配置文件，但 app 在运行时仍旧是调用的 automator，因此 notification 的 icon 貌似还是改不了的

### 更换图标

这个可以解决 app icon 更换的问题，但是尝试了一下不可以更换通知的 icon：[applescript - Change icon of notification when using osascript -e "display notification" - Stack Overflow](https://stackoverflow.com/questions/48856158/change-icon-of-notification-when-using-osascript-e-display-notification)
