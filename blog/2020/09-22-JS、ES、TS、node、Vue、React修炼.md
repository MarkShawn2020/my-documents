# JS、ES、TS、node、Vue、React 修炼

## node 运行 js、es、ts 脚本

### 0. 运行前检查

首先全局安装`es-checker`： `npm i -g es-checker`。

接着运行`es-checker`，可以检查项目内`node`对`es特性`的支持情况。

以我的项目（`mark-nuxt-koa-wechaty`）为例，运行`node -v`得知版本为`v12.18.3`，这已经是很新的`node`了。

但是，运行`es-checker`，会发现并不支持`import, export 和 tail-call`。

```text
……（其他类型的支持情况已省略）

Class
  √ Class
  √ super allowed in object methods
  √ class ABC extends Array { .. }

Module
  × Module export command
  × Module import command


=========================================
Passes 39 feature Detections
Your runtime supports 92% of ECMAScript 6
=========================================

```

因此，对于不同种类、使用了不同语法特性的 js 脚本，运行环境需要作相应地配置。

### 1. 对于纯 ES5 编写的 js 脚本

即 js 脚本中只有`require`之类的常规操作，直接使用`node xx.js`即可。

### 2. 对于使用了`import, export`等 ES6 特性的 js 脚本

解决方案一：使用`node -r esm xx.js`，需要提前`npm i esm`，顾名思义，`esm`就是`es module`的含义。

解决方案二：将`xx.js`改为`xx.mjs`，然后使用`node xx.mjs`。顾名思义，`mjs`就是`module js`的含义。

推荐使用第二种，这样不用修改文件类型。

\*解决方案三：使用`babel-node`，这个以后再研究，参考：https://juejin.im/post/6844903561910812685

### 3. 对于引用了其他本地资源的 js 脚本

例如，在我的项目中，使用了`dotenv`包以读取项目中`.env`文件内的环境变量，在我的 js 脚本中，我有如下的两句：

```js
require('dotenv').config();
const token = process.env.TOKEN;
```

由于，这个`.env`是在项目根目录下，因此，上述直接使用`node xx.js`的方式是不行了。

正确的运行方式，需要在项目根目录运行，即`node xx/xx.js`。

当然了，如果这个脚本本来就和项目根目录平行的话，那么`node xx.js`依旧是可行的。

但最重要的，由于一个标准项目，都需要各种资源的引用，因此单文件运行是不怎么可取的，所以都需要通过`package.json`进行统一配置。

因此，我们在`package.json`中加入`script`即可，例如。

```json
{
  "scripts": {
    "test_xx": "node xx/xx.js"
  }
}
```

### 4. 运行 ts 脚本

主要分为两类，一类是显式地转换成 js 文件再运行，一类是直接运行。

#### \* 方法一：命令行手动 ts 转 js

首先安装`typescript`：`npm i typescript -D`，然后运行转换：`tsc xx.ts`即可。

但我在测试过程中失败了：`tsc koa/bot.ts`

#### 方法二：IDE 中 ts 自动转 js（推荐）

首先全局安装`typescript`：`npm i -g typescript`，然后在 IDE 中配置`typescript`的自动转换，以 WebStorm 为例。

![image-20200918022607550](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/picgo/image-20200918022607550.png)

#### 方法三：使用`ts-node`直接运行 ts（推荐）

安装`ts-node`：`npm i ts-node -D`，然后运行`ts-node xx/xx.ts`即可。

值得注意的是，这种方法，可以兼容运行 js 脚本，即`ts-node xx/xx.js`也是可以没毛病的。

## eslint-prettier 配置

首先参考：https://segmentfault.com/a/1190000014755172

全局安装

```bash
sudo npm -g install eslint eslint-plugin-prettier eslint-config-prettier babel-eslint prettier eslint-plugin-html --save-dev
```

## BUGS

### 【控制变量调试法】xxx is not a constructor + without new

主要由以下几种矛盾。

### import 和 export

首先我有一个`bot.ts`脚本，它的导出方式为`export default Bot`。

我需要在`index.js`中导入`Bot`，采取`import Bot from './bot.ts'`的方式。

事后证明，这引来了很大的麻烦。

第一种变通方式，是改`import`为`require`，具体为`require('./bot.ts').default`。

这能够解决`import`和`export`之间的对应关系。

### es6 和 es5

但还有另外一个问题，因为该`bot.ts`脚本中使用了多个`class`与多个`new`，这导致编译产生问题。

对于这个的解决方式，是新建`tsconfig.json`配置文件，输入以下：

```json
{
  "compilerOptions": {
    "target": "ES6"
  }
}
```

在没有该配置文件的情况下，`ts`默认编译成了`es5`的代码，其中的`call`函数将产生错误。

而基于`es6`的转换，`class`的操作便正常无误。

### ts 和 js

此外，再配置了 es6 的转换后，我转念一想，毕竟都要转换，因此就不显式地导入`ts`了，转而直接导入`js`，代码重新改为`import Bot from './bot'`。

