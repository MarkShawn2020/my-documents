

> 本文纯技术，但我保证不枯燥。适合对象：想让 AI 编程效率起飞的前端工程师。

## 一切从一个"小需求"开始

上个月，我在扒 Dify 源码时，突然发现了一个神奇的东西。

一个叫 `code-inspector-plugin` 的前端插件，默默躺在依赖里。

试了一下，我整个人都惊了。

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined68747470733a2f2f63646e2e6a7364656c6976722e6e65742f67682f7a682d6c782f7374617469632d696d672f636f64652d696e73706563746f722f64656d6f2e676966)

看到没？按住快捷键，点击页面上任何组件，IDE 自动打开对应源代码。

就像开了透视眼。

我当时就把这个发现写成了文章（[还在用截图 Vibe Coding？太慢了！](https://mp.weixin.qq.com/s/Sjr_7YQgtZzNM5v28oZ9mA)），结果流量还挺猛：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105172439940.png)

但问题来了。

## 当 IDE 不再是 IDE

我是个重度 vibe coding 患者。

什么意思？我基本不在传统 IDE 里写代码了。我的"IDE"是 Claude Code，是 Cursor，是 iTerm。

所以这个"跳转到 IDE"的功能，对我来说有点鸡肋。

我真正需要的是什么？

**是精准的文件路径。**

想象一下，你在和 AI 结对编程，你说："帮我优化一下这个组件。"

AI 问："哪个组件？"

你："就是... 那个... 登录框那个..."

AI："？？？"

要是能直接复制组件的精确路径，直接扔给 AI，那该多爽？

于是，我决定魔改它。

## 两天的疯狂 Debug

改个功能能有多难？

我当时也是这么想的。

结果，我遇到了两个让人抓狂的问题。

### 坑一：本地包死活加载不上

正常来说，`pnpm add file:../my-plugin` 就能引用本地包。

但这个插件偏不。

`Module Not Found`。

各种姿势都试了，就是不行。

我翻遍了源码，终于在 `packages/core/src/server/use-client.ts` 的第382行发现了真相——

包索引机制写死了路径，根本不支持外部引用。

怎么办？

改！

把生成文件的位置改到执行环境的 `.cache` 文件夹，问题解决。

### 坑二：不想改包名的执念

为了让其他人能用上我的魔改版，最简单的办法是什么？

改个包名，发到 npm。

比如改成 `@mark/code-inspector-plugin`。

但这样做有个问题——以后原作者更新了，我得手动同步，还得改一堆 import。

太不优雅了。

我想要的是：**不改包名，但又能独立发布。**

这可能吗？

## 私有 npm 的魔法

我问了 Claude 老师很久，终于找到了答案：

**Cloudsmith。**

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174745821.png)

这是一个私有包托管服务。最骚的是，它能让你发布同名包，通过 registry 优先级来实现"覆盖"。

具体怎么玩？

### 方案一：偷天换日

在项目根目录创建 `.npmrc`：

```yaml
@code-inspector:registry=https://npm.cloudsmith.io/mark/code-inspector/
```

然后安装主包（但需要指定registry）：

```bash
pnpm add code-inspector-plugin@https://npm.cloudsmith.io/mark/code-inspector/code-inspector-plugin/-/code-inspector-plugin-1.2.11.tgz

```

它会优先从我的私有仓库拉包，而不是 npmjs。

### 方案二：全局代理

更激进一点，直接改掉默认 registry：

```yaml
registry=https://npm.cloudsmith.io/mark/code-inspector/
always-auth=true
```

"等等，"你可能会问，"那其他包怎么办？"

别慌，Cloudsmith 有个骚操作叫 upstream：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105175744733.png)

设置 npmjs 为上游，我仓库里没有的包，自动从 npmjs 拉。

完美！

## 原作者的反应

搞定之后，我兴冲冲地联系了原作者：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174112464.png)

"兄弟，我给你的插件加了个新功能！"

原作者很友好，但他有自己的想法：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105174027321.png)

暂时没空搞这个。

行吧，那就我自己先用着。

## 回到最初的问题

你可能会觉得奇怪——

花两天时间，就为了能复制一个文件路径？

至于吗？

如果你这么想，说明你还没体会过「精准上下文工程」的威力。

当你给 AI 的每一个指令都精准到行号，当你的每一次对话都不需要解释"是哪个文件"，当 AI 永远不会理解错你的意图...

你的编程效率，真的会起飞。

这就是为什么，我愿意花两天时间，死磕这个看似简单的功能。

因为它能让我接下来的每一天，都节省无数次复制粘贴和解释说明。

## 最后

如果你也是 vibe coding 玩家，欢迎试试我的魔改版：

```bash
# 方式一：指定 registry
pnpm add code-inspector-plugin@https://npm.cloudsmith.io/mark/code-inspector/code-inspector-plugin/-/code-inspector-plugin-1.2.11.tgz

# 方式二：配置 .npmrc 后直接安装
pnpm add code-inspector-plugin
```

对了，如果你觉得这个改动有意思，帮我去原仓库点个 star，顺便留言支持下这个 feature。

说不定作者看到呼声高，就会合并了呢？

毕竟，谁不想让自己的 AI 编程效率翻倍呢？

---

**P.S.** 下次当你觉得某个工具"差一点点"的时候，别忍着。改它！哪怕要花两天，哪怕要学一堆新东西。相信我，值得的。