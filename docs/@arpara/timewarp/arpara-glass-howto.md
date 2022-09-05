# arpara glass howto

## connect to mac

### refresh rate setting

Mac 2020 pro 只支持最高 60Hz 的分辨率，最新款 M1 才支持`ProMotion`技术。允许在 24-120Hz 之间自动切换。

> :warning: 关于 mac 上测试 arpara 眼镜的一点问题
>
> 1. 尽管我的 mac 屏幕本身可能不支持 120Hz，但是不影响对眼镜输出的分辨率，我测试了眼镜端 2d 模式下只可以`1920 * 1080 * 60Hz`，但`1920 * 1080 *120Hz`会闪屏无法使用；3d 模式下`3840 * 1080 * 60Hz`、`3840 * 1080 * 120Hz`、`5120 * 2560 * 30Hz`都是可以的，但`3840 * 1980 * 60Hz`会闪屏无法使用。是不是有点诡异？我感觉是眼镜的驱动程序有问题，如果是刷新率不能过高，这无法解释为什么 3d 模式下`3840 * 1080 * 120Hz`可行；如果是屏幕尺寸有要求，这无法解释为什么 3d 模式下`5120 * 2560 * 30Hz`可行。
> 2. 另外一个问题就是 3d 模式下的屏幕表现不符合预期。理论上 3d 模式下，应该是把屏幕分成两半（试想一下一个普通的 vr 视频，其实是把左右（或者上下）两个镜头拼起来放在一个视屏里）分别送给眼镜的左右镜渲染，但现在的问题是两个眼镜还是分别渲染了整屏，所以实际上等价于 2d 模式。我是不是缺少安装什么驱动？或者只能在特定的 app 里运行？
> 3. 分辨率的切换（也就是眼镜左下角的两个按钮）的时长也许可以接受，但是切换导致屏幕闪屏无法使用（以至于弹窗都无法合成）这里必须优化，我也是花了好长时间才意识到“出现炸屏后可以无视，继续按键切换模式”这个骚操作的，但是对于用户来说，就很不友好，很容易产生眼镜坏了的错觉。

设置分辨率在 `SystemSettings | Displays`下。参考： [Change the refresh rate on your MacBook Pro or Apple Pro Display XDR - Apple Support](https://support.apple.com/en-us/HT210742)

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/arpara-glass-howto-1643718320844-479c3df090b1e1f31a5df30f1d1c1fc40c34e943d53c8e96b551a656988641f1.png)

> :warning:如果没有那个`Refresh Rate`选项，可以按住`option`键，再单击`Scaled`（奇葩设定）。参考： [I can't find variable refresh rate in mac… - Apple Community](https://discussions.apple.com/thread/252060401)

- ref：
  - what's ProMotion: [What is ProMotion? Apple's killer screen tech explained](https://www.trustedreviews.com/news/what-is-promotion-apple-4132359)
  - Does Mac 2020 support 120 hz? [120 hz for Intel MacBook Air 2020? : mac](https://www.reddit.com/r/mac/comments/kh030u/120_hz_for_intel_macbook_air_2020/)
