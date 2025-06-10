- 文档首页
/实时音视频/实时对话式 AI/体验进阶/实时对话式 AI 字幕

实时对话式 AI 字幕

最近更新时间：2025.05.29 11:18:34首次发布时间：2024.09.03 11:03:15

[我的收藏](https://www.volcengine.com/docs/favorite)

有用

无用

在进行实时对话式 AI 场景下，你可以通过字幕功能，实时收到真人用户和智能体语音对话对应的文本内容，可用于应用终端实时显示字幕，保存对话记录用于分析、根据字幕返回时机手动触发新一轮对话等场景。  
通过服务端和客户端均可实现该功能，你可根据字幕的使用场景选择对应的方式，如你选择在应用终端实时显示字幕，建议使用客户端实现该功能。

## 应用场景

|场景|描述|
|---|---|
|实时显示字幕|将真人用户和智能体的语音实时转为文字，并在应用终端界面上展示，提升用户理解和参与度。|
|业务存储分析|将真人用户和智能体的对话文本内容记录并存储下来，用于后续的业务数据分析、服务质量监控或模型优化。|
|根据字幕返回时机手动触发新一轮对话|利用字幕返回的特定状态（如整句话结束）作为信号，手动触发下一轮对话开启，实现更灵活的交互逻辑。|

## 前提条件

你已参考[方案集成](https://www.volcengine.com/docs/6348/1310560) 构建一个完整的 AI 应用。

## 计费说明

该功能不额外收费，该场景计费项参看[实时对话式 AI 计费](https://www.volcengine.com/docs/6348/1392584)。

## 客户端实现

你可按照以下步骤实现该场景下字幕功能：  
步骤 1：开启字幕功能。  
步骤 2：对收到的字幕结果进行解析。

### 步骤 1：开启字幕功能

你需要在调用 [StartVoiceChat](https://www.volcengine.com/docs/6348/1558163) 接口开启智能体任务前，通过 `Config.SubtitleConfig` 结构配置以下字段开启客户端接收字幕功能和智能体字幕回调是否对齐时间戳功能：

|配置参数|说明|
|---|---|
|`DisableRTSSubtitle`|设置为 `false`，表示开启房间内客户端字幕回调功能。|
|`SubtitleMode`|- 取值为 `0` 时，表示对齐音频时间戳。该模式下，智能体输出字幕返回的是 TTS 模块转义后的字幕，与智能体朗读的时间戳一一对齐。但注意该字幕结果经过转写和处理，表情等符号可能无法显示。<br>- 取值为 `1` 时，表示不对齐音频时间戳。该模式下，智能体输出字幕返回的是 LLM 模块转义后的字幕，未经过 TTS 模块处理不带时间戳，但该模式下字幕生成速度更快。|

你可以参考以下示例代码进行请求：

```JSON
POST https://rtc.volcengineapi.com?Action=StartVoiceChat&Version=2024-12-01
{
    "AppId": "661e****543cf",
    "RoomId": "Room1",
    "TaskId": "task1",
    "Config": {
        "ASRConfig": {
            "Provider": "volcano",
            "ProviderParams": {
                "Mode": "bigmodel",
                "AppId": "93****21",
                "AccessToken": "MOaOa*****HA4h5B",
                "ApiResourceId": "volc.bigasr.sauc.duration",
                "StreamMode": 0
            }
        },
        "TTSConfig": {
            "Provider": "volcano_bidirection",
            "ProviderParams": {
                "app": {
                    "appid": "94****11",
                    "token": "OaO****ws1"
                },
                "audio": {
                    "voice_type": "zh_male_qingshuangnanda_mars_bigtts",
                    "speech_rate": 0,
                    "pitch_rate": 0
                },
                "ResourceId": "volc.service_type.10029"
            }
        },
        "LLMConfig": {
            "Mode": "ArkV3",
            "EndPointId": "epid****212",
            "MaxTokens": 1024,
            "Temperature": 0.1,
            "TopP": 0.3,
            "SystemMessages": [
                "你是小宁，性格幽默又善解人意。你在表达时需简明扼要，有自己的观点。"
            ],
            "UserPrompts": [
                {
                    "Role": "user",
                    "Content": "你好"
                },
                {
                    "Role": "assistant",
                    "Content": "有什么可以帮到你的？"
                }
            ],
            "HistoryLength": 3
        },
        "SubtitleConfig": {
            "DisableRTSSubtitle": false,
            "SubtitleMode": 0
        }
    },
    "AgentConfig": {
        "TargetUserId": [
            "user1"
        ],
        "WelcomeMessage": "Hello",
        "UserId": "BotName001"
    }
}
```

配置完成后，在真人用户与智能体对话期间，你可通过 [onRoomBinaryMessageReceived](https://www.volcengine.com/docs/6348/70081#IRTCRoomEventHandler-onroombinarymessagereceived) （硬件场景下使用`on_message_received`）回调接收字幕结果。该回调中的 `message` 字段中的内容为字幕结果，格式为二进制，使用前需解析。

### 步骤 2：解析字幕结果

收到的字幕结果为二进制，你需要阅读下文了解其结构进行解析。  
字幕回调格式如下：

|参数名|类型|描述|
|---|---|---|
|uid|String|消息发送者 ID。|
|message|String|二进制消息内容。与服务端返回二进制消息格式相同，详细参看[二进制消息格式](https://www.volcengine.com/docs/6348/1337284?s=g#binary)。|

  
二进制消息格式如下：  
![Image](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_b4680825ac48a324a261a993f0e95433.jpg)

|参数名|类型|描述|
|---|---|---|
|magic number|binary|消息格式，固定为 `subv`。|
|length|binary|字幕消息长度，单位为 bytes。存放方式为大端序。|
|subtitle_message|binary|字幕消息详细信息。格式参看[subtitle_message 格式](https://www.volcengine.com/docs/6348/1337284?s=g#subtitle1)。|

  
subtitle_message 格式：

|参数名|类型|描述|
|---|---|---|
|type|String|消息格式，固定为 `subtitle`，表示消息类型为字幕。|
|data|[data](https://www.volcengine.com/docs/6348/1337284?s=g#data)|字幕详细信息，包含字幕的文本、语言、说话人 ID 等具体信息。|

  
data

|参数名|类型|描述|
|---|---|---|
|text|String|字幕文本。|
|language|String|字幕语言。|
|userId|String|字幕来源者 ID。若字幕来源为真人用户，则该值为真人用户 UserId。若来源为智能体，则该值为智能体 UserId。|
|sequence|Int|字幕序号。|
|definite|Boolean|字幕是否为完整的分句。<br><br>- true：是。<br>- false：否。|
|paragraph|Boolean|字幕是否为完整的一句话。<br><br>- true：是。<br>- false：否。|

subtitle_message 的示例如下：

```JSON
{
"type": "subtitle",
"data" :[{
    "text": "上海天气炎热。气温为"
    "language": "zh"
    "userId": "bot1",
    "sequence":1,
    "definite":false,
    "paragraph":false
}]
}
{
"type": "subtitle",
"data" :[{
    "text": "上海天气炎热。气温为 30 摄氏度。"
    "language": "zh"
    "userId": "bot1",
    "sequence":2,
    "definite":true,
    "paragraph":false
}]
}
```

你可以参考以下示例代码对回调信息中的`message`内容进行解析。

```C++
//定义结构体
struct SubtitleMsgData {
    bool definite;
    std::string language;
    bool paragraph;
    int sequence;
    std::string text;
    std::string userId;
};

//回调事件
void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
    std::string subtitles;
    bool ret = Unpack(message, size, subtitles);
    if(ret) {
        ParseData(subtitles);
    }
}

//拆包校验
bool Unpack(const uint8_t *message, int size, std::string& subtitles) {
    int kSubtitleHeaderSize = 8;
    if(size < kSubtitleHeaderSize) { 
        return false;
    }
    // magic number "subv"
    if(static_cast<uint32_t>((static_cast<uint32_t>(message[0]) << 24) 
           | (static_cast<uint32_t>(message[1]) << 16) 
           | (static_cast<uint32_t>(message[2]) << 8) 
           | static_cast<uint32_t>(message[3])) != 0x73756276U) {
        return false;
    }
    
    uint32_t length = static_cast<uint32_t>((static_cast<uint32_t>(message[4]) << 24) 
           | (static_cast<uint32_t>(message[5]) << 16) 
           | (static_cast<uint32_t>(message[6]) << 8) 
           | static_cast<uint32_t>(message[7]));
           
    if(size - kSubtitleHeaderSize != length) {
        return false;
    }

    if(length) {
        subtitles.assign((char*)message + kSubtitleHeaderSize, length);
    } else {
        subtitles = "";
    }
    return true;
}

//解析
void ParseData(const std::string& msg) {
    // 解析 JSON 字符串
    nlohmann::json json_data = nlohmann::json::parse(msg);
    // 存储解析后的数据
    std::vector<SubtitleMsgData> subtitles;
    // 遍历 JSON 数据并填充结构体
    for (const auto& item : json_data["data"]) {
        SubtitleMsgData subData;
        subData.definite = item["definite"];
        subData.language = item["language"];
        subData.paragraph = item["paragraph"];
        subData.sequence = item["sequence"];
        subData.text = item["text"];
        subData.userId = item["userId"];
        subtitles.push_back(subData);
    }
}
```

## 服务端实现

你可按照以下步骤实现该场景下字幕功能：  
步骤 1：开启字幕功能。  
步骤 2：对收到的字幕结果进行解析。

### 步骤 1：开启字幕功能

你需要在调用 [StartVoiceChat](https://www.volcengine.com/docs/6348/1558163) 接口开启智能体任务前，通过 `Config.SubtitleConfig` 结构配置以下字段开启服务端接收字幕功能和智能体字幕回调是否对齐时间戳功能：

|配置参数|说明|
|---|---|
|`ServerMessageUrl`|业务服务端接收字幕结果的 URL 地址。你指定的 URL 地址将收到来自 RTC 服务器的 HTTP(S) POST 请求发送的字幕结果，格式为二进制，使用前需解析。|
|`ServerMessageSignature`|鉴权签名。你可传入该鉴权字段，在收到字幕结果后，与结果中的 `signature` 字段的值进行对比，用于鉴权，保证消息的可靠性与安全性。|
|`SubtitleMode`|- 取值为 `0` 时，表示对齐音频时间戳。该模式下，返回的是 TTS 模块生成的智能体字幕，与智能体朗读的时间戳一一对齐。但注意该字幕结果经过转写和处理，表情等符号可能无法显示。<br>- 取值为 `1` 时，表示不对齐音频时间戳。该模式下，返回的是 LLM 模块生成的智能体回复内容，未经过 TTS 模块处理不带时间戳，但该模式下字幕生成速度更快。|

你可以参考以下示例代码进行请求：

```JSON
POST https://rtc.volcengineapi.com?Action=StartVoiceChat&Version=2024-12-01
{
    "AppId": "661e****543cf",
    "RoomId": "Room1",
    "TaskId": "task1",
    "Config": {
        "ASRConfig": {
            "Provider": "volcano",
            "ProviderParams": {
                "Mode": "bigmodel",
                "AppId": "93****21",
                "AccessToken": "MOaOa*****HA4h5B",
                "ApiResourceId": "volc.bigasr.sauc.duration",
                "StreamMode": 0
            }
        },
        "TTSConfig": {
            "Provider": "volcano_bidirection",
            "ProviderParams": {
                "app": {
                    "appid": "94****11",
                    "token": "OaO****ws1"
                },
                "audio": {
                    "voice_type": "zh_male_qingshuangnanda_mars_bigtts",
                    "speech_rate": 0,
                    "pitch_rate": 0
                },
                "ResourceId": "volc.service_type.10029"
            }
        },
        "LLMConfig": {
            "Mode": "ArkV3",
            "EndPointId": "epid****212",
            "MaxTokens": 1024,
            "Temperature": 0.1,
            "TopP": 0.3,
            "SystemMessages": [
                "你是小宁，性格幽默又善解人意。你在表达时需简明扼要，有自己的观点。"
            ],
            "UserPrompts": [
                {
                    "Role": "user",
                    "Content": "你好"
                },
                {
                    "Role": "assistant",
                    "Content": "有什么可以帮到你的？"
                }
            ],
            "HistoryLength": 3
        },
        "SubtitleConfig": {
            "ServerMessageUrl": "https://example-domain.com/vertc/subtitle",
            "ServerMessageSignature": "b46ab****ad6a"
        }
    },
    "AgentConfig": {
        "TargetUserId": [
            "user1"
        ],
        "WelcomeMessage": "Hello",
        "UserId": "BotName001"
    }
}
```

你指定的 URL 地址将收到来自 RTC 服务器的 HTTP(S) POST 请求发送的字幕结果，格式为二进制，使用前需解析。

### 步骤 2：解析字幕结果

你指定的 URL 地址将收到来自 RTC 服务器的 HTTP(S) POST 请求发送的字幕结果，格式为二进制，你需要阅读下文了解其结构进行解析。

收到的 HTTP(S) POST 请求的内容格式如下：

|参数名|类型|描述|
|---|---|---|
|message|String|Base 64 编码的二进制消息内容。格式参看[二进制消息格式](https://www.volcengine.com/docs/6348/1337284?s=g#binary2)。|
|signature|String|鉴权签名。可与`StartVoiceChat`接口中传入的`ServerMessageSignature`字段值进行对比以进行鉴权验证。|

  
二进制消息格式如下：  
![Image](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_b4680825ac48a324a261a993f0e95433.jpg)

|参数名|类型|描述|
|---|---|---|
|magic number|binary|消息格式，固定为 `subv`。|
|length|binary|字幕消息长度，单位为 bytes。存放方式为大端序。|
|subtitle_message|binary|字幕消息详细信息。格式参看[subtitle_message 格式](https://www.volcengine.com/docs/6348/1337284?s=g#subtitle1)。|

  
subtitle_message 格式：

|参数名|类型|描述|
|---|---|---|
|type|String|消息格式，固定为 `subtitle`，表示消息类型为字幕。|
|data|[data](https://www.volcengine.com/docs/6348/1337284?s=g#data2)|字幕详细信息，包含字幕的文本、语言、说话人 ID 等具体信息。|

  
data

|参数名|类型|描述|
|---|---|---|
|text|String|字幕文本。|
|language|String|字幕语言。|
|userId|String|字幕来源者 ID。若字幕来源为真人用户，则该值为真人用户 UserId。若来源为智能体，则该值为智能体 UserId。|
|sequence|Int|字幕序号。|
|definite|Boolean|字幕是否为完整的分句。<br><br>- true：是。<br>- false：否。|
|paragraph|Boolean|字幕是否为完整的一句话。<br><br>- true：是。<br>- false：否。|

subtitle_message 的示例如下：

```JSON
{
"type": "subtitle",
"data" :[{
    "text": "上海天气炎热。气温为"
    "language": "zh"
    "userId": "bot1",
    "sequence":1,
    "definite":false,
    "paragraph":false
}]
}
{
"type": "subtitle",
"data" :[{
    "text": "上海天气炎热。气温为 30 摄氏度。"
    "language": "zh"
    "userId": "bot1",
    "sequence":2,
    "definite":true,
    "paragraph":false
}]
}
```

你可以参考以下示例代码对回调信息中的`message`内容进行解析。

```Go
const (
    subtitleHeader   = "subv"
    exampleSignature = "example_signature"
)

type RtsMessage struct {
    Message   string `json:"message"`
    Signature string `json:"signature"`
}

type Subv struct {
    Type string `json:"type"`
    Data []Data `json:"data"`
}

type Data struct {
    Definite  bool   `json:"definite"`
    Paragraph bool   `json:"paragraph"`
    Language  string `json:"language"`
    Sequence  int    `json:"sequence"`
    Text      string `json:"text"`
    UserID    string `json:"userId"`
}

func HandleSubtitle(c *gin.Context) {
    msg := &RtsMessage{}
    if err := c.BindJSON(&msg); err != nil {
       fmt.Printf("BindJson failed,err:%v\n", err)
       return
    }
    if msg.Signature != exampleSignature {
       fmt.Printf("Signature not match\n")
       return
    }

    subv, err := Unpack(msg.Message)
    if err != nil {
       fmt.Printf("Unpack failed,err:%v\n", err)
       return
    }

    fmt.Println(subv)

    //业务逻辑

    c.String(200, "ok")
}

func Unpack(msg string) (*Subv, error) {
    data, err := base64.StdEncoding.DecodeString(msg)
    if err != nil {
       return nil, fmt.Errorf("DecodeString failed,err:%v", err)
    }
    if len(data) < 8 {
       return nil, fmt.Errorf("Data invalid")
    }
    dataHeader := string(data[:4])
    if dataHeader != subtitleHeader {
       return nil, fmt.Errorf("Header not match")
    }
    dataSize := binary.BigEndian.Uint32(data[4:8])
    if dataSize+8 != uint32(len(data)) {
       return nil, fmt.Errorf("Size not match")
    }

    subData := data[8:]
    subv := &Subv{}
    err = json.Unmarshal(subData, subv)
    if err != nil {
       return nil, fmt.Errorf("Unmarshal failed,err:%v\n", err)
    }
    return subv, nil
}

func main() {

    r := gin.Default()
    r.POST("/example_domain/vertc/subtitle", HandleSubtitle)
    r.Run()
}
```

## 字幕使用建议

1. 在客户端回调和服务端回调字幕中，真人用户和智能体的字幕来源和特点不同：

||真人用户|智能体|
|---|---|---|
|客户端回调|- 来源：ASR 模块语音识别内容<br>- 特点：流式返回说话内容。例如：用户说话内容为：”你好。查询一下上海的天气。“返回效果如下：“你好。”“你好，查询”“你好。查询一下上海的天气”<br>- 说话过程中 ：<br>    - `definite`：始终为 `false`，表示一整句还未结束。<br>    - `paragraph`：始终为 `false` ，表示一整句还未结束。<br>- 说话结束时 ：<br>    - `definite` ：为 `true` ，表示一整句已结束。<br>    - `paragraph` ：为 `true` ，表示一整句已结束。|- 来源：根据 `SubtitleMode` 模式的不同，来源为 LLM 模块生成内容或 TTS 模块朗读内容。<br>- 特点 ：<br>    - 流式返回说话内容。存在分句和整句的区别。例如：分句1：上海天气炎热。分句2：气温为 30 摄氏度。整句：上海天气炎热。气温为 30 摄氏度。<br>    - 当新的分句开始时，字幕不会显示上一个已结束的分句。<br>- 说话过程中：<br>    - `definite` ：可能为 `false` （表示当前分句尚未结束）或 `true` （表示当前分句已结束，但一整句话还未结束）。<br>    - `paragraph`：始终为 `false` 。表示一整句还未结束。<br>- 说话结束时 ：<br>    - `definite` ：为 `true` ，表示分句已结束。<br>    - `paragraph` ：为 `true` ，表示一整句已结束。|
|服务端回调|- 来源：ASR 模块语音识别内容。<br>- 特点 ：识别到一个完整分句后返回。且当新的分句开始时，字幕不会显示上一个已结束的分句。例如：用户说话内容为：”你好。查询一下上海的天气。“返回效果如下：“你好。”“查询一下上海的天气”<br>- 说话过程中 ：<br>    - `definite`：始终为 `true`，表示分句已结束。<br>    - `paragraph`：始终为 `false` ，表示一整句还未结束。<br>- 说话结束时 ：<br>    - `definite` ：为 `true` ，表示分句已结束。<br>    - `paragraph` ：为 `true` ，表示一整句已结束。|- 来源：根据 `SubtitleMode` 模式的不同，来源为 LLM 模块生成内容或 TTS 模块朗读内容。<br>- 特点 ：识别到一个完整分句后返回。且当新的分句开始时，字幕不会显示上一个已结束的分句。例如：用户说话内容为：”上海天气炎热。气温为 30 摄氏度。“返回效果如下：“上海天气炎热。”“气温为 30 摄氏度。”<br>- 说话过程中 ：<br>    - `definite`：始终为 `true`，表示分句已结束。<br>    - `paragraph`：始终为 `false` ，表示一整句还未结束。<br>- 说话结束时 ：<br>    - `definite` ：为 `true` ，表示分句已结束。<br>    - `paragraph` ：为 `true` ，表示一整句已结束。|

2. 在不同的使用场景下，你可以根据 `definite`、 `paragraph` 和 `sequence` 字段来决定如何处理字幕。
    - 实时显示字幕  
        如果 `paragraph`=`false`，`definite`=`false`，用序号大的字幕覆盖序号小的。  
        如果 `paragraph`=`false`，`definite`=`true`，重新开始新的一句话，覆盖前一句话。  
        如果 `paragraph`=`true`，则说明一整句话结束。此时如果继续解析显示字幕，字幕会重复显示。
    - 存储字幕  
        如果仅为了存储字幕，可只保存 `definite`=`true` 且 `paragraph`=`true` 的字幕，减少存储的数据量，并确保保存的字幕是完整的。

## FAQ

Q1：是否支持字幕在用户和智能体说话之前就返回给业务端？  
A1：不支持。  
Q2：字幕是否支持接收图片  
A2：不支持。  
Q3：微信小程序端是否支持字幕功能？  
A3：暂不支持通过微信小程序客户端接收，可通过服务端接收。  
Q4：收到的字幕与实际内容相比有很多错误同音字。  
A4：不同模型对于同音字的识别结果不同。你可参看[如何提升语音识别准确性？](https://www.volcengine.com/docs/6348/1563620)提升字幕准确度。