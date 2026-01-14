四个月前在自己的公众号上开设了一个合集[手工川 Claude Code 笔记](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=Mzg2OTg5NDg3Mg==&action=getalbum&album_id=4139219220980793350#wechat_redirect)，原定五篇每周一篇，但因为各种原因，直到现在也只更了第一篇：[手工川 Claude Code 笔记 01. feature management](https://mp.weixin.qq.com/s?__biz=Mzg2OTg5NDg3Mg==&mid=2247491936&idx=1&sn=b73a640dddbf2a14c15782becb400052&chksm=ce94bed7f9e337c1954e55ff72d1720a1e6566d00d32e1d5898615240e83627f4d7a7a930d59&token=1014699198&lang=zh_CN#rd)。

尽管这四个月整个AI Coding的世界日新月异令人目不暇接，但我的主要关注点却没有太大的变化，那就是如何高质量的vibe coding，简而言之，就是如何在vibe coding里确保每一个feature能被顺利推进与妥善管理。

这个逻辑在我看来是自然而然的，如果我们认可或者说相信或者说不排斥 AGI = Next Token Prediction，那Vibe Coding = Next Feature Management。

以上便是我们本期文章的一些简要背景，下面希望和大家分享我这一年在vibe coding上的一些探索、经验和教训，希望对大家有些启发。

在此之前，推荐我们往期在[社群交流产出的几篇文章](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=Mzg2OTg5NDg3Mg==&action=getalbum&album_id=4114785509204000771#wechat_redirect)：
- [Vol 51. Claude Code 实战交流与最佳实践](https://mp.weixin.qq.com/s?__biz=Mzg2OTg5NDg3Mg==&mid=2247489838&idx=1&sn=92a764b15df8fd573ff7936cbb456e74&chksm=ce974699f9e0cf8f498e3a48d3537189a67b388469387de6ae3a1a8ee15bb10924abc9d0df08&scene=178&cur_album_id=4114785509204000771&search_click_id=#rd)
- [一代人有一代人的抽象：Vibe Coding 正在重新定义软件工程](https://mp.weixin.qq.com/s?__biz=Mzg2OTg5NDg3Mg==&mid=2247490497&idx=1&sn=aa857990979a6698b487a93fcfb07c45&chksm=ce974476f9e0cd6005654e4231f6e70c17b68c82ce478aab2a7db31712c2538bac7e7f9cce72&scene=178&cur_album_id=4114785509204000771&search_click_id=#rd)
- [AGI 或许真的流产了，但 AI 的春天才刚刚开始 | Vibe Seminar 04](https://mp.weixin.qq.com/s?__biz=Mzg2OTg5NDg3Mg==&mid=2247491083&idx=1&sn=d98c61c5bb679f1fe3df333b143c4286&chksm=ce9741bcf9e0c8aa36f92ac6521144e622e757c1d364a14b8f76815a46f5a1610f76acdca47b&scene=178&cur_album_id=4114785509204000771&search_click_id=#rd)
- [十问 Agent Skills：一场围绕 AI 编码新范式的深度研讨](https://mp.weixin.qq.com/s?__biz=Mzg2OTg5NDg3Mg==&mid=2247493421&idx=1&sn=1da1dcfec0adffc41016224ea22a0d89&chksm=ce94b89af9e3318cccf82badfc8386f68a20ee5a121f6b8e5f334d37d465d38a2125c8b5a294&scene=178&cur_album_id=4114785509204000771&search_click_id=#rd)

以及搬运的几篇关于Agent设计的文章：
- [Vivex：Claude Code 为什么好用 | 深度](https://mp.weixin.qq.com/s/9bW4ONCFMgdypPiEeHn3rg)
- [深度 | 为何强大≠好用？（AI Agent 产品经理必看）](https://mp.weixin.qq.com/s/oAg4EVL-5QIyoE-riF4GPA)
- [Shopify：从“作坊”到“工厂”，如何构建生产级AI Agent系统？](https://mp.weixin.qq.com/s/nSd9TVmTT2yg4M43QkAWDg)
- [谷歌万字长文解密：从原型到生产，构建可靠AI Agents的全栈技术指南](https://mp.weixin.qq.com/s/EQ5A_l4sWJ9AMB7i-7B9lw)

它们共同构成了我对AI Coding理论层面部分重要的理解。

---

我第一个想探讨的话题，是vibe coding为什么有效。

【此处联系ODDA循环，我们在很多次公开分享中有提及】

![](http://cdn.cs-magic.cn/picgo/20251230105417959.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

