7 年前我打数学建模比赛，我们团队采用了退火算法拿了一等奖，7 年间我一直记着这个算法，并多次用它对照我波澜起伏的人生，无意间发现它已经成为了我的主旋律。

它可以解释我的很多经历与动机，比如**为什么我这么痴迷于漂泊**，以及**不知天高地厚地去创业**。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305233609.png?x-oss-process=image/resize,w_800/quality,q_80)


我想，**我应该是在追求一种拥有张力的人生，而张力就意味着生命力，就意味着超越极限的一种可能**。

《征服市场的人：西蒙斯传》第三章的标题是：“**一定有办法对价格建模**”。这个话题也可以延展下去：“**一定有办法确定人生的最优解**”。

作为 P 人，两年前我曾经漫无目的地在大地上漂泊，三个月内途径了： 北京、武汉、咸宁、长沙、南宁、柳州、桂林、广州、东莞、惠州、深圳 、香港、杭州。

而今年春节以来的一个月内，我一下子遍访了20个城市，这次的目的略有不同，主要以创业的前辈以及好久未见的旧朋友为主，收获颇多。路线如下：1. 常州 2. 无锡 3. 苏州 4. 上海 5. 杭州 6. 广州 7. 香港 8. 深圳 9. 广州 10. 昆明 11. 曲靖 12. 成都 13. 重庆 14. 长沙 15. 武汉 16. 合肥 17. 南京 18. 上海 19. 泰安 20. 济南 21. 北京。

这一次本来还想继续走一下心心念的大西北和大东北，但实在时间、预算有限，北京的朋友们也希望我尽早回京进入工作状态。所以，只能下次了！

我还需要一点时间以整理出旅后感，并决定**周日晚上在北京五道口举办一场线下闭门分享会**，欢迎留言区与后台申请打卡交流~

好了，回到本文写作的初衷，由于本次旅行城市过多，我很想可视化我的旅行足迹，问了一下 DeepSeek，它给我推荐了一些方案。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305224810.png?x-oss-process=image/resize,w_800/quality,q_80)

其中西瓜足迹小程序已经搜索不到，而足迹地图小程序只能显示点亮效果，不能看到访问城市的顺序。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305225157.png?x-oss-process=image/resize,w_800/quality,q_80)

所以我就想到用 AI 给我快速开发一个能显示轨迹的产品，无非就是：
1. 数据系统
	1. 支持增量录入
	2. 支持一次性导入导出
	3. 支持城市、日期、交通工具等数据结构
2. 可视化系统
	1. 支持一张风格化的地图
	2. 支持突出显示遍访的城市
	3. 支持友好地显示城市的访问顺序
	4. 支持更酷的交通展示方式（例如高铁可以基于列车号展示沿途结点，飞机则可以像航旅纵横一样显示一条弧线）
3. 支持分享……
4. ……

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305225550.png?x-oss-process=image/resize,w_800/quality,q_80)

基于此，我就让 AI 开工了。

我本来是只用 Windsurf 的，但无奈中途经常 internal error，这背后的原因有很多种，比如说：
- 目前用的人太多了，比较卡，后端没有做很好的队列系统（这点为字节打 call）……
- 目标代码文件过长，导致处理起来出现问题……

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305230034.png?x-oss-process=image/resize,w_800/quality,q_80)

所以我顺带尝试了字节的 Trae。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305230216.png?x-oss-process=image/resize,w_800/quality,q_80)


实测下来，我觉得 Trae 目前比较优越的点有三个：
1. 对大模型的 api 调用做了队列控制，从产品体验上更 stable，可预期未来开付费高速通道后体验会更好
2. 内置了 web browser，非常适合前端开发项目（等于降维打击了 bolt）
3. 免费（当然，我不是很关心这个，但目前这个也很重要）

但最大的缺点还是慢，用的人太多了，尤其是我是通宵写的程序，在快天亮的时候，直接排队到离谱了（能达到 60 多……），这对我这样的专业开发者来说是很难接受的。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305230448.png?x-oss-process=image/resize,w_800/quality,q_80)


不过有一说一，Trae 对专业开发者来说，目前的优势有限，因为 AI IDE 的核心是给一个需求后它实现的好不好，在这点上，Trae 做的暂时并不会比 windsurf、cursor 等更好，但普通人确实无法抵挡它免费与稳定可靠的诱惑！

希望 Trae 继续加油，这是他们的 Discord：https://discord.com/invite/NV3MF24tAe

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305230644.png?x-oss-process=image/resize,w_800/quality,q_80)

ok，说回正事，我最后和 AI 共同开发出的可视化城市轨迹系统长这样：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250305230803.png?x-oss-process=image/resize,w_800/quality,q_80)

目前免费，快来试试吧：**vtrip.cs-magic.cn** ！

正在迭代中，已经给设计师加鸡腿，以设计更酷的地图与轨迹！

