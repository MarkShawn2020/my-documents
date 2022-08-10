---
title: VuePress你好，VuePres再见
slug: VuePress-Journal
tags:
  - Vuepress
category: Vuepress
cover: ''
position: 799
version: 0.1.0
fullScreen: false
---

## VuePress01 - 运行原理研究

### 服务端视角

#### 启动

启动时首先使用`npm run docs:dev`命令，即调用的`packages.json`文件中的`vuepress dev docs`命令。

![image-20200812195621125](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812195621125.png)

`vuepress`指向`@vuepress/core`。

![image-20200812200434428](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812200434428.png)

创建了一个`.node/App`程序（即服务端），并且启动了`createApp(options)`,`app.process`、`app.dev()`等几个命令。

由于我们直接使用`vuepress run dev`启动的，所以`options`为空。

![image-20200812203534119](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812203534119.png)

#### App.js

`App.js`文件中就是一个 App 类，导入了很多依赖，比如生成`Markdown`的，生成`Page`组件的，以及与`dev`、`build`相关的进程函数。

仔细看之前的`CreateApp(options)`函数，其实就是`App(options)`函数，经过该函数进行初始化。

![image-20200812204059251](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812204059251.png)

`app.process()`函数中用了异步函数，主要用于解析页面之类。

![image-20200812204540636](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812204540636.png)

#### DevProcess

`dev`函数中主要是使用`DevProcess`进行，并且会监听本地文件的变动，这里的本地文件是被程序特定的一些文件，主要是`markdown`、`vue`之类的。

与之对比，可以看一下生产环境的启动函数。

![image-20200812204720553](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812204720553.png)

可以看到，要简洁地多，主要是就是运行，然后渲染。

![image-20200812204855624](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812205235678.png)

再看一下这个`DevProcess`函数。

![image-20200812205235678](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812205344580.png)

使用了`events`包进行事件驱动，而且所有的`webpack`打包都是在这里进行的，详见如下：

![image-20200812205344580](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812204855624.png)

#### 文件监控

接下来看它的监控范围，首先是对`.js`、`.md`和`.vue`的监控。

![image-20200812210030040](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812210030040.png)

可以看到`.md`是根目录下全局监控，而`.vue`只限于在`.vuepress/components`下定义的。

:::tip 暂时还不清楚各类监控的设定缘由与效果差异 :::

