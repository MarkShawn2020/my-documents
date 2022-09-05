# electron prisma sqlite 2

[toc]

## PASS: test putting `prisma | @prisma/client` under release package.json

## :white_check_mark: cannot start when integrated with sqlite in packed version

suppose:

```yaml
APP=release/app
```

### step 1. add dependency in `APP/package.json`

```json
// release/app/package.json
"dependencies": {
    "sqlite3": "^5.0.2"
},
```

### step 2. rebuild project

:::warn maybe we should `node i -g node-gyp` first :::

```sh
[npm run rebuild] electron-rebuild --parallel --types prod,dev,optional --module-dir $APP
```

### step 3. build and pack again

```sh
npm run build
[npm run app:dir] electron-builder --dir
```

ref:

- [在 Electron 中使用 SQLite3 - 掘金](https://juejin.cn/post/6844903661336788999)

- [electron-builder electron (8.2.0) & sqlite3 (4.1.1) · Issue #4852 · electron-userland/electron-builder](https://github.com/electron-userland/electron-builder/issues/4852)

- [chore(deps): upgrade node-gyp to ^6.0.1 by malept · Pull Request #327 · electron/electron-rebuild](https://github.com/electron/electron-rebuild/pull/327)

- [sqlite - electron-packager with sqlite3 and webpack - Stack Overflow](https://stackoverflow.com/questions/50991453/electron-packager-with-sqlite3-and-webpack/51256562)

### step 4. PLUS: if we don't pack `sqlite3` into $APP, then we won't pass the webpack build process only if we add this

```js
// .erb/configs/webpack.config.base.ts
  externals: [
    ...Object.keys(externals || {}),

      // for prisma build
      // https://github.com/prisma/prisma/issues/6564#issuecomment-899013495
    {
      _http_common: '_http_common',
    },

	// for sqlite3 build
    // https://stackoverflow.com/a/51256562/9422455
    { sqlite3: 'commonjs sqlite3' },
  ],

```

## :white_check_mark: can normally open if no database connection in source code

```ts
// src/main/db.ts
interface FakePrisma {
  erp: {
    create: any;
    upsert: any;
    findMany: any;
  };
}

export const prisma: FakePrisma = {
  erp: {
    create: () => {
      console.log('fake-database: creating one');
    },
    findMany: () => {
      console.log('fake-database: finding many');
    },
    upsert: () => {
      console.log('fake-database: upserting one');
    },
  },
};
```

## using pure `sqlite3` and the programme goes well under prod, then failed with a popup suggesting me to integrate sqlite3

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png" width="480" />

## integrate prisma like sqlite

When add the `"@prisma/client": "^3.7.0"` into `APP/package.json`: <img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641290264413-57cae0d3b39ee3b8783d83a56ea24476ccbfdddc76b12d2c345f9cced752415c.png" width="480" />

So we then try to add `.prisma` into it.

```json
  "dependencies": {
    "@prisma/client": "^3.7.0",
    "sqlite3": "^5.0.2"
  },
  "devDependencies": {
    "prisma": "^3.7.0",
    "@prisma/client": "^3.7.0"
  }

```

<img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641293795481-b2c1a6b69d6a1b726668058367a514807d2dfdb0800bd355d419b48db85fe557.png" width="480" />

<img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641294082849-a16d9878554cebc58aed0ac7ce8b87b32f5ba62f4fe957a7e30b6b13162185c3.png" width="480" />

<img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641294185753-c1bf2a6bf3db20c554daeee3b02332667ff24f6542f7da8f85dfb166794e9f5b.png" width="480" />

After I moved the `libxxxxnode` into `main`, then things are ok, except still too slow!

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641294596528-f65b42bf2bc804b70c7c3f6254eff77d607048906fb64c3ca34f7d81aab9c3b8.png" width="480" />

I try to debug as [Other packages make Prisma load very slow · Issue #8484 · prisma/prisma](https://github.com/prisma/prisma/issues/8484) did:

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641295180935-1184a4b6fedb71a7de0cc9ef7d529bbeccd822dd3dd370014c3e449ca8965223.png" width="480" />

I found this app used my local packages, which maybe the issue behind the load problem.

So I uninstalled the global prisma:

```sh
npm uninstall -g prisma
```

Then I run again.

<img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641295340433-9db9c014cb84a5ee31e8600175343fbaa8465c99c2808a66ef5079202f695a6d.png" width="480" />

However, it starts to use the packages in my dev project.

Finally I do a copy before I run for test:

```sh
# $erb
# copy
cp prisma/schema.prisma $app/Contents/Resources/app/dist/main/
cp node_modules/.prisma/client/libquery_engine-darwin.dylib.node $app/Contents/Resources/app/dist/main

# run
open release/build/mac/皇家小虎快递分析系统.app/Contents/MacOS/皇家小虎快递分析系统
```

:sparkles: maybe it's because prisma is searching file location, so that the system runs slow! (since finally it didn't search any `schema.prisma`, which enlightened me!)

## I am quite sure now the problem is about package import with `prisma`

I added one log just at the entrance of the whole programme.

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641300763719-36feb313c6ae07962b53e5140d909ed3b462de2a8e425f3eefa789746adfe833.png" width="480" />

And I am lucky to see it is printed after programme runs in binary, and then wait, which indicates the start of programme is ok, except the packages.

<img alt="picture 19" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641300743690-a321e7f6c6325a6210c8c694936e99cb18c76ddba1748061953908cc1d7e2e5f.png" width="480" />

## Yeah, thanks Mac's console, I saw the dawn :sparkles::sparkles::sparkles

Stupid!

I found nothing helpful!

(Since the programme didn't cause any system exception, except block)

## Finally found the problem, it's about the block of searching path

Just add these two lines for debug the `findSync` sentence. <img alt="picture 24" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641309385635-2c7f27383d90ee8aac8e0e32db1af1556f44c6ce1375e3b8a5e43d220a263a04.png" width="480" />

Then you would know where does it go wrong. <img alt="picture 23" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641309113293-e1bedee09b6842acbf3a2b9df051fca3e7612735e584bf70113035b2301a64c7.png" width="480" />

I located to the source code. <img alt="picture 25" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641309815216-65fbe7024490017e84223d0a82247e52ddd400994c9a61491476e6abd8b6cbb4.png" width="480" />

It seems the path generated incorrectly.

Since this directory is generated via cli, I re-generate it, which looks more normal then.

<img alt="picture 26" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641309960859-813a4586ebe04ff12d61d4632641f4ee7bfb18a3c2d5171b9c70d26a1db081b1.png" width="480" />

And then we pack again.

```sh
npm run build
npm run app:dir
```

Look into what's new in the `APP/../main.js` <img alt="picture 27" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641310502054-05ca31db8f32b47a028d463efeb660dbcb3a04f7f5107e48bd230be78afd0dfd.png" width="480" />

OK, it's consistent with the source code after we `prisma generate`.

However, there's no `node_modules` neither `.prisma` under `main.js` directory now:

```sh
➜  main git:(main) ✗ ls
main.js             main.js.LICENSE.txt preload.js
```

It's because we didn't pack it into `app.asar` in electron.

So how to achieve this goal?

1. we cannot use `externalResources` choice since it only pack files into `Resources/` not `app/main/`
2. if we use `files`, then the files would list in `app.asar` under `app` directory, this is what we are looking for.
3. if we add the dependencies under `app/package.json`, then there would be `node_modules` installed under `app`. It is also suitable if there would generate a `.prisma/client`, we can give it a shot only if we add `@prisma/client` into `app/package.json`.

```json
// release/app/package.json
  "dependencies": {
    "sqlite3": "^5.0.2",
    "@prisma/client": "^3.7.0"
  }
```

However, I tried but to find there is NO `.prisma` folder in the target place.

And I tried locally to find that if I do not use `prisma generate` then I only got an blank template `index.js`, which is certainly not I want.

<img alt="picture 28" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641311767968-ad39fe926e5eb38bc8bda6d19f8950fd48937490b710e9b4e8b94d732254a453.png" width="480" />

So, the answer is clear now: we can't put `@prisma/client` into `app/package.json`, since it won't generate the right sql model unless we use `prisma generate`. And even the `.prisma` generated locally, it won't be packed into out target application's app.asar folder.

Therefore, the only way best suitable for us is to manually copy the local `.prisma` folder to `app/dist/main/` so that can be searched by `prisma` in the binary application.

We then use `prisma generate` to synchronize the `node_modules/.prisma/client/index.js` with out `prisma/schema.prisma` file (which would copied into `node_modules/.prisma/client/schema.prisma`), along with the generated query engine for MacOS: `node_modules/.prisma/client/libquery_engine-darwin.dylib.node`.[TODO: what should windows user do; maybe copy all the files into app is not ideal for cross platform use. Instead, we should consider about only copy the `schema.prisma` file, and let all the other work generated by platforms]

<img alt="picture 29" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641312184877-79c3520e1b1f69e51de79ffcbf8e380d7312f4a46878b205bc0b17be2600658c.png" width="480" />

### I finally understand why programme start by `double click` would be so slow

I added log before `findSync` again, and run by double click of the main programme.

<img alt="picture 32" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641313449263-88324bddd0fbb97399caee5b72123ffbbb24e3eab8fb8178a60df72e0561b001.png" width="480" />

And it should tell me that the `process.cwd()` is `/` that means from my computer root!

<img alt="picture 30" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641313359005-aaed92dce777b54143a8dd9e8e0fef9324be40bf97bfc9505008f3ef53c391dd.png" width="480" />

As a contrast, I ran it according the electron helper which is within the main programme.

And the `process.cwd()` is `~`, which is much much faster! <img alt="picture 33" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641313624357-a725375b40e1c762592a7944d97f514f4166824854722db189f5686000b3c66b.png" width="480" />

### what's the `findSync`

<img alt="picture 34" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641314504643-a85fb0c38c3b5f5d201cf17469b50cb23e82246ee94e8ae18d06eeeb2042a586.png" width="480" />

So, according the source code, the `findSync` starts from the `root`, then to search target `pattern`.

<img alt="picture 35" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641314655645-e8a564598b87018e4914e1d0e8b5b1cd3cbd624b4900715e3a4d791cc31bf751.png" width="480" />

Thus, from the commands before, we can see, it would search target pattern `node_modules/.prisma/client` or `.prisma/client` from `process.cwd()` (i.e. `/` when run main programme and `~` when run in shell)

What's the solution?

1. directly change the logic into `_ = __dirname`, and put `.prisma/client` under the `__dirname`, i.e. `app/main`

2. perhaps there's way (i.e. package or not) to not go this logic, which is so-called best practice? But sadly, I haven't found one after many times of hard search in github of prisma. I am looking forward the developers of prisma can give one.

   1. For example, maybe there is a way allows me to fill some parameters so that to disable the hard search or change the root from?

<img alt="picture 37" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641323620341-43c3b49ec507dca9a7bfc9907e7a70c40a78f4fafafe4f80f18d6394572e94cb.png" width="480" />

ref:

- [prisma/buildDirname.ts at 62b91fd9bd32da983f457857411edef6daeecda1 · prisma/prisma](https://github.com/prisma/prisma/blob/62b91fd9bd32da983f457857411edef6daeecda1/packages/client/src/generation/utils/buildDirname.ts)

## Current Solution: avoid `findSync'

avoid any call of `findSync`

```js
// node_modules/.prisma/client/index.js

// to save the hard search time(maybe from '/'), let us directly point out the target prisma client place
console.log({process_cwd: process.cwd(), __dirname});
const dirname = path.join(__dirname, '.prisma/client');
console.log({dirname});

// const { findSync } = require('@prisma/client/runtime')
//
// const dirname = findSync(process.cwd(), [
//     "node_modules/.prisma/client",
//     ".prisma/client",
// ], ['d'], ['d'], 1)[0] || __dirname
```

```text
// main files structure of an packed electron on Mac
// with `.prisma/client` besides `main.js`
// generate via ` find . ! -path '*node_modules/*' ! -path '*Frameworks/*' ! -path '*assets*' ! -path '*lproj'  ! -path '*svg'  | tree --fromfile --noreport -aC`

. // Main Entrance
└── Contents
	├── Frameworks
	├── Info.plist
	├── MacOS
	│   └── HJXH-DATA-ANALYSIS // Script Entrance
	├── PkgInfo
	└── Resources
		├── app
		│   ├── dist
		│   │   ├── main
		│   │   │   ├── .prisma
		│   │   │   │   └── client
		│   │   │   │       ├── index-browser.js
		│   │   │   │       ├── index.js
		│   │   │   │       ├── libquery_engine-darwin.dylib.node
		│   │   │   │       ├── package.json
		│   │   │   │       └── schema.prisma
		│   │   │   ├── main.js // Main Runner
		│   │   │   ├── main.js.LICENSE.txt
		│   │   │   └── preload.js
		│   │   └── renderer
		│   │       ├── index.html
		│   │       ├── renderer.js
		│   │       └── renderer.js.LICENSE.txt
		│   ├── node_modules
		│   └── package.json
		└── icon.icns
```

## make binary can use `prisma db push`

The question is to intercept `prisma` into package use, am I right?(maybe not...)

Anyway, we'd better have a try at the first: add `prisma` as a dependency of app.

<img alt="picture 36" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641321785532-83ca4daa59910c730e2bad819c3150024b3ad2ed11442a0b13c32bac10b9803a.png" width="480" />

Now, we have `prisma` in node_modules.

However, I doesn't be positive about running with `prisma` since it's only a dependency not a command.

There are at least two kinds of commands we can use, one for global, one for those under `node_modules/.bin`.

The sad truth is that only when we run `npm i prisma` in packed app, we can have a `prisma` under `node_modules/.bin`, which seems unacceptable. [TODO: so why they cannot generate a `prisma` under `.bin` when I have assigned `prisma` in `package.json` of released app]

```sh
➜  app git:(main) ✗ npm i prisma

added 2 packages, and changed 1 package in 2s

3 packages are looking for funding
  run `npm fund` for details
➜  app git:(main) ✗ ls node_modules/.bin
detect-libc  node-gyp     prisma       rimraf       sshpk-sign   which
mkdirp       node-pre-gyp prisma2      semver       sshpk-verify
needle       nopt         rc           sshpk-conv   uuid
```

So let's have a try step by step.

First, only add `prisma` in the `package.json` of release.

### 若在`release/package.json`里指定了`@prisma/client`，则打包里没有`.prisma/client/index.js`

<img alt="picture 38" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641324945482-fa4db7120dea10e4574be593ce72e09deb916861a0dc70ed3013e7be5bb7c7cc.png" width="480" />

### 若未指定（只指定一个`sqlite3`），则有

<img alt="picture 39" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641325459183-9c244e08847be8d54907006fe7756d3434c355a2bc0c69ed1590dcb7cbe6b9ae.png" width="480" />

### 若直接指定两个（2022-01-06 02:15:12），则像一个一样还是报错了，但是我联想到了`rebuild`

<img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-prisma-sqlite-2-1641406506923-9e06bf919325752ab1192f9da896232020a2cf200f4dfd43ee903abc7ade9cf6.png" />

So when I used `rebuild` (in fact, it's `npm run post-install` instead of `npm run rebuild`), everything is okay now! (although with a lot of errors...)

<img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-prisma-sqlite-2-1641406632784-f50b2d9e1a74dd4929dde5b75479ea8a3b459f694c34da06a97ae212df9474b2.png" />

### `rebuild` 确实是一大解药，`rebuild`完之后还要把`prisma`移到对应的`node_modules`目录旁，运行一遍`prisma generate`，目前我一套流程走下来，将`prisma`一步步同步，效果还行；只不过最后一步还是有问题，感觉双击程序启动找不到路径的问题还是存在。既然这样，步步同步的方式似乎也没啥性价比了

### 再测试一下步步同步的方式是否可以装 windows，如果也不行，我就直接放弃 prisma 了

确实不行，只有`darwin`，没有看到给`win`用的 query-engine.

### 在 binary 里需要用`npm i prisma`安装脚本

```sh
➜  app git:(main) ✗ ls node_modules/.bin
detect-libc  needle       node-pre-gyp rc           semver       sshpk-sign   uuid
mkdirp       node-gyp     nopt         rimraf       sshpk-conv   sshpk-verify which
➜  app git:(main) ✗ npm i prisma

added 2 packages in 2s

3 packages are looking for funding
  run `npm fund` for details
➜  app git:(main) ✗ ls node_modules/.bin
detect-libc  needle       node-pre-gyp prisma       rc           semver       sshpk-sign   uuid
mkdirp       node-gyp     nopt         prisma2      rimraf       sshpk-conv   sshpk-verify which
➜  app git:(main) ✗ which prisma
prisma not found
```

但尽管如此，在程序中依旧是不可以直接用`prisma`的 cli 命令的，因为这个依赖于全局`prisma`。 <img alt="picture 40" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641325864607-2eef51948928ecdea5945715cbcc3849ddc26853568fff06053836804a64d967.png" width="480" />

可以考虑一下指定脚本。

<img alt="picture 41" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641326080156-7dc342f49aac66cb4bd0494096f70a72c692f9a64faaf0141bae89788a5701fc.png" width="480" />

不过脚本里用相对路径需要格外小心，`.|..`的拼接，是相对于脚本执行者的路径而言的，而不是脚本文件！

```js
const absDir = require('path').resolve('../../node_modules/.bin/prisma');
```

比如这句话，在我使用`open ./MacOS/HJXH-DATA-ANALYSIS`打开时，因为脚本执行者是`~`，即`/Users/mark`，所以它其实以这个路径为基准，最终转换成了`/node_modules/.bin/prisma`，这显然是不对的。

<img alt="picture 42" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641327264657-175bfcdadaca7a51529cbd8825454b81f68a210316fe55ddff53e5dbde64d1eb.png" width="480" />

所以在拼接时要连接上文件路径，像这样就对了。

```js
const absDir = require('path').resolve(
  __dirname,
  '../../node_modules/.bin/prisma',
);
console.log(
  `database: "prisma db push", curDir: ${__dirname}, targetPrisma: ${absDir}`,
);
```

<img alt="picture 43" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641327334520-499a53220b0945365efd324d7b3b608b7c6f5434cff333074c7eba9734bcc3e2.png" width="480" />

不过接下来又报文件找不到了，不过这是小事，马上解决。

这里总结一下：

1. 在二进制程序里，用全局命令是不合适的，比较好的是用自己包里的命令，但这不像开发环境那样仿佛天生就有，具体要先`npm i prisma`安装生成`.bin/prisma`可执行文件，然后再用绝对路径去引用它，当然，我们既然可以执行命令行，当然也可以导出一个变量。
2. PASS: 将 prisma 命令导出，这样，在其他地方都可以用 prisma 了

### 指定 prisma 文件

注意看上面的报错，其实它已经提供了我们方法了，就是将`schema.prisma`放到指定位置，即`prisma/`下。

不过这里也能看出，他们的代码规范不统一，比如`prisma.schema`在主程序中，被搜索的路径可不止这点，而且貌似还是以`schema.`优先的，而不是`prisma/schema.prisma`。

方法 1. 在`package.json`中加入`prisma.schema`字段方法 2. 移动目前的文件（从`schema.prisma`到`prisma/schema.prisma`）

这里就用方法 1 了：

```json
// app/package.json
  6   "prisma": {
  7     "schema": "dist/main/schema.prisma"
  8   },
```

然而还是报错了。

<img alt="picture 45" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641328243751-1aca13f23cfe42d39a7e6e163f36b408ca1825b281f5c7046af681baf4572ac0.png" width="480" />

我验证了一下路径，是没问题的，于是顺着链接去官网看了看，突然就意识到了，这可能又是相对路径的问题。

<img alt="picture 44" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641328226861-1929fd1ce321d98fdd99aae4fc2230af695176fa38764dd25687793f3b1ee4d6.png" width="480" />

为验证我的想法， copy 一份为`prisma/schema.prisma`，预期应该还是不行，因为都是相对路径，根据官网的搜索路径`./prisma/schema.prisma`就变成了`~/prisma/schema.prisma`，`./schema.prisma`就变成了`~/schema.prisma`。

不出所料，果然！即便我路径里已经包含了两种`prisma`，它都找不到，就是因为相对路径拼接错误。

```text
➜  main git:(main) ✗ tree .
.
├── main.js
├── main.js.LICENSE.txt
├── preload.js
├── prisma
│   └── schema.prisma
└── schema.prisma
```

所以，我们应该自己指定路径了，既然这样，那么在`package.json`中指定路径也没有意义了，因为绝对路径肯定要基于文件路径拼接的，所以只能在程序中动态拼接。

```js
  3 const _p = require("path");
  4
  5 const schemaExePath = _p.resolve(
  6     __dirname, "../../node_modules/.bin/prisma");
  7
  8 const schemaFilePath = _p.resolve(__dirname, "schema.prisma");
  9
 10 console.log(`database: "prisma db push", curDir: ${__dirname}, targetPrismaExeP    ath: ${schemaExePath}, targetPrismaFilePath: ${schemaFilePath}`);
 11
 12 i.default.exec(`${schemaExePath} db push --schema ${schemaFilePath}`,
```

### `prisma/client`

OK！用路径拼接转绝对路径的方式，解决了上面的问题【TODO:给 prisma 提一个 pr，考虑一波基于文件的路径拼接，而非 process，要烦死了】，新的问题就是装一下`prisma/client`，

<img alt="picture 46" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641329044401-924bc44ed86e843bbf3d7f95bd397b823454b6390a2bdd8434d17585f4680012.png" width="480" />

这个比较简单。不过也有两种办法：

1. 直接命令行安装：`npm i @prisma/client`
2. FAILED:尝试把外部包导入看看是不是就不需要装了

这里用第一种办法：

<img alt="picture 47" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641329276722-1de83c864711b6136a77e6b4d78546bb25b06af805a31f86b886daa26c62ca12.png" width="480" />

成了！

### 最后一个问题，`query-engine` （2022-01-06 02:07:34 update: obviously not the last）

It seems to place the engine dirctly under th project, would b a nice solution.

<img alt="picture 48" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641341198622-23c03a1d8768467ff5da78eea2a3ecf820345938d9dc330e11c6871fce27c874.png" width="480" />

A full logo about no query-engine:

```text
01:51:49.127 › database: try to insert one iterm into `user`
01:51:49.133 › Error: Query engine library for current platform "darwin" could not be found.
You incorrectly pinned it to darwin

This probably happens, because you built Prisma Client on a different platform.
(Prisma Client looked in "/Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist/main/libquery_engine-darwin.dylib.node")

Searched Locations:

  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/.prisma/client
  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/node_modules/@prisma/client
  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist
  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist/main
  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist/main
  /tmp/prisma-engines
  /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist/main


To solve this problem, add the platform "darwin" to the "binaryTargets" attribute in the "generator" block in the "schema.prisma" file:
generator client {
  provider      = "prisma-client-js"
  binaryTargets = ["native"]
}

Then run "prisma generate" for your changes to take effect.
Read more about deploying Prisma Client: https://pris.ly/d/client-generator
    at cb (/Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/release/build/mac/HJXH-DATA-ANALYSIS.app/Contents/Resources/app/dist/main/main.js:2:1130669)
    at processTicksAndRejections (node:internal/process/task_queues:96:5)

```

## query-engine in Windows, another not positive problem

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-prisma-sqlite-2-1641406097880-52fd7d1b52661bbda1bcaaae269428e75a623e465b6113661d46264c107ec00a.png" />

PASS: try to use keyword of `native`

### 极小自动化程序搭建

1. prisma init and generate --> in order to generate target table
2. change `findSync` function to fasten speed --> in order to avoid search from pc root, which would cause even minutes wait
3. move `schema.prisma` into `release/app/` --> easy and default for programme search, which is consistent when in local development since `schema.prisma` is besides `index.js` under `node_modules/.prisma/client/`
4. use path-merge to generate ABSOLUTE path, both for `.bin/prisma` and `schema.prisma` --> in case for the default merge behavior of prisma is wrong when the base path is offered by programme rather then by file.
5. install `prisma`/`@prisma/client` in binary or try to pre-install

## :ballot_box_with_check: `prisma` in binary

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641244081948-ae8a83efcb1be3facf26b469c01373c949ac5290b5992996fd678650b16b2e87.png" width="480" />

When I didn't install `prisma` globally, neither had I placed `prisma` into binary, then the error `prisma command not found` occurred:

<img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641245007081-71ea6e315a6d7d980e03a74450dc5e57661ec5497791211443a37785d0e70f98.png" width="480" />

When I installed `prisma` globally, the error then came from `prisma file not found`.

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641244869137-b8237c6a5828025fe176e7e26acb08823ae96da2413a6cf25cf701e609913f38.png" width="480" />

So:

| install prisma globally | :white_check_mark: | :x: |

But when I added `prisma` file in the `package.json`:

```json
// package.json
    "extraResources": [
      "./assets/**",
      "prisma/schema.prisma"
    ],
```

And it did go to the target application at: `build/mac/皇家小虎快递分析系统.app/Contents/Resources/prisma/schema.prisma`

The file cannot be found yet in fact.

<img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641245255584-de651b38a5327b83e309e98e63ef7891f33b30bd48eb015d2f95dd66614b67f5.png" width="480" />

I thought of adding into `files` so that it can go to the `app.asar`, but in vain:

<img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641245688562-d7a4098c6a0ea4b5e465de2c2186a9c557dfd71b493ed7afdc533d6d0f407c10.png" width="480" />

Also failed for (in case it uses the relative path to `release/app`):

```js
     "../../prisma/schema.prisma",
```

## 最大的问题，不同启动方式，程序运行结果不一样，prisma 在可执行程序中找不到

<img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-prisma-sqlite-2-1641411307188-d2cfa0eb9f1bd80388ace2bf6f77188117e396c52a3ac4e5fa90b1fcd436b1d3.png" />

后来把程序移到`/Application/`里后就变快了，甚至运行其他程序都变快了……因为它们实际用的是`/Application/`里的那个`schema dir`。

prisma 目前的路径设计与机制，真地适合服务端程序，因为路径比较固定，客户端是真地要疯，程序启动的位置千奇百怪，变动也很频繁，导致 prisma 那套依赖文件自动生成的机制变得复杂且难以管理。

综上，electron 不适合与 prisma 搭配，electron 这种随处运行的程序应该选择机制更灵活的一些库，比如原生的`node-sqlite3`之类。

分析到此为止，和 prisma 说拜拜了！
