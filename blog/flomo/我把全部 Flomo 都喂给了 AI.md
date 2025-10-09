两年前，我就一直有做一个 AI 助手的想法，区别于大厂的 RPA（替自己点外卖买机票）、知识库（上传一堆工作文档），我更侧重”**我**“本身的数据，尤其是社交数据。

而我过去二三十年所有的数据，按照大模型喜欢的分类，主要分为以下几种：

- 短图文：
  - QQ 空间的说说
  - 微信朋友圈
  - Flomo、小红书、即刻等社交 App
  - ……
- 长图文
  - QQ 空间的日志
  - 微信公众号文章
  - 博客、Typora、Obsidian 等写作 App
  - ……
- 复杂模态
  - QQ、微信等聊天记录
  - 抖音、视频号、bilibili 等视频数据
  - ……

**理论上，拿到所有我的社交数据，并设计一种合适的压缩机制、分层或者向量化检索办法，就可以构建一个拟合我非常好的个人助手**。

由于大厂不具备渗透用户个人数据的合法性，因此这种事情，只能我们自己来。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/30eacace05f67ca7e15b0f3631c2edd5.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---

由于我近几年都是在 flomo 这款 App 里陆陆续续记录自己的随感，对它又爱又恨，所以今天我们先解锁一下如何把我们的 Flomo 都提取出来喂给 AI。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/0505fb50c9038e6d3e2780b83db1f76c.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

首先说明一下，flomo 官方是支持导出的，但仅限于选中某个标签后：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/04119ec33a60ae2f92e0e2a7d8d46b6d.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

此外，也比较尴尬，每 7 天只能导出一次：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3ef0cfe1f2191bfebbee3a7ef0209e66.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但更尴尬地是，我记得这两天我有导出过一次，但似乎卡在了中途。

因此好像就没有消耗我的 credits，这才允许我这次又能导出一次。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7786a9d1219ddf765fb726a9ba96f1fb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

导出后解压是个文件夹，里面有个主 html，按日期存着我们的所有图片文件。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1437603a564af03cdf835c11dae49aac.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

怎么说呢，有点像单反相机的那种存储方式，只不过没有 thumbnail。

另外，导出后的网页不是静态的，是独立于 flomo 的另一套 UI，支持筛选。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2cbf4464010db954209ad78d38422d14.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

不过还有点小 bug，因为我是在 #VibeCoding 体验 tag 下（总共 24 条记录）点击导出的，但它一共导出了 810 条，关键是这 810 条也不是我的全部 memos，全部应该是 1066 条。

总之，我还挺好奇 flomo 自带的导出是什么数据结构的，我确实没想到是一个 html。

可能是产品经理想了一下导出的需求，可能是方便用户自己管理筛选某条 memo 吧。

值得注意的是，flomo 官方页的 memo 展示里，图片是像朋友圈一样悬挂的；但导出页里则是像写文章一样插入的：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/56143482bb2a7f5df08d8c574ae02942.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---

但很显然，由于 html 里混杂着各种标记符、空格、图片地址等，整体是较大的（429KB）。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e023fcf2c714c47f5815455a02f871c9.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以并不太适合喂给 AI。

**目前在 200K token 以上的大模型只有 Gemini 2.5、GPT4.1、Llama 4**，但我们的**主力 Coding 模型是 Claude Code （200K）**，因此需要一些变通办法。

