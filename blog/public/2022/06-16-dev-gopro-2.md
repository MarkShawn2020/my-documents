---
tags: [开发笔记, GoPro]
---

# 编程 | GoPro 02: 玩转 OpenLab

1. 方案 1：物理手段解决
2. 方案 2：借助**OpenCV**基于文件创建时间进行推算
3. 方案 3：借助**GoPro Labs**添加时间戳浮层
   1. 浮层大小
   2. 浮层内容
   3. 浮层位置
   4. 二维码生成
   5. 二维码使用
   6. 缺陷
   7. 其他用处
4. \*方案 3 个人笔记
   1. LAB01: how to install the labs firmware
   2. LAB02: QR Controls For Settings
   3. LAB03: add an overlay to viedeo
5. 最后一点感受

在上一期【文章：gopro】中，我们提供了一种借助 gopro 基于延时摄影从而底层本高质量地全程记录个人生活的解决方案，实测中这个方案仍然有一些不足之处，本期就重点探讨时间戳相关的问题。

这个问题其实很关键，因为我们正在做的事情是长时间无感拍摄，目的是为了后期复盘，但在复盘过程中，由于延时时间跨度过长，我们希望知道视频里的每一帧所拍摄的实际时间，比如是某月某日的下午两点还是夜间十点，这是一个很自然的需求。

但很可惜，这个问题并不容易解决。

以下便基于这个问题，提供实际可行的三种方案。

## 方案 1：物理手段解决

如果你是一个比较传统的、具有较强时间观的人，也许这种方案特别适合你，那就是直接选购一款挂钟（这也是我在上篇文章中所采用的方法）。

例如，我们这里有一段使用挂钟时期的成品视频：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655354709985-843159c3c155958989a9d5791053dbaecaca765cf48c91ebed9afd66f5c1d33a.png)

将我们的挂钟摆在所拍摄视频中的合理位置，既增强了画面构图感，也能实时知道每一帧所对应的真实时间，这确实有一石二鸟之效。

但很可惜，这种方案，并未能坚持多久，原因是，廉价的挂钟机芯转动声音影响到了自己的睡眠。

按照我对睡眠无声的要求，在依次关闭空调、窗户、电脑散热器、硬盘柜之后，室内的声音强度耳测应该已经低于 30 分贝，此时挂钟的声音就显得尤为明显了。

尽管它不大，但确实也没那么动听，至少甚至不如星际穿越的曲子《Tick-Tock》的前奏。

除非我愿意花更多的时间与金钱去筛选到另一款真正无声的挂钟，但作为一名程序猿，也许有更廉价与炫酷的方案。

## 方案 2：借助**OpenCV**基于文件创建时间进行推算

> 本节参考：- [GoPro TimeStamp - The Eminent Codfish](https://www.theeminentcodfish.com/gopro-timestamp/)

事实上，由于我们的延时摄影采用了固定时间间隔的方案（有关“自动时间间隔”与“固定时间间隔”方案的差异与优劣，也在上篇文章中有阐述），因此只要我们知道视频的任何一帧所对应的真实物理时间，我们就可以基于等差数列算法进行推算。

而这，恰恰可行，因为 gopro 的视频输出格式为 mp4，里面保存了文件的创建时间。

不过，这个文件创建时间，可不是我们在电脑上看到的那个文件创建时间，这不是同一个概念。

例如，我们这里有一段视频的开头显示是 6 月 15 日 10 点 05 分：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655355366257-b01f6386d8aaa7fc57ca802956a6fd73fc4f6628385437e0055b8bd94622b6f9.png)

但在我们的文件管理器上查看该文件的创建时间却是 6 月 16 日 10 点 57 分：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655355421774-dc43ac335c5f11ebcbda9c81edde670f3e7f285321771c5f1a0ad443f8f22e2a.png)

这显然不是时区的问题，而是操作系统问题，即在操作系统里定义的文件创建时间是该文件在本地磁盘上首次产生的时间，而非文件本身的首次创建时间（对于该视频来说，尤指该视频开始拍摄的时间）。

但我们并非没有手段获取实际视频创建时间，答案就是基于软件解析的手段：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655356074973-cf5d985ee99cf99c2e87527c0ea19e095d2c433ceb7bed96d27be097804bb0ba.png)

上述代码使用了`ffprobe`这个指令解析了我们的 mp4 文件，从结果中的`creation_time`标签得到了我们想要的视频创建的真实时间，于是乎，最难的问题解决了。

