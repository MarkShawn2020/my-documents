---
author: MarkShawn2020
created: 2022-02-12
---

# 编程设计艺术思考（持续更新）

1. [快捷键设计](#快捷键设计)
   1. [与代码块相关的快捷键设计](#与代码块相关的快捷键设计)
      1. [对比分析与总结](#对比分析与总结)
      2. [跳转与选中代码块](#跳转与选中代码块)
      3. [折叠与展开代码块](#折叠与展开代码块)
      4. [快捷键修改前后对比](#快捷键修改前后对比)
   2. [bugfix: why `cmd + alt + \` converted to be `cmd + c`](#bugfix-why-cmd--alt---converted-to-be-cmd--c)

## 快捷键设计

在程序开发中，为了提高工作效率，我们一般都会使用快捷键。即使是非程序员，`ctrl + C/X/V/Z` 的组合也是烂熟于心（尽管他们对于系统内部发生了什么可能一无所知，尽管，也确实没必要知道。）

显然，程序员面临着更大的挑战，因为他们可能会接手不同的操作系统（windows, mac, linux 等)，面临不同的场景（vim, IDE, office 等），也往往会使用多个平台的软件（vscode, jetbrains 等），更不用说其他第三方软件/插件了。种种以上，对于对效率有着执着追求的程序员，如何管理与记忆这些互相掣肘的快捷键，将是一个头疼的问题。

甚至于我，从一开始只用鼠标点点点，到现在尝试统一各大平台的快捷键，我也已经走过了五年以上的时间（码龄）。我决心再往前一步，仔细分析一下快捷键的设计问题。

!!!tip vscode 的默认快捷键配置文件在：`/keybindings.json`，可以通过快捷菜单，输入`Open Default Keyboard Shortcuts(JSON)`打开。

    jetbrains打开快捷键的菜单：Preference(`cmd + ,`) --> Keymap

我们先考虑第一种问题（关于操作系统），因为我们可以暂定 mac 的`command`键=windows 的`windows`键，mac 的`option`键=windows 的`alt`键，由此`shift`, `ctrl`, `alt`键成为各大平台的通用键。原先我希望 mac 的`command`键能够提供额外的控制，但在我后来使用虚拟机经历了长达一个月的按键切换折磨后，我终于想到了一个如此简单粗暴却十分有效的办法：将`command`键映射成`ctrl`键，于是乎一切是如此和谐。因此，基于这些考虑，在我接下来的文章与设计中，将只会使用三个组合键：`ctrl | shift | alt`，多余的将不用，这是为通用性考虑，也为减少不必要的麻烦。

接下来第二个问题，vim, IDE or office? 在我学编程之前与初期，office 仍旧是我的主力输出工具，无论是文章创作与 ppt 展示，但后来便基本不用了。2021 年中旬开始，我频繁地开始使用 vim 直到 2022 年才逐渐领悟 vim 的各种神奇与方便。尽管如此，vim 与传统 IDE 的快捷键习惯仍是有泾渭分明的差异，因为在 vim 中，没有所谓真正意义上的快捷键（组合键 + 普通键），而都是基于命令式的、或是单键、双键式的，一方面很难统一，另一方面甚至没有统一的必要。

比如在 vim 的 normal 模式，按`ma`就生成了一个命名为 a 的标签，后续可以通过按`backquote + a`迅速定位到该标签，这比所谓的快捷键要快很多。试想一下，如果是快捷键，你将如何设计呢？假如你把`ctrl + alt`当做标签的触发键，然后以任意字母表示标签名，接下来还要设置一个键回到该标签，比如说`ctrl + alt + shift`，但是考虑到字母键太多了，将导致你几乎没有快捷键使用了。

如果硬要设计，也不无解药，现在的 IDE（vscode, jetbrains），都提供了二键组合，因此您可以设置`ctrl + m`触发标记标签（然后紧接着按一个键标记标签名），`ctrl + alt + m`触发定位标签（然后紧接着按一个键定位到该标签名所在位置）。可想而知，比 vim 慢了很多。

但毕竟 vim 的快捷键不是交互系统的通用设计范式，我们主要思考的是组合键，vim 作为独立的生态，我们自然也就无法兼容了，因此也不在本文的考虑范围内。也许可以考虑 office，这个留给有需求的读者自行考虑。

因此本文主要探讨不同 ide 之间的快捷键设计与我们的选择与设计问题，因此，更适合程序员阅读。

以下将从一些场景出发进行思考。

### 与代码块相关的快捷键设计

由于当代程序语言普遍是基于结构体语法设计的，例如 C/C + + /Java/JS 等主流语言(python 的缩进可以单向定位)都是基于括号来标识一个结构体的开始与结束，因此它们具有良好的定位功能。即：

1. 对于任意一个标准的程序片断，可以基于括号的一端，唯一标示其另一端
2. 基于上述便利，再基于标点或换行，可以在任意位置唯一标示其当前所在的结构体

于是，对于结构体来说，我们至少有以下功能可以设计：跳转定位、批量选择、折叠与展开。

#### 对比分析与总结

我们尝试对几个平台进行快捷键对比，分析学习各大厂商是怎么设计的，并给出我们自己的一份快捷键定制菜单。

!!!tip vscode 与 jetbrains 关于代码块的快捷键设计对比总结

    1. jetbrains对于`alt | shift`的使用比较符合用户习惯，而vscode则有些不统一；
    2. 但vscode对`[ | ]`的使用是优于jetbrains的`+ | -`的；
    3. vscode尽管没有实现部分指令，但是经过仔细考虑，也确实可以接受；
    4. 两者五五开，都需要经过用户自己的定制，才能较好地在两个平台之间获得近似的体验。

| item | vscode on macOS | jetbrains(pycharm) on macOS | custom design |
| --- | --- | --- | --- |
| jump to matched bracket | editor.action.jumpToBracket:<br/>`shift + cmd + \` | Move Caret to Matching Brace:<br/>`ctrl + m` | `cmd + \` |
| select matched brackets | editor.action.selectToBracket: none | none | `shift + cmd + \` |
| jump to left bracket | none | Move Caret to Code Block Start:<br/>`alt + cmd + [` | none |
| jump to right bracket | none | Move Caret to Code Block End:<br/>`alt + cmd + ]` | none |
| select to left bracket | none | Move Caret to Code Block Start with Selection:<br/>`shift + alt + cmd + [` | none |
| select to right bracket | none | Move Caret to Code Block End with Selection:<br/>`shift + alt + cmd + ]` | none |
| extend selection | none | Extend Selection:<br/>`alt + up` | `alt + up` |
| shrink selection | none | Shrink Selection:<br/>`alt + down` | `alt + down` |

| item | vscode on macOS | jetbrains(pycharm) on macOS | custom design |
| --- | --- | --- | --- |
| collapse this level | editor.fold:<br/>`alt + cmd + [` | Collapse:<br/>`cmd + -` | `cmd + [` |
| expand this level | editor.unfold:<br/>`alt + cmd + ]` | Expand:<br/>`cmd + +`/`cmd + =` | `cmd + ]` |
| collapse this level recursively | editor.foldRecursively:<br/>`cmd + k, cmd + [` | Collapse Recursively:<br/>`alt + cmd + -` | `alt + cmd + [` |
| expand this level recursively | editor.unfoldRecursively:<br/>`cmd + k, cmd + ]` | Expand Recursively:<br/>`alt + cmd + + `/`alt + cmd + =` | `alt + cmd + ]` |
| collapse this document | editor.foldAll:<br/>`cmd + k, cmd + 0` | Collapse All:<br/>`shift + cmd + -` | `shift + cmd + [` |
| expand this document | editor.unfoldAll:<br/>`cmd + k, cmd + j` | Expand ALL:<br/>`shift + cmd + +`/`shift + cmd + =` | `shift + cmd + ]` |
| collapse/expand to level [K] | none | Expand to Level [K]:<br/>`cmd + *, [K]` | `alt + cmd + \,[K]` |
| collapse/expand this document to level [K] | editor.foldLevel[K]:<br/>`cmd + k, cmd + [K]` | Expand All to Level [K]:<br/>`alt + cmd + *, [K]` | `shift + alt + cmd + \,[K]` |

#### 跳转与选中代码块

vscode 对括号跳转只提供了非常简单的一个快捷键`shift + cmd + \`，它的作用就是从当前光标开始向前定位到第一个英文圆括号或者花括号之左；如果是左括号，则再按一次将向前定位到右括号之左；否则，向后定位到左括号之左；如果没有对应的括号，则原地不动。

同时，vscode 也提供了`editor.action.selectToBracket`的指令，但是没有提供默认快捷键。作用是选中下一个代码块（英文圆括号或花括号之间的内容， 包括括号），光标会定位在右括号之右。

如果单从这两个命令来看，我觉得把`jumpToBracket`记为`cmd + \`，把`selectToBracket`记为`shift + cmd + \`是比较合理的（毕竟大多数情况下，`shift`都用于选中）。

vscode 没有提供任何方向性地跳转与选中代码块的指令，这个似乎也可以理解，因为一般选中代码，很少有需求是从某个光标开始到某个代码块的开始或结束，要选一般都是选整个代码块，也就是`editor.action.selectToBracket`，从这个角度去思考，vscode 阉割这部分功能也可以被认为是合理的。

jetbrains 相比较 vscode 来说，命令就更加丰富一些，除了直接选中代码块没有之外，其他的都有。不过值得注意的是，尽管 jetbrains 没有直接提供选中代码块的指令，但是提供了`extend/shrink selection`的指令，你可以通过多次按`alt + up`去依次选中单词、行、字符串、代码块等，所以也可以说是一个相当不错的功能。

遗憾的是，在 vscode 中暂时没有发现同等指令，只找到一个`Expand Line Selection: cmd + l`(`l`是`line`的意思)用于直接选中一行，个人觉得不够精细，而且也可以部分被`ctrl + c`替代，因为在未选中状态，`ctrl + c`默认选中一行并复制。

另外值得注意的是，jetbrains 中的`Move Caret to Code Block Start/End`支持单向括号定位跳转，这在 python 这种基于缩进的语言上将会有一些意想不到的效果，那就是如果往右定位跳转，将会直接跳转到最内部的代码块结尾（想象一下数据结构中的“右斜树”）；而如果往左定位跳转，将可以一层层往上。

#### 折叠与展开代码块

vscode 的折叠/展开主要以“fold”为主，关键字是`[`和`]`。

vscode 基于`cmd + k cmd + [K]`将全文档折叠和特定级别折叠统一了起来（0 代表 0 级别，也代表全文档），但引发的问题就是展开全文档没有对应的数字，结果选了个`j`(不明觉厉)。

此外，可能是考虑到了单级别的展开与折叠比较常用，所以绑定了单组合键`alt + cmd + [`/`alt + cmd + \`与其他操作需要的双组合键未能统一。从设计来看，并不是十分令我满意。个人觉得 vscode 不妨考虑冗余设计，集体允许`cmd + k ANY_SECOND_KEYS`的模式，并为单级别折叠与展开额外再提供一个单组合键。

jetbrains 的折叠展开主要以“expand”为主（正好和 vscode 相反），关键字是`+`和`-`。

其实我个人比较喜欢 vscode 的关键字设计，因为在大部分软件中`cmd + +`/`cmd + -`都是用于放大或者缩小字体的，而用`cmd + [`/`cmd + ]`去操纵结构体则同时显得更为合理（因为这几个关键字本身就是括号的意思）。

其次，jetbrains 使用`alt`表示循环，用`shift`表示全局，个人认为也很简单暴力。而单独用小键盘去表示指定级别的展开/折叠，虽然也可以理解，但还是给 mac 造成了一定困难，毕竟 Macbook Pro 也没有小键盘。我们需要重新 map。

#### 快捷键修改前后对比

macOS - vscode - keymap - changed:

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666595428-1d774a2af7dd3ea18ced0923cbb0bec75323a37d257aec1065dbea8c2253dc1d.png)

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666542947-8842e877c62701d1793078ef1057aebd88e05ebab75f170d0cda756bce4f4db8.png)

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666569417-ca616bc0ada9c550799841ec7fe1b0d247a47df739d6e52a8d76b3614fe072d1.png)

macOS - pycharm - keymap - changed:

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666436302-5080248703c57e4f10f4c80f638860d3605179fb09701b448606dd75cd616966.png)

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666160469-dbf2ab993fa301cfca8499e457bc1732a674eb0dd661d638e4a054a763c3d0e5.png)

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666244565-81fd291b3518de92b198de24fc72e48fe7514b6e39ba839c7a4336376486e82e.png)

### bugfix: why `cmd + alt + \` converted to be `cmd + c`

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-design-1644666049559-11595bbdf9defe2b771e206dbd5fe29a724222470addc13d32531010f3eed795.png)
