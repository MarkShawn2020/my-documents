---
title: 使用 Vertex AI 中的 Gemini API 生成内容 bookmark_borderbookmark 使用集合让一切井井有条 根据您的偏好保存内容并对其进行分类
slug: vertex-ai-gemini-api-bookmark_borderbookmark-1765498836331
source: https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/inference?hl=zh-cn
datetime: 2025-12-12T00:20:36.331Z
---

-   [Home](https://docs.cloud.google.com/?hl=zh-cn)
-   [Documentation](https://docs.cloud.google.com/docs?hl=zh-cn)
-   [AI and ML](https://docs.cloud.google.com/docs/ai-ml?hl=zh-cn)
-   [Vertex AI](https://docs.cloud.google.com/vertex-ai/docs?hl=zh-cn)
-   [Generative AI on Vertex AI](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/learn/overview?hl=zh-cn)
-   [API 参考](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/reference/rest?hl=zh-cn)

该内容对您有帮助吗？

发送反馈

# 使用 Vertex AI 中的 Gemini API 生成内容 bookmark\_borderbookmark 使用集合让一切井井有条 根据您的偏好保存内容并对其进行分类。

-   本页内容
-   [创建 Google Cloud 账号以开始使用](#get-started)
-   [支持的模型](#supported-models)
-   [参数列表](#parameters)
    -   [请求正文](#request)
    -   [响应正文](#response)
-   [示例](#sample-requests)
    -   [文本生成](#sample-requests-text-gen)
    -   [使用多模态提示](#sample-requests-text-gen-multimodal-prompt)
    -   [流式传输文本回答](#sample-requests-text-stream-response)
-   [模型版本](#model_versions)
-   [后续步骤](#whats_next)

使用 `generateContent` 或 `streamGenerateContent` 可通过 Gemini 生成内容。

Gemini 模型系列包含可处理多模态提示请求的模型。多模态一词表示您可以在一个提示中使用多种模态（或输入类型）。非多模态模型仅接受文本提示。模态可以包括文本、音频、视频等。

## 创建 Google Cloud 账号以开始使用

如需开始使用 Vertex AI 中的 Gemini API，请[创建一个 Google Cloud 账号](https://console.cloud.google.com/freetrial?redirectPath=%2Fmarketplace%2Fproduct%2Fgoogle%2Fcloudaicompanion.googleapis.com&hl=zh-cn)。

创建账号后，您可以使用本文档了解 Gemini 模型的[请求正文](#request)、[模型参数](#parameters)和[响应正文](#response)，并查看一些示例[请求](#sample-requests)。

准备就绪后，请参阅 [Vertex AI 中的 Gemini API 快速入门](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/start/quickstarts/quickstart-multimodal?hl=zh-cn)，了解如何使用编程语言 SDK 或 REST API 向 Vertex AI 中的 Gemini API 发送请求。

## 支持的模型

所有 Gemini 模型都支持内容生成。

**注意：**向请求添加大量图片会增加回答延迟时间。

## 参数列表

如需了解实现详情，请参阅[示例](#sample-requests)。

### 请求正文

查看更多代码操作。

浅色代码主题背景

深色代码主题背景

{
  "cachedContent": string,
  "contents": \[
    {
      "role": string,
      "parts": \[
        {
          // Union field data can be only one of the following:
          "text": string,
          "inlineData": {
            "mimeType": string,
            "data": string
          },
          "fileData": {
            "mimeType": string,
            "fileUri": string
          },
          // End of list of possible types for union field data.

          "videoMetadata": {
            "startOffset": {
              "seconds": integer,
              "nanos": integer
            },
            "endOffset": {
              "seconds": integer,
              "nanos": integer
            },
            "fps": double
          },
          "mediaResolution": enum
        }
      \]
    }
  \],
  "systemInstruction": {
    "role": string,
    "parts": \[
      {
        "text": string
      }
    \]
  },
  "tools": \[
    {
      "functionDeclarations": \[
        {
          "name": string,
          "description": string,
          "parameters": {
            object ([Ope](https://spec.openapis.org/oas/v3.0.3#schema)[nAPI Object Schema](https://spec.openapis.org/oas/v3.0.3#schema))
          }
        }
      \]
    }
  \],
  "safetySettings": \[
    {
      "category": enum (HarmCategory),
      "threshold": enum (HarmBlockThreshold)
    }
  \],
  "generationConfig": {
    "temperature": number,
    "topP": number,
    "topK": number,
    "candidateCount": integer,
    "maxOutputTokens": integer,
    "presencePenalty": float,
    "frequencyPenalty": float,
    "stopSequences": \[
      string
    \],
    "responseMimeType": string,
    "responseSchema": [schema](https://docs.cloud.google.com/vertex-ai/docs/reference/rest/v1/projects.locations.cachedContents?hl=zh-cn#Schema),
    "seed": integer,
    "responseLogprobs": boolean,
    "logprobs": integer,
    "audioTimestamp": boolean,
    "thinkingConfig": {
      "thinkingBudget": integer,
      "thinkingLevel": enum
    },
    "mediaResolution": enum
  },
  "labels": {
    string: string
  }
}

请求正文中包含具有以下参数的数据：

| 参数 |
| --- |
| 
`cachedContent`

 | 

可选：`string`

用作提供预测的上下文的缓存内容的名称。格式：`projects/{project}/locations/{location}/cachedContents/{cachedContent}`

 |
| 

`contents`

 | 

必需：`Content`

与模型当前对话的内容。

对于单轮查询，这是单个实例。对于多轮查询，这是包含对话历史记录和最新请求的重复字段。

 |
| 

`systemInstruction`

 | 

可选：`Content`。

适用于 `gemini-2.0-flash` 和 `gemini-2.0-flash-lite`。

有关引导模型获得更好性能的说明。例如，“回答尽可能简明扼要”或“请勿在回答中使用技术词汇”。

`text` 字符串会计入 token 限制。

`systemInstruction` 的 `role` 字段会被忽略，不会影响模型的性能。

**注意：**`parts` 中只应使用 `text`，并且每个 `part` 中的内容都应位于单独的段落中。

 |
| 

`tools`

 | 

可选。一段代码，可让系统与外部系统进行交互，以在模型知识和范围之外执行操作或一组操作。 请参阅[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/function-calling?hl=zh-cn)。

 |
| 

`toolConfig`

 | 

可选。请参阅[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/function-calling?hl=zh-cn)。

 |
| 

`safetySettings`

 | 

可选：`SafetySetting`。

针对每个请求的设置，用于屏蔽不安全内容。

在 `GenerateContentResponse.candidates` 上强制执行。

 |
| 

`generationConfig`

 | 

可选：`GenerationConfig`。

生成配置设置。

 |
| 

`labels`

 | 

可选：`string`。

您可以采用键值对格式添加到 API 调用中的元数据。

 |

#### `contents`

包含消息的多部分内容的基本结构化数据类型。

此类包含两个主要属性：`role` 和 `parts`。`role` 属性表示生成内容的个人，而 `parts` 属性包含多个元素，每个元素表示消息中的一段数据。

| 参数 |
| --- |
| 
`role`

 | 

`string`

创建消息的实体的身份。支持以下值：

-   `user`：表示消息是由真人发送的，通常是用户生成的消息。
-   `model`：表示消息是由模型生成的。

`model` 值用于在多轮对话期间将来自模型的消息插入到对话中。

 |
| 

`parts`

 | 

`Part`

构成单条消息的有序部分的列表。不同的部分可能具有不同的 [IANA MIME 类型](https://www.iana.org/assignments/media-types/media-types.xml)。

如需了解输入限制（例如 token 或图片数量上限），请参阅 [Google 模型](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/learn/models?hl=zh-cn)页面上的模型规范部分。

如需计算请求中的 token 数量，请参阅[获取 token 数](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/get-token-count?hl=zh-cn)。

 |

#### `parts`

包含属于多部分 `Content` 消息一部分的媒体的数据类型。

| 参数 |
| --- |
| 
`text`

 | 

可选：`string`。

文本提示或代码段。

 |
| 

`inlineData`

 | 

可选：`Blob`。

原始字节中的内嵌数据。

对于 `gemini-2.0-flash-lite` 和 `gemini-2.0-flash`，您可以使用 `inlineData` 指定最多 3000 张图片。

 |
| 

`fileData`

 | 

可选：`fileData`。

存储在文件中的数据。

 |
| 

`functionCall`

 | 

可选：`FunctionCall`。

它包含表示 `FunctionDeclaration.name` 字段的字符串，以及包含模型预测的函数调用的所有参数的结构化 JSON 对象。

请参阅[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/function-calling?hl=zh-cn)。

 |
| 

`functionResponse`

 | 

可选：`FunctionResponse`。

`FunctionCall` 的结果输出，其中包含表示 `FunctionDeclaration.name` 字段的字符串和包含函数调用的任何输出的结构化 JSON 对象。它用作模型的上下文。

请参阅[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/function-calling?hl=zh-cn)。

 |
| 

`videoMetadata`

 | 

可选：`VideoMetadata`。

对于视频输入，为视频的开始和结束偏移量（采用[时长](https://protobuf.dev/reference/protobuf/google.protobuf/#duration)格式），以及视频的帧速率。例如，如需指定从 1:00 开始的 10 秒剪辑，帧速率为每秒 10 帧，请设置以下内容：

-   `"startOffset": { "seconds": 60 }`
-   `"endOffset": { "seconds": 70 }`
-   `"fps": 10.0`

仅当视频数据以 `inlineData` 或 `fileData` 形式呈现时，才应指定元数据。

 |
| 

`mediaResolution`

 | 

可选：`enum`。

控制输入媒体的处理方式。如果指定，则此配置会替换 `generationConfig` 中的 `mediaResolution` 设置。 `LOW` 会减少每个图片/视频的 token 数量，这可能会导致细节丢失，但允许在上下文中包含更长的视频。支持的值：`HIGH`、`MEDIUM`、`LOW`。

 |

#### `blob`

内容 blob。如果可能，这会以文本而非原始字节的形式发送。

| 参数 |
| --- |
| 
`mimeType`

 | 

`string`

在 `data` 或 `fileUri` 字段中指定的文件的媒体类型。可接受的值包括：

**点击即可展开 MIME 类型**

-   `application/pdf`
-   `audio/mpeg`
-   `audio/mp3`
-   `audio/wav`
-   `image/png`
-   `image/jpeg`
-   `image/webp`
-   `text/plain`
-   `video/mov`
-   `video/mpeg`
-   `video/mp4`
-   `video/mpg`
-   `video/avi`
-   `video/wmv`
-   `video/mpegps`
-   `video/flv`

对于 `gemini-2.0-flash-lite` 和 `gemini-2.0-flash`，音频文件的时长上限为 8.4 小时，视频文件（不含音频）的时长上限为 1 小时。如需了解详情，请参阅 Gemini [音频](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/audio-understanding?hl=zh-cn#audio-requirements)和[视频](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/video-understanding?hl=zh-cn#video-requirements)要求。

文本文件必须采用 UTF-8 编码。文本文件的内容会计入 token 数限制。

图片分辨率没有限制。

 |
| 

`data`

 | 

`bytes`

[：要在提示中包含内嵌的图片、PDF 或视频的](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/image/base64-encode?hl=zh-cn) base64 编码。添加媒体内嵌时，您还必须指定数据的媒体类型 (`mimeType`)。

大小上限：20MB

 |

#### FileData

URI 或网址数据。

| 参数 |
| --- |
| 
`mimeType`

 | 

`string`

数据的 [IANA MIME 类型](https://www.iana.org/assignments/media-types/media-types.xml)。

 |
| 

`fileUri`

 | 

`string`

要包含在提示中的文件的 URI 或网址。可接受的值包括：

-   **Cloud Storage 存储桶 URI**：对象必须可公开读取，或者位于发送请求的同一 Google Cloud 项目中。对于 `gemini-2.0-flash` 和 `gemini-2.0-flash-lite`，大小限制为 2 GB。
-   **HTTP 网址：**文件网址必须可公开读取。您可以为每个请求指定一个视频文件、一个音频文件和最多 10 个图片文件。音频文件、视频文件和文档的大小不得超过 15 MB。
-   **YouTube 视频网址**：YouTube 视频必须由您用于登录 Google Cloud 控制台的账号所拥有，或者是公开的。每个请求仅支持一个 YouTube 视频网址。

指定 `fileURI` 时，您还必须指定文件的媒体类型 (`mimeType`)。 如果启用了 VPC Service Controls，则不支持为 `fileURI` 指定媒体文件网址。

 |

#### `functionCall`

从模型返回的预测 `functionCall`，其中包含表示 `functionDeclaration.name` 的字符串和包含参数及其值的结构化 JSON 对象。

| 参数 |
| --- |
| 
`name`

 | 

`string`

要调用的函数名称。

 |
| 

`args`

 | 

`Struct`

以 JSON 对象格式表示的函数参数和值。

如需了解参数详情，请参阅[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/function-calling?hl=zh-cn)。

 |

#### `functionResponse`

`FunctionCall` 的生成输出，其中包含表示 `FunctionDeclaration.name` 的字符串。还包含带有函数输出的结构化 JSON 对象（并将其用作模型的上下文）。这应包含根据模型预测生成的 `FunctionCall` 的结果。

| 参数 |
| --- |
| 
`name`

 | 

`string`

要调用的函数名称。

 |
| 

`response`

 | 

`Struct`

以 JSON 对象格式表示的函数响应。

 |

#### `videoMetadata`

用于描述输入视频内容的元数据。

| 参数 |
| --- |
| 
`startOffset`

 | 

可选：`google.protobuf.Duration`。

视频的起始偏移量。

 |
| 

`endOffset`

 | 

可选：`google.protobuf.Duration`。

视频的结束偏移量。

 |
| 

`fps`

 | 

可选：`double`。

发送给模型的视频的帧速率。如果未指定，则默认值为 `1.0`。可接受的最小值可低至 `0.0`，但不包括该值。最大值为 `24.0`。

 |

#### `safetySetting`

安全设置。

| 参数 |
| --- |
| 
`category`

 | 

可选：`HarmCategory`。

要为其配置阈值的安全类别。可接受的值包括：

**点击即可展开安全类别**

-   `HARM_CATEGORY_SEXUALLY_EXPLICIT`
-   `HARM_CATEGORY_HATE_SPEECH`
-   `HARM_CATEGORY_HARASSMENT`
-   `HARM_CATEGORY_DANGEROUS_CONTENT`

 |
| 

`threshold`

 | 

可选：`HarmBlockThreshold`。

基于概率阻止属于指定安全类别的响应的阈值。

-   `OFF`
-   `BLOCK_NONE`
-   `BLOCK_LOW_AND_ABOVE`
-   `BLOCK_MEDIUM_AND_ABOVE`
-   `BLOCK_ONLY_HIGH`

 |
| 

`method`

 | 

可选：`HarmBlockMethod`。

指定是将阈值用于概率得分还是严重程度得分。如果未指定，则系统会将阈值用于概率得分。

 |

#### `harmCategory`

用于屏蔽内容的有害类别。

| 参数 |
| --- |
| 
`HARM_CATEGORY_UNSPECIFIED`

 | 

未指定有害类别。

 |
| 

`HARM_CATEGORY_HATE_SPEECH`

 | 

有害类别为仇恨言论。

 |
| 

`HARM_CATEGORY_DANGEROUS_CONTENT`

 | 

有害类别为危险内容。

 |
| 

`HARM_CATEGORY_HARASSMENT`

 | 

有害类别为骚扰。

 |
| 

`HARM_CATEGORY_SEXUALLY_EXPLICIT`

 | 

有害类别为露骨色情内容。

 |

#### `harmBlockThreshold`

用于屏蔽回答的概率阈值级别。

| 参数 |
| --- |
| 
`HARM_BLOCK_THRESHOLD_UNSPECIFIED`

 | 

未指定的有害屏蔽阈值。

 |
| 

`BLOCK_LOW_AND_ABOVE`

 | 

屏蔽低阈值及以上的内容（即屏蔽较多的内容）。

 |
| 

`BLOCK_MEDIUM_AND_ABOVE`

 | 

屏蔽中等阈值及以上的内容。

 |
| 

`BLOCK_ONLY_HIGH`

 | 

仅屏蔽高阈值内容（即屏蔽较少的内容）。

 |
| 

`BLOCK_NONE`

 | 

全部不屏蔽。

 |
| 

`OFF`

 | 

在所有类别都已停用的情况下关闭安全设置

 |

#### `harmBlockMethod`

根据概率和严重级别组合屏蔽回答的概率阈值。

| 参数 |
| --- |
| 
`HARM_BLOCK_METHOD_UNSPECIFIED`

 | 

未指定有害内容屏蔽方法。

 |
| 

`SEVERITY`

 | 

有害内容屏蔽方法同时使用可能性得分和严重程度得分。

 |
| 

`PROBABILITY`

 | 

有害内容屏蔽方法使用概率得分。

 |

#### `generationConfig`

生成提示时使用的配置设置。

| 参数 |
| --- |
| 
`temperature`

 | 

可选：`float`。

温度 (temperature) 在生成回复期间用于采样，在应用 `topP` 和 `topK` 时会生成回复。温度可以控制词元选择的随机性。 较低的温度有利于需要更少开放性或创造性回复的提示，而较高的温度可以带来更具多样性或创造性的结果。温度为 `0` 表示始终选择概率最高的词元。在这种情况下，给定提示的回复大多是确定的，但可能仍然有少量变化。

如果模型返回的回答过于笼统、过于简短，或者模型给出后备回答，请尝试提高温度。 如果模型进入无限生成状态，将温度提高到至少 `0.1` 可能会改善结果。

`1.0` 是建议的温度初始值。

-   `gemini-2.0-flash-lite` 的范围：`0.0 - 2.0`（默认值：`1.0`）
-   `gemini-2.0-flash` 的范围：`0.0 - 2.0`（默认值：`1.0`）

如需了解详情，请参阅[内容生成参数](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/content-generation-parameters?hl=zh-cn#temperature)。

 |
| 

`topP`

 | 

可选：`float`。

如果指定，则使用核采样。

[Top-P](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/content-generation-parameters?hl=zh-cn#top-p) 可更改模型选择输出 token 的方式。系统会按照概率从最高（见 Top-K）到最低的顺序选择 token，直到所选 token 的概率总和等于 Top-P 的值。例如，如果 token A、B 和 C 的概率分别为 0.3、0.2 和 0.1，并且 top-P 值为 `0.5`，则模型将选择 A 或 B 作为下一个 token（通过温度确定），并会排除 C，将其作为候选 token。

指定较低的值可获得随机程度较低的回答，指定较高的值可获得随机程度较高的回答。

-   范围：`0.0 - 1.0`
-   默认（对于 `gemini-2.0-flash-lite`）：`0.95`
-   默认（对于 `gemini-2.0-flash`）：`0.95`

 |
| 

`candidateCount`

 | 

可选：`int`。

要返回的响应变体数量。 对于每个请求，您需要为所有候选词元的输出词元付费，但只需为输入词元支付一次费用。

指定多个候选项是适用于 `generateContent` 的预览版功能（不支持 `streamGenerateContent`）。支持以下型号：

-   `gemini-2.0-flash-lite`：`1`\-`8`，默认值：`1`
-   `gemini-2.0-flash`：`1`\-`8`，默认值：`1`

 |
| 

`maxOutputTokens`

 | 

可选：int

回复中可生成的词元数量上限。词元约为 4 个字符。100 个词元对应大约 60-80 个单词。

指定较低的值可获得较短的回答，指定较高的值可获得可能较长的回答。

如需了解详情，请参阅[内容生成参数](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/content-generation-parameters?hl=zh-cn#max-output-tokens)。

 |
| 

`stopSequences`

 | 

可选：`List[string]`。

指定一个字符串列表，告知模型在响应中遇到其中一个字符串时，停止生成文本。如果某个字符串在响应中多次出现，则响应会在首次出现的位置截断。字符串区分大小写。  
  
例如，未指定 `stopSequences` 时，如果下面的内容是返回的回复：  
  
`public static string reverse(string myString)`  
  
则返回的回复为以下内容，其中 `stopSequences` 设置为 `["Str", "reverse"]`：  
  
`public static string`

列表中的项目数量上限为 5 个。

如需了解详情，请参阅[内容生成参数](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/content-generation-parameters?hl=zh-cn#stop-sequences)。

 |
| 

`presencePenalty`

 | 

可选：`float`。

正例惩罚。

正值会惩罚生成的文本中已存在的 token，从而增加生成更多样化内容的概率。

`presencePenalty` 的最大值为 `2.0`，但不包括该数值。最小值为 `-2.0`。

 |
| 

`frequencyPenalty`

 | 

可选：`float`。

正值会惩罚生成的文本中反复出现的 token，从而降低重复内容概率。

`frequencyPenalty` 的最大值为 `2.0`，但不包括该数值。最小值为 `-2.0`。

 |
| 

`responseMimeType`

 | 

可选：`string (enum)`。

生成的候选文本的输出回答 MIME 类型。

支持以下 MIME 类型：

-   `application/json`：候选项中的 JSON 响应。
-   `text/plain`（默认值）：纯文本输出。
-   `text/x.enum`：对于分类任务，输出回答架构中定义的枚举值。

指定适当的回答类型，以避免出现意外行为。例如，如果您需要 JSON 格式的回答，请指定 `application/json`，而不是 `text/plain`。

`text/plain` 不支持与 `responseSchema` 搭配使用。 |
| 

`responseSchema`

 | 

可选：[schema](https://docs.cloud.google.com/vertex-ai/docs/reference/rest/v1/projects.locations.cachedContents?hl=zh-cn#Schema)

生成的候选文本必须遵循的架构。如需了解详情，请参阅[控制生成的输出](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/control-generated-output?hl=zh-cn)。

如需使用此参数，您必须为 `responseMimeType` 参数指定除 `text/plain` 以外的受支持 MIME 类型。

 |
| 

`seed`

 | 

可选：`int`。

当种子固定为特定值时，模型会尽最大努力为重复请求提供相同的回答。无法保证确定性输出。此外，更改模型或参数设置（例如温度）可能会导致回答发生变化，即使您使用相同的种子值也是如此。默认情况下，系统会使用随机种子值。

 |
| 

`responseLogprobs`

 | 

可选：`boolean`。

如果为 true，则返回模型在每个步骤中选择的 token 的对数概率。默认情况下，此参数设置为 `false`。

 |
| 

`logprobs`

 | 

可选：`int`。

返回每个生成步骤中排名靠前的候选 token 的对数概率。模型的所选 token 可能与每个步骤中排名靠前的候选 token 不同。使用介于 `1` 到 `20` 范围内的整数值指定要返回的候选项数量。

您必须启用 [`responseLogprobs`](#responseLogprobs) 才能使用此参数。

 |
| 

`audioTimestamp`

 | 

可选：`boolean`。

适用于以下模型：

-   Gemini 2.0 Flash-Lite
-   Gemini 2.0 Flash

为仅音频文件启用时间戳理解功能。

这是预览版功能。

 |
| 

`thinkingConfig`

 | 

可选：`object`。

针对 Gemini 2.5 及更高版本模型的[思考过程](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/thinking?hl=zh-cn)配置。

`thinkingConfig` 对象包含以下字段：

-   `thinkingBudget`：`integer`。默认情况下，模型会自动控制其思考程度不超过 `8,192` 个 token。
-   `thinkingLevel`：`enum`。控制模型在生成回答之前执行的内部推理量。较高的级别可能会提高复杂任务的质量，但会增加延迟和费用。支持的值包括 `LOW` 和 `HIGH`。

 |
| 

`mediaResolution`

 | 

可选：`enum`。

控制输入媒体的处理方式。`LOW` 会减少每个图片/视频的 token 数量，这可能会导致细节丢失，但允许在上下文中包含更长的视频。支持的值：`HIGH`、`MEDIUM`、`LOW`。

 |

### 响应正文

查看更多代码操作。

浅色代码主题背景

深色代码主题背景

{
  "candidates": \[
    {
      "content": {
        "parts": \[
          {
            "text": string
          }
        \]
      },
      "finishReason": enum (FinishReason),
      "safetyRatings": \[
        {
          "category": enum (HarmCategory),
          "probability": enum (HarmProbability),
          "blocked": boolean
        }
      \],
      "citationMetadata": {
        "citations": \[
          {
            "startIndex": integer,
            "endIndex": integer,
            "uri": string,
            "title": string,
            "license": string,
            "publicationDate": {
              "year": integer,
              "month": integer,
              "day": integer
            }
          }
        \]
      },
      "avgLogprobs": double,
      "logprobsResult": {
        "topCandidates": \[
          {
            "candidates": \[
              {
                "token": string,
                "logProbability": float
              }
            \]
          }
        \],
        "chosenCandidates": \[
          {
            "token": string,
            "logProbability": float
          }
        \]
      }
    }
  \],
  "usageMetadata": {
    "promptTokenCount": integer,
    "candidatesTokenCount": integer,
    "totalTokenCount": integer
  },
  "modelVersion": string
}

| 响应元素 | 说明 |
| --- | --- |
| `modelVersion` | 用于生成的模型和版本。例如：`gemini-2.0-flash-lite-001`。 |
| `text` | 生成的文本。 |
| `finishReason` | 模型停止生成词元的原因。如果为空，则模型尚未停止生成词元。由于回答使用上下文提示，因此无法更改模型停止生成词元的行为。  
-   `FINISH_REASON_STOP`：模型的自然停止点或提供的停止序列。
-   `FINISH_REASON_MAX_TOKENS`：已达到请求中指定的 token 数量上限。
-   `FINISH_REASON_SAFETY`：由于出于安全原因标记了回答，token 生成已停止。请注意，如果内容过滤器阻止输出，则 `Candidate.content` 为空。
-   `FINISH_REASON_RECITATION`：由于回答因未经授权的引用而进行标记，因此 token 生成操作已停止。
-   `FINISH_REASON_BLOCKLIST`：由于回答包含禁用词，因此 token 生成操作已停止。
-   `FINISH_REASON_PROHIBITED_CONTENT`：由于回答因包含禁止的内容（例如儿童性虐待内容 \[CSAM\]）而被标记，因此 token 生成操作已停止。
-   `FINISH_REASON_IMAGE_PROHIBITED_CONTENT`：由于提示中提供的图片因包含禁止的内容而被标记，因此 token 生成操作已停止。
-   `FINISH_REASON_NO_IMAGE`：由于提示中本应包含图片，但实际上并未提供，因此 token 生成操作已停止。
-   `FINISH_REASON_SPII`：由于回答因敏感的个人身份信息 (SPII) 而被标记，因此 token 生成操作已停止。
-   `FINISH_REASON_MALFORMED_FUNCTION_CALL`：候选项因格式错误和无法解析的函数调用而被屏蔽。
-   `FINISH_REASON_OTHER`：停止 token 的所有其他原因
-   `FINISH_REASON_UNSPECIFIED`：未指定完成原因。

 |
| `category` | 要为其配置阈值的安全类别。可接受的值包括：

**点击即可展开安全类别**

-   `HARM_CATEGORY_SEXUALLY_EXPLICIT`
-   `HARM_CATEGORY_HATE_SPEECH`
-   `HARM_CATEGORY_HARASSMENT`
-   `HARM_CATEGORY_DANGEROUS_CONTENT`

 |
| `probability` | 内容中的有害概率级别。  

-   `HARM_PROBABILITY_UNSPECIFIED`
-   `NEGLIGIBLE`
-   `LOW`
-   `MEDIUM`
-   `HIGH`

 |
| `blocked` | 一个与安全属性关联的布尔值标志，用于指示模型的输入或输出是否被阻止。 |
| `startIndex` | 一个整数，用于指定引用在 `content` 中的起始位置。 `startIndex` 以字节为单位，根据以 UTF-8 编码的响应计算得出。 |
| `endIndex` | 一个整数，用于指定引用在 `content` 中的结束位置。 `endIndex` 以字节为单位，根据以 UTF-8 编码的响应计算得出。 |
| `url` | 引用来源的网址。网址来源的示例可能是新闻网站或 GitHub 代码库。 |
| `title` | 引用来源的标题。来源标题的示例可能是新闻报道或书籍标题。 |
| `license` | 与引用关联的许可。 |
| `publicationDate` | 引用的发布日期。其有效格式为 `YYYY`、`YYYY-MM`、`YYYY-MM-DD`。 |
| `avgLogprobs` | 候选项的平均对数概率。 |
| `logprobsResult` | 返回每个步骤中排名靠前的候选 token (`topCandidates`) 和实际选择的 token (`chosenCandidates`)。 |
| `token` | 生成式 AI 模型会将文本数据细分为 token 以进行处理，token 可以是字符、字词或短语。 |
| `logProbability` | 表示模型对特定 token 的置信度的对数概率值。 |
| `promptTokenCount` | 请求中的词元数量。 |
| `candidatesTokenCount` | 响应中的词元数量。 |
| `totalTokenCount` | 请求和响应中的词元数量。 |

**注意**：出于结算目的，Gemini 3 Pro 及更高版本的模型在处理文档输入内容时所消耗的 token 会计为图片 token。

## 示例

### 文本生成

根据文本输入生成文本回答。

[Gen AI SDK for Python](#gen-ai-sdk-for-python) [Python (OpenAI)](#python-openai)[Go](#go) 更多

[](https://shell.cloud.google.com/cloudshell/editor?show=ide&cloudshell_git_repo=https://github.com/GoogleCloudPlatform/python-docs-samples&cloudshell_open_in_editor=genai/text_generation/textgen_with_txt.py)

查看更多代码操作。

[在 GitHub 上查看](https://github.com/GoogleCloudPlatform/python-docs-samples/blob/HEAD/genai/text_generation/textgen_with_txt.py)

浅色代码主题背景

深色代码主题背景

发送反馈

```
from google import genai
from google.genai.types import HttpOptions

client = genai.Client(http_options=HttpOptions(api_version="v1"))
response = client.models.generate_content(
    model="gemini-2.5-flash",
    contents="How does AI work?",
)
print(response.text)
# Example response:
# Okay, let's break down how AI works. It's a broad field, so I'll focus on the ...
#
# Here's a simplified overview:
# ...
```

您可以使用 OpenAI 库调用 Inference API。如需了解详情，请参阅[使用 OpenAI 库调用 Vertex AI 模型](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/call-vertex-using-openai-library?hl=zh-cn)。

```
from google.auth import default
import google.auth.transport.requests

import openai

# TODO(developer): Update and un-comment below lines
# project_id = "PROJECT_ID"
# location = "us-central1"

# Programmatically get an access token
credentials, _ = default(scopes=["https://www.googleapis.com/auth/cloud-platform"])
credentials.refresh(google.auth.transport.requests.Request())

# OpenAI Client
client = openai.OpenAI(
    base_url=f"https://{location}-aiplatform.googleapis.com/v1/projects/{project_id}/locations/{location}/endpoints/openapi",
    api_key=credentials.token,
)

response = client.chat.completions.create(
    model="google/gemini-2.0-flash-001",
    messages=[{"role": "user", "content": "Why is the sky blue?"}],
)

print(response)
```

```
import (
	"context"
	"fmt"
	"io"

	"google.golang.org/genai"
)

// generateWithText shows how to generate text using a text prompt.
func generateWithText(w io.Writer) error {
	ctx := context.Background()

	client, err := genai.NewClient(ctx, &genai.ClientConfig{
		HTTPOptions: genai.HTTPOptions{APIVersion: "v1"},
	})
	if err != nil {
		return fmt.Errorf("failed to create genai client: %w", err)
	}

	resp, err := client.Models.GenerateContent(ctx,
		"gemini-2.5-flash",
		genai.Text("How does AI work?"),
		nil,
	)
	if err != nil {
		return fmt.Errorf("failed to generate content: %w", err)
	}

	respText := resp.Text()

	fmt.Fprintln(w, respText)
	// Example response:
	// That's a great question! Understanding how AI works can feel like ...
	// ...
	// **1. The Foundation: Data and Algorithms**
	// ...

	return nil
}
```

### 使用多模态提示

根据多模态输入（例如文本和图片）生成文本回答。

[Gen AI SDK for Python](#gen-ai-sdk-for-python) [Python (OpenAI)](#python-openai)[Go](#go) 更多

[](https://shell.cloud.google.com/cloudshell/editor?show=ide&cloudshell_git_repo=https://github.com/GoogleCloudPlatform/python-docs-samples&cloudshell_open_in_editor=genai/text_generation/textgen_with_txt_img.py)

查看更多代码操作。

[在 GitHub 上查看](https://github.com/GoogleCloudPlatform/python-docs-samples/blob/HEAD/genai/text_generation/textgen_with_txt_img.py)

浅色代码主题背景

深色代码主题背景

发送反馈

```
from google import genai
from google.genai.types import HttpOptions, Part

client = genai.Client(http_options=HttpOptions(api_version="v1"))
response = client.models.generate_content(
    model="gemini-2.5-flash",
    contents=[
        "What is shown in this image?",
        Part.from_uri(
            file_uri="gs://cloud-samples-data/generative-ai/image/scones.jpg",
            mime_type="image/jpeg",
        ),
    ],
)
print(response.text)
# Example response:
# The image shows a flat lay of blueberry scones arranged on parchment paper. There are ...
```

您可以使用 OpenAI 库调用 Inference API。如需了解详情，请参阅[使用 OpenAI 库调用 Vertex AI 模型](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/call-vertex-using-openai-library?hl=zh-cn)。

```

from google.auth import default
import google.auth.transport.requests

import openai

# TODO(developer): Update and un-comment below lines
# project_id = "PROJECT_ID"
# location = "us-central1"

# Programmatically get an access token
credentials, _ = default(scopes=["https://www.googleapis.com/auth/cloud-platform"])
credentials.refresh(google.auth.transport.requests.Request())

# OpenAI Client
client = openai.OpenAI(
    base_url=f"https://{location}-aiplatform.googleapis.com/v1/projects/{project_id}/locations/{location}/endpoints/openapi",
    api_key=credentials.token,
)

response = client.chat.completions.create(
    model="google/gemini-2.0-flash-001",
    messages=[
        {
            "role": "user",
            "content": [
                {"type": "text", "text": "Describe the following image:"},
                {
                    "type": "image_url",
                    "image_url": "gs://cloud-samples-data/generative-ai/image/scones.jpg",
                },
            ],
        }
    ],
)

print(response)
```

```
import (
	"context"
	"fmt"
	"io"

	genai "google.golang.org/genai"
)

// generateWithTextImage shows how to generate text using both text and image input
func generateWithTextImage(w io.Writer) error {
	ctx := context.Background()

	client, err := genai.NewClient(ctx, &genai.ClientConfig{
		HTTPOptions: genai.HTTPOptions{APIVersion: "v1"},
	})
	if err != nil {
		return fmt.Errorf("failed to create genai client: %w", err)
	}

	modelName := "gemini-2.5-flash"
	contents := []*genai.Content{
		{Parts: []*genai.Part{
			{Text: "What is shown in this image?"},
			{FileData: &genai.FileData{
				// Image source: https://storage.googleapis.com/cloud-samples-data/generative-ai/image/scones.jpg
				FileURI:  "gs://cloud-samples-data/generative-ai/image/scones.jpg",
				MIMEType: "image/jpeg",
			}},
		},
			Role: "user"},
	}

	resp, err := client.Models.GenerateContent(ctx, modelName, contents, nil)
	if err != nil {
		return fmt.Errorf("failed to generate content: %w", err)
	}

	respText := resp.Text()

	fmt.Fprintln(w, respText)

	// Example response:
	// The image shows an overhead shot of a rustic, artistic arrangement on a surface that ...

	return nil
}
```

### 流式传输文本回答

根据文本输入生成流式传输模型回答。

[Gen AI SDK for Python](#gen-ai-sdk-for-python) [Python (OpenAI)](#python-openai)[Go](#go) 更多

[](https://shell.cloud.google.com/cloudshell/editor?show=ide&cloudshell_git_repo=https://github.com/GoogleCloudPlatform/python-docs-samples&cloudshell_open_in_editor=genai/text_generation/textgen_with_txt_stream.py)

查看更多代码操作。

[在 GitHub 上查看](https://github.com/GoogleCloudPlatform/python-docs-samples/blob/HEAD/genai/text_generation/textgen_with_txt_stream.py)

浅色代码主题背景

深色代码主题背景

发送反馈

```
from google import genai
from google.genai.types import HttpOptions

client = genai.Client(http_options=HttpOptions(api_version="v1"))

for chunk in client.models.generate_content_stream(
    model="gemini-2.5-flash",
    contents="Why is the sky blue?",
):
    print(chunk.text, end="")
# Example response:
# The
#  sky appears blue due to a phenomenon called **Rayleigh scattering**. Here's
#  a breakdown of why:
# ...
```

您可以使用 OpenAI 库调用 Inference API。如需了解详情，请参阅[使用 OpenAI 库调用 Vertex AI 模型](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/call-vertex-using-openai-library?hl=zh-cn)。

```
from google.auth import default
import google.auth.transport.requests

import openai

# TODO(developer): Update and un-comment below lines
# project_id = "PROJECT_ID"
# location = "us-central1"

# Programmatically get an access token
credentials, _ = default(scopes=["https://www.googleapis.com/auth/cloud-platform"])
credentials.refresh(google.auth.transport.requests.Request())

# OpenAI Client
client = openai.OpenAI(
    base_url=f"https://{location}-aiplatform.googleapis.com/v1/projects/{project_id}/locations/{location}/endpoints/openapi",
    api_key=credentials.token,
)

response = client.chat.completions.create(
    model="google/gemini-2.0-flash-001",
    messages=[{"role": "user", "content": "Why is the sky blue?"}],
    stream=True,
)
for chunk in response:
    print(chunk)
```

```
import (
	"context"
	"fmt"
	"io"

	genai "google.golang.org/genai"
)

// generateWithTextStream shows how to generate text stream using a text prompt.
func generateWithTextStream(w io.Writer) error {
	ctx := context.Background()

	client, err := genai.NewClient(ctx, &genai.ClientConfig{
		HTTPOptions: genai.HTTPOptions{APIVersion: "v1"},
	})
	if err != nil {
		return fmt.Errorf("failed to create genai client: %w", err)
	}

	modelName := "gemini-2.5-flash"
	contents := genai.Text("Why is the sky blue?")

	for resp, err := range client.Models.GenerateContentStream(ctx, modelName, contents, nil) {
		if err != nil {
			return fmt.Errorf("failed to generate content: %w", err)
		}

		chunk := resp.Text()

		fmt.Fprintln(w, chunk)
	}

	// Example response:
	// The
	//  sky is blue
	//  because of a phenomenon called **Rayleigh scattering**. Here's the breakdown:
	// ...

	return nil
}
```

## 模型版本

如需使用[自动更新版本](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/learn/model-versioning?hl=zh-cn#auto-updated-version)，请指定不含尾随版本号的模型名称，例如 `gemini-2.0-flash`，而不是 `gemini-2.0-flash-001`。

如需了解详情，请参阅 [Gemini 模型版本和生命周期](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/learn/model-versioning?hl=zh-cn#gemini-model-versions)。

## 后续步骤

-   详细了解 [Vertex AI 中的 Gemini API](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/model-reference/gemini?hl=zh-cn)。
-   详细了解[函数调用](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/function-calling?hl=zh-cn)。
-   详细了解 [Gemini 模型的接地回答](https://docs.cloud.google.com/vertex-ai/generative-ai/docs/multimodal/ground-gemini?hl=zh-cn)。

该内容对您有帮助吗？

发送反馈