接下来，我们就基于视频领域的一些基本概念为我们的视频加上时间戳信息。

第一步是关于帧的。

在之前文章中我们说我们的视频是每 5 秒延时拍摄一帧，也就是每过一帧实际时间就要**大致**加五秒，这是一个很重要的信息。

而整个流程就是使用 opencv 读取我们视频的每一帧，然后算出该帧的时间，然后将格式化的时间戳放到那一帧上面去，最后再输出成一个新的视频，这个过程就叫“烧录”。

核心代码如下：

```py
# ref: - [GoPro TimeStamp - The Eminent Codfish](https://www.theeminentcodfish.com/gopro-timestamp)
import time
from datetime import datetime, timedelta

import cv2
import subprocess as sp
from tqdm import tqdm

from get_file_creation_time import get_creation_time

FONT_COLOR = (0, 0, 200)  # blue, green, red


def get_output_file_path(file_path):
    return file_path[:-4] + '_with-timestamp' + file_path[-4:]


def add_timestamp_for_video(file_path):
    # Opens the video import and sets parameters
    video = cv2.VideoCapture(file_path)

    if not video.isOpened():
        raise Exception(f"failed to open video of {file_path}")

    FPS = video.get(cv2.CAP_PROP_FPS)
    width = video.get(cv2.CAP_PROP_FRAME_WIDTH)
    height = video.get(cv2.CAP_PROP_FRAME_HEIGHT)
    frames_cnt = int(video.get(cv2.CAP_PROP_FRAME_COUNT))  # float -> int
    duration = frames_cnt / FPS

    # Initializes time origin of the video
    creation_time = get_creation_time(file_path)
    cur_frame_time: datetime = creation_time
    print(
        f"frames_cnt: {frames_cnt}, FPS: {FPS}, initial_timestamp: {cur_frame_time}, dimension: {width} x {height}, duration: {duration}")

    # Command to send via the command prompt which specifies the pipe parameters
    command = ['ffmpeg',
               '-y',  # (optional) overwrite output file if it exists
               '-f', 'rawvideo',  # Input is raw video
               '-vcodec', 'rawvideo',
               '-pix_fmt', 'bgr24',  # Raw video format
               '-s', str(int(width)) + 'x' + str(int(height)),  # size of one frame
               '-r', str(FPS),  # frames per second
               '-i', '-',  # The input comes from a pipe
               '-an',  # Tells FFMPEG not to expect any audio
               '-vcodec', 'mpeg4',
               '-b:v', '10M',  # Sets a maximum bit rate
               get_output_file_path(file_path)  # output file path
               ]

    # Open the pipe
    pipe = sp.Popen(command, stdin=sp.PIPE, stderr=sp.PIPE)
    print('====== OpenCV is processing =======')
    process_time_start = time.time()

    # Reads through each frame, calculates the cur_frame_time, places it on the frame and
    # exports the frame to the output video.
    for i in tqdm(range(frames_cnt)):
        success, image = video.read()
        if not success:
            print(f"ERROR: failed to read frame of [{i + 1}/{frames_cnt}]")
            continue

        cur_frame_time += timedelta(seconds=5)
        cv2.putText(image, 'Date: ' + str(cur_frame_time)[0:10], (50, int(height - 150)),
                    cv2.FONT_HERSHEY_COMPLEX_SMALL, 2,
                    FONT_COLOR, 3)
        cv2.putText(image, 'Time: ' + str(cur_frame_time)[11:], (50, int(height - 100)), cv2.FONT_HERSHEY_COMPLEX_SMALL,
                    2,
                    FONT_COLOR, 3)
        assert image is not None
        pipe.stdin.write(image.tobytes())

    print('====== finished =======')
    process_used_time = time.time() - process_time_start
    print(
        f"used time: {process_used_time} seconds, video period: {duration} seconds, multiplier: {process_used_time / duration}")
    video.release()
    pipe.stdin.close()
    pipe.stderr.close()


if __name__ == '__main__':
    add_timestamp_for_video("/Volumes/Disk1/videos/gopro日常/gopro延时生活/2022-06-14/GH011701.MP4")

```

输出结果：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655358120832-aa46758f93ddc61e960a10c274e8fb7ea49276b152f7d3fa6e343d02c1e2bc9a.png)

