

凌晨 2 点，我盯着 Claude Code 的对话框，第 47 次截图，第 47 次粘贴。

"帮我修复这个按钮的样式 bug。"

Claude 很努力地分析着我的截图："根据图片显示，这可能是一个 flex 布局的对齐问题，建议检查 components/Button 目录下的..."

5 分钟过去了，它还在猜。

我突然意识到一个荒诞的事实：2025 年了，我们已经有了能写代码的 AI，却还在用石器时代的方式告诉它 bug 在哪里。这就像你有一个超级助手，他能瞬间修复任何问题，但你必须用哑语比划半天才能告诉他东西坏在哪。

说真的，那一刻我差点想摔键盘。

---

事情的转机出现在我扒 Dify 源码的时候。你知道的，作为一个技术博主，扒优秀项目的源码是日常。Dify 作为目前最火的 AI 应用开发平台，代码质量相当高，我本来只是想学习下它的架构设计。

然后在 package.json 里，我发现了一个有意思的依赖：`code-inspector-plugin`。

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105220436597.png)

这名字听着就很带感，inspector，检查员？我顺手点进去看了下文档——妈的，宝藏啊！

这插件能让你直接从网页上点击任何元素，瞬间在 IDE 里打开对应的源代码文件，精确到行。你按住`Opt+Shift`，鼠标悬浮在页面上，每个元素都会显示它的源码位置。点一下，VSCode 自动打开，光标已经定位好了。

```html
<!-- 原理很简单，编译后的HTML会带上这样的属性 -->
<div data-insp-path="src/components/Button.tsx:42:10">
  Click Me
</div>
```

就这么一个简单的映射，但效果炸裂。我当时的感觉就像——你用了十年的诺基亚，突然有人递给你一部 iPhone。

---

激动了大概 30 秒，我就发现问题了。

这个插件默认是给 Cursor、VSCode 这些传统 IDE 用户设计的。点击就跳转到 IDE，很合理。但我是个重度 Vibe Coding 用户啊！什么是 Vibe Coding？说白了就是完全在 AI 对话界面里写代码，根本不开 IDE。

我们这群人已经养成了一种奇怪的习惯：在 Claude Code 或者 Codex 里直接`@`文件路径，然后让 AI 帮我们改代码。IDE？那是什么，能吃吗？

所以我需要的不是"打开 IDE"，而是"复制路径"。我要的是点一下按钮，路径直接进剪贴板，然后我粘贴给 Claude："喂，src/components/Button.tsx:42:10 有个 bug，帮我搞定。"

行吧，自己动手丰衣足食，开始魔改。

---

第一个想法很简单：加个切换按钮，用户可以选择是"打开 IDE"还是"复制路径"。改代码倒是不难，几个小时就搞定了基本功能。真正的噩梦从测试开始。

我想用`pnpm add ../code-inspector-plugin`的方式本地测试我的修改。结果呢？Module not found！

我懵了。明明路径是对的，为什么就是找不到模块？

接下来的 8 个小时，我像个侦探一样在源码里追踪问题。console.log 打了一堆，断点打了无数个，最后终于定位到`packages/core/src/server/use-client.ts`的第 382 行。

原来这货的包索引机制有个隐藏假设：它默认自己永远在 node_modules 里运行。当你用本地路径引用时，这个假设就崩了。

解决方案其实很简单，把生成文件改存到被执行环境的`.cache`文件夹就行。但找到这个解决方案，花了我整整一天。

**一行代码的修改，背后是 8 小时的 debug。**

我发誓，那天晚上我真的考虑过转行。

---

第二天，代码改完了，准备发布。新的问题来了：包名。

原作者已经在 npmjs 上占了`code-inspector-plugin`这个名字。我有几个选择，每个都很蛋疼：

1. 改包名 → monorepo 里几十处引用都要改，还会与 upstream 彻底脱轨
2. 用 GitHub Packages → 必须用 scope 包名（@xxx/code-inspector），还是要大改
3. 等原作者 merge 我的 PR → 我联系了原作者，人很 nice，但我们在设计理念上有分歧，而且他最近比较忙

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105220551795.png)

正当我准备硬着头皮改包名的时候，Claude 给了我一个建议：用 Cloudsmith 搭私有 npm 仓库。

说实话，我之前从没听说过 Cloudsmith。但研究了一下，这方案简直绝了。

---

Cloudsmith 最牛的地方是它支持 upstream。什么意思呢？

1. 我在 Cloudsmith 上发布同名包`code-inspector-plugin`
2. 设置 npmjs 为 upstream
3. 当用户从我的仓库安装包时，如果某个依赖在我这儿找不到，会自动去 npmjs 找

