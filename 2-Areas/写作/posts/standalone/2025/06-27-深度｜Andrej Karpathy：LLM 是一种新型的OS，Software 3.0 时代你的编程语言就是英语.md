# 深度｜Andrej Karpathy：LLM 是一种新型的OS，Software 3.0 时代你的编程语言就是英语

Andrej Karpathy Z Potentials

 _2025年06月27日 11:32_ _北京_

![](http://mmbiz.qpic.cn/sz_mmbiz_png/Z300vPwLQkkv763EiadS1eTfFnMp5Hm5eOAOX8AR81TFQM0azAFDNI8FLC15ITUMugG5sPQFR5icA7L1aGKWias3w/300?wx_fmt=png&wxfrom=19)

**Z Potentials**

我们与Z Potentials同频共振

437篇原创内容

公众号

![图片](https://mmbiz.qpic.cn/mmbiz_png/ib38wYqSEotAWYWPj5Jt0TtKMzQIQYslNiaXDZH9Fmn9mWGHsJlg3az0I5kvcszl7o5o7RXx92IZVoN7Ls3lyNsA/640?wx_fmt=png&from=appmsg&wxfrom=13&tp=wxpic)

图片来源：Andrej Karpathy

**Z Highlights**

- 软件正经历70年未有之大变局，我们正从 Software 1.0 (代码) 和 2.0 (权重) 迈向 Software 3.0 (提示词)。**英语，成为了最热门的新编程语言。**
    

- LLM 不仅仅是API，更像是一种**全新的操作系统 (LLM OS)**。它拥有自己的“CPU”、“内存”，并像1960年代的大型机一样，通过云端以“分时共享”模式提供服务。
    

- 软件的消费者不再只有人类（通过GUI）和计算机（通过API），而新增了**第三类消费者：智能体。未来的软件和基础设施需要原生为智能体设计，使其更易于理解和操作。**
    

**从代码到提示词：Software 3.0 范式革命与英语的崛起**

大家好，我是 Andrej Karpathy。很高兴今天能在这里和大家聊聊 AI 时代的软件。我听说在座的很多都是即将进入行业的学生，我认为这绝对是一个极其独特且有趣的入行时机。根本原因在于，**软件正在再次发生改变。**在过去70年里，软件的底层逻辑几乎没有变过，但在近几年，它却以前所未有的速度连续迭代了两次。这意味着有海量的软件等待着我们去创造和重写。

几年前，我提出了 Software 2.0 的概念。Software 1.0 是我们熟悉的经典代码，由人类用特定编程语言为计算机编写的指令。Software 2.0 则是神经网络的权重。你不再是直接编写代码，而是通过精心准备数据集，让优化器自动寻找最优的参数（权重），以此来“编程”。当时，我观察到在特斯拉，我们 Autopilot 的软件栈中，越来越多的C++代码 (Software 1.0) 被神经网络 (Software 2.0) 所取代。而今天，我们迎来了更深刻的变革：**Software 3.0**。随着大语言模型的出现，神经网络本身变得“可编程”了。**Software 3.0 的程序就是你的提示词 (Prompts)，而你的编程语言，就是英语。**

这三种范式各有优劣，作为未来的开发者，我们必须全部精通，并学会在它们之间灵活切换，为不同的功能选择最合适的编程方式。

**LLM 更是操作系统：一个正在重塑的计算生态**

我们该如何理解 LLM？吴恩达曾说“AI是新的电力”，这个比喻很传神，因为它确实展现了LLM如同公共设施的一面：由大型公司投入巨额资本构建“电网”训练大模型，然后通过API按流量计费输送“智能”。但我觉得，一个更贴切的比喻是：**LLM 是一种新型的操作系统 (LLM OS)**。

在这个“LLM 操作系统”的架构中，**LLM 本身扮演着中央处理器（CPU）的角色，负责核心的逻辑处理；其不断扩展的上下文窗口则像是计算机的内存（RAM），承载着临时的工作信息**；而它能够调用的计算器、代码解释器、浏览器等外部工具，就好比是操作系统的外部设备（Peripherals）。

更有趣的是，我们现在正处于 LLM OS 的“1960年代”。由于算力昂贵，LLM 被集中部署在云端，我们都像是通过“瘦客户端”（终端）与大型机进行交互的“分时共享”用户。个人电脑（PC）的革命尚未到来，但我们已经看到了早期迹象（比如用 Mac Mini 在本地运行模型）。**而我每次和 ChatGPT 对话时，都感觉自己像是在用命令行终端 (Terminal) 与这个新系统互动。我们还未给它发明出像 Windows 或 macOS 那样通用的图形用户界面 (GUI)。**

**最大机遇：构建“部分自治”的AI产品**

要驾驭 LLM，我们必须理解它的“心智模型”。我喜欢把 LLM 看作是“人的灵魂”——一种对人类的随机模拟。正因如此，它表现出了一种类似人类的、涌现式的“心理”特征。

**一方面，LLM 拥有百科全书式的知识和近乎完美的记忆力**，如同电影《雨人》中的“Savant”（学者综合症患者），博学强记。但另一方面，它也存在诸多问题：它会产生幻觉，一本正经地编造事实；它的智能水平参差不齐，在某些领域超越专家，却会在简单问题上犯低级错误；它患有严重的“顺行性遗忘症”，每次交互都像一次重启，无法像人类一样通过经验积累和“睡眠”来巩固知识，形成真正的专长；此外，它还相当天真，容易受到提示词注入等安全手段的欺骗。**因此，与 LLM 协作，我们需要扬长避短。**

![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)

我认为，目前最大的机会在于开发“**部分自治**”的应用。不要总想着一步到位实现全自动的AI智能体，那就像直接造“钢铁侠机器人”。**我们现阶段更应该做的是“钢铁侠战衣”——一个强大的人类增强工具。**无论是 AI 编程助手 Cursor，还是 AI 搜索引擎 Perplexity，这些成功的早期 AI 应用都展现了相似的成功模式。它们能够自动处理繁琐的上下文信息，智能地编排后台多个不同模型的调用，并通过定制化的图形界面（GUI）来呈现结果。**这套机制的核心目的，是让用户能够极速地完成对 AI 生成内容的验证，从而构建一个高效的“AI生成-人类验证”迭代闭环。**

一个成功的AI应用还应具备“**自治滑块**”（Autonomy Slider）的概念。**一个好的GUI能极大地加快验证速度，而一个设计合理的“自治滑块”则能确保AI“不脱缰”，避免它生成过多、过复杂的我们无法审查的内容。**

**人人都是程序员：从Vibe Coding到为智能体设计的未来**

Software 3.0 不仅是一种新范式，更是一种高度可及的范式。因为它使用自然语言，编程的门槛被前所未有地降低了。**我之前创造了一个词叫“Vibe Coding”，指的是一种你完全凭感觉、凭“Vibes”去编程的新方式。你不再纠结于代码细节，而是用大白话向LLM描述你想要的东西，它就能帮你实现。**这让那些没有经过专业训练的人也能创造软件，这在以前是不可想象的。

这种趋势的终极体现是：**我们不仅要为人类写软件，更要为智能体写软件。**过去，我们主要为两类用户设计信息和界面：一类是人类，通过图形界面（GUI）与之交互；另一类是计算机，通过应用程序接口（API）进行通信。**现在，我们迎来了第三种消费者：智能体。但目前，我们的网站、文档、应用大多是为人类的视觉和点击习惯设计的，智能体难以理解。比如，文档里一个“点击这里”的链接，对智能体来说毫无意义。**

因此，我们需要创造新的标准和工具，**未来的文档应该优先提供简洁的 Markdown 版本，网站的操作应提供等效的命令行（如 cURL）指令，从而让信息对智能体更加“可读”和“可执行”。**在未来的十年里，我们将见证那枚“自治滑块”从增强人类的“战衣”模式，逐步滑向赋能智能体的“自主”模式。而构建这一切的重任，正落在我们这一代开发者和创业者的肩上。

谢谢大家！

原视频：Andrej Karpathy on Software 3.0: Software in the Age of AI

https://youtu.be/LCEmiRjPEtQ?si=If9fKJlvCKcBfynx

编译：Wex Wang

_请注意，本文编译自文末载明的原始链接，不代表Z Potentials立场。如果您对本文有任何想法或见解，欢迎在评论区留言互动探讨。_

_Z Potentials将继续提供更多关于人工智能、机器人、全球化等领域的优质内容。我们诚邀对未来充满憧憬的您加入我们的社群，与我们共同分享、学习、成长。_

**-----------END-----------**

****[![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)](https://mp.weixin.qq.com/s?__biz=MzI4NTgxMDk1NA==&mid=2247506405&idx=1&sn=29bdac1ee34aaceade9e66e9b0867d8f&scene=21#wechat_redirect)****

****🚀** 我们正在招募新一期的实习生**

[![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)](https://mp.weixin.qq.com/s?__biz=MzI4NTgxMDk1NA==&mid=2247503698&idx=4&sn=ade3fdbb8a82ca59be3212c4843bb1a0&scene=21#wechat_redirect)

******🚀** 我们正在寻找有创造力的00后创业****

[![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)](https://mp.weixin.qq.com/s?__biz=MzI4NTgxMDk1NA==&mid=2247494663&idx=1&sn=8fab67231b9ebc593ac65864fd8f7e00&scene=21#wechat_redirect)

![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)

_**关于Z Potentials**_  

![图片](data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='1px' height='1px' viewBox='0 0 1 1' version='1.1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Ctitle%3E%3C/title%3E%3Cg stroke='none' stroke-width='1' fill='none' fill-rule='evenodd' fill-opacity='0'%3E%3Cg transform='translate(-249.000000, -126.000000)' fill='%23FFFFFF'%3E%3Crect x='249' y='126' width='1' height='1'%3E%3C/rect%3E%3C/g%3E%3C/g%3E%3C/svg%3E)