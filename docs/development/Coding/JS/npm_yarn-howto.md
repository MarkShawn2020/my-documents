# npm/yarn howto

1. [BEST-PRACTICE: nvm](#best-practice-nvm)
   1. [install](#install)
   2. [use](#use)
2. [BEST-PRACTICE: `mirror-config-china`](#best-practice-mirror-config-china)
   1. [a chinese mirror practice: how does it save an electron project](#a-chinese-mirror-practice-how-does-it-save-an-electron-project)
   2. [config npm mirrors](#config-npm-mirrors)
   3. [config yarn mirrors](#config-yarn-mirrors)
3. [BEST-PRACTICE: how to install `node-sass`](#best-practice-how-to-install-node-sass)
   1. [Step 1. ensure `sass-binary-site` enabled in `.npmrc`](#step-1-ensure-sass-binary-site-enabled-in-npmrc)
   2. [Step 2. change node/npm version](#step-2-change-nodenpm-version)
4. [npm commands](#npm-commands)
   1. [update package](#update-package)
   2. [check exist, locally and globally, with and without dependencies](#check-exist-locally-and-globally-with-and-without-dependencies)
5. [TUTORIAL: modify `diff2html-cli` html logo](#tutorial-modify-diff2html-cli-html-logo)
   1. [Step 1. locate the package position](#step-1-locate-the-package-position)
   2. [Step 2. modify the template html file, since the inner code generates dependent on it](#step-2-modify-the-template-html-file-since-the-inner-code-generates-dependent-on-it)
   3. [Ref 1. check tree structure](#ref-1-check-tree-structure)

## BEST-PRACTICE: nvm

ref:

- [nvm/README.md at master · nvm-sh/nvm](https://github.com/nvm-sh/nvm/blob/master/README.md)

### install

```sh
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash

export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh" # This loads nvm
```

### use

```sh
nvm install 14
nvm use 14
```

## BEST-PRACTICE: `mirror-config-china`

```sh
npm i -g mirror-config-china --registry=https://registry.npm.taobao.org
# 查看npm配置
npm config list
# 查看环境变量
source ~/.bashrc && env
# then enable local
```

### a chinese mirror practice: how does it save an electron project

This is the problem which I met.

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640779337829-npm_yarn-howto-83184c036aa89f0f72993d0be12f1a05fce1f12fbb6fa6cf29db901a23803851.png" width="480" />

And in fact, there is one cn mirror set for electron, so I can't understand why. <img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640779402198-npm_yarn-howto-ba1bd753798fafa6b255373088034da1c14e786f216febaf6c23a80714af54d6.png" width="480" />

Maybe the format is wrong, since a `xxx = true` looks a bit wield. Or maybe the project resolves some packages ont only from 'electron_mirror', or specifically, to download `electron-v1.xxx.zip`, it won't use `electron_mirror`, etc.

Anyhow, I should give `mirror-config-china` project a try.

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640779604692-npm_yarn-howto-6448401a3dd430d9ea918072cc93bfaad3f67dc4048a92f719cbc96797ce6bc7.png" width="480" />

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640779616200-npm_yarn-howto-27f9747dbd4781f12d7efc9d74d7bf55c5c5987697da0f5f7eda014c2906cbd7.png" width="480" />

I followed the above guidance, and then I should succeed!

<img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640779657719-npm_yarn-howto-5c446ef298d7eb27cde4613b90617e9491e400aa6291e7ebd3c3288ca2b1614e.png" width="480" />

The current config info is as the following, in which the `electron-mirror` value is in fact the same (except a `= true` ending).

```sh
(base) ➜  electron-typescript-example git:(master) npm config list
; "builtin" config from /usr/local/lib/node_modules/npm/npmrc

prefix = "/usr/local"

; "user" config from /Users/mark/.npmrc

; registry = "https://registry.npm.taobao.org/" ; overridden by project

; "project" config from /Users/mark/Documents/mark_projects/皇家小虎/HJXH/hjxh_express_match/erb/electron-typescript-example/.npmrc

chromedriver-cdnurl = "https://npm.taobao.org/mirrors/chromedriver"
couchbase-binary-host-mirror = "https://npm.taobao.org/mirrors/couchbase/v{version}"
debug-binary-host-mirror = "https://npm.taobao.org/mirrors/node-inspector"
disturl = "https://npm.taobao.org/dist"
electron-mirror = "https://npm.taobao.org/mirrors/electron/"
flow-bin-binary-host-mirror = "https://npm.taobao.org/mirrors/flow/v"
fse-binary-host-mirror = "https://npm.taobao.org/mirrors/fsevents"
fuse-bindings-binary-host-mirror = "https://npm.taobao.org/mirrors/fuse-bindings/v{version}"
git4win-mirror = "https://npm.taobao.org/mirrors/git-for-windows"
gl-binary-host-mirror = "https://npm.taobao.org/mirrors/gl/v{version}"
grpc-node-binary-host-mirror = "https://npm.taobao.org/mirrors"
hackrf-binary-host-mirror = "https://npm.taobao.org/mirrors/hackrf/v{version}"
leveldown-binary-host-mirror = "https://npm.taobao.org/mirrors/leveldown/v{version}"
leveldown-hyper-binary-host-mirror = "https://npm.taobao.org/mirrors/leveldown-hyper/v{version}"
mknod-binary-host-mirror = "https://npm.taobao.org/mirrors/mknod/v{version}"
node-sqlite3-binary-host-mirror = "https://npm.taobao.org/mirrors"
node-tk5-binary-host-mirror = "https://npm.taobao.org/mirrors/node-tk5/v{version}"
nodegit-binary-host-mirror = "https://npm.taobao.org/mirrors/nodegit/v{version}/"
operadriver-cdnurl = "https://npm.taobao.org/mirrors/operadriver"
phantomjs-cdnurl = "https://npm.taobao.org/mirrors/phantomjs"
profiler-binary-host-mirror = "https://npm.taobao.org/mirrors/node-inspector/"
puppeteer-download-host = "https://npm.taobao.org/mirrors"
python-mirror = "https://npm.taobao.org/mirrors/python"
rabin-binary-host-mirror = "https://npm.taobao.org/mirrors/rabin/v{version}"
registry = "https://registry.npm.taobao.org/"
sass-binary-site = "https://npm.taobao.org/mirrors/node-sass"
sodium-prebuilt-binary-host-mirror = "https://npm.taobao.org/mirrors/sodium-prebuilt/v{version}"
sqlite3-binary-site = "https://npm.taobao.org/mirrors/sqlite3"
utf-8-validate-binary-host-mirror = "https://npm.taobao.org/mirrors/utf-8-validate/v{version}"
utp-native-binary-host-mirror = "https://npm.taobao.org/mirrors/utp-native/v{version}"
zmq-prebuilt-binary-host-mirror = "https://npm.taobao.org/mirrors/zmq-prebuilt/v{version}"

; node bin location = /usr/local/Cellar/node/17.2.0/bin/node
; cwd = /Users/mark/Documents/mark_projects/皇家小虎/HJXH/hjxh_express_match/erb/electron-typescript-example
; HOME = /Users/mark
; Run `npm config ls -l` to show all defaults.
```

Thanks `mirror-config-china`! It do save me a lot of time.

### config npm mirrors

#### approach 1 (recommend)

- [mirror-config-china - npm](https://www.npmjs.com/package/mirror-config-china)

#### approach 2

```sh
### show registry
npm config get registry
# https://registry.npmjs.org/

### change to chinese registry
npm config set registry http://r.cnpmjs.org # It syncs with registry.npmjs.org.
npm install
# reference: https://stackoverflow.com/a/27216097/9422455
```

### config yarn mirrors

```yaml
# ~/.yarnrc
registry "https://registry.npm.taobao.org" sass_binary_site "https://npm.taobao.org/mirrors/node-sass/" phantomjs_cdnurl "http://cnpmjs.org/downloads" electron_mirror "https://npm.taobao.org/mirrors/electron/" sqlite3_binary_host_mirror "https://foxgis.oss-cn-shanghai.aliyuncs.com/" profiler_binary_host_mirror "https://npm.taobao.org/mirrors/node-inspector/" chromedriver_cdnurl "https://cdn.npm.taobao.org/dist/chromedriver"
```

ref:

- [如何在国内加速 yarn install | Recording](https://www.jibing57.com/2020/02/24/how-to-speed-yarn-install-interiorly/)

## BEST-PRACTICE: how to install `node-sass`

### Step 1. ensure `sass-binary-site` enabled in `.npmrc`

#### Option 1: use `mirror-config-china`

!!!warning this would set into `project/.npmrc`

ref: [BEST-PRACTICE: `mirror-config-china`](#best-practice-mirror-config-china)

#### Option 2: set directly

!!!warning this would set into `~/.npmrc`

```sh
# this would set into `~/.npmrc`
npm config set sass-binary-site=https://npm.taobao.org/mirrors/node-sass
```

### Step 2. change node/npm version

If the last step not works, then maybe you need to change the node version.

For example, one of my projects used `node-sass` of version `"node-sass": "^4.14.1",`, and according to the official `node-sass` documentation, it lists:

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-howto-1642841662888-801b5f5f69831c1fc22b0430c10d9cea0079cc51c58815fd2260ba001e627bd5.png)

And at that time, my node version is `17+`, so I use `nvm` [BEST-PRACTICE: nvm](#best-practice-nvm) to change it down to `14` and `npm i -D node-sass` and worked.

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-howto-1642841787353-3028ce9fdfa5b03b272ecb705ccafbaa3e5469d1e6d64fa36b268872ff29ca0d.png)

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-howto-1642841802474-23d1f0911ea6d1c73f2c7bb5d6a58c3278862d58f77beb5d2fb95dc85f6379e1.png)

## npm commands

### update package

```sh
# update all
npm update

# update a specific one
npm update PACKAGE

# filter out out-of-dated packages
npm outdated
```

see: - [node.js - npm check and update package if needed - Stack Overflow](https://stackoverflow.com/questions/16525430/npm-check-and-update-package-if-needed)

### check exist, locally and globally, with and without dependencies

```sh
# check a npm package P exist locally
npm list P

# check a npm package P exist globally: `/usr/local/lib/node_modules/PACKAGE`
npm list -g P

# check exist without dependencies
npm list P --depth=0
```

ref:

- [How to check if an npm package installed globally or locally | Reactgo](https://reactgo.com/check-npm-packages-installed/)

## TUTORIAL: modify `diff2html-cli` html logo

### Step 1. locate the package position

```sh
npm list -g diff2html-cli
# /usr/local/lib

cd /usr/local/lib/node_modules/diff2html-cli
```

ref:

- [javascript - Where does npm install packages? - Stack Overflow](https://stackoverflow.com/questions/5926672/where-does-npm-install-packages#:~:text=The%20npm%20modules%20are%20first,your%2Dproject%2Fnode_modules%20).&text=which%20will%20print%20the%20location%20along%20with%20the%20list%20of%20installed%20modules.)

### Step 2. modify the template html file, since the inner code generates dependent on it

The main change is to add an icon ref:

```html
<!-- the icon path need to be absolute, since when executing `diff2html` in terminal, the path cannot ensure to be int current directory -->
<link
  rel="icon"
  href="/usr/local/lib/node_modules/diff2html-cli/logos/logo.png" />
```

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-howto-1642744901058-548b42f9ffdc9c14247c60cd0bf63d8dd5620328ed96cc7d1e9eef7233a4c956.png)

ref:

how to change logo in html

- [html - How do I put my website's logo to be the icon image in browser tabs? - Stack Overflow](https://stackoverflow.com/questions/11488960/how-do-i-put-my-websites-logo-to-be-the-icon-image-in-browser-tabs)

logo url

- [Manage | FreeLogoDesign](https://www.freelogodesign.org/manager/showcase/d8b47e4c8338433bb7e70e4b99c2daa9)

### Ref 1. check tree structure

```text
➜  diff2html-cli tree -L 2 .                                                                             [21-01-22 | 1:57:54]
.
├── LICENSE
├── README.md
├── bin
│   └── diff2html
├── lib
│   ├── cli.d.ts
│   ├── cli.d.ts.map
│   ├── cli.js
│   ├── cli.js.map
│   ├── configuration.d.ts
│   ├── configuration.d.ts.map
│   ├── configuration.js
│   ├── configuration.js.map
│   ├── http-utils.d.ts
│   ├── http-utils.d.ts.map
│   ├── http-utils.js
│   ├── http-utils.js.map
│   ├── logger.d.ts
│   ├── logger.d.ts.map
│   ├── logger.js
│   ├── logger.js.map
│   ├── main.d.ts
│   ├── main.d.ts.map
│   ├── main.js
│   ├── main.js.map
│   ├── types.d.ts
│   ├── types.d.ts.map
│   ├── types.js
│   ├── types.js.map
│   ├── utils.d.ts
│   ├── utils.d.ts.map
│   ├── utils.js
│   ├── utils.js.map
│   ├── yargs.d.ts
│   ├── yargs.d.ts.map
│   ├── yargs.js
│   └── yargs.js.map
├── logos
│   └── logo.png
├── node_modules
│   ├── abbrev
│   ├── ansi-regex
│   ├── ansi-styles
│   ├── arch
│   ├── clipboardy
│   ├── cliui
│   ├── color-convert
│   ├── color-name
│   ├── cross-spawn
│   ├── diff
│   ├── diff2html
│   ├── emoji-regex
│   ├── end-of-stream
│   ├── escalade
│   ├── execa
│   ├── get-caller-file
│   ├── get-stream
│   ├── highlight.js
│   ├── hogan.js
│   ├── is-docker
│   ├── is-fullwidth-code-point
│   ├── is-stream
│   ├── is-wsl
│   ├── isexe
│   ├── mkdirp
│   ├── nice-try
│   ├── node-fetch
│   ├── nopt
│   ├── npm-run-path
│   ├── once
│   ├── open
│   ├── p-finally
│   ├── path-key
│   ├── pump
│   ├── require-directory
│   ├── semver
│   ├── shebang-command
│   ├── shebang-regex
│   ├── signal-exit
│   ├── string-width
│   ├── strip-ansi
│   ├── strip-eof
│   ├── tr46
│   ├── webidl-conversions
│   ├── whatwg-url
│   ├── which
│   ├── wrap-ansi
│   ├── wrappy
│   ├── y18n
│   ├── yargs
│   └── yargs-parser
├── package.json
└── template.html

55 directories, 38 files
```
