# webstorm_bugfix

## FIXED: taro TS2304: cannot find name `definePageConfig` or `defineAppConfig`

对比之前跑通的葫芦心安发现，是 taro 脚手架的模板不同。

葫芦心安用的是云开发模板，而现在北京健康宝项目用的是 taro-ui 模板；

此外，云开发模板里使用了`global.d.ts`：

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm-bugfix-1657210494342-b96cc2aace95d794a589d8da39565ba51a87a153ef1c082040f56799b5ef754b.png)

而 taro-ui 模板里是没有的，尽管官方说 tato 3.4 里已经支持 `definePageConfig` 等两个宏变量。

结论！

脚手架谨慎用！

## FIXED: `XXX Component cannot be used as a JSX component`

使用 `yarn` 重装一下，不要用 `npm`。

其他升级 react 相关的、配置文件相关的都不管用。

## FIXED: `TypeError: this.cliEngine is not a constructor`

ESLINT 6 需要 webstorm 2019.1.3 及以上才支持。

ESLINT 8 需要 webstorm 2021.2 及以上才支持。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm-bugfix-1652138915611-0d08a09a6745aaee9bee02b3694cbcaa17de72cae441f5ef623cdcd9e071b561.png)

ref:

- [TypeError: this.cliEngine is not a constructor – IDEs Support (IntelliJ Platform) | JetBrains](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360004195120-TypeError-this-cliEngine-is-not-a-constructor)

## FIXME: solve `named capture` problem of webstorm

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640854673573-readme-8c2f4e6e9db2aa37f9bba372b2d2039dab7a4310fcbad63f9b9d9f019112c303.png" width="480" />

## webstorm refactor(rename) too long time

<img alt="picture 44" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641706539558-a03613bfcc7e4d4d0df479c0e1267bd0b73405bb75e93bf1fed7f3d3b7979d1f.png" />

<img alt="picture 45" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641706545588-f6231a5f6c0adfee467bcc37f92b5cf15ddd1201390c33e32921f8f51548e630.png" />

ref:

