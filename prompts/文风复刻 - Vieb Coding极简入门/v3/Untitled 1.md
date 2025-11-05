# 我从 Dify 源码里挖出个宝贝，然后花两天把它改得更狠了

> 本文适合中高级前端工程师，以及所有在用 AI 辅助编程的开发者。

## 一个让人上瘾的小功能

凌晨三点，我盯着 Dify 的源码发呆。

不是 debug，是在找宝贝。

作为一个重度 Claude Code 用户，我每天要在终端和 AI 之间复制粘贴上百次代码路径。你懂的，告诉 AI "去改那个组件" 远不如告诉它 "去改 `src/components/header/index.tsx:42` 这一行"。

**上下文精准度，决定了 AI 编程的效率上限。**

就在我快要放弃的时候，突然在 Dify 的 package.json 里看到一个不起眼的依赖：`code-inspector-plugin`。

这玩意儿是什么？

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined68747470733a2f2f63646e2e6a7364656c6976722e6e65742f67682f7a682d6c782f7374617469632d696d672f636f64652d696e73706563746f722f64656d6f2e676966)

**按住快捷键，点击页面上任何元素，自动在 IDE 中打开对应源代码。**

牛逼。

我立刻写了篇文章安利（[还在用截图 Vibe Coding？太慢了！](https://mp.weixin.qq.com/s/Sjr_7YQgtZzNM5v28oZ9mA)），流量稳步增长：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105172439940.png)

但问题来了——

## 它还不够狠

这个插件默认是给"正常"开发者用的，点击后会打开 VSCode 之类的 IDE。

可我不正常啊。

我是个 vibe coder，我的 IDE 是 iTerm，我的编辑器是 Claude Code，我需要的不是"打开文件"，而是"获取精确路径然后复制给 AI"。

于是我决定魔改它。

第一版改动很简单，加个功能：点击后不打开 IDE，而是复制完整路径到剪贴板。代码跑通了，功能实现了，我很开心。

直到我试图把改动分享给其他人。

## 两个让人崩溃的技术坑

### 坑一：本地包死活加载不了

正常人的开发流程：

```bash
# 本地开发
pnpm add ../my-modified-plugin
# 完美运行
```

我的情况：

```bash
# 本地开发
pnpm add ../my-modified-plugin
# Module Not Found ???
```

调了整整一天，翻遍了源码，终于在 `packages/core/src/server/use-client.ts:382` 找到了罪魁祸首——原作者写的包索引机制不够 robust，不支持外部引用。

**解决方案**：把生成的临时文件改存到执行环境的 `.cache` 文件夹，同时支持本地 demo 和外部引用。一行代码，解决一天的痛苦。

### 坑二：不想改包名但又要独立发布

我不想 fork 一个独立版本（维护成本高），也不想改包名（`@mark/code-inspector-plugin` 太丑了），但又需要独立发布我的修改版。

这看起来像个悖论。

我和 AI 聊了两个小时，它给了我一个神奇的方案：**Cloudsmith 私有 registry**。

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174745821.png)

简单说，就是搭建自己的 npm 镜像服务器，包名不变，但从我的服务器下载。

## 优雅的解决方案

### 方案一：偷天换日式

在项目根目录的 `.npmrc` 文件里加一行：

```yaml
registry=https://npm.cloudsmith.io/mark/code-inspector/
```

这会让所有包都从我的私有源下载。"等等，那其他包怎么办？"

别慌，Cloudsmith 支持设置 upstream：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105175744733.png)

我的服务器上没有的包，会自动从 npmjs 拉取。完美的中间人攻击（褒义）。

别忘了加上：

```yaml
always-auth=true
```

### 方案二：精准打击式

如果你不想改全局 registry，可以只针对这个包：

```bash
pnpm add code-inspector-plugin@https://npm.cloudsmith.io/mark/code-inspector/code-inspector-plugin/-/code-inspector-plugin-1.2.11.tgz
```

由于它还依赖其他分包，在 `.npmrc` 里加上：

```yaml
@code-inspector:registry=https://npm.cloudsmith.io/mark/code-inspector/
```

## 和原作者的灵魂对话

改完之后，我兴冲冲地联系了原作者：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174112464.png)

"兄弟，我给你的插件加了个超酷的功能！"

"哦，听起来不错，但我最近在忙别的..."

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174027321.png)

行吧，大佬都这样，我理解。

## 为什么要这么折腾？

你可能会问：就为了复制个路径，至于花两天时间魔改别人的代码吗？

我的答案是：**太值了。**

在 AI 编程时代，每一次不精准的上下文描述，都会导致 AI 理解偏差。每一次理解偏差，都需要多轮对话纠正。每多一轮对话，效率就降低 20%。

当你一天要和 AI 对话 200 次时，这个效率提升会让你的产出翻倍。

**精准的上下文工程，是 AI 编程的核心竞争力。**

这也是为什么我会在凌晨三点读 Dify 源码，为什么会花两天时间改一个"小功能"。

在 Vibe Coding 的世界里，每一个细节优化，都可能带来指数级的效率提升。

---

_如果你也想试试这个魔改版插件，安装方法我都写在上面了。_

_期待你的 vibe coding 之旅一帆风顺。_

_下次凌晨三点，或许我们会在某个开源项目的 commit history 里相遇。_