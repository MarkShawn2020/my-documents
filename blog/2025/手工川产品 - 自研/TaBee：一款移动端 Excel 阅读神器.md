
```insta-toc
---
title:
  name: Table of Contents
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

# Table of Contents

- 01. 从痛点出发的功能设计
- 02. 未来计划：需要你的建议
- 03. 开发中的真实挑战
    - 1. 要不要 AI Native
    - 2. AI 写 Pivot 功能真地难啊
    - 3. 各种宕机
- 04. Windsurf 的 DeepSeek 上新体验
- 05. 写在最后
```


前些天，朋友发来一份复杂的 Excel 表格，当我用手机打开时，缩放的挫败感让我意识到：**手机端表格阅读的体验，真地很痛！**  

作为一名独立开发者，我决定花一天时间彻底解决一下这个需求。  

于是，这款最小可行产品（MVP）就和大家见面啦~



![demo](https://poketto.oss-cn-hangzhou.aliyuncs.com/202501312358538.png?x-oss-process=image/resize,w_800)

---

##  **01.** 从痛点出发的功能设计 

在网页版 [TaBee](https://github.com/markshawn2020/tabee) 的开发中，我聚焦三个核心问题：  

1. **表格适配手机屏幕**  
   - 将传统表格拆分为单条记录的卡片式布局，支持左右翻页  
   - 自动处理合并单元格，支持最多 3 层表头展开
2. **性能与兼容性**  
   - 通过 Web Workers 异步解析文件，10MB 以内的 Excel 加载时间控制在 3 秒内  
   - 虚拟滚动技术确保万行数据流畅浏览（实测 iPhone 12 无卡顿）  
3. **零数据风险的隐私设计**  
   - 所有数据处理均在本地完成，关闭页面即清除数据  

这些功能已完整落地在 V1 版本中。  

---

## **02.** 未来计划：需要你的建议

目前收到一些用户反馈，主要集中在两个方向： 
- **小程序版本需求**：网页在移动端仍需要手动输入网址，不够便捷；尤其是我们可以直接把文件在小程序中打开，参考：[开放能力 / 聊天素材打开](https://developers.weixin.qq.com/miniprogram/dev/framework/material/support_material.html)（值得注意的是，Taro V3 相关的接口是错误的，oh yeah 又可以提个 PR 了）
- AI 问答相关，有点像 kimi、智谱清言（btw 文件发送到智谱清言之后并没有自动进入对话框，这是个 bug）等任何大模型产品都会做的，就看谁的效果更好了，而我如果要做表格分析解析，应该会优先选 deepseek-r1 吧

**如果你希望推出小程序版，以下功能哪些对你最有价值？**  
1. AI 问答表格
2. 微信分享单条记录链接  
3. 基础编辑功能（修改数值、添加备注）  
4. 实时协作（显示他人光标位置）  
5. 自动生成简易图表
6. 其他……
欢迎在评论区用编号告诉我你的选择。  

---

## **03.** 开发中的真实挑战

### 1. 要不要 AI Native

这个问题在做的过程中一直摇摆不定。

设想一下，程序拿到了用户的一张 Excel 表格，然后我们想把它们按行变成一个一条条关系记录，这个需求哪些地方是需要 AI 的？

实际拆解下来，会发现，真实的工作流是：
1. 读取 Excel 文件，得到一个 workbook
2. 遍历 workbook，得到可能多张 worksheets
3. 分析每张 worksheet 里的连续块，得到可能多个表格
4. 确定表格的表头行数
5. 遍历数据行，每行分别与表头拼接成一条 record，用于移动视图

猜猜上述 5 个步骤哪些要用 AI，哪些不用？

事实上，只有第四步是比较适合用 AI 的，因为我们可以把表格的前 N 行丢给 AI（比如 deepseek-r1），让它分析哪部分是表头，哪部分是数据区，这个让 AI 来做是再合适不过的。

如果不用 AI 呢？那就有点麻烦了，我们人类一般是通过分析前几行之间的关系，一般可以一下得出结论，所以确实是基于语义的。其次是基于是否有合并单元格或者颜色等。

但我们打开一个文件，分析那么多步，最后只用大模型确定一下表头的行数，这怎么想怎么 hmm…… 怪怪的。

所以这个项目，如果只是为了 pivot 展示的话，AI 暂时不是核心，因此我直接用了一个持久化可修改的整型变量写死了我测试表的表头行数，留待后续再考虑要不要上 AI。

### 2. AI 写 Pivot 功能真地难啊

这个 MVP 原先的预估可能就 4 小时内的工作量，但最后还是花了 12 个小时，很大的一部分工作都卡在了 Pivot 上。

Pivot 就是把横的表变成纵向的，也就是矩阵里的转职。

根据 claude 建议，我一开始使用了 python 生态的 pandas alternative —— nodejs 生态的 danfojs，它有类似 pandas 一样的 API。

可是用着用着，发现它每次 hot reload 都要加载很久，很影响开发体验，每次都一大堆下面这些，老长老长：

```
Platform node has already been set. Overwriting the platform with node.

cpu backend was already registered. Reusing existing backend factory.

The kernel '_FusedMatMul' for backend 'cpu' is already registered

The kernel 'Abs' for backend 'cpu' is already registered

...
```

由于有我愚蠢勤奋的 AI 老哥，我就直接弃坑 danfojs，让 AI 手写转置了。

如果这是一个全密集数组也就罢了，但我特地找了一个表头有合并单元格、表数据也有合并单元格，甚至还有一些数据异常的表，这就麻烦大了。

我一开始想用无脑的自动向下向右填充算法，这会导致若一个单元格为空且独立，但上方或者左方有值，则会被填充，这与人类实际表格中当且仅当处于被合并单元格时才可被填充的条件是不一致的。

但 Anyway，我让 AI 去做 pivot，去写 fill 的时候，它竟然主动地去分析了 row-span 和 col-span，这样精确知道了哪些是待合并单元格，从而写出了相对稳健的算法。

但尽管如此，我还是卡了好几个小时，中途实在憋不住……

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010537658.png)

因为我的产品比较苛刻，我希望在标准视图下保留所有的合并单元格等，但在移动端视图（转置）下，表头的合并单元格要保留，但数据行的值要获取实际值，这就把 AI 难倒了，所有的 AI 无论是 claude、gpt-4o 还是 deepssek-r1，都拜下了阵来。

后来我自己亲自 log 调试，确认了：
1. 它有时候分不清填充的方向是向左还是右是向上还是下
2. 它在转置的时候并没有把 row-span 转成 col-span，把 col-span 转成 row-span
3. 数据行需要在生成移动视图之前需要先全部填充完毕，但拷贝一份新的显然性能不够高效，于是我给每个单元格加了一个 `realValue` 的 field，这样就可以在 O(n) 的复杂度下把所有的单元格的两种状态都确定了

所以在亲自指点它正确的解决方案之后，它才终于顺利地完成作业：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010539717.png)


总之，AI 整体比较稳定，偶尔有惊喜，偶尔也是笨的要死。前一个偶尔也许为我节省了十分钟时间，但后一个偶尔就要耗去我数小时。

但如果没有 AI 呢？

也许我一天都写不完写不对这个，或者直喊：“好无聊啊，谁来找我玩啊”……

### 3. 各种宕机

美缝夜晚的 Windsurf：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010551901.png)

