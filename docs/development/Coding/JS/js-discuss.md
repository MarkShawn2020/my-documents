# js discuss

[toc]

## `then-catch` vs `try-catch`

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641809779883-c7d09989902e6954494a736f27aa0a6d7543634380efa56c31b33e746b447575.png" />

## Prettier comment alignment

It can't be done in prettier, since the developers consider it as a sophisticated task, and also not consistent with their option philosophy.

<img alt="picture 49" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641728758989-050575f27ccd7519f8c804cbdaedd189053b9c610dc9a50022f81948a22392c9.png" />

<img alt="picture 50" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641728763921-c9e32578e1ba7488eccbdd62bd33c00728f976d3e5bc18da1c88fe2f47405e78.png" />

<img alt="picture 52" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641728776000-36a88c1b29c6642190b794fef9ef2931d14ded06848061f46da80c4872410ab9.png" />

ref:

- [Feature request: vertical alignment. · Issue #350 · prettier/prettier](https://github.com/prettier/prettier/issues/350)

- [Handle block scoped alignement formatting · Issue #188 · prettier/prettier](https://github.com/prettier/prettier/issues/188)

- [Option Philosophy · Prettier](https://prettier.io/docs/en/option-philosophy.html)

## Excel Select

Since there are too many excel packages, not unified, unknown problems, I decided to not use excel.

<img alt="picture 27" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641582345747-cff2c666104fbcd0a3e8318d6c6b3e788fae74aac3fabeaad528426426391c1f.png" />

<img alt="picture 26" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641582333762-9af3250d78cf646a2beb7915c63f2e9d979b77458639db916328e6aaab0c258e.png" />

After all, to them, using excel or not, doesn't differ too much. But to me, not.

## TODO: Database Select: `node-sqlite3`, `better-sqlite3`, `typeorm`, `prisma`

A wonderful and respective thing the `typeorm` did, is to provide developers with a clarified, transparent, and full api, which is hardly to see in prisma or so packages.

<img alt="picture 23" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641565563329-0b89484f2919f47e6775fb78384ff17fbd1f56d9d8a04d0d40c886ca435e95a2.png" />

At least, from my own experience, the prisma is even still hardcoding their database query status, which seems unacceptable for those like me to develop a robust application.

## [ERR_REQUEST_ESM]

If your code copied from some place using require, and you can't run it now out of `ERR_REQUEST_ESM`, **it doesn't mean the code is wrong but maybe mean it's written in the `node v2` times**.

<img alt="picture 32" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640506880513-esm-and-cjs-e78aac5c0197ac862b3ffd79928281bbef7aa3ddb2b174aa275b49e61b570e6a.png" width="480" />

<img alt="picture 30" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640506761078-esm-and-cjs-99e60788adab33f6ce6096f54a34d91ff2ef29f7249f762a5e745d95005134e4.png" width="480" />

<img alt="picture 31" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640506791606-esm-and-cjs-73099ad6f0939938ecc3952806c375622188afc3ee3261964aedaf95d653dcfc.png" width="480" />

And now, the simplest remedy you can use is to change all the `require` into `import` like this:

<img alt="picture 33" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640507226907-esm-and-cjs-f4cf785aa0b5e5377c0ea6ebee710ea62c939b538d1f42e01cc67f6f7af59c76.png" width="480" />

And change the file extension from `.js` to `.mjs`, then things is ok: <img alt="picture 34" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640507277192-esm-and-cjs-25a0f1a62101aba503461e3dc2b9f3ef77763e2e0d535869b4d4730a45d3c05b.png" width="480" />

ref:

- [javascript - Error [ERR_REQUIRE_ESM]: require() of ES Module not supported - Stack Overflow](https://stackoverflow.com/questions/69081410/error-err-require-esm-require-of-es-module-not-supported)

## cjs 和 mjs 不要混用

目前我经过测试，已经充分认识到 cjs 和 mjs 的不可调和矛盾了，甚至 babel 也不方便解决这个问题。

接下来要注意两点，第一点就是代码导入时`require`和`import`不要混用，第二点也是最关键的一点，那就是对每个新包要确认一下它是否加了`"type": "module"`的属性，尤其是 webpack 的那些包，基本都是 full ESM 的...对 Electron 极其不友好。。。

## babel 的失败尝试

```sh
babel src --no-babelrc --out-dir lib/es --extensions '.ts,.tsx' --ignore '**/*.spec.ts' --config-file ./.babelrc.es
```

```json
// ./.babelrc.es
{
  "ignore": ["node_modules/**/*"],
  "presets": [
    ["@babel/preset-typescript"],
    [
      "@babel/preset-env",
      {
        "loose": true,
        "modules": false
      }
    ],
    "@babel/preset-react"
  ],
  "plugins": [
    "@babel/plugin-proposal-class-properties",
    "babel-plugin-add-module-exports",
    "@babel/plugin-transform-classes"
  ]
}
```

ref:

- [es6 modules - How can I use an ES6 import in Node.js? - Stack Overflow](https://stackoverflow.com/questions/45854169/how-can-i-use-an-es6-import-in-node-js)

- [Node.js 如何处理 ES6 模块 - 阮一峰的网络日志](https://www.ruanyifeng.com/blog/2020/08/how-nodejs-use-es6-module.html)

- [johnloy/esm-commonjs-interop-manual](https://github.com/johnloy/esm-commonjs-interop-manual)

- [Transpile to ES modules with Babel](https://krasimirtsonev.com/blog/article/transpile-to-esm-with-babel)

## database-orm: prisma vs typeorm

- [prisma/prisma: Next-generation ORM for Node.js & TypeScript | PostgreSQL, MySQL, MariaDB, SQL Server, SQLite & MongoDB (Preview)](https://github.com/prisma/prisma)

## `interface` vs `abstract class`

It's very interesting to see how different is between an interface and an abstract class.

For me, the project of `hjxh_express_match`, interface is enough, and provides me more advantage in running since they are workded ony in compile stage.

ref:

- [oop - What is the difference between interface and abstract class in Typescript? - Stack Overflow](https://stackoverflow.com/questions/50110844/what-is-the-difference-between-interface-and-abstract-class-in-typescript)

## eslint catch/then/return

In fact, it's a pipe, just like `case`, which I know it until today.

So, we must return something in `catch/then`, in order not to goto next pipe.

Also, put `then` before `catch` is sometimes good since `catch` can capture the error caused by inner of `then`.

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641042487784-79a3ad412d849352a555d4d0cf5c0cb2d3463f057473eedd236900ea0d4b6faa.png" width="480" />

Finally, I wrote like this (with eslint `'no-useless-return': 'off'` disabled): <img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641042720348-42db9bd503053b892b699543df353142eecfda3b1cdfc15ad790231596834ba1.png" width="480" />

ref:

- [eslint-plugin-promise/catch-or-return.md at development · xjamundx/eslint-plugin-promise](https://github.com/xjamundx/eslint-plugin-promise/blob/development/docs/rules/catch-or-return.md)

## Avoid hardcoding of Prisma Error codes

I first followed the official documentation, and reviewed the section of `error codes`, however didn't get any message on how to import them except hard coding.

And then I searched the source code, but in vain:

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641041427075-47a1ee3ffdaac0a145f37e2156479c4bae379d768b5cc0910ce6b738942806fc.png" width="480" />

And its' shocking to me that I even couldn't find the `P2002` error since it's the error of `duplicate id`, which captured by my programme.

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641041566110-bdccc7860b53fac834aee51204ea3b0dc77d3d6276bc60816e683ce7225e0732.png" width="480" />

Whereas, I can find such as `P1003`, and no exception: without `P1000` and other `P100X` codes.

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641041505840-49ca86c607dcd0cf605643f9e799509e83300fcd6cd25d368673e2c11b7c5935.png" width="480" />

And finally I tried to search in the github issues.

At first, I got nothing.

Then I use `is:issue in:title code`, and then quickly find one which is what I am expecting to.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641041256885-fdcc576ad7ed19b0ad896b55be3f93885bf98dab86f1bf3c425bd09a22a8a9a0.png" width="480" />

But it's so sad that no reply on this issue.

I added one comment then.

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-discuss-1641041711825-5f637e4af061a2d736b3cd67e77af0c4655de328bdd0d2f945230bea70694847.png" width="480" />

ref:

- [Prisma error reference (Reference) | Prisma Docs](https://www.prisma.io/docs/reference/api-reference/error-reference#error-codes)

- [Export error code constants in npm package · Issue #10394 · prisma/prisma](https://github.com/prisma/prisma/issues/10394)

## `Enum` or `Union / Array`

for literal const (like `redux`):

```ts
export const Ping = 'Ping';
export type Ping = typeof Ping;

export const RequestSelectFile = 'RequestSelectFile';
export type RequestSelectFile = typeof RequestSelectFile;

export const RequestReadFile = 'RequestReadFile';
export type RequestReadFile = typeof RequestReadFile;

export type Channels = Ping | RequestSelectFile | RequestReadFile;
```

for iterating:

```ts
const buttonStatus = ['HIDDEN', 'ENABLED', 'DISABLED'] as const;
// Notice that the array and type can have the same name if you want
type ButtonStatus = typeof buttonStatus[number];
```

for switch

```ts
// Union types
switch (key) {
  case 'HIDDEN': return ...;
  case 'ENABLED': return ...;
  case 'DISABLED': return ...;
  // Notice that there's no default case
}

// Enums
switch (key) {
  case ButtonStatus.HIDDEN: return ...;
  case ButtonStatus.ENABLED: return ...;
  case ButtonStatus.DISABLED: return ...;
  default: return ...;
}
```

ref:

- [Should You Use Enums or Union Types in Typescript?](https://blog.bam.tech/developer-news/should-you-use-enums-or-union-types-in-typescript)

## `for...of` or `.forEach`

The main debate is that `for...of` is a 'loop', while `forEach` is a 'iteration', which seems faster since it can be parallel.

Although I prefer `for...of` since I learned it from `python` and `C11`.

ref:

- [guard-for-in - Rules - ESLint - Pluggable JavaScript linter](https://eslint.org/docs/rules/guard-for-in)

- [Using 'ForOfStatement' is not allowed (no-restricted-syntax) · Issue #1271 · airbnb/javascript](https://github.com/airbnb/javascript/issues/1271)
