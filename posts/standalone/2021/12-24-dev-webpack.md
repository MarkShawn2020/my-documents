---
tags: [开发笔记, Webpack, 前端]
---

# 编程 | 记与 Webpack 十二小时的奋战

2021 年 12 月 24 日

## Content

这篇必须用中文记录，而且直到目前还没有完全解决，只实现了一个还可以接受的替代方案，背后还有一些东西没弄明白。

先直接说结论：

1. 如果所有的依赖包都是`commonjs`形式（使用`require`和`module.export`），子包的`package.json`中没有定义`type: "module"`，则 webpack 无论怎么写，基本都不会出错，直接运行`webpack --config xxx.webpack.config.js`即可
2. 如果`xxx.config.js`文件中使用了`import xxx from xx`或者子包都是用的`type: "module"`，则在项目的`package.json`中定义一些`type: "module"`，也可以解决问题
3. 如果出现了`commonjs`和`esm`混用的情况，则会报错，要么导致`Cannot use import statement outside a module`，要么导致`mjs`等等无法导入因为有`type: module`之类的问题，下面着重说一下在该种情况下的解决方案

我碰到的问题就是，我直接 clone 的 github 上的两个 boilerplate，一个是`electron-react-typescript-webpack-boilerplate`，还有一个是[electron-typescript-react](https://github.com/diego3g/electron-typescript-react#:~:text=electron-typescript-react)，这两个 boilerplate 虽然配置有些差异，而且一个用到了`babel`一个没用，但是共同点就是`webpack.config.js`中都没有使用`import`语法，`webpack`的所有依赖也都是`commonjs`。

而我为了将`markdown`文件在前端渲染出来，虽然我可以直接使用`marked`或者`react-markdown`这类 package，但是基于以前`nextjs | gatsby`等框架的经验，直接基于`webpack`进行`markdown`解析体验会比较好（毕竟两个项目都用上`webpack`了）。

但是问题来了，我在`webpack`官网中找到加载`markdown`相关的`loaders`的 [remark-loader | webpack](https://webpack.js.org/loaders/remark-loader/#inspiration) 章节时，实际使用发现`remark-html`是`esm`，没法直接用，我的`webpack`会报错。

接着我就经历了 12 个小时的奋斗，尝试了几乎所有能找到的方案，从最基础的改`type: "module"`，到用上`babel-register`，甚至详细去读了`webpack`、`babel`的相关内容，最后不得不都以失败告终。其中应该说最有影响力、提供解决方案最多（然而最终都失败）的帖子应该是下面这个：

- [How can I use ES6 in webpack.config.js? - Stack Overflow](https://stackoverflow.com/questions/31903692/how-can-i-use-es6-in-webpack-config-js)

问题说的很清楚，就是要在`webpack.config.js`中使用`ES6`。

但答案都不 OK，最终，我在万念俱灰无数次之后，偶然在 [Bug at render-markdown stage of tutorial: Must use import to load ES Module · Discussion #27758 · vercel/next.js](https://github.com/vercel/next.js/discussions/27758) 这个帖子里找到了一句话：`npm install remark@13 remark-html@13`，凭着经验，我一下就知道是怎么回事了，因为前两天我刚刚与万恶的`webstorm`不支持`tailwindcss`最新版最终不得不安装`tailwindcss@2.0.1-compat`做了同样艰苦的斗争！

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640346360145-webpack-bugfix-349711dd9f694e145b5dc4a1ddae42e2955043d9a23747857b50d1423368dd9f.png" width="480" />

果然，安装指定的版本后，项目终于成功运行：

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640346477725-webpack-bugfix-7d4cd572dc5ec9fe5ad511c4156c56e047cbe30184b88b8c95601c1d21b1b02e.png" width="480" />

至此，所有与`webpack`的斗争，应该说告一段落了，不然，我下一个更艰苦卓绝的打算，可能就是去看`nextjs`之类重型框架的源码，剖析它们是怎么高大上地使用`webpack`了。。

所以，目前，我可以确定的就是，只要保证所有`webpack`依赖的库都是`commonjs`，就可以不借助`babel`使项目运行，毕竟当一个前端项目需要用上`babel`的时候，它肯定就已经是另一个项目了，于是，一键 DELETE 恢复世界清净。

<img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640347058731-webpack-bugfix-901426db9195c9d0a7ec92ef0370f3a94d57f35b9b78808b330f4929e3341574.png" width="480" />

不过事实上，就像我开头说的，我 clone 了两个项目，其中一个用了 babel，用于转换`jsx`之类的文件的，它是基于`electron-forge`的，为了弄清楚当时的报错我还特意去看了这个库，说实话也没怎么弄明白。它的这个`boilerplate`对我最大的启发，应该是写了一个标准的`main`和`renderer`之间通信的接口，即：

1. main 中暴露 api 给 renderer 使用的接口定义

```ts
// src/@types/bridge.d.ts
import {api} from 'electron/bridge';

declare global {
  // eslint-disable-next-line
  interface Window {
    Main: typeof api;
  }
}
```

1. main 中对 api 使用的收发封装

```ts
// electron/bridge.ts
import {contextBridge, ipcRenderer} from 'electron';

export const api = {
  /**
   * Here you can expose functions to the renderer process
   * so they can interact with the main (electron) side
   * without security problems.
   *
   * The function below can accessed using `window.Main.sendMessage`
   */

  sendMessage: (message: string) => {
    ipcRenderer.send('message', message);
  },

  /**
   * Provide an easier way to listen to events
   */
  on: (channel: string, callback: Function) => {
    ipcRenderer.on(channel, (_, data) => callback(data));
  },
};

contextBridge.exposeInMainWorld('Main', api);
```

这两个文件，包括 main 和 render 程序中如何使用这两个文件的写法对我还是有很好的指导作用的，至少 electron 官网上对 typescript 的范式介绍比较少，这就需要从这些 boilerplate 中寻找指点。

但除此之外，这个 boilerplate 对我的意义就不大了，而且，我也不怎么看得懂它给定的几个`scripts`，其实无法就是开发版、生产版、运行、打包与测试的不同命令，但是被他搞的有点负责，相比较之下，另一个 boilerplate 就很好，清晰明白，也有可能上半年我在学习 electron 的时候正好用的就是第二个 boilerplate，但无论怎样，确实第二个更好。

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640347712904-webpack-bugfix-5b369e0dff7ff239ccac2debcdc0a1dbf626a177b96e8f07b9fb9cf1e9ef977c.png" width="480" />

---

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640347790778-webpack-bugfix-dec8b0f034c1fea196744e1f5f4d8772efad854d0a2d28d7858995617024a57e.png" width="480" />

但为了确信这一点（2 比 1 好），我又重新去确认了一下 github 的 star 数，结果，并不是这样的，第一个 boilerplate 的 star 有 1.2k，而第二个只有 176，好家伙……我的直觉真不靠谱。

不过这也解释地通，因为第一个是叫`electron-typescript-react`，第二个叫`electron-react-typescript-webpack-boilerplate`，表面上后者是前者的具化，因为名词更多。

但事实上，恰恰相反，在`electron-typescript-react`中反而既有`webpack`也有`babel`，其实比另一个涉及的东西还有多……从这个角度想，第一个 boilerplate 星多，应该至少归结于三个点：

1. 名字短
2. 加了`babel`，让使用者有了更多发挥的空间
3. `bridge`的接口写的棒，对使用者有更大的价值
4. ...

Anyway，这大概就是关于目前这个问题的所有思考，和两个 boilerplate 带给我的启发。

接下来，才是工作的重头戏，那就是手上工具顺了，就要立即投身到业务实现上了。

但仍然，我开头说的还有一些问题是没有解决的，罗列如下：

1. 为什么`webpack`官网的所有`loader`的配置都是`import`导入的，难道他们所有的 dependencies 都是 esm 吗？
2. 有可能不是，因为我还看到他们的有些 loader 可以使用`type: "auto"`这种配置，应该就是自动对多种 type 的 js 采取不同的策略智能打包的意思，但这个可以作用于`config.js`的抬头吗？好像不可以吧，因为我看他们是用在`rules`里的。
3. 肯定存在很多`commonjs`和`esm`混用的项目的，如果不引入`babel`，`webpack`是否可以有策略正常运行呢？目前，他们都是基于`babel`的吗？
4. 如果是基于`babel`，我认为我之前尝试装那么多`babel`依赖，应该也可以正常运行啊，为什么就不能奏效呢？

关于第三点，我突然想到我上半年也写过脚本，翻出来看了一下： <img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640348790672-webpack-bugfix-66129064c7e8a8c55c2161aad0bcce67f18e484b1cf913921f14bd01688a3542.png" width="480" />

可以看到，确实是要用`babel_register`进行子程序注册的，并且我也确实是用`import`进行导包的： <img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640348883256-webpack-bugfix-a0039a63671200450ee7bc85582444eecf757b3c9393f8bd3443e2b72b79dedd.png" width="480" />

人老了啊，记性不行了，当时应该研究这些东西也花了一星期的，结果都一点印象没了，幸好好记性不如烂笔头，整理了当时的代码库。再回想开头看的那个关于`babel_register`的解决方案，内心突然就有些豁然开朗了： <img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640349025625-webpack-bugfix-045d3c71ca84950c4a03136ad85db57f3652e3aa1f0600b59ebcdfd8eaf8c66f.png" width="480" />

不过呢，至少这个项目，我应该暂时不需要了 hhh，如果需要，到时候`yarn add`一顿乱装，加个`babel-register`脚本，改一下启动命令行，应该就行了，hhh，肯定不会像今天这样头疼了。

那就暂时先这样，对该问题的记录到此为止。

## Former Record

> ### [Problem] SyntaxError: Cannot use import statement outside a module
>
> This discussion is very close to what I happened to, however they gave no solution, except pointed out that there may be some package using `es` which seems **not proper for webpack**, and inspired me to have a check at [the target package](#the-target-package-of-remark-html-i-wanted-to-import) I wanted to import as official webpack suggested me to.
>
> - [javascript - Why does Error 'SyntaxError: Cannot use import statement outside a module ' when I try to use ES Modules? - Stack Overflow](https://stackoverflow.com/questions/70114861/why-does-error-syntaxerror-cannot-use-import-statement-outside-a-module-when)
>
> ### The target package of `remark-html` I wanted to import
>
> - [remark-loader | webpack](https://webpack.js.org/loaders/remark-loader/#root)
>
> ### [Failed] Solution of `babel-node`
>
> It seems that `babel-node` is a possible solution to this problem, since it when I installed it, it automatically detected what's going wrong of all my webpack loaders.
>
> <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640327908025-webpack-bugfix-51cf4a831368a2ef7d3cf8957e88c6c5f9528ec63aa21ab93ff4602781cdc6cd.png" width="480" />
>
> ### [Failed] Solution of `@babel/register`
>
> - [How can I use ES6 in webpack.config.js? - Stack Overflow](https://stackoverflow.com/questions/31903692/how-can-i-use-es6-in-webpack-config-js)

## 真正唯一的收获

前段时间有个字节的小姐姐，和我表述想转码的意愿，聊下来觉得前端对她可以一试，毕竟目前各种开发岗位里前端是相对来说最容易上手的了……

但是！

这说的只是十二十年前纯粹用`html + css + jquery` 或者 `php`的时代！

现在，前端技术突飞猛进，各种范式层出不穷，变得越来越复杂了，三大框架`AngularJS | React | Vue`就不说了，`webpack`和`babel`绝对能让大厂的前端开发掉一层皮……

但 anyway，如果不论这些，平时写写前端真地能让人心情大好，获得感十足，用一位朋友对开发的态度来说：“平时自己写些玩玩挺好的，当做工作就太无聊了”，确实如是~

保持学习，保持热爱！ <img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640349694440-webpack-bugfix-7adf1882ddf381568cee583516f84f77d56237f255c73a5bcceb153755794696.png" width="480" />

reference:

- [How to transpile ES modules with webpack and Node.js - LogRocket Blog](https://blog.logrocket.com/transpile-es-modules-with-webpack-node-js/)

- [How can I use ES6 in webpack.config.js? - Stack Overflow](https://stackoverflow.com/questions/31903692/how-can-i-use-es6-in-webpack-config-js)

- [diego3g/electron-typescript-react: An Electron boilerplate including TypeScript, React, Jest and ESLint.](https://github.com/diego3g/electron-typescript-react)

- [Devtography/electron-react-typescript-webpack-boilerplate: Pre-configured boilerplate for Electron + React + TypeScript + Webpack](https://github.com/Devtography/electron-react-typescript-webpack-boilerplate)

- [remark-loader | webpack](https://webpack.js.org/loaders/remark-loader/#inspiration)

- [Bug at render-markdown stage of tutorial: Must use import to load ES Module · Discussion #27758 · vercel/next.js](https://github.com/vercel/next.js/discussions/27758)

- [TypeScript + Webpack - Electron Forge](https://www.electronforge.io/templates/typescript-+-webpack-template)

- [ipcMain | Electron](https://www.electronjs.org/zh/docs/latest/api/ipc-main)
