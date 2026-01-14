---
articleTitle: 如何更好地管理你的 Claude Code
publishDate: 2025-06-27 
tags:
- 开源
- Claude-Code
- 配置管理
- 开发工具
- Vibe-Coding
categories: 技术实践 
description: 当 Claude Code 配置文件破损且体积膨胀到 6MB 时，我开发了一个管理工具来解决这个问题 
articleSubtitle: 发布 CCM 以及 VC101 社区冷启动
author: 南川 
episodeNum: Vol 47.
---

今天早上正准备打开 claude code 干活时，发现程序崩了！

后来发现是 claude code 的配置文件坏了，后面不知道为啥有两行多余的内容。

昨天还没事的，这真不知道是因为啥。

怎么发现的呢？

访问能坚持 json 格式是否合法的在线网站 https://www.json-online.com/check/ ，然后把 claude code 的配置文件复制粘贴上去即可，比如 `cat ~/.claude.json | pbcopy` 可以一键复制。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/88e9cbe35124f636c0cf63cd31644476.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

我还尝试使用 `jsonrepair` 这样的库进行自动修复，但它只能修复半结构化的 json（比如流式输出时，这对大模型场景来说非常有用，可以实时渲染大模型的输出，尤其是图表等场景）。

而我们是多了一串字，这属于 json 破损，修复不了，所以还是手动修复吧。

这是我们今天遇到的第一个问题：修复破损配置。

---

但紧接着，我看着 3600 多行总计 6 兆多的配置文件，感到一股强烈的冲动，这也太大了！

回顾了一下一周以前（期间我重置过一次）的交流，一天一兆一年得三百兆，_可能会大幅拖慢 claude code 的运行与检索速度（需要验证）_。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1bb4228a020b856124cfee06abdf04fb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以我使用 `jless` 工具仔细分析了一下文件结构，它可以可交互地钻取查看 json 文件：

```shell
jless ~/.claude.json
```

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/6e63b3b0b9257769b0e620886d384bf5.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

可以看到 claude code 配置文件里存储了大量的信息，包含配置与会话历史。

会话历史在 `projects` 键下，一共有 26 个，存储了所有的对话内容（仅包含我的问题，不包含它的回复）。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/40d27eb32226abe1598f1ab7645d16c6.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

**由于图片、文件等都是基于 base64 直接编码塞进 prompt 的，这正是导致我们文件越来越大的最主要原因！**（参考微信存储空间）

因此，为了更好地分析与管理我们的 claude code 会话，我就让 claude code 自己做了一个工具，命名为 **`vctool-claude-code-manager`，它可以智能地提取出项目/会话列表、统计体积、支持排序**！

```ad-tip

目前，我们已经将该工具开源发布到了npm仓库，您可以 `npm i -g vctool-claude-code-manager` 下载安装，然后 `ccm stat` 使用。
```

以下就是其实际体验截图：

```shell
➜  ~ ccm
Usage: claude-code-manager [options] [command]

A CLI tool to assist with Claude Code vibe coding workflows

Options:
  -V, --version   output the version number
  -h, --help      display help for command

Commands:
  stat [options]  Display Claude Code session statistics
  help [command]  display help for command


➜  ~ ccm stat -h
Usage: claude-code-manager stat [options]

Display Claude Code session statistics

Options:
  -w, --width <number>  Maximum display width (default: "80")
  --sort-by <method>    Sort method: ascii, size, +ascii, -ascii, +size, -size (default: "ascii")
  -h, --help            display help for command

```

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/c57d31b28945f027213802a5d43de509.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

按体积倒序（可以看到最大的一个项目直接干掉了 5MB）：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7e8ac7eb0386ae1d15cf5c36448f4298.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

支持备份：

```shell
**➜  vctool-claude-code-manager git:(main) l ~/.claude*.json
-rw-r--r--@ 1 mark  staff   6.2M  6 27 12:27 /Users/mark/.claude-2025-06-27T11:56:28+0800.json
-rw-r--r--  1 mark  staff   596K  6 27 18:03 /Users/mark/.claude.json

➜  vctool-claude-code-manager git:(main) ccm backup
✓ Claude config backed up successfully
  Source: /Users/mark/.claude.json
  Backup: /Users/mark/.claude-2025-06-27T10:06:41+0800.json

➜  vctool-claude-code-manager git:(main) l ~/.claude*.json
-rw-r--r--  1 mark  staff   596K  6 27 18:06 /Users/mark/.claude-2025-06-27T10:06:41+0800.json
-rw-r--r--@ 1 mark  staff   6.2M  6 27 12:27 /Users/mark/.claude-2025-06-27T11:56:28+0800.json
-rw-r--r--  1 mark  staff   596K  6 27 18:03 /Users/mark/.claude.json
**
```

备份之后，我们还可以为目前的 claude code 配置瘦身（清空 projects 列表，1.0.5 以上支持），可以看到瘦身后体积从 596k 降低到了 504k。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/c0c6a1a716d8f974491fd187c259696e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

它还支持不少参数，可供灵活选择：

```shell
➜  ~ ccm slim --help
Usage: claude-code-manager slim [options]

Remove project entries from Claude config (keeps current directory by default)

Options:
  --force            Skip confirmation prompt
  --include-current  Also remove current directory from projects
  -h, --help         display help for command

```

当然，如果你不想使用我们的工具，也有更基础的办法可以做到，比如基于 `yq`：

```shell
brew install yq
yq -i '.projects = {}' ~/.claude.json
```

但这样就全部清空了，没法像我们的工具一样，能做到更灵活的控制。

不过如果你愿意的话，也可以，毕竟：

> After the night I burned all memory, my dream becomes transparent, as I trashed all yesterdays, my step becomes lighter.
>
>
> 有一个夜晚我烧毁了所有的记忆，从此我的梦就透明了。有一个早晨我扔掉了所有的昨天，从此我的脚步就轻盈了。
>
>
> ——泰戈尔

现在，`vctool-claude-code-manager` 已经发布到 npmjs，欢迎大家下载使用与多提意见！

- npmjs: https://www.npmjs.com/package/vctool-claude-code-manager
- github: https://github.com/the-vc101/vctool-claude-code-manager
- 一键安装：`npm install -g vctool-claude-code-manager`
- 如何使用：`ccm --help`
- 主要功能（分析项目列表）：`ccm stat`
- 其他功能：
  - 备份：`ccm update`
  - 瘦身：`ccm slim`
  - ……

第一个用户已经成功体验上！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5b97e0725b5579fb95e31dd79da3288a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3d27e54aa73aac31c7181cb1cc6ca66e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---

好地，以上就是我们本期的主要内容。

但 **One More Thing**！

注意我们的 github 链接，有没有什么诡异的发现？

没错！

**我们联合 WayToAGI、AI 产品榜、火山、百度、腾讯、阿里等朋友，搭建了一个 Vibe Coding 101 社区平台！**

即日起，你可以访问 `https://vc101.cs-magic.cn` 查询 Vibe Coding 相关的文章、工具、黑客松、资源链接等。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/c42dcc413003da46849aee0956f18660.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ecc5db231e85fe5e2badc8f6a5997eb0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

这个平台目前还处在一个非常早期的探索阶段，如果你感兴趣，欢迎加入一起交流探讨与共建！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7b31959a9593255345d0313def2087da.JPG?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