![我发布的插件，source: https://cloudsmith.io/~mark/repos/code-inspector/packages/](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105220655305.png)


这意味着什么？**我可以完全不改包名，直接"劫持"这个包的安装流程。**

当然，要让这个方案 work，用户需要配置一下。这里有两种方式：

**方式一：全局替换 registry（简单粗暴）**

```yaml
# .npmrc
registry=https://npm.cloudsmith.io/mark/code-inspector/
always-auth=true
```

这样配置后，所有包都会先从我的 Cloudsmith 找，找不到才去 npmjs。用户可以直接`pnpm add code-inspector-plugin`，就会安装我的版本。

**方式二：只替换特定 scope（更优雅）**

```yaml
# .npmrc
@code-inspector:registry=https://npm.cloudsmith.io/mark/code-inspector/
```

这种方式下，只有`@code-inspector/`开头的包会从我的仓库拉。但主包`code-inspector-plugin`没有 scope，所以需要手动指定完整 URL：

```bash
pnpm add code-inspector-plugin@https://npm.cloudsmith.io/mark/code-inspector/code-inspector-plugin/-/code-inspector-plugin-1.2.11.tgz
```

我个人更推荐方式二。虽然安装命令长了点，但好处是其他开发者一眼就能看出这是个私有源的包，而且不会影响其他包的安装。

这种感觉，就像你在堵车的高速上发现了一条只有本地人知道的小路。

---

两天两夜的折腾，最终的成果是这样的：

我的魔改版支持一键切换"IDE 打开"和"复制路径"两种模式。你可以根据自己的工作流选择。Cursor 党继续用 IDE 打开，Vibe Coding 党用复制路径，各取所需。

更重要的是，它彻底改变了我的调试体验。让我用一张图来说明区别：

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefinedCC%E4%B8%8A%E4%B8%8B%E6%96%87%E6%9C%BA%E5%88%B6-2025-11-05-140011.png)

看到区别了吗？效率提升不是一点半点，是数量级的差异。

而且你知道最爽的是什么吗？当你的工具足够好，你会开始用不同的方式思考问题。以前遇到复杂的 bug，我会想"算了，描述起来太麻烦，还是自己改吧"。现在？"管它多复杂，反正 3 秒就能告诉 AI 准确位置。"

这种心理负担的消除，让我更愿意把任务交给 AI。这才是真正的价值。

---

如果你也想试试，下面是具体的配置方法。

先说最常用的两个框架：Vite 和 Next.js。

**Vite 配置（最简单）：**

```js
// vite.config.js
import { CodeInspectorPlugin } from 'code-inspector-plugin';

export default {
  plugins: [
    CodeInspectorPlugin({
      bundler: 'vite',
      showSwitch: true,  // 显示切换按钮
      copy: true,        // 默认复制模式
    }),
  ],
};
```

**next.config.ts 配置差异（个人亲测，目前demo里是不足的，后面应该可以再提个 PR）：**

| Next.js 版本 | Webpack                                                                             | Turbopack                                                            |
| ------------ | ----------------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| **<= 15.2**  | 插件配置在 webpack 内，同时启用 next dev （默认 --webpack）                         | 插件配置在 experimental.turbo 内，同时启用 next dev --turbo （强制） |
| **> 15.2**   | 插件配置在 webpack 内，同时设置 turbo 为空字典，同时启用 next dev --webpack（强制） | 插件配置在 turbo 内，同时启用 next dev（默认 --turbo）               |

安装的话，推荐用方式二（指定 scope registry）：

```bash
# 1. 配置.npmrc
echo "@code-inspector:registry=https://npm.cloudsmith.io/mark/code-inspector/" >> .npmrc

# 2. 安装主包（需要完整URL）
pnpm add code-inspector-plugin@https://npm.cloudsmith.io/mark/code-inspector/code-inspector-plugin/-/code-inspector-plugin-1.2.11.tgz

# 分包会自动从cloudsmith拉取，不用操心
```

---

写到这里，我想起一句话：优秀的工程师和普通工程师的区别，不在于谁写代码更快，而在于谁更懂得优化自己的工具链。

两天的魔改时间，换来的是未来无数个 3 秒钟。值吗？太他妈值了。

更重要的是，这个过程让我意识到：我们正处在一个工具大爆炸的时代，但大部分工具还没有为 AI 工作流优化。code-inspector-plugin 原本是为人类设计的，帮开发者快速定位代码。但稍加改造，它就成了 AI 的眼睛，帮 AI 精确理解 UI 与代码的映射。

还有多少这样的工具，等待着被重新发现和改造？

在 AI 时代，最有价值的不是学会使用工具，而是学会改造工具。因为现有的工具，大多是为上个时代设计的。而未来，属于那些能够 bridge 人类世界和 AI 世界的人。

欢迎来到精确上下文工程的新世界。

---

**最后的最后，帮个忙？**

其实我已经给原作者提了PR：[feat: Add Shift+Alt+C mode switching between IDE and copy modes · Pull Request #409](https://github.com/zh-lx/code-inspector/pull/409)

如果你也觉得这个功能有用，不妨去GitHub给这个PR点个👍或者留个评论支持一下。要是原作者看到大家都需要这个功能，说不定就merge了。（同样，也特别感谢原作者的工作，非常有用！）

到时候大家就能直接`pnpm add code-inspector-plugin`用上官方版本，不用折腾什么私有仓库了。我这两天配置Cloudsmith的经历，说实话，能省则省😂（也不知道13天之后降级为免费版会有什么限制，一直都还没看：）

![](https://the-dummy.oss-cn-beijing.aliyuncs.com/undefined20251105222318476.png)


开源的魅力就在于此——我们不是被动的使用者，而是可以一起让工具变得更好的参与者。

---

关注「手工川」，一个用AI改变开发方式的技术博主。最近在研究如何让AI更懂我们的代码，如果你也在探索AI辅助开发的新范式，欢迎一起交流。