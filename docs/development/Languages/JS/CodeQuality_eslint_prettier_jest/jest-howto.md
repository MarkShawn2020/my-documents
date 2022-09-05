# jest howto

[toc]

## top js test frameworks

top 1: `jest`

top 2: `mocha`

others are: `jsamine`, `tape`, etc.

In project of `rehype-shortcodes`, I found them using `tape` and seems cabinet(小巧的) and output-friendly.

Nevertheless, I used to use `jest` and `ts-jest` which is mature and strong. So I didn't pretend to dive into `tape` deeper.

## `jest` ESM support

1. Add `"type": "module"` in package.json
2. Add `transform: {}` in `jest.config.js`
3. use one of the following approach to run jest in `esm` mode:
   1. `node --experimental-vm-modules ./node_modules/.bin/jest JS_FILE`
   2. `NODE_OPTIONS=--experimental-vm-modules npx jest JS_FILE`
   3. Add `"scripts": {"test": "NODE_OPTIONS=--experimental-vm-modules npx jest"}` in `package.json`, then run `test JS_FILE` in command line
   4. Add `--experimental-vm-modules` in webstorm jest configuration, and then click run button: <img alt="picture 35" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640519248016-jest-howto-009c6056a3584775b30ffeafabe837f98f2218515f396a293faf23d7676c2ef8.png" width="480" />

ref:

official answer of jest

- [ECMAScript Modules · Jest](https://jestjs.io/docs/ecmascript-modules)

stackoverflow solution

- [javascript - How to use ESM tests with jest? - Stack Overflow](https://stackoverflow.com/questions/68956636/how-to-use-esm-tests-with-jest)

## `jest` + `typescript` + `ESM`

```js
// jest.config.js
module.exports = {
  preset: 'ts-jest/presets/default-esm', // or other ESM presets
  globals: {
    'ts-jest': {
      useESM: true,
    },
  },
  moduleNameMapper: {
    '^(\\.{1,2}/.*)\\.js$': '$1',
  },
};
```

ref:

recommend:

- [ESM Support | ts-jest](https://kulshekhar.github.io/ts-jest/docs/next/guides/esm-support/)
