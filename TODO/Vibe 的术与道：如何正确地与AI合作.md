

作为一名技术博主，原本想的是 Vibe Coding，但转念一想，不仅仅是 Coding，其实是 Writing、Proposing 等所有与 AI 交互的场景，其实都可以视为一种 Vibe，即我在 [手工川的 AI 方法论 | 上海 AI NIGHT 分享](https://mp.weixin.qq.com/s/zw7KDC0bUZldqpU3IwhmZg) 中所提及的 **WYFIWYG（What You Feel Is What You Get，所想即所得）**，这是对以往 **WFSIWYG（What You See Is What You Get，所见即所得）** 的一次飞跃。

但 AI 想要落到实地，我们还需要解决如何从 **我所想** 真正地变成 **我所得**。

前段时间一位好朋友找到我，她是位音乐教师，几乎完全不懂 AI，问我如何才能利用 AI 实现作谱。

我显然也不知道作曲，但我知道如何与 AI 合作：

1. **如何喂给 AI 看得懂的东西（让 AI 舒服）**
2. **如何提高与 AI 的默契度（让自己舒服）**

对于第一点（让AI舒服），虽然我不懂音乐，但我懂计算机，知道计算机世界里有一种东西叫做 DSL，也很确定音乐一定有音乐的 DSL，我只要让 AI 生成这样的 DSL，然后导入专业的音乐软件，就变相实现了 AI 作曲。

```ad-tip DSL (Domain-Specific Language)

领域特定语言 (DSL) 是一种为解决特定领域问题而设计的专用计算机语言。与通用编程语言（如 Java 或 Python）旨在解决各种问题不同，DSL 使用特定领域的词汇、概念和语法，使其在该专业领域内更具表现力、更高效。

例如，SQL 是用于数据库查询的 DSL，HTML 是用于定义网页结构的 DSL。通过为特定任务提供量身定制的语法，DSL 可以让领域专家（如分析师或设计师）更轻松地工作，并使代码更简洁、更易于理解。
```

果不其然，**AI 助手（我最推荐的日用 AI 助手：ai.studio）** 推荐了我们 `MusicXML`。

```ad-tip MusicXML

MusicXML 是一种基于 XML（可扩展标记语言）的开放标准文件格式，专为表示西方的通用音乐记谱法而设计。它的核心目标是成为不同乐谱软件之间交换和存档数字乐谱的通用语言。

作为一种领域特定语言（DSL），MusicXML 使用描述性的标签来详细记录乐谱的每一个元素，例如 `<note>`（音符）、`<pitch>`（音高）、`<duration>`（时值）和 `<articulations>`（演奏法）。它专注于“是什么”（乐谱的结构和内容），而不是“如何做”（如何播放或绘制）。

在 MusicXML 出现之前，不同打谱软件（如 Finale、Sibelius）之间的文件互不兼容。MusicXML 的出现解决了这一难题，实现了乐谱数据的无缝迁移和共享，已成为数字乐谱领域的事实标准。
```

接着，朋友在 AI 助手的帮助下，很快生成了一份 MusicXML 文件，朋友问怎么用啊？

我说：”**来，我教你，问 AI**“。

这不是玩笑。

哪里不懂，就问 AI 就好了，你就说，我现在有一份 MusicXML 文件，我不知道怎么用，我该怎么办；至于朋友，她会问：如何导入到西贝柳斯。当然，朋友甚至可能连”导入“这个词都想不到，哪页没问题，直接问”我怎么在西贝柳斯里用这个 MusicXML 文件“。

```ad-tip 西贝柳斯 (Sibelius)

西贝柳斯（Sibelius）是由 Avid 公司开发的一款世界领先的专业级乐谱制作软件（打谱软件）。它是作曲家、编曲家、音乐出版商和教育工作者的首选工具之一，用于创建、编辑和打印达到出版标准的高质量乐谱。

与 MusicXML 这样的数据格式不同，西贝柳斯是一个功能完备的应用程序。它提供图形用户界面，用户可以通过鼠标、键盘或 MIDI 设备直观地输入音符和乐谱符号。其核心优势在于强大的自动化布局与排版引擎、逼真的音频回放功能以及丰富的自定义选项。

作为行业标准，西贝柳斯能够完美地导入和导出 MusicXML 文件，这使其能够与 Finale 等其他主流打谱软件进行数据交换，实现了乐谱文件的跨平台协作。
```

**AI 的向下兼容能力是史无前例的，而且它还绝对耐心；尽管说话没那么靠谱，但对普通人来说，至少比大部分身边的人更靠谱。**

就这样，朋友就分分钟实现了：我想要 xxxx 这样风格的曲子，然后在她擅长的音乐软件里听到了 AI 生成的效果。

当然，**prompt 工程** 是一个大章节，Anthropic 的官方文档里专门有一篇 [Claude 4 Prompt 工程的最佳实践](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/claude-4-best-practices)，我让 claude 自己总结为类似[Python 之禅](https://peps.python.org/pep-0020/)的表达方式如下：

```ad-tip The Zen of Vibe Coding, by Claude-Opus-4.1

明确优于模糊。

上下文胜过孤立指令。

正向指引优于负向限制。

具体胜过抽象。

示例应当纯粹。

并行优于串行。

通用性重于特例。

思考带来洞察。

格式即是沟通。

简单任务也值得完整对待。

现在胜过永不。

面对歧义，拒绝猜测的诱惑。

应当有一种——最好只有一种——明确的方式来表达需求。

虽然这种方式在开始时可能并不明显，除非你已经深谙Claude 4的特性。

实用性永远战胜纯粹性——但这不意味着牺牲清晰度。

错误永远不应该悄悄传递。

如果实现很难解释，那提示词就需要重写。

如果实现很容易解释，那提示词可能已经足够好。

精确的指令是个好主意——让我们多写一些这样的指令。
```

基于上述这些原则，都可以让AI更舒服，从而实现自己的功能性需求。

下一步是让自己舒服，提高自己的非功能性需求。

这里面也有很多种办法，比如 Anthropic 官方有个 [prompt improver](https://www.anthropic.com/news/prompt-improver)，可以用于调试优化自己的prompt：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/08e719ce7b6340737689df555e2a1a5f.png?x-oss-process=image/quality,q_90/rotate,0)

它甚至支持多参数、多prompt的二维调试对比，尽管我实际测试时多prompt部分好像有点不太明白。

在我的往期文章 [手工川的 AI 方法论 | 上海 AI NIGHT 分享](https://mp.weixin.qq.com/s/zw7KDC0bUZldqpU3IwhmZg) 里也提到了一种 **主动压缩** 的技巧，也可以实现 prompt 的不断迭代优化，我也在考虑封装成一个专门的小产品，供大家使用。

除了压缩，还可以变体，比如 claude code 最近新出了 [output-style](https://docs.anthropic.com/en/docs/claude-code/output-styles)，可以修改AI的输出风格，比如让它以霸道总裁或者温柔女友的风格与你对话，既不会降低回复的质量，还能顺带提供情绪价值，如果再接个好一点的 TTS 语音输出（例如：[豆包的端到端语音大模型](https://www.volcengine.com/docs/6561/1594360)），体验直接拉满。

```ad-tip TTS (Text-to-Speech)

文本转语音（Text-to-Speech，简称TTS），也称为语音合成，是一种将书面文本转换为人类语音输出的技术。它的核心目标是让计算机或设备能够“朗读”数字文本，是实现人机语音交互的关键组成部分。

现代TTS系统通常基于深度学习，其工作流程主要包括两个阶段：首先，通过自然语言处理（NLP）前端分析文本，将其转换为包含发音、语调、节奏等信息的语言学特征；然后，由声学模型（如声码器 Vocoder）后端将这些特征合成为最终可听的音频波形。

得益于神经网络技术的发展，TTS生成的语音已从早期机械、生硬的电子音，发展到如今在音色、情感和自然度上都与真人声音高度相似的水平。这项技术广泛应用于语音助手、导航系统、有声读物以及为视障人士服务的辅助功能中。
```

总之，**Vibe 的核心就是 WYFIWYG**，时刻体悟这点，不要把 AI 只当做工具，要当做人，一个有智慧的人，human，you know？


>AI用的好的人，一定不会是软件工程师，而是那些善于沟通的，有people skill的人。 —— 马工（公众号：瑞典马工）
>
>More than machinery we need humanity. —— [Charlie Chaplin : The Final Speech from The Great Dictator](https://www.charliechaplin.com/en/articles/29-the-final-speech-from-the-great-dictator-)

脑子灵一点~
