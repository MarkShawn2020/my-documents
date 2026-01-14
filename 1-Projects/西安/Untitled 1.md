我知道你们可能看不懂，我大白话解释一下这是什么？

这是一个原生通知系统，每次iterm里的某个tab里的tmux的某个window的某个pane里的cc完成任务或者问卷工具之时就需要human in the loop！

这时候我们的 Lovnotifier 就会弹出一个通知，无论我现在在做什么，点击它就可以精准跳回iterm里的那个tab里的tmux的那个window的那个pane，然后检查cc的工作！

That's it，you know？Enjoy it！My bro！

---

太爽了，给自己开发了一个并行vibe coding通知器，这样就可以变成一个消息队列有序地消费各个ai的工作。

![](http://cdn.cs-magic.cn/picgo/20251221203751158.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


我是基于  terminal-notifier   实现的，过程挺艰辛的，应该说调试了一下午吧，最大的难点在于两个：

1. 点击「显示」后跳转回「iterm2中原tab内原tmux的原window的原pane」，这一步我通过循循善诱的办法一步步先让ai写个简单的程序，再慢慢升级实现的，最后能实现在cc的post-hook里精准地拿到上下文完成跳转，已经超出我的预期了
2. 第二个是使用自己的App（Lovnotifier）以及Icon，如果只完成1，样式不好看，但没想到为了实现自定义样式，费了巨大的劲，cc怎么都搞不定，最后用codex，我让codex联网检索仔细分析，最后它说如果我们只基于 terminal-notifier  的方案是不行的，必须亲自基于objc/swift开发一个最小的app或者把 terminal-notifier  包装成一个独立的app（如果这就是真相的话，那cc途中应该也给出过）。我实在没有精力去challenge它了，我说好吧，那你包吧，最后就搞定了！

![](http://cdn.cs-magic.cn/picgo/20251221204221308.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


结果发现还有一个漏网之鱼，那就是问卷工具！

当cc执行问卷工具时，会堵塞任务，也是需要我们返回去解决的！

![](http://cdn.cs-magic.cn/picgo/20251221212552096.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


让 cc 仿着写了一个，但似乎并不work：

![](http://cdn.cs-magic.cn/picgo/20251221212944858.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

后来绕了一圈发现，是因为我同时在另一个进程里让cc给我改通知的按钮呈现，结果它使用alterer取代了基于 terminal-notifier   的Lovnotifier，而这个似乎有问题，直接通知出不来……

花了老大劲debug清除后，回头让cc重新写，就一次性搞定了！

![显式触发问卷工具](http://cdn.cs-magic.cn/picgo/20251221221035184.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


![一旦问卷工具触发，我们的程序就开始弹通知了，点击后就可以跳转到对应的程序](http://cdn.cs-magic.cn/picgo/20251221221030116.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

---

最后，上架！

> 手工川工作室新上架Lovnotifier，一款自用的【真并发】vibe coding通知系统让自己成为AI督工，超级有用，今天优化了一整天，see more at：https://lovstudio.ai/app/lovnotifier

![](http://cdn.cs-magic.cn/picgo/54022b1f1681caddd23f9cfccf2a4639.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

*btw，考虑到我在基于tmux并发vibe coding的路上解决的各大痛点，是时候做一个真vibe coding助手了，有一说一：）*