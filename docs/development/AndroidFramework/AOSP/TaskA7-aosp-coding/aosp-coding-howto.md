# aosp coding howto

## use `androidmk` to change `mk` file into `bp` file

path: `out/soong/host/linux-x86/bin/androidmk`

```sh
# create soft link
ln -s out/soong/host/linux-x86/bin/androidmk androidmk
```

ref:

- official intro:[Soong 编译系统  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/setup/build?hl=zh-cn)

- [android mk 与 bp,Android.bp 你真的了解吗\_方萌-CFT 的博客-程序员信息网 - 程序员信息网](https://www.i4k.xyz/article/weixin_34342589/117589957)

- [(23 条消息) Android.bp 入门指南之 Android.mk 转换成 Android.bp_IT 先森-CSDN 博客\_android.mk 转 android.bp](https://blog.csdn.net/tkwxty/article/details/104411520)
