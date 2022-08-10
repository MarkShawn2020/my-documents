# THe World From A Coder's Eye

1. [different and usually better choice from a coder](#different-and-usually-better-choice-from-a-coder)
2. [持续整理之道](#持续整理之道)
3. [一个比较极客的 TODO](#一个比较极客的todo)
4. [discuss: "Always On Top" window design between macOS and windows](#discuss-always-on-top-window-design-between-macos-and-windows)
5. [如何调试（debug）](#如何调试debug)

## different and usually better choice from a coder

- torrent relative
  - webtorrent

reference:

- [Getting started - Chrome Developers](https://developer.chrome.com/docs/extensions/mv3/getstarted/)

- [GoogleChromeLabs/link-to-text-fragment: Browser extension that allows for linking to arbitrary text fragments.](https://github.com/GoogleChromeLabs/link-to-text-fragment)

- [Link to Text Fragment - Chrome 网上应用店](https://chrome.google.com/webstore/detail/link-to-text-fragment/pbcodcjpfjdpcineamnnmbkkmkdpajjg)

- [链接滚动加高亮 - Chrome 这波骚操作我们等了二十多年 - 极诣数字营销](https://maxket.com/link-to-text-and-highlight-chrome/)

## 持续整理之道

update@2022-02-17: 在我编辑 markdown 文章的时候，经常需要不断地操纵文档结点，提升或移动等。

我一开始觉得，这是很笨拙的工作，是要从顶层设计避免的。也就是尽可能地先想好大框架，然后去填东西。

后来，随着我的文档越来越多，达到了 150+文档，100w+文字，这个持续积累的过程中我发现，根本不存在所谓的文档大纲树之类的顶层设计，提前设计好自己想要写什么，分哪些类的工作是徒劳且有些幼稚的。

如果说硬要有什么顶层设计，我觉得是如何保证每一篇新的文章、每一个新的结点都能在 O(1)的性能上完成。

在此基础之上，我意识到了，每次开辟新的章节或者文章时，首先先立好符合该章节的主题，尽量具体一些。比如在我整理 linux 相关的笔记的时候，我一开始是碰到什么知识点都单独以 2 级标题去记录的。

后来知识点越来越多，并且逐渐呈现了一些可以聚类的规律，比如这几个问题都是关于文件系统的，那几个问题都是关于网络的。

这时候，我们要做的就是，归类，然后整合成三级结点，例如我现在的 linux 笔记大纲如下：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark-the-world-from-the-eye-of-a-coder-1645110297679-1d2e9fa8a86e2b2a78fb3d37dbe7d08743f2dde326c034b5d2a54276f8cd7859.png)

如果你仔细看，会发现，现在的章节就像一本书一样，有专门探讨环境配置的，有专门的探讨文件系统的，每个二级分类下又有不同的子问题与可能多个解决方案。

最想说的是，这不是一蹴而就的，不是我一开始就想这么设计的，大多数情况下，对某个领域的知识点不会像这篇 linux 一样这么密集，如果直接以按照书本章节那种 3-4 个层级去组织会让人觉得很害怕。

但只要你慢慢积累，一开始先平级地整理几个问题，渐渐地开始归类，最终可能还因为某个章节过于庞大，再独立出去（同时加上一个超链接）。

这样去组织文档，你会发现整个文档偶尔失控，但整体有序。

我想了很久，我觉得，这是我想要的与认可的“持续整理之道”。

再举个具体的例子，比如我们要整理一个新的知识点，是关于实习期间如何租房才能效益最大化的。

我们可能就要如此归类：`求职 - 实习 - 租房`，或者`效益 - 租房 - 实习` 等等。

不管用哪种，这肯定是一个具体的、多级子领域问题，我们需要将其分类到合适的位置去。

从数据结构角度来说，我是不希望让我的文档结构过深，成为斜树或者偏树的。

比较合适的办法，是学习 B 树，我们抽象地使用 `flatten` 的技术，将这个话题以一个单独的而非多层级的问题记录。

之后会越来越多的有其他相关话题加进来，也许你最后可能发现，这几个话题更适合打一个 `生活智慧` 的总标签，而非 `求职专栏`。

对，从程序的角度来说，就是用 B 树，这应该是程序智慧帮助我们管理学习的一个有效的案例。

尽管可能从未有人和你说过这一点。

## 一个比较极客的 TODO

![picture 50](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark-the-world-from-a-coder%27s-eye-1643126473099-33c2f1a8b61dfb10bfdd44dcceb559e245ed459236f37708b76ed430efff7325.png)

1. 通过 python 加命令行输出控制台和 markdown 两种格式
2. 基于 markdown 的渲染生成 html，再反向通过 html 基于鼠标操作原 markdown

很妙！程序的世界可太有意思了！

## discuss: "Always On Top" window design between macOS and windows

ref:

- [Why does OS X not have always-on-top? - Quora](https://www.quora.com/Why-does-OS-X-not-have-always-on-top)

## 如何调试（debug）

使用`debug`或`verbose`的参数，一般要加`--`，也有的开发者（比如 linux 平台的`find`指令）加`-`：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_net-all-you-should-know-1644548138416-17feb7d79946bf038579b0d1cc9b1887f34a00341db1a103ae53d21adb51aa05.png)

使用`DEBUG=true`的环境变量：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_net-all-you-should-know-1644547980040-7a7d3ee4067270142d7661e89985057c48d5ffe350fe995dd25691543d771ae2.png)
