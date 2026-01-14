---
title: BUG FIX
slug: bug_fix
menuTitle: BUG FIX
category: 网站开发
position: 3
fullScreen: false
---

<a id="【已解决】关于cookie-universal-nuxt无法移除cookie的问题"></a>

## 【已解决】关于`cookie-universal-nuxt`无法移除`cookie`的问题

2020-08-31 17:17:48 <a id="原因分析"></a>

### 原因分析

大多数情况下，这是由于`path`不同导致的。

当调用`this.$cookies.set()`进行`cookie`设定，但未提供`path`参数时，将默认存储在当前所在路由下。

之后，若再次调用`remove()`函数，且未提供`path`参数，将默认移除首页`/`下的参数。

此时，问题就发生了。

<a id="解决方案"></a>

### 解决方案

对于一些通用数据，比如`user`，建议存储时显式存储在`/`路径下，以免不必要的麻烦。

此外，`cookie-universal`里设定的`removeAll()`函数，默认只能清空`/`下的参数。

详情见`cookie-universal`的使用说明：

```js [node_modules/cookie-universal/README.md]
// note that removeAll does not currently allow you
// to remove cookies that have a
// path different from '/'
```

<a id="【部分解决】关于markdown的heading导航异常的问题"></a>

## 【部分解决】关于`markdown`的`heading`导航异常的问题

<a id="原因分析-1"></a>

### 原因分析

很有可能是因为在`content`中对`markdown`解析时，经过`remark-parse`后，`markdown`内的`heading`出现了`tabindex=-1`。

于是，我特地去看了一下`github`的`readme`内的`heading`导航。发现它是没有`tabindex=-1`且可以正常导航的。

我又测试了一下，在该`heading`上添加`tabindex=-1`，发现依旧可以正常导航。再联想之前在自己的网站上测试去除`tabindex=-1`依旧不能正常导航，基本确定不是`tabindex=-1`的问题。

<a id="测试过程"></a>

### 测试过程

|  |  |  |
| --- | --- | --- |
| 直接复制粘贴导航栏中有用的`a`代码 | 可以正常跳转 |  |
| 只保留`a`标签的`href`属性（且是转以后的） | 可以正常跳转（谷歌浏览不可以） |  |
| 只替换`a`标签的`href`属性（其他的`arai-hidden`等属性保持不变） | 仅第一次点击可正常跳转，之后的点击异常；<br />经过`F12`重启，确认`href`属性依旧是转义后的 |  |
| 只去除`a`标签的`data-v`属性 | 无效 |  |
| 删除`a`标签的所有其他属性 | 无效 |  |
| 删除`a`标签内部的子节点 | 无效 |  |
| 只保留`a`标签的`href`属性（未转义） | 无效 |  |
|  |  |  |

测试结果：可能是`heading`的点击穿透问题。

<a id="解决方案-1"></a>

### 解决方案

考虑到只有页面的侧边栏（TOC）有导航意义，因此直接禁用`heading`链接的点击即可。

经过一番搜索，只需要加上`cursor-point: none`的样式即可，在`tailwindcss`中为`cursor-point-none`。

但这样，就无法直接在页面内导航了。

<a id="总结展望"></a>

### 总结展望

也许有其他的解决方案，但我还没找到。

目前，是不支持页内`heading`导航了。

<a id="【已解决】关于tailwindcss中ul没有样式的问题"></a>

## 【已解决】关于`tailwindcss`中`ul`没有样式的问题

<a id="原因"></a>

### 原因

是因为`tawiwindcss`定义了一个`base.css`，这里面对一些`html`的基本样式做了修改。

```css [node_modules/tailwindcss/dist/base.css]
ol,
ul {
  list-style: none;
  margin: 0;
  padding: 0;
}
```

