
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

- 探索 1：看看有没有写好了的报告生成插件
- 探索 2：如何将 json 变量转成 md 格式
- 探索 3：如何实现高效翻译 json 键
- 探索 4：要不要这么麻烦？
- 是时候把这些工作都串起来了以及工作预告！
- coze 插件开发的一些注意事项
```

>本文为《从零开始：用Coze搭建BP智能评估系统》系列第二篇，聚焦AI自动化生成PDF报告的实战方案。
>
>通过开发`smart-json2md`插件实现JSON转Markdown，结合`json-key-translator`解决中英文键名翻译难题，最终打通从BP解析、数据转换到文档生成的完整链路。
>
>附开源代码与效果实测，效率提升90%，为创投评估提供高效自动化工具。

最近我们的一位客户需要实现 AI 自动解析 BP 并生成评估报告的功能，在经过一些调研后，我们决计采用 coze 实现其核心业务逻辑。

本篇是该系列第二篇，重点探讨如何程序化智能输出 pdf 文档的需求。在之前我们已经实现了 AI 读取与分析的需求，并确定了一种约定大模型结构化输出的最佳实践。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401110112.png?x-oss-process=image/resize,w_800/quality,q_95)

本文的主要测例为字节跳动今日头条 2013 年的 BP，后台回复 **今日头条**，即可阅览。
 ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250329161706.png?x-oss-process=image/resize,w_800/quality,q_80)

考虑到字节跳动的公开数据较多，为防止 AI 基于已学习的内容进行回答产生预期偏差，辅助测例采用了自己去年的 BP，感兴趣的朋友请后台证明您的投资人身份，即可阅览。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250331015835.png?x-oss-process=image/resize,w_800/quality,q_95)


下面开始我们的探索之旅。

## 探索 1：看看有没有写好了的报告生成插件

程序化生成报告是一个又复杂又常用的工作，一般我们要依赖第三方工具，所以先尝试搜索看看有没有官方的插件，果然，还是有的。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250401141914.png?x-oss-process=image/resize,w_800/quality,q_95)

但注意细节，这个 Doc Maker 插件的工具 create_document 的参数 formatted_markdown 是需要一个 markdown 格式的文字输入。

这也可以理解，因为 markdown 本身就有 section 之类的概念，是在程式语言里和文档相对比较近的，一搜也可以搜出一大堆。

但我们目前是 json 格式（为了控制大模型定向输出），所以需要先转成 markdown 格式。

搜了一圈，有一些转换的实现，但要么是转成表格（因为 json 往往是结构化的），要么 json 内部已经定义好了 h、p 等结点，和我们的需求不太吻合，我们是与 html 标签无关的纯数据。

看来，要手搓一个 json2md 插件了，让它可以把 top 的几层结点自动识别成嵌套的 markdown 标题结点，然后剩余的部分，就用可嵌套列表呈现即可。

说干就干，反正有 AI。

## 探索 2：如何将 json 变量转成 md 格式

AI 大概在一个小时内就理解了我的需求，实现了一个 npm 库（发布在[smart-json2md - npm](https://www.npmjs.com/package/smart-json2md)）。
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250402020326.png?x-oss-process=image/resize,w_800/quality,q_95)

并基于这个库包了一个 coze 插件。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250402022549.png?x-oss-process=image/resize,w_800/quality,q_95)

在 cursor 里大致的 prompt 如下（省略了 AI 的回复，再埋个彩蛋：正在做一个新的、更好用的 cursor 聊天记录导出插件）：

```md

我要开发一个 npm 脚本，用于将 json 文件转成 markdow  
  
