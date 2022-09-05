
## howto change `mk` file to be `bp` file

### use `androidmk`

path: `out/soong/host/linux-x86/bin/androidmk`

```sh
# create soft link
ln -s out/soong/host/linux-x86/bin/androidmk androidmk
```

ref:

- official intro:[Soong 编译系统  |  Android 开源项目  |  Android Open Source Project](https://source.android.google.cn/setup/build?hl=zh-cn)

- [android mk 与 bp,Android.bp 你真的了解吗\_方萌-CFT 的博客-程序员信息网 - 程序员信息网](https://www.i4k.xyz/article/weixin_34342589/117589957)

- [(23 条消息) Android.bp 入门指南之 Android.mk 转换成 Android.bp_IT 先森-CSDN 博客\_android.mk 转 android.bp](https://blog.csdn.net/tkwxty/article/details/104411520)

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
