
# Vibe Coding 实战：几分钟重构一个 Chrome 扩展

作为科技自媒体，我每天都在和各种网络素材打交道。收藏一篇好文章、分享一个有趣的项目、整理一份技术周报——这些场景都需要一个看似简单却极其高频的操作：**复制网页的标题和链接**。

很久以前我用一个叫 TabList 的插件，后来它下架了。再后来我在自己的 lovpen-sider 项目里集成了复制功能，因为当时想做一个全能的 sidebar 插件。但随着精力分散和产品定位调整，我决定把这个功能单独抽离出来。

今晚，我和 Claude Code 进行了一次对话。几分钟后，一个全新的独立项目 **Lovpen Copy Title** 就诞生了。

## 痛点：复制链接这件小事

我的日常工作流涉及大量的内容整理：

- 在 Obsidian 里用 Markdown 格式记录参考资料
- 在微信群里分享值得一看的文章（这时候 Markdown 格式就不合适了）
- 给公众号文章添加外链引用

这意味着我需要**多种复制格式**：有时候只要 URL，有时候需要「标题 + 网址」，有时候需要 `[标题](URL)` 的 Markdown 链接。而且必须足够快——最好是一个快捷键搞定。

<!-- 评注建议：可以补充一下为什么现有的"右键复制链接"不能满足需求，强调"标题+链接"组合的价值 -->

## 产品：Lovpen Copy Title

最终实现的功能很简单但很实用：

- **⌘K**：复制「标题 + 网址」格式
- **⌘⇧K**：复制 Markdown 链接格式
- 支持 5 种预设格式 + 自定义模板
- 复制成功后显示优雅的提示

![cmd+K复制标题格式效果](https://github.com/MarkShawn2020/chrome-copy-title/raw/main/assets/cmd+K%E5%A4%8D%E5%88%B6%E6%A0%87%E9%A2%98%E6%A0%BC%E5%BC%8F%E6%95%88%E6%9E%9C.png)

![cmd+shift+K复制markdown格式效果](https://github.com/MarkShawn2020/chrome-copy-title/raw/main/assets/cmd+shift+K%E5%A4%8D%E5%88%B6markdown%E6%A0%BC%E5%BC%8F%E6%95%88%E6%9E%9C.png)

技术栈选择了 TypeScript + React + Tailwind + Vite，延续了原项目的技术风格，也方便后续维护。

```ad-tip

MV3（Manifest V3）是 Chrome 扩展的最新架构规范。相比 MV2，它引入了 Service Worker 替代 Background Page、更严格的权限模型、以及对远程代码的限制。虽然提升了安全性和性能，但也给开发者带来了一些适配成本。
```

## 开发过程：一次典型的 Vibe Coding

这次开发最有意思的部分，是 Claude Code 展现出的「架构思维」。

我的第一条 prompt 非常简单：

> 我想把本项目中的标题复制功能独立为一个插件

Claude 没有立刻动手写代码，而是先做了一轮深入分析。它扫描了原项目中涉及复制功能的所有代码模块：

![](http://cdn.cs-magic.cn/lovpen/table-1765727743893-78i3pa.png)

然后它给出了三种方案的对比：

![](http://cdn.cs-magic.cn/lovpen/table-1765727745310-zbnt54.png)

<!-- 评注建议：这里可以展开讲讲为什么「完全独立」是最佳选择，以及这种方案对比思维在日常开发中的价值 -->

Claude 推荐了方案 A，并给出了清晰的理由：标题复制功能完整自洽，无需依赖原项目其他功能；作为独立插件可以上架 Chrome Web Store；维护成本低，无跨项目同步问题。

它甚至主动规划了新项目的目录结构和权限最小化方案：

```
copy-title-extension/
├── manifest.json
├── src/
│   ├── background.ts      # 快捷键处理
│   ├── popup/
│   │   ├── index.html     # popup UI
│   │   ├── popup.ts       # 交互逻辑
│   │   └── popup.css      # 样式
│   └── storage.ts         # 简化版存储
├── icons/
└── package.json
```

接下来它问了我几个关键决策点：UI 框架选择、功能范围、构建工具、是否需要与原项目设置同步。

我只回复了一句：

> 可以迁移，但项目名要加前缀 chrome-

然后 Claude 就开始执行了。几分钟后，一个完整的项目 `chrome-copy-title` 就创建好了——包括所有源代码、配置文件、构建脚本。

```ad-tip

Vibe Coding 是一种新兴的编程范式，开发者通过自然语言与 AI 协作完成软件开发。核心理念是「描述意图，而非编写代码」。开发者负责把控方向和决策，AI 负责分析、设计和实现。这种模式特别适合快速原型开发和代码重构场景。
```

## 踩坑：Chrome 快捷键的那些事

在第一次开发 TabList 替代版时，我在快捷键配置上卡了很久。Chrome Extension 的快捷键系统有几个「隐藏规则」：

1. **快捷键个数有限制**：每个扩展最多只能注册 4 个快捷键
2. **组合键有限制**：`Option` 和 `Command` 似乎不能同时使用
3. **注册机制**：修改 manifest 中的 commands 后，需要**卸载扩展后重新安装**才会生效，仅仅 reload 是不够的

Claude 在这方面的知识确实有盲区——它不太了解 Google 的这些底层设定。这次迁移因为沿用了已经验证过的快捷键配置，所以没有造成太大阻碍。

<!-- 评注建议：可以补充一下如何自定义快捷键（chrome://extensions/shortcuts），以及权限设置的建议 -->

安装扩展后，建议将其设置为「完全访问权限」以确保快捷键在所有页面生效：

![建议完全访问权限](https://github.com/MarkShawn2020/chrome-copy-title/raw/main/assets/%E5%BB%BA%E8%AE%AE%E5%AE%8C%E5%85%A8%E8%AE%BF%E9%97%AE%E6%9D%83%E9%99%90.png)

## 本地安装

如果你也想用这个扩展，可以从 GitHub 克隆后本地安装：

```bash
git clone https://github.com/MarkShawn2020/chrome-copy-title.git
cd chrome-copy-title
pnpm install
pnpm build
```

然后打开 `chrome://extensions/`，开启「开发者模式」，点击「加载已解压的扩展程序」，选择 `dist/` 目录即可。

![本地安装插件](https://github.com/MarkShawn2020/chrome-copy-title/raw/main/assets/%E6%9C%AC%E5%9C%B0%E5%AE%89%E8%A3%85%E6%8F%92%E4%BB%B6.png)

## 写在最后

这次开发体验让我再次感受到 Vibe Coding 的魅力：

- **从 idea 到可用版本只用了几分钟**
- **AI 不只是写代码，更是在做架构决策**
- **人类负责把控方向，AI 负责执行细节**

有趣的是，这个项目的 GitHub Contributors 列表里有两个人：我和 Claude。这大概就是人机协作的最好注脚。

项目地址：[https://github.com/MarkShawn2020/chrome-copy-title](https://github.com/MarkShawn2020/chrome-copy-title)