![LLM上下文长度对比，source: https://www.vellum.ai/llm-leaderboard](https://poketto.oss-cn-hangzhou.aliyuncs.com/8aa6aa5d84b8c27193a13934be70e2af.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

一种办法，是大力出奇迹，就使用 gemini 等超长窗口模型。

但更好的办法，是我们先对我们的内容进行一些压缩。

很显然，在搭建 AI 理解个人超长图文这个场景里，我们可以做粗细两套检索系统。

- 粗检索系统：所有图文都向量化
  - 早期：只检索文本
  - 中后期：对图片逐步增加图转文辅助信息，以支持混合图文检索
- 细检索系统：针对局部的图文（比如某条 memo），组合一起丢给多模态 LLM 进行分析

因此，我们不妨先做一版只让 AI 读取文本的粗检索系统（V1）。

我们首先需要获取所有的 memo，然后对它们进行压缩编码。

---

至少有两种获取的办法。

第一种是基于 flomo 的官方 API。

> 做好产品不易，我们强烈建议在有预算的情况下付费使用所有正版产品。

![source: https://help.flomoapp.com/advance/api.html](https://poketto.oss-cn-hangzhou.aliyuncs.com/beec1c86393878221f42c6201f30fc00.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

第二种是去 github 淘淘运气。

果然 github 上有一些基于 flomo 的开源仓库，它们允许我们输入 flomo 的 token，然后模拟前端 api，获取 flomo 的 memo 记录。

但很可惜有点 bug。

我也没有时间和信心去细看，毕竟是别人的仓库，所以就直接丢给 cc。

结果它非常不辱使命，很快就搞定了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3be5aac1ada223ee22b573147da86ce8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

原因是 Makefile 里的版本号要进行修改。

这我真不会，只能高喊一句：**CCNB**！

后来，很快，我就用 cc 继续魔改这个开源库，越改越上头，加了很多有用的命令：

```shell
➜  flomo-cli git:(main) python -m cli -h
usage: flomo [-h] {list,search,config} ...

Flomo 命令行工具 - 管理和查看你的浮墨备忘录

positional arguments:
  {list,search,config}  可用命令
    list                列出备忘录
    search              搜索备忘录
    config              配置管理

options:
  -h, --help            show this help message and exit

➜  flomo-cli git:(main) ✗ python -m cli list -h
usage: flomo list [-h] [-l LIMIT] [-f {json,table,markdown}] [-c] [-q] [-o OUTPUT] [--url {full,id,none}]
                  [--no-meta] [--min] [--order-by {created_at,updated_at}] [--order-dir {asc,desc}]

options:
  -h, --help            show this help message and exit
  -l LIMIT, --limit LIMIT
                        限制返回的备忘录数量
  -f {json,table,markdown}, --format {json,table,markdown}
                        输出格式 (默认: json)
  -c, --compact         紧凑的JSON输出
  -q, --quiet           安静模式，不显示进度信息
  -o OUTPUT, --output OUTPUT
                        导出到文件 (指定文件路径)
  --url {full,id,none}  URL展现形式: full=完整URL, id=仅显示ID, none=不显示 (默认: full)
  --no-meta             不包含元数据 (创建时间、更新时间等)
  --min                 最小化输出 (仅内容和基本信息, 适合喂给大模型)
  --order-by {created_at,updated_at}
                        排序字段 (默认: created_at)
  --order-dir {asc,desc}
                        排序方向: asc=升序(旧到新), desc=降序(新到旧) (默认: desc)
```

使用起来也很简单，先配置 token（等会会告诉大家怎么拿 token），然后就可以导出我们的记录了。

```shell
➜  flomo-cli git:(main) python -m cli config --token "14798930|Om8f*******NX018kuPSx"
认证token已保存

➜  flomo-cli git:(main) python -m cli config --show
当前token: 14798930|O*****************************NX018kuPSx
```

导出有很多种选项，比如按照表格格式，或者 markdown 格式，甚至最大压缩格式：

```shell
➜  flomo-cli git:(main) python -m cli list --order-dir desc --limit 2 -f table
正在获取备忘录...
共获取到 1076 条备忘录
序号 | 创建时间          | 内容预览
--------------------------------------------------
 1   | 2025-08-04        | 今天终于把一年前vibe coding刚火起来的时候扬言要2
 2   | 2025-08-04        | 测试新增一条，应该会变成1036

➜  flomo-cli git:(main) python -m cli list --order-dir desc --limit 2 -f markdown
正在获取备忘录...
共获取到 1076 条备忘录
# Flomo 备忘录

## 1. 2025-08-04 20:43:38

今天终于把一年前vibe coding刚火起来的时候扬言要2小时内做一个新版flomo的计划付诸实践
……

➜  flomo-cli git:(main) python -m cli list --order-dir desc --limit 2 -f markdown --min
正在获取备忘录...
共获取到 1076 条备忘录
1|2025-08-04|今天终于把一年前vibe coding刚火起来的时候扬言要2小时内做一个新版flomo的计划付诸实践  它由两部分构成，一个是基于py的 flomo-cli 核心api系统  一个是基于rust、ts的flomo-ui 桌面软件 flomo garden（由于没有Windows，暂时只支持MacOS，下载地址：https://github.com/MarkShawn2020/open- flomo-ui/releases ）  以上两个都支持填写bearer token后批量获取自己
的memo、存储到本地数据库、展示、并导出md、json、table等格式，其中md还支持压缩以喂给大模型  最后，为了辅助大家轻松获取bearer token，我还写了一个whats-my-token的谷歌插件  一条龙服务，让你不迷路
2|2025-08-04|测试新增一条，应该会变成1036
```

加上 `-o` 参数后，就可以把输出导出到文件，我们测试一下不同格式下的输出大小。

```shell
➜  flomo-cli git:(main) l ~/Downloads/my-flomo*
-rw-r--r--  1 mark  staff   370K  8  4 23:23 /Users/mark/Downloads/my-flomo-data.md
-rw-r--r--  1 mark  staff   276K  8  4 23:23 /Users/mark/Downloads/my-flomo-data.min.md
-rw-r--r--  1 mark  staff   455K  8  4 23:28 /Users/mark/Downloads/my-flomo.min.json
```

我们刚刚知道 flomo 官方导出了 804 条 memos，文件大小为 429KB，折合 1076 条为：574KB。

基于此我们可以获得各种格式下的压缩比为：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d728b9bb2f42a84c481fae4d1e09ee56.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

可以看到，我们使用专门为大模型导出的压缩比达到了惊人的一半以下。

而输出内容是什么呢？

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1d4eb4e0e674ba13849f32c804c15a99.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

可以看到，就是一行行输出，每行一条 memo，包含序号、日期以及完整的具体内容。

**你就可以拿着这个压缩版的 markdown 文件，丢给 ai，去分析，去对话了**。

---

很显然，在 vibe coding 时代，要想卖出自己的作品（暂且不谈产品与商品），一个好看的 GUI 是必不可少的。

所以我今天还额外花了几个小时给大家做了一个精美的 GUI （**Flomo Garden**），方便大家解锁更多的功能。

![Flomo Garden 首页](https://poketto.oss-cn-hangzhou.aliyuncs.com/e9414a5091912a18724ed6e4e7c2d9cb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

只需要在设置里填写好自己的 token 即可：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/c0275e9274ba89c3f5dd59568f754cf7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

它同样支持导出功能，并且完全可视化，支持预览：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/b0e46c8d91fe2acbd9c88329b20a9d60.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

同样支持压缩模式：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1961fb77ecdc31045c4b2183ca087050.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

还支持更好的搜索体验（尽管 cli 版本也支持）：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d4d259740e6d5623b45c5e197e5dfa7c.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

你可以直接访问：https://github.com/MarkShawn2020/open-flomo-ui/releases 下载，目前完全免费。

---

好了，我们现在回头再讲一讲怎么拿到 flomo 的 token。

你同样有两种办法。

第一种是土办法，打开 F12 后，手动去找。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d147da54f2a6f6ba97972ef1a0b8f7b0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但是今天，你不必了，我又开发了一款超级好用的谷歌插件：**Whats My Token**，安装后直接刷新即可自动检测到所有网站里涉及的 bearer token。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/b6f0f19b72a413f95b74046fba30ce70.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

你直接一键复制即可。

同样感谢 CC，没有它，我很难做到如此。

你可以访问 https://github.com/MarkShawn2020/chrome_whats-my-token 下载，永久免费。

---

好了，以上就是怎么把 flomo 全部喂给 AI 的各种姿势，赶快你也自己试试吧~

---

Flomo 是我为数不多又爱又恨边用边骂的产品，仅次于claude code、cursor、windsurf等。

希望人类意识，能因更多像这样的美好产品、故事，而永存。

**Please fight for our human's consciousness.**

2025年08月04日23:51:36
