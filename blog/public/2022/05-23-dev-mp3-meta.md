---
tags: [开发笔记, 音乐]
---

# 编程 | 逼哥的音乐元数据修复

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310547240-0ba20a542cc9ebc6cf5540ad60c8e4ec8ae831b74d05ee16d60e98dba83e91ae.png)

今日在 Apple Music 中导入逼哥的音乐库时，出现了信息乱码：

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310695038-ed58410316d27f140f6d1df184971f369407b68053846151b1271578df0946ea.png)

可以看到，主要是`title`和`author`列出现了问题，这不禁引起了我的兴趣。

我第一反应便是去对应的原素材文件夹，右键 get info，可以看到确实是有两个属性是乱码（左边是原来的，右边是后续修复的）。

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310814595-e051efe2bf22ee099843f2cade8051e1d0ec73864ba0540e7a27ac86faea5c7e.png)

我原以为可以直接在属性窗上修改，结果不行。

于是我就想到，可能需要借助一些专业软件。果然，**涉及到 apple music 列表显示的关键信息，是 mp3 文件的 meta 数据**：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310896397-b120adf7f15be2c82193521a2a0dbcc92abf91708af94d195fa03a8ee44a0752.png)

按照老经验，去我们的破解专用软件站去下载：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310917717-96c26a3d5605a5736b8575c3946b946d627eac259ac48017ed8d361fec5ee494.png)

使用起来很简单，导入我们的文件夹，然后一个个修改 mp3 原数据的信息即可：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653310979865-312e6d473496ab4b99c3ef50bbbc7e49640ec2ff0f91d66f8ba8da5b3a68c0ef.png)

但既然了解了背后的原理，一个个手动修改元数据未免太慢了。

考虑到我导入的音乐，其文件名本身是良好定义的，所以直接写个程序去批量化处理比较好。

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653311076592-c5fac94b7c1c9fbac41da0763a2b415c7eeb97a1a8af5bc0577497b97fada43e.png)

它们用的是`eyeD3`这个库：

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653311105001-491e73b2c2fdcaf3c0a822892515284a07555e8bc4f07f2da2242b0b8edc9283.png)

使用方法也非常简单，一看就明白：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653311130085-98b0cb7b131b2ea6a9f72142e5ed18ceba98e24d5392f6bef5b782df861ceb2a.png)

那就轻松了，我们直接写程序即可。

```py
import eyed3
import re
import os


def edit_mp3_meta(fp, title, author):
    print("fp_: ", fp)
    audiofile = eyed3.load(fp)
    # ref: https://stackoverflow.com/a/67541983/9422455
    audiofile.tag.artist = u'%s' % author
    audiofile.tag.title = u'%s' % title
    # ref: https://stackoverflow.com/a/32908607/9422455
    audiofile.tag.save(version=eyed3.id3.ID3_DEFAULT_VERSION, encoding='utf-8')


if __name__ == '__main__':
    author = "李志"

    # 处理第一个乱码文件夹，它们内部的命名是 “李志 - 歌名（专辑）.mp3"，用正则提取比较方便
    # dir = '/Volumes/Disk2/resources/乐/lizhi-18砖/2015年《i.O》 (2014-2015李志跨年音乐会)'
    # for fn in os.listdir(dir):
    #     fp_ = os.path.join(dir, fn)
    #     song_name_match = re.match(f'{author} - (.*?)\(2014i／O版\).mp3', fn)
    #     assert song_name_match, fn
    #     song_name = song_name_match.groups()[0]
    #     edit_mp3_meta(fp_, song_name, author)

    # 处理第二个乱码文件夹，里面有两个CD文件夹，因此使用`walk`迭代，音乐命名是其本身，因此直接提取
    for root, dirs, fns in os.walk('/Volumes/Disk2/resources/乐/lizhi-18砖/2013《108个关键词》'):
        for fn in fns:
            if fn.endswith("mp3"):
                fp = os.path.join(root, fn)
                song_name = fn[:-4]
                edit_mp3_meta(fp, song_name, author)

```

处理完后，我们重新导入这些音乐，就发现，apple music 中的属性都正常了：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mark_eidt-mp3-meta-1653311311787-92d45f8fae2b0ac6518f4bcaeb3db6e71d3a3ebaebd8a239a1d8657b0f0e2b50.png)

希望对你有用~

查询参考：

- [mac get info 乱码 - Google 搜索](https://www.google.com.hk/search?q=mac+get+info+%E4%B9%B1%E7%A0%81&newwindow=1&ei=TXuLYrGBDf_N2roPw_Sf6AM&ved=0ahUKEwjx27uRzfX3AhX_plYBHUP6Bz0Q4dUDCA4&uact=5&oq=mac+get+info+%E4%B9%B1%E7%A0%81&gs_lcp=Cgdnd3Mtd2l6EANKBAhBGAFKBAhGGABQuAVYjQhg2AtoAXAAeACAAZ0BiAGJBJIBAzAuNJgBAKABAcABAQ&sclient=gws-wiz)
- [mp3 modify title and author - Google 搜索](https://www.google.com.hk/search?q=mp3+modify++title+and+author)
- [Mp3tag - Download](https://www.mp3tag.de/en/download.html)
- [Mp3tag 1.2.2 中文破解版 for Mac 音频元数据编辑工具](https://macwk.com/soft/mp3tag)
- [python modify mp3 tag - Google 搜索](https://www.google.com.hk/search?q=python+modify+mp3+tag)
- [Accessing MP3 metadata with Python - Stack Overflow](https://stackoverflow.com/questions/8948/accessing-mp3-metadata-with-python)
- [Welcome to eyeD3 — eyeD3 0.9.4 documentation](https://eyed3.readthedocs.io/en/latest/)
- [eyed3 unicode - Google 搜索](https://www.google.com.hk/search?q=eyed3+unicode&oq=eyed3+unicode&aqs=chrome..69i57j69i60.3349j0j7&sourceid=chrome&ie=UTF-8)
- [encoding - Processing chinese character using eyed3 in python - Stack Overflow](https://stackoverflow.com/questions/30388411/processing-chinese-character-using-eyed3-in-python)
