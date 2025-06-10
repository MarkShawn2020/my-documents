# 微信小程序开发

## UI 框架

see: - [8 个最热门的微信小程序 UI 组件库 - V2OA - Way To Office Automation](https://v2oa.com/archives/3/)

### 基于 vue

比较推荐的框架是 `weui` 和 `colorui`，其中直接用微信开发工具其实无法获得自动补全的功能，但是可以使用 HBuilderX 这款软件。

![在HBuilderX中可以对`weui`进行自动补全](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/weapp-dev-1656383048007-b3ec18d7dee03f441494ef939c15ea67a326ef00eb8e52cc309c175901b6f75d.png)

![在微信开发工具中不可以对`weui`进行自动补全](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/weapp-dev-1656383051926-0b9d3c66753fb388346443e89ec6764f3cc3f5357b0b26720bc23e8b72a17212.png)

所以使用`HBuilderX`加上一套主流小程序 UI 框架，然后基于 typescript 与 vue 将有不错的开发体验。

或者就要使用基于 react 的 taro 框架了，不过小程序端就缺少高质量的 ui 组件。

### 基于 react

据说 vant 是 gitee 年度最有价值开源项目之一：[小程序 UI 框架推荐：Vant 让你优雅的飞\_牛客博客](https://blog.nowcoder.net/n/e9e2bc2bbbba483aac52ecb6e9d878b8?from=nowcoder_improve)

我看了一下好像确实不错：[Field 输入框 - react vant](https://react-vant.3lang.dev/components/field)

反正比 taro-ui 要好很多，而 weui-wxss 又很难用。
