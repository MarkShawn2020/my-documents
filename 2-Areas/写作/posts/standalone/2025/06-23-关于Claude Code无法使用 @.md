---
author: 南川
publishDate: 2025-06-23
articleTitle: 关于 Claude Code 无法使用 @
articleSubtitle: 以及如何更好地debug
episodeNum: Vol. 44
seriesName: 
tags:
  - Claude-Code
  - 软连接
  - Debug
---

> 一句话总结：因为有破损的软链接。

---

## 背景

回忆了一下，是前几天为了赶一个项目，在电脑 C 上把某项目 B 软链接到了项目 A 内，后续又由于不断地更换目录与重命名等，导致软连接破损。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/86b327615ca4b3989d947dda123d1ddb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

然后就出现了使用 claude code 时，按`@`键无法获得智能提示的 bug。

期间对比了另一台电脑 D 没有这个问题（虽然它也用了软链接，但是没有经历多次重命名导致破损）。

今天早上用回电脑 C 时，发现没有智能建议是一件几乎无法正常开发的阻碍。

值得注意的是，一个月前我们使用 claude code 时，刚开始还没有@功能，也用的很开心。

这才一个月，当 claude code 已经深入到我们的开发流程之后，发现这个事情就几乎无法忍受了。

从这点上来说，专业开发者对工具还是很 picky 的，这也是我们很少使用目前主流 agent（尤其是通用 agent 产品）的原因。

---

## debug 中的错误判断

想说一说调试过程中的一些思考，帮助以后更快地 debug。

期间，我有两次错误的判断。

第一次判断，是在电脑 C 里 `~/.zshrc` 里配置了自定义的 wordchars，这样我就能在 iterm 里按住 opt 键，然后左右跳转到一些中文标点（否则只能跳到下一个英文单词）。

```
# ref: [iTerm2中文标点跳转配置 | Google AI Studio](https://aistudio.google.com/prompts/1aU_p9ftokgT9OzhBdK9hK-z4qsLdZyFK)
# 将中文标点符号视为单词分隔符
WORDCHARS='*?_-.[]~=&;!#$%^(){}<>。，！？'
```

但我是很清楚的，刚配完这个功能后，calude code 应该是 work 的，并没有罢工，但在 claude code 罢工后竟然怀疑这个，然后取消这个，依旧无解。

第二次判断，是今早尝试重装（大部分情况下可以解决问题）之后发现还是无效，我怀疑是因为电脑 C 是 M 芯片，但电脑 D 是 Intel 芯片，会有环境差异。

但这个也完全经不住推敲。

因为我非常相信 claude code 的官方团队几乎清一色 M 芯片，另外我电脑 C 也一直是 work 的，只不过突然不 work 了，所以不应该是系统的问题。

我为什么能怀疑出这么多显而易见的错误推敲呢？

可能是因为我实在不知道从 @ 能用到 @ 不能用期间电脑到底发生了什么。

当你对一件事的发生（什么时间什么地点，前后差异）甚至定义（什么叫@，专业术语叫 autocomplete）都不清楚的时候，你会完全丧失基本的判断与行动力。

---

## 如何解决的？

最后怎么解决的呢？

先是在 claude code 报了一个 issue：`/bug`。

发现在新加坡低质量节点（无法通过 claude 初始化）上，这个 bug 都无法提交成功。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/41577574b02f7580ddeca67bf85bf497.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

在美国高质量节点上可以。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d40a19d641ddfa219d02699a1ab48c74.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

```ad-tip
但这些节点都是可以用于正常工作的（通过claude初始化后，即使节点质量比较低，但依旧不会被ban。这个应该很多人都不知道）。
```

顺带提交了个 issue，后来找到问题后就关了：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9481ff0ddff71d769baed3e45ff4ca01.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

参考 https://github.com/anthropics/claude-code/issues/1397#issuecomment-2950171924 。

---

## 如何确认是否有破损文件

依旧参考上述链接，使用命令：

```
rg --files --follow . >/dev/null
```

如果提示 `zsh: command not found: rg`，则：

```
brew install rg
```

再次运行即可（以下就是找到有破损链接的结果）：

```
➜  py git:(main) ✗ rg --files --follow . >/dev/null
rg: ./td: No such file or directory (os error 2)
```

正常情况下会没有输出。

## 一些有用的命令行

我发现官网还挺鸡贼的，都没给出（不过确实也不是那么重要，可以理解）。

可以参考 https://www.reddit.com/r/ClaudeAI/comments/1kduobf/claude_code_still_charging_me_despite_having_max/

但它的问题和这个还不太一样，而且比较有破坏性，经常建议你 `rm -rf ~/.claude` 而非是备份后再删除……

如果只是卸载的话：

```
npm uninstall -g @anthropic-ai/claude-code
```

查看有哪些 claude：

```shell
➜  py git:(main) ✗ which -a claude
/Users/mark/.nvm/versions/node/v20.18.1/bin/claude

```

可能会有多个，我之前就有多个（有一个在 homebrew 下），后来我就把它删了。

阻止 claude code 自动更新（如果需要指定版本用于调试的话）：

```
claude config set -g autoUpdaterStatus disabled
```

## 最终比较有用的收获与原则

1. 指定工具相关的问题，优先 github issue 搜索：https://github.com/anthropics/claude-code/issues
2. 排查类似突然不奏效这样的问题，优先复盘那段时间干了什么，动了哪些变量，并结合 1
3. claude code YYDS（今天又是给 claude code 带货的一天）！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3bed37b54f3878d3884f5bf12590c97b.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 如果你也对 claude code 感兴趣

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/39cc1d58d4ca16cd11d3ef33bf4b8597.JPG?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 如果你对技术大类感兴趣

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/460bee0383fce881babe66ab81434fc5.JPG?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
## 如果你对Agent、AI大类感兴趣

微信加我，发送个人简介，一起交流，感谢！

