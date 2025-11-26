> 感谢 Claude Code，感谢 Dify，感谢时代，狗头保命先。
>
> ![](https://poketto.oss-cn-hangzhou.aliyuncs.com/101d816ebe5610f0ce4e4828b17b3049.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

今年我们用 Coze、Dify 给客户交付了一些项目，他们普遍都有使用 AI 进行分析，甚至私有化部署的需求。

我原先也比较单纯，其实客户也根本不知道什么 Coze、Dify 啥的，他们只知道必须要用 AI，必须要用 Deepseek。

说实话，他们其实也不是很清楚 AI、Deepseek 这些东西到底如何，他们只知道别人在用，国家也在推，以及，他们知道应该是一堆文件啪地丢进某个地方，然后啪的一下一堆文字或者什么的吐出来。

当他们找到我说隔壁的 xxx 已经做了一个 yyy，效果 zzz，我们得赶紧做一个 aaa，我好拿着去见 bbb，然后我们就可以 ccc。

基于我之前头部大模型公司的短暂工作经验，我的第一个问题是，你们到底是想拿订单还是想融资，这两个不一样。

如果是前者，我框框框用 AI 给你们（哦不我们）做个 demo，怎么酷炫怎么来，客户一定嘎嘎地给我们鼓掌，然后啪的一下钱就打过来。

如果是后者，那你给我找一两个教授负责设计与评估，再找一二十个研究生负责测试与写报告，我们做一个牛逼嘎嘎的 agent，每天一个小迭代，每周一个大版本，每个月一次汇报，每季度一个里程碑。

***Which is what all the top AI Founders / ProductManagers / Engineers are exactly doing everyday.*** 

但他们似乎无法理解后者，但也似乎无法满足于前者：我不管你什么 bench 不 bench，我要的是一个客户看起来牛逼哄哄的 agent，预算是这个数，时间是这个数，人手是这个数，走不走？

得了。

走起。

（以上纯属段子，如有雷同，纯属巧合）

---

在我们公众号（手工川）往期的文章中，已经持续整理了 coze、dify 的部分实战经验，如果你感兴趣，可以从头开始学起：

- [AI 实战 01. 如何用 Coze 搭建 BP 智能评估系统（上篇）](https://mp.weixin.qq.com/s/WOfDzdOcsCqRpMf3_-XQhQ)
- [AI 实战 02. 如何用 Coze 搭建 BP 智能评估系统 02](https://mp.weixin.qq.com/s/3sbeESXExyHVo2ldQekOhw)
- [AI 实战 03. 如何在微信小程序中集成 coze](https://mp.weixin.qq.com/s/zwtH6fakXGe1i6dYC3cy2A)
- [AI 实战 04. Dify + Deepseek 私有化部署](https://mp.weixin.qq.com/s/cmhv4maJPt6nSRgkvpgh4A)
- ……

但上述文章只告诉了你在 coze、dify 等体系里怎么调用各种 api、怎么设计各种架构实现。

今天，我们基于强大的 claude code，隆重地给大家推出最新的系列：Vibe Coding 秒天秒地秒一切从 0 到 1 到 10 到 100 新手级保姆级管家级满血实操经验教训过程结果分享……

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d725a4c4853bdc73363b79c546971bcf.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

**恰好前几天 coze 刚开源，所以我们来爆改 dify！**

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e3303a840dedc95f0f159fba76daebac.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![截止2025年07月28日, source: https://www.star-history.com/#langgenius/dify&coze-dev/coze-studio&n8n-io/n8n&Date](https://poketto.oss-cn-hangzhou.aliyuncs.com/3ee290d0fd6f94dd88c2975ed1009b3a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

> btw，恭喜 Dify 2025 年 7 月份 Star 突破 10 万大关！

**为什么是 dify？**

因为它开源，甚至还被骑脸输出过。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/8dd6ac018f26635070c407cb14c0b2df.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

既然别人能改，还能改的如此猖狂，那说明这玩意确实好用对不！

**而为什么是 Vibe Coding？**

来，请看手工川公众号往期 VCR：

- Vibe Coding 相关的经验、交流：
	- [Vol 47. 如何更好地管理你的 claude code 以及 VC101 冷启动](https://mp.weixin.qq.com/s/mtc3tN8-SA_om0R4JzHCBA)
	- [Vol 48. Cursor 北京 Meetup Takeaways：人机协作的最佳实践与未来畅想](https://mp.weixin.qq.com/s/nbUmosXXuRYM1O1bXEjgXw)
	- [Vol 51. Claude Code 实战交流与最佳实践](https://mp.weixin.qq.com/s/8fEPWeSF2d7Xhbo8OBzSeg)
	- （目前重点推荐）[Vol 59. 一代人有一代人的抽象：Vibe Coding 正在重新定义软件工程](https://mp.weixin.qq.com/s/yb6mPKisaSg8J2COdV2tWQ)
	- ……
- Vibe Coding 能干嘛：
	- [Vol 53. N-Clip：Claude Code 给自己写了个剪切板](https://mp.weixin.qq.com/s/kjfJ-Pp0XVAgLMujXwNlZQ)
	- ……
- Vibe Coding 可能遇到的问题：
	- [Vol 42. 关于 Claude Code 在国内无法使用，以及各种代理问题的共性](https://mp.weixin.qq.com/s/tcWe2K-AOjED4oaaVcciwQ)
	- [Vol.44 关于 Claude Code 无法使用 @](https://mp.weixin.qq.com/s/m89KVpJ0IcQ1rJzdhrLw5A)
	- [Vol 49. Vibe Coding 的坑到底有多少？](https://mp.weixin.qq.com/s/ucMfmsaXLP8cJCO3XHHsMQ)
	- ……
- 如果你还不知道什么是 slash command，可以看：
	- [Vol 52. Claude Code Command：被严重低估的效率神器](https://mp.weixin.qq.com/s/KzrkXnR3nrq-oIxFHU8xmw)
	- [Vol54. Vibe Coding 技巧：实用的 /checkpoint 命令增强项目管理](https://mp.weixin.qq.com/s/P5OmJH8gwr7dq8RQv0MZmQ)
	- [Vol 55. 你离顶级 Vibe Coder 至少差一个超级指令](https://mp.weixin.qq.com/s/TgXRZE33yiUzpBOVAai08g)
	- ……
- Vibe Coding 相关的热点与探索：
	- [Vol 46. Gemini CLI 一夜极限测评，谷歌掀翻了 Vibe Coding 的牌桌](https://mp.weixin.qq.com/s/MNJ2PWRFiNy8rW_nGCkI2w)
	- ……

> Vibe Coding 正在深刻改变工程师的开发范式，也在加速改变软件工程的生产关系，这是软件历史上百年未曾有之大变局，欢迎 follow 我们一起探索！

---

## 从调参到工作流到知识库到私有化部署到二开，Dify始终都在

话说回来，本来我也没有想改任何 Dify 的冲动，毕竟最早的时候 Dify 是主打的低代码，大家可以在 Dify 的工作区里很方便地搭建一个大模型调用节点，然后非常轻松地调节待使用的模型与参数，然后将其转化为可被直接调用的后端 api。还是非常方便的。再后来才有了知识库、有了工作流、有了 Agent 等等。

而我们给客户交付的产品与服务，往往是基于客户的场景针对性的开发，比如只需要大模型调用、知识库、AI 助手等等，什么 chatflow、workflow 啥的听都听不懂。

因此我第一反应是自己写一个独立的前端，部署在独立的服务器上，然后在 dify 官方云环境里配置好大模型或者业务 workflow，暴露出 api 给我们的前端或者服务器。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e9ec4c6e4bf0668f86789283cddc5eca.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但这种方案有诸多问题。

第一个问题，是用户的数据不能出网，需要完全私有化（也就是数据库、文件存储、大模型调用全部都要私有化）。

第二个问题，是 dify 的官方云环境对工作流数量、文件数量、文件容积等有严格的限制（这也不难理解，毕竟云端是 2C，一个用户 1 个 G，一万个用户就 10 个 T 了，非常吓人）。

所以答案都指向了一个词：**私有化**。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/fe99d7776155ca745884aaf8dcb08848.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---

私有化至少有两种办法。

一种是基于 docker，直接拉取 dify，然后本地化运行，暴露接口，这样我们就拥有了一个独立运行的 dify 实例，开箱即用跑在 localhost 上的 dify 网页，在里面可以搭建工作流、知识库等，参考：https://docs.dify.ai/zh-hans/getting-started/install-self-hosted/docker-compose。

```shell
# 假设当前最新版本为 0.15.3
git clone https://github.com/langgenius/dify.git --branch 0.15.3
cd dify/docker
cp .env.example .env
docker compose up -d
```

而这个 dify 实例，一般我们是不会直接给客户看的，所以我们需要额外写一个前端，把 dify 的能力像微服务一样嵌在这个前端里（甚至也会额外写一个独立的后端，用于对接旧有的 api 等）。

另一种就是基于源代码二开，参考：https://docs.dify.ai/zh-hans/getting-started/install-self-hosted/local-source-code。

```shell
git clone https://github.com/langgenius/dify.git
# 分别运行中间件、后端、前端等，具体参考：https://docs.dify.ai/zh-hans/getting-started/install-self-hosted/local-source-code
```

但我最近发现，直接修改 dify 源代码（而非只作为一个 docker 服务）会有更大的优势，原因如下：

1. dify 的前端是基于 react+tailwind，后端是 python 的 flask，这些正好是当前主流的技术栈，也是我最熟悉的技术栈，改起来完全没压力
2. dify 需要单独 2-4 个 G 左右的运行空间，对于普通的服务器（4 核 8G）来说，如果我们再独立开一个前后端（而放着 dify 自己的前后端不用），实在是有点面要买两碗吃一碗倒一碗的奢侈了
3. 【对运维人员更重要】直接修改 dify 的源代码，把业务代码嵌入 dify 的框架，而非把 dify 嵌入自己的业务代码框架，有利于**直接基于 dify 的 docker 环境一键部署**，这是最显著的优势，成为高质量交付的关键
4. 有 AI 啊，魔改代码不要太方便！

---

## 潘多拉魔盒的开始

### Step 1. 准备代码环境

参考 https://docs.dify.ai/zh-hans/getting-started/install-self-hosted/local-source-code ，略作修改。

我们的新产品名取名 lovme。

1. 下载代码并建立分支

```shell
# 1. 下载代码
git clone https://github.com/langgenius/dify.git lovme
cd lovme

git checkout -b lovme
```

2. 独立命令行启动后端

```shell
cd api
cp .env.example .env
awk -v key="$(openssl rand -base64 42)" '/^SECRET_KEY=/ {sub(/=.*/, "=" key)} 1' .env > temp_env && mv temp_env .env
# 安装uv（mac我就用brew了）
brew install uv
uv sync
uv run flask db upgrade
uv run flask run --host 0.0.0.0 --port=5001 --debug
```

ok 的话，我们要初始化一下管理员账户（具体可以参考：[私有化部署账号密码存在哪里了？ · Issue #93 · langgenius/dify](https://github.com/langgenius/dify/issues/93)）：

```shell
flask reset-password
```

3. 备份并启动新的 web （http://localhost:3000）

```shell
# 在没有产生 node_modules 之前，先备份
cp -r web web-lovme

cd web-lovme
pnpm i && pnpm dev

git add . && git commit -m "BREAKING CHANGE: 让我们魔改 Dify"
```

登录前端，确认顺畅。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/dcd32bc99c871be80daedae190b243df.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

4. 启动旧的 web 作为对照 （http://localhost:3001，后端默认配置是与 3000 端口通信的，所以 3001 这个只能看一下纯前端效果）

```shell
cd web
pnpm i && pnpm dev
```

5. 至此，魔改环境大功告成，你的界面大致如下：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/21dcc3e20895cee6fd3776c81ebafa87.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

6. 可能的问题

**问题 1：端口占用**

开发中经常会碰到某个端口被占用的情况，直接输入如下（修改对应端口），即可无脑杀除。
`lsof -ti :3000 | xargs kill -9`

如果希望简单点，可以把下述 alias 写入 bash/zsh
`killport() { lsof -ti :$1 2>/dev/null | xargs -r kill -9 2>/dev/null; }`

这样以后就可以 killport XXX 了

**问题 2：数据库冲突**

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d791f63675103d5fd20ea6db05a9a576.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

多个 docker 运行 postgresql 时都暴露 5432 接口就会有冲突：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9317a7fdf51c17f758e7ddacd319b5c1.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 2. 准备 cc 环境

> 工欲善其事必先利其器。

我们优先使用 cc。

我们使用到的 cc 配套工具如下：

1. 手工川自研 cc 管理工具 [MarkShawn2020/claude-code-manager: A powerful CLI tool for managing Claude Code workflows with automatic execution tracking and analytics.](https://github.com/MarkShawn2020/claude-code-manager)
2. 手工川自研 cc 深度思考指令集，具体可以参考我们写的文章 [一代人有一代人的抽象：Vibe Coding 正在重新定义软件工程](https://mp.weixin.qq.com/s/yb6mPKisaSg8J2COdV2tWQ) ：

![source: 手工川《代码已死，Vibe永生》](https://poketto.oss-cn-hangzhou.aliyuncs.com/abcb94146fbfe931d34b657cef212380.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

```ad-tip

自从研发出手工川think指令集，我自己超级深度使用（超50%的prompt），也在很多群里推广过，但依旧有很多人不解，我简单理了一下，大概有以下这几种问题：
1. 不明白为什么需要使用think模式（基于DS的教育，使用cc的群体里这类人基本上不存在）
2. 不明白为什么需要用指令去声明think模式（这类人目测很多，他们对“函数”是没有太大概念的）
3. 不明白为什么think模式需要分级（首先分级不是我分的，是Anthropic自己分的，其次我认同）
4. 不明白think模式之间的分级差异（我们这张图的差异显示就非常的细致）
5. ultra党：觉得既然ultrathink有用，那就无脑ultrathink好了（他们走向了另一个反面）
6. ……
```

好地我们开始。

我们依次分别为前端文件夹(`./web-lovme`)、后端文件夹（`./api`）、根目录（`.`）都执行一遍 `/init`，它会自动生成对项目的分析并保存在 `./CLAUDE.md` 内供后续使用。

此外，cc 的记忆检索是递归的：

![source: https://docs.anthropic.com/en/docs/claude-code/memory#how-claude-looks-up-memories](https://poketto.oss-cn-hangzhou.aliyuncs.com/beb1e1effe9b119978c0611804dadc45.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

如果你希望知道当前 cc 的全部记忆的话，有两种办法：

1. 在 cc 里按 `/memory` ，它会允许你单项选择项目或者全局级别的记忆
2. 如果你想一下子看到全部的，可以使用我们的 `ccm memory` 命令。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/67f59b260d4330c087ce06721df8e648.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 3. 魔改产品名

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5eb28d8cc2957d214167827e20753ace.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

```ad-tip

左下角和右下角的悬浮按钮都是开发环境专用，左边是nextjs，右边是tanstack，可以无视。
```

在 cc 里直接输入：

```shell
/ttt 把 branding（dify）改成 LovMe
```

其中，`/ttt` 是我们的自定义 cc slash command，表示三级思考，一般用于轻量重构，需要较全局的项目分析。

cc 立即做了一顿分析，并且给出了具体的实施步骤。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2bbf3370f3cb32321950a23ff9894a59.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

我个人觉得他的这个分析很有价值，翻译给大家看看：

```markdown
用户要求我将品牌名称从“dify”更改为“LovMe”。该命令要求我仔细思考这个问题。

这似乎是一项将项目或应用程序从“dify”重命名/重塑为“LovMe”的任务。鉴于我所在的网络目录似乎是一个 dify 项目（根据工作目录路径判断），这很可能是一项全面的品牌重塑任务。

让我仔细想想这涉及哪些方面：

1. 了解范围：这是一项品牌重塑任务，涉及将整个代码库中所有对“dify”的引用更改为“LovMe”。
2. 多维度分析：

- 技术维度：需要查找并替换文本字符串、配置值、文件名、包名等。
- 用户体验维度：这会影响所有面向用户的文本、UI 元素和文档。
- 系统维度：可能影响数据库架构、API 端点和环境变量。
- 法律/商标维度：名称变更具有法律影响。
- 市场营销维度：品牌形象彻底改变。
- 运营维度：部署配置、域名等。

3. 需要综合方法：

- 搜索所有出现的“dify”（不区分大小写）
- 搜索所有出现的“Dify”
- 搜索“DIFY”（全部大写）
- 查找各种文件类型：.js、.ts、.tsx、.json、.md、.html、.css 等。
- 检查 package.json 和配置文件。
- 检查环境变量。
- 检查文档。
- 检查图片文件和资源。
- 检查 API 端点和路由。

4. 哲学思考：这不仅仅是查找和替换操作。这是一项根本性的身份变更，它会影响：

- 品牌认知
- 用户认知
- 市场定位
- 技术架构（如果品牌名称嵌入在 URL、API 等中）

我将探讨这项全面的品牌重塑工作的更广泛影响。软件项目在更改其核心身份时会经历重大转变。这
涉及复杂的技术、战略和运营考量，远远超出了简单的文本替换。

品牌重塑过程需要一种细致、多层次的方法。历史先例表明，成功的更名需要在技术、法律和用户体验领域进行周密的规划。我需要系统地规划旧品牌名称存在的每一个潜在接触点，并制定一套完整的转型战略。

重点关注的领域包括确保无缝的技术迁移、维护用户信任、维护现有的集成，以及创建平稳的过渡，以最大限度地减少对现有用户和系统的干扰。

⏺ 我将帮助您将“dify”更名为“LovMe”。这是一项全面的品牌重塑任务，需要对整个代码库进行系统分析并谨慎执行。

⏺ 更新待办事项
⎿ ☐ 分析代码库结构并识别所有 dify 引用
☐ 搜索所有大小写变体：dify、Dify、DIFY
☐ 检查 package.json 和配置文件
☐ 更新所有对 LovMe 的文本引用
☐ 更新文档和 README 文件
☐ 检查环境变量和 API 端点
☐ 运行 lint 和 typecheck 以确保没有错误
```

我想表达的是，这个分析结果已经超过了绝大多数工程师，正常工程师在这个活上，我觉得其实是干不过 cc 的。

这个时间可能会比较长（10-20 分钟），因为会修改几十个 i18n 文件。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1d5ce47d34331b69e7371d7e8b1642ef.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/36335a68c1153d0d007871f1aaae5d7e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 3. 魔改公司名

魔改公司名要比产品简单的多，因为公司名一般就在底部。

所以直接二级思考轻轻松松拿下：

```shell
/tt 请继续修改公司名为 Neurora Tech.
```

但由于我们刚刚的改动较大，信噪比也较低，所以建议先 `/compact` 一下。

为什么不是 `/clear` 呢？因为我们希望保留我们在重构一个项目的记忆，并且展现一步步改动目标内容的过程。

> 我们 Vibe Coding 交流群里有人问过什么时候用 `/compact`，什么时候用 `/clear`。
>
> 其实很简单，`/clear`后的上下文只有 CLAUD.md 等文件，而 `/compact` 后就是文件 + 压缩后的上下文，与之对比如果我们什么都不做的话，那就是文件+完整上下文。
>
> 我个人倾向于在完成一个子任务的时候就压缩，而不是等到窗口（200k）爆炸时强制被动压缩。以及倾向于在执行一个新的不相关子任务时清空或者新开一个 session。
>
> 这些都是经验，法无常形，需要多尝试多体会多总结。

十分钟后，底部（以及其他我们自己都不知道哪里会需要的地方）已经自动修改完毕：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/840e375e22ca806cfc22e14156135dc7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e0e2d734ce1d18598c06d48b56355de1.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 4. 魔改 logo

由于 logo 属于图像，所以要比上述的文字修改稍微复杂点。

在 cc 里有很多种操作图像的办法，但我们 **不推荐** 直接把一个图像拖到（mac：ctrl + v）cc 里，然后对它说，我要这个 logo。

原因是，在 cc 里会把输入的图像转成 base64 塞入自己的上下文，而 cc （以及目前所有的大模型）都不支持使用程序操控自己的上下文。

所以我们要把自己的 logo 文件以文件形式存储在 cc 能够读取的地方。

按照传统方式，我们需要把 logo 文件放到 `./public` 下，这是 nextjs app 的标准静态资源管理办法。

但因为这里是 cc，我们可以有更高级的办法。

比如我司的所有物料都是在 `/Users/mark/__core__/neurora`，那我们就可以在 cc 的配置里加上这个目录：

```json ~/.claude/settings.json

{
  ...
  "permissions": {
    ...
    "additionalDirectories": [
      "~/__core__",
      ...
    ]
    ...
  },
  ...
}
```

然后就可以对 cc 说（需要三级思考）：

```
/ttt logo和favicon要用 @/Users/mark/__core__/neurora/设计/logo/neurora_logo_1280.svg。
```

它就会自动读取该文件，理解后，自动复制到 `./public/` 下，并做一些额外的处理。

很快，我们 logo 就改成功了，记得按住 cmd + 刷新浏览器以确保资源 reload 生效。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/304b69864c96ceca787795b084df61fc.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 5. 魔改主题

对于不懂前端的朋友来说，这个需求其实会非常之难，他们（比如我这次）往往会像如下 prompt 一样让 AI 继续修改其他的组件样式。

```shell
/tttt is running… 很好，现在请基于我们的新设计风格、主题等，修改所有其他组件

---

⏺ 这是一个大型设计系统重构任务，需要系统性地分析和实施。让我深入分析当前项目结构，制定全面的迁移策略。

⏺ Update Todos
⎿  ☐ 分析项目组件架构和现有设计系统
☐ 重构基础 UI 组件(Button, Input, Card 等)
☐ 更新布局组件(Header, Sidebar, Navigation)
☐ 修改页面级组件适配新主题
☐ 测试组件兼容性和响应式布局
☐ 优化性能和可访问性
```

一个页面还好，比如我们让它修改登录页，逐一细化修改需求后，慢慢可以接近我们心目中的样子。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e240e9e3c81f744a24f09b9d34bb9bcf.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但很多页面这个办法就不可行了。

**最后我们发现在我们不经意间（昨晚通宵）AI 在无数多的文件里使用了自定义的 `neurora-xxx` 的样式标记，导致出现两套系统，成为灾难。**

无奈，只好回滚。

```shell
b117ad788 (HEAD -> lovme) HEAD@{0}: reset: moving to HEAD~1
e0798ca43 HEAD@{1}: reset: moving to HEAD~1
31ba8f551 HEAD@{2}: reset: moving to HEAD~1
4618b6c8f HEAD@{3}: reset: moving to HEAD
4618b6c8f HEAD@{4}: reset: moving to HEAD
4618b6c8f HEAD@{5}: checkout: moving from main to lovme
32df3b68c (origin/main, origin/HEAD, main) HEAD@{6}: checkout: moving from e0798ca431aa982f5ddc8b6d0a477221e92dc8f8 to main
e0798ca43 HEAD@{7}: checkout: moving from 31ba8f551758908b9ab92b594a5d0dbc8fd501cd to HEAD~1
31ba8f551 HEAD@{8}: checkout: moving from lovme to HEAD~1
4618b6c8f HEAD@{9}: commit: feat: signin page theme
31ba8f551 HEAD@{10}: reset: moving to HEAD
31ba8f551 HEAD@{11}: commit: refactor: supabase theme init
e0798ca43 HEAD@{12}: commit: fix: landing page scroll
b117ad788 (HEAD -> lovme) HEAD@{13}: commit: feat: init landing page

```

接着我们尝试了让 cc 去直接修改 tailwind 配置相关的内容。

部分有效。

最终还是出现了两套主题混杂的效果。

自己研究后发现，类似 button 这种组件采用了组合的方案。

以 button 的 `btn-primary` 配置为例，起在 `/app/components/base/button/index.css` 中使用了：

```css
  .btn-primary {
    @apply
    shadow
    bg-components-button-primary-bg
    border-components-button-primary-border
    hover:bg-components-button-primary-bg-hover
    hover:border-components-button-primary-border-hover
    text-components-button-primary-text;
  }
```

也就是说背景色使用 `--color-components-button-primary-bg`，这是在 `./themes` 文件下的 theme 配置文件里定义的。

所以最好的做法（我和 AI 一致同意），是我们再新建一套自己的 theme 文件，这样侵入性最小，可扩展性也最高。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7f795d41e577689cb4e2b49bac5bf9ca.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### Step 6. 魔改 landing page

目前在我们在登录前的首页会自动跳转到 `/signin`路由，缺少专业的落地页。

我们可以分两步走，先让它不要跳转停在 landing page，其次再优化 landing page。

老技巧，先 `/compact`（只剩 13%了）。

```shell
> /compact

  ⎿  Compacted. ctrl+r to see full summary


> /ttt is running… 目前产品在未登录状态会直接跳转到 /signin 路由，希望有个简单的落地页

  ⎿  Allowed 7 tools for this command
```

经过一些小波折（dify 的 `next.config.ts` 里写死了重定向）后，它实现了目标（尽管还有个小 bug：不可以滚动）。


好地，现在让我们开始干大活。

我们先使用我们的

```shell
> /tttt is running… 请基于 @DESIGN.md 重构 landing page @app/page.tsx

---

Let me start by adding the design tokens to the Tailwind config, then refactor the
landing page component.

First, I'll update the Tailwind config to include the design tokens from DESIGN.md:

⏺ Update Todos
⎿  ☒ 分析 DESIGN.md 设计规范和当前落地页结构
☐ 更新 Tailwind 配置添加 DESIGN.md 设计令牌
☐ 重构落地页组件采用 Supabase 风格的暗色主题
☐ 实现设计规范中的组件样式(按钮、卡片等)
☐ 测试响应式布局和国际化功能
```

很好，右边是我们的参考目标（supabase），左边是我们一行 prompt vibe coding 的结果，这个绿色的主题以及样式，确实和目标很接近了（就是还不够高级，意思是另外的价格：）。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/df3faca5c51a49630b5350760a5153b5.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但最后发现，我们的需求确实比较难不看代码直接搞定，我们最终找到一个比较满意的目标网站（https://indiekit.pro/），综合使用了各种技巧（包括定制版手工川网站克隆专用指令，见 Appendix）实现了高保真地复刻，大家看一下效果~

首屏：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/8162647a1c4f41dea68d76031b97fbb0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



特性：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/29d57e5aaceb16696b2d87ae4d1c24e1.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


用户评价：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/b4176080bcaa40e90110bf74d5dff2ff.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


定价：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/c1fb3edb152b5b4195c182dc0daf401c.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


FAQ：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/158ee60e1cc98bb33a4309e2e4b3c5e4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

Footer：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2dc70e2419eb7214df85f9ed952423b2.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

由于它的克隆只花了一分钟，复刻只花了十分钟，能达到这样（我觉得70分的水平），我是很满意的。

也说明我们的工具、指令、工作流等都能达到商业化级别水准。

技术真地改变了太多。

## Further Steps

下一期（如果大家支持的话），我将继续展现如何基于 Vibe Coding 实现：

- 在 Dify 系统中集成一个 sidebar 聊天助手
- 在该聊天助手中集成 RAG 等 Agent 能力
- 在 Dify 系统中实现多租户系统（这个较为敏感，我需要和 Dify Team 聊一下，确保不影响 Dify 商业化）
- 留言区留下，你想加的功能实现
- ……

## Appendix

### 手工川 Gemini 元指令: generate-command

> 为什么你需要这款命令：工程师顶级原则：找到遵循与迭代顶级原则。
>
> btw：本命令作者：手工川 & Claude Code （对不起，这个元命令不是 Gemini 自己写的，希望未来它能加把劲）。

````toml
# Command: generate-command
# Version: 2.0.1
# Created: 2025-01-27
# Updated: 2025-07-28
# Author: markshawn2020
# Changelog:
#   2.0.1 (2025-07-28): Fixed markdown code block nesting issue by using ~~~ instead of ```
#   2.0.0 (2025-01-27): Enhanced with intelligent command naming and Gemini CLI compatibility
#   1.0.0 (2025-01-26): Initial version adapted from Claude CLI

description = "Generate a new Gemini CLI slash command with version management support"
prompt = """
# Generate Gemini CLI Slash Command with Version Management

You are creating a new Gemini CLI slash command with built-in version management. Based on the user's requirements, generate a complete TOML command file with version control.

## Version Management Features

This command supports:
- **Semantic versioning** (MAJOR.MINOR.PATCH)
- **Automatic backup creation** when updating existing commands
- **Version history tracking** in comments
- **Changelog generation** for updates

## Instructions:

**FIRST: Analyze the input and generate appropriate command name**

Before proceeding, analyze the user's input to determine:
- Is it a valid command name (lowercase, ASCII, no spaces, ≤15 chars)?
- Or is it a description that needs command name generation?

If input needs command name generation:
1. Analyze the meaning and purpose of the description
2. Generate 2-3 short, descriptive English command names (3-12 characters)
3. Use kebab-case for multi-word names
4. Present numbered options to user and ask for their preference
5. Wait for user selection before proceeding

6. **Parse the arguments intelligently**: Handle multiple input formats
   - **Format 1**: `<command-name> "<description>" [project|user] [version] [additional-requirements]`
   - **Format 2**: `"<description>"` (auto-generate command name)
   - **Format 3**: `<description>` (if input doesn't look like a valid command name, treat as description)

   **Smart Command Name Generation**:
   - If input contains non-ASCII characters, spaces, or is too long (>15 chars), treat as description
   - Generate 2-3 short, appropriate English command names based on the description's meaning
   - Use descriptive but concise naming (3-12 characters)
   - Present options to user for selection

   **Parameters**:
   - `command-name`: The name of the slash command (without /) - auto-generated if not provided
   - `description`: What the command does - extracted from input or user-provided
   - `scope`: "project" (`.gemini/commands/`) or "user" (`~/.gemini/commands/`) - defaults to "user"
   - `version`: Semantic version (defaults to "1.0.0" for new commands)
   - `additional-requirements`: Any special features needed

2. **Version Management Process**:
   - Check if command file already exists using `@<command-path>` or shell commands
   - If exists: Create backup with current version number using shell commands
   - Update version number (increment appropriately based on changes)
   - Add changelog entry as comment in TOML file
   - Always include creation and update dates

3. **Create the appropriate directory structure**:
   - For project commands: `.gemini/commands/`
   - For user commands: `~/.gemini/commands/`
   - Use shell commands to create directories: `mkdir -p <path>`
   - Create `versions/` subdirectory for backups if needed

4. **Generate the command file** with proper Gemini CLI TOML format and complete metadata:

   ~~~toml
   # Command: <final-command-name>
   # Version: X.Y.Z
   # Created: YYYY-MM-DD
   # Updated: YYYY-MM-DD
   # Author: markshawn2020
   # Original Description: [user's original input if different from command name]
   # Changelog:
   #   X.Y.Z (YYYY-MM-DD): [Initial version or description of changes]

   description = "[clear, concise description of what the command does]"

   prompt = '''
   # Task: [Task description]

   You are an expert at [specific role/domain].

   Your instructions are to:
   5. [Specific instruction 1]
   6. [Specific instruction 2]
   7. [Specific instruction 3]

   The user's raw command is appended below your instructions.
   '''
   ~~~

   **Metadata Requirements**:
   - **Always include**: Command name, version, created date, updated date, author
   - **Author**: Always use "markshawn2020"
   - **Dates**: Use YYYY-MM-DD format (current date for new commands)
   - **Version**: Start at 1.0.0 for new commands
   - **Changelog**: Track all versions with dates and change descriptions

5. **Backup Strategy**:
   - Before updating: Use shell command `cp command-name.toml command-name.v[old-version].toml`
   - Keep backup files for rollback capability
   - Optional: Move backups to `versions/` subdirectory using `mv` commands

6. **Consider these Gemini CLI capabilities based on requirements**:
   - **Shell operations**: Use `!` commands or shell mode for git, file operations
   - **File operations**: Use `@` commands to read files, shell commands to write
   - **GitHub operations**: Use `!gh` commands for GitHub CLI integration
   - **Web operations**: Use `/tools` to check available web search tools
   - **Directory operations**: Use `@directory/` to read directory contents
   - **MCP tools**: Use `/mcp` to check available MCP server tools

7. **Argument Handling Options**:
   - Use `{{args}}` placeholder for direct argument injection
   - Or use default behavior where arguments are appended after two newlines
   - Choose based on whether you need precise argument placement

## Command arguments: {{args}}

**IMPORTANT**:
1. Start by analyzing the input for intelligent command naming
2. If input needs command name generation, provide options and wait for user selection
3. Always include complete metadata (author: markshawn2020, version, dates, changelog)
4. Use current date (2025-01-27) for new commands

Create the Gemini CLI slash command file now with version management, ensuring it follows Gemini CLI best practices and includes proper authorship metadata.
"""

````

### 手工川网站克隆专用 Gemini 指令: encode-html

> 为什么你需要这款命令：gemini 的超长上下文窗口使得它比其他任何工具都更适合分析一坨网页，并输出你想要的，我们专门做了各种写入优化，还支持仅克隆样式、克隆样式与内容等全部两种场景。

```toml
# Command: encode-html
# Version: 2.0.0
# Created: 2025-07-28
# Updated: 2025-07-28
# Author: markshawn2020
# Description: Analyzes HTML to extract design system and/or content structure for cloning
# Changelog:
#   1.0.0 (2025-07-28): Initial version
#   1.1.0 (2025-07-28): Added conditional output path logic
#   2.0.0 (2025-07-28): Major refactor - added two modes (style/full), reduced redundancy, added content analysis

description = "Analyzes HTML to extract design/content. Outputs to ./design/{filename}.md or ./design/index.md. Supports two modes: style-only or full clone."

prompt = '''
分析提供的HTML内容。首先询问用户需要哪种克隆模式：

1. **style** - 仅提取设计风格（颜色、字体、间距、组件样式）
2. **full** - 完整克隆（包括设计风格 + 内容结构、文本、布局）

如果用户没有明确指定，默认使用 **style** 模式。

---

## Style 模式输出格式

### 设计系统
~~~javascript
// tailwind.config.js 扩展
{
  colors: { primary: "#xxx", secondary: "#xxx", ... },
  fontFamily: { sans: ["字体"], ... },
  spacing: { base: "1rem", ... },
  borderRadius: { DEFAULT: "xxx", ... }
}
~~~

### 核心组件
逐个列出识别到的组件：
- **组件名**: 简短描述
- **样式**: `关键Tailwind类`
- **状态**: hover/focus变化

### 布局模式
- 主要布局结构和容器宽度
- 响应式断点行为

---

## Full 模式输出格式（包含Style模式所有内容，另外增加）

### 页面结构
~~~
Header
  - Logo: [文本/图片路径]
  - Navigation: [菜单项列表]

Main Content
  Section 1: [标题]
    - 组件类型: [Hero/Features/等]
    - 标题文本: "xxx"
    - 副标题: "xxx"
    - 内容布局: [描述]

  Section 2: [标题]
    - ...

Footer
  - 版权信息: "xxx"
  - 链接组: [列表]
~~~

### 内容清单
- 所有标题文本
- 段落内容摘要
- 按钮/CTA文本
- 图片资源列表

### 交互元素
- 表单字段和标签
- 可点击元素及其目标

---

**输出要求**：
1. 保持简洁，避免冗余描述
2. 使用实际值而非占位符
3. 直接保存到相应路径：
   - HTML文件输入 → `./design/{filename}.md`
   - 其他输入 → `./design/index.md`
4. 确保design目录存在
'''
```
