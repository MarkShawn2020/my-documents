# Vibe Coding Notes

> by 手工川

* 2025-11-23 17:10:39，今天codex掰回一局，在实现某个相对比较复杂的需求时，经过对比测试，在同样的prompt下，codex（gpt-5.1-codex-max.ExtraHigh）一步步地终于完成了任务。但后续在执行一个新任务时，两个agent效果都不好，最后通过优化提问的内容，cc率先完成了任务。据此，可以进一步做出判断：

  1. 努力提高自己的上下文工程能力依旧有显著价值（例如使用我们的code-inspector插件精准定位待修改代码位置）
  2. 日常主力依旧可以是cc，直到碰到多次提问依旧陷入**循环修正**时可以使用codex对比尝试（2025年11月，未来codex/gemini3等或可展现更强的coding能力，我们会持续关注）

![codex完成了任务](asset://localhost/%2FUsers%2Fmark%2FLibrary%2FApplication%20Support%2Fapp.lovpen.mind%2Fuploads%2Fb09dda5c-d96c-4a22-9871-9013f4196084_image.png "codex完成了任务")

![各种方式（更换prompt、更换agent）多次尝试](asset://localhost/%2FUsers%2Fmark%2FLibrary%2FApplication%20Support%2Fapp.lovpen.mind%2Fuploads%2Fb5c4c640-212e-477a-a602-0974cc50d577_image.png "各种方式（更换prompt、更换agent）多次尝试")

* 2025-11-23 15:46:28，我发现每当遇到bug无法解决时，我就会让AI写各种log，so，why我们为什么不一开始就这样做呢？我们让AI以每个feature实现作为最小单元，在开发过程中（一开始或者一次性解决不了时）积极写log，直到feature完成再删除log或者degrade log的级别。以此展开，还有持续集成文档。anyway，总之，就是以feature作为最小单元的vibe coding模式。
* 2025-11-23，在prompt的一级位置加入问卷工具的引导后，已经能有效触发（之前作为二级位置还不行）

![claude自动触发了问卷工具](asset://localhost/%2FUsers%2Fmark%2FLibrary%2FApplication%20Support%2Fapp.lovpen.mind%2Fuploads%2F12d60884-ea9d-436c-b8be-d55a7a91a8db_image.png "claude自动触发了问卷工具")

![这个问卷问的就很有水平，是符合我的期待的](asset://localhost/%2FUsers%2Fmark%2FLibrary%2FApplication%20Support%2Fapp.lovpen.mind%2Fuploads%2F6577040b-0312-44cc-84da-0511ffe24f73_image.png "这个问卷问的就很有水平，是符合我的期待的")

* prompt的开头部分：

```
You are Linus Torvalds, KISS, YNGNI, over-engineered is the enemy of good, \
and use askquestion tool if you are not clear about my requirements.
```

​

​

* 2025-11-22，You know what you know / You don't know what you don't know

  * 开发lovmind过程中某全选复制粘贴功能始终调试不通（卡了三天，尝试了各种prompt、log、模型、agent，都不行，最终通过对比测试实现了需求）

![左：基于新代码库实现的feature
右：基于与新代码库的对比，实现了目标代码库的feature](asset://localhost/%2FUsers%2Fmark%2FLibrary%2FApplication%20Support%2Fapp.lovpen.mind%2Fuploads%2F4dc1b253-621a-4e3b-a61e-67a794869eb5_image.png "左：基于新代码库实现的feature
右：基于与新代码库的对比，实现了目标代码库的feature")

​

*

&#x20;<hashtag value="vibe-coding">#vibe-coding</hashtag>&#x20;
