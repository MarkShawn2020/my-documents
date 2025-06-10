
> 在这篇文章中，我们将深入探讨如何利用 Coze 工作流平台，搭建一套高效的 BP（商业计划书）智能评估系统。
> 
> 文章详细描述了从文件读取、批量处理到利用大模型进行内容分析的整个流程，并分享了在实际操作中遇到的挑战与解决方案。
> 
> 通过具体的案例，如字节跳动今日头条的商业计划书，您将了解到如何通过标准化的数据结构，实现更高效的评估与决策支持。
> 
> 若您对 AI 自动化处理、数据结构化输出以及大模型应用有兴趣，本篇教程将为您提供全面的技术指导和实战经验。

本文目录：

```insta-toc
---
title:
  name: 本文目录：
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

# 本文目录：

- 尝试 1：让 AI 自动读取与分析 BP，但是失败了
- 经验 1：如何正确读取文件
- 经验 2：如何批量读取文件
- 尝试 2：现在我们来试试让 AI 分析 BP 里的内容吧
- 经验 3：标准化结构化输出
- 经验 4：结构化输出的最佳实践
- 经验 5：让 AI 快速地生成 json 结构体测例
```



最近我们的一位客户需要实现 AI 自动解析 BP 并生成评估报告的功能。

按照惯例，写一个网页服务，输入是 BP 文件，输出是被大模型分析过后的结构化信息，再调用一个排版输出程序，优化优化就可以了：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331022318.png?x-oss-process=image/resize,w_800/quality,q_95)

但考虑到身边一些朋友频繁向我安利 Coze、Dify 等工作流平台，恰好这个项目的标准化程度又比较高，所以可以拿来试试手。

在**征得客户同意**之后，我们决定把这个方案的过程记录与同步出来，尤其是分享该解决方案中我们碰到的坑、思考与应对策略，希望对您有所帮助。

本文的主要测例为字节跳动今日头条 2013 年的 BP，后台回复 **今日头条**，即可阅览。

 ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329161706.png?x-oss-process=image/resize,w_800/quality,q_80)

考虑到字节跳动的公开数据较多，为防止 AI 基于已学习的内容进行回答产生预期偏差，辅助测例才用了自己自己去年的 BP，感兴趣的朋友请后台证明您的投资人身份，即可阅览。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331015835.png?x-oss-process=image/resize,w_800/quality,q_95)

基于客户诉求，我们约定 BP 的目标分析包括项目基本信息、商业计划书、专利、团队、财务状况几个大维度，结合大模型，数据结构的定义具体如下：

```json
{
  "projectInfo": {
    "projectName": "string", // 项目名称
    "companyName": "string", // 企业名称
    "companyCode": "string", // 统一社会信用代码(如有)
    "industryCategory": "string", // 行业分类
    "developmentStage": "string", // 发展阶段
    "projectManager": "string", // 项目负责人
    "contactPerson": "string", // 项目联系人
    "contactPhone": "string" // 联系电话
  },
  "businessPlan": {
    "projectSummary": "string", // 项目简介
    "productsAndServices": "string", // 产品与服务
    "industryAndMarket": "string", // 行业与市场
    "coreTechnology": "string", // 核心技术
    "businessModel": "string", // 商业模式
    "coreTeam": "string", // 核心团队
    "strategicPlanning": "string" // 战略规划
  },
  "patents": [
    {
      "patentNumber": "string", // 专利号
      "patentName": "string", // 专利名称
      "inventors": ["string"] // 发明人
    }
  ],
  "teamMembers": [
    {
      "name": "string", // 姓名
      "organization": "string", // 单位
      "position": "string", // 职务
      "education": "string", // 学历
      "experience": "string" // 履历
    }
  ],
  "financials": {
    "revenueProjections": [
      {
        "year": "number",
        "amount": "number"
      }
    ],
    "expenseProjections": [
      {
        "year": "number",
        "amount": "number"
      }
    ],
    "profitProjections": [
      {
        "year": "number",
        "amount": "number"
      }
    ]
  }
}
```

基于此，我们的 prompt 主体大致为：

```md

你是一名创投大赛的评委

现在我将给你一个参赛团队的 bp 等相关材料 {{input}}

请您解析并生成如下数据结构：

	```json
	{
	  "projectInfo": {
	    "projectName": "string", // 项目名称
	// 省略剩余部分
	}
	```

```

## 尝试 1：让 AI 自动读取与分析 BP，但是失败了

考虑到当前的很多大模型，都支持直接读取文件，所以我们尝试在一个工作流里直接搞定用户输入 bp 文件、大模型输出分析结果的需求。

但很遗憾，尽管我们在工作流里确保了输入为文件或者文件列表，coze 也正确地将这些文件转成了 oss，但并没有自动读取这些文件的内容，导致最后胡编乱造。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331021836.png?x-oss-process=image/resize,w_800/quality,q_95)

