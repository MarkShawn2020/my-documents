# ios 逆向

ref:

- [iOS 砸壳总结 - zeinber's Blog](https://blog.zeinber.top/post/reverse/ios-dumpdecrypt-summary/)

## MonkeyDev

### instruction

install: - [安装 · AloneMonkey/MonkeyDev Wiki](https://github.com/AloneMonkey/MonkeyDev/wiki/%E5%AE%89%E8%A3%85)

### FIXED: `failed to connect to 'raw.githubusercontent.com'`

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/git-bugfix-1653568601761-9ad778546157b9c8b629105174dd99e937524a029f837b99f0aaf66d26847741.png)

ref:

- [Failed to connect to raw.githubusercontent.com:443 - 知乎](https://zhuanlan.zhihu.com/p/115450863)

- [raw.Githubusercontent.com ᐅ Learn more about Githubusercontent](https://ipaddress.com/website/raw.githubusercontent.com)

### FIXED: `xcode 12 Types.xcspec not found`

solution:

```sh
ln -s /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/Library/Xcode/PrivatePlugIns/IDEOSXSupportCore.ideplugin/Contents/Resources /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/Library/Xcode/Specifications
```

ref:

- [xcode 12 Types.xcspec not found · Issue #266 · AloneMonkey/MonkeyDev](https://github.com/AloneMonkey/MonkeyDev/issues/266)
