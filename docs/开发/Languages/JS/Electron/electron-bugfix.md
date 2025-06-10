# electron-bugfix

1. [:white_check_mark: when mock/test, 'Electron failed to install correctly, please delete node_modules/electron and try installing again'](#white_check_mark-when-mocktest-electron-failed-to-install-correctly-please-delete-node_moduleselectron-and-try-installing-again)
   1. [conclusion](#conclusion)
2. [electron-rebuild error](#electron-rebuild-error)
3. [:white_check_mark: can't resolve `rebuild` in `postinstall`](#white_check_mark-cant-resolve-rebuild-in-postinstall)
4. [:white_check_mark: webpack dev server](#white_check_mark-webpack-dev-server)
5. [:white_check_mark: registry diff caused build error](#white_check_mark-registry-diff-caused-build-error)
6. [:white_check_mark: native module](#white_check_mark-native-module)
   1. [electron build sqlite3](#electron-build-sqlite3)
   2. [`electron-builder install-app-deps` error](#electron-builder-install-app-deps-error)
7. [:white_check_mark: windows cannot select file](#white_check_mark-windows-cannot-select-file)
8. [:white_check_mark: Can't use `ContextBridge` which `ContextIsolation is true`](#white_check_mark-cant-use-contextbridge-which-contextisolation-is-true)
   1. [Official Documentation](#official-documentation)
   2. [A simple solution: give up using `ContextBridge`](#a-simple-solution-give-up-using-contextbridge)
   3. [A seemly good solution: `nodeIntegration: true; contextIsolation:false`](#a-seemly-good-solution-nodeintegration-true-contextisolationfalse)
   4. [A more sophisticated solution: based on `WebPack`](#a-more-sophisticated-solution-based-on-webpack)
      1. [add `global = globalThis` in `index.html`](#add-global--globalthis-in-indexhtml)

## :white_check_mark: when mock/test, 'Electron failed to install correctly, please delete node_modules/electron and try installing again'

<img alt="picture 28" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641586545015-6e15ba21daa92b4474735f4c9e8513259f60d365301b0847b1935bc0c9f356dd.png" />

I didn't find any `path.txt` for electron, even for any package. <img alt="picture 29" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641586908495-225613deee0af42af0e1763c04e1d28fecace907506d0a9ce2edfab1fca0d08a.png" />

However, if I explore global electron, then it has (ref: [Browse an installed package](https://www.google.com/search?q=enter+npm+package#:~:text=Browse%20an%20installed%20package)):

<img alt="picture 30" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641587194504-cd78e81a21e2871fbc517996c2ec6cdccb93294e0e75349685c9547fbcee452f.png" />

As a contrast:

<img alt="picture 31" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641587311833-b8434599978a2ad98b4f7efac3068156bb05fe825ce184c712396786863a9700.png" />

What's interested, if I use `node install.js` as suggested by [node.js - Electron and Webpack ENOENT: no such file or directory, open '/path.txt' - Stack Overflow](https://stackoverflow.com/questions/39419814/electron-and-webpack-enoent-no-such-file-or-directory-open-path-txt):

<img alt="picture 32" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641587420146-6b262ffe8de375b236a000201db95cd66118251ecbcdf0ac382927b62ddbbdd1.png" />

Then things are all ok! <img alt="picture 33" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641587499881-ba1d30816abdb3883ca90c59e8f64e060372cc727679a9877faa31dca33a757f.png" />

### conclusion

If we want to use `electron` for project mock, we may activate it using:

```sh
cd node_modules/electron
node install.js
```

Or, according to the source code, we can provide an environment variable:

```sh
ELECTRON_OVERRIDE_DIST_PATH=XXXX
```

## electron-rebuild error

one possible problem is about `registry`.

<img alt="picture 21" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641561636763-a8c8998254763dba35d2279c17d5f846465115a419a442bcb164ed03563392df.png" />

## :white_check_mark: can't resolve `rebuild` in `postinstall`

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641554575880-abfb7317cd46fb8e54fd6a54d48c33597f7c32cc5c8567df776bfedf3a758d7e.png" />

In this article [ERROR in dll renderer Module not found: Error: Can't resolve 'undefined' · Issue #43 · rvpanoz/luna](https://github.com/rvpanoz/luna/issues/43), which occurs the problem a bit like me, and its solution is to remove the cannot-resolve package of `undefined`.

So I learned it, and do find a package named as `rebuild` in my `package.json` file.

<img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641554293693-2647abc6e3152709bae4155a7628ea9db4d0d69844bfbc7706f1e57f5f965d8d.png" />

Then I removed it, and re `npm run postinstall`, and it succeeded!

<img alt="picture 19" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641554431120-f1a659286619fcb90a8781fa7cb20e0e011ae380b07a536362ef114446f1d25b.png" />

## :white_check_mark: webpack dev server

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641553334892-6e7bf907b20bb5557bb63f7e9cb70ebe939b9edd545c64d15a51cbcb6944975b.png" />

solution:

1. add `// @ts-ignore`, official way

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641553995920-a435fa37225e7ff6380aa1dc30a9e29e7533e2b00c84ff639c1785f478184854.png" />

2. add an extended interface, at: https://github.com/DefinitelyTyped/DefinitelyTyped/issues/27570#issuecomment-474628163

ref:

- [[@types/webpack] 'devServer' does not exist in type 'Configuration' · Issue #27570 · DefinitelyTyped/DefinitelyTyped](https://github.com/DefinitelyTyped/DefinitelyTyped/issues/27570)

## :white_check_mark: registry diff caused build error

<img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641551393710-9a1c96847a7e7154ba7e311576463c6f91dc3edc2d7fed349bbfc71b82b3c923.png" />

## :white_check_mark: native module

The proper way to deal with native module is to:

1. install it into devDependencies in the project root
2. install it as a dependency in the release/app

ref:

- [Warn user when installing native dependency to `./package.json` · Issue #1171 · electron-react-boilerplate/electron-react-boilerplate](https://github.com/electron-react-boilerplate/electron-react-boilerplate/issues/1171)

### electron build sqlite3

```sh
electron-rebuild -f -w sqlite3
```

'-f' means 'force' '-w' means 'module'

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641561684721-9a4867d960620d29d17b1c52d3a6d39ea1dd60c726529e0e08db89b90f386421.png" />

ref:

- [electron-rebuild - npm](https://www.npmjs.com/package/electron-rebuild?activeTab=readme)

- [electon-rebuild fails for sqlite3 · Issue #322 · electron/electron-rebuild](https://github.com/electron/electron-rebuild/issues/322)

- [Help me use Electron! · Issue #126 · JoshuaWise/better-sqlite3](https://github.com/JoshuaWise/better-sqlite3/issues/126)

### `electron-builder install-app-deps` error

can change the `electron-builder` into `electron-rebuild`.

<img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641553039789-8c866cee84f806b3a58d321ac8ae12e718fb50e3598f2e3ee963e1123c4ab9af.png" />

core ref:

- [[install-app-deps] what does it do? · Issue #1906 · electron-userland/electron-builder](https://github.com/electron-userland/electron-builder/issues/1906)

## :white_check_mark: windows cannot select file

This is a feature/restriction in windows platform.

The solution is to use one of `openFIle` and `openFolder`.

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-bugfix-1641486288453-b22352e5583541ceb8b3314f58d5863e0875d7631c94f21d8ab40eb236ea2aeb.png" />

ref:

- [dialog | Electron](https://www.electronjs.org/zh/docs/latest/api/dialog#dialogshowopendialogsyncbrowserwindow-options)

- [[Bug]: showOpenDialog with openFile and openDirectory only selects directories in Windows · Issue #30651 · electron/electron](https://github.com/electron/electron/issues/30651)

- [\_FILEOPENDIALOGOPTIONS (shobjidl_core.h) - Win32 apps | Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/ne-shobjidl_core-_fileopendialogoptions)

## :white_check_mark: Can't use `ContextBridge` which `ContextIsolation is true`

### Official Documentation

- [Context Isolation | Electron](https://www.electronjs.org/docs/latest/tutorial/context-isolation)

### A simple solution: give up using `ContextBridge`

In this article, the one who happened to the same issue finally uses only `ipcMain` and `ipcRenderer` with no `ContextBridge` set.

- [Uncaught ReferenceError: global is not defined · Issue #10035 · webpack/webpack](https://github.com/webpack/webpack/issues/10035)

Although it's OK, since the `ipcMain - ipcRenderer` solution can do almost anything rather than base on a `ContextBridge`.

### A seemly good solution: `nodeIntegration: true; contextIsolation:false`

- [Electron 12+ 出现 require is not defined 报错解决 - 轶哥](https://www.wyr.me/post/680)

### A more sophisticated solution: based on `WebPack`

- [javascript - Getting ReferenceError: require is not defined when passing contextIsolation: true with preload script - Stack Overflow](https://stackoverflow.com/questions/69183918/getting-referenceerror-require-is-not-defined-when-passing-contextisolation-tr)

- [Uncaught ReferenceError: global is not defined · Issue #10035 · webpack/webpack](https://github.com/webpack/webpack/issues/10035)

- [webpack - ReferenceError: global is not defined at eval - Stack Overflow](https://stackoverflow.com/questions/45175521/referenceerror-global-is-not-defined-at-eval)

#### add `global = globalThis` in `index.html`

- [javascript - React and Electron with Draft.js: "Global is not defined" - Stack Overflow](https://stackoverflow.com/questions/65586906/react-and-electron-with-draft-js-global-is-not-defined)
