# jetbrains-howto

## my recommended configuration

### uncheck inspection on `redundant local variable`

config:

![picture 2](.imgs/jetbrains-howto-1660213190102-79e0a167e1914be5ced868e4f23dffa6d3648cfbdc8d3e1f6365c8755327aee1.png)  

reason: 方便随时开合一些程序逻辑，inline不方便

![picture 1](.imgs/jetbrains-howto-1660213177132-b4d99c8577d1ba67a26296ab2651dca3715c6447b3c38e77d0188fbaa222768d.png)  

if not:

![picture 3](.imgs/jetbrains-howto-1660213284017-d9e0e69952e24660cdd6bbc61780a80284396c6cf2802776ee6a15ed74960ec9.png)  

## how to customize file template

:::warning
jb 的 `file template` 与 `live template` 是两套不同的体系，在 `live template` 中可以使用 `EDIT VARIABLES` 去自定义变量，但在 `file template` 中基于 `velocity` 语法，实现方式是不一样的，具体见下文。
:::

打开文件模板可以看到有个 [`Apache Velocity`](https://velocity.apache.org/engine/devel/user-guide.html) 的超链接，它表示 jb 的文件模板是基于 Velocity 这门语言的：

![picture 1](.imgs/jetbrains-howto-1659944256968-9c28020077b46cb3e832fb4e82592c773f7f7d3938d6220f798ee9aade0495ee.png)  

### 有哪些 jb 预定义的变量

参考：[File template variables | IntelliJ IDEA](https://www.jetbrains.com/help/idea/file-template-variables.html)

有：

![picture 5](.imgs/jetbrains-howto-1659944611452-4585ddf5d80c3623410b937ac2d4da212df93a075e3d0f59d693b4f9bad2e842.png)  

值得注意的是，没有现成的 `YYYY-MM-DD` 格式的日期。如果需要的话，需要用 `velocity` 语法去实现。

### 如何在单文件定义变量

![picture 4](.imgs/jetbrains-howto-1659944488621-5a0c2ba00d050233eb31e308197c0d328da4e17f87ce8e6580da3dfb0d32cd2f.png)  

### 如何引用其他文件

直接把 `#set` 的部分拆出去，然后用 `#parse` 导入即可，不能用 `#include`，因为 `#include` 只是纯文本导入，而 `#parse` 可以解析。

![picture 3](.imgs/jetbrains-howto-1659944466625-76cfbfb2b60451d539b4650f0d4a8e3590cb6aa67801f925b5c1e379f2d5a3c7.png)  

![picture 2](.imgs/jetbrains-howto-1659944458582-903788f41d1c9ea4ca160995f91283837613adae08d1db577ca25f6a832d12a8.png)  

## inspection on `suspicious.name.assignment`

官方解释：[Code Inspection: Suspicious variable/parameter name combination | PhpStorm](https://www.jetbrains.com/help/phpstorm/javascript-and-typescript-suspicious-variable-parameter-name-combination.html)

stackoverflow 的讨论 [java - IntelliJ says, should probably not be passed as parameter x - Stack Overflow](https://stackoverflow.com/questions/34379580/intellij-says-should-probably-not-be-passed-as-parameter-x)

指点的 jb 源码： [intellij-community/SuspiciousNameCombinationInspectionBase.java at 210e0ed138627926e10094bb9c76026319cec178 · JetBrains/intellij-community](https://github.com/JetBrains/intellij-community/blob/210e0ed138627926e10094bb9c76026319cec178/java/java-analysis-impl/src/com/intellij/codeInspection/suspiciousNameCombination/SuspiciousNameCombinationInspectionBase.java)

## nbsp 空格显示设置

see: - [2020.2 showing |NBSP| – IDEs Support (IntelliJ Platform) | JetBrains](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360009442799-2020-2-showing-NBSP-)

在`Help | Find Action | Registry | editor.show.special.chars`里设置。

选择显示时的效果：

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jetbrains-howto-1656906625520-b834c9aa7081ce0f8fea14255222028f1881e4618816dd8e13152c02a88fc208.png)

选择不显示时的效果：

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jetbrains-howto-1656906688216-fb4ab848042da8b9b6ae1b6cc157f786e80670190c1c525ca4d1a1c77c5873f8.png)

## jetbrains 各版本下载链接生成脚本

```py
def gen_download_url(software="webstorm", name="WebStorm", version="2020.3.3", suffix="exe"):
    """
    download page (webstorm as the example): https://www.jetbrains.com/webstorm/download/other.html
    software: {pycharm, webstorm, ...}
    suffix: {exe, dmg}
    """
    url_pycharm_professional = "https://download-cdn.jetbrains.com/python/pycharm-professional-2020.3.5.dmg"
    url_webstorm = "https://download-cdn.jetbrains.com/webstorm/WebStorm-2020.3.3.exe"
    return f"https://download-cdn.jetbrains.com/{software}/{name}-{version}.{suffix}"
```

## BEST-PRACTICE: jetbrains version manage

### 1. the plugin of `eval restart`

plugin repo: https://plugins.zhile.io

plugin name: 'IDE Eval Reset'

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jetbrains-howto-1642485827260-f451b4ff7ea352b26fd4c6d13a512ff88c8ff067dd754cb9d51e1d979e6af907.png)

### 2. the approach to manage versions

Download the toolbox at here: [JetBrains Toolbox App: Manage Your Tools with Ease](https://w ww.jetbrains.com/toolbox-app/)

And then download or uninstall specific versions of jetbrains products.

For example, since the hack plugin of `eval start` (which allows you to use jetbrains product periodically freely) won't support the versions of webstorm after 2021.2, we can easily download the old version in toolbox.

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jetbrains-howto-1642485538134-6f36f7277858541772744c00ac24f01f243fcfd7b282a5aceddd5df6fc72c798.png)

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jetbrains-howto-1642485565528-42c0dec28204e8878ecf4f1a59ed5d70ef5d6cb428377f11fcb7cc885e842fd1.png)

ref:

- [JetBrains 全系列软件激活教程激活码以及 JetBrains 系列软件汉化包](https://www.macwk.com/article/jetbrains-crack)

- [ide - How to downgrade IntelliJ to older version - Stack Overflow](https://stackoverflow.com/questions/18519560/how-to-downgrade-intellij-to-older-version)

## improve jetbrains efficiency

1. Disable all unnecessary plugins
2. Increase memory for IntelliJ IDEA [Help / Change memory settings]
3. Exclude folders and Unload modules
4. Disable on-the-fly import management
5. Pause inspections check

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640194669995-jetbrains-howto-bb60024de03a0f70a741740db732e6d44c514c077f1132051728b80595dcc2ae.png" width="480" />

reference:

- [Simple Steps for Improving Your IDE Performance | The Kotlin Blog](https://blog.jetbrains.com/kotlin/2021/06/simple-steps-for-improving-your-ide-performance/)
