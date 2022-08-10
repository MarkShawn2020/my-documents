# frameworks howto

## instruction

- [(19 封私信 / 66 条消息) Android Framework 如何学习，如何从应用深入到 Framework？ - 知乎](https://www.zhihu.com/question/46486807/answer/1724325999)

- :sparkles: 教会你`hmm | godir | jgrep | cgrep`的使用[Tutorial: Diving into Android Source Code - YouTube](https://www.youtube.com/watch?v=NsqFOSzoYE8&t=120s)

- :sparkles: :sparkles: 教你用 gdb 调试 Native C++代码 [GDB 在線調試 Android Framework Native C/C++代碼-软件开发平台及语言笔记大全(超详细)](https://www.cntofu.com/book/46/android_note/gdbzai_xian_diao_shi_android_framework_native_c__c.md)

## AOSP

## IDE review java frameworks

### compile `idegen`

use `bash` (not `zsh`, otherwise the script won't pass, see: [mmm 编译模块报错 Couldn't locate the directory - 简书](https://www.jianshu.com/p/2a4731385773))

```sh
bash
source build/envsetup.sh && lunch rk3399_Android10-userdebug

mmm development/tools/idegen
```

### config `ulimit`

otherwise, the android studio would complain the logs (each module would) and it would be rather slow to index (more than half of hour or more).

```sh
echo "ulimit -S -n 2048" >> ~/.bashrc

bash
source ~/.bashrc
```

ref:

- [Android Studio 调试 Android Framework 层代码 - 知乎](https://zhuanlan.zhihu.com/p/295363172)

### android-studio `.vmoption` config

ensure the place.

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/source-code-insiight-1644589276145-6355a0fabcb222d1f85a965635bd965a11382b02e77f48b69062a30c4a3deeb9.png)

ensure not some wrong configs (like spell errors)

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/source-code-insiight-1644589315281-ce2d0704b9928321b451ec4098cb98d4f3f5dc0ea3f6a9678460960a6f48982b.png)

see:

- [Unrecognized VM option 'UseCompressedOops ' – IDEs Support (IntelliJ Platform) | JetBrains](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360004340840-Unrecognized-VM-option-UseCompressedOops-)

### android-studio `inotify limit` config

```sh
echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
```

ref:

- [performance - Android Studio shows the warning inotify limit is too low - Stack Overflow](https://stackoverflow.com/questions/33959353/android-studio-shows-the-warning-inotify-limit-is-too-low/56756211)

### use custom framework/jdk

see:

- :sparkles: :sparkles: :sparkles: 一篇非常详细的文章：[Android Framework 调试 | River Young](http://riveryoung.cn/2020/12/09/Android-Framework-Debug/)

- 有些地方不是很清楚：[Android Studio 调试 Android Framework 层代码 - 知乎](https://zhuanlan.zhihu.com/p/295363172)

### use `facets/gradle`

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/source-code-insiight-1644583979433-a190875f6a0fee43a3088913057cf07379166f6d9e9925f609d721590bb8eee0.png)

看起来很有效：

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/source-code-insiight-1644584892009-cf9b9116092580e9be6b7407c15d4e67adb461017270db9a843db3ad17d3d7d8.png)

see:

- 配置智能提示：[Frameworks detected in android studio - Stack Overflow](https://stackoverflow.com/questions/33231460/frameworks-detected-in-android-studio)

### debug java frameworks

ref:

- :sparkles: :sparkles: 这个不错，里面讲了很多种办法，比如日志断点！值得学习！ [Android Studio 你不知道的调试技巧 | Weishu's Notes](https://weishu.me/2015/12/21/android-studio-debug-tips-you-may-not-know/)

- [Android Framework 调试 | River Young](http://riveryoung.cn/2020/12/09/Android-Framework-Debug/)

## IDE review native frameworks

### read native Frameworks

1. 打开以下开关，编译时就会自动生成 `**/CMakeLists.txt`

```sh
SOONG_GEN_CMAKEFILES=1 SOONG_GEN_CMAKEFILES_DEBUG=1
```

目录在 `out/development/ide/clion/frameworks/native/**/CMakeLists.txt`

2. 在`clion`中打开 `CROOT/frameworks/native`，此时是没有智能提示的

3. 在`clion`中引入我们的根目录`cmake`文件，也就是`out/development/ide/clion/frameworks/native/CMakeLists.txt`

4. 标记我们`Project`视图下的根目录为`Root for Headers and Sources`

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/source-code-insiight-1644610581905-27d806130ee09121eab597bcfb7861ea3259f5135c75c44005a032a53f8a8f9d.png)

5. 重启 IDE，等待索引更新完成，然后自动跳转就配好了！芜湖起飞！

!!!warning 注意，貌似基于`SOONG_GEN_CMAKEFILES`生成 `CMakeLists.txt` 的方式，开销还是很大的，所以编译较慢（感觉慢了两三倍），所以如果 api 没有什么大变动，编了一次后下次就不要启用了。所以比较合适的是不要导出……

---

TODO: 但是我后来发现，还不够。 编译自动生成的 `CMakeLists.txt` 里包含的库补全，需要自己手动添加目标库。然后这些库的 cpp 文件就会都罗列在项目根目录下，至于为啥不是树状结构，是因为这些都是引用，并且来自不同的目录结构。

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645591398752-6e0ca8269ca425919dbb14fa129d684a4e99effafccf0f06b586220d59f673ea.png)

ref:

- [如何顺滑地查看 Android Native 代码 | HansChen 的博客](http://blog.hanschen.site/2019/10/11/aosp-native-ide/)

### 导入 `out/**/CMakeLists.txt` 工程后的编译

在编译过程中，由于和安卓默认编译环境不一样，可能会存在各种各样的问题，尤其是语法问题。

涉及到语法问题，简单检查会发现，一般都不是什么大问题，因此就要把他们屏蔽。

办法就是修改对应的 `CMakeLists.txt` 文件，整个文件分成自己包库与依赖包库，一般是在依赖包库会出现问题，在最后面的 `CXX-FALGS` 后面一次次编译补上所需要的屏蔽条件即可，例如我在编译 `libsurfaceflinger` 中，要补全的条目如下：

```cpp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-int-float-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder-init-list")
```

## debug native frameworks

ref:

- :sparkles: :sparkles: :sparkles: 【绝对推荐】一定要掌握 [如何调试 Android Native Framework | Weishu's Notes](https://weishu.me/2017/01/14/how-to-debug-android-native-framework-source/)

- (CSDN 版，可能是同一个人) [(1 条消息) 如何调试 Android Native Framework_android 的博客-CSDN 博客\_android native 调试](https://blog.csdn.net/sinat_29384657/article/details/76685742?ops_request_misc=&request_id=&biz_id=102&utm_term=android%20studio%20native%20%E8%B0%83%E8%AF%95&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-76685742.pc_search_result_control_group&spm=1018.2226.3001.4187)

### 生成 debug 版本的 framework 文件

- [android ndk - How to make debug build of specific module under AOSP tree? - Stack Overflow](https://stackoverflow.com/questions/21447675/how-to-make-debug-build-of-specific-module-under-aosp-tree)

### debug `.so` file

- [Android 动态调试 so 文件 - 知乎](https://zhuanlan.zhihu.com/p/58468014)

- [第九章 Android 原生程序动态调试（二）（lldb 调试器） - 极客分享](https://www.geek-share.com/detail/2798359447.html)

- [(1 条消息) 第九章 Android 原生程序动态调试（二）（lldb 调试器）\_zlmm741 的博客-CSDN 博客\_android lldb](https://blog.csdn.net/zlmm741/article/details/105538556)

### debug native

以下三篇应该是一样的：

- [如何调试 Android Native Framework - 知乎](https://zhuanlan.zhihu.com/p/24867284)
- [tiann/android-native-debug: Debug Android Framework Native Code Tutorial.](https://github.com/tiann/android-native-debug)
- [如何调试 Android Framework？ | Weishu's Notes](https://weishu.me/2016/05/30/how-to-debug-android-framework/)

- [LLDB 调试 Android Native 程序 - Coding&Life - 博客园](https://www.cnblogs.com/ciml/p/14154668.html)

- [(1 条消息) 【安卓 framework 实战】使用 lldb 调试 Android native 源码\_nianxing123 的博客-CSDN 博客](https://blog.csdn.net/qq_23542165/article/details/121275404)

- [【安卓 framework 实战】使用 lldb 调试 Android native 源码 - 简书](https://www.jianshu.com/p/3eb6315cb710)

- [安卓底层 native 代码的调试 - 掘金](https://juejin.cn/post/6994708442233946119)

### LLDB relative

- [LLDB 调试和实战 - 简书](https://www.jianshu.com/p/8a9fd3b2b9ae)

- [LLDB 使用详解以及断点调试教程 - 掘金](https://juejin.cn/post/6844903794740822029)

- [There is no LLDB in sdk manager in android-studio - Stack Overflow](https://stackoverflow.com/questions/61649693/there-is-no-lldb-in-sdk-manager-in-android-studio)

- [macos - LLDB Error: Unable to resolve breakpoint to any actual locations - Stack Overflow](https://stackoverflow.com/questions/31122871/lldb-error-unable-to-resolve-breakpoint-to-any-actual-locations)

### FIXED: `ld.lld: error: undefined symbol: graphic_policy(int)`

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588183041-6643592b34632faef340ffe8a6f9baa7597d40faf43c97daffb862cb6e37256f.png)

这个原因，我具体也不清楚，因为一是以前没有单独编过`native`，二是后来又改了很多 `surfaceflinger` 部分，看这外部的报错信息，似乎正与我改的部分有关，但具体到内部又发现似乎无关……

所以我目前的做法就是先把它注释掉，这看起来好像影响不大……

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588365881-e75c80d6ffb6606d4b6b3fb638e47a1a49a406b549428071142ea9bd0343f66d.png)

然后重新编译，目前似乎一切都很正常！

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588403242-61bab44d027d5b9b2b3b5096c421502c1a2aac970732de2125f0aef3588adb31.png)

## 属性详解

### 官方参考

- [将系统属性作为 API 实现  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/devices/architecture/sysprops-apis)

### 系统属性解决方案对照表

| - | native get | native set | java get/set | adb get/set | note |
| --- | --- | --- | --- | --- | --- |
| define `persist.XXX` in `SurfaceFlingerProperties` | Y | Y | Y(maybe?) | N | 已查 se 策略中 sf 不允许 adb 使用 |
| define `persist.XXX` in `device/**.props` | Y | N | Y(maybe?) | Y | db 修改后，sf 中似乎依旧是旧值 |
| define `persist.XXX` both in `SurfaceFlingerProperties` and `device/**.props` | Y | Y(maybe?) | Y(maybe?) | Y | 1. 感觉有些繁琐，2. 也许应该独立写个 sysprops 而非写进 `SurfaceFlingerProperties`（因为那是属于平台的） |

### 属性命令

```sh
adb shell getprop

adb shell setprop

# 监控所有属性
adb shell watchprop
```

ref:

- [(1 条消息) Android 实用技巧之 adb 命令：getprop，setprop，watchprops 命令的使用\_寒江蓑笠的专栏-CSDN 博客\_adb setprop](https://blog.csdn.net/heqiangflytosky/article/details/69432749)

### 属性列表

```text
// File: sysprop.proto

syntax = "proto3";

package sysprop;

enum Access {
  Readonly = 0;
  Writeonce = 1;
  ReadWrite = 2;
}

enum Owner {
  Platform = 0;
  Vendor = 1;
  Odm = 2;
}

enum Scope {
  Public = 0;
  Internal = 2;
}

enum Type {
  Boolean = 0;
  Integer = 1;
  Long = 2;
  Double = 3;
  String = 4;
  Enum = 5;

  BooleanList = 20;
  IntegerList = 21;
  LongList = 22;
  DoubleList = 23;
  StringList = 24;
  EnumList = 25;
}

message Property {
  string api_name = 1;
  Type type = 2;
  Access access = 3;
  Scope scope = 4;
  string prop_name = 5;
  string enum_values = 6;
  bool integer_as_bool = 7;
  string legacy_prop_name = 8;
}

message Properties {
  Owner owner = 1;
  string module = 2;
  repeated Property prop = 3;
}
```

### 属性在 adb 中的访问

由于 `surfaceflinger_display_prop` 被配置了除了 `init` 和 `surfaceflinger` 都不可以访问，所以 adb 是无法获取信息的。

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644961947306-365a2ba35a5553755d4d32e08685dacc3c8fa442e74c22cc3b76fa3107933f23.png)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644962007430-63053d9457f81699f582c2d933e4b7629c6fbd02d647bbb01706d67373eb4c02.png)

因此我们最好自定义一个配置项。

### 属性在代码中的访问

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644956365781-f7faee0f87bea20047027cf2544874972ed15f499de8971cbdd5769c3f8b6cd5.png)

### `SystemProperties` 和 `SettingsProvider`

目前看到最详细的一篇文章：- [(1 条消息) Android 系统属性读取和设置详解\_wenzhi 的博客-CSDN 博客\_android 系统属性的读取和设置](https://blog.csdn.net/wenzhi20102321/article/details/120029551)， 这里面重点对比了 `SettingsProvider` 和 `SystemProperties`的读取问题。

其中，`SystemProperties` 既可以在 C++中调用，也可以在 Java 层调用，因此是最适合我们 `surfaceflinger` 的修改目标的。

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644954678894-2184d72cee016ae198e398c77e4365a038f279c7b4a91b3648fc7a5c004bcc34.png)

在 JAVA 中调用 `SystemProperties`:

!!! tip 如果是调用 `surfaceflinger` 的属性，即 `surfaceflinger/sysprop/SurfaceFlingerProperties.sysprop`，则在 java 中要定义为 `android.sysprop.SurfaceFlingerProperties`，如下： ![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644955082677-1b15e5eb9ae9419a5fe94569e30d394eebcfe8610ff8ba0295cc8d1781118b9c.png)

```java
import android.os.SystemProperties; //需要uid系统权限


//读取
String SystemProperties.get(String key)；
int SystemProperties.getInt(String key, int def)
long SystemProperties.getLong(String key, long def)
boolean SystemProperties.getBoolean(String key, boolean def)

//设置
void SystemProperties.set(String key, String val)
```

在 C++中调用 `SystemProperties`:

cpp++ //读取数值 char flag[PROPERTY_VALUE_MAX]; property_get("persist.sys.camera.port", flag, "0"); int port = flag[0] - '0'; //适用于 flag 字符串数值小于 10 的情况

//设置 property_get("persist.sys.camera.port", "0");

```

### TODO: 配置系统全局固定属性

我先尝试了在`device`中添加属性。

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644986544796-882285542154ae30c7c129ae88ac8affb8d9853f3cf0e98b1135441a4999bb89.png)

我后来发现在`/system/libsysprop`下定义了很多属性，并且有在`adb shell getprop`中能找到的，比如：`gsm.network.type`。

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644988047702-11880135ad9bea5c57f480e13240046c826a7d7194e79597e8ef6f8a802cb29b.png)

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644988112942-0601bf85ddc25e97e359f58ab3bdd5fe9330d14a6c4b200b888cdce26528304d.png)

这个模块的 `Android.bp` 其实很简单，就是把目录下的所有 `.sysprop` 文件都加载。

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644987990277-670cf265944ab6b555e1355d089659e20b72afcb4e84172b1ea676c9b115229d.png)

### `SystemProperties` 逻辑

而在这篇文章：- [(1条消息) Android 知识点 040 —— setprop persist.属性_adc-CSDN博客](https://blog.csdn.net/yush34/article/details/105275120) 中介绍了 `SystemProperties` 的程序逻辑。

属性文件读取的顺序依次为：` /default.prop -> /system/build.prop -> /system/default.prop -> /data/local.prop`

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644955172003-4ea039f8e85c0cd621f691954558e845a8a95ae8593a4dcef49da77ccab4c982.png)

其中 `persist.` 开头的将有写入动作（并且重启后不会重置）：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644955251254-1c27ee0e9857690399cf0534803c7620bdba6f542d3acdb5aa331901c66fce0f.png)

### `SystemProperties` 可配置区域

根据这篇文章：- [Android 添加自定义系统属性_marton_13的博客-程序员秘密 - 程序员秘密](https://www.cxymm.net/article/qq_27256793/80455514) 介绍到了一个其他文章没怎么提到过的在 `system/core/rootdir/int.rc` 里配个人自定义属性：

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644955753951-c879eec8b7fd881d71dca82deb4df048e5e8209f90890dda8622fca9b2783754.png)

FIXME: 我查了一下，这里确实有配属性的，不过不多，而且好像还和是否 `persist` 的逻辑混在一起，你也不清楚如果在这里定义 `persist.` 变量是否有效，因为有可能在生效函数之后。

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644955843838-59901699d2a7d917cbcdfc8cf863b9c3a9242240177fd0dd3c9ae48ff081ef1c.png)

### 在 `build.prop` 中配置实例

这篇文章挺推荐：- [Android系统开发入门-3.添加系统属性 | 一叶知秋](http://qiushao.net/2019/11/20/Android%E7%B3%BB%E7%BB%9F%E5%BC%80%E5%8F%91%E5%85%A5%E9%97%A8/3-%E6%B7%BB%E5%8A%A0%E7%B3%BB%E7%BB%9F%E5%B1%9E%E6%80%A7/)， 里面说了 Android 9.0 之后google不推荐把property直接加载 `/system` 分区，否则一定要在 `BoardConfig.mk` 里继续配置。

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644956628048-67fecc6f07edc248a2306332452914807a7f3e880e70ea1c36461e15b9b469fa.png)

在这篇文章：- [(1条消息) 02 Android系统之添加系统属性_本末实验室-CSDN博客_android 添加系统属性](https://blog.csdn.net/feit2417/article/details/105209725) 中，介绍了在 `/system/build.prop` 和 `/vendor/build.prop` 下配置属性并编译的方法：

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644956067014-b8b68a62375d4d06fcdc6f6a35793075686d98e942850db5d1e02ca2e5edc7a4.png)

FIXME: 这种直接写进 `build.prop` 并烧录的办法，肯定是可以通过 `adb shell getprop` 读到了，但是c++代码和java代码里怎么读呢？

### FIXME: 修改完sysprop后api不匹配的问题

修改了模块的sysprop之后，重新编译整机会有api不匹配的问题。

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1644747304677-4be7f7fdbf1e0755f93dc2727db6c652ad79244b90886433ca679fad88830f11.png)

根据提示更新即可。

TODO: 在这之后，或许就可以用`adb shell getprop`的方式获得这些属性信息了。
```
