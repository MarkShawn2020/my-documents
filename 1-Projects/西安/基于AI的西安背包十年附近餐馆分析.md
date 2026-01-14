最近几天在西安的背包十年青年客栈，每天都不知道吃什么，好在前台甩给了我一份pdf文档，里面记载着附近很多被验证过的美食店。

![](http://cdn.cs-magic.cn/picgo/20251219233627295.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


但坏也坏在这里，我看着这pdf里这么多的店名，不禁眼花缭乱，实在是一头雾水啊，总不能一个个去搜吧！

![](http://cdn.cs-magic.cn/picgo/20251219233720152.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

这时候突然灵机一动，要不，我 vibe 个程序，它自动解析pdf里的店名，然后基于高德批量地获取精确的坐标，然后在地图上显示出来？

说干就干，that's it！

---

在此之前，我们需要先在[高德开放平台](https://console.amap.com/dev/key/app) 上新建一个应用：

![](http://cdn.cs-magic.cn/picgo/20251217150503586.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

并且生成key（注意前端和后端的key要分开）：

![](http://cdn.cs-magic.cn/picgo/20251217150701716.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


拿到高德 key之后在，参考 [概述-MCP Server | 高德地图API](https://lbs.amap.com/api/mcp-server/summary) 在 claude app 里配置高德mcp：

![](http://cdn.cs-magic.cn/picgo/20251217150806103.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

配置了后，可以enable所有权限：

![](http://cdn.cs-magic.cn/picgo/20251217151628570.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

接着交给claude artifact（我看artifact上有这么多小程序、轻页面，就想着先拿它试试手，天真地以为可以满足我的需求）：

![](http://cdn.cs-magic.cn/picgo/20251217150929982.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

点击（始终）允许claude调用mcp：

![](http://cdn.cs-magic.cn/picgo/20251217151302425.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

但报错了！高德提示 platform不匹配：

![](http://cdn.cs-magic.cn/picgo/20251217151348483.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

被高德无情拒绝了之后（虽然是我的锅），claude还是不依不饶默默地做了个app，像一个无比可靠的老实人：

![](http://cdn.cs-magic.cn/picgo/20251217151725358.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

不过需要fix一下：

![](http://cdn.cs-magic.cn/picgo/20251217151746079.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

中间出现了闪烁：

![](http://cdn.cs-magic.cn/picgo/recording_2025-12-17T0718.gif)

不过很快就自动修好了，呈现了初始页面：

![](http://cdn.cs-magic.cn/picgo/20251217152023041.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

**至此，艺术已成！**

---

但，我们还是想玩把大的，搏一搏，单车变摩托！

赶紧换上web服务的key：

![](http://cdn.cs-magic.cn/picgo/20251217151457305.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

配置好后，让claude重新测试，确实可以了：

![](http://cdn.cs-magic.cn/picgo/20251217152128412.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

你看这个claude，写的高德搜索接口，还知道设置位置和距离的组合搜索：

![](http://cdn.cs-magic.cn/picgo/3c8d6a75112a0cb8ce5e38759ad56aca.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


**AI时代，撸起袖子就是干，好嘛！**

经过大概50步左右，终于开始汇总输出了：

![](http://cdn.cs-magic.cn/picgo/20251217153103437.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

高德地图官方坐标拾取器搜索背包十年西安钟楼店的结果是`108.947547,34.261267`，显示在钟楼的北边（也符合实际结果）：

![](http://cdn.cs-magic.cn/picgo/20251217154453233.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

claude里输出的是：`108.947547, 34.261267`，是一样的，但地图（基于openstreetmap）显示却在了钟楼的西边：

![](http://cdn.cs-magic.cn/picgo/20251217154431810.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

坐标确认无误，但显示不正确，看样子还是前端组件的问题，我prefer还是用高德前端组件，但又开始报错，解决多个问题后，还是像一开始一样显示空白：

![](http://cdn.cs-magic.cn/picgo/20251217155438581.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


**claude artifact本质上是一个可以运行tsx单文件的沙箱环境，感觉能力有限，我一个地图显示的需求，都做不了……**

而且大部分情况下，它都需要重写整个tsx文件，效率有点慢。

打算换一个家伙！

---

上Lovable！

![欢迎 Lovable，generated via nano-banana-pro](http://cdn.cs-magic.cn/picgo/2f5813b6e7618940b18c5457770637771c820b8d.jpeg?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


结果tmd lovable不支持高德mcp，一人血书跪求……

![](http://cdn.cs-magic.cn/picgo/20251217155630530.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


---

再换！

上 cc！

![欢迎 Claude Code，generated via nano-banana-pro](http://cdn.cs-magic.cn/picgo/%E6%AC%A2%E8%BF%8E%20claude%20code%20-%20nano-banana-pro.jpeg?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)




考虑到这个项目对高德mcp还是有一定需求，所以我切回了cc尝试继续调试（先把artifact里的tsx文件下载下来，再初始化初始化）：

```prompt

基于 @xian-food-map.tsx 初始化本项目，使之可以基于pnpm dev运行
```

![](http://cdn.cs-magic.cn/picgo/20251217155940409.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


然后打开F12（artifact不知道怎么打开F12），复制粘贴一些bug给cc继续分析，然后就搞定了！

![](http://cdn.cs-magic.cn/picgo/20251217160331909.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

定位功能也是正常的：

![](http://cdn.cs-magic.cn/picgo/20251217160411074.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

不过后面遇到了gps拿不到定位的问题，所以fallback使用wifi，但wifi其实也不准，会飘到其他的地方（因为应该是按猫的地址而不是wifi地址，或者它本身的定位偏差较大）

接着我们喂入手工川设计风格，并增加了距离指示器、标签，个人非常满意，效果如下：

![](http://cdn.cs-magic.cn/picgo/f93dfbe3c91bdd1911313503f19935a4.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

![AI手搓的力导向布局算法](http://cdn.cs-magic.cn/picgo/b5a6ce49b1d983687b8523cdf4084537.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


再接着我们进一步基于高德，实现了搜索匹配，cc还手搓了一个Haversine距离算法以解决高德搜索结果里不包含距离的问题：

![](http://cdn.cs-magic.cn/picgo/16e415405c9c63876a246f6275bf5419.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


![AI手搓的Haversine距离算法](http://cdn.cs-magic.cn/picgo/20251217230001663.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

事实上目前的完成度已经非常高了。

**尽管我原先只是为了知道背包十年前台发给我的美食文件里哪个离我最近，我好去吃午饭，结果现在都晚上了，越做越上头，连饭都索性不吃了……**

![](http://cdn.cs-magic.cn/picgo/20251217230240639.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


我下一个需求是把这个美食地图产品SaaS化，并且更加通用化，与cc的对话如下：

```md

- **Q:** /tttt 请将这个项目全系升级为 Lovmap，以适合大家基于地图进行数据分析、出行规划、探店等...
- **A:** 我需要先了解当前项目的结构和代码，然后制定升级计划。让我探索一下代码库。
- **A:** 现在我对项目有了全面了解。这是一个大型重构任务，需要将 Lovfood（美食地图）升级为 Lovmap（通用地图平台）。让我进入计划模式来详细设计。
- **A:** 让我先深入了解当前代码，然后设计升级方案。
- **A:** 现在我对项目有了全面了解。这是一个单文件架构的美食地图应用（约580行），使用高德地图，硬编码了13个西安餐厅数据。...
- **A:** 明确了：需要后端 + AI解析PDF + 扩展字段 + 保留示例。让我启动Plan代理来设计详细方案。
- **A:** 方案设计完成。让我将计划写入文件，然后确认一个关键问题。
- **A:** 确认使用 Supabase。计划已完整，包含：...
- **A:** 计划已批准，开始实施。
- **A:** Tailwind 配置已经是 shadcn 兼容格式。需要添加 path alias。
- **A:** 更新 index.html 标题，然后检查构建。
- **A:** 修复 TypeScript 类型错误。
- **A:** TypeScript 检查通过。Phase 1 完成，更新进度。
- **A:** **Phase 1 完成！** 项目已重构为模块化架构：...
- **Q:** 很好，请继续，supabase的配置信息是：...
- **A:** 现在更新页面使用 Supabase 数据。
- **A:** 需要修复 `getCategoryColor` 函数，让它从传入的 categories 获取颜色而不是硬编码。
- **A:** **Phase 2 代码完成！** 现在需要你在 Supabase 执行 SQL 脚本。...
- **Q:** 是不是可以程序化搞定？
- **A:** 可以，用 Supabase CLI。
- **A:** CLI 已安装。初始化并执行 migration。
- **A:** 数据库表创建完成。现在继续 Phase 3: PDF导入。
- **A:** **Lovmap 升级完成！**...
- **Q:** 上传一份pdf后，一直提示解析中…… @src/components/import/PDFUploader.tsx:119:11
- **Q:** [Request interrupted by user]
- **Q:** pdf解析后的文本显示为：(��
- **A:** PDF二进制解析在Edge Function不好处理。改为前端提取文本，后端只做LLM解析。
- **A:** 已修复。现在流程是：...
- **Q:** main.tsx:1 Parse error: Error: 无法从文件中提取文本...
- **A:** pdf.js worker 加载问题。修复配置。
- **A:** 版本5.x的worker路径不同。用禁用worker模式先跑通。
- **Q:** 继续
- **A:** pdfjs-dist 5.x 有兼容性问题，降级到稳定版本。
- **A:** 已降级到 pdfjs-dist 3.11.174。刷新页面再试导入 PDF。...
- **Q:** 依旧显示：Parse error: Error: 无法从文件中提取文本...
- **A:** 添加详细日志定位问题。
- **A:** 刷新后再试，查看控制台日志。会显示：...
- **Q:** Reading PDF file: 西安早餐推荐2025.pdf 93797 bytes...
- **A:** 问题找到了：`items: 0` 说明这是**扫描件/图片PDF**，没有文本层。需要OCR识别。
- **Q:** [Request interrupted by user]
- **Q:** 不，暂时直接报错提示暂时不支持扫描件即可
- **A:** 完成。现在扫描件PDF会提示：**"此PDF为扫描件/图片，暂不支持。请上传含文本层的PDF或TXT文件"**...
- **Q:** 好的，另一份文件显示：...
- **A:** 文本提取成功了！问题在Edge Function解析。没有OpenAI Key时简单解析不够智能。...
- **A:** 完成。现在前端直接解析，不依赖Edge Function。刷新后再试：...
- **Q:** 可以对接zenmux api，参考@'/Users/mark/projects/my-documents/reference/zenmux/Quick Start.md' ，以及 @.env 里已经配置了key
- **Q:** This session is being continued from a previous conversation that ran out of context. The conversation is summarized below:...
- **A:** 我来集成 ZenMux API 进行智能解析。...
- **A:** 创建 AI 解析模块：
- **A:** 更新 PDFUploader 使用 AI 解析：
- **A:** 更新提示文字：
- **A:** ZenMux API 已集成完成。...
- **Q:** 很棒，返回坐标这步，可以使用高德（已经配置了mcp）批量获取
- **Q:** [Request interrupted by user]
- **Q:** 很棒，返回坐标这步，可以使用高德（已经配置了mcp）批量获取
- **A:** 让我看下当前的地理编码实现：
- **A:** MCP 工具是对话层的，前端代码还是要调用高德 REST API。不过可以优化成批量请求（高德支持每次最多 10 个地址）：
- **A:** 已优化为批量请求：...
- **Q:** /ttt @src/components/import/ImportPreview.tsx:57:7 正常应该分散步：...
- **A:** <thinking>...
- **A:** <thinking>...
- **A:** <thinking>...
- **A:** 先重构 PDFUploader，移除坐标获取逻辑：
- **A:** 创建 POI 搜索函数：
- **A:** 重构 ImportPreview，加入渐进式 POI 搜索：
- **A:** 更新 MapPage 传递位置上下文：
- **A:** 重构完成。新的流程：...
- **Q:** @src/components/import/ImportPreview.tsx:218:9 目前大模型解析出地点后，要允许用户批量或者单个的进一步更新每个地点的具体信息，但同时要有个选项，是否以某个位置（用户定位或者手动输入）为中心
- **A:** 完成。现在 ImportPreview 支持：...
- **Q:** 为什么定位失败了：...
- **A:** 这是 macOS 定位服务的问题。常见原因：...
- **Q:** [Request interrupted by user]
- **Q:** 不要fallback，我要的是用户引导...
- **A:** 两个问题，一起修复：...
- **A:** 已修复：...
- **Q:** 显示：地图未加载完成，请稍后再试
- **A:** 说明地图还没初始化完。让我检查 useAMap 的加载逻辑：
- **A:** 问题在于 useEffect 依赖 `containerRef` 但 ref 对象引用不变，导致 `.current` 变化时 effect 不会重新运行。
- **A:** 等等，如果 SDK 加载太快（缓存），effect 可能在 DOM 渲染前就运行了。改用更可靠的方式：
- **A:** 已修复。现在如果 DOM 还没准备好，会用 `requestAnimationFrame` 等待再初始化。...
- **Q:** 好的，在gps不行的情况下，退步到wifi定位
- **A:** ImportPreview 的定位也加上同样的 fallback：
- **A:** 已完成。两处定位都加了 fallback：...
- **Q:** 只在所有定位都失败了后才弹窗吧
- **A:** 当前逻辑已经是只在最后才弹窗。你是指去掉中间的 console.log 吗？
- **A:** 已去掉中间的 console.log，现在只在 GPS + WiFi 都失败后才弹窗。
- **Q:** 导入和添加应该变成一个按钮，即录入位置，然后在一个dialog里支持多种输入方式
- **A:** 明白，将"导入"和"添加"合并为一个入口。
- **A:** 完成。现在"录入"按钮会显示一个选择界面：...
- **A:** TypeScript 检查通过。现在"导入"和"添加"已合并为一个"录入"按钮，点击后显示选择界面。
- **Q:** @src/components/location/LocationForm.tsx:89:7 手动录入地址里经纬度为什么有预设？
- **A:** 因为传入了 `defaultLng/defaultLat`（地图中心），但手动输入时应该为空，让用户通过搜索地址获取。
- **A:** 已修复。现在手动录入时经纬度为空，用户需要：...
- **Q:** @src/components/ui/button.tsx:42:7 在信息没有填写完整之前不应该支持添加吧
- **Q:** [Request interrupted by user]
- **Q:** @src/components/location/LocationForm.tsx:96:11 在输入地名附近应该支持高德匹配，以获取更精确的地方和位置
- **A:** 重构为搜索建议模式，输入时自动匹配高德 POI：
- **A:** 完成。手动录入现在支持：...
- **Q:** /fix-by-add-log 输入后没有效果
- **A:** 已添加调试日志：...
- **Q:** 好的，我已经重新更新 .env 文件，包含GAODE_API_KEY，和VITE_GAODE_WEB_KEY
- **Q:** [Request interrupted by user]
- **Q:** 好的，我已经重新更新 .env 文件，包含GAODE_API_KEY，和VITE_GAODE_WEB_KEY，刚刚的报错是key平台不匹配
- **A:** 明白，需要更新代码使用新的 `VITE_GAODE_WEB_KEY`。
- **A:** 现在从环境变量读取 key。需要**重启 dev 服务器**让新的 .env 生效。...
- **A:** 已完成：...
- **Q:** 你先别清除log啊
- **A:** 抱歉，加回来：
- **A:** 日志加回来了。重启 dev 服务器后再测试，贴控制台输出给我。
- **Q:** 还是报错，是不是得用后端key：...
- **A:** 对，前端调用 REST API 需要用 **Web服务** 类型的 key，不是 JS API key。...
- **A:** 现在分开了两个 key：...
- **Q:** 需要结合我现在的位置搜索，否则直接搜到北京去了。。。
- **A:** 需要传入位置上下文限制搜索范围。
- **A:** 完成。现在搜索会带上：...
- **Q:** 搜索的时候可以显示距离吗？
- **A:** 完成。搜索结果现在会在名称右侧显示距离：...
- **Q:** 搜索结果的数据如下：...
- **A:** 原来 `distance` 是空数组。高德文本搜索返回的 distance 不可靠，需要手动计算距离：
- **A:** 完成。现在用 Haversine 公式手动计算距离，基于你的当前位置和 POI 坐标。再试试搜索。

---

*Exported with [Lovcode](https://github.com/MarkShawn2020/lovcode) - A desktop companion app for AI coding tools*
```

尽管逗了一大圈，但好在还是实现了自己想要的效果。

它支持创建多个项目！

![](http://cdn.cs-magic.cn/picgo/20251217232828256.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

每个项目支持独立的数据管理！

![](http://cdn.cs-magic.cn/picgo/20251217232905994.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

支持手动输入与文件导入两种录入模式！

![](http://cdn.cs-magic.cn/picgo/20251217232924525.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


……（以下省略十万字）

---

当我兴奋地拿着这个（充满商业潜力的：）美食可视化项目和清迈的朋友交流时：


![](http://cdn.cs-magic.cn/picgo/20251219231505731.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)

好家伙！

![](http://cdn.cs-magic.cn/picgo/20251219231553537.png?imageslim%7CimageMogr2/format/jpeg/size-limit/1000k!)


反向产品设计！

你觉得这个idea如何！

你一票我一票，我们下个版本肝出来！


