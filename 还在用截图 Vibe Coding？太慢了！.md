在我们之前整理的教程 [手工川精讲吴恩达Claude Code教程 04. Prompt范式、深度思考、上下文工程与MCP](https://mp.weixin.qq.com/s/8xOjGUkXzCGSOvB74vnd8A) 中，我们给出了将截图作为上下文喂给AI的开发范式。

![之前埋的一个坑，现在开始补坑啦~](https://poketto.oss-cn-hangzhou.aliyuncs.com/51eac2930f3dad7b6dfec46b0711431b.png?x-oss-process=image/quality,q_90/rotate,0)



这种方法，在模型具备视觉理解的基础上，大部分情况下表现良好，比较通用。

但这并非始终有效。

因为UI是代码编译的产物，代码是有序的、结构化的，而UI则是按层绘制的，是更复杂的。

当我们给cc一张图，它往往是个bug界面的显示，然后质问cc如何修复时，cc至少需要做以下分析：
1. 图里的内容是什么，反应了什么问题（包含哪些关键词）
2. 基于业务逻辑与关键词，在代码库里搜索，以确定代码位置
3. 修改目标代码，以修复bug

然而，第1、2步的耗时可能会相当长（分钟级别），或者质量低下（找的位置不对），我们事实上有更好的手段。

那就是我们今天想给大家介绍的 `code-inspector-plugin`，这是一款支持定位UI源代码所在位置的插件。

参考 [zh-lx/code-inspector: 🚀 Click the dom to open your IDE and position the cursor at dom's source code location! 点击页面 dom 来打开 IDE 并将光标自动定位到源代码位置!](https://github.com/zh-lx/code-inspector) 你可以 `npm i code-inspector-plugin -D` 安装在你的前端项目内，它几乎支持所有主流前端框架：

✅ vue2 / vue3 / nuxt  
✅ react / nextjs / umijs  
✅ preact  
✅ solid  
✅ qwik  
✅ svelte  
✅ astro

以目前最火的 react-vite 项目为例，你只需要修改对应的配置文件：

```shell
npm i code-inspector-plugin -D
# or
yarn add code-inspector-plugin -D
# or
pnpm add code-inspector-plugin -D
```


```js
// vite.config.js
import { defineConfig } from 'vite';
import { codeInspectorPlugin } from 'code-inspector-plugin';

export default defineConfig({
  plugins: [
    codeInspectorPlugin({
      bundler: 'vite',
    }),
  ],
});
```

接着你就能实现官网的效果，按住 `opt+shift`后，悬浮在前端界面上就可以弹出点击跳转打开对应源代码的功能：

![code-inspector](https://cdn.jsdelivr.net/gh/zh-lx/static-img/code-inspector/demo.gif)

它的逻辑也很直接，就是在生成的网页代码里加上源代码的位置映射：

![每个结点都会加上 data-insp-path 字段](https://poketto.oss-cn-hangzhou.aliyuncs.com/470b9da28e04b4a4daccdadf315a8793.png?x-oss-process=image/quality,q_90/rotate,0)

然后按住 `opt+shift` 键后就进入元素选取状态。

点击后就会使用默认编辑器（比如vscode）打开目标文件，并自动定位到对应的行列位置。

---

### Claude Code 适配

以上，一切都非常棒。

但考虑到大家现在vibe coding，很多甚至都不用编辑器，而是在聊天窗里直接 `@`，因此，我们需要升级一下本项目。

我们模仿 [React Developer Tools](https://react.dev/learn/react-developer-tools) 也做了一个悬浮球，点击它时支持在 `在IDE中打开（用于 Cursor等用户） | 复制路径（用于 Claude Code 等用户）` 两种模式间切换。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/630ff339b4e6ffa9f28d3da6510cbb44.png?x-oss-process=image/quality,q_90/rotate,0)

安装办法基本对齐原仓库，只不过略做了修改，具体参考 [MarkShawn2020/code-inspector: Enhanced Developer Tool with Copy-to-Clipboard & Modern UI](https://github.com/MarkShawn2020/code-inspector)。

```shell
# npm
npm i @neurora/code-inspector -D

# yarn  
yarn add @neurora/code-inspector -D

# pnpm
pnpm add @neurora/code-inspector -D
```


```js
// vite.config.js
import { defineConfig } from 'vite';
import { CodeInspectorPlugin } from '@neurora/code-inspector';

export default defineConfig({
  plugins: [
    CodeInspectorPlugin({
      bundler: 'vite',
      // Enable copy mode by default
      showSwitch: true,
      copy: true,
    }),
  ],
});
```





---

### Attention

不过，注意这个插件适合前端，而且前端要基于打包器，如果你是一个纯html项目，那就无法使用~

---
### Acknowledge

希望大家用的开心，也感谢原作者的贡献，确实有提高生产力。

btw，我是在 [Dify](https://dify.ai/) 源代码里发现这个精致的小玩意儿的~


