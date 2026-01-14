## CH01 - The Very Intro to Python

### Overview

本章节主要讲解 Python 的一些发展与洞见，以提供读者对 Python 多方位、立体化的认知，并指导搭建好综合的程序开发环境，为后续的学习、生产建立基础。

本章核心：

- Python 分 Python2 和 Python3，Python2 诞生于 1991 年，其开发者为 Gudio，并于 2020 年 1 月 1 日官方宣布停止维护，因此接下来所有的 Python 项目都是 Python3 版本；
- Python 在近 20 年内的地位与热度一直在上升，得益于大数据处理相关的优势，目前跻进前五，与 Java、C/C++同在一线阵营；
- Python 的应用方向广泛，目前主要用于网站开发、网络爬虫、数据可视化、机器学习和自动化运维；
- 要想顺利安装好 Python 的各大 IDE（集成开发环境），需要对操作系统的环境变量有一定的了解；

### What's python and what's python for?

#### 为什么要学 Python？

我们先把这个问题放在首位，这个问题其实很重要，因为这并不不偶然。

有人会说：“因为大家都在学 Python，所以我不能落下”，这或许可以称之为一个理由。

但你真地明白大家为啥要学 Python 吗？或者，你去问问那些学的比较深入的人，他真地喜欢 Python 吗？我觉得，在你学习 Python 之前，如果可以，问一下那些人：“嘿，老哥，你为啥学 Python？学习 Python 给你生活带来了什么改变吗？”作为一门编程语言，按照直觉，这应该不会有什么令人出乎意料的答案。比如你可能听到：“啊，学习 Python 啊，我感觉它很容易学“，或者”谁知道呢，也许可以用 Python 可以减轻我的工作负担吧”。

这些答案都是可以接受的，但如果你问我，我会回答：“我可以用 Python 完成非常多原本不可能完成的任务；在学习过程中，我更懂计算机了；我从未感觉学习一门编程语言能像 Python 一样如此富有魅力，以至于更像是一种享受，以至于我现在全身心地投入到了 Python 的推广教学当中去了，以至于我必须把 Python 的首字母大写以表示这是 Python 而非其他种 python”。

**_"Easy, Powerful, Prevailing and then Enjoyable, Beautiful, Philosophical"_**，这就是我为什么要学 Python 的答案：

1. 因为简单，所以我很快地掌握了它的使用
2. 因为有用，所以我很快地做出了一些东西
3. 因为流行，所以我很快地找到了一些工作
4. 并且它是美丽而富有哲学意味的，由此开发 Python 的体验是令人享受的
5. 最后，它在一定程度上改变了我的生活，改变了我的职业规划，并带给了我一种新的审视世界的角度

感性到此结束，我们来看看这三个要素究竟是怎么把我引向学习 Python 的热潮中去的：

- C、C++、JAVA 等语言非常 Powerful 并且 Prevailing，但是它们并不 easy，比如 C 中的指针让人望而生畏，知乎的轮子哥曾经专门教一个人 C 语言，安排一周讲解所有基本概念，但却安排了两周给他讲授指针，可想而知
- Matlab、R、JavaScript 等语言并不那么难，但都只是特定领域的专用语言，如果你要走学术那你可要好好学学 matlab 或 R 等，如果你要做前端可要好好学习 JavaScript 等，总之它们都不适用于所有人，当然类似的还有一些大数据时代专用的语言比如 Go、Scala 等也可归于这一类
- 再举个不是很流行的例子，比如 lua 之类的语言
- 但有一种算不上编程语言的语言，我必须突出一下，那就是 Markdown，它是一种标记语言，广泛地用于互联网的博客写作与 Github 项目的首页展示，比如本系列教程就是完全基于 Markdown 的。By the way，我的英文名就叫 Mark
- 因此，当你不知道要学哪门编程语言以应对未来就业市场的冲击的时候，选 Python 准没错；如果你知道自己要学哪门编程语言，又正好读到我们这份教程，那我想说：“加油，请坚定地走下去”。此时或许可以再来波鸡汤：“未来你一定会感谢现在如此明智而又努力的你的！”

#### Python 到底是什么？

