
```insta-toc
---
title:
  name: Table of Contents
  level: 1
  center: false
exclude: ""
style:
  listType: dash
omit: []
levels:
  min: 1
  max: 6
---

# Table of Contents

- 1. 先基于 coze 搭建好核心 AI 业务
- 2. 尝试直接发布微信小程序，但是失败了
- 3. cursor 提效百倍，小程序、云开发、打字机效果……
- 附
```

最近我们的一位客户需要实现 AI 自动解析 BP 并生成评估报告的功能，在经过一些调研后，我们决计采用 coze 实现其核心业务逻辑。

本篇是该系列第三篇，重点探讨如何将 coze 能力集成到小程序内。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408144346.png?x-oss-process=image/resize,w_800/quality,q_95)

本文的主要测例为字节跳动今日头条 2013 年的 BP，后台回复 **今日头条**，即可阅览。
 ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329161706.png?x-oss-process=image/resize,w_800/quality,q_80)

下面开始我们的探索之旅。

---

## 1. 先基于 coze 搭建好核心 AI 业务

在之前的两期文章里，我们已经实现了 AI 读取与分析 BP 并直出报告的需求，但中间还是饶了很多弯路，比如使用了 json 这种中间的数据形态。

不过这个弯路是有意义的，一方面它可以使我们的数据更结构化，控制能力更强；另一方面也方便作为 API 对外输出。

但为了减少排版上的工作压力，我们让 [claude](https://claude.ai/chat/b9184e9f-7036-4f29-a622-4fbd3c2b8dd3) 优化了一下，它给了一份直出 markdown 的 prompt，实测效果很不错。

```
您是一名创投大赛评委，请分析参赛团队的商业计划书材料 {{input}}，并生成一份结构清晰的 Markdown 格式报告。

请按照以下结构组织内容：

## 项目基本信息

| 信息类别 | 内容 |
|----------|------|
| 项目名称 | [提取] |
| 企业名称 | [提取] |
| 企业代码 | [提取] |
| 行业分类 | [提取] |
| 发展阶段 | [提取] |
| 项目负责人 | [提取] |
| 项目联系人 | [提取] |
| 联系电话 | [提取] |

## 商业计划书摘要
### 项目简介
[提取并整理项目简介内容]

### 产品与服务
[提取并整理产品与服务内容]

### 行业与市场分析
[提取并整理行业与市场内容]

### 核心技术优势
[提取并整理核心技术内容]

### 商业模式说明
[提取并整理商业模式内容]

### 战略规划
[提取并整理战略规划内容]

## 核心团队成员

| 姓名 | 单位 | 职务 | 学历 | 履历摘要 |
|------|------|------|------|----------|
| [姓名1] | [单位1] | [职务1] | [学历1] | [履历1] |
| [姓名2] | [单位2] | [职务2] | [学历2] | [履历2] |
| ... | ... | ... | ... | ... |

## 知识产权情况

| 专利号 | 专利名称 | 发明人 |
|--------|----------|--------|
| [专利号1] | [专利名称1] | [发明人1, 发明人2, ...] |
| [专利号2] | [专利名称2] | [发明人1, 发明人2, ...] |
| ... | ... | ... |

## 财务预测分析

### 收入预测 (单位：万元)
| 年份 | [年份1] | [年份2] | [年份3] | [年份4] | [年份5] |
|------|---------|---------|---------|---------|---------|
| 金额 | [金额1] | [金额2] | [金额3] | [金额4] | [金额5] |

### 支出预测 (单位：万元)
| 年份 | [年份1] | [年份2] | [年份3] | [年份4] | [年份5] |
|------|---------|---------|---------|---------|---------|
| 金额 | [金额1] | [金额2] | [金额3] | [金额4] | [金额5] |

### 利润预测 (单位：万元)
| 年份 | [年份1] | [年份2] | [年份3] | [年份4] | [年份5] |
|------|---------|---------|---------|---------|---------|
| 金额 | [金额1] | [金额2] | [金额3] | [金额4] | [金额5] |

## 评委点评
[基于上述信息，简要分析项目的优势、劣势和投资价值]

注意：
1. 请使用 Markdown 语法，确保格式正确，便于阅读
2. 如原始材料中某些信息缺失，可在对应位置标注"未提供"
3. 尽量保持格式一致性和美观性
4. 财务数据中的年份应根据原始材料中的实际预测期间提取，不要使用固定年份
```

基于以上，我们最新的工作流升级到了 0.3 版本。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408153001.png?x-oss-process=image/resize,w_800/quality,q_95)

跑出来的效果也很不错，直出了表格，比我们手动自己写渲染要方便一些。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250406173155.png?x-oss-process=image/resize,w_800/quality,q_95)

## 2. 尝试直接发布微信小程序，但是失败了

在 coze 的项目开发面板可以创建新项目，它支持智能体和应用两种。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408153730.png?x-oss-process=image/resize,w_800/quality,q_95)

我们可以尝试创建应用（后面会有一期讲创建智能体的，也很好用，但场景不一样）。

