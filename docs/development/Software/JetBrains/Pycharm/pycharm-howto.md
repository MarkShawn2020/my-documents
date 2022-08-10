# pycharm-howto

1. [在 pycharm 中的 opencv 智能提示](#在pycharm中的opencv智能提示)
   1. [最终解决方案](#最终解决方案)
   2. [研究概要](#研究概要)
   3. [研究细节](#研究细节)
   4. [剩余疑惑](#剩余疑惑)
2. [console output colorful log](#console-output-colorful-log)
3. [doc stub on class](#doc-stub-on-class)
4. [pycharm vs vscode](#pycharm-vs-vscode)
   1. [when configure test](#when-configure-test)
5. [create pycharm shortcut](#create-pycharm-shortcut)
6. [How to sort parameters of a function call](#how-to-sort-parameters-of-a-function-call)
   1. [Parameter Info](#parameter-info)
   2. [Parameter Suggestions](#parameter-suggestions)

## FIXED: pycharm 中创建 test 测例，但默认 target_directory 定位异常

pycharm 中创建 test 的 target_directory 的默认规则如下：

1. 当前工程（或文件夹？具体我也不清楚）下若有 tests 文件夹，则创建于此
2. 若没有，则创建于当前文件夹下

但我们的 target_directory 却出现了异常，总是跑到`venv/lib/python3.9/site_packages/numpy`下面的某个 tests 模块下，除非把 numpy 卸载了才行。

我已经尝试过的办法：

- 更换不同的 venv 目录
- 重装 venv
- 修改 interpreter path（加入本工程 path）
- 重装 numpy、opencv
- 删除.idea、**pycache**文件夹
- ...

均不行，最后还是通过重建了工程，然后把原工程文件全复制过来才解决问题。

我猜应该是原工程的数据库配置文件出问题了？咱也不清楚，也许是那个文件夹的风水不好……

最后，我把那个文件夹拆分了，都换到了新的地方，然后把它删了~

## 在 pycharm 中的 opencv 智能提示

### 最终解决方案

将`cv2`的路径加入环境路径

### 研究概要

1. 来自 youtrack 的相关问题，但都没有解决我的问题

- [Code completion doesn't work for attributes of cv2 module of opencv-python : PY-23426](https://youtrack.jetbrains.com/issue/PY-23426)
- [Code completion doesn't work for cv2 module : PY-35691](https://youtrack.jetbrains.com/issue/PY-35691)

2. 基于 anaconda 的解决方案，接下来我们确实可以基于 anaconda 做 opencv 的分析，但当时在研究 pycharm，所以不予考虑

- [最简单：Mac 安装 python-opencv ｜保姆级步骤｜小白专用｜让报错都去死吧 - 哔哩哔哩](https://www.bilibili.com/read/cv9542204/)

3. 基于国人在 cv 程序里加入路径的方法，终于得到解药

- [python pycharm 中使用 opencv 时，没有代码自动补全提示\_老李的森林的博客-CSDN 博客\_cv2 没有自动补全](https://blog.csdn.net/13011803189/article/details/125125100)

### 研究细节

果然还是中国人才能救中国人！

pycharm 无法自动补全 opencv 已经困扰我一两周了，谷歌所有帖子俺都看了，都不得行！

后来想想，国内肯定也有这样的问题，不然那些学校里的老师和学生都不用 opencv 或者以一种常人无法忍受的姿势使用 opencv 吗？

然后百度一番 就找到解决方案了：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1655801661246-cfa4de9dca3310c127baf62dddb7c8aa8de9badd7da9a2977c77b3289c8b5491.png)

不过尽管问题从标上解决了，本的问题还是没理解，pycharm 理论上应该是可以自动加载的，毕竟 opencv 可不是什么野鸡包，但实在没有精力再去刨根问底了……

怎么会，继续干！

进一步研究会发现，那个 csdn 的小伙子其实改法有点多余，cv2 里面其实已经有那句导入了，所以实际上真正要改的就是把路径加到前面去，因此只要加一句就可以了，而非两句：

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1655801680313-b7e2e9575fa1f885881ab9c06af972fd3f99ad490fb744ba5a11c7cdc5875d92.png)

然后再去思考，这句话的意思其实就是把本文件所在的文件夹加到系统的环境变量里去。

因此，这就很简单了，这句代码也不用加，直接在 ide 里把环境变量配置一下：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1655801704477-9061a1e95a275b8433f87e952d23acd409d810bfc9794f529fa3bca8364bea91.png)

实测可行！

所以目前得到的结论就是，当我们使用 pycharm 创建一个工程时，会自动把当前环境的 site_packages 写入 path。

理论上会遍历这个 site_package 里的包，但是对 opencv 无效，opencv 是基于 so 文件进行动态链接的。

这就导致 ide 正常撸代码时没有 opencv 的提示，但是运行时会动态加载因此不会出错；另外，如果我们使用 python console，这玩意也会执行解释器，因此 cv 在里面也会智能提示。

那么我们的问题就彻彻底底退化成了，opencv 为啥要手动配置到环境变量里去，是版本问题还是设计问题？

接着，顺着 OpenCV 的那个**init**.py 文件进一步跳转到底层，发现了惊人的一幕：我们的缓存文件里的**init**文件，竟然是一个有问题的文件！

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1655801751661-dc4260d7f7d83356d9e34d206826af21be4e21f64c2fea0d743108b8199ef03d.png)

这个问题似乎指向了在 stackoverflow 里有些人重装 python 或者重装 pycharm 可行的问题的解，因为他们的缓存文件跟我一样出现了严重的问题。

因此我们考虑把这个缓存文件夹给完全删除，然后重启 ide 试试。

但是很遗憾的是，再次重启后，仍旧是那样。

但是神奇的是，此时我已经把 cv2 库从我们的环境变量中移除了，然而 IDE 依旧能够智能提示。

这又解释了为啥 stackoverflow 上一些人回复说有些时候有，有些时候又没有。

根据俺们的经验猜测，这是因为 IDE 的.idea 工程配置文件进行了缓存存储记忆，在我们顺利导入某个库之后，之后就都能导入了。

为了验证这个想法，我们把.idea 全部删掉，然后再次重启，确认接下来是否又将无法正常提示。

果然，它再次无法正常智能提示：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1655801837195-b5f8a3f386dde96e55d7bf4965e172cf33c33b71a17d99bbb822f24709a5a5a5.png)

基于此，一个可以接受的方案成型了，那就是每次配置 opencv 的工程时，额外把 cv 的路径加入到解释器的环境变量内。

这个可以通过 IDE 的 UI 操作完成，也可以比较破坏性地钻入 cv 库的实现里去加。

而 jb 之类的 IDE 在首次加完之后，将会把路径写入.idea，后续可以把环境变量清除而不会影响使用。

至于为啥一定要多此一步，是 opencv 的问题，还是 IDE 的问题，俺决定不再思考了，收~

### 剩余疑惑

1. 那个缓存文件为啥长那样，是否就是无法正常加载`opencv`的原因所在？

2. 最终到底是版本问题，还是设计问题，还是自己的操作系统问题？

## console output colorful log

1. download the plugin of `grep console`.
2. configure the colors for different levels of log

![picture 67](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pycharm-howto-1644105854755-76f585c8fce01407998cc37b35761cd7d39b20759bbf3a5236bfdb647bfcc3a4.png)

!!!tip I only checked the `INFO` level and configured its background color to be `green`.

    And now it looks pretty good.

> ref

- [python - PyCharm logging output colours - Stack Overflow](https://stackoverflow.com/questions/20333674/pycharm-logging-output-colours/45534743)

## doc stub on class

It's sad that pycharm doesn't support documentation stub on a class.

For example, on a `TypedDict`.

It only works on functions, parameters and so on.

A property method hack can be seen at: https://stackoverflow.com/a/15537029/9422455

ref:

- [Specify types with docstrings | PyCharm](https://www.jetbrains.com/help/pycharm/using-docstrings-to-specify-types.html#example)

- [How to document class attributes in Python? - Stack Overflow](https://stackoverflow.com/questions/3051241/how-to-document-class-attributes-in-python)

## pycharm vs vscode

### when configure test

pycharm is very nice when you want to configure a unit test, just right click the function you want to and the popup would lead you to auto create a test file next to your code.

<img alt="picture 80" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640679886177-pycharm-howto-6dfa2505546af9c878c5f2d20de2316a5c7542fed98161dc98f9d63765d302e6.png" width="480" />

And this feature, I can't find in VSCode, neither from the extension markets.

## create pycharm shortcut

```sh
/usr/bin/charm
```

<img alt="picture 81" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640680433604-pycharm-howto-3b5a3ea573a1dd307da177bcc18dff75de2f2c72c5e8cedb028daffbfe8d5113.png" width="480" />

ref:

- [python - Launch Pycharm from command line (terminal) - Stack Overflow](https://stackoverflow.com/questions/22133861/launch-pycharm-from-command-line-terminal)

## How to sort parameters of a function call

This is a very old question that I struggled with for a long time, since I started to learn python, whenever I was using pycharm, anaconda, jupyter, or so on.

### Parameter Info

In VScode, the parameter hints can trigger by ` ⇧ + ⌘ + space` default(which conflicts with MacOS's SpotlightSearch) so that I changed it into ` ⌥ + P` as the following shows:

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639938002501-056940fa4d3449daffc5fd2678b439a51b48bba99305cf872a8207ef3ee21e4e.png" width="700" />

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639938037918-e4eb856d664e1cf1c4a4fc65dea40cb10df26a6005871e56174ecb38eb74ef0a.png" width="700" />

The experience VSCode represents the function parameter info is good and impressive, while in pycharm not.

<img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639938689611-22ec571e92b6ed75024db1f5d3c17da768bd48725c87bf5f9d3368fffc1c6a32.png" width="720" />

We can easily found that contrary to the VSCode, pycharm's parameter info lacks of the detail instructions which seems a bit weak and not too nice for those who are newbies or forgot how to use this function.

### Parameter Suggestions

In VSCode, the parameter is triggered automatically or by typing ` ⌃ + Space` and sorted by groups (which is the most import), so the user can easily get to know what parameter to choose.

<img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639939162390-beab8f849bd3fd3470c2f76b070c254698641a7a56ba7be351dde04af48c41ba.png" width="720" />

This are quite corresponding to developers' intuition, while in pycharm things again become hard to understand and even unbearable.

<img alt="picture 14" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639939312819-719e5bc6600abbecc2c7853eae1f5623d6e055cfed5a8d44a154fecefe818df0.png" width="720" />

Why should the pycharm put those words such as `lambda`, `None`, `not` in the first place? Does my system goes wrong?

However, when I tried to search in the web, I am shocked to find the official jetbrains reply the result is out of intelligence, which seems too absurd and unacceptable since we can then find all the inner parameter are at the last.

<img alt="picture 15" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639939567706-3649dbfbd89fdfc98a0c8fe5f40a7ef7e3442603d20c4fef8d2b24521c0dec06.png" width="720" />

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639939719172-403266211b6d6bfff628a8b51fae2110d94fdd53db80ed2e368835829ecd9bb8.png" width="480" />

ref:

- [Autocomplete - sort by method/parameter/class – IDEs Support (IntelliJ Platform) | JetBrains](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360007074700-Autocomplete-sort-by-method-parameter-class)

- [Code completion | PyCharm](https://www.jetbrains.com/help/pycharm/auto-completing-code.html)

- [PyCharm: Why does `audioop` get prefered? - Stack Overflow](https://stackoverflow.com/questions/69352610/pycharm-why-does-audioop-get-prefered?noredirect=1#comment122796385_69352610)
