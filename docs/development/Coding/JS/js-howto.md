# js-howto

## BEST-PRACTICE: js parse float to int

ref:

- [Convert a Float Number to Int in JavaScript | Delft Stack](https://www.delftstack.com/howto/javascript/javascript-float-to-int/)

## TODO: prettier plugin of `decorators`

This experimental syntax requires enabling one of the following parser plugin(s): 'decorators-legacy, decorators' (9:0)

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641894406039-133b59aa7e51366d78542af9a0cf0f91344d4a17eace2e1fed1bd0110d8ffa9c.png" />

## jsdoc

ref:

- [Automate JavaScript API Documentation with JSDoc ← Alligator.io](https://alligator.io/js/jsdoc/)

## modify `process.env`

Here explained why the variable cannot change since it has been compiled into a const string. [environment variables - Can't set values on `process.env` in client-side Javascript - Stack Overflow](https://stackoverflow.com/questions/52871895/cant-set-values-on-process-env-in-client-side-javascript) <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641239508558-76650a9fe7ba3910d2a30f7ffee4b20c4f478b4e69518fe537a4806cd349202a.png" width="480" />

And here's also the same problem but caused `terser` plugin not work: [Error happened when processing on the assignment statement of 'process.env'. · Issue #736 · terser/terser](https://github.com/terser/terser/issues/736)

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641239575492-9178f1c0c29d71302c0179c03bf7d72589ae8380c864297ae8ad99357c4afa95.png" width="480" />

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641239637983-fabb9d225b44656dfda1119765d0ff09d43a2ea4aa9a3e84870be74c6b723dcc.png" width="480" />

- [Handling process.env.SOME_UNDEFINED_KEY as undefined with DefinePlugin · Issue #12444 · webpack/webpack](https://github.com/webpack/webpack/issues/12444)

And I finally found one superb solution:

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641242384770-1735c971e0dc4c8544f7eec28eab5b84147af46e6063203370398c87a0ced622.png" width="480" />

- [node.js - How to forbid replacing process.env variables during compilation in webpack? - Stack Overflow](https://stackoverflow.com/questions/53801753/how-to-forbid-replacing-process-env-variables-during-compilation-in-webpack/69844926#69844926)

So that:

```js
// .erb/configs/webpack.config.main.prod.ts:75

    new webpack.DefinePlugin({
      VAR_ENV: 'process.env',
    }),

```

Then I can use like the following, in which I can change `process.env` into `dbUrl`, and passed the compile time check.

```ts
VAR_ENV.DATABASE_URL = dbUrl;
```

## node exec sub commands

I got to the conclusion that I should choose `exec` instead of `execFile` for a more universal use.

The core usage may be:

```js
const {exec} = require('child_process');
exec('cat *.js missing_file | wc -l', (error, stdout, stderr) => {
  if (error) {
    console.error(`exec error: ${error}`);
    return;
  }
  console.log(`stdout: ${stdout}`);
  console.error(`stderr: ${stderr}`);
});
```

ref:

- [Child process | Node.js v17.3.0 Documentation](https://nodejs.org/api/child_process.html)

- [node.js - exec vs execFile nodeJs - Stack Overflow](https://stackoverflow.com/questions/46445805/exec-vs-execfile-nodejs)

## webpack

ref:

A good article thoroughly talked about what's webpack and how to use it.

- [How to transpile ES modules with webpack and Node.js - LogRocket Blog](https://blog.logrocket.com/transpile-es-modules-with-webpack-node-js/)

## receive arg from command line [Standard Method (no library)]

```sh
# the first arg
process.env.argv[2]
```

The arguments are stored in `process.argv`

Here are the node docs on handling command line args:

> process.argv is an array containing the command line arguments. The first element will be 'node', the second element will be the name of the JavaScript file. The next elements will be any additional command line arguments.

```js
// print process.argv
process.argv.forEach(function (val, index, array) {
  console.log(index + ': ' + val);
});
```

```sh
node process-2.js one two=three four
```

This would generate:

1. node
2. /Users/mjr/work/node/process-2.js (the file)
3. one (the first argv)
4. two=three
5. four

ref:

- [javascript - How do I pass command line arguments to a Node.js program? - Stack Overflow](https://stackoverflow.com/questions/4351521/how-do-i-pass-command-line-arguments-to-a-node-js-program)

## change string to number [DON'T]

The discussion suggests me not to change a string to number.

ref:

- [Angular typescript convert string to number - Stack Overflow](https://stackoverflow.com/questions/66052793/angular-typescript-convert-string-to-number)

- [angular - How to properly change a variable's type in TypeScript? - Stack Overflow](https://stackoverflow.com/questions/33615680/how-to-properly-change-a-variables-type-in-typescript)

## best practice to use Exceptions

### catch error

```js
function handleError() {
  try {
    throw new RangeError();
  } catch (e) {
    switch (e.constructor) {
      case Error:
        return console.log('generic');
      case RangeError:
        return console.log('range');
      default:
        return console.log('unknown');
    }
  }
}

handleError();
```

### extend error

```js
class MyError extends Error {
  constructor(message) {
    super(message);
    this.name = 'MyError';
  }
}
```

ref:

- [exception - Proper use of errors - Stack Overflow](https://stackoverflow.com/questions/23790509/proper-use-of-errors)

- [exception - What's a good way to extend Error in JavaScript? - Stack Overflow](https://stackoverflow.com/questions/1382107/whats-a-good-way-to-extend-error-in-javascript)

## [HANDBOOK] fs read file, async and part

TODO: From my point of view, the `fs.createReadStream` is a ???

ref:

- [Promise - JavaScript | MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)

- [node.js - How to read file with async/await properly? - Stack Overflow](https://stackoverflow.com/questions/46867517/how-to-read-file-with-async-await-properly)

- [javascript - node.js/ read 100 first bytes of a file - Stack Overflow](https://stackoverflow.com/questions/23720032/node-js-read-100-first-bytes-of-a-file)

- [javascript - how to use async/await with fs.createReadStream in node js - Stack Overflow](https://stackoverflow.com/questions/58431076/how-to-use-async-await-with-fs-createreadstream-in-node-js)

- [Node.js Stream(流) | 菜鸟教程](https://www.runoob.com/nodejs/nodejs-stream.html)

- [JavaScript Promises - reject vs. throw - Stack Overflow](https://stackoverflow.com/questions/33445415/javascript-promises-reject-vs-throw)

- [javascript - Why does Node.js' fs.readFile() return a buffer instead of string? - Stack Overflow](https://stackoverflow.com/questions/6456864/why-does-node-js-fs-readfile-return-a-buffer-instead-of-string)

## csv read and parse

### modify header

buffer padding algorithm [Node.js buffer with padding (right justified fill) example](https://gist.github.com/miguelmota/b296c10b68a91fa6041297a6778de81e)

```js
const buf = Buffer.alloc(32);
const a = Buffer.from('1234', 'hex');
a.copy(buf, buf.length - a.length);
console.log(buf.toString('hex')); // 0000000000000000000000000000000000000000000000000000000000001234
```

[fs.read](https://nodejs.org/api/fs.html#:~:text=subsequent%20read%20operations.-,fs.read,-(fd%2C%20buffer%2C%20offset)

[fs.write](https://nodejs.org/api/fs.html#:~:text=its%20original%20name-,fs.write,-(fd%2C%20buffer%5B%2C%20offset)

After I did a hard modification, a new problem arises from, i.e. ~~blank~~ placeholder (update: it's `zero`).

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641750359863-e93a5d344bd4394c2e36f819acff8e5218a0041067c045bd39038dfa03cd2c40.png" />

And the solution is replacing there blanks, ref: [node.js - Removing a null character from a string in javascript - Stack Overflow](https://stackoverflow.com/questions/22809401/removing-a-null-character-from-a-string-in-javascript)

```ts
// 1.
s.replace(/\0/g, '');

// 2.
s.replaceAll('\0', '');
```

Then I need to use this transform into `fast-csv`:

```ts
// src/main/modules/parseFile/center.ts:78
    .pipe(
      csv.parse({
        headers: (headers) => headers.map((h) => h?.replace(/\0/g, '')),
      })
    ) // PR: header true/false; ref: https://stackoverflow.com/a/22809513/9422455
```

However, I thought this a little not elegant, so I came up a new idea:

```ts
// src/main/modules/parseFile/handler/checkCsvEncoding.ts:85
const bufToWrite = Buffer.alloc(L);
const tempBuf = iconv.encode(s, encoding);
const offset = L - tempBuf.length;
tempBuf.copy(bufToWrite, offset);
fs.write(fd, bufToWrite, 0, L, 0, (err) => {
  // prettier-ignore
  return !err? resolve({
    useIconv: encoding === ValidEncoding.gbk, 
    offset
    }) : reject(new GenericError(errorModifyingHeader, `replace error: ${err}, string: ${s}, bufToWrite: ${bufToWrite}`));
});
```

I saved the offset, so that when I open this file again, I can use this offset quickly located the real start without `\0`.

And it did work!

#### then, what about repeatability?

After a battle of mind, I gave up with the wonderful write back idea, since it would destroy the raw data and inflexible or costly to re-use the sheet.

I then do not modify the data, but to use header map:

```ts
// src/main/modules/parseFile/center.ts:72
const progress = new ParsingProgress();
const headers = (headers) =>
  headers.map((header) => (header === SIGNAL_ID ? COL_ID : header));

s2.pipe(
  new SizeTransformer(fs.statSync(fp).size, (pct) =>
    progress.updateSizePct(pct),
  ),
).pipe(csv.parse({headers})); // PR: header true/false; ref: https://stackoverflow.com/a/22809513/**9422455**
```

### `node-csv` or `fast-csv`

First, I chose `csv` since its star is more than `fast-csv`'s.

<img alt="picture 71" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640635030511-csv-d2df9d938bfadf6af66e0e1d9fe1a5dee37891c7455eedbe84f048ff4227f119.png" width="480" />

However, I soon happened to find it's too raw to chinese file parse, since the `csv` can't handle the `gbk` problem, at least, not automatically. <img alt="picture 73" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640638212636-csv-a8397a9973387672ab6bbf9feee651be1d97a47c9e8a255b125ea62feb613329.png" width="480" />

And the behind reason is that the `fs.createReadStream` doesn't support our `gbk` format. <img alt="picture 72" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640638161109-csv-208716b9781a4ed34babbb56fef9cf4c214377689e850fc35c14b5b5c0d4ab5a.png" width="480" />

As a contrast, the `fast-csv` helped me a lot.

If I just use `fast-csv` to read `gbk` file, then the default garbled(乱码) would be shown(but not error), which would output correctly if we added the pipe of `iconv` conversion.

```ts
import * as csv from '@fast-csv/parse';
import * as fs from 'fs';
import iconv from 'iconv-lite';

fs.createReadStream('./samples/erp_md.csv')
  .pipe(iconv.decodeStream('gbk'))
  .pipe(iconv.encodeStream('utf-8'))
  .pipe(csv.parse({headers: true}))
  .on('error', (error) => console.error(error))
  .on('data', (row) => console.log(row))
  .on('end', (rowCount: number) => console.log(`Parsed ${rowCount} rows`));
```

In conclusion, maybe I don't know whether the speed when handling data of `fast-csv` is faster than the `node-csv`, but it does free me a lot from annoying encoding problems, which is also `fast`!

I then would not hesitate to choose `fast-csv`.

ref:

- [adaltas/node-csv: Full featured CSV parser with simple api and tested against large datasets.](https://github.com/adaltas/node-csv)

- [CSV Project - Node.js CSV package](https://csv.js.org/)

- [csv-parse vs fast-csv vs node-csv | npm trends](https://www.npmtrends.com/csv-parse-vs-fast-csv-vs-node-csv)

- [node.js - Parsing a CSV file using NodeJS - Stack Overflow](https://stackoverflow.com/questions/23080413/parsing-a-csv-file-using-nodejs)

- [csv-parse vs fast-csv vs node-csv | npm trends](https://www.npmtrends.com/csv-parse-vs-fast-csv-vs-node-csv)

- [node.js - Parsing a CSV file using NodeJS - Stack Overflow](https://stackoverflow.com/questions/23080413/parsing-a-csv-file-using-nodejs)

- [Node.js 解决 csv 文件乱码的两种办法 | 全栈渐进之路](https://brickyang.github.io/2018/03/10/Node-js-%E8%A7%A3%E5%86%B3-csv-%E6%96%87%E4%BB%B6%E4%B9%B1%E7%A0%81%E7%9A%84%E4%B8%A4%E7%A7%8D%E5%8A%9E%E6%B3%95/)

`iconv`解码`gbk`必备！

- [iconv-lite - npm](https://www.npmjs.com/package/iconv-lite)

- [(20 条消息) nodejs 读取 csv 中文乱码\_CaanDoll 的博客-CSDN 博客](https://blog.csdn.net/CaanDoll/article/details/84639668)

### `fast-csv` problem of quotes

ref:

- [Getting Started | Fast-CSV](https://c2fo.github.io/fast-csv/docs/introduction/getting-started)

### csv not closed

I did test, and to find that the stream is destroyed but not closed, since read by block but parse by row.

<img alt="picture 34" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/js-howto-1641589088462-aef98f82fa7119db7eff3535c4bbedf1b331c90e65ea4b9fda1618b53dc1b47c.png" />

So the better way is to detect header first.

## run js in different envs

### browser env

just open the chrome, and the console of it.

### node env

```sh
node .
```

### node + esm

```sh
node --experimental-modules .
```

And then, in the console, use dynamic import like this: `var s; import("XXX").then(r => s.default)`.

!!!warning javascript doesn't support `esm`

ref:

- [dynamic import can't be used in the REPL · Issue #19570 · nodejs/node](https://github.com/nodejs/node/issues/19570)

### node + esm + ts

1. install `ts-node`

```sh
npm i -D ts-node
tsc --init
```

2. modify `tsconfig.json` file

```json
// tsconfig.json
{
  "module": "esnext" /* Specify what module code is generated. */,
  "modulesolution": "node" /* Specify how TypeScript looks up a file from a given module specifier. */,
  "esModuleInterop": true /* Emit additional JavaScript to ease support for importing CommonJS modules. This enables `allowSyntheticDefaultImports` for type compatibility. */
}
```

3. run `node --loader ts-node/esm FILE` instead of `ts-node FILE`

ref:

- [Can't run my Node.js Typescript project TypeError [ERR_UNKNOWN_FILE_EXTENSION]: Unknown file extension ".ts" for /app/src/App.ts - Stack Overflow](https://stackoverflow.com/questions/62096269/cant-run-my-node-js-typescript-project-typeerror-err-unknown-file-extension)

## use `__filename` and `__dirname` in ESM

```js
import {dirname} from 'path';
import {fileURLToPath} from 'url';

const __dirname = dirname(fileURLToPath(import.meta.url));
```

ref:

- [ecmascript 6 - Alternative for \_\_dirname in Node.js when using ES6 modules - Stack Overflow](https://stackoverflow.com/questions/46745014/alternative-for-dirname-in-node-js-when-using-es6-modules)
