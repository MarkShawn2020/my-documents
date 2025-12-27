# 马斯克开源Twitter推荐算法，GitHub秒破万星，还承诺每24-48小时进化一次

关注前沿科技 量子位

 _2023年04月01日 12:03_ _北京_

##### 金磊 发自 凹非寺  
量子位 | 公众号 QbitAI

**马斯克**的“开源承诺”，终于如约而至。

就在刚刚，马斯克正式宣布：

> 大部分（Twitter的）**推荐算法**将在今天开源，剩下的也会跟进。

![图片](https://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKcOQURibIReOZsHmZRaslfDFqg9pyreJWsXyo51JibnKMxX3kk2k3zcUg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

而且马斯克紧接着亮出了GitHub上Twitter推荐算法源代码的地址。

仅仅数小时，便揽获**上万**个Star：

![图片](https://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahK7ZkabSM492xImQh8JKIdD1tbE7Ac5rLKXADItHrQwWvEY02Bt2kC0w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

除此之外，马斯克还表示：

> 推特将每24到48小时更新一次基于用户建议的推荐算法。

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKXpBx944lAeoqWicp3N0ryiaBhw5LEwwYSxsv6ZRcFjUvLhmCyIaOKODw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

至此，这个号称每天从5亿条推文做推荐的大算法的庐山真面目，终于得以露出。

## Twitter的推荐算法长什么样？

据介绍，Twitter的推荐系统基于一组核心模型和功能，可以从推文、用户和互动数据中提取潜在信息。

这些模型的作用是回答Twitter网络中的重要问题，例如，“未来你与另一个用户互动的概率是多少？”或者，“Twitter上有哪些社区以及其中的趋势推文是什么？”

若是能够准确回答这些问题，就可以让Twitter提供更多相关的推荐。

Twitter的推荐系统由三大部分构成：

- 从不同的推荐源获取最好的推文，这个过程称为候选源。
    
- 使用机器学习模型对每条推文进行排名。
    
- 应用heuristics和filters，例如过滤来自已屏蔽用户的推文、NSFW内容和已看到的推文。
    

负责构建和提供“For You”时间轴的服务被称为“Home Mixer”。

“Home Mixer”建立在“Product Mixer”之上，这是定制的Scala框架，有助于构建内容的动态流。

这项服务作为软件主干，连接不同的候选源、评分函数、heuristics和filters。

![图片](https://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKw2ar5Lmm2CGqplDIGQHYunia9w6qtZiciciafo7PRAQhIZQEV23icKpmnGQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

## 候选源（Candidate Sources）

Twitter使用多个候选源来为用户检索最近和相关的推文。

对于每个请求，推特尝试通过这些源从数亿条推文池中提取最佳的1500条。

从您关注的人（内部网络）和不关注的人（外部网络）中寻找候选人。

如今，“为您推荐”时间轴平均由50％的内部网络推文和50％的外部网络推文组成（尽管这可能因用户而异）。

### 内部网络资源（In-Network Source）

内部网络资源是最大的候选来源，旨在提供关注的用户最相关、最新的推文。

它使用逻辑回归模型高效地对关注的人的推文进行排名，以其相关性为基础。然后将排名最高的推文发送到下一阶段。

排名内部网络推文最重要的组成部分是Real Graph。

Real Graph是一种模型，用于预测两个用户之间的互动可能性。用户和推文作者之间的Real Graph分数越高，就会包括更多他们的推文。

内部网络来源最近成为Twitter的研究对象。最近Twitter停止使用Fanout服务，这是一个12年前用来从每个用户的推文缓存中提供内部网络推文的服务。

![图片](https://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKajBU8IicqjkbXBpQTsIXkRLTTREsjoWVHnv1xHYG6wURoMkBTS8PKrQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 外部网络资源（Out-of-Network Sources）

在用户网络之外寻找相关的推文是一个棘手的问题。

因为如果你不关注作者，怎么知道某条推文是否与你相关？

为此，Twitter采取了两种方法来解决这个问题。

一个是社交图（Social Graph）。

这个方法是通过分析你关注的人或有相似兴趣的人的活动，来估计你会发现什么是相关的。

主要遍历参与的图，并按照以下步骤回答以下问题：

- 我关注的人最近在Twitter上发了什么消息？
    
- 谁和我一样喜欢类似的推文，他们最近还喜欢什么？
    

团队根据这些问题的答案生成候选推文，并使用Logit模型对产生的推文进行排名。

这种类型的图形遍历对于外部网络推荐是必不可少的；团队开发了 GraphJet，一个维护用户和推文之间实时交互图的图形处理引擎，来执行这些遍历。

虽然这种搜索Twitter参与和关注网络的启发式方法已经被证明是有用的，但嵌入式空间方法已经成为外部网络推文的更大来源。

第二个是嵌入空间（Embedding Spaces）。

嵌入式空间方法旨在回答一个关于内容相似性的更普遍的问题——什么推文和用户与我的兴趣相似？

Embeddings通过生成用户兴趣和推文内容的数字表示来工作。然后可以计算这个嵌入空间中任意两个用户之间的相似度，推文或用户-推文 对。

只要生成准确的embedding，就可以使用这种相似性作为相关性的替代。

Twitter 最有用的嵌入空间之一是 SimClusters。

SimClusters 使用自定义矩阵分解算法发现由一群有影响力的用户锚定的社区（有14.5万个社区，每三周更新一次）。

用户和推文在社区空间中表示，并且可以属于多个社区。社区的规模从个人朋友群的几千名用户到新闻或流行文化的数亿用户不等：

![图片](https://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKiahoXKYOsu5WVmYojGiaYKLrluwYKr4CbzTXjAd0JyRuvXxaoOSibastA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

……

更多与之相关的详细内容，可戳文末链接~

## One More Thing

Twitter的算法开源了，然后手快的网友吧……都已经开始根据算法总结怎么成为大V了![图片](https://res.wx.qq.com/t/wx_fed/we-emoji/res/v1.3.10/assets/newemoji/Yellowdog.png?tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)：

你关注的人数和关注你的人数比例很重要、订阅TwitterBlue有一定作用……

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/YicUhk5aAGtDpWYn6fW5MgCs1v38icJahKod4aekDSb63juqo6Jo21Ie9k2vXBqRich4O9r8CmMS3iaOe73UUnKPIA/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

参考链接：  
[1]https://blog.twitter.com/engineering/en_us/topics/open-source/2023/twitter-recommendation-algorithm  
[2]https://github.com/twitter/the-algorithm  
[3]https://twitter.com/elonmusk/status/1641874582473695246  
[4]https://twitter.com/steventey/status/1641892386564640768?s=46&t=iTysI4vQLQqCNJjSmBODPw

— **完** —

**「人工智能」、「智能汽车」微信社群邀你加入！**  

欢迎关注人工智能、智能汽车的小伙伴们加入交流群，与AI从业者交流、切磋，不错过最新行业发展&技术进展。

PS. 加好友请务必备注您的姓名-公司-职位噢 ~

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/YicUhk5aAGtBIYHY6XEtEedPhTUYAdKev9WH0ibWHOr4IYOvI1T6MNuV9yicoJffRAe0KhiaNwJXX4lhKJNaq8C01g/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

  

**点这里👇关注我，记得标星哦～**

![](http://mmbiz.qpic.cn/mmbiz_png/YicUhk5aAGtCEFSVW5ubo08Zfv1qB5iapricibTBdETkBNtolJxnSUib6UXhjWWz3aib8vETY00P2lKR1uG3qLHicSoWg/300?wx_fmt=png&wxfrom=19)

**量子位**

追踪人工智能新趋势，关注科技行业新突破

3326篇原创内容

公众号

**一键三连「分享」、「点赞」和「在看」**

**科技前沿进展日日相见 ~** 

![图片](https://mmbiz.qpic.cn/mmbiz_svg/g9RQicMD01M0tYoRQT2cMQRmPS5ZDyrrfzeksiay90KaDzlGBH61icqHxmgFKfvfXtVuwTHV740CDLAaXU1LIfZyoJEpYKcRIiaE/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)