都几个月过去了还没修好 markdown 排版的 cursor：

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010553594.png)

真是难兄难弟啊！

但我才是真难啊！

---

## **04.** Windsurf 的 DeepSeek 上新体验

今天 DeepSeek 也第一时间上架了 windsurf 系统内，处于 Beta 模式，V3 价格是 claude 的 1/4，R1 则是一半。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010541438.png)

在我做表格展示部分时，由于 claude 始终不能给出满意的结果，所以中途换了 DeepSeek R1，结果分析地有模有样，效果还是有一点，虽然没有根本性地解决问题。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010543639.png)

但是。

但是 windsurf 里的 DeepSeek R1 有 bug，它会推理且输出答案后，无限重复，也就是继续推理继续输出答案…… 根本不能停！

这……

我真地很想问候一下 windsurf 团队集体……

所以，只能放弃使用。

而 V3，我个人觉得应该会比 claude 略逊一筹，简单试了试，没有特别大效果，我就还是 all in claude 了。

所以，生产力场景还是难埠啊！

而且 cursor 还没上新。

这几天 DeepSeek 的 API 网站文档等全是宕机状态，API 很多小伙伴反馈也不稳定（尽管我个人觉得还好，再次感谢黄 sir！），但有一个令人振奋的好消息！

那就是硅基流动率先上新 DeepSeek 啦！大家可以充值用，这下应该不会崩溃了： https://siliconflow.cn ！

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010548916.png)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010548523.png)


---

## **05.** 写在最后

这个项目的代码已完全开源，欢迎访问 [GitHub 仓库](https://github.com/markshawn2020/tabee) 交流或贡献代码。  

此刻的 TaBee 仍是一个粗糙的工具，但如果你也遇到过手机看表格的困扰，不妨试试这个方案——**它可能不完美，但足够真诚**！

如果你对 Tabee 的小程序版极其感兴趣，千万记得要点赞分享转发哦，因为我会根据大家的需求决定要不要再花一两天时间给大家把小程序版本实现出来！（尽管已经写了一个 V0.0.1……）

![IMG_7836.PNG](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010603169.PNG)

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/202502010556992.png)