完全可行。

### TS2792：could find module xxx

基于以上三点改进后，脚本可以正常运行，但是 IDE 对于两个`import`语句有红色报警提示，说找不到。

我试过了，如果把编译目标改为`ES5`就没有问题，但是那样脚本就没法运行了。所以索性就不理了。

### 总结

这次的解决方案，总体来说比较满意，但仍不是完美。

我知道这就是 ts 到 js 和 es6 到 es5 的一些编译问题，但确实过于复杂与细节，我在有限的时间内暂时只能想出这样的方案。

具体如下：

1. 按照正常的 ts 书写方式书写 ts 文件
2. 按照正常的导入导出方式书写导入导出（使用 import 和 export 而非 commonJS 的 require，没有必要）
3. 配置`tsconfig.json`的编译目标为`ES6`（或以上）
4. 记得开启 IDE 的自动编译 ts 文件的功能

## 微信与 Wechaty 二维码研究

### 状态 1：wechaty 本地有用户信息且有效

有效是指该用户的本地缓存信息依旧有效，并且未被其他平台挤下线。

此时，wechaty 启动后不会产生二维码，`scan`事件不会被调用。

### 状态 2：wechaty 本地无用户信息或无效

此时，wechaty 启动后会产生`status=2`的二维码，`scan`事件持续监听。

### 状态 3：二维码被扫之后的状态

当一个二维码被扫（即使没有登录）或自然过期之后，其他人扫描该二维码均会显示该二维码无效。

这种情况下，首先考虑服务器用户是否已经在线，如若在线，则不用扫描。

如若不在线，且是本人，则确认服务器是否在运行，是否是最新的二维码，如果均是，则服务器有问题。

如果不是本人，则需要以**以新的用户标识重启服务器**，因为服务器只有一个 token，只可供一位用户使用，相应地，也只能真正产生唯一的一个有效的二维码。

### 对 wechaty 服务器前后端搭建的要求

在仅有一个 token 的情况下，基于以上的分析，我们的服务器至少需要实现以下一些功能。

首先是单用户的基本功能：`onScan | onLogin | onLogout | onMessage`。

这些完整包括了一个用户的所有生命周期。

我们首先要保证服务器后端传送出来的二维码信息与用户状态均是最新的，如若不是，也应该至少提供手动刷新最新状态的方式，比如浏览器内的 api 刷新。

其次考虑多用户共用 1 个 token 的情况。在这种情况下，首先考虑最复杂的一种状态，即服务器正在以 A 用户身份标识在运行，B 用户扫了一个二维码。

显然，B 用户的二维码是无效的，B 需要寻求新的二维码。

因此，对于前端来说，必须保证无论任何人在任何时候访问，都能得知最新的用户状态，主要是有无用户正在使用。

显然，B 用户应当无权停止 A 用户的使用，要想 A 用户下线，必须 A 用户自己主动挤下自己的账号（比较简单）或者提供前端退出自己账号的功能，这样就要涉及到了 cookie 或者 token 等操作。

### wechaty bug

当 wechaty 拿到一个 qrcode 之后，如果 A 用户扫码，但点击了取消，此时 wechaty 虽然捕捉到了扫码、取消的操作，但是它会立即再拿取一个 qrcode，这个时候问题就来了。

A 用户重新再扫之前取消确认的二维码，微信系统显示成功在 iPad 登录，然而 wechaty 服务器内直接就 miss 了这样的一个状态。

作为对比，若 A 用户此时退出该 iPad 登录状态，转而继续扫新的二维码，会发现成功登录之后能够捕捉 wechaty 的消息。

这里的微信设计是**对于一张二维码，即使取消也可以重新扫描，即使已经登录也可以扫描，多次有效**。

基于此 bug，对于前端的设计要求便是，一旦二维码经过扫描，则不应再出现，如果用户点击了取消，则再扫一张即可，如果重新扫描旧的二维码，将导致 wechaty 无法监控到登录状态的 bug 发生。

## 前后端接口设计

可以考虑把主要的接口放在前端，因为 react 内基于 webpack 的文件引用方式不能超出项目范围，但我们的后端基于 node 是可以的。

![image-20200920000052509](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/picgo/image-20200920000052509.png)

## React 开发建议

### 尽量避免组件重复渲染

在绝大多数情况下，基于`react hook`的组件设计，稍有不慎，就能造成巨量甚至死循环的重复渲染。

一种比较好的开发习惯，就是对于每个组件的开头都写一个`render log`，这样可以理清组件与组件之间的渲染传导关系，例如如下。

![image-20200921163126793](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/picgo/image-20200921163126793.png)

尽管这段日志暴露出了十分多的问题，但是渲染的顺序都是很清晰的，并且可以非常方便地知道问题在哪，从来一个个解决问题。

我建议在开发期间持续保留这些组件入口渲染的打印，其他函数之类的可以视情况抉择。
