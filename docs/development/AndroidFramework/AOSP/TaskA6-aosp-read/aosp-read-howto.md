# aosp read howto

## read native framework based on clion

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
