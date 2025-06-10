最近一个朋友想让我帮他获取一些专利数据，具体就是**在国家专利检索及分析系统里搜索自己感兴趣的标的（比如“沙发”），然后把检索结果里的文件一一下载下来**。

国家专利检索及分析系统可以通过如下方式找到，也可以直接访问：**https://pss-system.cponline.cnipa.gov.cn/conventionalSearch** 。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ccc098ee958ea657cb13f60a1065e9d4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

搜索时需要先登录：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d6b8d032c1110e2c9fe240dbee368a94.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

登录时有个滑动验证码：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1207f24001f4e1e13be4ee7abdc4acd6.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

首页是个搜索框：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/905217282a499ab20d3f9a7bb09c1172.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

搜素后默认图文布局，一页展示 10 条数据：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/470399159f740386bdeead3de480d2c7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

可以选择修改每一页展示条目数量，最多一页 40 条：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1d69134747ff97f102abdea0d7a1ecde.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

打开 **Charles（一款专业网络调试工具）**，对列表数据进行抓包。

成功拿到，都是明文：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2318002b8fe525c54d8280fd60151a44.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

尝试进行参数重发，发现不行：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/b0e833179c1e9a9d6c4c9aadb1d5e203.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

分析原因，对比一下我们第三页和第四页的发送请求，发现 `executableSearchExp` 和 `parseSearchExp` 是一样的，但和 `searchExp` 都使用了 AES，其中的值不一样，而且很显然是加密的。

```json
%% 第三页 %%
{
	"executableSearchExp": "AES(ES%2FjKNy1poYNq2H8%2FmfJvg%3D%3D)",
	"parseSearchExp": "AES(ES%2FjKNy1poYNq2H8%2FmfJvg%3D%3D)",
	"searchExp": "AES(wLZILXq3i7hqhnkfDLg89eOz%2BQSZCT1RhK7FF2UXqns%3D)",
	"sortFields": "-APD",
	"pagination": {
		"page": 3,
		"limit": 10
	},
	"dbName": "CNDB%2CWPDB",
	"interfaceId": "2001154"
}

%% 第四页 %%
{
	"executableSearchExp": "AES(NxbARNRmirlYpN10xvdfpA%3D%3D)",
	"parseSearchExp": "AES(NxbARNRmirlYpN10xvdfpA%3D%3D)",
	"searchExp": "AES(HP1j4iViR7%2BIN2blQ4aZ7fAkrJiXX1ILzG28KBmjH4I%3D)",
	"sortFields": "-APD",
	"pagination": {
		"page": 4,
		"limit": 10
	},
	"dbName": "CNDB%2CWPDB",
	"interfaceId": "2001154"
}
```

在请求中检索这个值，发现都只在 request 里，而非 response 里，这也意味着这些值**需要在客户端里基于某个脚本进行计算，再发送给服务端**：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1c50cf4e63007cd6781a2d7146a57adb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

初步判断，这个任务如果需要高并发，必须对客户端脚本进行逆向。

但朋友只是希望能够获取**尽可能多的结果，而非尽可能快**。因此，我们只需要实现 **RPA（Robotic process automation，机器人流程自动化）**，而非大规模高速网络爬虫。

这样，我们就不需要费力去做逆向。

对逆向感兴趣的可以移步我 2021 年耗时一周从某拼十万行混淆 JS 中逆向解析近 20 个指纹函数的文章： [南川逆向笔记 | 攻破 PDD 风控系统（一） | 南川笔记](https://www.markshawn.com/blog/2021/05/12/%E8%AE%B0%E9%80%86%E5%90%91%E6%94%BB%E7%A0%B4%E6%8B%BC%E5%A4%9A%E5%A4%9A%E5%8A%A0%E5%AF%86%E7%B3%BB%E7%BB%9F)。

**四年过去了，有了超级智能 AI 的加持，我们曾经的很多工作都值得重来一遍。

**只是，可惜的是，当时的那种莽劲儿，那种秒天秒地的盲目自信，再也回不去了。**







