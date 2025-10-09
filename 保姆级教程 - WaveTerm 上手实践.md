
直接启用ai会报错。
![](https://poketto.oss-cn-hangzhou.aliyuncs.com/08c069d9dfdc2b184f7b6ce8ae4b9d6a.png?x-oss-process=image/quality,q_90/rotate,0)

需要进行设置。

点击 Add AI  Preset：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/fa9bbd4869dc847a8a44a29a4ef5c755.png?x-oss-process=image/quality,q_90/rotate,0)

它是个 json：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/46faad1dee3829e17f0a831bb8c30772.png?x-oss-process=image/quality,q_90/rotate,0)

通用场景我喜欢 gemini，所以我按如下填，主要确保 `ai:model` 和 `ai:apitoken`这两个字段要对，具体可以参考文尾 gemini 配置章节：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3e3a05a0e4f3a0359e2ac33219f1a9b0.png?x-oss-process=image/quality,q_90/rotate,0)

配置结束后，再点击下拉菜单就可以看到预设的模型了：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/41618e6a4ae291a6662e4920e86e2aa8.png?x-oss-process=image/quality,q_90/rotate,0)


## Appendix

### providers

| provider | latest model name | list models                                                     | get api keys                                |
| -------- | ----------------- | --------------------------------------------------------------- | ------------------------------------------- |
| gemini   |                   | https://ai.google.dev/gemini-api/docs/models?hl=zh-cn           | https://aistudio.google.com/apikey<br>      |
| claude   | claude-opus-4-1   | https://docs.anthropic.com/en/docs/about-claude/models/overview | https://console.anthropic.com/settings/keys |
|          |                   |                                                                 |                                             |


gemini 访问有问题：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/b54ed673d70b5569df03b82b9eaaed1c.png?x-oss-process=image/quality,q_90/rotate,0)

似乎需要激活，https://console.cloud.google.com/apis/api/generativelanguage.googleapis.com/metrics?project=gen-lang-client-0994980986：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/6ff115f26c54227f16a18b1049c6f296.png?x-oss-process=image/quality,q_90/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a73d834de6f8bac5a345779513913282.png?x-oss-process=image/quality,q_90/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/edbb949e0e7da76464b50304b1e5a2c6.png?x-oss-process=image/quality,q_90/rotate,0)


Anthropic也有：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/376e2dbaa3bc314c4a0d6001d62bec91.png?x-oss-process=image/quality,q_90/rotate,0)

咦，右上角更新重启后好了
![](https://poketto.oss-cn-hangzhou.aliyuncs.com/f3e35964bbde0afb21a60f3980075661.png?x-oss-process=image/quality,q_90/rotate,0)