可以看到，基本一比一的处理速度，也就是说原视频时间有多长，程序运行时间就有多长，对于延时摄影来说，一天的录制输出大概就是十分钟的视频，因此脚本每天的运行时长也就是在十分钟左右，这是可以接受的。

不过这个脚本也有一点点小问题。

第一个问题是每次读取到第二十帧的时候就会报错，之后就没问题，不明白什么原因，也似乎不影响程序的表现，这个属于 opencv 范畴的问题了，留到以后再考虑了。

第二个问题就是输出的视频文件比原文件要小很多，直接差了十倍……：

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655358301337-0a3bc21ac1b530ed8f43053e33a9dc99fc89d90bd464a0e3335c942c9c01ab41.png)

我们放在一起比对了一下，发现分辨率是没区别的，区别可能是在编码上：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655358410672-57cab49192da7b59eed7ba618c39d6d255cee16c69296294643a68eff01f401d.png)

实际看了一下，发现确实画质上有较大区别，比如原视频的白墙很光滑：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655358467434-475e70206879f5478766392201a3660654973eec188934dfe157dbd2a24e0bb0.png)

但编码后的白墙就明显有那种类似波纹的效果了：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655358486566-93f149d18618d08ed0741e37dce78415d64e105c79d847a015f57ce19da5d9f1.png)

从这个角度上说，如果不考虑修改脚本，使之输出原质量的视频，那么我们的脚本输出的视频就只能当做备份与参照视频了，毕竟十倍的比率确实也有一些用武之地。

然而，这个脚本实际上还有另一个问题，那就是时间不一定能对齐。

比如刚刚文件对比图上，一个是 20 秒，一个是 19 秒，当然这个其实没有太大所谓了（虽然很非遗所以，也许就是和上面那个有两帧无法处理的问题有关），我更关心的是另一个对齐问题，曝光与时间间隔。

就是，怎么说呢，我现在并不确定 gopro 的曝光与拍摄间隔之间的关系，比如说，假设我们设置拍摄间隔为 2 秒，曝光时长为 1 秒，那么它是每 3 秒拍一次照片还是每 2 秒拍一张呢？

如果是每 3 秒拍一次照片，那么我们的算法每一帧加 5 秒就有问题，因为没有算上曝光时间，这样就会导致累积时间变少。

但如果是每 2 秒拍一张照片，那么更极端的一个情况，例如拍摄间隔为 1 秒，曝光时长为 2 秒，则似乎就无法拍摄了……

所以，这里有研究一下的必要。

总之，这种借助 opencv 进行后期处理的手段还是有一定实用价值，适用于很多其他的领域，是一种通用技术手段，我们有必要掌握，并且我对熟练掌握 opencv 之后输出我们想要的视频结果的可能性抱有很高的期望，除了曝光与拍摄间隔对齐的问题之外。

但输出的画面质量不佳（若提高质量（假设可行），势必速度会下降）与额外脚本运行的不便等因素，使我最后选择了第三种更干净的方案：`GoPro Labs`。

## 方案 3：借助**GoPro Labs**添加时间戳浮层

如果说第二种方案属于后期，那么本方案则属于前期了。

众所周知，防患于未然，能从前期着手的方案，基本都是最优的。

而 GoPro Labs 就能帮助我们实现这点。

我们要做的事情就是：

1. 下载 GoPro Labs 的固件版本，完成固件升级（我的 GoPro 是 9，是支持的）
2. 制作我们的时间戳浮层二维码，扫描后使用

主要通过这个网站： [https://gopro.github.io/labs/control/overlays/](https://gopro.github.io/labs/control/overlays/) 生成我们所需的二维码，这里的每个参数都比较重要，我们一一解释：

### 浮层大小

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655359589767-225e990742d950f8587e2c402e3368a9e244f5412a936ac5d47065be0bfe3eea.png)

`vertical size`是浮层的整体高度，而非单个文字的高度，由于浮层支持多行文本，因此为了目标字体大小，多行文本时对应的竖直高度也要变高，我们设置为 60，对应三行文本，（也就是每行 20，单位大概是像素），效果不错

`horizontal size`是浮层的整体宽度，因为这个底层是按行排版文本，因此我们直接设置成 0，让它自动调整浮层的宽度即可，即所有行中最长的行的宽度

`offset from the edge`是与画面边缘（应该是 Y 轴，因为 X 轴距离可以通过下文的换行符控制）的距离， 目前使用的是 10，效果还不错