在写这份系列教程之前，我有承诺给我的读者，要在书中体现程序员的思维，Now，这是第一个：**证伪往往比证明更容易**。即我无法准确定义 Python 是什么，但可以准确地回答一个伪命题，比如：“Python 是最好的编程语言？”这显然是不成立的，毕竟 Python 的平均运行效率在 Java 的十分之一左右，在 C 的百分之一左右。

> 以下内容是关于软件测试的，暂时可以不用理解

我们可以再深入一些，什么是证伪比证明更容易，我们可以借用软件工程中单元测试的概念来试图说明这一点。比如你写了一个验证用户输入的手机号码是否合法的程序，作为用户如果他不信任你的程序的话，他会怎么测试你的程序呢？他可以先输入一个空值，看看会不会报错；如果会，再输入一个字符串看看会不会；如果依旧会报错，再输入一个负数看看会不会报错；如果还是会，再输入一个小数看看会不会报错；如果仍然会报错，再输入一个十位数号码看看会不会报错……

严格意义上，到上一步，测试已经结束了，如果所有的以上都报错，然后用户输入了一个 11 位正整数提示通过，那么你的程序就已经合格了。所以你看前面的所有步骤都是在证伪，是一步步去伪存真，最后才能能够勉强证明你的程序是合格的。为啥这还只能算合格？因为你还没考虑首字为 0 的情况，以及没有考虑该电话号码是否符合其他更鲜为人知的中国电话号码规范，furthermore，我们还没讨论该程序对国外电话号码的检验与适用情况。所以你看，证明一个程序是正确的，或者说 robust（稳健的），是多么地不容易。这便是我要花这么长的篇幅拒绝一上来就回答 Python 是什么的原因。

此外，我们还有第二个程序员思维：**封装是一把双刃剑**。同样是这个测试手机号码输入合法的程序，一些对 Python 了解较为深入的同学会嘲笑到，直接用正则表达式匹配 11 个数字不就解决了初步的校验问题了吗？没错，是这样的。正则表达式就是对一些字符串处理逻辑、模式的封装，并对上层提供一个更加简单、容易理解、容易调用的接口，以使上层的开发人员能够用更少的代码完成更强大、更复杂的逻辑处理。但这是一把双刃剑，因为封装让所有的一切变得更加抽象，让你无法理解你的错误，为啥会这样呢？什么又是封装呢？为了更好地理解这一点，我们再选取一个通俗易懂的例子：金融危机。

> 以下内容是关于软件调试的，个人觉得这个例子还可以，建议理解

对于程序员来说，整个世界的金融体系就是一个庞大的系统工程，它是由无数的政客、商人、普通人等，以及一整套货币体系、商品流动等构成的。当我不是一个金融研究者的时候，整个金融体系对于我来说就是一个封装地很完整的工程，我并不了解其金融的运转细节，但当我要去取钱的时候，我知道我要做的就是我去这个金融体系里的所有银行中的我可以取钱的那家银行取钱。用程序的逻辑描述就是：

```py
金融体系.所有银行.返回我开户的那家银行().返回这家银行旗下离我最近的网点().前往取钱(取钱金额=?, 其他参数)
```

是吧，其实就是这个意思，这个世界的封装让世界变得有序，让做某件事情的逻辑变得很清晰，但一旦哪里出了问题，由于你不知道每一步的逻辑是怎样的，也不知道有没有隐藏的 bug，因此出了问题就会很棘手。比如就这个取钱的函数，你因为下雨没取到钱，这是一件很严重的事情，因为你会想不应该啊，这个金融体系应该能够支持我即使下雨天也能取到钱的，毕竟也没让我输入是否下雨这个参数啊，也就是说下雨不应该成为最终能不能取到钱的影响因素。但为啥最后没取到呢？

你最后仔细检查了一下程序逻辑，才发现，在这个`前往取钱(取钱金额=?, 其他参数)`的函数里虽然有考虑在下雨天的时候带伞以能够前往网点的函数调用，但这个调用没考虑你下雨天因为不小心滑倒摔伤被送进医院从而导致这个调用无法正常返回一个`已经抵达网点`的较低层输入，最后自然就没取取到钱，甚至会直接报错。你这么去想的话，就能明白为啥金融危机的争论这么久了，因为整套 ABS 体系过于复杂让人蒙圈，但比 ABS 更复杂的是整个世界的国际霸权体系，而比这个更复杂的是，根植在这个世界下的人性的复杂，这导致了推演、排查整个金融危机的原因，并优化这个金融体系的工作变得相当困难。甚至直到现在，我们都不能确定这个金融体系能像 1+1 保证等于 2 一样稳定的运转，这便是封装带来的不利之处。

