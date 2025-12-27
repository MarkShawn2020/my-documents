

访问 https://docs.github.com/en/graphql/overview/explorer ，使用 GraphQL Explorer：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/567779cf576930fb5855355195cc8dfc.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

点击登录授权，还可以获得所有的组织权限。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/904a9c6162c0ef417fb57a808d223684.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

怎么用呢？

最好的一点是按 `shift+space` 或者 `ctrl+space` 的自动补全功能。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a6e0b2f28b9d7faea20f5463bb8da7c7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

比如要罗列 repo 列表就是输入 repositories，如果有报错，会提示，一看就明白。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3735bb5e6c961dda510ff77ec931b151.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

注意，它是一个图检索，所以会有边和结点的概念。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/747170ac937976df5767ae2fe3e73f9d.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

按住 cmd 后这些变量会支持跳转，可以跳转到文档，非常方便！！！

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/449e4c6fc7847f5502dcc596504650d4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

如果实在不知道怎么写，还可以直接问页面上的 AI。

看来无法直接通过repo获取commits统计（需要分页或许所有commmits，这个代价有点高）。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/169274eb370b067f1b1c414293b8d974.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

也不支持api级别获取insights。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/4acb20d08e6b09405b215dfc09ffe8eb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

看来我们只能通过先获取所有commits，再聚合了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9f5656dcdf4f342909c9c2cc69653a3f.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

也支持 graphql：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/3be91c4fb6090952fbad6640a939340d.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但感觉是错的：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/94b99256e577e0f7203c60ddc25fd656.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---

可以先升级一下 gh：

```shell
➜  ~ gh --version
gh version 2.73.0 (2025-05-19)
https://github.com/cli/cli/releases/tag/v2.73.0

➜  ~ brew upgrade gh
……
gh 2.73.0 -> 2.76.1
……

➜  ~ gh --version
gh version 2.76.1 (2025-07-23)
https://github.com/cli/cli/releases/tag/v2.76.1

```



