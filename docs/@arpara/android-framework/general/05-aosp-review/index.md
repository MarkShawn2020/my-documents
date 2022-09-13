## how to review java frameworks in IDE

### compile `idegen`

use `bash` (not `zsh`, otherwise the script won't pass, see: [mmm 编译模块报错 Couldn't locate the directory - 简书](https://www.jianshu.com/p/2a4731385773))

```sh
source build/envsetup.sh && lunch rk3399_Android10-userdebug

mmm development/tools/idegen
```

### config `ulimit`

otherwise, the android studio would complain the logs (each module would) and it would be rather slow to index (more than half of hour or more).

```sh
echo "ulimit -S -n 2048" >> ~/.bashrc
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

## how to debug java frameworks

ref:

- :sparkles: :sparkles: 这个不错，里面讲了很多种办法，比如日志断点！值得学习！ [Android Studio 你不知道的调试技巧 | Weishu's Notes](https://weishu.me/2015/12/21/android-studio-debug-tips-you-may-not-know/)

- [Android Framework 调试 | River Young](http://riveryoung.cn/2020/12/09/Android-Framework-Debug/)

## how review native frameworks in IDE

### how to read native framework based on clion

see: :sparkles::sparkles::sparkles: - [CLion project generator](https://android.googlesource.com/platform/build/soong/+/HEAD/docs/clion.md)

以下是加了 cmake 后编译输出的目录结构：

![picture 35](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-read-howto-1645676260488-70514b613a068259bce0e5433a33b8dc4b6868bc3a5512ee19a237cc8af7afe8.png)

地址是在 `out/development/ide/clion/frameworks/native/**/CMakeLists.txt`。

如果你想改哪个模块，就导入哪个模块的 cmake 文件，导入后 ide 就会自动只对那些文件进行代码提示，其他的不会。

如果你想再包括其他的，直接在 cmake 文件里加一点 include 就行。

在项目结构上有两种办法：

1. 直接打开 cmake（导致 cpp flattened），然后在`Tool | CMake | Change Project Root`
2. 直接打开 project，再 select cmake files (ide 会自动弹窗)

另外同时查看多个项目的话可以在 `development` 下配置（我当时想配置`out`，结果没注意其实配的是`development`，我说怎么始终没有`surfaceflinger`部分呢，当时非常不解!一定要注意前面有没有`out`！)

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-read-howto-1645676600906-574d19958013236b5b5402fbb24c52c930dda7854611c3e0124c85b3163efe38.png)

最后，如果想手动加入其它源代码查看，可以在 cmake 里手动配置 `include`。

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

办法就是修改对应的 `CMakeLists.txt` 文件，整个文件分成自己包库与依赖包库，一般是在依赖包库会出现问题，在最后面的 `CXX-FLAGS` 后面一次次编译补上所需要的屏蔽条件即可，例如我在编译 `libsurfaceflinger` 中，要补全的条目如下：

```cpp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-int-float-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder-init-list")
```

## how to debug native frameworks

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

#### FIXED: `ld.lld: error: undefined symbol: graphic_policy(int)`

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588183041-6643592b34632faef340ffe8a6f9baa7597d40faf43c97daffb862cb6e37256f.png)

这个原因，我具体也不清楚，因为一是以前没有单独编过`native`，二是后来又改了很多 `surfaceflinger` 部分，看这外部的报错信息，似乎正与我改的部分有关，但具体到内部又发现似乎无关……

所以我目前的做法就是先把它注释掉，这看起来好像影响不大……

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588365881-e75c80d6ffb6606d4b6b3fb638e47a1a49a406b549428071142ea9bd0343f66d.png)

然后重新编译，目前似乎一切都很正常！

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/frameworks-howto-1645588403242-61bab44d027d5b9b2b3b5096c421502c1a2aac970732de2125f0aef3588adb31.png)