而 Python 正是基于 C 语言之上封装起来的更高级的编程语言，它的 easy 正是来自于对很多 c 语言较为直观的逻辑的复杂的组合、包装与简化。

> 以下内容是关于软件编码的，暂时可以不用理解

但直到现在，我都无法给出 Python 是什么，虽然你可以在维基百科、百度百科、Python 官网、[Guido van Rossum](https://en.wikipedia.org/wiki/Guido_van_Rossum)（Python 创始人）口中得到无数种定义。相比于在这些囿于世俗、教科书般死板的解释，我更愿意简单地称 Pyhton 就是一门**_Easy, Powerful, Prevailing_**的语言，比如以下。

```py
>>> 1+1
2
```

好吧，不开玩笑，我们用直观的例子，解释什么是 Python。你打开你的计算机，在没有开机的时候它就只是一个硬件，是没有任何灵魂可言的。现在你开机了，随着屏幕的不断闪烁，你进入了你习以为常的欢迎界面，这就是构建在计算机底层芯片、内存、主板之上的操作系统，可能是 Windows，可能是 Mac，也可能是 Linux 等。接着，你终于进入了你的桌面，然后打开了你的某个开发 Python 程序的软件，可能是 PyCharm，可能是 Jupyter Notebook，可能是 IDLE，也可能是 Sublime，甚至可能就是一个记事本，然后输入了一些读起来很像英文诗的语句：

```py
# 本代码可直接运行，但本代码纯属娱乐，欢迎交流

from datetime import date

class Person:
	def love_or_not(self, the_guy, the_time):
		"""
		To love or not to love, that's a question.
		"""
		return True

if __name__ == "__main__":
    she = Person()
    me = Person()

    if she.love_or_not(the_guy=me, the_time=date.today()):
        print("I should be a better man!")
    else:
        print("Please give me a cigar!")

    print("After all, tomorrow is another day!")
```

这段代码如此简单明白，因为它正是 Pythonic（极具 Python 风格）的代码，并且确实可以，理论上来说，这就是 Python，这些就是 Python 想表达且能实现的东西。

作为对 Python 的尊敬，我们还是提供一份维基百科的解释如下：

> **Python**（英国发音：[/ˈpaɪθən/](https://zh.wikipedia.org/wiki/Wikipedia:國際音標英語發音) 美国发音：[/ˈpaɪθɑːn/](https://zh.wikipedia.org/wiki/Wikipedia:國際音標英語發音)）是一种广泛使用的[解释型](https://zh.wikipedia.org/wiki/直譯語言)、[高级编程](https://zh.wikipedia.org/wiki/高级编程语言)、[通用型编程语言](https://zh.wikipedia.org/wiki/通用编程语言)，由[吉多·范罗苏姆](https://zh.wikipedia.org/wiki/吉多·范罗苏姆)创造，第一版发布于 1991 年。可以视之为一种改良（加入一些其他编程语言的优点，如面向对象）的[LISP](https://zh.wikipedia.org/wiki/LISP)。[[来源请求\]](https://zh.wikipedia.org/wiki/Wikipedia:列明来源)Python的设计哲学强调代码的[可读性](https://zh.wikipedia.org/wiki/可读性)和简洁的语法（尤其是使用[空格缩进](https://zh.wikipedia.org/wiki/越位规则)划分代码块，而非使用大括号或者关键词）。相比于C++或Java，Python让开发者能够用更少的代码表达想法。不管是小型还是大型程序，该语言都试图让程序的结构清晰明了。
>
> 与[Scheme](https://zh.wikipedia.org/wiki/Scheme)、[Ruby](https://zh.wikipedia.org/wiki/Ruby)、[Perl](https://zh.wikipedia.org/wiki/Perl)、[Tcl](https://zh.wikipedia.org/wiki/Tcl)等动态类型编程语言一样，Python 拥有[动态类型系统](https://zh.wikipedia.org/wiki/類型系統)和[垃圾回收](<https://zh.wikipedia.org/wiki/垃圾回收_(計算機科學)>)功能，能够自动管理内存使用，并且支持多种编程范式，包括面向对象、命令式、函数式和过程式编程。其本身拥有一个巨大而广泛的标准库。
>
> Python [解释器](https://zh.wikipedia.org/wiki/解释器)本身几乎可以在所有的[操作系统](https://zh.wikipedia.org/wiki/操作系统)中运行。Python 的其中一个[解释器](https://zh.wikipedia.org/wiki/直譯器)[CPython](https://zh.wikipedia.org/wiki/CPython)是用[C 语言](https://zh.wikipedia.org/wiki/C语言)编写的、是一个由社群驱动的自由[软件](https://zh.wikipedia.org/wiki/軟體)，当前由[Python 软件基金会](https://zh.wikipedia.org/wiki/Python軟體基金會)管理。

#### 部分编程语言基本信息

|  | 创始人 | 时间 | 国 家 | 主要应用 |
| --- | --- | --- | --- | --- |
| Python | Gudio van Rossum | 1991 | 荷兰 | 大数据的挖掘和处理，开发 web，系统运维，云计算，金融理财分析，人工智能等 |
| C | Dennis MacAlistair Ritchie | 1978 | 美国 | 主要用于像操作系统一类偏底层的应用开发，包括像 Windows/Linux 这样的大型商业操作系统，以及嵌入式操作系统、嵌入式设备上的应用 |
| C++ | Bjarne Stroustrup | 1982 | 美国 | 应用软件，基础软件和高级语言的运行时环境，业务型应用软件的后台 |
| C# | Anders Hejlsberg | 1998 | 丹麦 | 多用于开发桌面应用程序、Web 应用程序、RIA 应用程序（Silverlight），智能手机应用程序 |
| Java | James Gosling | 1990 | 加拿大 | 用于开发大中型商业应用，桌面应用，消费和嵌入式领域 |
| JavaScript | Brendan Eich | 1995 | 美国 | 唯一一种在所有主流平台都被原生支持的编程语言，因此在所有主流平台都可以用于进行插件开发。常见的有浏览器插件和扩展程序 |
| Go | Rob Pike,Ken Thompson,Robert Griesemer | 2009 | 美国 | 可解决面向对象程序设计的麻烦，帮助程序设计师处理琐碎但重要的内存管理问题 |

#### 各大编程语言排名信息

排行榜这种东西，总会具有争议性，但总体来说还是具有相当地参考价值。就好比关于国内高校的学术排名历来就有“Top1 有两个，Top3 有五个，Top5 有十个“的梗一样，在 IT 界也是很容易一言不合就开架的。Anyway，我们就根据 TIOBE 的排名来看一下各大编程语言的排行情况，对此有意见或感兴趣的可以访问 TIOBE 官网：[index | TIOBE - The Software Quality Company](https://www.tiobe.com/tiobe-index//)以及其它相关网站。

> TIOBE 编程社区索引是编程语言受欢迎程度的指标。索引每月更新一次。评级基于全球熟练的工程师，课程和第三方供应商的数量。诸如 Google，Bing，Yahoo！，Wikipedia，Amazon，YouTube 和 Baidu 等流行的搜索引擎用于计算评分。重要的是要注意，TIOBE 索引与*最佳*编程语言或*大多数代码行*所用的语言无关。

根据 TIOBE 2020 年 1 月份的摘要显示，每个人都认为 Python 将连续第二年成为 TIOBE 的年度编程语言。但这一次却是 C 语言凭借 2.4％的年增长率获得了该奖项。为什么 C 语言仍然很热门？这种趋势背后的主要驱动力是物联网（IoT）和当今发布的大量小型智能设备。当将 C 应用于对性能至关重要的小型设备时，C 会很出色；并且 C 相对来说还算容易学习，每个处理器都有一个 C 编译器。以下是目前 TIOBE 编程社区索引指数对比图。

![image-20200118155039173](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118155039173.png)

此外，比起趋势图，用表格展示或许更直观一些，且看：

| Programming Language | 2020 | 2015 | 2010 | 2005 | 2000 | 1995 | 1990 | 1985 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Java | **1** | 2 | **1** | 2 | 3 | - | - | - |
| C | 2 | **1** | 2 | **1** | **1** | 2 | **1** | **1** |
| Python | **3** | 7 | 6 | 6 | **23** | 21 | - | - |
| C++ | 4 | 4 | 3 | 3 | 2 | **1** | 2 | 12 |
| C# | 5 | 5 | 5 | 8 | 8 | - | - | - |
| Visual Basic .NET | 6 | 10 | - | - | - | - | - | - |
| JavaScript | 7 | 8 | 8 | 9 | 6 | - | - | - |
| PHP | 8 | 6 | 4 | 5 | 29 | - | - | - |
| SQL | 9 | - | - | 97 | - | - | - | - |
| Objective-C | 10 | 3 | 22 | 37 | - | - | - | - |
| Lisp | 31 | 18 | 16 | 12 | 14 | 5 | 3 | 2 |
| Ada | 35 | 29 | 25 | 15 | 15 | 6 | 4 | 3 |
| Pascal | 219 | 16 | 13 | 75 | 12 | 3 | 20 | 5 |

整体来看，1895 年起 C 是第一名的位置，十年后 C++可能由于 STL 的原因开始登顶，并开始与 C 语言并驾其驱。直到 2010 年 JAVA 开始后来居上。而 Python 则默默发力，一举从 2000 年排名 20 几直到现在稳居第三。我们可以简单理一下，编程语言的发展经历了机器语言、汇编语言和高级语言的过程，其中 C 语言是高级语言的集大成者与基石，在那个年代单机控制系统是编程的刚需，所以火热是正常的。后来开始进入了桌面时代，因此 C++开始大显身手，并编写出了很多复杂的程序。接着进入了移动互联时代，JAVA 因为其一次编译随处运行的特性迅速占领了整个嵌入式市场。而我们现在是什么时代呢？数据时代！对于海量数据的处理需求与人工智能的火热，催生了基于数据与应用的交互需求，因此 Python 这种脚本语言得以大显身手，并在其发展中不断演化，吸收其他编程语言的优秀思想与设计，实现了阶级跃升。

大胆预测一种较大概率存在的模型：底层用 C，设备用 JAVA，桌面用 C++，之间的粘合与原型开发用 Python，网页用 JavaScript，苹果推自己的 Swift，微软推自己的 C#，等等。所以从适用性来看，C/C++、JAVA、Python 的组合无意是强大的，当然了，背后还有一个语言与它们交互，那就是 SQL/NoSQL。这就是我觉得较为稳定、主流的框架了。其他各个领域会有各自的主流语言，比如统计语言 R/SAS，人工智能领域 Scala/Go 等。

### Know more about your operating system

#### 什么是系统调用：cmd | bash?

在任何一门操作系统课中，首先接触的、也是贯穿全书的、也是最重要的概念之一就是系统调用（System Call）。为了解释它，让我们首先回到上个世纪五六十年代。

大约在 20 世纪 50 年代末期，与机器无关的编程语言被首次提出。随后，人们开发了几种实验性质的编译器。第一个编译器是由美国女性计算机科学家[葛丽丝·霍普](https://link.zhihu.com/?target=https%3A//zh.wikipedia.org/wiki/%E8%91%9B%E9%BA%97%E7%B5%B2%C2%B7%E9%9C%8D%E6%99%AE)（Grace Murray Hopper）于 1952 年为[A-0 系统](https://link.zhihu.com/?target=https%3A//zh.wikipedia.org/wiki/A-0_%E7%B3%BB%E7%B5%B1)编写的。而到了 1960 年代早期，商用电脑制造商制造了[批处理](https://link.zhihu.com/?target=https%3A//zh.wikipedia.org/wiki/%E6%89%B9%E5%A4%84%E7%90%86%E4%BB%BB%E5%8A%A1)系统，此系统可将工作的建置、调度以及运行[序列化](https://link.zhihu.com/?target=https%3A//zh.wikipedia.org/wiki/%E5%BA%8F%E5%88%97%E5%8C%96)。

如今，操作系统越来越复杂，图形界面越来越友好，但始终不变的是都会保留一个能直接控制操作系统的命令行入口，在 windows 内叫 Commands Shell（即 cmd），在 linux/unix（包括 mac）内叫 Bash Shelle（即 bash）。程序员们（尤其是黑客们）便是通过这些入口高效、快速的执行对计算机的操控与管理的，因为这里的命令几乎与操作系统内部的系统调用直接挂钩。

而所谓系统调用，便是能够执行一个系统级别的操纵命令，它们一般是一些用于实现各种系统功能的子程序，比如打开一个文件，比如杀死一个进程等。在 Linux 2.4.4 版内核中，共有 221 条系统调用命令。在 windows 中提供了上千个 win32 的 api 用以间接调用（或不涉及调用）windows 内核中的系统调用。

严格意义上，系统调用是操作系统内核中的一些控制语句，而 cmd 和 bash 往往是指在操作系统中提供给程序员与系统调用打交道的一些命令语句。以下以 windows 的 cmd 为例，简单介绍一些重要的命令。

#### Windows 中的 cmd 启动

按住键盘`Windows + R`，即在左下角打开了一个`运行窗口`，输入 cppmd```后便可打开一个黑窗，它有以下特征：

1. 窗口标题即 cppmd.exe```这个程序的路径
2. 窗口中显示的内容中，前几行描述了操作系统的版本信息和版权信息等
3. 最后一行的内容，默认是你的用户文件夹位置

![image-20200118201415719](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118201415719.png)

这里值得注意的是：

1. 默认的用户文件夹位置其实已经定义在了系统变量中，它的变量名叫`USERPROFILE`
2. 这个默认的 profile 文件夹位置，我们一般不对它做修改，因为与你的用户文件夹初始化有关
3. 但 CMD 打开后，默认显示的位置我们是可以考虑对它做些修改的，为什么呢？因为目前它打开的是我的 profile 文件夹，如果我在这个黑窗里直接创建一个 python 程序，那么这个 python 程序就会和这个文件夹下的内容混在一起了，比如，我们复制该路径，在`运行窗口`中输入后回车便得到一个资源管理器窗口：

![image-20200118202203742](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118202203742.png)

这个文件夹窗口也有几点值得注意：

1. 可以看到，在我们的用户文件夹下，已经有了很多内容，所以并不适合在黑窗里直接运行一些操作，尤其是和 IO（即输入输出文件）相关的操作
2. 地址栏自动识别成了我的用户登陆名，实际上在这里也可以输入那个路径，得到的结果是一样的。即在`Windows + R`生成的`运行窗口`里输入文件夹路径和在`资源管理器`的地址栏里输入文件夹路径是一样的，但前者速度更快
3. 窗口内的文件夹分三种，第一种是以`.`开头的文件夹名（蓝色框），这种文件夹里存储的一般都是一些程序自动生成的配置文件，不要轻易地去修改它，除非你知道自己在做什么；第二种就是正常地文件夹（红色框）；第三种是一些隐藏文件夹（绿色框），一般是存储了一些程序地运行数据，比如备份之类的，严格意义上被自动隐藏的文件夹，是没有任何理由不能动的
4. 我们之后会涉及到该窗口内一些文件夹内的一些文件的自定义配置

#### Windows 中的环境变量

我们有多种方法查看与修改系统中的环境变量，而这个是非常重要的，因为它涉及到很多程序（尤其是指编程程序）的正常运行：

1. 方法一：在 cmd 中输入`set`即可看到环境变量的情况
2. 方法二：在资源管理器 - 右击计算机 - 选择属性 - 选择高级系统设置 - 选择环境变量，便能看到上方用户环境变量和下方系统环境变量的情况

![image-20200118205432179](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118205432179.png)

在上图中，可以看到 cmd 显示的一些数据和右方的界面展示的数据大致是一一对应的，不过 cmd 中给出的环境变量比比右边界面给出的多，比如 cmd 的第一个变量叫`ALLUSERPROFILE`在右边就没有出现（不过没出现的一般我们都不用考虑）；然后左边和右边第一个共有的变量叫 cppLASSPATH`，这个我们也不用关心；第三个我标红的变量是`HOMEPATH`，这其实是我们后续要安装的Anaconda软件默认的一个主页路径；而`JAVA_HOME```就是要运行 JAVA 的主页路径（本教程不考虑）。

这张图里最重要的要关心的两个变量是`NC`和`Path`。

首先`NC`变量是我自己设置的，为什么自己设置一个变量呢，因为我想让我所有的程序生成的文件都在一个文件夹内，比如在之后我们的章节中，我们既会通过 JupyterNotebook 创建一些程序文件，也会通过 PyCharm 创建一些程序文件，而把这些文件分别归到有结构的文件夹内是有益的，比如以下的一种目录，我就比较欣赏：

```json
C:
	- NC_WORKSPACE
		- Jupyter Notebook Projects
			- nb_1
			- nb_2
			- ...
		- PyCharm Projects
			- pc_1
			- pc_2
			- ...
	- Users
		- WZ988KR
			- ...
	- ...
```

因此，你也可以设置以下自己的一个工作区文件夹，以后无论用什么编程语言、用什么编程环境，写的程序都全部归类在这样的一个工作区文件夹下，将是一件非常易于后续维护的事情。

但你也许会问，`NC`和 cpp:\NC_WORKSPACE`有什么关系呢？其实就是等价关系，毕竟变量名越短越好，那这个变量名我们怎么用呢？还是回到我们的cmd黑窗，输入`echo %NC%`，就可以发现，它竟然显示了`NC`这个变量所等价的路径。所以`%xxx%```便是 windows 翻译环境变量的一种语法标记。

聪明的你应该能意识到了，既然`NC`可以转换成其实际含义，那么`PATH`也应该可以，于是就有下图。

![image-20200118211816569](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118211816569.png)

可以看到，确实如此，当我们使用`echo %PATH%`之后，它确实显示出了密密麻麻的一堆路径，每条路径都是分号结尾的，注意这个约定，在大多数编程语言中，分号都代表着一句话的终结，比如 Python、C 语言等。

最后你可能会问，那这些路径有什么用呢？答案是大有用处。

首先，我随机选择一条路径，比如就最后一条吧，图中最后一条是 cpp:\Users\WZ988KR\AppData\Local\GitHubDesktop\bin`，我先选中后cppontrol + C`复制到剪切板（注意不要带结尾的分号），然后在这个窗口下方输入 cppd `然后空格再粘贴，其中cppd`命令是切换路径的含义，这样窗口的路径就跳转到了该文件夹了。

接着我再输入`echo echo hello > hello.bat`，这样就在当前文件夹下创建了一个`hello.bat`的批处理文件，其中的内容就是`echo hello`这一行话，这里我们暂时可以不用理解`echo`的机制，只要知道它可以显示文字，而`>`可以将文字存入文件就可以了。

然后我们就可以测试以下语句，即直接输入`hello.bat`，甚至在任意文件夹路径下输入`hello.bat`都能得到同样的结果（红色是手动输入的，蓝色是自动输出的结果，右边的 cmd 是新打开的一个）。

![image-20200118215049495](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118215049495.png)

原因是因为`hello.bat`是在 cpp:\Users\WZ988KR\AppData\Local\GitHubDesktop\bin`这个文件夹下的（不信可以打开资源管理器看看），然后这个`bin`的路径又在系统的`PATH`变量中，当windows要执行一个没有绝对路径的前缀的程序时，它会依次遍历所有系统环境路径下的文件夹下的可执行文件，主要包括`.exe`文件和`.bat```文件。

如果你在 cmd 中输入`hello.bat`或者输入`hello`（可以省略后缀）程序没有相应的输出，甚至报错（比如以下用`del hello.bat`先删除`hello.bat`文件再执行`hello`命令，发现错误），则有几种可能：

1. 你没有正确输入单词，比如输成了`heLLo`或者`hello.baT`等
2. 你的`hello.bat`文件不在系统环境路径下，比如你只是在桌面新建了一个`hello.bat`文件，但是你的桌面路径并不在系统路径里（当然你可以把你的桌面加入路径，那样就可以正常地、在任何文件夹下运行`hello`了）
3. 你的`hello.bat`文件在系统环境路径内，但是有多个，你可能想执行的是第二个`hello`程序，但是却因为路径的先后关系执行了第一个，于是引起了意外的、令人困惑的结果，还很不容易察觉

![image-20200118215606799](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118215606799.png)

前两种应该讲的比较清楚了，但针对第三种，有必要展开一下，因为第三种情况是很有可能在实际种发生的。比如，你先在官网下载了一个纯净版 Python，并加入了环境路径。之后又下载了 Ananconda，并且也把它加入了环境路径，这样问题就来了，当你在 cmd 中直接输入`py`，它会运行哪个呢？比如如下的环境路径情况。

![image-20200118220928820](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118220928820.png)

![image-20200118221016631](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118221016631.png)

![image-20200118221102719](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118221102719.png)

可以看到，确实在两个不同的路径下分别有一个`py.exe`程序，根据环境路径的顺序，由于 Ananconda 在前，所以会运行 Anaconda 环境下的`python.exe`。我们可以通过`where python`这个命令去验证一下。

![image-20200118221449407](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/image-20200118221449407.png)

如果你的电脑上安装了某个程序的多个版本，那最好的办法是给它们重新命名，比如把`py37`文件夹下的`py.exe`重命名为`python37.exe`，这样你输入`pyhton37`就可以运行该程序，而你输入`python`则会运行 Anaconda 环境下的`python.exe`程序。这也是在一个电脑里同时安装`python2`和`python3`的解决方案，不过好消息（同时更是坏消息）是，今年（2020 年）1 月 1 日`python2`已经停止维护了。

#### Mac OS 中的环境变量

南川 P.F.A 教学第一期（上-Mac 群）群内交流。

以上就是本期关于 Python 以及相关语言、CMD 以及环境变量的相关介绍，下期如何安装 Python 的 IDE，我们再见！

### Reference and Recommendation

#### 图灵 Python 图书一览表

![img](http://q45kgq2g9.bkt.clouddn.com/CH01%20-%20The%20Very%20Intro%20to%20Python.assets/20180409200251453.png)

#### 参考网址

- [Python - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/Python)
- [Python (programming language) - Wikipedia](<https://en.wikipedia.org/wiki/Python_(programming_language)>)
- [index | TIOBE - The Software Quality Company](https://www.tiobe.com/tiobe-index//)
- [Python 书单，附阅读路线图！\_zhusongziye 的博客-CSDN 博客](https://blog.csdn.net/zhusongziye/article/details/79871738)
- [17 幅思维导图 | Python 编程之核心知识体系（第三版更新） - 知乎](https://zhuanlan.zhihu.com/p/35516692)
- [玩转 Terminal 终端：入门指南及进阶技巧 - 少数派](https://sspai.com/post/45534)
- [请问：是先有操作系统还是先有编译系统？为什么？ - 知乎](https://www.zhihu.com/question/20474187)
- [观点|对《大家都在点赞 Windows Terminal，我决定给你泼一盆冷水》一文的商榷](https://linux.cn/article-10831-1.html)
- [浅谈 CMD 和 win powershell 的区别\_qq_29166327 的博客-CSDN 博客](https://blog.csdn.net/qq_29166327/article/details/79461748)
- [Linux 中共有多少个系统调用？ 为什么要用系统调用？ - 道客巴巴](http://www.doc88.com/p-748646126865.html)
- [从系统调用看 UNIX 与 windows 的差别](https://techlog.cn/article/list/10182493)
- [echo | Microsoft Docs](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/echo)
-

#### 书籍导航

- 最大的免费英文电子书下载网，可下载到许多 Python 书籍： [b-ok.cc/s/python](https://b-ok.cc/s/python)
- Python 官方的书籍清单网： [Find the best Python books - pythonbooks.org](https://pythonbooks.org/)
-

#### 教程导航

- [Python 教程 - 廖雪峰的官方网站](https://www.liaoxuefeng.com/wiki/1016959663602400)
- [Python Tutorial - Learn Python and be above par - DataFlair](https://data-flair.training/blogs/python-tutorial/)
-

#### 技术手册

- [Windows 命令 | Microsoft Docs](https://docs.microsoft.com/zh-cn/windows-server/administration/windows-commands/windows-commands)
- [CMD 命令\_百度百科](https://baike.baidu.com/item/CMD%E5%91%BD%E4%BB%A4/9684689?fr=aladdin)
- [Mac 上“终端”中的键盘快捷键 - Apple 支持](https://support.apple.com/zh-cn/guide/terminal/trmlshtcts/mac)
-
