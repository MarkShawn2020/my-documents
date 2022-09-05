# surfaceflinger patch research 2022

> 年前主要是理清 surfaceflinger 从 8 到 11 的变迁，以及从我们之前已有的 patch 中寻找能用的东西，这个工作已经基本完成，已经基本实现 10 上面的反畸变效果。
>
> 年后主要是将反畸变从 10 再移植到 11 上，并将代码进一步梳理。

首先看 `RenderEngine::drawLayers` 函数。

对比下来，可以发现，第一个区别（也是最主要的区别）是`layer`从原先的类对象变成了常量指针。

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-patch-research-2022-1644939887962-e160ed15be98c3ef32427cdba32796e92c21fffd097a8969739da5dfece8e80f.png)

所以很多 layer 的方法调用，也从原先`Layer.`变成了`Layer->`：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-patch-research-2022-1644940007318-55697012a5c8100e9b308bc4d79b2f313cf0e6399a4927adfaea0a7c164566d2.png)

其他方面，尽管有增有减，但主要还是体现在各种逻辑判断、校验上，实际核心部分改动不大，也几乎没有什么改动。

比如我们需要的``变量是用于 gl 贴纸的裁切的，可以看到 10 和 11 之间几乎没有什么区别：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-patch-research-2022-1644940166347-ae3eb675362144df6339f19dc4c20f7ce588fc80e36d37316de50bad9b744f3a.png)

再比如我们需要的`renderengine::Mesh::VertexArray<vec2> texCoords`变量是用于 gl 贴纸的坐标变换的，可以看到 10 和 11 之间也几乎没有什么区别。

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/sf-patch-research-2022-1644939614528-0f56c79a4f4ea68afab8c6884a8c089bd999d4c164cbb6f7a2e831440923497e.png)
