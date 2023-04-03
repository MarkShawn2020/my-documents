# 美丽中国-携手未来系统-研发笔记

## TODO

### 3.1 后端与数据库

- [ ] 设计数据库账号信息表、大咖信息表（~Sun, 2.12）
- [ ] 搭建api系统，测试信息表的增删改查（~Sun, 2.12）
- [ ] （可选）设计埋点系统（~Fri, 2.17）
- [ ] （可选）设计反爬系统（~Fri, 2.17）
- [ ] 稳定性测试、压力测试（~Sun, 2.19）

### 3.2 前端

- [ ] 实现解析并播放 bilibili 视频链接 （优先尝试 iFrame 方案）（~Fri, 2.10）
- [ ] 实现解析并渲染微信公众号文章 （优先使用爬虫方案）（~Fri, 2.10）
- [ ] 实现解析并渲染 word 文档 （需要调研）（~Fri, 2.10）
- [ ] 实现生成大咖信息页布局，各类模块交互体验正常（~Wed, 2.15）
- [ ] 实现生成携手系统关系图，交互体验正常（~Wed, 2.15）
- [ ] 确定与实现网页整体布局（~Fri, 2.17）
- [ ] 确定与实现登录模块UI与交互（~Fri, 2.17）
- [ ] 确实与实现其他非核心功能模块（例如：网站备案号）（~Fri, 2.17）

## 网站实现

### 建立

使用 nextjs + typescript

```sh
# for ubuntu install npm with the latest, ref: https://askubuntu.com/a/480642/1629991
sudo apt install npm
sudo npm cache clean -f
sudo npm install -g n
sudo n stable

# app
npx create-next-app@latest --ts hand-future
npm install eslint@8.22.0 --save-exact
```

## 外链实现

### bilibili 视频链接

参考：

- 「馨客栈研究院」网站嵌入bilibili视频的一些总结 - 哔哩哔哩, https://www.bilibili.com/read/cv6775208

## TIPS

### `fetch` 不能用 `localhost`，否则会导致 `cause: Error: connect ECONNREFUSED`

ref: https://github.com/node-fetch/node-fetch/issues/1624#issuecomment-1235826631

### React HOOK 不能在 Servr Component （也就是 `app/page`）里写，而要放到 Client Component (也就是 `pages/xxx`里)

### nextjs: `appDirs` in `next.config.js`

see: https://nextjs.org/blog/next-13

### ts: generate indexed array

```ts
// soluton 1: target: ES6
[...Array(10).keys()]

// solution 2:
Array.from(Array(10).keys())
```

ref: https://stackoverflow.com/questions/3746725/how-to-create-an-array-containing-1-n

## BUGFIX

## solved: `error - Failed to download `Inter` from Google Fonts. Using fallback font instead.`

```sh
# 配置代理
export HTTP_PROXY="http://localhost:7890
# 下载资源
npm run build
```

ref: Next.js example takes a long time to compile due to Inter google fonts - Stack Overflow, https://stackoverflow.com/questions/74889692/next-js-example-takes-a-long-time-to-compile-due-to-inter-google-fonts

### solved: `ESLint: TypeError: this.libOptions.parse is not a function`

ref: https://stackoverflow.com/questions/73509984/eslint-typeerror-this-liboptions-parse-is-not-a-function

```sh
npm install eslint@8.22.0 --save-exact
```
