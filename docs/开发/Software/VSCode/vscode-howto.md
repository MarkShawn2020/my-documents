
## extensions

- [awesome-vscode | 🎨 A curated list of delightful VS Code packages and resources.](https://viatsko.github.io/awesome-vscode/#bash)

## snippets

### documentation: vscode snippet

- [Userdefinedsnippets - vscode-docs](https://vscode-docs.readthedocs.io/en/latest/customization/userdefinedsnippets/)

a good and detailed article concludes many methods to use code snippets

- [Custom polymorphic code snippets in VS Code - LogRocket Blog](https://blog.logrocket.com/custom-polymorphic-code-snippets-in-vs-code-e76d8cad656b/)

### how to develop snippet extensions

- [Support for Snippet prefix and other values inside Snippet's body · Issue #54661 · microsoft/vscode](https://github.com/Microsoft/vscode/issues/54661)

ref:

- [vscode-extension-samples/extension.ts at main · microsoft/vscode-extension-samples](https://github.com/Microsoft/vscode-extension-samples/blob/main/completions-sample/src/extension.ts)

### can snippets use variables

1. we can use predefined variables

   since vscode has defined some common variables I can use, i.e. macro variables, so that reduced my work of developing an extension

   - [Snippets in Visual Studio Code](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_variables)

2. others we can't, see also [can snippets cannot use functions](#can-snippets-cannot-use-functions)

### can snippets use functions

- [Execute functions during snippet expansion · Issue #10561 · microsoft/vscode](https://github.com/microsoft/vscode/issues/10561)

- [[Solved] Visual studio code Dynamic snippet evaluation in VSCode - Code Redirect](https://coderedirect.com/questions/396102/dynamic-snippet-evaluation-in-vscode)

### can snippet use regex in prefix

use multiple prefixes as an alternative to the target of using regex in prefix

- [visual studio code - Is there a way to use regex expression in vscode snippet prefix? - Stack Overflow](https://stackoverflow.com/questions/54388765/is-there-a-way-to-use-regex-expression-in-vscode-snippet-prefix)

### why snippet with backquote(`\``) not works

[Snippet with prefix "``" (double backtick) not working for inline Markdown code block - Stack Overflow](https://stackoverflow.com/questions/72672897/snippet-with-prefix-double-backtick-not-working-for-inline-markdown-code) introduced the reason that "\`" not works is that the "\`" is not a "word character":

> The prefix can be anything but "suggestions as you type" are only triggered when typing a word character. What that is defines the corresponding language. For non word prefixes suggestion must be triggered manually, using ctrl+space

### TODO: how to make snippet work with backquote(`\``)

use sequenced command:

```sh

```

## how to enable suggestion for markdown

```json
// User/settings.json
    // ref: - [Enable quick suggestions for Markdown in VS Code - Deepan Seeralan](https://www.deepanseeralan.com/tech/enable-quick-suggestions-for-markdown-in-vscode/)
    "[markdown]": {
        "editor.quickSuggestions": {
            "other": true,
            "comments": false,
            "strings": false
        }
    },
```

ref:

- [Enable quick suggestions for Markdown in VS Code - Deepan Seeralan](https://www.deepanseeralan.com/tech/enable-quick-suggestions-for-markdown-in-vscode/)

## how to configure python interpreter and auto activate

After installed my local virtualenv, I need to activate it.

Of course, I can activate it manually and each time I created a new terminal:

```sh
source .pyenv/bin/activate
```

However, it's inflexible anyway.

After a little search, I found the solution: [Using Python Environments in Visual Studio Code](https://code.visualstudio.com/docs/python/environments#_select-and-activate-an-environment)

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641469133605-b34b8637c25585c8ca695f461fe2bf900eb83bad2c88e37f2df9d815abdbf009.png" />

The following first two choices are in fact the same, the second of which is right the interpreter I created manually, and the first one is listed here since I configure it in the settings.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641469255250-e242d4697d598127b97b8e87b32182b88ccd4e146693f79b7677a9f611b24820.png" />

Also, as we can see, there are two many python interpreters, one of which seems unnecessary: the one of `/usr/local/bin/python3`.

And then I use `rm -rf /usr/local/python` to delete all the unwanted python directories, as well as any other `pytyon3*`.

Then reload the window, the unwanted `python3` disappeared.

But there is still a question, about the duplication of `/usr/bin/python`.

I found only the first one is valid, because after I clicked the second one, the bottom left of my vscode shows no interpreter.

I couldn't know where the duplication arises from, and searched a bit only to find that the official vscode developers responded the duplication of jupyter kernels have been repaired, which is not certainly what I happened.

Then I opened devtools of vscode and find that when I switch to the last interpreter, error messages arise up, telling me there is no `$mark/usr/bin/python` which indicated that it joins the `/usr/bin/python` with the current working directory `$mark`.

OK, I might reload to see what would happen.

However, I noticed there is a choice of `reload without extensions`, then I chose that but to find the menu of selecting interpreters has gone, which means it's just an extension instead of built one.

So the problem is about the extension.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641470830942-9b8a8529f43314bde425ef409f20ae0dc0eb47b6308cc73e3a907cf31b9b54ff.png" />

TODO: remedy the selecting interpreter.

Then I found the feature of `selecting python interpreter` is provided by `python` extension officially.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641471024978-ecaad76fc53d5103aadbeaab11e7263aaec513d22caed88f9e9c471bbfb6ff6c.png" />

So why would I have a **duplicated and invalid** option of interpreter?

ref:

- [How Can I Properly Uninstall Python from Mac (Solved)](https://osxuninstaller.com/uninstall-guides/properly-uninstall-python-mac/)

- [python - VS Code - Cleanup list of interpreters - Stack Overflow](https://stackoverflow.com/questions/65075045/vs-code-cleanup-list-of-interpreters)

- [Fixes for listing of duplicate kernels in kernel picker by DonJayamanne · Pull Request #4066 · microsoft/vscode-jupyter](https://github.com/microsoft/vscode-jupyter/pull/4066)

## how to upload image in markdown

After a litter research deep into the extension of `markdown image`, I'd think it has a main drawback that doesn't allow me to save local first and then upload together which is rawly supported in typora.

It only supports save to local or upload to cloud when insert the image at the first time, and then doesn't provide a choice to upload in local then.

I may write a tool then.

## TODO: add multi circle

It seems that vscode didn't support a `multi cursors mode` allows me to switch so that when I tap UP or DOWN, then new cursors added up or down like jetbrains.

<img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641457943128-10415c9e080212beabf42311905d7cc9b8671da4e1724ddaf1fe0083ec612e06.png" />

Since I do think this trigger mechanism is more user-friendly.

## TODO: python auto import not work: `indexing: true`

I suffered from the problem of not able to auto import from libraries.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1640994377794-d0aec0fcddd0cc02bba71adb7b9ea54b1c2b520db87fbd726bfad2e44ecd1783.png" width="480" />

And I used conda as my internal interpreter, along with `pylance` as my language server.

You can see there is a `python3.8` in my sys paths, with is where `pprint` package is so that I can use `from pprint import pprint`.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1640994393466-955d41ee72c26130951ef521f412c53098006f936fe39aabed834e858d6ea800.png" width="480" />

However, I failed.

After a hard search, I finally found this solution at: [Can you set "python.analysis.indexing": true and see if this fixes things for you? ](https://github.com/microsoft/pylance-release/issues/547#:~:text=Can%20you%20set%20%22python.analysis.indexing%22%3A%20true%20and%20see%20if%20this%20fixes%20things%20for%20you%3F)

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1640994626889-e0a44941de16ac56eb61a7c94adb093867c0ad0f0df8a76e318c291d4ae756e2.png" width="480" />

And it did work, though it's too many !

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1640994240944-c71be2cda0dd0b073cc757fdb987a61867464e9339218ead9893d49720444ac5.png" width="480" />

Then after I removed some path settings, it became less:

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1640994867355-c2459988525a86fa8bfffe0e19563c3a616f0541727ad79c14577312686ddd62.png" width="480" />

Then I thought, maybe it's because `conda`, which has too many packages, and I created a new virtualenv.

Whereas, I failed again, for almost the same result.

## how to custom vscode theme/css

Among of a lot of color themes, I do favor in `One Dark Pro Darker`.

Since now, the only one problem disturbing me is when I search for menu item, there are two choices (in fact one most bright is the current menu, and another second bright is the current choice) which seems not consistent with my intention: i.e. when I tapped 'Enter', it means I choose one, which should be the most bright one.

However, as you know, it doesn't.

I then, (finally has time and mood to figure out this), tried another themes, any of them are correct brightness order.

So, what I should do? Should I give up current favorite theme? Or should I continue to bear with the annoying design.

Luckily, I followed my intension, and found a way to solve this perfectly: to change the css.

And what a genius I am again, since I thought about a key word: `list`, and then it is!

```json
// settings.json
    "workbench.colorCustomizations": {
        "list.activeSelectionBackground": "#1f4106"
    },
```

Just add the coding above into `settings.json`, and a consistent design comes:

<img alt="picture 21" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641307793794-cbe1a0c21be69e80d6e806b2c0d1969428984420bf347f7b45ca4379caec174d.png" width="480" />

And thanks to `One Dark Pro Darker` again. May anyone like it as well!

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1641307912485-3986218a5d817a971c8281f04b0ad40f825b50880cc306ae2c747f837a6fa1f3.png" width="480" />

ref:

- [Highlight color custom](https://binaryify.github.io/OneDark-Pro/#/?id=highlight-color-custom)

## how to suppress `autopep8` of `sort import` for python `sys.insert`

recommend way is to use `# nopep8` or `# noqa`

```py
import sys # nopep8
sys.path.insert(0, '/path/to/packages') # nopep8

import local_package
```

ref:

- [python - Allow statements before imports with Visual Studio Code and autopep8 - Stack Overflow](https://stackoverflow.com/questions/54030320/allow-statements-before-imports-with-visual-studio-code-and-autopep8)


## how to trigger open via 'double click'

I thought it were something like 'preview' (in webstorm), whereas not.

In fact, it's `open mode`.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640846888387-vscode-howto-36e792d582384dc7a049a65ce68790bf6a9a2694cdf5f44eabf306537d2e6e68.png" width="480" />

And it's helpful when I want to multiple manipulate the files in the 'workbench'.

ref:

- [vscode open via double click rather than single click - Google Search](https://www.google.com.hk/search?q=vscode+open+via+double+click+rather+than+single+click)

## TODO: In VSCode, how to render shell commands in markdown (not under preview mode)

I can't make the raw shell commands to have syntax highlight like the following:

```sh
rm -rf FILE
```

As a contrary, some specific keys would have effects, like the following:

```sh
if [[ -f FILE ]]
then rm -rf FILE;
fi
```

They are rendered as the following: <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640772242441-vscode-howto-fe09201ca8b8bb542ac5829bef92362eb8440c0d22d07eee844eb81626b820c2.png" width="480" />

What I expected to is that ont only highlight `if | then |fi`, but also highlight `rm / find / sed...`.

Am I expecting too much?

ref:

- [linux - Bash Code Block Syntax colouring - Stack Overflow](https://stackoverflow.com/questions/36064368/bash-code-block-syntax-colouring)

## how to add commentLine-cursorDown support like jetbrains

TODO: not satisfied since when I comment in an empty line, then it will still cursor down

### step 1. install plugin of 'multi-command', which allows you diy your key and commands like a `macro`

!!!warning it's `multi-command` rather than `multi-comment`

### step 2. diy my own comment line and cursor down

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640273434198-vscode-howto-f644632b7e3de4e96283be1077b0181ad823a92ab0c823c17699d69f40181d4f.png" width="480" />

ref:

- [Automatically switch to next line on comment · Issue #22901 · microsoft/vscode](https://github.com/Microsoft/vscode/issues/22901)

- [multi-command - Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=ryuta46.multi-command&ssr=false#overview)

## how to make double click to select a whole word with '-'

just to exclude '-' from the `word separators` is OK!

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640267591863-vscode-howto-dd58c887e87b8893ff10725c9fb606f8b5ffe993d8acff6a8171520e1a8d5483.png" width="480" />

ref: https://superuser.com/a/1357918

## how to start vscode using `code .`

在安装完 VSCode 后，命令行中并不会默认拥有`code`命令，根据官网指示有多种办法实现。我采用使用命令行直接向 zsh 注入`code`命令：

```sh
cat << EOF >> ~/.zprofile
# Add Visual Studio Code (code)
export PATH="\$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
EOF
source ~/.zprofile
```

> ref

- [Running Visual Studio Code on macOS](https://code.visualstudio.com/docs/setup/mac)

## how to ignore/hide/exclude files in vscode

### SOLVED: what's `files.exclude` mean?

It's about files that would be hidden in the vscode.

```json
    "files.exclude": {
        "**/__init__.py": true,
        "**/__pycache__": true,
        "**/.classpath": true,
        "**/.factorypath": true,
        "**/.project": true,
        "**/.settings": true,
        "**/.idea": true
    },
```

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1644508065818-0816b1304cff9d94de06d277f3942fafe0bc2bf67c50ab5371efdca069f1a9ce.png)

see:

- [How to hide all files & folders starting with dot? : vscode](https://www.reddit.com/r/vscode/comments/jlhpho/how_to_hide_all_files_folders_starting_with_dot/)

## how to make python click jump/crossref

在` "python.analysis.extraPaths"`项中加入目标库的`site_packages`路径就可以！（不是加`python`，也不是加单独的 library，都没用，必须是`site_packages`！）

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-howto-1657102764438-e0733d12911d606a08caae91bde21c1d8bd7229d77d9d036593b13013b34a6a8.png)

ref:

- [Auto-imports only work for code from currently open files when indexing is enabled · Issue #1055 · microsoft/pylance-release](https://github.com/microsoft/pylance-release/issues/1055)

## about 'new file' when right click on a file

I am interested at finding one issue about this feature on VSCode's github at ["New file" / "New folder" on file context menu · Issue #83693 · microsoft/vscode](https://github.com/microsoft/vscode/issues/83693).

And the official considers this feature better suitable for an extension. <img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640110292460-vscode-howto-d85086990f33be5b30df47326d11ce6691b3068b3928af026d9b9083776edbce.png" width="480" />

And at the later part of this page, I found one had posted a handy extension, so I just installed it which helped me solve out this problem perfectly.

ref:

- ["New file" / "New folder" on file context menu · Issue #83693 · microsoft/vscode](https://github.com/microsoft/vscode/issues/83693)

- [New - Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=wenfangdu.faster-new)

## about switch tab view

It's a classic scene when we wanna switch between tabs, and I find out that the default shortcut in VSCode is `⌘ + K, ⌘ + ⌥ + >` for next tab (`<` for previous).

And before which what confused me is that the concept of 'tab' and 'editor', which the 'editor' in VSCode means the 'tab' in the chrome, and I couldn't understand what does the 'tab' mean in VSCode though it does exist.

And after when I searched and figured out the right concept of 'editor' according to following answer, I managed to modify the key just from 'Keyboard Shortcuts' 'panel'(ops, maybe I should named it as a 'editor', so wield!) <img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640107428265-vscode-howto-29f2bb2beaf16e0a9cb84332970e62e4800d4bcb28a21c1fb96fedffefafbbc7.png" width="480" />

ref:

- [vscode settings - Is there a quick change tabs function in Visual Studio Code? - Stack Overflow](https://stackoverflow.com/questions/38957302/is-there-a-quick-change-tabs-function-in-visual-studio-code)

## about definition suggestion

the first one is the `definition show popup` as mentioned in <img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640104688310-vscode-howto-bcf19e8c6e0f56799b24d8d13cebcabd7ac11c2b77b7641247d2c78ddd66e83e.png" width="480" />
