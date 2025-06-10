# ios

1. [短信拦截](#短信拦截)
   1. [方法 1：回 0000 或者 00000 退订](#方法1回0000或者00000退订)
   2. [方法 2：启用 sms 过滤中介](#方法2启用sms过滤中介)
      1. [app：VeroSMS（可能不支持中文关键词）](#appverosms可能不支持中文关键词)
      2. [app：短信别烦我（免费）](#app短信别烦我免费)
      3. [sms 过滤中介原理](#sms过滤中介原理)
   3. [自己开发 sms app 的可行性](#自己开发sms-app的可行性)
2. [一键换装方法汇总](#一键换装方法汇总)
   1. [辅助触控，不可行](#辅助触控不可行)
   2. [Frida 方案，不确定](#frida方案不确定)
3. [Appium + WebDriverAgent](#appium--webdriveragent)
   1. [TODO: session id null](#todo-session-id-null)
   2. [FIXED: 解决 13.3 高版本 xcode 提示 Could not build module 'RoutingHTTPServer' 导致不能编译](#fixed-解决133-高版本xcode-提示could-not-build-module-routinghttpserver-导致不能编译)
   3. [FIXED: 返回的 json 串 sessionId 为什么是 null](#fixed-返回的-json-串-sessionid-为什么是-null)

## 短信拦截

### 方法 1：回 0000 或者 00000 退订

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/iOS-1655514768908-acb9577fd8fb0c4bf4258715785dedb2f36ca37af050c6f50fc95aad5eab0166.png)

实测好像没反应，看 B 站的某些视频用的是移动的号码，我是电信的，不知道是否是因为电信没有此类服务。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/iOS-1655514852927-5971ab98ef757a6e77353114f7dbdab6d6c8d8560004ea181cd9e458d7950bac.png)

我们不知道到底有没有起作用，也无法验证，不能坐以待毙，继续寻求新的方法。

### 方法 2：启用 sms 过滤中介

#### app：VeroSMS（可能不支持中文关键词）

在 [Can I block all messages with a specific word in them? : ios](https://www.reddit.com/r/ios/comments/cqq8dn/can_i_block_all_messages_with_a_specific_word_in/)、 [Blocking words in iMessage - Apple Community](https://discussions.apple.com/thread/251286779) 中给出了使用“VeroSMS”这款 app 的方案。

它的使用方法如下：- [How To Automatically Block Spam SMS By Keyword on iPhone (No Jailbreak)](https://www.rushlywritten.com/2020/01/how-to-block-spam-sms-text-by-keywords-iphone.html)，但我实测下来可能有不支持中文关键词的问题。

#### app：短信别烦我（免费）

于是寻求中文解决方案，在 [搞定 iOS 骚扰短信，用这几款 App-什么值得买](https://www.smzdm.com/p/12707913/) 中介绍了三款 app：“黑白短信”、“熊猫吃短信”、“短信过滤+”。

前面两款都是收费的（不过很便宜），第三款软件说是免费的（但点了一下其实还是要收费，6 元）。于是我在 app store 里搜了一下，确实搜到了熊猫吃短信，接着找到了一款免费的“短信别烦我”，设置了一下，感觉还行：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/iOS-1655514871238-8d3de8507b552ae218b6edc95ba5d9d4fc98489ef33f891c3f237b4d5ec2b91e.png)

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/iOS-1655514880599-940ffaea957eeff94b474f02833f5a16b2bd9498bfae6e7b884bea6be3f25165.png)

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/iOS-1655514885510-7a7fc65f8d4dc16ce0d42e7a34028209dd0fa93491a546df840ec08a029f189e.png)

#### sms 过滤中介原理

ios 的系统限制，必须设置一个 app 作为 sms 消息过滤中介，也就是说，不下载（或自己开发）app，无法启用 sms 过滤功能，只能将不在收件人列表中的短信统一归类（还只是 filter 不算 block）。

因此下载 app 是必须的，我试了两款，一款是 verosms，好像是 apple 论坛回复的，但目测对中文支持不行，测试貌似没反应；一款就是这个免费的”短信别烦我”了。

但是由于 ios 的沙盒限制（见：- [iOS Messages reading using swift | Apple Developer Forums](https://developer.apple.com/forums/thread/7912)），任何一款 app 都无法获取其他 app 的具体信息，也就是我们无法开发一个 app 去获取所有已经受到的短信，然后对他们进行分类、拦截，所以 sms app 早用早受益，因为它只可以拦截新收到的消息。

其具体原理，在你设置拦截规则后，sms 中介会将目标号码加入系统拦截列表，后续目标号码的短信就会首先被系统拦截，而无需再经过 sms app；只有当你向该目标号码发送三次短信或者加入联系人方可解除拦截。也就是触发的时候是从 app 向下报给系统，响应的时候是从系统往上再到 app。

### 自己开发 sms app 的可行性

感觉没有必要，但可以参考下面的一些文章，它们用了`CallKit`，不清楚对 Message 是否有用。

- [BCSingh/CallBlocker: An iOS call blocker sample app in Swift using CallKit.](https://github.com/BCSingh/CallBlocker)

- [iOS / Swift: Is it possible to block some incoming calls with CallKit for a specific country? - Stack Overflow](https://stackoverflow.com/questions/61729138/ios-swift-is-it-possible-to-block-some-incoming-calls-with-callkit-for-a-spec)

- [ios - blocking phone number in call kit - Stack Overflow](https://stackoverflow.com/questions/53663184/blocking-phone-number-in-call-kit)

## 一键换装方法汇总

### 辅助触控，不可行

按道理，辅助触控理论上是可行的方案，但很遗憾的是，ios 的辅助触控在依次录制多个手指后，会统一起来同时运行，这与我们一步步操作的目标是不一样的。因此不可行。

ref:

- [在 iPhone 上使用辅助触控 - Apple 支持 (中国)](https://support.apple.com/zh-cn/guide/iphone/iph96b21954/ios)

### Frida 方案，不确定

如果我们直接将手机越狱，然后再使用类似按键精灵的脚本，完全是可行的，但是成本太高了。

如果不越狱，是否也可以基于 frida 实现呢？也许可以，在 [iOS | Frida • A world-class dynamic instrumentation framework](https://frida.re/docs/ios/#without-jailbreak) 里描述了越狱和非越狱两种情况下分别使用 frida 的办法，但是很复杂，我没怎么明白，留待以后研究吧。

## Appium + WebDriverAgent

主要参考：

- [IOS + Appium 自动化教程 - 简书](https://www.jianshu.com/p/da1e00777273)

- [非常重要，不然就放弃了！：WebDriverAgent 重签名爬坑记 - 温一壶清酒 - 博客园](https://www.cnblogs.com/hong-fithing/p/15203980.html)

- [How to Trust an App on iPhone & iPad to Fix “Untrusted Developer” Message](https://osxdaily.com/2021/05/07/how-to-trust-an-app-on-iphone-ipad-to-fix-untrusted-developer-message/)

- [iOS 自动化之 WDA（WebDriverAgent）安装及踩坑（本文仅作经验记录，原 WDA 已经废弃，详细请看更新说明）\_杨小扬的专栏-程序员资料\_wda 安装 - 程序员资料](http://www.4k8k.xyz/article/xlyrh/108410738)

### TODO: session id null

- ["sessionId" : null - Support - Appium Discuss](https://discuss.appium.io/t/sessionid-null/32175/3)

### FIXED: 解决 13.3 高版本 xcode 提示 Could not build module 'RoutingHTTPServer' 导致不能编译

resolution: 将 assign 改成 unsafe_unretained 重新编译 成功

ref:

- [(5 条消息) 解决 13.3 高版本 xcode 提示 Could not build module 'RoutingHTTPServer' 导致不能编译\_Oh_MyBy 的博客-CSDN 博客](https://blog.csdn.net/Oh_MyBy/article/details/103895366)

### FIXED: 返回的 json 串 sessionId 为什么是 null

ans:

新版的 WDA 就这个样子

ref:

- [返回的 json 串 sessionId 为什么是 null · TesterHome](https://testerhome.com/topics/23554)
