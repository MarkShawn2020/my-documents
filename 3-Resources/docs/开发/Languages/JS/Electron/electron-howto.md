# electron howto

1. [electron best practice](#electron-best-practice)
   1. [design of dependency workflow](#design-of-dependency-workflow)
   2. [app path, storing db, log, etc](#app-path-storing-db-log-etc)
   3. [log into file](#log-into-file)
2. [electron test](#electron-test)
3. [sqlite best practice](#sqlite-best-practice)
   1. [don't use relative path as sqlite position](#dont-use-relative-path-as-sqlite-position)
4. [log electron](#log-electron)
   1. [TODO: idealog color configuration](#todo-idealog-color-configuration)
5. [build for Windows on Mac](#build-for-windows-on-mac)
6. [build native dependencies and for multi platforms](#build-native-dependencies-and-for-multi-platforms)
7. [custom app logo](#custom-app-logo)
   1. [a good start](#a-good-start)
   2. [customize icon for unpacked app](#customize-icon-for-unpacked-app)
   3. [square .icon](#square-icon)
8. [electron-builder `files` map](#electron-builder-files-map)
9. [⭐️⭐️⭐️ debug binary electron](#️️️-debug-binary-electron)
10. [`ipcRenderer` communication](#ipcrenderer-communication)
11. [hwo to use `preload.ts`](#hwo-to-use-preloadts)
    1. [the `preload` script won't run if we just start the main process](#the-preload-script-wont-run-if-we-just-start-the-main-process)
    2. [it's ok when we just use `preload.js`](#its-ok-when-we-just-use-preloadjs)
    3. [what about using a `preload.ts`](#what-about-using-a-preloadts)
       1. [remedy 1, the `tsc` solution](#remedy-1-the-tsc-solution)
    4. [how to remedy the `electron-react-boilerplate` project](#how-to-remedy-the--electron-react-boilerplate-project)

## electron best practice

### design of dependency workflow

<img alt="picture 35" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641598093588-a14b7935afbcc384502d11ece03eab4f86772b695bfe904cd39f8180e934d21b.png" />

How to organize your project structure quite depends on your project scale and realization.

For example, since my project is not too big, I combined almost all the constant variables into one file `const.ts` in each module, containing `channels` , `error_types`, `defined variables`, etc.

### app path, storing db, log, etc

Since the `userData` is the sub path of `appData` with the name of our application, so it's better to put all of our data into `userData`.

```ts
// src/main/base/utils.ts
export const getRootPath = () => app.getPath('userData');

export const getLogPath = () => path.join(getRootPath(), 'main.log');

export const getDbPath = () => path.join(getRootPath(), 'hjxh_data.sqlite');
```

!!!tip If run under the development, since the app is run via `electron .`, so the `userData` points to the `Electron`, which is different from the real build version with the actual name defined in our `package.json/build`.

ref:

- [app | Electron](https://www.electronjs.org/docs/v14-x-y/api/app#appgetapppath)

### log into file

```ts
log.transports.file.resolvePath = () => getLogPath();
log.transports.file.format = '{y}-{m}-{d} {h}:{i}:{s}.{ms} {level}: {text}';
```

ref:

- [megahertz/electron-log: Just a simple logging module for your Electron application](https://github.com/megahertz/electron-log#overriding-consolelog)

## electron test

When all the `ts-node / esm` relative environment is prepared well, there still exists some problems.

For example, concerning about database, since I use it derived from app runtime, and then it would not be mocked unless we start our script as a real electron app rather than a script for unittest.

<img alt="picture 36" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641634838700-73855e534fc5987fd8ae13abe4a70a08ac88078a46f1dafa4857981f244c0484.png" />

## sqlite best practice

### don't use relative path as sqlite position

When using relative path, many packages including system would treat it on the base of current process directory.

However, if the application is build into binary and run by click, then the behavior would become a bit different since e.g. in Mac the application is run with `process.cwd() = '/'`.

And then if we write our data into a sqlite which is created with relative path, such as `./test.db`, then the error would arise up because of permission.

So the best practice is to use `AppData` directory via `path.join(app.getPath('appData'), dbName)`.

## log electron

There are two places where console.log output goes:

If you log in the renderer process, you can see it in the console in the browser window. If you open the dev tools programmatically you can see this console even after building.

If you log in the main process, you can see these messages **if you start the installed app or the unpacked binary via command line**. In windows this would be the app.exe in the win-unpacked directory that electron-builder creates.

Another alternative would be a logger like `electron-log` that writes the log messages into a configured file.

ref:

- [node.js - Electron - Where does logging go? - Stack Overflow](https://stackoverflow.com/questions/51866016/electron-where-does-logging-go/51881711)

And I am surprised to find that it has been in the `electron-react-typescript` boilerplate.

<img alt="picture 9" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641400174339-197d9edb335e41d6d68eae58bf512f6cec757749415defd5fa87fb63c537ac0e.png" />

And it's used for `Auto-Update`.

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641400215835-87f663610072a1e27f1da23a200f39b21f3e3f798a27270d1e9e5dd5d37ea255.png" />

ref:

- [megahertz/electron-log: Just a simple logging module for your Electron application](https://github.com/megahertz/electron-log)

- [logging - Where can I find the logs for my Electron app in production? - Stack Overflow](https://stackoverflow.com/questions/41140960/where-can-i-find-the-logs-for-my-electron-app-in-production)

However, it may not work since the output still goes into the terminal.

### TODO: idealog color configuration

## build for Windows on Mac

Using this command:

```sh
electron-builder build --win
```

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641369861536-a425061cf7dc95030f6e2d90279fa39a62333acf181bd5f415d5fc6d9c245643.png" width="480" />

But then: <img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641370003105-4c933a2dae29f931f023269210b3a2d609cd218edd24c205643bfa2518f9aa2f.png" width="480" />

Hence, we need a mirror.

## build native dependencies and for multi platforms

It seems this is auto finished by `electron-builder`, which is described at: [This module can automatically determine the version of Electron and handle the manual steps of downloading headers and rebuilding native modules for your app.](https://www.electronjs.org/docs/latest/tutorial/using-native-node-modules#:~:text=This%20module%20can%20automatically%20determine%20the%20version%20of%20Electron%20and%20handle%20the%20manual%20steps%20of%20downloading%20headers%20and%20rebuilding%20native%20modules%20for%20your%20app.)

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641369455356-de2696cc998305e33a63cfa320438182cb1058f3219da95df2b3993541d870fe.png" width="480" />

## custom app logo

### a good start

All we need to do is to follow: [Changing electron app icon. Generate icns | by Khoa Pham | Fantageek | Medium](https://medium.com/fantageek/changing-electron-app-icon-acf26906c5ad)

In which it directs us to download [onmyway133/IconGenerator: 🍱 A macOS app to generate app icons](https://github.com/onmyway133/IconGenerator)

success when run after pack.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641367831443-9ec96d4bce17056e6abf363cd144266c952a154a3aa7fec43afc2145d5ca028a.png" width="480" />

### customize icon for unpacked app

If we wanner the icon does work in unpacked environment, we need to replace the default icon in the module.

```sh
cp ./assets/icon.icns node_modules/electron/dist/Electron.app/Contents/Resources
```

Or we can follow the above article, right click app, and change the icon.

### square .icon

When I pack for windows, it told me the icon size is at least '256 x 256'.

However I checked the raw image `xx.png`, and admitted that the size is far bigger than this, but only to be converted to '256 x 204'.

I realized it may be owing to the size ratio, and I changed the image file into a square one. <img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641369646888-cd19bed16ca970d1b078ca722f2464221a47f054162de3bf10154efd5a1759e6.png" width="480" />

And then, it worked!

ref:

- [angular - How to Change ElectronJS App default Icon? - Stack Overflow](https://stackoverflow.com/questions/58351575/how-to-change-electronjs-app-default-icon)

## electron-builder `files` map

The current problem has become clarified, that is files not found.

We need a map, since I tried `files` but in vain.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641148225241-7024811ff97dcbf12b0b6fbbd55ba645706c76be5464f6709b699d2bbd239c5f.png" width="480" />

Now, the problem is that the database would auto create after first query, while it's empty and then causes errors.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/electron-howto-1641152259910-b7c6267ebdebb2f92da0194da0c417ea56039d03d07c10cc0726155b9b3b3e35.png" width="480" />

- [Using Prisma with the Electron Framework · Issue #9613 · prisma/prisma](https://github.com/prisma/prisma/issues/9613)

## ⭐️⭐️⭐️ debug binary electron

Here's what worked for me on Mac.

In terminal type `lldb path/to/build.app` In the opened debugger type `run --remote-debugging-port=8315`. It should open a window of your app. Open Chrome at `http://localhost:8315/` Click on the name of the app. For example, Webpack App. If you don't see anything in the opened tab, focus on the window of your app.

ref: https://stackoverflow.com/a/56634497/9422455

## `ipcRenderer` communication

It deserves my attention that the msg interface from main process is so-called `ipcMainEvent` which is not exported.

<img alt="picture 79" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640678460651-electron-howto-12d652220f222d268d792307f8e0523bfc5b47ea28c4b56795c240ed44fce75b.png" width="480" />

So, for typescript support, I need to define a 'hooked ipcMainEvent' like this:

```ts
interface IpcMainEvent extends Event {
  // eslint-disable-next-line @typescript-eslint/ban-types
  reply: Function;
}
```

And when communicating, I should be careful with the difference between `on` and `once`, and don't forget to close the channel if need.

<img alt="picture 74" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640672448044-electron-howto-940254219636fb7b6bbdfea1faf735478526cefe89f48a4e6d2cef6acfe509e6.png" width="480" />

ref:

- [IpcMainEvent Object extends `Event` | Electron](https://www.electronjs.org/docs/latest/api/structures/ipc-main-event)

- [ipcRenderer | Electron](https://www.electronjs.org/docs/latest/api/ipc-renderer)

## hwo to use `preload.ts`

ref:

- [Using typescript in Electron's preload scripts - Stack Overflow](https://stackoverflow.com/questions/49076033/using-typescript-in-electrons-preload-scripts)

suppose:

```yaml
MAIN: src/electron/main
RENDERER: src/renderer/index
PRELOAD_TS: src/electron/preload.ts
PRELOAD_JS: src/electron/preload.js
RUN_MAIN: electron MAIN, or like
RUN_RENDERER: webpack serve --config WEBPACK_DEV_CONFIG_RENDERER.js, or like
```

### the `preload` script won't run if we just start the main process

First, if we only run `electron MAIN` or `electron -r ts-node/register/transpile-only MAIN` (ts support), the electron window would run successfully no matter we pointed a `preload` file or not since the file would only run just before the renderer process, i.e. after the main process and separate.

### it's ok when we just use `preload.js`

If we just use `preload.js`, then no matter we use webpack or not, the programme would run well.

### what about using a `preload.ts`

The main problem concerning with `preload.ts` is that when we use electron, we are likely to use different pack method for main process and the renderer one, and the core concept is whether the `preload.ts` had been compiled into `preload.js` and executed by the renderer.

#### remedy 1, the `tsc` solution

If we first created a `preload.ts` file and it doesn't export anything to with the main or renderer codes, then the only change we need to do is that to add `tsc PRELOAD_TS && ` before the `RUN_RENDERER`.

It can be expected to see the `preload.ts` changed into `preload.js` and all the things goes ok.

For example, we can write pure `ts` type of `preload`, and it in fact needs no extra modification since the interface is perfect except a little dangerous since we didn't put constraint on the api request. More can be found refer to: [Security considerations](https://www.electronjs.org/docs/latest/tutorial/context-isolation#:~:text=over%20the%20bridge.-,security%20considerations)

<img alt="picture 62" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640619986956-electron-howto-1ce7cdbe555ac69cf6f36e74efe332354d4bfda0fc47257f55efb8c46d629538.png" width="480" />

I do care about the safe problem if this is a huge app developed for commercial use.

But If I write more apis, then it would drive me to separate my apis in another file, and the renderer, as well as the main, would read from the file together. At the same time, `tsc` would compile the `preload.ts` along with the separate file to `.js`, then a `emit skipped` error may happen if the electron main to read a `interface.ts` file but to find there exists both `interface.ts` and `interface.js`.

### how to remedy the `electron-react-boilerplate` project

Dive into the source coe of [electron-react-boilerplate](https://github.com/electron-react-boilerplate/electron-react-boilerplate#:~:text=electron-react-boilerplate%0A%20%20%0A%20%20%2F-,electron-react-boilerplate,-Public%20template) , we can know the programme startup flow under the development environment is as the following:

```mermaid
flowchart TD

subgraph Start[npm run start]
PreStart[check port in use] -->
StartRender
end


subgraph StartRender[\`npm run start:renderer\`]

subgraph WebpackDev[\`webpack serve --dev.config\`]
subgraph BeforeRun[before run: \`npm run start:main\`]
ElectronStart[run electron main]

end
end
end
```