Debug 可以发现，coze 只是把文件链接塞入到了 prompt 里，而非文件里的内容：

```json
{"model":"DeepSeek-V3-0324","model_meta":{"temperature":0.8,"max_tokens":1024,"top_k":0,"stream":true},"messages":[{"role":"system","content":"你是一名创投大赛的评委，现在我将给你一个参赛团队的 bp 等相关材料 ['https://p3-bot-workflow-sign.byteimg.com/tos-cn-i-mdko3gqilj/0f58858a70934eb09970ac19e2281151.pdf~tplv-mdko3gqilj-image.image?rk3s=81d4c505&x-expires=1774462021&x-signature=kQiUVSfa6ujm1ruKo5RzxiW%2FdiI%3D&x-wf-file_name=%E9%A3%9E%E8%84%91BP-20241231.pdf']\n ，请您解析并生成如下数据结构：\n\n```json\n{\n  \"projectInfo\": {\n    \"projectName\": \"string\", //

// 后面省略
```

因此尽管现在的很多大模型都支持文件读取，但是在 coze 里直接使用这套不可行。

## 经验 1：如何正确读取文件

如果我们用的是 dify，则可以直接使用 dify 内置的 doc extractor 组件，它可以解析输入的文档。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331172516.png?x-oss-process=image/resize,w_800/quality,q_95)

其中，当输入是一个文件列表的时候，它会返回一个 json 结构：

```json
{
"text": [
// 解析出的文件内容 1
// 解析出的文件内容 2
// ...
]
}
```

但 coze 并没有提供这样的内置组件，而是需要我们手动地去找自己喜欢的插件。

我们可以优先选用 coze 官方的插件，换用各种搜索词（doc、extractor、read 等），发现 coze 官方确实有一个「文件读取」插件可以读取 doc、docx、pdf 等格式的文档，基本可以满足我们 BP 资料上传的需求。

> todo: 🤔 考虑到 bp 还有 pptx 格式，这个也需要做一些测试……

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331174401.png?x-oss-process=image/resize,w_800/quality,q_95)

这个插件的输入是一个文件的 url 地址，输出是一个 object，包含每个文件的处理结果，当处理成功时，code 的状态码为 0。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331174315.png?x-oss-process=image/resize,w_800/quality,q_95)

可以看到，这个插件已经很好地将将今日头条的 BP 内容解析了出来，当然，这里必须提个醒：**程序化解析文件是一件挺复杂的工作，目前 coze 仅仅是把文字和图片转成了 markdown 格式，但并没有做视觉理解等额外工作，如果后续大模型理解效果不佳，不一定是大模型的问题，很有可能是被解析环节受限了**。

基于这个插件，我们可以非常方便地搭建一个单文件读取工作流。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331230157.png?x-oss-process=image/resize,w_800/quality,q_95)

## 经验 2：如何批量读取文件

如果我们希望实现多文件解析，我们可以工作流嵌工作流，然后使用批处理。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331230248.png?x-oss-process=image/resize,w_800/quality,q_95)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331230305.png?x-oss-process=image/resize,w_800/quality,q_95)

这是最便于理解与实现的一种设计模式，把每个工作流都拆解成独立的工作流，然后组合起来。

除了这种方式之外，我们还可以直接在一个工作流里实现非独立的批处理子工作流：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331230823.png?x-oss-process=image/resize,w_800/quality,q_95)

这是一种相对比较高级的写法，dify 和 coze 都支持，但更直观。

尽管如此，这种写法目前有一些局限，可能是 coze 的设计缺陷，并困惑了我一整个晚上，我尝试研究了coze 自带的「变量聚合」结点、「输出」结点、「变量赋值」结点，以及第三方插件「对象变量聚合」，都无法实现我想要的在一个批处理体中输出一个完整的 object 的功能。

最终我不得不写了一个代码块用于主动构造一个 object 的输出以便下游结点使用：

```nodejs
// 在这里，您可以通过 ‘params’  获取节点中的输入变量

// input: "https://p26-bot-workflow-sign.byteimg.com/tos-cn-i-mdko3gqilj/f423cd3a7a634394857fc0b17bf7e9d5.pdf~tplv-mdko3gqilj-image.image
// ?rk3s=81d4c505&x-expires=1774517959&x-signature=B2N2cG%2Be%2FM5eeZJPpvcwjXCpTic%3D&x-wf-file_name=Bytedance_BP_2013.pdf"

async function main({ params }: Args): Promise<Output> {

    // 对 URL 进行解析
    const url = new URL(params.input);

    // 获取查询字符串中的参数
    const query = url.searchParams.get('x-wf-file_name');

    if(!query) throw new Error("no query found")

    return {
        "file": {
            "name": query,
            "content": params.content
        }
    }
}
```

总之，我们终于实现了批量读取文件并结构化输出的功能，以便后续丢给大模型进行分析。

## 尝试 2：现在我们来试试让 AI 分析 BP 里的内容吧

我们把之前写好的批量文件解析工作流 `bp_read` 串联作为大模型的输入，然后使用我们的今日头条 BP 作为测例，发现大模型已经完美地解读出了我们的目标数据。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331235953.png?x-oss-process=image/resize,w_800/quality,q_95)

全部输出为：

```json
{
  "projectInfo": {
    "projectName": "最懂你的-基于社交挖掘和个性化推荐的新媒体",
    "companyName": "北京字节跳动科技有限公司",
    "companyCode": "",
    "industryCategory": "移动互联网/新媒体",
    "developmentStage": "成长期",
    "projectManager": "张一鸣",
    "contactPerson": "",
    "contactPhone": ""
  },
  "businessPlan": {
    "projectSummary": "基于社交挖掘和个性化推荐的新媒体平台，通过独创的个性化资讯发现引擎，为用户提供个性化的资讯阅读体验。",
    "productsAndServices": "头条网页版及系列APP，提供泛资讯内容，覆盖新闻、博客、影评、段子等，并通过个性化推荐技术精确推荐读者感兴趣内容。",
    "industryAndMarket": "移动互联网广告市场高速增长，泛阅读类应用已成为移动广告投放重要媒介。移动互联网开启了崭新的个性化数字媒体市场。",
    "coreTechnology": "独创的数据处理和推荐技术框架，自然语言处理、多媒体处理，社交挖掘分析，高维度用户兴趣建模，资讯建模和匹配，高性能的实时大规模数据运算。",
    "businessModel": "通过广告系统，基于用户兴趣和场景的推荐广告，以及数据输出服务实现商业化。",
    "coreTeam": "技术、产品、研发导向的核心成员，在搜索与数据处理，社交网络挖掘，移动产品方向经验丰富。",
    "strategicPlanning": "2013年产品会不断突破，加强进入壁垒，并尝试国际化和商业化。扩充信息类型和来源，强化社区互动，深挖用户特征，升级推荐系统。"
  },
  "patents": [],
  "teamMembers": [
    {
      "name": "张一鸣",
      "organization": "北京字节跳动科技有限公司",
      "position": "创始人 CEO",
      "education": "南开大学软件工程专业",
      "experience": "2012年3月，创立字节跳动；2009年9月，创立九九房；2008年，加入海内/饭否管理团队；2006年，加入酷讯；2005年，毕业南开大学软件工程专业。"
    },
    {
      "name": "黄河",
      "organization": "北京字节跳动科技有限公司",
      "position": "产品",
      "education": "北京工业大学",
      "experience": "9年经验，九九房移动产品总监，自我创业。"
    },
    {
      "name": "梁汝波",
      "organization": "北京字节跳动科技有限公司",
      "position": "研发",
      "education": "南开大学",
      "experience": "8年经验，艾克赛利主任工程师，九九房研发总监。"
    },
    {
      "name": "屠锋锋",
      "organization": "北京字节跳动科技有限公司",
      "position": "商务拓展",
      "education": "北京大学、德州大学",
      "experience": "11年经验，Oracle美国、微软中国高级产品经理，海豚浏览器VP。"
    }
  ],
  "financials": {
    "revenueProjections": [
      {
        "year": 2014,
        "amount": 6000
      }
    ],
    "expenseProjections": [
      {
        "year": 2012,
        "amount": 1450
      },
      {
        "year": 2013,
        "amount": 6254
      },
      {
        "year": 2014,
        "amount": 8968
      }
    ],
    "profitProjections": []
  }
}
```

## 经验 3：标准化结构化输出

尽管我们的大模型已经按照我们预设的数据结构输出了我们想要的内容，但是它被包裹在了一层代码块里，而非我们预期的一个干净的 json 文件。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401001002.png?x-oss-process=image/resize,w_800/quality,q_95)


那如果在 prompt 上增加一些限制，强制大模型生成标准化的 json 格式，是否可行呢？

答案是可行的，基于 claude 的指导，它推荐我在 prompt 的最后加上一段：

```md
注意：
1. 直接返回JSON字符串，不要添加任何markdown格式
2. 不要使用```json和```标记
3. 严格按照示例格式
```

确实有效，coze 终于直接返回不带代码块的核心内容了，并且似乎还做了自动识别大模型的输出是否可结构化（pretty json）的工作，如果可以的话，则可以点击大模型输出按钮，然后展现可钻取的数据对象。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401003228.png?x-oss-process=image/resize,w_800/quality,q_95)

## 经验 4：结构化输出的最佳实践

如果细心点我们可以发现，coze 在输出的 section 里还可以指定输出 json 格式。这是非常有意思的一种设定，在这里设定 json 结构后，就无需再在 prompt 里指定了，这样 prompt 可以精炼到极致了：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401005035.png?x-oss-process=image/resize,w_800/quality,q_95)

可以看到，**这套解决方案的系统提示词非常简单，就只是告诉它你要干嘛即可，而目标内容完全在输出里指定**。

这种做法的另一个优点是把逻辑与数据进行分离，非常便于后续维护，以及多少有点“**less structure, more intelligence**”的味道🤔

如果我们这时候点击大模型输出按钮，可以看到其结果正是我们第一套方案里不加咒语的标准化输出结果形式（输出包含代码段），所以我们可以合理怀疑，coze 是在默认大模型输出的基础之上，又做了一层 json 提取的工程优化。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401005101.png?x-oss-process=image/resize,w_800/quality,q_95)

除此之外，我们通过 coze 默认提供的 debug 窗口，可以看到实际的大模型通信流，所以当我们勾选了 json 的输出时，它会默认在调用大模型的参数里指定为 json，并且把我们在 json 格式输入框里指定的内容嵌入到 prompt 内。

我们可以开启 debug：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401005213.png?x-oss-process=image/resize,w_800/quality,q_95)

可以看到，实际的 system prompt 如下：

```markdown
- Carefully consider the user's question to ensure your answer is logical and makes sense.
- Make sure your explanation is concise and easy to understand, not verbose.
- Strictly return the answer in json format.
- Strictly Ensure that the following answer is in a valid JSON format.
- The output should be formatted as a JSON instance that conforms to the JSON schema below and do not add comments.

Here is the output schema:
'''
{
	"output": Output
}
Output:{
	"projectInfo": ProjectInfo
	"businessPlan": 
// …… （省略部分数据结构定义）

'''

// 以下则是我们写的 system prompt（自动嵌入了文件解析结果）
你是一名创投大赛的评委，现在我将给你一个参赛团队的 bp 等相关材料 [{'content': '![ 最懂你的](https://lf-bot-studio-plugin-resource.coze.cn/obj/bot-studio-platform-plugin-tos/BYTE_RAG_UPLOAD_BIZ_TYPE/None_1743439743731_JI5R0HrTJ3.jpeg)最懂你的 -基于社交挖掘和个
// ...（省略部分文件解析结果）
, 'name': 'Bytedance_BP_2013.pdf'}]，请你分析一下
```

这个 prompt 有几个值得玩味的地方：
1. 对大模型做了一些思考理性、回答人性的预设
2. 对大模型的回答做了全过程严格 json 化的约束
3. json 的 schema 是递归向前展开的（区别于标准的 json schema，参考：[JSON Schema | Fullstack.wiki](https://fullstack.wiki/json-schema/index)）
4. 用户引用的变量，是以文字形式直接嵌入 prompt 的（当然这几乎是所有工作流产品的标配）

ok，基于以上的分析，我们可以看到 coze 确实做了一些脏活，用户用起来更舒服了，效果也更好了。

## 经验 5：让 AI 快速地生成 json 结构体测例

那怎样快速地约定输出的结构化呢？在 AI 时代也很简单，让随便哪个大模型基于你预设的数据结构（结构参考客户或者大模型生成）生成一套伪数据：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329150232.png?x-oss-process=image/resize,w_800/quality,q_80)

然后复制粘贴导入即可：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329150424.png?x-oss-process=image/resize,w_800/quality,q_80)

当然，最好给这个数据结构加个顶层结点（比如 `data`），以方便后续直接引用整个结点的信息（但要注意结点展开层级不要超过 3，否则会丢失）：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329150735.png?x-oss-process=image/resize,w_800/quality,q_80)

btw，coze 的 json 结构化输出里的键不能是中文，这个 coze 团队应该考虑优化一下，还是有不少麻烦，后续文章我会提供一种智能的解决方案：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329151133.png?x-oss-process=image/resize,w_800/quality,q_80)


---

以上就是本篇教程的上篇，重点解决了我们解决方案里第一步 AI 读取与分析 BP 的需求，下期我们将实现下一步报告排版生成，敬请期待！
