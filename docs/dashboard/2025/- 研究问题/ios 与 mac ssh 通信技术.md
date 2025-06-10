---
date: 2022/07/23
---

# ios 与 mac ssh 通信技术

## AppleScript Relative

### 发送按键事件

根据这篇核心参考（推荐）：[Complete list of AppleScript key codes](https://eastmanreference.com/complete-list-of-applescript-key-codes)，我们知道箭头键是不支持使用`keystroke`而只能使用按键码的。

一些 sample 如下：(ref: https://apple.stackexchange.com/a/314650):

```osascript
tell application "System Events"
    key code 124 using {shift down, command down} --> Right arrow
    key code 8 using command down --> ⌘-C
    key code {4, 14, 37, 37, 31, 47} --> H, e, l, l, o, .

    keystroke "v" using command down --> ⌘-V
    keystroke "Hello." --> H, e, l, l, o, .
end tell
```

ref:

- [macos - AppleScript Command Sendkeys? - Ask Different](https://apple.stackexchange.com/questions/314647/applescript-command-sendkeys)

- [macos - How do I automate a key press in AppleScript? - Ask Different](https://apple.stackexchange.com/questions/36943/how-do-i-automate-a-key-press-in-applescript)

## XCode Relative

### 针对 Simulator 和 Device 使用不同的 framework 分别编译

搜了一下，有不少方法，但都比较复杂，比如 [iphone - iOS: How to add different frameworks for device and simulator in the same code xcode swift? - Stack Overflow](https://stackoverflow.com/questions/48785934/ios-how-to-add-different-frameworks-for-device-and-simulator-in-the-same-code-x) 中给了一个谷歌的脚本……

其他答案还有： [Using separate device and simulato… | Apple Developer Forums](https://developer.apple.com/forums/thread/86759)

最简单的办法还是将 target 复制一份，然后分别设置每个 target 所需的不同的 framework，这个办法最好在我们导入 framework 之时就先分配好。

多说一句，这种复制的办法，我发现没法单独指定 destination，好像指定了一个后，另一个 target 也会跟着变……真地 annoying……

### 在 XCode 中重命名一个变量

方法 1：快捷键`Command + control + E`。

方法 2：选中变量后，右键`Refactor`里面的`Rename`，这个挺好的，跟 jetbrains 操作习惯差不多。

ref:

- [ios - variable name changing in whole program - Stack Overflow](https://stackoverflow.com/questions/23865830/variable-name-changing-in-whole-program)

- [Finding and Refactoring Code | Apple Developer Documentation](https://developer.apple.com/documentation/xcode/finding-and-refactoring-code)

## `NMSSH` relative

### 在 Xcode 中配置`NMSSH`

核心参考：

- [Build and use in your iOS project · NMSSH/NMSSH Wiki](https://github.com/NMSSH/NMSSH/wiki/Build-and-use-in-your-iOS-project)

核心要领:

1. 基于`NMSSH-iOS.xcodeproj`编译时需要设置好`Destination`，simulator 和 real device 需要分别编译
2. 编译完成后，要通过`show build folder`定位到 product-framework 所在文件夹，并一层层往下找到 framework 文件
3. 将 framework 导入自己的 xcodeproject 的时候，可以不用向官网一样去修改`build phase`，因为可以在导入时弹窗选择，但是一定要选中`copy`选项，否则编译时将找不到 framework
4. 弹窗选完之后，还要在 target 页面，把 framework embed 进工程，否则也会找不到。target 为 simulator 时只需要选非签名 embed 即可，真机运行必须要签名，签名方法之前自动化时已研究过，此处会记录之前的签名信息，即”川南“。

如果没有配置好的话，一般会出现各种找不到的问题，例如：

- [Undefined symbols for architecture i386: · Issue #28 · NMSSH/NMSSH](https://github.com/NMSSH/NMSSH/issues/28)

### 在 `swift` 中使用 `objective-c`，从而调用`NMSSH`

基于 [ios - How to use NMSSH in swift - Stack Overflow](https://stackoverflow.com/questions/26110980/how-to-use-nmssh-in-swift) 这个帖子我们知道，我们需要首先在`swift`工程中建立 `objective-c`桥，方法参考： [How do I call Objective-C code from Swift? - Stack Overflow](https://stackoverflow.com/questions/24002369/how-do-i-call-objective-c-code-from-swift)，主要基于里面的这个答案：https://stackoverflow.com/a/24005242/9422455

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ios-ssh-1655142628111-d2fd273cce2536145a7cfe322fbfe280673e52776e616b6b3b967eceec1fa4fa.png)

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ios-ssh-1655142646923-195f1368d259f5f6735f363b234d52f809696e612dee1c8f29b73c5a6347837c.png)

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ios-ssh-1655142671067-50e01e541764eeb440f5b8a921fdd1006680e9863d97117b9413ab866c0e9831.png)

根据上面的步骤先完成基础搭建后，再根据 [ios - How to use NMSSH in swift - Stack Overflow](https://stackoverflow.com/questions/26110980/how-to-use-nmssh-in-swift) 把`NMSSH`的调用方法按葫芦画瓢装进去。

### 基于`NMSSH`执行 mac 命令

参考： [ssh - NMSSH for iOS - listening and parsing data from a channel - Stack Overflow](https://stackoverflow.com/questions/31336795/nmssh-for-ios-listening-and-parsing-data-from-a-channel)

```objective-c
NSError *error = nil;
NSString *response = [session.channel execute:@"ls -l /var/www/" error:&error];
NSLog(@"List of my sites: %@", response);
```

## Swift Relative

ref:

- Swift 官方教程（Apple）：[Swift | Apple Developer Documentation](https://developer.apple.com/documentation/swift#2984801)

## SwiftUI relative

ref:

- SwiftUI 官方教程（Apple）：[Creating and Combining Views — SwiftUI Tutorials | Apple Developer Documentation](https://developer.apple.com/tutorials/swiftui/creating-and-combining-views)

### change background color

```swift
    Text("Hello, World!")
        .padding()
        .foregroundColor(.red)
        .background(Color.yellow)
        .background(Color(red: 0.03, green: 0.03, blue: 0.03))
```

ref:

- [SwiftUI Color :: TrozWare](https://troz.net/post/2020/swiftui-color/)

- [How can I change background color of button in SwiftUI? - Stack Overflow](https://stackoverflow.com/questions/56610253/how-can-i-change-background-color-of-button-in-swiftui)

### fixed: button only respond to text part

```swift
Button(action: {
    //code
}) {
    Text("Click Me")
    .frame(minWidth: 100, maxWidth: .infinity, minHeight: 44, maxHeight: 44, alignment: .center)
    .foregroundColor(Color.white)
    .background(Color.accentColor)
    .cornerRadius(7)
}
```

ref:

- [SwiftUI Button tap only on text portion - Stack Overflow](https://stackoverflow.com/questions/57333573/swiftui-button-tap-only-on-text-portion)

## Objevtive-C relative

### obejctive-C function (especially multi args)

ref:

- [Objective-C Functions](https://www.tutorialspoint.com/objective_c/objective_c_functions.htm)

关于不理解 `objective-c` 中函数多参数时需要命名的讨论，很有意思：- [Don't understand multiple parameter declarations in objective-c - Stack Overflow](https://stackoverflow.com/questions/3026432/dont-understand-multiple-parameter-declarations-in-objective-c)

### `NSString` relative

ref:

- [NSString by example](https://eezytutorials.com/ios/nsstring-by-example.php#.YqeALRO-uDV)

- [objective c - Name for %@ %d in an NSString - Stack Overflow](https://stackoverflow.com/questions/7906948/name-for-d-in-an-nsstring)

- [String Format Specifiers](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Strings/Articles/formatSpecifiers.html)

### 在 `objective-c` 中合并字符串

我最终使用了 `NSMutableString`，然后使用其`appendString`或者`appendFormat`方法，用起来还算顺手。

ref:

- [iOS NSString 和 NSMutableString - 简书](https://www.jianshu.com/p/4202259c654e)

- [Shortcuts in Objective-C to concatenate NSStrings - Stack Overflow](https://stackoverflow.com/questions/510269/shortcuts-in-objective-c-to-concatenate-nsstrings)

- [iphone - How to append int value to string? - Stack Overflow](https://stackoverflow.com/questions/5893793/how-to-append-int-value-to-string)

- [iphone - Converting int into NSString - Stack Overflow](https://stackoverflow.com/questions/12153051/converting-int-into-nsstring)

- [objective c - Append string with variable - Stack Overflow](https://stackoverflow.com/questions/7070046/append-string-with-variable)

- [ios - How to append a string to NSMutableString - Stack Overflow](https://stackoverflow.com/questions/9180671/how-to-append-a-string-to-nsmutablestring)
