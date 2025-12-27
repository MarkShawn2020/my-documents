# 博客框架选型

## 选型依据

- 主流静态网站生成器框架排名[^rank]: https://jamstack.org/generators/

[^rank]: 排名的前三名分别是`nextjs`, `hugo`, `gatsby`，其中 hugo 是基于 go 语言的，其他两个都是基于 js，尤指基于 react，这也多少说明了目前 react 生态的繁荣，再往后还有 nuxt（基于 vue）的，是用于对标 nextjs 的。而关于 nextjs 和 gatsby，这两者有一些比较重要的区别，具体可以见 2022 年 nextjs 和 gatsby 详细对比：https://prismic.io/blog/compare-nextjs-vs-gatsby

## 选型列表

- nextjs 的一些 demo（包括一款基于 md 的博客）: https://nextjs.org/docs/basic-features/data-fetching/overview
- （选型 1）：基于 nextjs、md 的博客 demo: https://github.com/vercel/next.js/tree/canary/examples/blog-starter
- 基于 nextjs 的专用于博客生成的 nextra: https://nextra.vercel.app/
- （选型 2）：nextra 的开发分支: https://github.com/shuding/nextra/tree/core
- gatsby 的一些 demo（包括一款 gitbook 样式）: https://www.gatsbyjs.com/starters/
- （选型 3）：基于 gatsby、gitbook 的博客 demo: https://www.gatsbyjs.com/starters/hasura/gatsby-gitbook-starter/
- （选型 4）：hexo: https://hexo.io/zh-cn/

## 选型结果

最终选了选项 2，即 nextra，它的主要优点如下：

1. 底层基于目前最优秀、活跃的 nextjs 框架
2. 默认已配置了一个开箱即用、ui 尚可的模板工程(比 hexo 的默认效果强非常多，非常适合知识库)
3. 环境配置基本无压力，没有出现意外（gatsby 测试的几个 demo 都有依赖问题，nextjs 自己的 markdown demo 也有点问题）
4. nextra 拥有一个 core 分支，可以自己修改 nextra 的逻辑，然后再输出，所以在这点上，等价于拥有 nextjs 的完全开发能力，另外其工程设计、代码质量也很不错这点比我两年前用的 vuepress 要棒非常多（vuepress 也在排名之列）

所以基于以上，我认为 nextra 在生命力、易用性、扩展性、审美上，均达到了目标期望，是可以值得 all in 的 modern markdown-based blog framework.

## 其他

感谢立党哥推荐的 nextra 与昱昊哥推荐的 notion，实测下来确实都很棒，不过 notion 偏产品，所以不在本次技术横评之列。

!!! note 这是一条笔记

::: 这也是一条笔记（某些框架下）才可以看见 :::