可以选择适合自己的模板，以下是目前（2025年04月08日）所有公开的模板。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408153855.png?x-oss-process=image/resize,w_800/quality,q_95)

有些模板是需要付费的，有些则是需要专业版。

你也可以开发自己的模板，然后做一个定价。

收入最高的一个模板竟然卖出了 600 多万 🤔

不过必须是 coze 生态内参加了某些活动拿奖的才可以当做模板售卖……

害。。

两周前我还用 AI 给这些模板做了一个分析报告，感兴趣的可以后台回复 **coze 模板报告**。

![99402860a77306bdb9ed491b4f4265f5.jpg](https://poketto.oss-cn-hangzhou.aliyuncs.com/99402860a77306bdb9ed491b4f4265f5.jpg?x-oss-process=image/resize,w_800/quality,q_95)

回到应用模板，简单看了一圈之后觉得内容洞察那个模板是比较接近我们这个产品需求的。

比如我们可以第一个框作为文件输入组件，第二个框设定一些参数调整，然后第三个框输出结果。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408214504.png?x-oss-process=image/resize,w_800/quality,q_95)

但这个模板不是移动端 / 小程序端的。

如果我们要创建移动端，可以从头建立一个空白的应用，并且选择移动版。

coze 确实做了不少工作，连 icon 都可以 AI 自动生成。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408215108.png?x-oss-process=image/resize,w_800/quality,q_95)

在用户界面选择**小程序和 H5**。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408215239.png?x-oss-process=image/resize,w_800/quality,q_95)

然后就可以使用 coze 的无代码组件轻松地拼凑自己的用户界面。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408215613.png?x-oss-process=image/resize,w_800/quality,q_95)


但很可惜，coze 移动端暂时还不支持文件上传组件（网页端可以），蚌埠住了。

![db92bb433637d4d1a4471de13a68d6ad.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/db92bb433637d4d1a4471de13a68d6ad.png?x-oss-process=image/resize,w_800/quality,q_95)

coze 的 AI 助手也有点点蠢萌蠢萌🤔

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408215735.png?x-oss-process=image/resize,w_800/quality,q_95)

anyway，我觉得 coze 的整体工程做的真心不错，但还是功亏一篑，我这个需求凉了。

## 3. cursor 提效百倍，小程序、云开发、打字机效果……

无奈，我们只好使用传统开发流程。

因为我的前端是 React 技术栈，以前一般都会用 Taro 开发。（国内一般用 UniApp）

现在有 AI 了，时代不一样了，我可以让 AI 直出小程序代码了。

而且初始的 prompt 非常简单，在 cursor 里直接 at 我之前写的技术文章，然后让它基于我的文章改成小程序版本即可。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408220556.png?x-oss-process=image/resize,w_800/quality,q_95)

很快，它就搭建了一个最初步的程序，再后续我又连续让它加上了云开发、用户系统、流输出等功能。

大的图片找 gpt-4o，小的图片 / icon 找 claude 生成 svg 再转 png ，UI 则直接让 AI 来搞定。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408221153.png?x-oss-process=image/resize,w_800/quality,q_95)

最终首页长这样。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408220916.png?x-oss-process=image/resize,w_800/quality,q_95)

比较难的是在小程序中实现流输出（打字机效果）。

经过一番检索知道小程序不支持大模型专用的 SSE 传输协议，只支持分块传输。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408221418.png?x-oss-process=image/resize,w_800/quality,q_95)

我们把 coze 的一些流输出相关的文档拉取（比如直接复制粘贴保存为 md）到本地，交给 ai 阅读理解。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250408221544.png?x-oss-process=image/resize,w_800/quality,q_95)

这里面的核心是几点：
1. 微信的分块传输基本类似于 sse，可以直接客户端发起，在 `onChunkReceived` 回调里处理增量传输数据即可
2. coze 的工作流支持同步、异步、流输出（需要在工作流结点的最后转成流输出模式）三种模式，拥有不同的 api，需要仔细甄别。其中同步的意思就是发起一个工作流，然后阻塞式等待一次性跑完输出；异步就是发起触发一个工作流的任务，然后用户后续定期检查这个任务的进度，最终也是一次性跑完输出；流式就是不必等大模型输出完毕就可以持续获得最新的输出结果（**这个还挺有意思的，因为工作流的大模型结点不一定是最终结点，所以很好奇它的具体机制🤔，有懂的可以一起交流**）。具体可以看：
	1. [执行工作流 - 文档 - 扣子](https://www.coze.cn/open/docs/developer_guides/workflow_run)
	2. [执行工作流（流式响应） - 文档 - 扣子](https://www.coze.cn/open/docs/developer_guides/workflow_stream_run)

最终终于顺利地搞定了流输出！

【实时输出视频】


## 附

- 使用 cursor 开发小程序的过程整体是比较顺利的，但有被一个小的问题卡了很长时间，那就是生成的代码里会混用 `openid / openId`、`nickname / nickName` 等，导致一堆 bug。临时的解决办法是直接全局替换，终极的解决办法是最好在 prompt 里指定一些变量命名规范。

---

以上就是本期的全部内容，希望对您有用！下期继续，敬请期待！


