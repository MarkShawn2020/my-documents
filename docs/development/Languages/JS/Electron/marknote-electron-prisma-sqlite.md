1. [目标](#目标)
2. [在生产环境下可以读取`.env`变量](#在生产环境下可以读取env变量)
3. [目前已经实现在生产环境下，拥有环境变量，prisma 可以读取](#目前已经实现在生产环境下拥有环境变量prisma可以读取)
4. [实现方式](#实现方式)
5. [实现细节](#实现细节)
6. [在打包环境下，没有环境变量](#在打包环境下没有环境变量)
7. [不考虑环境变量，直接硬编码数据库文件地址](#不考虑环境变量直接硬编码数据库文件地址)
8. [electron-builder load `.env`](#electron-builder-load-env)
9. [打包环境下，竟然读到了环境变量](#打包环境下竟然读到了环境变量)
10. [重开项目进行分段测试！](#重开项目进行分段测试)
11. [摊牌了](#摊牌了)

> 本篇谨以记录一天一夜（2022 年 1 月 1 日晚 8 点到 1 月 2 日晚 11 点）才解决某软件打包后运行异常的问题，原本只为弄清问题，理清思路，才一步步调试记录，遂成文章。
>
> 本次为破解难题，可谓心情沉重与复杂，全程关灯关门听着大提琴与钢琴奋战才有所获。但最终的答案，却并非来自问题本身，而是涉及到问题背后的问题，因而，给我的教训更为深刻，价值也更为宝贵，遂刊之。

## 目标

- :white_check_mark: G1. 在开发环境下，实现初始化数据库、运行中 CRUD 数据库
- :white_check_mark: G2. 在生产环境下，实现初始化数据库、运行中 CRUD 数据库
- :white_circle: G1. 在打包环境下，实现初始化数据库、运行中 CRUD 数据库（update: :white_check_mark: solved since it's out of permission）

## 在生产环境下可以读取`.env`变量

### 目前已经实现在生产环境下，拥有环境变量，prisma 可以读取

### 实现方式

在`webpack.config.main.prod.ts`中，使用`dotenv-webpack`插件，会自动读取`.env`变量 <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641202097111-0447d8c9b7bd4cd446543df4d7035c78d381a8761aec5cb5b05cbf6b7723f0bb.png" width="480" />

### 实现细节

1. 运行`npm run build`

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641202237567-148ee19c466945aed7f23593a02481637c539148cba0fe1a432f256503955cad.png" width="480" />

2. 运行`electron release/app`

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641202270373-c3cf875b689d3bd464af4ca317c504e7cb0f8efb0383731d8c1f76bbe03dc93e.png" width="480" />

可以看到，已经有`DATABASE_URL`变量，该输出由源代码执行：

```ts
// src/main/db.ts
import dotenv from 'dotenv';
import {app} from 'electron';
import path from 'path';

dotenv.config();

const dbPath = path.join(app.getPath('userData'), 'sqlite.db');
const dbUrl = `file:${dbPath}?connection_limit=1`;
console.log(`The db url specified is ${dbUrl}, and the envs are:`);
console.log(process.env);
```

3. 该输出证明，`build`环境中已经有了`.env`变量

## 在打包环境下，没有环境变量

## 不考虑环境变量，直接硬编码数据库文件地址

遇到了 Query 的问题，猜测是`query_engine`或者`@prisma`没有存放到指定位置的问题。

```js
PrismaClientKnownRequestError: Failed to validate the query: `Field does not exist on enclosing type.` at `Query.findManyerp`
```

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641204200999-c3b7893d1e1a9b20659680a5516ed4a55ae9e5d1b9a0ab0da9c5ecfae5334b76.png" width="480" />

## electron-builder load `.env`

## 打包环境下，竟然读到了环境变量

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641206574494-62b217d0682587a549060e729667364448d1db47ffca110edd765a2345230dbe.png" width="480" />

去掉以下之后，依旧有：

```js
// package.json
      {
        "from": "prisma.env",
        "to": ".env"
      }
```

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641206809254-93caae8af81cc0898e0e41c0a8a3f515508e6907a32a5e8ae7fcd1f7ce418502.png" width="480" />

再尝试去掉以下，还是有。。

```js
// package.json
      "node_modules/.prisma/client/**/*",
```

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641206997694-7ff13106e6e66c40c94c82b9f9efd584941b6be7cad0a22009cfa676ffeac3f2.png" width="480" />

——————

再尝试去掉最后的一项：

```js
// package.json
'node_modules/@prisma/client/**/*';
```

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641207175716-7b76bc74a00534f1271bbd55c26a6ad32d225fff2f655199472616ab35dda167.png" width="480" />

他喵的，还是有啊。

难道是缓存？

我删掉再试一遍！

——————

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641207355025-cced27ae67e7b5471da8da199da9fed844268c387ab664321849800903174184.png" width="480" />

沃日啊，还有！

这下我就不明白了……

不知道是不是`dotenv-webpack`还是`prisma generate`搞的鬼。

我再把`dotenv-webpack`取消了看看！

——————

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641207608998-81f1ed696f9e63e07364a0881b38bc5f19b89d3f6264357e8e930f62770ecdd0.png" width="480" />

哈哈哈哈，果然没有了！

看样子真跟这个有关，那现在我再加回来，看看还有没有。

——————

果然又有了！

<img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641207757455-df00e99a1719abe2f2d8db45495098f6405b94e6886a51b0533558bf3f926366.png" width="480" />

那现在，我再去程序中，把`dotenv`的`config`句，取消，应该就没了吧！

```ts
// src/main/db.ts
dotenv.config();
```

——————

擦，还是有！ <img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641208023687-21c3e53559a2a67ae2ae2b5eb22d8f578d9240ff0182ea3b0ab18daa2ddc3211.png" width="480" />

如果果然如此的话，那我直接用默认的`options`属性，是不是就可以了！

```ts
// src/main/db.ts
-export const prisma = new PrismaClient(options);
+export const prisma = new PrismaClient();
```

这样，预期还是一样，会报`query`的问题，而不是像之前那样，报环境变量的问题。

因为，在`option`为空的情况下，`prisma`会去读`prisma/schema.prisma`，然后里面默认加载的是`env(DATABASE_URL)`。

—————

然而意外发生了！程序打不开了！只有一片空白！

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641208467702-92290684115599f52a6b00c011cc46c5ad977100676b4c9f381b752958311121.png" width="480" />

但我用`lldb`却显示是正常的。当然，`lldb`太强大了，不能作为程序是否能正常运行的标准。

<img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641208439561-e1fbee9c30db0ee9c3834c20e44cde786fff0103879e2b56074938355640942f.png" width="480" />

等等，沃日，又出现了！卧槽，连数据库都连接上了！

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641208528717-17aaac50924d7ad35ebbb0be0087b60774dff4a9b0869a01f058c9fcde1b46da.png" width="480" />

沃日，我好像悟:sparkles::sparkles:到了什么！

看！默认的配置，除了`url`还有一个`provider`哦！！！

<img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641208953995-a523f3097e0c5f74fbc8aa8f85729b78eb203fd7803bdb83ef935b8c48a58420.png" width="480" />

所以！！！

如果我们在程序中，直接同时指定这两项，是不是就等价于读取了本地`schema.prisma`了！

——————

之前用 url 的配置，虽然正确，但是覆盖了`prisma`的文件配置，然而，要想数据库真正正确地连接，除了`url`项之外，可还要有其他项的啊！

```ts
// src/main/db.ts
@@ -17,6 +17,8 @@ const options: PrismaClientOptions = {
   datasources: {
     db: {
       url: dbUrl,
+      // @ts-ignore
+      provider: 'sqlite',
     },
   },
 };
```

为啥要加这个`@ts-ignore`呢？因为`d.ts`里没有这个定义：

<img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641209316277-e6d097dca96bbec8649b5c60ec477809dc061cd51f83c1af50a6d3aa486854b4.png" width="480" />

所以，是我为了和`schema.prisma`对上，才加的，不知道结果会咋样……

——————

好的，又进入等待环节了……

<img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641209424635-f6326c5773fb7227f83e086a88f3518f564911707bf1c6b3f6b42ac3a53609e7.png" width="480" />

不过，根据上次经验，可能意味着是成功的。

<img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641209524193-a1d946546ed78e7a60a135149788448a3108ea2ab5669e915bb4ee44749e7cb7.png" width="480" />

我擦，很快就打脸了啊，并不是的！

这里应该是被类型报错了，意味着我不能加`provider`关键字。然后按照报错提示，去 read 了 more：

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641209686471-c2e5dde8844d15d542567d7c8136c1fa6efddb3df2e66f30b01a3eacdc425b99.png" width="480" />

You see！这是在 api 上做了限制，只可以'programmatically'修改`url`，其他的信息是不可以的！

那行吧！

既然我们的环境变量现在是奏效的，那就直接用环境变量吧，这里不加任何参数【TODO：当然了，我们等会要去测一下，到底是哪个`prisma`文件进行初始化的，以及 url 到底是是啥】

——————

呜呜呜，在大概 20-30 秒的空白后，程序终于启动了，表现良好！

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210163127-a260b7367fc18cb9bc08dbf44caf8a068f542e8f8e61f2793c2ef4c1515f0916.png" width="480" />

但我现在真地好奇，它到底是插的哪个数据库………………

总感觉，可能就是我本地的那个数据库……

如果是这样，我把那个数据库文件换换位置，它是不是又凉凉了…………

可能真的是本地的！因为我发现我的`navicat`被阻止了！

<img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210311381-d612f775c3c949cc7e8d278586807be36eb2e6c7b4450918b47653db662879c0.png" width="480" />

刚刚插完！navicat 又好用了！而且一共 23 万条，是和本次插入目标一致的！

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210443057-64cd868895dc6118df816ea33858d0dfcfce611f8f333b1227866664ec538060.png" width="480" />

<img alt="picture 21" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210453610-df7ec67a9fd52a6dee9465570f3ca8a89eb620e683f28eab5b78743ee3aee8ec.png" width="480" />

我有一个大胆的想法！

是不是因为，navicat 占着资源不放，导致我的程序启动很慢的！

因为我设置的`connection_limit=1`，为了防止插入失败！

——————

不行啊，还是很慢！还是 30 秒！我刚刚数了！

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210621195-dd0e5440f638be5836265de03d231f6ed4e4c78cf7b9d187e95dfeca7a7d7d58.png" width="480" />

那是不是因为我在初始化的时候，就启动`query`，导致阻塞了呢？

我先试试不在启动的时候插入。

PASS: 我记得`github`上，也有`start wait too long`的问题的，晚点去看看。

——————

所以我先把 db 的初始化 query 放到了菜单栏里，主程序不在初始时执行任何数据库动作。

```ts
// src/main/menu.ts
        {
          label: 'test database connect',
          click() {
            prisma.erp
              .findMany({ take: 2 })
              .then((e) => {
                console.log(`queried data: ${e}, it should has 2 items`);
                return 1;
              })
              .catch(console.error);
          },
        },
```

这样，预期程序启动速度就会很快了吧！

<img alt="picture 23" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641210956609-06255f626bbf7f80e5357241fb7f1a124b3e85b4d56a269cdc41d5a754802fa7.png" width="480" />

沃日啊，并没有！

还是 30 多秒呢！

行啊，再测一个！

是不是数据库连接就很慢，我直接不初始化数据库行不行？

哦不行，太麻烦了，之前试过，要改很多地方，主要是 typescript 会检查导入，我直接把数据库变量取消的话，需要同时修改很多才能通过编译。

:white_check_mark: 测试无数据库情况下的启动速度。结果：非常快！

——————

但是，你猜，你知道现在是啥情况吗？

是我用 lldb 或者程序启动，秒开，一切正常；接着我在内部包点击打开，需要 30 秒，然后一切正常；最后我直接在程序 logo 上点击，需要一分多钟，然后数据库没有数据结果。。

奔溃啊。

搞了这么久，还是老问题：

<img alt="picture 24" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641211571111-b2a036e5ee4fa8b346cb63205a687b6673932d9bef062abeb7e781562077a4b3.png" width="480" />

---

使用 asar 依旧不行。

## 重开项目进行分段测试！

1. 剔除 db 模块（prisma, sqlite)之后秒开，2022-01-03 21:04:34
2. 。。。

ONE HOUR LATER...

<img alt="picture 25" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-prisma-sqlite-1641222126966-6b16ac915cb84333c6a0902dd19e80723746f9f5dda13aea3c11bd7c33570d0a.png" width="480" />

## 摊牌了

历经整整有 30 个小时，原因终于在一个犄角旮旯的地方找到了：权限！！！

![image-20220103231434862](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/image-20220103231434862.png)

由于我将 sqlite 数据库存在项目里（默认行为），但并有打包进入程序，所以在开发时（无论是开发模式还是生产模式）没有问题，但是打包成可运行程序后，就有读写权限问题了。

这导致程序启动的时候，直接 cpu 飙升（到七八十），为啥呢？肯定是陷入了权限申请的无线循环！

然后三十多秒中甚至一分多钟后才打开，为啥呢？因为超时放弃了！

那为什么在摸索的过程中有出现过可以打开的情况呢？

那是因为我有过将 sqlite 存到 userdata 的尝试，那样连接的时候就没问题了，只不过 prisma 找不到，因为 prisma 要提前配置。

那接下来怎么办？

肯定还是不能在 userdata 里直接存业务数据的把，这样太大了？但也许也不是这么个意思，app 就那么大（1-300M），数据是单独存在程序对应的数据区的，即使把程序卸载，数据还在，这个模式应该还是比较合适的。不合适的是直接把 sqlite（尤其是已经有数据的）打包进程序，虽然我有这么做过，网上也有这么做的，但是场景不同啊，别人打包进去可能只是存一些基本数据、用户数据等，不像我这个场景，是用来存业务的，存业务应该是在 userdata 里新开数据库！这样才稳妥！

诶……

ref:

SPECIAL THANKS：

- [javascript - Exported Electron APP doesn't work on MacOS - Stack Overflow](https://stackoverflow.com/questions/49784259/exported-electron-app-doesnt-work-on-macos)

about electron:

- [Node 原生模块 | Electron](https://www.electronjs.org/zh/docs/latest/tutorial/using-native-node-modules)

- [electron-userland/electron-builder: A complete solution to package and build a ready for distribution Electron app with “auto update” support out of the box](https://github.com/electron-userland/electron-builder)

- [Getting Started - Electron Forge](https://www.electronforge.io/)

- [python - No such file or directory inside app.asar (electron/nodejs) - Stack Overflow](https://stackoverflow.com/questions/59566904/no-such-file-or-directory-inside-app-asar-electron-nodejs)

about prisma:

- [Prisma Client API (Reference) | Prisma Docs](https://www.prisma.io/docs/reference/api-reference/prisma-client-reference#upsert)

- [Deploying projects using Prisma to the cloud | Prisma Docs](https://www.prisma.io/docs/guides/deployment/deployment)

- [Prisma has a very slow startup time when my database has 100+ tables · Issue #10236 · prisma/prisma](https://github.com/prisma/prisma/issues/10236)

- [javascript - Electron-Prisma Error: can not find module '.prisma/client' - Stack Overflow](https://stackoverflow.com/questions/69323946/electron-prisma-error-can-not-find-module-prisma-client)

- [angularjs - How to use Prisma with Electron - Stack Overflow](https://stackoverflow.com/questions/64088437/how-to-use-prisma-with-electron)

about environment variables: (a good discussion about whether to use dynamic env)

- [Discussion between SigmaSoldier and Albert Chen | chat.stackoverflow.com](https://chat.stackoverflow.com/rooms/186836/discussion-between-sigmasoldier-and-albert-chen)

- [dotenv-cli - npm](https://www.npmjs.com/package/dotenv-cli)

- [kentcdodds/cross-env: 🔀 Cross platform setting of environment scripts](https://github.com/kentcdodds/cross-env)

- [How To Use .env Variables In package.json | GenUI](https://www.genui.com/resources/env-variables-json)

- [Environment variables | Prisma Docs](https://www.prisma.io/docs/guides/development-environment/environment-variables)

- [node.js - electron-builder, how to set node environmental variables - Stack Overflow](https://stackoverflow.com/questions/54214340/electron-builder-how-to-set-node-environmental-variables)