`Limit dispaly time`设置成 unlimited 即可。

### 浮层内容

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655359884415-4a3b036583d6c3be88ca734bf9e9e51f76a3f6600c7ca7d3a5fd2751f4609384.png)

这个就是配置我们的自定义文本与时间、日期的地方，它是一行行下来的，可以自己用`\n`分隔符换行（但不可以换顺序，所以时间始终在日期之前）。

为了从简，我没有加任何个人自定义短语（一开始加了自己的昵称，后来觉得太冗余了，所以还是留空了），但我在尾部加了两个空行，这是为了主动地增加相机与底部（X 轴）的边距，这样输出的视频里的时间戳在我 mac 电脑上预览时不会被进度条挡住。

### 浮层位置

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655360216872-e9f80b49b95e94ae25f967b4693cdd17aef45684d829b5e2986a0b246b40e314.png)

我将时间戳放在了左下角，因为我平常会在右下角办公，而画面中上部则是主体区域。

我们的场景中不需要使用 GPS。

### 二维码生成

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655360265681-720de6db987621a49e2a200321fcffca430ef8a599e20145dd6d7804e5b3aba5.png)

在生成二维码附近还有是否选择`active`的选项，我之前一开始捣鼓 lab 时弄出了 bug，在 模式设置：[GoPro Labs: QR Controls For Settings](https://community.gopro.com/s/article/GoPro-Labs-QR-Control?language=en_US#secondupdate) 中设置出了一个没有的模式，导致系统死掉，最后刷回 GoPro9 1.5 的稳定固件版本，然后重新升级到 lib 版本才恢复，这其中既有可能是模式问题，也有可能是这个浮层当时选了`permanent`选项，因此我现在已经完全不敢点这个选项了。但并不影响我目标功能的实现。

基于这些，最终的二维码就生成了，它对应的 QR Command 是：

```text
g0oMBRNO=10oMBURN="(0,60)[BLHH:MM:SSaa mm-dd-yyyy]\n"
```

以后我直接基于这个 Command 字符串进行修改即可，还是很方便的，比如加上自定义前缀与后缀的结果如下：

```text
g0oMBRNO=10oMBURN="(0,60)哈哈哈[BLHH:MM:SSaa mm-dd-yyyy]略略略\n"
```

如果我们用函数去表达这个字符串输出就是：

```py
def gen_gopro_overlay(
    overlay_edge: int,
    overlay_width: int,
    overlay_height: int,
    content_leading: str,
    content_ending: str,
    datetime_format: str
    ) -> str:
    return f'g0oMBRNO={overlay_edge}oMBURN="({overlay_width},{overlay_height}){content_leading}[BL{datetime_fornat}]{content_ending}'
```

注意到，我们的时间格式也是可以自定义的，并且如果我们基于从字符串（而非网页交互）出发去生成二维码，那么我们就可以定义日期在前时间在后的格式了，比如`yyyyy-mm-dd HH:MM:SSaa`。虽然这一点未经过测试，但想必是可行的（写文章时才意识到的，hh~）

### 二维码使用

只需要将升级成 lab 固件版本的 gopro 打开后对准我们的二维码，就会自动识别并应用了，然后“BOOM”，一个可爱的浮层就出现了！

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655360991571-d8d1b7e0310840ea24d4942d811b06c8afce5eb567d92a10db6ca0642adcd2f5.png)

### 缺陷

1. 除了上文提到的容易导致系统挂掉之外，正常操作不会有问题
2. 经测试，我们的时间戳浮层对照片和夜间延时没有效果，对普通视频与正常延时有效果。经过思考，我这个项目一开始采用夜间延时的方案现在觉得不太适用，因为实测下来在夜间我屋子几乎全黑的环境下即使开了夜间延时也几乎无法拍出能看清的画面，而白天看投影时又会导致曝光过高，因此直接放弃夜间的效果即可。当初拍夜间是为了监测睡眠，那段时间也会在睡觉时留一盏小灯（戴眼罩）以获得最好的拍摄效果，现在睡眠项目已经结项了，因此不需要了。我也更喜欢无声+全黑的睡眠环境。
3. 关于上一点，也好像不是没有解决方案，正如我笔记中记载的 [Combining the video overlay and interval video feature.](https://community.gopro.com/s/question/0D53b00008QAGooCAH/combining-the-video-overlay-and-interval-video-feature?language=en_US) 这篇帖子里的小哥貌似碰到的就是和我差不多的问题并有一个解决方案，但我暂时已经不需要了，以后有机会再研究吧！

### 其他用处

GoPro Labs 的功能不仅限于添加浮层这一项，恰恰相反，这是里面最小的一个应用之一。

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-timestamp-1655361326041-ae5359c76c082cda93c03f928c7e5ad513c1636b7dd46f1865dbf5e6b75e3da9.png)