目前查到的公开的 json2md 也是node 生态的，但是它的 json 里要约定h1、h2、p等键，参考：[IonicaBizau/json2md: :pushpin: A JSON to Markdown converter.](https://github.com/IonicaBizau/json2md)  
  
而我希望是一个平凡的 json 文件，转为自动有层级的 markdown，这个该如何设计  
  
另外，我发布的时候，是不是要换个名字？因为 json2md 被占了？是的话，取什么好

---

我觉得 与 smart 或者 auto 相关的命名会比较好

---

smart-json2md 如何

---

我觉得本工具应该支持任意深度的 json 转成以标题为主的嵌套结构，但markdown 的标题最大支持 6 级，而且用户有时候也不希望文章层级过多，所以应该允许用户输入最小标题层级（默认为 1）和最大标题层级（默认为6），当节点深度大于最大标题层级时，后续的内容就自动变成ordered/unordered bullet（也可以作为参数选项）

---

现在我想做成 coze 插件（需要是单文件，但可以把本项目 smart-json2md 作为环境依赖 ），位置@coze-plugin， 这是其官方的示例代码：  
  
  
import { Args } from '@/runtime'; import { Input, Output } from "@/typings/json2md/json2md"; /** * Each file needs to export a function named `handler`. This function is the entrance to the Tool. * @param {Object} args.input - input parameters, you can get test input value by input.xxx. * @param {Object} args.logger - logger instance used to print logs, injected by runtime * @returns {*} The return data of the function, which should match the declared output parameters. * * Remember to fill in input/output in Metadata, it helps LLM to recognize and use tool. */ export async function handler({ input, logger }: Args<Input>): Promise<Output> { return { message: "Hello, world!", }; };

```

基于此，我们测试一下，看到，基本满足需求，json 格式的输出已经自动转成了有章节的 markdown 格式。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250402020814.png?x-oss-process=image/resize,w_800/quality,q_95)

但发现还有一个问题（之前文章留的一个彩蛋），由于 coze 内的结构化输出必须用英文键，导致我们的输出是英文的标题，这就很怪异，需要转换。

## 探索 3：如何实现高效翻译 json 键

考虑到键又不是很多（但也不是很少），手动翻译这个事情会让人心累，不如交给大模型自动完成。

但如果我们一股脑地把整个 json 文件丢给大模型，由于文件可能很大，但翻译的键又很少，又必然造成很多浪费，所以我们需要一种权衡的办法。

经过大概一天的探索，我大概探索了以下方案：
1. 递归遍历获得 json 变量的所有 keys，每个单独地调用翻译 api（例如 google）
2. 递归遍历获得 json 变量的所有 keys，然后全部一起调用一次翻译 api（例如 deepseek），生成翻译后的 string list
3. 程序化将 json 转成 json schema，再用 llm 翻译这个 schema，再回头组装

其中，方案一显然性能有点差，方案三主要是考虑同一个单词在不同语境里可能有不同的翻译，所以希望基于 json schmea 尽可能保留其环境特征，从而能让大模型更准确地翻译。我也确实花了点时间写了一个这样的插件（尽管是 AI 写的）。

但即使我们拿到了 schema 表，也需要一个中间映射表，而且标准的 json schema 还是挺复杂的，要加 `type`、`object`等字段，对于我们这个需求来说，有点冗余。

所以，最后我选择了方案二。

为了实现方案二，我们需要拆解成三步：

1. 实现 json2keys 函数：从 json 中提取所有的键，成为一个列表（或者元祖，都可以）
2. 实现翻译函数：接收一个字符串列表，输出翻译后的字符串列表（基于大模型）
3. 实现 `translate_json_keys` 函数：基于输入的 json 变量和翻译后的字符串列表构建映射表，再基于这个映射表实现键的翻译

我过去两天探索这个花了不少时间，如果只是为了实现端到端的翻译 json 变量的键，用 AI 写起来还是挺方便的，但是为了思考把大模型那一步择出去，导致代码就复杂了很多。

我给 cursor 的 prompt 最终是这么写的（之前已经经历了三个大版本的迭代）：

```md
我要开发一个 npm库 json-key-translator，用于翻译 json 变量里的英文键  
  
它的输入是一个 json 变量  
  
我的思路是可以对照网站 i18n 的操作，为目标语言生成一个映射表，区别是 i18n 里基于映射表修改的是原 json 的值，现在我们映射的是键、改的是键  
  
至于生成这个待翻译的映射表，可以考虑用 deepseek 大模型实现
```

后面也改了很多，但最终还是完成了任务，代码开源在：
- [MarkShawn2020/2025-04-02_json-key-translator: 高效的 json 键翻译脚本，支持对接 coze](https://github.com/MarkShawn2020/2025-04-02_json-key-translator)
- [json-key-translator - npm](https://www.npmjs.com/package/json-key-translator)

在我们开源的 npm 库 `json-key-translator` 中主要导出了两个函数：

- extractKeysFromJson 用于从 json 变量中提取 key 列表，基于这个我们实现了 coze 插件中的 json2keys 工具
- translateKeys 在参数中指定翻译函数，用于直接翻译 json 变量，基于这个再加上翻译工作流我们实现了 coze 插件中的 translate_json_keys 工具

其中，我们的翻译工作流非常简单，就指定一个列表输入，让 coze 翻译，输出另一个列表即可。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404224827.png?x-oss-process=image/resize,w_800/quality,q_95)

但我们需要把这个工作流嵌入到插件中，这需要一点新思，我们需要用到 coze 的 API 技术。

参考 [在 coze 中执行工作流](https://www.coze.cn/open/playground/workflow_run)章节，我们只需要修改我们的 token 和 workflow id，然后复制代码到我们的插件内即可。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404225411.png?x-oss-process=image/resize,w_800/quality,q_95)

最后我们在 coze 平台的插件里调用工作流的核心代码为：

```ts
import { Args } from '@/runtime';
import { Input, Output } from "@/typings/translate_json_keys/translate_json_keys";
import {translateKeys, extractKeysFromJson} from 'json-key-translator';
// Our official coze sdk for JavaScript [coze-js](https://github.com/coze-dev/coze-js)
import { CozeAPI } from '@coze/api';


export async function handler({ input, logger }: Args<Input>): Promise<Output> {
  logger.info(`input: ${JSON.stringify(input, null, 2)}`)
  const json = JSON.parse(input.json)

  const translatedJson = await translateKeys(json, {
    targetLanguage: "zh",

    translationFn: async(json, options) => {
      logger.debug(`json: ${JSON.stringify(json, null, 2)}`)

      const apiClient = new CozeAPI({
        token: input.COZE_TOKEN,
        baseURL: 'https://api.coze.cn'
      });

      const res = await apiClient.workflows.runs.create({
        workflow_id: '7489415965785079848',
        is_async: false,
        parameters: {
        input: JSON.stringify(json.keys),
        },
      })
      logger.info(`translated result: ${JSON.stringify(res, null, 2)}`)

      const data = JSON.parse(res.data).output
      logger.debug(`data: ${data}`)
      return data

    },
  });

  return {
    output: JSON.stringify(translatedJson.translatedJson),
  };
}
```

所以我们现在已经实现了通过一个插件把 json 中的英文键翻译成中文，所以把这个插件嵌入到我们之前的报告解析流，就可以直接中文的结构化输出啦。

## 探索 4：要不要这么麻烦？

我们回顾一下我们的工作。

我们为了更好地结构化解析 BP 资料，在 coze 大模型的输出章节使用了 json 变量，基于此我们大幅简化了 prompt，生成的结果也更可预期。

但由于 coze 的设计缺陷，为了使用这个 json 的变量，我们必须使用英文的键，导致在输出报告的时候中英文混杂很尴尬。

因此为了解决翻译的问题，我们写了一个通用的翻译插件，再把输出的英文 json 翻译回来。

这里面有一点是可以优化的。

我们为什么不可以直接输出中文的 json 呢？

既然中文对我们更重要，而且coze 所谓的强制 json 输出也只是在 prompt 上做了一些约束，我们完全可以也直接使用中文的 prompt，这样就可以直出中文 json 了。

所以我们的 prompt 改为如下：

```md
您是一名创投大赛评委，请分析一个参赛团队的 bp 材料 {{input}}，目标数据结构：

	```json
	{
	  "项目信息": {
	    "项目名称": "string",
	    "企业名称": "string",
	    "企业代码": "string",
	    "行业分类": "string",
	    "发展阶段": "string",
	    "项目负责人": "string",
	    "项目联系人": "string",
	    "联系电话": "string"
	  },
	  "商业计划书": {
	    "项目简介": "string",
	    "产品与服务": "string",
	    "行业与市场": "string",
	    "核心技术": "string",
	    "商业模式": "string",
	    "核心团队": "string",
	    "战略规划": "string"
	  },
	  "专利列表": [
	    {
	      "专利号": "string",
	      "专利名称": "string",
	      "发明人": ["string"]
	    }
	  ],
	  "团队成员": [
	    {
	      "姓名": "string",
	      "单位": "string",
	      "职务": "string",
	      "学历": "string",
	      "履历": "string"
	    }
	  ],
	  "财务信息": {
	    "收入预测": [
	      {
	        "年份": "number",
	        "金额": "number"
	      }
	    ],
	    "支出预测": [
	      {
	        "年份": "number",
	        "金额": "number"
	      }
	    ],
	    "利润预测": [
	      {
	        "年份": "number",
	        "金额": "number"
	      }
	    ]
	  }
	}
	```

注意：
1. 直接返回JSON字符串，不要添加任何markdown格式
2. 不要使用```json和```标记
3. 严格按照示例格式
```

基于此思路，我们升级了我们的工作流，在输入口添加了一个 `useJson` 布尔变量，当勾选时我们走英文 json 再翻译的路径，不勾选时我们走直出，效果如下，非常ok：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404233235.png?x-oss-process=image/resize,w_800/quality,q_95)

## 是时候把这些工作都串起来了以及工作预告！

好了，现在我们已经基于各种工作流、插件，实现了输入一份或者多份 BP 材料，输出一个中文 json，再自动转成 markdown，再自动生成 docx 文档，现在是时候串起来看看效果了。

我们输入今日头条的测例：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250405003440.png?x-oss-process=image/resize,w_800/quality,q_95)

工作流跑完后输出了一份解析后的 docx 文档，打开后内容如下：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250405003655.png?x-oss-process=image/resize,w_800/quality,q_95)

可以看到，该有的内容基本都有了。

但依旧有一些缺陷：

1. 生成的文档，在内容上还不够详实，审美上也有待大幅提高
2. 生成的文档是个 oss 网址，如果能直接生成文档的预览就好了

基于以上的问题，我们将在下一期文章中做进一步的探索与实现。

可以预告的是：

1. 我们将有一个小程序的实现
2. 我们将允许直接生成用户预设的 docx 模板（这是一个超棒的功能，为此我们还独立开发了一个独立的网站，敬请期待！）
3. 我们将优化 prompt、对接更多 API、采用browser use等技术 以丰富内容并非降低幻觉

## coze 插件开发的一些注意事项

- 插件的工具里可以先定义好元数据的输入与输出参数，接着就可以在代码里从 `@/typings/XX/XX`里导入输入与输出的 schema（XX 是工具名），也建议如此去写，而不要在代码里独立定义输入与输出的 schema，因为：
	- 如果代码运行时不符合代码的 schema，会在工具页测试不通过；
	- 如果代码运行时符合代码的 schema，但不符合元数据的 schema，会通过工具页测试，**但是会在插件页的”运行示例“按钮处运行失败，并且也会在被外部调用时失败，这是 coze 的一个设计不同步的缺陷**
- **在插件的变量定义里声明通用 object 是一个灾难**。因为我们必须清晰地声明这个 object 的所有键乃至子键，否则不被通过：
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404232324.png?x-oss-process=image/resize,w_800/quality,q_95)

- 插件的依赖包更新太慢（npmjs 上已经更新版本，但是 coze 这边要过好几个小时才能同步，新发布一个包倒是立即就能搜到），这在基于自己本地开发、快速迭代的库时是个灾难；以及 `@coze/api`包竟然不是内置🤔
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404232414.png?x-oss-process=image/resize,w_800/quality,q_95)

- 此外，在被外部调用时，工具页的线上日志始终是空的，应该也是一个 bug：
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250404232343.png?x-oss-process=image/resize,w_800/quality,q_95)


---

以上就是本篇教程的上篇，重点解决了我们解决方案里第三步 AI 程序化输出报告的需求，下期我们继续，敬请期待！