其次是对`.vuepress`文件夹下的`config`文件进行监控，支持`.js`、`.yml`和`.toml`三种格式，是写死的，所以`.yaml`、`.json`这两种格式是不被监控的，这里写的有点死了，用正则会更好一些，不过如果想监控自己的其他文件可以配置`siteConfig.extraWatchFiles`字段，参见：[配置 | VuePress（#extraWatchFiles）](https://vuepress.vuejs.org/zh/config/#extrawatchfiles)

1. 我的项目配置的就是`.yaml`格式，在了解到`.yaml`配置文件不在监控列表内后，我改成了`.yml`结尾，结果发现`js-yaml`不能完整解析`.yml`格式。

2. 基于此，我去修改了`vuepress`的源码，以使它支持`config.yaml`的监控。

3. 但最后我发现了`siteConfig.extraWatchFiles`这个配置，所以我最后采用了这个，基于此，我现在的`config.js`里就多了如下的监控文件：

![image-20200813031450552](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200813031450552.png)

此外，还对 frontmatter 进行监控，如下：

![image-20200812210245060](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812210245060.png)

#### 打包与服务器

接着就是使用`webpack`进行一些资源的打包与解析，比如`html`。

![image-20200812210428181](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812210428181.png)

接着是使用`express`创建服务器。

![image-20200812210723659](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812210723659.png)

可以看到，公共资源都在`./public`下，而以`/`结尾的如果匹配不到文件，则会自动寻找`index.html`文件，我之前在配置`sidebarRecursive`的时候，就经常出现`index.html`匹配不上的报错，我后来的做法是给每个有路由的文件夹都配一个`index.md`文件占位，并且在解析`sidebarRecursive children`的时候排除这个`.md`文件（也可以不排除，就是像官方一样留空就可以，但这样会使该文件夹下的其他文件与它同层级，这不是我想要的）。

最后是一些`host`和 `port`等的配置。

![image-20200812211219741](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200812211219741.png)

至此，服务器就创建成功了，打开浏览器地址可以看到所渲染出来的默认页面。

那从客户端视角来看，这一切又是如何呈现的呢？

### 客户端视角

#### 组件依赖图

首先，我们分析一下默认的主题，它位于`node_modules/@vuepress/theme-default`。

首先使用`webstorm`生成一下组件的依赖图。

![image-20200813023649261](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200813023649261.png)

可以看到，所有的一级组件都经由`util/index.tsx`展开，二级组件再被一级组件所单独或共享使用。不过`util/index.tsx`中只是定义了各个解耦的被调用函数，直接看并没有什么欧诺个，所以我们还是先从`layouts/Layout.vue`看起。

#### Layout

可以看到，组件如官网所述，主要分`components`、`global components`、`layouts`三大块，其中`layouts/Layout.vue`是默认入口。

这个组件在哪定义为入口的，我还没找到，所以先看组件吧。

![image-20200813021205905](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200813021205905.png)

在这个`Layout.vue`中，主要由以下组件构成

```bash
.theme-container
	- Navbar
	- Sidebar
		- .sidebarRecursive-mask
		- v-slot:sidebarRecursive-top
		- v-slot:sidebarRecursive-bottom
	- <View>
		- Home
		- Page
			- v-slot:page-top
			- v-slot:page-bottom
```

其中最关键的就是`Home`与`Page`的分支判断，这其实就是对应两种`View`，而依据就是`frontmatter`中`home`字段是否为真。

了解到这点之后就很清楚了，如果我们想多设几种`View`，只要再这里修改`if...else...`的逻辑就可以了。

:::tip 在 VuePress 官网里并没有`View`的概念，这个概念来自于其他一些框架，比如`Nuxt`、`Gatsby`之类，我引入到这里，是因为 VuePress 默认的主题将组件按照作用域划分分组，对实际开发来说体验不是很好。我的想法是，`Nav`、`Sidebar`、`Footer`之类都可以作为通用组件，而内容主区域可以有多个呈现，比如展示`Home`、`Page`，以及`PageList`等等其它种可能。

基于此，我尝试将`Home`和`Page`分离出来独立到`View`文件夹内，这样直接`dev`模式运行是没有问题的。但是！打包发布却出现了严重的问题！

所以，还是乖乖地放在`components`里面吧。。。

最后，关于父（`@parenttheme`）子（`@theme`）主题的引用，请参考：[主题的继承 | VuePress](https://vuepress.vuejs.org/zh/theme/inheritance.html#%E7%BB%84%E4%BB%B6%E7%9A%84%E8%A6%86%E7%9B%96) :::

## VuePress02 - 使用体验分析

### 设计相关

#### 覆写设定不合理

以页面导航为例，在组件中判断一个页面的上一页或者下一页是什么，需要通过多个层级的多次判断，比如先判断主题有没有上下页，再判断页面是否有上下页，判断的位置隐含在`links`里或者`frontmatter`中。

作为`vuepress`的使用者，我经常需要在`console`中打印出当前页面的变量，以判断什么变量出于什么作用域范围内，我想说，这不是必要的。如果作者采用更加友好的设计方式，在后端与中端过程中将组件完全覆写，可以大大减少前端的逻辑判断。

也许这会束缚前端`vue`组件开发的灵活度，但框架毕竟是框架，使用`vuepress`的开发者应有能力在程序的配置阶段把一切设定好（如果框架机制允许的话）。也许我更崇尚配置式的框架吧，例如爬虫领域的`python`框架`scrapy`。

![image-20200815012805614](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/20200815012805.png)

### 配置相关

#### 多语言配置（这是真坑）

![image-20200814002121393](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/image-20200814002121393.png)

#### 使用自己的主题

在没有别人主题或者自己暂时没有经验的情况下，可以先把`vuepress`默认的主题拷贝出来，路径是在`node_modules/@vuepress/theme-default`，在配置的时候有几点一定要注意（至少是对于新手来说）。

1. 将主题文件夹放在`docs/.vuepress`下，一定一定！不然`dev`可以运行，`build`一定会出错！
2. 修改`index.tsx`里的内容：

```js
module.exports = {
  extend: '@vuepress/theme-default',
};
```

3. 按照官网要求，重命名为`vuepress-theme-YOUR-THEME-NAME`
4. 修改`.vuepress/config.js`里的内容：

```js
module.exports = {
  theme:  require.resolve('./vuepress-theme-YOUR-THEME-NAME'),
  ...
}
```

#### config.yaml 或 config.yml

经过测试，`js-yaml`对`.yml`解析的支持有限，因此推荐使用`.yaml`。

如需使用，请在`config.js`的`extraWatchedFiles`字段中加入相应的监控文件路径。

### 运行相关

#### navbar 的下划线

在`element-ui`中，只要成功点击了某导航项的切页，无论是单链接是子链接，下划线都会更新到那一项上。

但我发现`vuepress`里没有实现，需要解决一下。

例如当我点击了我的`博客`下拉菜单中某一项后，页面成功跳转，但下划线没了。

![image-20200813032635390](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/20200815012640.png)

与之对比的是，如果是在首页，则会有。

![image-20200813032701945](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/20200815012641.png)

#### sidebar 的热更新

在我更新我的本地文档时，已经启动的`vuepress`可以在两秒内监测到内容的变化，并相应地更新前端的呈现，但是对应的`siderbar`则不会自动更新。

按道理，`toc`是从文档内容中提取出的，`sidebarRecursive`基于`toc`呈现，理应做到同步更新，这是值得优化的一个点。

#### frontmatter 格式问题

![image-20200816121349543](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816121349543.png)

### 插件相关

#### [@vuepress/plugin-nprogress](https://vuepress.vuejs.org/zh/plugin/official/plugin-nprogress.html)

这个插件是用来显示页面跳转的时候顶部加载的进度条，如下所示。

![image-20200815193651544](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200815193651544.png)

当网站刚启动的时候，或者网速很慢的时候，这个进度条就会比较明显。

不过，由于网站以静态内容为主，正常情况下，这个条只会一闪而过。

### 永久链接

官网对于永久链接的设定不甚详细。

如下，我也搞不清这个文章发布是怎么算的。

![image-20200816093945554](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816093945554.png)

翻了一下源代码，在`node_modules/@vuepress/shared-utils/lib/getPermalink.js`里有如下，生成链接的函数接收五个参数，其中第三个参数就是时间，这些模板变量都是从这个时间中解析出来的。

![image-20200816094124718](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816094124718.png)

接着定位到了`node_modules/@vuepress/core/lib/node/Page.js`

![image-20200816094645568](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816094645568.png)

而这个`this.date`呢，是根据这个函数生成的。

![image-20200816094813159](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816094813159.png)

最后到了`node_modules/@vuepress/core/lib/node/util/index.tsx`

![image-20200816094959257](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816094959257.png)

注意这个`DATE_RE`，我拷贝出来一下：` /(\d{4}-\d{1,2}(-\d{1,2})?)-(.*)/`，所以这个程序的意思就是，依次从 frontmatter.date、文件名和文件夹名中提取`YYYY-M?M-D?D-FILENAME`的格式，一旦提取到，就会生成它的永久链接。

尴尬了，我原先素材的取名都是`YYMMDD`的，例如：

![image-20200816095412067](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816095412067.png)

于是，写了个脚本，重命名了一下。

![image-20200816100625252](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816100625252.png)

接下来就是永久链接的路由配置，由于我们的 nav 和 sidebar 是自己自己写的，所以需要自己对应上。

按照规则，现在的文章路径，以`2020-05-26-杨季.md`为例，变成了`/2020/05/26/杨季`。

但专辑名也要相应地换一下，目前文件夹名是`A01-考研专辑`，对应的`index.md`，专辑名显然不能换，但我们也想用一个好记的路径，因此直接在`index.md`里设置 frontmatter，这里就不要用`date`变量了，而是直接`permalink`，如下。

![image-20200816101325695](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816101325695.png)

但这样做有个弊端，我们在生成`menus`和`sidebar`时需要先解析文件内容，与我一开始简单地通过文件路径生成网络路由的初衷不符，虽然`vuepress`本身便是基于此的。

:::tip 如上标准化文件名后，还要在`config.js`中，配置永久路径的模板变量。

![image-20200816102550549](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816102550549.png)

这样才能被`vuepress`解析。 :::

### 路由的中文转义

程序内部对每个路由会有三种形式：`relativePath | regularPath | path`，其中`relativePath`是本地文件路径，`regularPath`是转义后的路径，而`path`顾名思义应该是最终的路径。

此外，还有一个`permanlink`，是用户指定的文件的最终访问路径。

在我们的程序中，直接按照文件路径配置 nav 和 sidebar 是比较符合 common sense 的，操作起来也是比较容易，只要用`fs`遍历或者递归即可。**这样的操作，它本身不应该有问题，如果有问题，那一定是框架的问题**。

#### 未配置 permalink 的结果

:white_check_mark: vuepress 生成了`.html`结尾的目标节点，该路径的中文形式就是本地文件路径，具体网络路径为`/zh/S01-%E6%96%87%E9%9B%86/G01-%E7%A0%94%E7%A9%B6%E7%94%9F%E5%8D%87%E5%AD%A6%E6%A1%88%E4%BE%8B/A02-%E7%95%99%E5%AD%A6%E4%B8%93%E8%BE%91/2020-06-12-%E7%8E%8B%E9%80%B8%E6%88%90.html`![image-20200816150514054](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816150514054.png)

:white_check_mark: 当直接访问上条`.html`结尾的路径时，会跳转到没有`index.html`结尾的路径，对应的就是本地文件路径。

![image-20200816150727187](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816150727187.png)

:white_check_mark: 最后，若直接访问中文路径，或者访问该转义路径，是等价的。

![image-20200816150829410](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816150829410.png)

#### 配置了 permalink 的结果

:white_check_mark: 此时，如果直接访问`/考研专辑/`或者`/%E8%80%83%E7%A0%94%E4%B8%93%E8%BE%91/`是可以成功跳转的。

![image-20200816144956705](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816144956705.png)

:x: 然而虽然下面的路径`/%E8%80%83%E7%A0%94%E4%B8%93%E8%BE%91/index.html`，根据路由显示也是跳转上面的路径，但是事实上，当我们输入网址后，会被浏览器解析成`/考研专辑/index.html`，从而失配。

![image-20200816145024359](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816145024359.png)

:x: 紧接着，即我们程序中设定的本地文件路径映射，虽然也显示跳转，但会直接转义，导致跳转失败。

![image-20200816145042228](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816145042228.png)

值得注意的是，如果文件路径都是英文，配置了`permalink`之后，路径的跳转都没问题。

有问题的点在于，当使用转义后的本地文件路径去访问时，浏览器指向了转义前的路径（即中文），而该路径是没有跳转项的，导致跳转失败。

所以，问题的解决就在于，**能否配置一个转义前（中文）的本地文件路径，使之跳转到最终的 permalink**。

或者，**不要转义本地文件路径**。

#### 修改源代码

如下，对`node_modules/@vuepress/core/lib/node/internal-plugins/routes.js`转义后的路径重新解码，保证原文件路径对最终路径的映射，即可成功解决中文路径跳转问题。

![image-20200816155711710](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200816155711710.png)

### 总结、担忧与考虑

其实标准化 url 也是很好的一种设计，能让程序更加地稳健，但却出现了我遇到的 permalink 强行跳转导致转义失配的结果。我解决的方法是对标准化之前的文件路径建立映射。

在我的项目中，目前还不存在由于 url 编码而产生歧义的可能，其他项目可能要自行把握。也希望看到更优秀的解决方案！

## VuePres03 - 我为什么放弃了 VuePress

### 选择 vuepress 的理由

### 放弃 vuepress 的理由

### 展望

### 回顾

弃更，落差太大了。
