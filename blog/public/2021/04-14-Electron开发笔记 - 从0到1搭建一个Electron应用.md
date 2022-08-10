# Electron 开发笔记 - 从 0 到 1 搭建一个 Electron 应用

## 0. 技术选型与项目约定

我们将从一个 html 文件起，逐步添加 react、typescript、webpack、electron、redux、react-redux 等内容。

本项目的前端框架是基于 react 的。

## 1. 配置 html 文件

对任何一个前端应用，html 文件都是必要的，有些框架需要自己定义且允许覆盖（比如 next），有些框架则是内置（creacte-react-app）。

我们先配置一个基本的 html 文件，如下：

```bash
mkdir MyElectron001 && cd MyElectron001
vim index.html
```

在 html 文件中书写的重点是要定以一个 id 元素（本项目中我们约定为`app`），用于前端（本项目中即`react`）生成的`html`内容的替换。

其他基本信息也可以在`head`中填写，后续也可以自动替换，我们暂时先硬写`title`等信息。

```html
<!-- index.html -->
<!DOCTYPE html>
<html>
  <head>
    <title>MyElectron001</title>
  </head>

  <body>
    <div id="app"></div>
  </body>
</html>
```

这个文件理应可以直接打开并在浏览器中展现，只不过还没有什么内容，但是可以看到窗口的标题是我们制定的标题。

## 2. 使用 react 和 react-dom 编写网页内容

我们使用`react`可以组件化的创建网页，所以安装`react`，以及附带的`react-dom`。

其中`react`只包含一个`react`应用的核心部分，包括组件实现、更新调度等。而`react-dom`则是一种针对 DOM 的平台实现，主要用于在`web`端渲染。

```
yarn add react react-dom typescript
mkdir src && cd src
vim index.js
```

```js
// src/index.js

import React from "react"
import ReactDOM from "react-dom"

import App from "./app"

ReactDOM.render(
    <App>,
    document.getElementById("app")
)
```

然后再创建`app.js`文件，因为它们引入了。

```bash
vim app.js
```

## 3. 使用 webpack 进行打包

`react`本身只提供了一种代码书写的范式，它本身并不直接生成相应的前端文件，我们需要用到`webpack`进行打包。

返回根目录后，安装`webpack`相关依赖库，并初始化`webpack`配置文件。

```bash
yarn add -D webpack webpack-cli @webpack-cli/generators
npx webpack-cli init	# 初始化webpack配置文件
```

## 使用 typescript

初始化`tsconfiig.json`配置文件。

```bash
# 自动生成 tsconfig.json
# npm install -g typescript
# tsc -v
tsc --init
```
