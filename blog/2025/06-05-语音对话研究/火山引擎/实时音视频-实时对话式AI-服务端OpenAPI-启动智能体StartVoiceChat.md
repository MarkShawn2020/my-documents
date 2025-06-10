- 文档首页
/实时音视频/实时对话式 AI/服务端 OpenAPI/启动智能体 StartVoiceChat

启动智能体 StartVoiceChat

最近更新时间：2025.06.03 10:43:54首次发布时间：2025.05.15 13:15:32

[我的收藏](https://www.volcengine.com/docs/favorite)

有用

无用

在实时音视频场景中，你可以调用此接口在房间内引入一个智能体进行 AI 实时交互。​

RTC 提供语音识别（ASR）、语音合成（TTS）、大模型（LLM） 一站式接入，同时也支持通道服务，使用此接口灵活接入第三方大模型/Agent。​

注意事项​

- 请求频率：单账号下 QPS 不得超过 60。​

- 请求接入地址：仅支持 rtc.volcengineapi.com。​

- 调用该接口启动智能体任务后，若真人用户退出房间，180 s 后该智能体任务会自动停止，但该 180s 内仍会计费。为避免不必要的费用，建议真人用户退出房间后，及时调用 [StopVoiceChat](https://www.volcengine.com/docs/6348/1404672) 接口关闭智能体任务。​

前提条件​

调用该接口前，你需要开通语音识别、语音合成和大模型服务并配置相关权限策略，详情请参看[方案集成前置准备](https://www.volcengine.com/docs/6348/1315561)。​

调用接口​

发送 HTTP(S) 请求时，你需要符合火山引擎规范。调用接口的请求结构、公共参数、签名机制、返回结构，参看[调用方法](https://www.volcengine.com/docs/6348/1178320)。​

请求说明​

- 请求方式：POST​

- 请求地址：https://rtc.volcengineapi.com?Action=StartVoiceChat&Version=2024-12-01​

调试​

API Explorer

您可以通过 API Explorer 在线发起调用，无需关注签名生成过程，快速获取调用结果。

[去调试](https://api.volcengine.com/api-explorer/debug?action=StartVoiceChat&serviceCode=rtc&version=2024-12-01&groupName=%E6%99%BA%E8%83%BD%E4%BD%93)

​

请求参数​

下表仅列出该接口特有的请求参数和部分公共参数。完整公共请求参数请见[公共参数](https://www.volcengine.com/docs/6348/1178321)。​

Query​

Action String 必选 示例值：StartVoiceChat​

接口名称。当前 API 的名称为 StartVoiceChat。​

​

Version String 必选 示例值：2024-12-01​

接口版本。当前 API 的版本为 2024-12-01。​

​

​

Body​

AppId String 必选 示例值：661e7ae5543cf​

你的音视频应用的唯一标志，参看[创建 RTC 应用](https://www.volcengine.com/docs/6348/69865#%E6%AD%A5%E9%AA%A44%EF%BC%9A%E5%88%9B%E5%BB%BA-rtc-%E5%BA%94%E7%94%A8%EF%BC%8C%E8%8E%B7%E5%8F%96-appid)获取或创建 AppId。​

​

RoomId String 必选 示例值：Room1​

智能体与真人通话的房间 ID，必须与真人用户使用客户端 SDK 进房时使用的 RoomId 保持一致。​

​

TaskId String 必选 示例值：task1​

智能体任务 ID。你需要对每个智能体任务自行定义 TaskId，且在后续进行任务更新和结束时也须使用该 TaskId。参数定义规则参看[参数赋值规范](https://www.volcengine.com/docs/6348/70114)。​

TaskId 是任务的标识，在一个 AppId 的 RoomId 下 TaskId 是唯一的，不同 AppId 或者不同 RoomId 下 TaskId 可以重复，因此 AppId + RoomId + TaskId 是任务的唯一标识，可以用来标识指定 AppId下某个房间内正在运行的任务，从而能在此任务运行中进行更新或者停止此任务。​

​

Config Object 必选 示例值：-​

智能体交互服务配置，包括语音识别（ASR）、语音合成（TTS）、大模型(LLM)、字幕和函数调用（Function Calling）配置。​

ASRConfig Object 必选 示例值：-​

语音识别（ASR）相关配置。​

Provider String 必选 示例值：volcano​

语音识别服务提供商。该参数固定取值：volcano，表示仅支持火山引擎语音识别服务。可使用以下模型：​

- 火山引擎流式语音识别（识别速度更快）​

- 火山引擎流式语音识别大模型（识别准确度更高）​

两者详细差异（如可识别语种、支持的能力等），请参见[流式语音识别](https://www.volcengine.com/docs/6561/109880)和[流式语音识别大模型](https://www.volcengine.com/docs/6561/1354871)。​

​

ProviderParams Object 必选 示例值：-​

服务配置参数。支持服务如下：​

- [火山引擎流式语音识别大模型](https://www.volcengine.com/docs/6348/1558163#c15xHW7pRs)​

- [火山引擎流式语音识别](https://www.volcengine.com/docs/6348/1558163#gNhOQ1AI4r)​

不同服务下，该结构包含字段不同。具体参看如下描述：​

火山引擎流式语音识别大模型​

火山引擎流式语音识别大模型，识别速度稍慢，但识别准确度更高。可识别语种、支持的能力等，请参看[流式语音识别大模型](https://www.volcengine.com/docs/6561/1354871)。​

Mode String 必选 示例值：bigmodel​

模型类型。该参数固定取值：bigmodel，表示火山引擎语音识别大模型。​

​

AppId String 必选 示例值：93****21​

开通火山引擎流式语音识别大模型服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10011?)获取。​

​

AccessToken String 必选 示例值：MOaOaa_VQ6****1B34UHA4h5B​

与开通流式语音识别大模型服务 App ID 对应的 AccessToken，用于身份认证。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10011?)获取。Access Token 查找方式，可参看[如何获取 Token](https://www.volcengine.com/docs/6561/196768#q1%EF%BC%9A%E5%93%AA%E9%87%8C%E5%8F%AF%E4%BB%A5%E8%8E%B7%E5%8F%96%E5%88%B0%E4%BB%A5%E4%B8%8B%E5%8F%82%E6%95%B0appid%EF%BC%8Ccluster%EF%BC%8Ctoken%EF%BC%8Cauthorization-type%EF%BC%8Csecret-key-%EF%BC%9F)。​

​

ApiResourceId String 可选 示例值：volc.bigasr.sauc.duration​

火山引擎流式语音识别大模型服务开通类型：​

- volc.bigasr.sauc.duration：小时版。​

- volc.bigasr.sauc.concurrent：并发版。​

默认值为 volc.bigasr.sauc.duration。​

​

StreamMode Integer 可选 示例值：0​

语音识别输出模式：​

- 0：流式输入流式输出。识别结果会分段、实时地返回。该模式下识别速度更快，适用于实时字幕场景。​

- 1：流式输入非流式输出。即在完整接收并处理完整个语音片段后，一次性返回最终的识别结果。该模式下识别准确率更高，适用于不需要语音打断功能的场景。​

默认值为 0。​

​

context String 可选 示例值："{\"hotwords\": [{\"word\": \"CO2\"},{\"word\": \"雨伞\"},{\"word\": \"鱼\"}]}"​

热词直传（通过 JSON 字符串直接传入）。​

如果某些词汇（比如人名、产品名等）的识别准确率较低，可以其作为热词传入 ASR 模型，提高输入词汇的识别准确率。例如传入"雨伞"热词，发音相似的词会优先识别为“雨伞”。​

大小限制：热词传入最大值为 200 tokens，超出会自动截断。​

​

boosting_table_id String 可选 示例值：26603****1-adad​

热词词表 ID。你需要在[火山语音技术_热词管理](https://console.volcengine.com/auth/login?redirectURI=%2Fspeech%2Fhotword)创建热词词表，并获取热词 ID。​

说明​

执行优先级：热词词表低于热词直传。即如果同时配置了热词直传和热词词表，系统会先执行热词直传，后执行热词词表。​

​

boosting_table_name String 可选 示例值：古诗词列表​

热词词表名称。你需要在[火山语音技术_热词管理](https://console.volcengine.com/auth/login?redirectURI=%2Fspeech%2Fhotword)创建热词词表，并获取热词词表的文件名称。​

说明​

执行优先级：热词词表低于热词直传。即如果同时配置了热词直传和热词词表，系统会先执行热词直传，后执行热词词表。​

​

context_history_length Integer 可选 示例值：0​

上下文轮次。将最近指定轮数会话内容送入流式语音识别大模型，有助于模型理解当前对话的背景，从而提升大模型识别准确性。取值范围为 0、 [1,21)，0 表示不开启该功能。​

​

correct_table_id String 可选 示例值：26603****1-adad​

替换词 ID。将 ASR 识别出的特定词汇替换为预期的标准词汇，可用于纠错、脱敏或别名替换等。比如“智立”替换为“致力”。你需要先在[火山语音技术_替换词管理](https://console.volcengine.com/speech/correctword)创建替换词，并获取替换词 ID。​

说明​

执行优先级：替换词低于热词。即如果一个词同时是热词和替换词的源词，则优先执行热词，再执行替换词。例如，原词为“智立”：​

- 若热词有“致力”，替换词要求“智立→治理”，那最后结果为 “致力”。​

- 若热词有“致力”，替换词要求“致力→治理”，那最后结果为 “治理”。​

​

correct_table_name String 可选 示例值：古诗词​

替换词文件名称。你需要先在[火山语音技术_替换词管理](https://console.volcengine.com/speech/correctword)创建替换词，并获取替换词的文件名称。​

说明​

执行优先级：替换词低于热词。即如果一个词同时是热词和替换词的源词，则优先执行热词，再执行替换词。例如，原词为“智立”：​

- 若热词有“致力”，替换词要求“智立→治理”，最后结果为 “致力”。​

- 若热词有“致力”，替换词要求“致力→治理”，最后结果为 “治理”。​

​

​

火山引擎流式语音识别​

​

​

VADConfig Object 可选 示例值：-​

VAD（语音检测） 配置。​

SilenceTime Integer 可选 示例值：600​

判停时间。房间内真人用户停顿时间若高于该值设定时间，则认为一句话结束。取值范围为 [500，3000)，单位为 ms，默认值为 600。​

​

​

VolumeGain Float 可选 示例值：0.3​

音量增益值。增益值越低，采集音量越低。适当低增益值可减少噪音引起的 ASR 错误识别。默认值为 1.0，推荐值 0.3。​

​

InterruptConfig Object 可选 示例值：-​

语音打断配置。​

说明​

该参数仅当 Config.InterruptMode=0 即开启语音打断模式时生效。​

InterruptSpeechDuration Integer 可选 示例值：500​

自动打断触发阈值。房间内真人用户持续说话时间达到该参数设定值后，智能体自动停止输出。取值范围为0，[200，3000]，单位为 ms，值越大智能体说话越不容易被打断。​

默认值为 0，表示用户发出声音且包含真实语义时即打断智能体输出。​

​

InterruptKeywords String[] 可选 示例值：["停止", "停下"]​

关键词打断。若用户说话内容包含任一传入关键词，智能体则立刻停止输出。​

若配置该参数，只有识别到配置的打断词时才会触发打断，以降低背景环境人声无打断的干扰。使用该参数时，建议 InterruptSpeechDuration 设置为 0，避免自动打断触发阈值过高，导致关键词打断不生效。​

​

​

TurnDetectionMode Integer 可选 示例值：0​

新一轮对话的触发方式。​

- 0：服务端检测到完整的一句话后，自动触发新一轮对话。​

- 1：收到输入结束信令或说话字幕结果后，你自行决定是否触发新一轮会话。​

默认值为 0。该功能使用方法参看[配置对话触发模式](https://www.volcengine.com/docs/6348/1544164)。​

​

​

TTSConfig Object 必选 示例值：-​

语音合成（TTS）相关配置。​

IgnoreBracketText Integer[] 可选 示例值：[1,2]​

过滤大模型返回内容中指定标点符号中的文字后再进行语音合成。你需要在大模型 Prompt 中自行定义哪些内容放在指定标点符号内。具体使用方法参看[过滤指定内容](https://www.volcengine.com/docs/6348/1350596)。​

支持取值及含义如下：​

- 1：中文括号（）​

- 2：英文括号()​

- 3：中文方括号【】​

- 4：英文方括号[]​

- 5：英文花括号{}​

默认值为空，表示不进行过滤。​

​

Provider String 必选 示例值：-​

语音合成服务提供商。使用不同语音合成服务时，取值不同。支持使用的语音合成服务及对应取值如下：​

- volcano （服务自上而下语音生成速度递减，情感表现力递增）​

- 火山引擎流式语音合成​

- 火山引擎语音合成大模型（非流式输入流式输出）​

- 火山引擎声音复刻大模型（非流式输入流式输出）​

- volcano_bidirection（服务自上而下语音生成速度递减，情感表现力递增）​

- 火山引擎语音合成大模型（流式输入流式输出）​

- 火山引擎声音复刻大模型（流式输入流式输出）​

- minimax​

- MiniMax 语音合成​

​

ProviderParams Object 必选 示例值：-​

配置所选的语音合成服务。不同服务下，该结构包含字段不同：​

- [火山引擎语音合成](https://www.volcengine.com/docs/6348/1558163#dmrj1ReHH8)​

- [火山引擎语音合成大模型（流式输入流式输出）](https://www.volcengine.com/docs/6348/1558163#ou3sIH_4Xj)​

- [火山引擎语音合成大模型（非流式输入流式输出）](https://www.volcengine.com/docs/6348/1558163#Oa9E5BGlCj)​

- [火山引擎声音复刻大模型（流式输入流式输出）](https://www.volcengine.com/docs/6348/1558163#BpeLnxEH-6)​

- [火山引擎声音复刻大模型（非流式输入流式输出）](https://www.volcengine.com/docs/6348/1558163#gXn-yWcVT0)​

- [MiniMax 语音合成](https://www.volcengine.com/docs/6348/1558163#xt4MXtOjw-)​

火山引擎语音合成​

app Object 必选 示例值：-​

火山引擎语音合成服务应用配置。​

appid String 必选 示例值：94****11​

开通火山引擎语音合成服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/8?)获取。​

​

cluster String 必选 示例值：volcano_tts​

已开通语音合成服务对应的集群标识（Cluster ID）。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/8?)开通服务后获取。​

​

​

audio Object 必选 示例值：-​

火山引擎语音合成服务音频配置。​

voice_type String 必选 示例值：BV001_streaming​

音色。可登录[语音技术控制台](https://console.volcengine.com/speech/service/8?)购买音色后获取，即 Voice_type。​

​

speed_ratio Float 可选 示例值：1.0​

语速。取值范围为[0.2,3]，默认值为 1.0，通常保留一位小数即可。取值越大，语速越快。​

​

volume_ratio Float 可选 示例值：1.0​

音量。取值范围为 [0.1,3]，默认值为 1.0，通常保留一位小数即可。取值越大，音量越高。​

​

pitch_ratio Float 可选 示例值：1.0​

音高。取值范围为 [0.1,3]，默认值为 1.0，通常保留一位小数即可。取值越大，音调越高。​

​

​

​

火山引擎语音合成大模型（流式输入流式输出）​

app Object 必选 示例值：-​

火山引擎语音合成大模型服务应用配置。​

appid String 必选 示例值：94****11​

开通火山引擎语音合成大模型服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/8?)获取。​

​

token String 必选 示例值：OaO****ws1​

与语音合成大模型服务 App ID 对应的 AccessToken，用于身份认证。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10011?)获取。Access Token 查找方式，可参看[如何获取 Token](https://www.volcengine.com/docs/6561/196768#q1%EF%BC%9A%E5%93%AA%E9%87%8C%E5%8F%AF%E4%BB%A5%E8%8E%B7%E5%8F%96%E5%88%B0%E4%BB%A5%E4%B8%8B%E5%8F%82%E6%95%B0appid%EF%BC%8Ccluster%EF%BC%8Ctoken%EF%BC%8Cauthorization-type%EF%BC%8Csecret-key-%EF%BC%9F)。​

​

​

audio Object 必选 示例值：-​

火山引擎语音合成大模型服务音频配置。​

voice_type String 必选 示例值：BV001_streaming​

已开通音色对应的音色种类（Voice_type）。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10011?)购买音色后获取。​

​

pitch_rate Integer 可选 示例值：0​

音调。取值范围为 [-12,12]。默认值为 0。取值越大，音调越高。​

​

speech_rate Integer 可选 示例值：0​

语速。取值范围为[-50,100]，100 代表 2.0 倍速，-50 代表 0.5 倍速。默认值为 0。取值越大，语速越快。​

​

​

Additions Object 可选 示例值：-​

火山引擎语音合成大模型服务高级配置。​

enable_latex_tn Boolean 可选 示例值：true​

是否播报 Latex 公式。​

- true：播报。 ​

- false：不播报。​

默认值为 false。​

说明​

为 true 时，disable_markdown_filter 也需为 true 才可生效。​

​

disable_markdown_filter Boolean 可选 示例值：true​

是否对 Markdown 格式内容进行过滤。​

- true：过滤。例如，**你好**，会读为“你好”。​

- false：不过滤。例如，**你好**，会读为“星星你好星星”。​

默认值为 false。​

​

enable_language_detector Boolean 可选 示例值：false​

是否自动识别语种。[支持哪些语种？](https://www.volcengine.com/docs/6561/1257543)​

- true：自动识别。​

- false：不自动识别。​

默认值为 false。​

​

​

ResourceId String 必选 示例值：volc.service_type.10029​

调用服务的资源信息 ID，该参数固定取值：volc.service_type.10029；​

​

​

火山引擎语音合成大模型（非流式输入流式输出）​

app Object 必选 示例值：-​

火山引擎语音合成大模型服务应用配置。​

appid String 必选 示例值：94****11​

开通火山引擎语音合成大模型服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10007?)获取。​

​

cluster String 必选 示例值：volcano_tts​

已开通语音合成大模型服务对应的集群标识（Cluster ID）。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10007?)开通服务后获取。​

​

​

audio Object 必选 示例值：-​

火山引擎语音合成大模型服务音频配置。​

voice_type String 必选 示例值：zh_female_meilinvyou_moon_bigtts​

已开通音色对应的音色种类（Voice_type）。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/10007?)购买音色后获取。​

​

pitch_rate Integer 可选 示例值：0​

音调。取值范围为 [-12,12]。默认值为 0。取值越大，音调越高。​

​

speech_rate Integer 可选 示例值：0​

语速。取值范围为[-50,100]，100 代表 2.0 倍速，-50 代表 0.5 倍速。默认值为 0。取值越大，语速越快。​

​

​

​

火山引擎声音复刻大模型（流式输入流式输出）​

app Object 必选 示例值：-​

火山引擎声音复刻大模型服务应用配置。​

appid String 必选 示例值：94****11​

开通火山引擎声音复刻大模型服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)获取。​

​

token String 必选 示例值：OaO****ws1​

与开通声音复刻大模型服务 App ID 对应的 AccessToken，用于身份认证。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)获取。Access Token 查找方式，可参看[如何获取 Token](https://www.volcengine.com/docs/6561/196768#q1%EF%BC%9A%E5%93%AA%E9%87%8C%E5%8F%AF%E4%BB%A5%E8%8E%B7%E5%8F%96%E5%88%B0%E4%BB%A5%E4%B8%8B%E5%8F%82%E6%95%B0appid%EF%BC%8Ccluster%EF%BC%8Ctoken%EF%BC%8Cauthorization-type%EF%BC%8Csecret-key-%EF%BC%9F)。​

​

​

audio Object 必选 示例值：-​

火山引擎声音复刻大模型服务音频配置。​

voice_type String 必选 示例值：S_N****T7k1​

声音复刻声音 ID。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)获取。​

​

speed_ratio Float 可选 示例值：1.0​

语速。取值范围为[0.8,2]，默认值为 1.0，通常保留一位小数即可。取值越大，语速越快。​

​

​

Additions Object 可选 示例值：-​

火山引擎声音复刻大模型服务高级配置。​

enable_latex_tn Boolean 可选 示例值：true​

是否播报 Latex 公式。​

- true：播报。​

- false：不播报。​

默认值为 false。​

说明​

为 true 时，disable_markdown_filter 也需为 true 才可生效。​

​

disable_markdown_filter Boolean 可选 示例值：true​

是否对 Markdown 格式内容进行过滤。​

- true：过滤。例如，**你好**，会读为“你好”。​

- false：不过滤。例如，**你好**，会读为“星星你好星星”。​

默认值为 false。​

​

enable_language_detector Boolean 可选 示例值：false​

是否自动识别语种。[支持哪些语种？](https://www.volcengine.com/docs/6561/133350)​

- true：自动识别。​

- false：不自动识别。​

默认值为 false。​

​

​

ResourceId String 必选 示例值：volc.megatts.default​

调用服务的资源信息 ID，该参数固定取值：volc.megatts.default。​

​

​

火山引擎声音复刻大模型（非流式输入流式输出）​

app Object 必选 示例值：-​

火山引擎声音复刻大模型服务应用配置。​

appid String 必选 示例值：94****11​

开通火山引擎声音复刻大模型服务后获取的 App ID，用于标识应用。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)获取。​

​

cluster String 必选 示例值：volcano_icl​

已开通声音复刻大模型服务对应的集群标识（Cluster ID）。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)开通服务后获取。​

​

​

audio Object 必选 示例值：-​

火山引擎声音复刻大模型服务音频配置。​

voice_type String 必选 示例值：S_N****T7k1​

声音复刻声音 ID。你可登录[语音技术控制台](https://console.volcengine.com/speech/service/9999?)获取。​

​

speed_ratio Float 可选 示例值：1.0​

语速。取值范围为[0.8,2]，默认值为 1.0，通常保留一位小数即可。取值越大，语速越快。​

​

​

​

MiniMax 语音合成​

Authorization String 必选 示例值：eyJhbG****SUzI1N​

API 密钥。前往 [Minimax 账户管理-接口密钥](https://platform.minimaxi.com/login)获取。​

​

Groupid String 必选 示例值：983*****669​

用户所属组 ID。前往 [Minimax 账号信息-基本信息](https://platform.minimaxi.com/login)获取。​

​

model String 必选 示例值：speech-01-turbo​

发起请求的模型版本。可取值：​

- speech-01-turbo：最新模型，拥有出色的效果与时延表现。​

- speech-01-240228：稳定版本模型，效果出色。​

- speech-01-turbo-240228：稳定版本模型，时延更低。​

​

URL String 必选 示例值：https://api.minimax.chat/v1/t2a_v2​

请求语音合成 URL，该参数固定取值：https://api.minimax.chat/v1/t2a_v2。​

​

voice_setting Object 可选 示例值：-​

音频配置。​

speed Float 可选 示例值：1.0​

语速。取值越大，语速越快。取值范围为 [0.5,2]，默认值为1.0。​

​

vol Float 可选 示例值：1.0​

音量。取值越大，音调越高。取值范围为 (0,10]，默认值为 1.0。​

​

pitch Float 可选 示例值：0​

语调。取值越大，语调越高。取值范围为 [-12,12]，且必须为整数。默认值为 0，表示原音色输出。​

​

voice_id String 可选 示例值：male-qn-jingying​

系统音色编号/复刻音色编号。​

- 系统音色可前往 [voice_setting.voice_id](https://platform.minimaxi.com/document/T2A%20V2?key=66719005a427f0c8a5701643#YqSh1KAoyms1WH4XJrdeIrrb)查询。​

- 克隆音色参看[FAQ](https://platform.minimaxi.com/document/FAQ?key=66701d031d57f38758d581be)。​

​

​

​

pronunciation_dict Object 可选 示例值：-​

特殊标注配置。可对特殊文字、符号指定发音。​

tone String[] 可选 示例值：["燕少飞/(yan4)(shao3)(fei1)","达菲/(da2)(fei1)"，"omg/oh my god"]​

用于替换需要特殊标注的文字、符号及对应的发音，可用于调整声调或指定其他字符的发音。格式为 "原文字/注音"，注音部分根据语言类型采用不同方式标注：​

- 英文注音：使用对应发音的英文单词，例如："omg/oh my god"。​

- 中文注音：使用拼音，并在每个音节后以括号标注声调，音调用数字表示：​

- 一声（阴平）：1​

- 二声（阳平）：2​

- 三声（上声）：3​

- 四声（去声）：4​

- 轻声：5​

例如，"燕少飞/(yan4)(shao3)(fei1)"、"达菲/(da2)(fei1)"。​

​

​

timber_weights Object[] 可选 示例值：-​

合成音色权重设置。可通过该参数设置多种音色混合，并调整每个具体音色权重。最多支持 4 种音色混合。​

说明​

timber_weights 与 VoiceSetting.voice_id 必须设置其中一个。 ​

voice_id String 可选 示例值：male-qn-jingying​

音色编号。当前仅支持系统音色，可前往 [voice_setting.voice_id](https://platform.minimaxi.com/document/T2A%20V2?key=66719005a427f0c8a5701643#YqSh1KAoyms1WH4XJrdeIrrb) 查询。​

​

weight Integer 可选 示例值：1​

权重。取值为整数，单一音色取值占比越高，合成音色越像。取值范围为[1,100]。​

​

​

stream Boolean 可选 示例值：false​

是否开启流式输出。​

- false：不开启流式输出。​

- true：开启流式输出。​

默认值为 false。​

​

language_booststring String 可选 示例值：auto​

增强指定小语种/方言场景下的语音表现。不同场景下取值及含义如下：​

- 不明确小语种类型：auto。取值为 auto 时，模型将自主判断小语种类型。​

- 小语种：​

- Spanish：西班牙语​

- French：法语​

- Portuguese：葡萄牙语​

- Korean：韩语​

- Indonesian：印度尼西亚语​

- German：德语​

- Japanese：日语​

- Italian：意大利语​

- auto：自动模式​

- 方言：​

- Chinese,Yue：粤语。Chinese,Yue 仅当 MiniMaxTTSConfig.model=speech-01-turbo 时生效。​

默认值为空。​

​

​

​

​

LLMConfig Object 必选 示例值：-​

大模型相关配置。支持的大模型平台如下：​

- [火山方舟平台](https://www.volcengine.com/docs/6348/1558163#yh0bMioaxx)​

- [Coze 平台](https://www.volcengine.com/docs/6348/1558163#FDSwIx4bH5)​

- [第三方大模型/Agent](https://www.volcengine.com/docs/6348/1558163#KI2Fiaz2T4)​

不同大模型平台下，该结构包含字段不同，具体参看如下描述：​

火山方舟平台​

Mode String 必选 示例值：ArkV3​

大模型平台名称。使用火山方舟平台时，该参数固定取值： ArkV3。​

​

EndPointId String 可选 示例值：ep-22****212​

自定义推理接入点 EndPointId。当需要使用模型推理功能（如直接调用部署的基础模型）时，此参数为必填。​

可前往[控制台](https://console.volcengine.com/ark/region:ark+cn-beijing/endpoint?config=%7B%7D)创建或查询自定义推理接入点。​

说明​

- 当前仅支持自定义推理接入点，不支持预置推理接入点。​

- EndPointId 与 BotId 不可同时填写，若同时填写，则 EndPointId 生效。​

​

BotId String 可选 示例值：botid****212​

应用 ID。需要使用方舟应用实验室功能时，为必填。可前往[控制台](https://console.volcengine.com/ark/region:ark+cn-beijing/assistant)创建或查询应用 ID。​

说明​

- 请确保你的应用使用的是自定义推理接入点，目前暂不支持预置推理接入点。​

- ​![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_2248e02256af3c2bc3782c8878a8a892.png)​​

- EndPointId 与 BotId 不可同时填写，若同时填写，则 EndPointId 生效。​

​

Temperature Float 可选 示例值：0.1​

采样温度，用于控制生成文本的随机性和创造性，值越大随机性越高。取值范围为（0,1]，默认值为 0.1。​

​

MaxTokens Integer 可选 示例值：1024​

输出文本的最大 token 限制。默认值为 1024。​

​

TopP Float 可选 示例值：0.3​

采样的选择范围，控制输出 token 的多样性。模型将从概率分布中累计概率超过该取值的标记中进行采样，以确保采样的选择范围不会过宽，值越大输出的 token 类型越丰富。​

取值范围为[0,1]，默认值为 0.3。​

​

SystemMessages String[] 可选 示例值：["你是小宁，性格幽默又善解人意。你在表达时需简明扼要，有自己的观点。"]​

系统提示词。用于输入控制大模型行为方式的指令，定义了模型的角色、行为准则，特定的输出格式等。​

​

UserPrompts Object 可选 示例值：[ { "Role": "user", "Content": "你好" }, { "Role": "assistant", "Content": "有什么可以帮到你的？" }, { "Role": "user", "Content": "你是谁？" }, { "Role": "assistant", "Content": "我是你的智能问答助手。" }​

用户提示词，可用于增强模型的回复质量，模型回复时会优先参考此处内容，引导模型生成特定的输出或执行特定的任务。​

UserPrompts 存储的对话轮数受 HistoryLength 控制。例如UserPrompts中预先存储了两轮对话，HistoryLength设置为 3，用户已进行了三轮对话，第四轮会话开始时，UserPrompts中存储的内容会被全部删除。​

说明​

UserPrompts 中 Role 的取值只包含 user 和assitant，且必须成对出现，否则大模型可能会出现未定义行为。​

​

HistoryLength Integer 可选 示例值：3​

历史问题轮数。默认值为 3。​

在调用该接口时需要确保所有 UserPrompts 和 SystemMessage 消息文本总长度不超过大模型上下文长度。​

例如：历史问题轮数为 3，使用 Skylark2-lite-8k 大模型，长度限制为 8k，UserPrompts 预先存储了两轮对话，用户输入了第一轮会话的问题，此时 system messgage+UserPrompts+第一轮会话问题总长度不超过8k。​

​

Tools Object[] 可选 示例值：-​

使用 Function Calling 功能时，定义模型可以调用的工具列表。仅支持函数作为工具，提供模型生成的 JSON 输入函数列表。​

该功能使用方法参看 [Function Calling](https://www.volcengine.com/docs/6348/1554654)。​

说明​

Function Calling 功能不支持和联网插件、知识库插件同时开启。​

type String 可选 示例值：function​

工具类型。可取值及含义如下：​

function：函数调用。​

​

function Object 可选 示例值：-​

函数调用配置。​

name String 可选 示例值：get_current_weather​

函数名称。​

​

description String 可选 示例值：获取指定城市的天气信息​

对函数用途的描述，供模型判断何时以及如何调用该工具函数。​

​

parameters JSONMap 可选 示例值：-​

函数请求参数，以 JSON Schema 格式描述。具体格式请参考 [JSON Schema](https://json-schema.org/understanding-json-schema) 文档。​

​

​

JSON

复制

{​

"type": "object",​

"properties": {​

"location": {​

"type": "string",​

"description": "城市，如：北京",​

},​

},​

"required": ["location"],​

}​

​

​

​

​

​

Prefill Boolean 可选 示例值：false​

将 ASR 中间结果提前送入大模型进行处理。​

- true：开启。启用后，允许将 ASR 识别中间结果提前发送给大模型进行处理，以降低延时。​

- false：关闭。等待 ASR 模块识别出相对完整的一句话后再送入大模型处理。​

默认值为 false。​

说明​

开启后会产生额外模型消耗。​

​

VisionConfig Object 可选 示例值：-​

视觉理解能力配置。仅在推理点选择 vison 系列模型时生效，如Doubao-vision-pro-32k。该功能使用说明参看[视觉理解能力](https://www.volcengine.com/docs/6348/1408245)。​

说明​

该功能仅在使用 EndPointId（推理点）接入大模型，且推理点选择 vison 系列模型时才生效，如Doubao-vision-pro-32k。​

Enable Boolean 可选 示例值：true​

是否开启视觉理解功能。​

- false：不开启。​

- true：开启。​

默认值为 false。​

​

SnapshotConfig Object 可选 示例值：-​

截图相关配置。截图送入大模型以供理解信息。​

StreamType Integer 可选 示例值：0​

截图流类型。​

0：主流。​

1：屏幕流。​

默认值为 0。​

​

ImageDetail String 可选 示例值：auto​

图片处理模式。取值及含义如下：​

- high：高细节模式。适用于需要理解图像细节信息的场景，如对图像的多个局部信息/特征提取、复杂/丰富细节的图像理解等场景，理解更全面。​

- low：低细节模式。适用于简单的图像分类/识别、整体内容理解/描述等场景，理解更快速。​

- auto：自动模式。根据图片分辨率，自动选择适合的模式。​

默认值为 auto。​

​

Height Integer 可选 示例值：640​

送入大模型截图视频帧高度，取值范围为 [0, 1792]，单位为像素。​

不填或传 0 时自动修改为 360。​

传入大模型截图视频帧宽度自动按传入高度进行比例计算。​

​

Interval Integer 可选 示例值：1000​

相邻截图之间的间隔时间，取值范围为 [100, 5000]，单位为毫秒。默认值为 1000。​

​

ImagesLimit Integer 可选 示例值：2​

单次送大模型截图数。取值范围为 [0, 50]。​

不传或传 0 时自动修改为 2。​

​

​

StorageConfig Object 可选 示例值：-​

截图存储配置。​

Type Integer 可选 示例值：0​

存储类型。​

- 0：按照 Base 64 编码存入服务端缓存，会话结束后自动删除。​

- 1：存储至 TOS 平台。使用 TOS 存储前需前往[控制台](https://console.volcengine.com/tos/?)开通该服务。​

​

TosConfig Object 可选 示例值：-​

TOS 存储配置。​

AccountId String 可选 示例值：account_id​

火山引擎平台账号 ID，例如：200000000。查看路径参看[查看和管理账号信息](https://www.volcengine.com/docs/6261/64929)。​

说明​

- 此账号 ID 为火山引擎主账号 ID。​

- 若你调用 OpenAPI 鉴权过程中使用的 AK、SK 为子用户 AK、SK，账号 ID 也必须为火山引擎主账号 ID，不能使用子用户账号 ID。​

​

Region Integer 可选 示例值：0​

存储桶区域。不同存储桶区域对应的 Region 不同，具体参看 [Region对照表](https://www.volcengine.com/docs/6348/1167931#region)。​

默认值为 0。​

说明​

该字段填入的存储桶区域需要与你在 TOS 平台创建存储桶时选择的区域相同。​

​

Bucket String 可选 示例值：bucket​

存储桶名称。前往[控制台](https://console.volcengine.com/tos/bucket?)创建或查询。​

​

​

​

​

​

Coze 平台​

Mode String 必选 示例值：CozeBot​

大模型平台名称。该参数固定取值：CozeBot。​

​

CozeBotConfig Object 必选 示例值：-​

Coze 智能体配置。​

Url String 必选 示例值：https://api.coze.cn​

请求地址。该参数固定取值：https://api.coze.cn​

​

BotId String 必选 示例值：73****68​

Coze 智能体 ID。​

可前往你需要调用的智能体开发页面获取。开发页面 URL 中 bot 参数后的数字即智能体 ID。例如开发页面 URL 为：https://www.coze.cn/space/341/bot/73428668，则 BotId 为 73428668。​

​

APIKey String 必选 示例值：czu_UEE2mJn6****MHxLCVv9uQ7H​

Coze 访问密钥。​

你可以生成[个人访问令牌](https://www.coze.cn/open/oauth/pats)以供测试。线上环境注意替换为 OAuth 访问密钥。你可根据不同的使用场景，选择不同的 OAuth 授权方式，详情参考 [OAuth 应用管理](https://www.coze.cn/open/docs/developer_guides/oauth_apps)。​

说明​

创建个人访问令牌或 OAuth 应用时，你需要根据你的 Bot 使用场景勾选对应权限，否则会鉴权失败。​

​

UserId String 必选 示例值：123​

标识当前与智能体对话的用户，由你自行定义、生成与维护。UserId 用于标识对话中的不同用户，不同的 UserId，其对话的上下文消息、数据库等对话记忆数据互相隔离。如果不需要用户数据隔离，可将此参数固定为一个任意字符串，例如 123，abc等。​

​

HistoryLength Integer 可选 示例值：3​

历史问题轮数。默认值为 3。​

在调用该接口时需要确保作为上下文的用户消息和智能体消息文本总长度小于模型上下文长度。​

例如：历史问题轮数为 3，使用 Skylark2-lite-8k大模型，该模型上下文长度限制为 8k，询问第 10 个问题时，需保证第 10 个问题的长度与第八、九轮用户消息和智能体消息文本的总长度之和不得超过 8k。​

​

Prefill Boolean 可选 示例值：false​

将 ASR 中间结果提前送入大模型进行处理。​

开启该功能后可不等待 ASR 模块识别出完整的一句话再送入大模型处理，而是将 ASR 识别中间结果提前送入大模型进行处理以降低延时。​

- true：开启。​

- false：关闭。​

默认值为 false。​

说明​

开启后会产生额外模型消耗。​

​

EnableConversation Boolean 可选 示例值：false​

是否将上下文存储在 Coze 平台。​

若需要使用 Coze 平台上下文管理相关功能，如将指定内容添加到会话中，可开启此功能。功能开启后 RTC 不再存储上下文内容。​

- false：不开启。​

- true：开启。​

默认值为 false。​

说明​

EnableConversation 为 true 时会导致HistoryLength设置无效。​

​

​

​

第三方大模型/Agent​

Mode String 必选 示例值：CustomLLM​

​

URL String 必选 示例值：https://api.***.com/v1/chat/completions​

​

ModelName String 可选 示例值：name1​

​

APIKey String 可选 示例值：pat*****123231​

​

MaxTokens Integer 可选 示例值：1024​

​

Temperature Float 可选 示例值：0.1​

​

TopP Float 可选 示例值：0.3​

​

SystemMessages String[] 可选 示例值：["你是小宁，性格幽默又善解人意。你在表达时需简明扼要，有自己的观点。"]​

​

UserPrompts Object 可选 示例值：[ { "Role": "user", "Content": "你好" }, { "Role": "assistant", "Content": "有什么可以帮到你的？" }, { "Role": "user", "Content": "你是谁？" }, { "Role": "assistant", "Content": "我是你的智能问答助手。" }​

大模型 User 角色预设 Prompt，可用于增强模型的回复质量，模型回复时会优先参考此处内容。​

UserPrompts 存储的对话轮数受 HistoryLength 控制。例如UserPrompts中预先存储了两轮对话，HistoryLength设置为 3，用户已进行了三轮对话，第四轮会话开始时，UserPrompts中存储的内容会被全部删除。​

说明​

UserPrompts 中 Role 的取值只包含 user 和assitant，且必须成对出现，否则大模型可能会出现未定义行为。​

​

HistoryLength Integer 可选 示例值：3​

​

Feature String 可选 示例值：{\"Http\":true}​

​

Prefill Boolean 可选 示例值：false​

​

Custom String 可选 示例值：-​

自定义 JSON 字符串，可传入业务自定义参数。​

​

​

​

SubtitleConfig Object 可选 示例值：-​

配置字幕回调。​

可通过客户端或服务端接收回调消息，消息格式为二进制，使用前需解析。详细说明参看[实时对话式 AI 字幕](https://www.volcengine.com/docs/6348/1337284)。​

DisableRTSSubtitle Boolean 可选 示例值：false​

是否关闭房间内客户端字幕回调。​

- true：关闭客户端字幕回调。​

- false（默认值）：开启客户端字幕回调。开启后，在客户端实现监听 [onRoomBinaryMessageReceived](https://www.volcengine.com/docs/6348/70081#IRTCRoomEventHandler-onroombinarymessagereceived)（以 Android 为例），即可接收字幕回调消息。​

说明​

如需通过服务端接收字幕回调，请配置 ServerMessageUrl 和 ServerMessageSignature。​

​

ServerMessageUrl String 可选 示例值：https://example-domain.com/vertc/subtitle​

接收字幕结果的 URL 地址。通过服务端接收字幕回调时必填。​

接收结果的 URL 必须以域名开头。如果 URL 为 HTTPS 域名，请确保该域名 SSL 证书合法且完整。​

可通过 curl -v http(s)://yourexample-domain.com/vertc/subtitle 命令对域名进行快速校验：​

- 若返回 HTTP 状态码为 301，301 或 302，则说明域名不可用，POST 方法可能会重定向为 GET。​

- 若返回 307或 308则说明域名可用，且始终保持 POST方法。​

注意​

如果你同时通过该接口接收任务状态变化回调和字幕回调，请确保在 ServerMessageUrl ServerMessageURLForRTS 填入相同的 URL，否则会导致无法接收任务状态回调或字幕回调。​

​

ServerMessageSignature String 可选 示例值：b46ab5f1d8ad6a​

鉴权签名。通过服务端接收字幕回调时必填。​

在接收到字幕结果后，与结果中的 signature 字段值进行对比以进行鉴权验证。​

​

SubtitleMode Integer 可选 示例值：0​

字幕回调时是否需要对齐音频时间戳。​

- 0：对齐音频时间戳。​

- 1：不对齐音频时间戳。取 1 时可更快回调字幕信息。​

默认值为 0。​

​

​

FunctionCallingConfig Object 可选 示例值：-​

使用 Function Calling 功能时，从服务端接收工具返回的信息指令配置。​

Function Calling 功能使用详情参看[功能说明文档](https://www.volcengine.com/docs/6348/1359441#callingconfig)。​

说明​

该功能仅在使用火山方舟平台时生效。​

ServerMessageUrl String 可选 示例值：httphttps://example-domain8080/m2​

服务端接收 Function Calling 函数工具返回的信息指令的 URL 地址。功能使用详情参看[服务端实现 Function Calling 功能](https://www.volcengine.com/docs/6348/1554654#%E6%9C%8D%E5%8A%A1%E7%AB%AF%E5%AE%9E%E7%8E%B0)。​

接收结果的 URL 必须以域名开头。如果 URL 为 HTTPS 域名，请确保该域名 SSL 证书合法且完整。​

ServerMessageUrl 和 ServerMessageSignature 均填写正确才能开启该功能。​

​

ServerMessageSignature String 可选 示例值：TestSignature​

鉴权签名。​

你可传入该鉴权参数，在接收到函数调用信息结果后，与结果中的 signature 字段值进行对比以进行鉴权验证。​

​

​

InterruptMode Integer 可选 示例值：0​

是否启用语音打断：​

- 0：开启语音打断。开启后，一旦检测到用户发出声音，智能体立刻停止输出。​

- 1：关闭语音打断。关闭后，智能体说话期间，用户语音输入内容会被忽略不做处理，不会打断智能体讲话。​

默认值为 0。​

​

​

AgentConfig Object 必选 示例值：-​

智能体相关配置，包括欢迎词、任务状态回调等信息。​

TargetUserId String[] 必选 示例值：["user1"]​

真人用户 ID。即使用客户端 SDK 进房的真人用户的 UserId。仅支持传入一个 UserId。​

​

WelcomeMessage String 可选 示例值：Hello​

智能体启动后的欢迎词。​

​

UserId String 可选 示例值：BotName001​

智能体 ID，用于标识智能体。​

由你自行定义、生成与维护，支持由大小写字母（A-Z、a-z）、数字（0-9）、下划线（_）、短横线（-）、句点（.）和 @ 组成，最大长度为 128 个字符。​

若不填，默认值为 voiceChat_$(TargetUserId)_$(timestamp_now)。​

说明​

- 同一 AppId 下 UserId 建议全局唯一。若同一 AppId 下不同房间内智能体名称相同，会导致使用服务端回调的功能异常，如字幕、Function Calling 和任务状态回调功能。​

- UserId 取值与 TargetUserId 不能重复。​

​

​

EnableConversationStateCallback Boolean 可选 示例值：false​

是否接收智能体状态变化回调，获取智能体关键状态，比如如“聆听中”、“思考中“、“说话中“、“被打断“等。功能详细说明，参看[接收状态变化消息](https://www.volcengine.com/docs/6348/1415216)。​

- true：接收。可通过客户端或服务端接收智能体状态变化回调。​

- 通过客户端接收：还需在客户端实现监听回调 [onRoomBinaryMessageReceived](https://www.volcengine.com/docs/6348/70081#IRTCRoomEventHandler-onroombinarymessagereceived)（以 Android 端为例）。​

- 通过服务端接收：需配置字段 ServerMessageURLForRTS 和 ServerMessageSignatureForRTS。​

- false：不接收。​

默认值为 false。​

​

ServerMessageSignatureForRTS String 可选 示例值：b46ab5f1d8ad6a​

服务端接收任务状态变化回调的鉴权签名。​

你可传入该鉴权参数，在接收到回调结果后，与结果中的 signature 字段值进行对比以进行鉴权验证。​

​

ServerMessageURLForRTS String 可选 示例值：https://example-domain.com/vertc/callback​

服务端接收任务状态变化的 URL 地址。​

接收结果的 URL 必须以域名开头。如果 URL 为 HTTPS 域名，请确保该域名 SSL 证书合法且完整。​

注意​

如果同时通过该接口接收任务状态变化回调和字幕回调，请确保在 ServerMessageURLForRTS 与 SubtitleConfig.ServerMessageUrl 填入相同 URL，否则会导致无法接收任务状态回调或字幕回调。​

​

​

Burst Object 可选 示例值：-​

音频快速发送配置。​

开启该功能后，可通过快速发送音频实现更好的抗弱网能力。​

说明​

该功能仅在嵌入式硬件场景下支持，且嵌入式 Linux SDK 版本不低于 1.57。​

Enable Boolean 可选 示例值：true​

是否开启音频快速发送。​

- false：开启。​

- true：关闭。​

默认值为 false。​

​

BufferSize Integer 可选 示例值：10​

接收音频快速发送片段时，客户端可缓存的最大音频时长。取值范围为[10,3600000]，单位为 ms，默认值为 10。​

​

Interval Integer 可选 示例值：10​

音频快速发送结束后，其他音频内容发送间隔。取值范围为[10,600]，单位为 ms，默认值为10。​

​

​

​

​

​

返回参数​

本接口无特有的返回参数。公共返回参数请见[返回结构](https://www.volcengine.com/docs/6348/1178322)。​

其中返回值 Result 仅在请求成功时返回 ok，失败时为空。