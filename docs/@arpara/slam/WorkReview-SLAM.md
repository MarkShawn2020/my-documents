# Work Review on SLAM

## 项目目标

能实时地基于四目cv成像与三个imu数据，对手柄的空间位姿进行测算。

## 理论基础

### 单目摄像头能干什么

在只有单个摄像头的情况下，由于小孔成像的基本原理，我们无法准确感知物体的实际大小与相对摄像头的距离。

大多数情况下，我们之所以能根据照片想象出实际场景，实际上是因为我们具有一定的常识，以及大脑负责了对计算机来说最困难的部分：将平面图片逆向还原成三维空间。[^1]

![picture 33](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656783879621-19093d44a678fab8628c2fb974a97d8a020007aedb4b03baaf79b581eb379613.png)  

因此，单目摄像头缺少了深度信息，仅有单目成像，我们无法知道手柄的空间具体位姿。

### 双目摄像头能干什么

双目摄像头模拟了人的双眼，左眼+右眼的搭配能以不同的角度真实感知物体的距离，原理可以参考这篇文章： [【深度相机系列三】深度相机原理揭秘--双目立体视觉 - 知乎](https://zhuanlan.zhihu.com/p/32199990)

也就是假设两个相机位于同一平面（即光轴平行，即下图中L所在水平线与R所在水平线平行）时，P分别投影在两个绿点处，根据初中几何相似知识，我们在焦距（f）、基线（baseline）、xl和xr（物体在图中的像素点位置）已知的情况下，就可以算出物体的实际空间距离。

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656785764431-4f11b7e33aaaf052adb4484b70c95d5b050d190d0d9d5c846b841a65929b8ff8.png)  

这其中，焦距、基线，都属于内参，可以在出厂时固定并通过与厂商联系获取，也可以自行使用业界的参数标定法（例如张正友标定法）。

但这个xl、xr却是我们需要通过算法去判定的，因为在两张图中，计算机不知道哪个点对哪个点，而一旦知道，就能测算出来了。这是问题一。

此外，两个相机的光轴并不往往在同一个平面（以我司眼镜上的四目摄像头为例，似乎都有一些向外的倾角，以获取更大的视野），因此成像分析部分就会困难一些。而解决这个问题的办法就是基于单应矩阵[^2]实现图像矫正。

![picture 35](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656786525049-8ca22cd43f9e107510e41d222a5589b7f1aa72cafec3e0d5bf01e030606bf072.png)  

此外，从最原始的办法出发，要想在另一张图中找到第一张图中与某个像素点匹配点，可以通过遍历全图实现，复杂度达到了$O(n^2)$，此外，假设每个点都需要周遭K个点才能确定其匹配度的话，那复杂度就是$O(kn^2)$甚至$O(n^3)$，显然难以接受。

如果能有一种办法可以快速地缩小查找范围，就可以显著加快匹配速度。第一个答案就是极线约束。

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656787170401-19ad2839b3c8072f28577ad16ef0e89b3730939e5535fd02186668e6cce08848.png)  

这样以来，从需要在一个平面找，变成了在一条直线上找，因此复杂度降到了$O(n\sqrt{n})$。

当然，实际情况下，肯定会有误差，因此不必然一定在一条直线上，因此可以使用滑动窗口法适当放宽搜查范围，也就是$O(kn\sqrt{n})$。

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656787389276-497c7a1ade66ee13f0358acf393c7ff915799525e05d54dcdbe9f569bdd39a84.png)  

以及，最终，我们还可以把它理解成一个最优化问题：

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656787475650-d5702f8097336547ce9678386c7c4e3b7261d413f02542da90ffc06c50b12710.png)  

关于马尔科夫随机场，这篇文章写的很通俗易懂： [马尔科夫随机场(MRF)在深度学习图像处理中的应用-图像分割、纹理迁移 - 知乎](https://zhuanlan.zhihu.com/p/38343732)

其他关于双目视觉的参考：

- [一篇文章认识《双目立体视觉》 - 腾讯云开发者社区-腾讯云](https://cloud.tencent.com/developer/article/1824593)

### 单目+imu

这篇文章不错： [计算机视觉方向简介(三) | 单目微运动生成深度图 - 知乎](https://zhuanlan.zhihu.com/p/33956636)

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656791613761-242375872dbeb880edc13d851bbab826629c9bce114c06e43516d97501231a52.png)  

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656791621047-1b27ebea199010dae2b0f52eda52e4ac819be5580931eab772a1f79bfd00bc7f.png)  

### 如何确定两张图内的像素点之间的匹配对应关系

### 理解与使用ORB-SLAM

### 物体检测技术（基于yolo）

- [【经典论文解读】YOLOv4 目标检测_一颗小树x的博客-CSDN博客_yolov4](https://guo-pu.blog.csdn.net/article/details/119673960?spm=1001.2014.3001.5502)

- [(21) YOLOv3 - YouTube](https://www.youtube.com/watch?v=MPU2HistivI)


### 如何测算imu位姿

- [基于 IMU 的位姿解算_一颗小树x的博客-CSDN博客_imu位姿解算](https://guo-pu.blog.csdn.net/article/details/123388193?spm=1001.2014.3001.5502)

## ORB-SLAM

source: [ORB-SLAM Project Webpage](http://webdiis.unizar.es/~raulmur/orbslam/)

两篇论文分别发表于2015、2016年：

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/WorkReview-SLAM-1656844832096-caea151ae65131b8317c9836aaf64365cee19bd8e4fd3ace4d0a94b58774735a.png)  


## 项目条件

### 四目摄像头

在眼镜上配有左上（LT）、右上（RT）、左下（LD）、右下（RD）四个摄像头。

其内参为（数据来源：金天4月1日答复）：

```yaml
# intrinsic
Camera.fx: 274.1932382064952
Camera.fy: 275.36181187641506
Camera.cx: 316.23880553912664
Camera.cy: 236.82068245645195

# fish eye    
Camera.k1: 0.012230065289018368
Camera.k2: -0.020113887598814294
Camera.k3: 0.020268290416176487
Camera.k4: -0.00615665479360849

# baseline (unit: m)
baseline: 0.065
```

## 路径分析

[^1]: [(21) The Math behind (most) 3D games - Perspective Projection - YouTube](https://www.youtube.com/watch?v=U0_ONQQ5ZNM&t=201s)

[^2]: 关于单应矩阵，可以看这篇，我觉得写得非常生动形象： [从零开始一起学习SLAM | 神奇的单应矩阵 - 知乎](https://zhuanlan.zhihu.com/p/49435367)

## 会议记录

### 2022-07-08, Fri

可见光问题

逆向  fpc 灯带

灯环要重新做

1. 灯圈设计之前，用惠普的灯圈去做测试
2. 通线调通后，再看看追踪能不能做

