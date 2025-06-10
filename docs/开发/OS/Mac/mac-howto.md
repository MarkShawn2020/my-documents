
## ipad air 5 64G 选购依据

产品对比官网： [iPad Air (4th generation) vs iPad Air (5th generation) vs iPad Pro 11‑in. (3rd generation) - Apple](https://www.apple.com/ipad/compare/?modelList=ipad-air-4th-gen,ipad-air-5th-gen,ipad-pro-11-3rd-gen)

4 代和 4 代的差异主要体现在芯片上，我的电脑就是 intel，现在想试试 m1 芯片，所以 4 代不考虑了：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1656125802778-3c3bb111ca321d155998d80d65a4a3d1904e28231dab3a3d115ab1fe1807f371.png)

ipad 上玩音乐创作还是一绝的，这种场景需要屏幕相对较大，所以不考虑 mini 的主要原因是这个：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1656125864040-53ab26f31ae664aecb664a5cd78af613f5571e16251dc9043c60af272ca77cc6.png)

我之前就想要紫色来着，可惜当时看的没有货，只有蓝色，我手机就是蓝色：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1656125982881-854bc761d129ea4ebc23d1073644dd056331c06eec5b4921d75fc3af19aafbfb.png)

总结一下的话就是：

- 不选 mini 是因为屏幕太小，不适合艺术创作；
- 不选 air 4 是因为芯片不是 m1；
- 不选 pro 是因为性能过剩； 只选 64g 是因为家庭基于无线与外接硬盘已经足够；综上，air 5 64g 紫色这一款是满足我需求性价比最高的产品。

最后，感谢文文姐给我预付款：

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1656125920753-5097c38e44acd90a4a45adf77c908e8616bbda5ca21d590b82fb33e6649a82af.png)

## numbers

### trigger applescript within numbers

ref:

- [Trigger applescript from within numbers?!? - Apple Community](https://discussions.apple.com/thread/1876601)

## mac switch between hidden/minimized tabs

值得注意的是，mac 对 hidden 与 minimize 是两种不同的处理方式，当我们 minimize 一个程序的时候，我们是没法通过 command + tab 方式再次切换过去的，它几乎消失了。

如果我们想在 command+tab 中还能找到它，我们要用 command+Hidden 去隐藏，而非 command+Minimize 去最小化。

此话，我们还可以用 option+command+Hidden，去只显示当前窗口，而隐藏所有其他窗口，这非常方便可以看到桌面的样子。

ref:

- [macos - Cmd+Tab does not work on hidden or minimized windows - Ask Different](https://apple.stackexchange.com/questions/112350/cmdtab-does-not-work-on-hidden-or-minimized-windows)

## mac 录屏

### 为什么 mac 录屏无法录制耳机（系统输出）

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1645518525249-644e1071fba6deea0061b9cc06718f3d9d59e57d7845e6007f7c50d452f08c17.png)

ref:

- [How do I record a screen with audio in a Mac with headphones on? - Quora](https://www.quora.com/How-do-I-record-a-screen-with-audio-in-a-Mac-with-headphones-on)

## mac dict config

- [把查词做到极致的 macOS 原生词典，其实很好用 - 少数派](https://sspai.com/post/43155)

## how to disable `iphone copy ...`

![picture 53](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1644080853251-57607a179b69f78416d49c0ef20a4a5fad1f69e3d54838ec6d16468389bb83a5.png)

> ref

- [Use Universal Clipboard to copy and paste between your Apple devices - Apple Support](https://support.apple.com/en-us/HT209460)

## how to disable floating window after macOS screenshot

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1645005374576-ebc17e84dacb48bbbd8c60fa4bd9528e0fcb8f0d7d47d52ede71c855fed4544c.png)

ref:

- [How to Remove the Floating Screenshot Preview Thumbnail in macOS – Techstacker](https://techstacker.com/remove-floating-screenshot-thumbnail-macos/)

## mac file system management

### trash

position: `~/.Trash`

open trash:

```sh
open ~/.Trash
```

> ref

- [command line - How to open "Trash" through terminal? - Ask Ubuntu](https://askubuntu.com/questions/327943/how-to-open-trash-through-terminal)

## 远程控制 windows

> ref

- [mac 远程控制 windows 系统 - 知乎](https://zhuanlan.zhihu.com/p/104556030)

## add filepath into python path permanently

1. we need to add path into `$PYTHONPATH`, instead of `$PATH`
2. we should add into `~/.zshrc`, as well as `~/.bashrc` in case that running py under any circumstance.

evidence: <img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-howto-1641511085541-a244d55e39261e05045f7d395b99f353814c167f734668e8db63cafa6ee9e3af.png" />

> ref

- [Permanently adding a file path to sys.path in Python - Pretag](https://pretagteam.com/question/permanently-adding-a-file-path-to-syspath-in-python)

## how to configure permanent environment variable?

I tried but to find only if I push `A=xxx` into `.zshrc` file can it work rather than into `.bashrc` which even causes to the garbled(乱码) output.

For example, I will use this:

```sh
echo "\nhjxh=/Users/mark/Documents/mark_projects/皇家小虎/HJXH/hjxh_express_match
zkj=101.43.125.199\n" >> ~/.zshrc
source ~/.zshrc
```

so I can see the tail of file changes into: <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640100055610-c39f574cec7b27008ba8308488e64c85c981993a49cc1886cdd7f2ebdffe66c7.png" width="480" />

## Can local dns set and work for chrome? [No, it can't]

But, I can still use the local DNS for terminal use, e.g, when I added `101.43.125.199 zkj`

<img alt="picture 21" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640066362448-b6f73d4f5d677d1fa123301020a4756633f1b8d0cb1997a9e9c2f61b34b15466.png" width="480" />

then I can DIRECTLY see the `zkj` as an alias of `101.43.125.199` since my MacOS would help me do the right thing:

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640066478897-1d6726e83768ed72a7baa96f068b5efd206003f2f1d24662bb22883b68454020.png" width="480" />

Compared to export variable into PATH file, this method's best advantage is that I do not need to write a `$` prefix and at the same time, the shortage is that it can only work for IP address while in PATH file I can define more variables.

However I can't let it work in the chrome, which seems a bit disappointing.

> ref

- [How can I set Chrome to use local DNS from hosts file? - Quora](https://www.quora.com/How-can-I-set-Chrome-to-use-local-DNS-from-hosts-file)

## how to uninstall Microsoft AutoUpdate and microsoft worksuits

1. locate the microsoft auto-update application

At this step, I used the Alfred to help me goto the target position, just enable the alfred search by start with a `/`.

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639942458223-2656adce34f2b76a6e84abd2fe69de1b7b9c306a08085f6c92743ff91131ace4.png" width="480" />

2. quit its running process, and then delete it.

3. deleting all the microsoft work suit, since they seem not helpful than the wps and the experience is rather terrible.

> ref

- [What Is Microsoft AutoUpdate on Mac and How to Delete It](https://www.guidingtech.com/what-is-microsoft-autoupdate-mac-how-to-delete/)

- [How to Delete Microsoft AutoUpdate from Mac](https://osxdaily.com/2019/07/20/how-delete-microsoft-autoupdate-mac/)

## how to disable sudo password

see: https://jefftriplett.com/2022/enable-sudo-without-a-password-on-macos/

`sudo visudo`

change:
`%admin          ALL = (ALL) ALL`

to:
`%admin          ALL = (ALL) NOPASSWD: ALL`

re-login may need.

## TODO: how to symlink `/home` to `/Users`

I did it in recovery mode on `Ventura` system, with `shift + command + t` to open hidden terminal, and executed the following:

```sh
mount -uw /
ln -s /Users /home

ls /home
# out: share
```

It's OKAY, but it won't after I rebooted.

ref: - [unix - Mac OS X - How to Symlink /home to /Users - Ask Different](https://apple.stackexchange.com/questions/44058/mac-os-x-how-to-symlink-home-to-users)