在此基础上，我们可以覆写这些`css`样式，有基于`css`和基于`plugin`等多种方式，具体可以见：[Adding Base Styles - Tailwind CSS](https://tailwindcss.com/docs/adding-base-styles)。

<a id="【已解决】关于element-ui按需入的问题（重要）"></a>

## 【已解决】关于`Element-UI`按需入的问题（重要）

<a id="现场"></a>

### 现场

按照`element-ui`官方文档，我在`.babelrc`文件中配置了对`element-ui`的按需引入，如下。

```js {3-11}[.babelrc]
{
  "presets": [["es2015", { "modules": false }]],
  "plugins": [
    [
      "component",
      {
        "libraryName": "element-ui",
        "styleLibraryName": "theme-chalk"
      }
    ]
  ],
  "env": {
    "test": {
      "presets": [
        [
          "@babel/preset-env",
          {
            "targets": {
              "node": "current"
            }
          }
        ]
      ]
    }
  }
}

```

然而，根据`analyze`显示，`element-ui`所占的体积大的惊人。

![image-20200824201732382](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200824201732382.png)

<a id="解决方案-2"></a>

### 解决方案

参考[脚本之家\_www.jb51.net](https://www.jb51.net/)这篇文章，给我的主要启发是：**不能直接在`.babelrc`文件中配置，而是在`nuxt.config.js`的`build`选项中启用`babel`的配置**。

```js
  build: {
    analyze: true,
    babel: {
      plugins: [
        [
          'component',
          {
            libraryName: 'element-ui',
            styleLibraryName: 'theme-chalk',
          },
        ],
      ],
    },
  },
```

<a id="结果"></a>

### 结果

目前的页面分析结果如下，可以看到，`element-ui`的体积大小，已经相较于之前好了很多，连同另外一个`css`框架一起只占一半的依赖包体积了。

![image-20200824201157993](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200824201157993.png)

<a id="【已解决】关于移动端页面无法滚动的问题"></a>

## 【已解决】关于移动端页面无法滚动的问题

找了一遍，果然是`overflow`的问题，出在了这里：

![image-20200822222041677](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200822222041677.png)

这里原作其实是判断使用`single page`的，我把`single`部分删了，变成了这样。

我没有测试过原作的移动端显示，但现在的问题就是移动端无法滚动了。

因此删除`overflow-y-hidden`。

<a id="【已解决】bug：element-ui中的loading不居中的问题"></a>

## 【已解决】BUG：Element-UI 中的`loading`不居中的问题

参见：[element-ui 局部区域 loading 效果](https://blog.csdn.net/wangguoyu1996/article/details/81394817?utm_medium=distribute.pc_feed_404.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase&depth_1-utm_source=distribute.pc_feed_404.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecas)

换个图标就可以了。

<a id="非正常显示效果（默认图标）"></a>

### 非正常显示效果（默认图标）

```vue
v-loading="loginLoading"
<!-- element-loading-spinner="el-icon-loading" -->
element-loading-text="正在努力奔跑……"
```

![image-20200822022440891](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200822022440891.png)

![image-20200822022026311](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200822022026311.png)

<a id="正常显示效果（换了图标后）"></a>

### 正常显示效果（换了图标后）

```vue
v-loading="loginLoading" element-loading-spinner="el-icon-loading"
element-loading-text="正在努力奔跑……"
```

![image-20200822022337209](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200822022337209.png)

![image-20200822021931120](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200822021931120.png)

<a id="原因-1"></a>

### 原因

默认使用`svg`图片占位，而父级元素`.el-loading-mark`只有一个`text-align: center`的居中设定（而非`display: flex; justify-content: center`）。

所以默认的那个圈圈不会居中，换成`<i class="icon-xxx"></i>`就可以解决了，因为它支持`text`级别的居中。

<a id="关于asyncdata的用法"></a>

## 关于 asyncData 的用法

不可以在子组件中使用。

具体可以参见[vue.js - Nuxt 子组件内可以使用 asyncData 吗？ - SegmentFault 思否](https://segmentfault.com/q/1010000012989100)

害，费了老长时间测这个问题了。

<a id="【已解决】bug：关于无法在ide中移动、删除或重命名文件（夹）的问题"></a>

## 【已解决】BUG：关于无法在 IDE 中移动、删除或重命名文件（夹）的问题

<a id="现场-1"></a>

### 现场

我想重命名`CS`文件夹为`coding`文件夹，然而出现了`IOException`。

![image-20200821012423773](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200821012423773.png)

很明显，这是因为文件夹被占用，但我并不清楚是谁在占用，我的 IDE 也不够强大到为我分析出是哪个程序或者子程序。

我尝试关闭了我正在运行的 IDE 内的程序，但并没有解决问题，说明是来自外部的。

我尝试又关闭了一些外部程序，比如`typora`，因为当它打开了这个文件夹下的某个文件后，IDE 将无法对该文件或该文件所在的文件夹进行一些敏感操作。

但这一切都未能奏效。

这是十分令人恼火而绝望的，因为你并不知道那个程序对该文件将持续占用控制到什么时候。

在我以前的经历中，我经常做的一件事就是重启 IDE，这是往往有效的，但，这实在代价太大了。

于是，这一次，我打算深入研究一下这个问题，我把目光投向了我的搜索引擎。

<a id="行动"></a>

### 行动

我从“文件被占用”这一情景出发，进行搜索。

我之所以知道这样的一种术语，是因为我曾经使用过 360 安全卫士的“解除文件占用”功能，偶尔还是有效的。但更多的时候并不有效。

我很快找到了这篇文章[win10 文件被占用无法删除如何解决－系统城](http://www.xitongcheng.com/jiaocheng/win10_article_47290.html)，跟着它的指导，我输入了文件夹名结果跳出一堆候选结果。凭借经验，我重新输入了文件夹的绝对路径，顺利地找到了始作俑者——“TgitCache.exe”。

![image-20200821013210368](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200821013210368.png)

这个结果意料之外，但情理之中。因为在之前，我也遇到过因为 git 的占用，导致文件系统无法操作的情况，那个时候我直接杀死了任务管理器中的无数个 git 子进程，不想再次尝试。

但我实在不清楚 TgitCache 具体是个什么东西，我再次搜索，在这个帖子中发现有人有和我一样的问题：[如何停止并启动 TGitCache.exe？ - 问答 - 云+社区 - 腾讯云](https://cloud.tencent.com/developer/ask/82180)。

一些大佬留言只要关闭`TortoiseGit`的`Status Cache`就可以了。

![image-20200821013827496](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200821013827496.png)

但我如此设置之后，返回 IDE，依旧未能解决问题。

我决定重启一下`TortoiseGit`。

:::warning 但我并不知道怎么重启这玩意，然后右键在文件夹内点击了`Bisect reset`，获得一个 error 之后，发现刚刚输入的文章内容全无了，我简直欲哭无泪。不过还好文章在 IDE 中同步打开了，调用`local history`成功找回了原来的内容，我真是太爱这个功能了！ :::

我通过任务管理器杀死`TortoiseGit`。

![image-20200821014739527](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200821014739527.png)

但我懵逼了，IDE 中依旧不能重命名。。。

<a id="解决方案-3"></a>

### 解决方案

一顿操作猛如虎后，我最后还是选择直接关闭 IDE，然后重启，这下终于成功了。

人生大抵如此，兜兜转转，还是要回到原点~

<a id="【已解决】bug-在markdown文件中引用vue组件，props不能成功传入的问题"></a>

## 【已解决】BUG: 在 markdown 文件中引用 vue 组件，props 不能成功传入的问题

<a id="现场-2"></a>

### 现场

这是因为在读取 markdown 文件过程中，变量名自动取成了小写，导致原先定义的驼峰式 prop 变量无法正常赋值。

具体而言就是，在 markdown 中`:wordList`会变成`:wordlist`，而原先的 vue 组件中则会保持`wordList`的 prop 不变，这导致了 vue 组件多了一个`wordlist`属性，而`wordList`则为空。

<a id="解决方案-4"></a>

### 解决方案

<a id="【部分解决】bug-content-theme-docs中关于indexmd的路由问题"></a>

## 【部分解决】BUG: content-theme-docs 中关于 index.md 的路由问题

<a id="现场-3"></a>

### 现场

![image-20200818171926502](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818171926502.png)

<a id="解决方案-5"></a>

### 解决方案

使用`index.vue`等 page 页面去定义这些路由即可。

<a id="【已解决】bug-关于frontmatter中未定义fullscreen字段，导致全屏切换组件无效的问题"></a>

## 【已解决】BUG: 关于 frontmatter 中未定义 fullScreen 字段，导致全屏切换组件无效的问题

<a id="现场-4"></a>

### 现场

我封装了一个点击切换全屏的组件，它依赖于父组件（即`nuxt-content`页面的`document.fullScreen`属性）。

我在测试的过程中发现了问题，原因是我的一些页面没有初始化`fullScreen`的`frontmatter `，而我的切换逻辑仅仅是简单的取反，即`document.fullScreen=!document.fullScreen`。

我修改这个逻辑，希望它变得更加稳健，即`document.fullScreen=!(document.fullScreen || false)`。

然而，并不奏效，我忽视了我靠切换`fullScreen`属性以改变网页展示的行为，依赖于 vue 对 data 元素的监听。

由于我们的 markdown 文件事先并没有写入`fullScreen`，因此导致 vue 并没有监听到该键，所以之后的操控行为并非响应式的。

<a id="解决方案-6"></a>

### 解决方案

第一种解决方案就是修改原来的 markdown 文件，使之包含一个默认的初始值，比如`fullScreen: false`。

第二种解决方案，则是修改一下生成`frontmatter`或者解析`frontmatter`步骤的代码，使`frontmatter`或者`document `有着合理的默认值。此外，对于不规范的 markdown 文档，还应在 console 中进行 warning 提示。

<a id="【已解决】bug-content-theme-docs中关于index键重复的问题"></a>

## 【已解决】BUG: content-theme-docs 中关于 index 键重复的问题

<a id="bug初见面"></a>

### BUG 初见面

我在使用`nuxt-content`官方的`content-theme-docs`主题时，遇到了浏览器警告，提示我`index`键重复。

![image-20200818163726511](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818163726511.png)

这样的报错，我是大概知道什么原因的。

这是因为我刚刚从`vuepress`框架迁移到`nuxt`框架上来，`vuepress`需要每个文件夹下有一个`index.md`文件用以渲染该文件夹路径，而当访问这些没有`index.md`的文件夹路径时，将失败。由于这些文件夹路径大多又和导航栏、侧边栏相绑定，耦合很高，极易出现意想不到的 bug。

`nuxt-content`虽然也是基于文件路径，但是给出了更加灵活的路由方案，因此不需要如此大费周章。

基于此，**我直接删除或者重命名了博客文件夹下所有（除首页）的`index.md`文件**。

于是，报错不再发生了。

<a id="bug再见面"></a>

### BUG 再见面

尽管如此，意外还是继续发生了。

同上，如果我直接访问一个没有`inedx.md`的文件夹路径，`nuxt-content`也会报出`page not found`的问题，只不过，由于`content-theme-docs`主题里的侧边栏设计的比较巧妙，即**文件夹路径默认不可点击**，因此发觉不了这样的问题。

但是，现在有一项新的需求：**没有 index.md 文件将无法实现面包屑导航的功能**。

即当从`AAA/xxx.md`文件导航回`AAA`文件夹时，由于该文件夹下没有`index.md`文件，将导致导航失败。

基于此认识，如果我们想让自己的文件导航系统更加稳健，我们还是应当采取`vuepress`的管理方案，**每个文件夹下必须有一个`index.md`文件用于导航占位**，或者，**在程序中设置对应的路由选项**，比如为其设定一个默认的页面展示。

我认为，两者可以结合使用，使程序具有更强的扩展性与兼容性。

于是，**我再次新建了一些`index.md`文件**，并**再次触发了`index key 重复`的报错**。

<a id="摸索历程"></a>

### 摸索历程

#### 源代码检查

查看源代码，原来是`content-theme-docs`的作者，在遍历文章列表（以生成侧边栏）时，将文章的`slug`作为了键索引。

`slug`是什么鬼呢？在`gatsby`框架里`slug`就是文件的路径，即域名后面的一串`path`。

但在`nuxt`中我检查出以下的结果。

首先是`marked`包中有`slug`的生成方式，如下。

![image-20200818165256663](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818165256663.png)

有点复杂，主要是我并不知道这里面的`e`是什么，是文件名？还是文件路径？不得而知。

接着在`content-theme-docs`中有一个`slug`的赋值操作。

```js [nuxt-content-theme-mark/index.tsx]
export default (userConfig) => {
  const config = defu.arrayFn(userConfig, defaultConfig);

  config.hooks['content:file:beforeInsert'] = (document) => {
    const regexp = new RegExp(
      `^/(${config.i18n.locales.map((locale) => locale.code).join('|')})`,
      'gi',
    );
    const dir = document.dir.replace(regexp, '');
    const slug = document.slug.replace(/^index/, '');

    document.to = `${dir}/${slug}`;
  };

  return config;
};
```

可以看到，这里的`slug`主要是从文档的`slug`属性中，替换掉`index`，并生成文档的路由地址，但貌似也不是我们想要的答案。

再接着，我们查到了`content-theme-docs`中关于导航栏生成的代码。

```html {2,11}[nuxt-content-theme-mark/components/global/app/AppNav.vue]
<li
  v-for="(docs, category, index) in categories"
  :key="category"
  class="mb-4"
  :class="{ 'lg:mb-0': index === Object.keys(categories).length - 1 }">
  <h3
    class="mb-2 text-gray-500 uppercase tracking-wider font-bold text-sm lg:text-xs">
    {{ category }}
  </h3>
  <ul>
    <li
      v-for="doc of docs"
      :key="doc.slug"
      class="text-gray-700 dark:text-gray-300"></li>
  </ul>
</li>
```

在这里，首先对所有的目录进行遍历，这些目录其实不是文件系统中的目录，而是定义在每篇文章里`frontmatter`中的字段`category`。

```vue
categories() { return this.$store.state.categories[this.$i18n.locale] }
```

:::tip

说到这儿，如果对`content-theme-docs`生成侧边栏的方式不满意，以及对于`frontmatter`中需要人为加入`directory`而非`tags`等设定不满意的话，可以重写一下`AppNav.vue`文件。（我自己目前还挺满意的，我并不想 hack 这个文件，以改变所有文章的筛选显示。我会采取`\$content()`的方法进行筛选。 :::

由于目录一般来说都是些不一样的文件名，而且`categories`已经是一个集合（应该是），不存在键重复的问题。

但最后一行，`doc.slug`就有问题了，因为这里的 slug，很有可能就是文档名，即对于任意文件夹下的`index.md`文件，其`slug`都等于`index`，由此引发了键冲突。

<a id="解决方案-7"></a>

### 解决方案

由于`vue`中的遍历，键只是一种索引，比较随意，因此简单修改以上源代码，将键设置为其他字段就好了，比如本地文件系统的路径地址，这个肯定唯一。

实践结果显示，浏览器确实不再报错了，解决方案有效！

<a id="反思总结"></a>

### 反思总结

尽管问题解决了，但是还有一些困惑存在。

#### 1. `content-theme-docs`这个 slug 到底是怎么生成的，为什么只生成了文件名（而不是像其他框架一样生成了文件的相对路径）？

留待后续解决吧！

<a id="【已解决】bug-element-ui默认drawer不能滚动"></a>

## 【已解决】BUG: element-ui 默认 drawer 不能滚动

<a id="需求"></a>

### 需求

我需要实现一个点击`菜单`�� 弹出一个`抽屉`，显示可供选择的菜单项。

<a id="现场-5"></a>

### 现场

我使用了`el-drawer`帮助我完成这样的需求。

在开发过程中，我尝试放入了一个较长的列表项，这直接导致抽屉中的内容高度超过 100%，并无法滚动。

问题是无法滚动，这不符合常识。

我搜索到这样的一篇帖子：[[Bug Report] el-Drawer Rolling Problem Repair · Issue #17600 · ElemeFE/element](https://github.com/ElemeFE/element/issues/17600)，原来是`drawer`内部的 css 设定了`overflow:hidden`。

了解到这样的信息后，我立即验证了一下，果然是这个问题。

![image-20200818160242494](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818160242494.png)

那么解决方案就很简单了，通过各种方式修改成`overflow:auto`即可。

<a id="解决方案-8"></a>

### 解决方案

帖子中给出的方法是修改`element-ui`的`index.css`文件，我尽量避免这样的措施。

我选择的方法是对该组件进行`css穿透`设置，详情如下。

```scss
/deep/ .el-drawer {
  overflow: auto !important;
}
```

可以看到，浏览器里已经成功覆写了内部`overflow:hidden`的设定，转而变成`overflow:auto`，满足了我们滚动的需求。

<a id="反思总结-1"></a>

### 反思总结

有几点值得注意。

#### 1. 为什么 element-ui 要屏蔽溢出

不得而知。

也许是他们认为打开的抽屉，不应有超出的内容，毕竟真实世界中抽屉是不可以装超过自身体积的东西的。

所以，也许有其设定的合理性。

在此共识上，我自己也尽量遵循这样的一种设定，我目前是开发阶段，所以直接装入了一个很长的列表，后续会把它们组合，尽量使之不超过整个容器体积。

但尽管如此，我还是倾向于可以竖向滚动，因此我还是在组件中使用了穿透的方式，以防万一。

#### 2. 两种穿透方式

```less
/* 方式一，使用/deep/，通用 */
/deep/ .el-drawer {
  overflow: auto !important;
}

/* 方式二，使用 >>>，sass不支持 */
>>> .el-drawer {
  overflow: auto !important;
}
```

#### 3. 穿透设置要点

以下写法是不正确的，这意味着在`el-drawer`下的一些子级元素需要进行`overflow:auto`的设定。

```less
.el-drawer /deep/ {
  overflow: auto !important;
}
```

在这里的实际需求是`el-drawer`其本身需要进行`overflow:auto`的设定。

因此，顺序很重要。

<a id="【已解决】bug-prettier对jsx格式style分行后浏览器解析无法识别"></a>

## 【已解决】BUG: prettier 对 jsx 格式 style 分行后浏览器解析无法识别

<a id="现场-6"></a>

### 现场

初始代码，一行 jsx，定义了多个 css 属性。

![image-20200818132729397](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818132729397.png)

经过`prettier`美化后，变成了多行。

![image-20200818133051185](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818133051185.png)

然而，在浏览器里渲染出来，却多了换行符导致`css`无效。

​ ![image-20200818133210747](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200818133210747.png)

<a id="解决方案-9"></a>

### 解决方案

使用正则替换一下。

```js
const styleReplace = (s) => {
  const s2 = s
    .trim()
    .replace(/\s*(\S*): (\S*);\s*/g, "'$1': '$2',")
    .replace(/style="(.*?)"/m, ':style = "{$1}"');
  console.log(s2);
  return s2;
};
```

<a id="反思总结-2"></a>

### 反思总结

待更。