- [IntelliJ "Looking for Usages" freezes when refactoring/renaming enum entry - Stack Overflow](https://stackoverflow.com/questions/35713388/intellij-looking-for-usages-freezes-when-refactoring-renaming-enum-entry)

## :white_check_mark: IDE prettier not work

It's awkward since I used to write a `.prettierignore` (and then forgot) which disabled the prettier feature.

<img alt="picture 24" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641570105621-93874a507c9c0ccac4f13c8557707de0555cff2afed981b0800efc4205af186c.png" />

It's really like: when you use one way to solve out one problem, and then the one is the new problem.

## breakpoint does not work when debug typescript

### settings

Try to disable `js.debugger.use.node.options` in WebStorm registry.

You can do it by going to `Help -> Find Action`

In there just enter `Registry`.

ref:

- [node.js - Webstorm debugger breakpoints doesn't work in nodejs - Stack Overflow](https://stackoverflow.com/questions/30584923/webstorm-debugger-breakpoints-doesnt-work-in-nodejs)

### usage

#### correct usage

Use the option of `Debug TypeScript`.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641397756604-41e5517008a327ef4a9fe18bf5eff650016d15cd68770cc2caeb25e4e8add161.png" width="100%" />

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641397780548-5c78c909833b63864cd46673309851ff35aee553bd16bc0c903f6a53422b8023.png" width="100%" />

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641397805136-e77d330866c28f07dd66304b6dd252081cc64fd545262e487259ad23e6ab9249.png" width="100%" />

#### wrong usage

Don't use the option of `Debug 'db.ts'`.

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641397884871-0f537dbc04c6c485419c01476a2d73cf733c5d0c735f6cd823304b29a46fd1c1.png" width="100%" />

Since it doesn't work. <img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641397844244-f4927e7d432f15a3bb7b5ed4a7b7a99bbfabeb76398ff022d0cc8c8dab104fc2.png" width="100%" />

#### commands comparison

```sh
# right
/usr/local/bin/node --require ts-node/register --inspect-brk=63590 /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/src/main/db.ts
Debugger listening on ws://127.0.0.1:63590/eb5a68a9-6c82-4fa5-b432-f2daee811c0e
For help, see: https://nodejs.org/en/docs/inspector
Debugger attached.


# wrong
/usr/local/bin/node /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/node_modules/ts-node/dist/bin.js /Users/mark/Documents/mark_projects/hjxh/hjxh_express_match/erb/src/main/db.ts
```

See! The key maybe `--inspect-brk=63590`.

In fact, just use `--inspect` is ok:

```sh
node --require ts-node/register --inspect  src/main/db.ts
```

ref to: [Debugging - Getting Started | Node.js](https://nodejs.org/en/docs/guides/debugging-getting-started/)

<img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641398795545-22636d44ff7be2c131c264cf2f20560a209be8ea2f43007ede4acefe0ae18b88.png" />

<img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1641398811138-e7881ac92d6afa1af0cd0c10a43394a23fc53cd61ba801c097175ab1e9e6bd61.png" />

## PASS: webstorm terminal overflow when log `json.stringify`

when log json, it's normal:

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1640982063870-04e4dcc77fc53b37f1b29f195f62ab49c31d79decbb955503f4195831bc87e7e.png" width="100%" />

while using `JSON.stringify` not, since 'percentage' is overflow...

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/webstorm_bugfix-1640982122589-2cf56e01719afdcab8dedb67aaec95dc4915eccbad9f2f660057d81160796fee.png" width="100%" />

## suppress TS7016 Could not find a declaration file for module

I couldn't find where does it come from after searching all the possible keywords in webstorm settings relative to `declaration` with `typescript`.

Luckily, I came to know it's because of `tsconfig.json` file that tells me the problem, and the method to suppress it is to allow `implicit any`.

add `ts-config.json` with ["noImplicitAny": false](https://github.com/microsoft/TypeScript/issues/14379#issuecomment-305768525)

ref:

- [bug: TS7016 Could not find a declaration file for module · Issue #14379 · microsoft/TypeScript](https://github.com/microsoft/TypeScript/issues/14379)

## alias between eslint and webpack

```sh
yarn add -D eslint-import-resolver-alias
```

ref:

- [(20 条消息) webpack 小记——alias 与 eslint_weixin_34195364 的博客-CSDN 博客](https://blog.csdn.net/weixin_34195364/article/details/91445085)

## `tailwindcss` auto-completion not work with WebStorm

It's a very tricky problem upon I turned into `create-react-app + typescript + tailwindcss` development.

First, I just point out why does It happen -- It's all about compatibility(兼容性) problem, which has been a stereotype(陈词滥调).

All should thank to one inspirational(有启发性的) article when one managed to find the bug position in the dyed(染色的) log file after when he feedback to the jetbrains support team who asked him for the log which can be found here as the following screenshot:

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639848214052-ad5ea63d44b964202f042062872eb4a5566b6500f27c74ecef9cfb294b8ae5e0.png" width="720" />

And how to dye our target programme? It's rather easy just to modify the content of `Debug Log Settings`, i.e. adding `#com.intellij.taiwind:trace`.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639848335463-824b47c96e63347bda0e137a39ce562eef3dd38f9290b1754e5adbba6cb93cbc.png" width="720" />

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639848360081-47fea27dc1486646fcc1b7143c5ad4552102f78d57b1901ac53f3e2a564664d9.png" width="720" />

Then I opened the log file in VSCode, and find the keyword of `tailwindcss` from down to top. Luckily, the last one is just what I am looking for -- a perfect error -- which indicates me to upgrade the `postcss` package up to 8.

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639848565530-414ed558a8463bec60bd698f4b66430df8f45cadb3ce952838cc71b2e2c9a5b6.png" width="720" />

Hence, after some `delete and reinstall` some packages, especially the evil `carco` which is unnecessary and harmful, and I finally managed to own the done-right tailwindcss intellisense.

Thanks again the one who 'taught' me to dye the log which is rather beneficial to me!

ref:

- [Webstorm 排查插件问题(tailwindcss 不智能提示) - 掘金](https://juejin.cn/post/6946605866460119077)