它还有很多其他有趣的场景应用，必须运动检测、自动切换模式等，详情可参考：

- [GoPro Labs: QR Controls For Settings](https://community.gopro.com/s/article/GoPro-Labs-QR-Control?language=en_US#secondupdate)

- [(151) GoPro Labs: How to Use QR Codes to Instantly Switch Your Settings - YouTube](https://www.youtube.com/watch?v=YaXcu0E10WM)

- [(151) GoPro Labs 2021 New Features for Hero 9, Max, Hero 8, Hero 7: Hands-on Details & Explainer - YouTube](https://www.youtube.com/watch?v=0LCGiO7jMEw)

## \*方案 3 个人笔记

### LAB01: how to install the labs firmware

see [Hero9 Black Product Update | GoPro](https://gopro.com/en/us/support/hero9-black-product-update), but I failed to generate the target firmware in this site.

So I downloaded it in other place, e.g. - [Need HERO9 Black firmware update v1.5 | GoPro Forums](https://www.goproforums.com/threads/need-hero9-black-firmware-update-v1-5.87636/), which directed me to the dropbox download page: - [GoPro Hero 9 firmwares fishycomics.zip](https://www.dropbox.com/s/edh41nffo6d6gns/GoPro%20Hero%209%20firmwares%20fishycomics.zip?dl=0)

And finally, I saved two different firmwares in local disk, one for stable version, one for the lib one:

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-1655351979322-5f9d394f99b48f506a3fb28de9adadfd94be9ebc9f57562d3925e88635f16863.png)

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/gopro-1655340186034-7e904daaa952ca0a5c3457c103fcddaa9eaee79362a7051a179ef1ca14576416.png)

ref:

- [GoPro Labs Information](https://community.gopro.com/s/article/GoPro-Labs?language=en_US)

### LAB02: QR Controls For Settings

see:

- documentation: [GoPro Labs: QR Controls For Settings](https://community.gopro.com/s/article/GoPro-Labs-QR-Control?language=en_US#secondupdate)

- custom qr control: [https://gopro.github.io/labs/control/custom/](https://gopro.github.io/labs/control/custom/)

### LAB03: add an overlay to viedeo

see:

- [https://gopro.github.io/labs/control/overlays/](https://gopro.github.io/labs/control/overlays/)

ref:

- [How do I add timestamp to Hero 10 videos?](https://community.gopro.com/s/question/0D53b00008HOPq7CAH/how-do-i-add-timestamp-to-hero-10-videos?language=en_US)

- [Burning timestamp on GoPro movie : gopro](https://www.reddit.com/r/gopro/comments/pt6u8j/burning_timestamp_on_gopro_movie/)

bugfix: gopro labs won't add timestamp to interval videos, see:

- [Combining the video overlay and interval video feature.](https://community.gopro.com/s/question/0D53b00008QAGooCAH/combining-the-video-overlay-and-interval-video-feature?language=en_US)

## 最后一点感受

国外的极客生态真地很繁荣，一个小小的 gopro 就能玩出这么多的花样，反观国内，似乎还停留在各种参数的堆砌与各种大饼的圈画上，实则看不到太多对待一个具体的事物（而非钱）研究的诚意与专注的热爱。

之前携国货之光大疆无人机奔赴川藏线，它真地很好。但现在身处帝都，最终还是无用武之地，幸好有位天体物理博士愿意收购它，让它继续发光发热。而我，则只有尽我可能，把一些有趣的东西搞的更明白一些、更有用一些、更好玩一些。

gopro 的话题，从上篇的 open-gopro 到本篇的 GoPro Labs，基本已经涉及了 gopro 核心开发生态的方方面面，朋友们需要时完全可以顺着这两篇一窥 gopro 的里子，进而玩出新的花样。

下一期，我们聊聊最近做的另外一个有趣的小东西：投影与手机遥控器。

Best Wishes to All of You.
