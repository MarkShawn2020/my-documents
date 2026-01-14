---
author: 南川
publishDate: 2025-06-25
articleTitle: Comate 让编程进入"智能体时代"
articleSubtitle: 暨百度AI开放日回顾
episodeNum: Vol. 45
seriesName: 
tags:
  - VibeCoding
  - Comate
  - 百度
  - AI-IDE
---

6 月 23 日，手工川受邀参加了百度 AI 开放日·文心快码专场，作为经常使用 Cursor、Windsurf 的开发者，我对这个"国产 Cursor"很感兴趣。

听说我要去，孵化器的一位朋友 Lisa 也很感兴趣，临时决定一起前往。有意思的是，她完全没有开发经验，但在现场也顺利完成了从 0 到 1 的应用搭建，相当开心。

![Lisa的体验](https://poketto.oss-cn-hangzhou.aliyuncs.com/c8cf2a22113af0efd7a1a3456594e997.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 从插件到 IDE：百度的 AI 编程野心

作为大模型落地最成熟的场景，AI Coding 一直是各大科技公司的必争之地。百度这次推出独立的 AI IDE，背后有着深刻的战略考量。

正如百度团队所说："**AI 应用时代，研发方式将产生颠覆性变化。研发工具完全自主可控，产品才能够及时跟随 AI 发展进行演变。**"从插件升级到独立 IDE，不仅是产品形态的升级，更是百度对未来编程范式的重新定义。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/167bd23ff23699baa31fab4a1aacbfdc.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 现场震撼：当 AI 编程成为"全民技能"

### 1. 小学生的"降维打击"

两位小学生的现场演示挺有意思。他们用 Zulu 智能体快速搭建了钢琴模拟器等小应用。这种低门槛的编程方式，确实会改变编程教育的格局——类似于 Scratch 当年的影响，但这次是直接生成可用的代码。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/46e59d02cab6cb66a16eec3ecac76a5d.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 2. 一分钟搭建 Demo 的极限挑战

开场的快速搭建 Demo 比赛中，最快的参赛者在一分钟内完成了任务。使用方式和 Cursor 类似——自然语言描述需求，AI 自动规划执行。不过百度强调了他们在中文理解和本地化场景上的优势。

![dbq，忘了拍了，放张我当时的实时体验吧！](https://poketto.oss-cn-hangzhou.aliyuncs.com/ebb3239010419fd8119b33100a9ea9fd.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 3. "一个人就是一支团队"成为现实

一位嘉宾分享的《从算法到系统的全流程搭建，一个人就是一支团队》尤其引人深思。他展示的表格清晰地显示了**不同开发阶段中 AI 与人工的占比变化**——AI 正在逐步接管重复性工作，让开发者专注于真正需要创造力的部分。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a49ba3869cf9f2684f3a5111526b5c3c.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

## 深度体验：Comate IDE 的核心能力

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/11ac579c8b3f544585b20446fa41a63a.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 1. Zulu 智能体：从"写代码"到"说需求"

Zulu 是这次发布的明星功能，它不仅仅是一个代码生成器，更像是一个能理解业务逻辑的编程搭档。

**实战案例：Next.js 项目问题解决**

在测试中，我故意制造了一个 Next.js 项目回滚后的依赖问题。Zulu 分析 package.json 后给出了`pnpm add next@15.3.1 --force`的解决方案。响应速度和准确性都不错，和 Cursor 的表现相当。

**核心能力解析：**

- **深度理解代码库**：自动调用代码搜索、文件读取等工具，理解整个项目的业务逻辑
- **自动执行命令**：可以自动执行终端命令，完成环境设置、程序运行、测试等工作
- **精准代码采纳**：支持代码片段级与文件级采纳，通过 Diff 形式展示变更
- **多模态交互**：支持自然语言、截图等多种输入方式

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/10b40e08cbb5b3201d89df37c0135c21.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,90)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/cbd2f4235916739803ec4b9764d34621.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 2. 前端场景革命：设计即代码

**Figma to Code 功能**让设计稿秒变代码成为现实。

这个功能对我来说特别有吸引力！

前段时间参与小程序开发项目时，就遇到过 Figma 设计稿转代码的需求。

当时我们碰到了不少问题：生成的界面与实际屏幕不一致（需要手动调整 Taro 框架的默认 750px 配置到 375px）、代码体积过大等。

而 Comate IDE 的演示中，Zulu 不仅生成了高还原度的页面，还能自动匹配项目框架，这种智能化程度确实让人期待。

**网页预览与元素级调试**功能同样惊艳：

- 独立的预览按钮，无需跳转浏览器
- 点击即可选中需要修改的元素
- 自动识别运行时错误并修复

不过在使用中也发现一些待优化的地方：

- 预览功能的稳定性需要提升，有时需要 reload window
- 在预览页面时快捷键会被劫持
- 建议将 Preview 作为独立进程运行

【f2c-demo-0610.MP4】

### 3. MCP 协议：连接万物的编程新范式

通过 MCP（Model Context Protocol）协议，Comate IDE 可以连接外部服务和能力，打造"无限透明工具箱"。现场演示的 GitHub 集成让人印象深刻：

- 自动获取 GitHub 上的开发任务
- 通过 SQLite MCP 访问本地数据库
- 完成需求后自动提交 PR

这种开放性让 Comate IDE 不再是一个孤立的工具，而是整个开发生态的连接器。

【cut-mcp-0617-github-sqlite.mov】

### 4. 超级补全：重新定义代码编写体验

全新的代码预测改写引擎带来了革命性的编码体验：

- **代码改写**：不仅能新增代码，还能智能修改现有代码
- **光标预测**：根据编辑历史预测下一处修改位置
- **多行改写**：一处修改，自动应用到相似代码块

在演示中，仅通过连续按 Tab 键就完成了整个类型转换的编码需求，效率提升显著。

【SuperComplete-demo.mp4】

### 5. 团队协作新模式：规则即传承

自定义规则功能解决了团队协作的痛点：

- 将隐性的编码规范转化为显性规则
- 支持项目级和本地级规则设置
- 兼容 Cursor Rules，无缝迁移

现场演示中，通过预设规则，Zulu 在生成新的操作符时自动遵循了项目规范，避免了代码风格不一致的问题。

【Rules】

说到这个我就更不困了，欢迎大家在 comate 里搜索「oh-my-prompt」插件，这是我年初开发的一款 AI IDE 专用多 prompt 管理系统，支持跨 IDE、一键切换、智能同步 Global / Project Prompt，目前支持 cursor、windsurf、comate！

## 实际使用建议

基于我的实际体验，有以下几点需要开发者注意。

### preview 功能很好用，希望继续优化

- 独立的预览按钮，很棒，分析过程非常可靠；部分需要改进的点：
  - tab 的背景色不和谐
  - 在改了一些需求后，再次点击，不是很稳定（我需要 reload window 才可以让它重新触发一次 preview 的动作）

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a01e233bfe4eb5a7fb121e90bc872b84.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 在代码报错后，点击前端的复制按钮，结果被 block 了，值得注意的是，windsurf 也有这个问题（这个很烦，希望百度能高优先级解决一下，我找过 windsurf issue，他们还没有解决，也很慢）

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ed23f6fb5e0f1915c76801f6671dc781.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 产品设计方面可能的建议（个人视角）
  - **加上选中元素发送到对话框（windsurf 支持，非常有用！！！）**
  - preview 可以独立于 conversation，因为比较像是一个独立进程
  - 快捷键（cmd+shift+p）会被劫持，需要点击 tab 窗格或者其他区域才可以触发

### Shell 集成很实用

comate 的 shell 集成了相较于默认的 shell 更好的自动补全功能，不需要按 tab 键，而且建议看起来很不错。但有几个加强的点
：

- 在按 cmd+K 清空 console 后，这个自动补全就没了，不知道为啥

- 在 suggestion 里，只有参数，没有解释，还不够友好（最好能自定义是否显示）

- UI 上也有一些问题（强调色部分看不清）

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/79c4807a99d15f974734257fb4b63753.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 对话回滚刚需

回滚真地刚需，参考我与几位 AI 创业者的视频：

【VibeCoding 技巧-不断回滚】

comate 在这方面当然也是支持的：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9c52c5cb53300a7890431080453e18bf.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

**甚至不仅支持向后滚，还支持向前滚**（windsurf 不支持，需要手动在对应文件里 cmd+Z 撤销），这一波 comate 上分！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/eaf33149bae1306c9feda891dc5e01f3.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

不过在询问了现场的开发小哥后，才知道目前必须先停止生成才能回滚，建议官方优化这个交互。

### 联网检索刚需

我们 vibe coding 的时候经常需要参考外部网页资料，我们当然可以手动获取这些，比如我之前基于 jina-ai 开发了一个 md-dlp 命令行，方便我们一键将某个网页存储成 md 文件：[我写了个 md-dlp: 可能是一键提取网页的最佳实践](https://mp.weixin.qq.com/s/TgxcffrUiP_p-LFRC8iiAg)

不过我目前对这个 md-dlp 还有一些不满意，正在基于最新的工作流开发一个更牛逼的，**敬请期待**！

comate 等 AI IDE 当然支持这样的功能，但目前仅适用于 chat 面板：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a9573572423ef5161bb5968447347163.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

Agent 面板暂不支持：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7e6e3540a1c58257e7e528f5f8cf4ffd.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以我最后不得不先在 chat 面板输入一个网页链接（comate 官方网址），然后让它抓取，完了之后再选择 apply，操作有点割裂！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e1065c95ca0f5a05e60e910a82a0b0fb.jpeg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

希望 comate 团队尽快支持统一的操作！

## 写在最后

百度 AI 开放日让我们看到了国产 AI IDE 的崛起。Comate IDE 不仅在功能上可以对标国际顶尖产品，在本土化、多智能体协同等方面还有独特优势。

虽然产品还有一些细节需要打磨（如 Preview 稳定性、Tab 自动补全等），但整体体验已经相当出色。特别是在解决实际问题、提升开发效率方面，展现出了强大的潜力。

对于开发者来说，这是一个最好的时代——AI 正在重新定义编程。我们需要拥抱变化，从"代码工人"转变为"数字创造者"。而对于那些一直想学编程的朋友们，现在或许是最好的入门时机。

毕竟，当小学生都能用 AI 快速搭建应用时，你还在等什么呢？

---

_想要体验 Comate IDE？访问 [comate.baidu.com](https://comate.baidu.com/) 即可免费下载。支持 VS Code、JetBrains 全系列、Visual Studio 等主流 IDE。_

_关注**手工川**，我们将持续分享 AI 时代的编程新体验与深度评测。_

**注：本文基于百度 AI 开放日现场体验撰写，产品功能可能会持续更新优化。**
