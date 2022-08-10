# vmware howto

1. [installation](#installation)
2. [configuration](#configuration)
   1. [cpu](#cpu)
   2. [memories](#memories)
   3. [disk storage](#disk-storage)
   4. [disk type](#disk-type)
3. [vmware best practice](#vmware-best-practice)
   1. [retina solution](#retina-solution)
   2. [config keyboards](#config-keyboards)
      1. [1. :sparkles: mac host key](#1-sparkles-mac-host-key)
      2. [2. copy paste](#2-copy-paste)
   3. [vpn proxy](#vpn-proxy)
      1. [1. know what's your ip and vpn port of host machine](#1-know-whats-your-ip-and-vpn-port-of-host-machine)
      2. [2. ensure the net type in vm](#2-ensure-the-net-type-in-vm)
      3. [3. specify the vpn manually in vm](#3-specify-the-vpn-manually-in-vm)
   4. [share files between host(mac) and guest(ubuntu)](#share-files-between-hostmac-and-guestubuntu)
      1. [BEST-PRACTICE: use `vmhgfs-fuse` and auto-complete supported](#best-practice-use-vmhgfs-fuse-and-auto-complete-supported)
      2. [resolution 1. use `/mnt/~`](#resolution-1-use-mnt)
      3. [mount host user folder to guest (transfer file from guest to host)](#mount-host-user-folder-to-guest-transfer-file-from-guest-to-host)
      4. [umount user folder in guest](#umount-user-folder-in-guest)
      5. [TODO: transfer file from host to guest](#todo-transfer-file-from-host-to-guest)
      6. [TODO: the `scp` resolution](#todo-the-scp-resolution)
4. [vmware bugfix](#vmware-bugfix)
   1. [vmware](#vmware)
   2. [:white_check_mark: `fuse: bad mount point 'mnt/hgfs': Transport endpoint is not connected`](#white_check_mark-fuse-bad-mount-point-mnthgfs-transport-endpoint-is-not-connected)
   3. [vmware ubuntu filesystem startup](#vmware-ubuntu-filesystem-startup)
      1. [:white_check_mark: `initramfs` problem](#white_check_mark-initramfs-problem)
      2. [:white_check_mark: `Stuck at fsck "/dev/sda1: clean xxx/xxx files [...] " after upgrade to Ubuntu 16 from 14`](#white_check_mark-stuck-at-fsck-devsda1-clean-xxxxxx-files---after-upgrade-to-ubuntu-16-from-14)
   4. [:white_check_mark: vmware change `super` key, so that the `command` key won't make the ubuntu react as 'showing all the active applications'](#white_check_mark-vmware-change-super-key-so-that-the-command-key-wont-make-the-ubuntu-react-as-showing-all-the-active-applications)
   5. [disk storage not enough since there are too many deleted versions](#disk-storage-not-enough-since-there-are-too-many-deleted-versions)
      1. [Step 0.1. enable usb driver disk manage (read/write permission)](#step-01-enable-usb-driver-disk-manage-readwrite-permission)
      2. [Step 0.2. umount driver](#step-02-umount-driver)
      3. [Step 0.3. unplug and plug driver](#step-03-unplug-and-plug-driver)
      4. [Step 1. find and go to target driver](#step-1-find-and-go-to-target-driver)
      5. [Step 2. go to trash dir under driver](#step-2-go-to-trash-dir-under-driver)
      6. [Step 3. list all the trash files and rm them (need permission)](#step-3-list-all-the-trash-files-and-rm-them-need-permission)
5. [run emulator on ubuntu vmware](#run-emulator-on-ubuntu-vmware)
   1. [FIXME: unable to run `emulator` after building AOSP](#fixme-unable-to-run-emulator-after-building-aosp)
   2. [FIXME: `emulator: WARNING: system partition size adjusted to match image file (3083 MB > 800 MB)`](#fixme-emulator-warning-system-partition-size-adjusted-to-match-image-file-3083-mb--800-mb)
   3. [FIXME: `Error "context mismatch in svga_sampler_view_destroy" running GUI programs on Ubuntu in a VM`](#fixme-error-context-mismatch-in-svga_sampler_view_destroy-running-gui-programs-on-ubuntu-in-a-vm)
   4. [FIXME: `TSC frequency mismatch between VM and host`](#fixme-tsc-frequency-mismatch-between-vm-and-host)
6. [BEST-PRACTICE: disable side channel mitigations for performance](#best-practice-disable-side-channel-mitigations-for-performance)

## installation

the storage screenshot of installation start

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642237022330-053e8fff5fe8f3e89ed601f005a3f5735089aee559c1e8eb86c7e2700ba30fb7.png" />

## configuration

### cpu

PR: 12 processors (Is it enough? And will it affect the host?)

### memories

PR: 11G for vm, 5G for host (Is it enough? And will it affect the host?)

### disk storage

~~500G. Since the size of AOSP is about more than 200G, so 500G, which is double, is reasonable for that need.~~

> ~~:warning: However, we'd better pre-allocate the disk space for speed, and if we set it later, the machine transfer time would be costly!~~

Update at 2022-01-24:

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642984951132-b4241a818717209d43d9773a05a29b3cf69e69eb3f79deac584fbe5060d022fa.png)

You see, the 500G pre-allocated disk takes up more than 600G, when I just download the AOSP mirror, how could it be?

The answer becomes clear: **The so-called pre-allocated disk size doesn't mean the full size of the disk to be used, but to be only the core running disk size of virtual machine, so that it's unnecessary to pre-allocate a huge size (such as 500G) for it!!!**

Hence, I would just delete the mirror, and re-install one, with no option for pre-allocated size, since I remembered on stackoverflow or anywhere other it said there has no or slight efficiency effect on whether we enable or disable the option pre-allocate.

> :warning: And after I just did nothing to the vmware settings (i.e. 20Gb for vmware), and tried to install the AOSP, it warns me that the disk space is not enough. **So We still need to allocate a big enough disk space, but not a pre-allocated one!**

FIXME: Space not enough!

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642989696716-0982e10a82b7ad3869b46aea88ea67b50d9673294f97132fab2d31fc6245f4ff.png)

但是就很奇怪，因为我重新分配过磁盘大小，理论上来说应该是够的：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642990005066-b159502f78500f58cc060889d19e0b65fc15459c19b31b3c26a6f20bbf6a46fa.png)

算了，暂时没时间研究这个问题了，我先同步再创建一个更大的新的镜像试试吧，顺带验证默认的 shell 支持不支持`# xxx`和`# !IMPORTANT xxx`.

### disk type

I searched the difference between different bus types, and it seems that it's better for me to use the default choice of `scsi`.

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642829938828-c8242d90386b16a1658d2732575863d4953a6cbc2364f6c2685dfa6006bc6ac5.png)

ref:

- [SCSI、SATA 和 NVMe 存储控制器条件、限制和兼容性](https://docs.vmware.com/en/VMware-vSphere/7.0/com.vmware.vsphere.vm_admin.doc/GUID-5872D173-A076-42FE-8D0B-9DB0EB0E7362.html)

- [Solved: SCSI vs SATA in VM hard drive settings. - VMware Technology Network VMTN](https://communities.vmware.com/t5/VMware-Fusion-Discussions/SCSI-vs-SATA-in-VM-hard-drive-settings/td-p/919991)

## vmware best practice

### retina solution

!!!tip 1. 有些帖子说要安装`vmware tools`，但我看我的 vmware 里应该是已经有了，因为当我想点那个按钮的时候，显示的是`reinstall vmware tools`，此外，这个按钮必须是启动了虚拟机后才会可点，而且启动后也不一定可点…… 2. 忘了。。

First, check the `use full solution for retina display`, otherwise the screen is 模糊的（像素化）了。 <img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642246537248-83ff3fd47950c36434e088ebc1ae05b0d4ad2b6cd8c9fc1d617ae0709e396d80.png" />

However, the cost is that all the text or icons then look too tiny, so that can't be used.

The solution is to set the solution of the system and the display scale:

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642246691148-a206fe3f32d14b3b9140908f4ed06c95def396a34750c6c6ac3b483e32bb1fe5.png" />

Then the screen looks real!

But there is still a drawback, that is each time switch the view, the scale would goes back. To solve this, if the virtual machine is a Mac, then adjust the solution via:

```sh
// mac terminal
sudo defaults write /Library/Preferences/com.apple.windowserver DisplaysolutionEnabled -bool true
```

However, if it's a ubuntu, I don't know how to realize it now. PR: ubuntu solution.

At last, the retina solution under full-screen mode:

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642246913466-69d9e7e6680c20b4cb19a746694fe62c24cab09c3bf721a8e10f518a8eaa5d7d.png" />

FIXME: retina solution of default scale size

ref:

- [Enable Retina Display Support](https://docs.vmware.com/en/VMware-Fusion/12/com.vmware.fusion.using.doc/GUID-E142FF07-372C-4952-9AF7-B52865CCDAD1.html)

- [已解决：Ubuntu 13.04（Retina 显示屏）中的分辨率 - VMware 技术网 VMTN](https://communities.vmware.com/t5/VMware-Fusion-Discussions/solution-in-Ubuntu-13-04-Retina-Display/td-p/864271)

- [virtual machine - Guest OS solution (text too small) in vmware workstation 12 player - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/297569/guest-os-solution-text-too-small-in-vmware-workstation-12-player)

explain why ubuntu conflicts with the retina since it's not for high-dpi screen.

- [Solved: solution in Ubuntu 13.04 (Retina Display) - VMware Technology Network VMTN](https://communities.vmware.com/t5/VMware-Fusion-Discussions/solution-in-Ubuntu-13-04-Retina-Display/td-p/864271)

it's useful when start a mac vmware on a mac.

- [在 VMware Fusion 中启用 HiDPI macOS 来宾虚拟机](https://macops.ca/macos-vms-hidpi/)

- [(20 条消息) Retina MBP 的 Windows 虚拟机视网膜屏的显示效果问题总结\_qysh123 的专栏-CSDN 博客](https://blog.csdn.net/qysh123/article/details/19128269?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164224171816780269865282%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=164224171816780269865282&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-19128269.first_rank_v2_pc_rank_v29&utm_term=vmvare+retina&spm=1018.2226.3001.4187)

### config keyboards

#### 1. :sparkles: mac host key

We can specify whether to enable mac host keyboard shortcuts. <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642343093491-9df62f0afaa72f1e81ad499b0a9fe95081e71ebe79589ec795785388c6dee76f.png" />

However, before we do that, we should consider about it carefully that **should you sacrifice your ubuntu experience for the mac multi-tasks or to sacrifice your mac experience for a pure ubuntu use**.

Although there is one option for us to specify which command key for ubuntu, I failed to let it work.

A possible resolution is to config file place: `~/.vmware/preference.ini`, see: 1. not found config file: [sanbarrow.com](http://sanbarrow.com/vmx/vmx-preferences-ini.html) 2. not found config file: [How to change or disable hotkey for VMware Player? - Super User](https://superuser.com/questions/234918/how-to-change-or-disable-hotkey-for-vmware-player)

However(updated@2022-02-12):

不需要替换文件！（也很难找到）

只要在 vmware 的键盘中，添加一个 `Command -> Ctrl` 的映射即可！

然后一切都是如此的丝滑！

妙啊！（折磨了我一个月了 :cry:）

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vmware-howto-1644606761996-f3e8affdcd3913489c008f206df5b06d2905e0022f15e0e4f16f00cb1b16dec0.png)

#### 2. copy paste

!!!warning OUTDATED: use `command -> ctrl` map ! Since the copy paste in linux, are default triggered by the combined key of `ctrl + shift`, so we can specify the key map:

    <img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642344159090-57a3cfb0715bd2f3e9bdc354eb4e34a77b668719d9b0a1084423e9823b10c794.png" />

    ref to [How to Copy Paste in Terminal in Ubuntu and Other Linux](https://itsfoss.com/copy-paste-linux-terminal/#:~:text=On%20Ubuntu%20and%20many%20other,pasting%20text%20in%20the%20terminal.)

    And in fact, since the default select / copy / paste actions in ubuntu is triggered by `ctrl` by default, I can accept to use `ctrl A/C/V` in vm to avoid annoying different problems caused by command.

Only need to map `Command` to `Ctrl`! (updated@2022-02-12)

### vpn proxy

In normal circumstance, the net is okay.

However, since I use clashx, I can visit outer net in my mac, which is a problem that the virtual machine can not share with the foreign net with the host.

#### 1. know what's your ip and vpn port of host machine

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642348196305-8ce3091ff233d927db350b55d3b1d7bbe085fd5b95c381e336e3ebec29f240a4.png" />

#### 2. ensure the net type in vm

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642348303987-40ecf1bc1c2960577d7818c30ce8e980e120734440c4159c6dd9ba68d18ba094.png" />

#### 3. specify the vpn manually in vm

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-1642348157085-5862a3e8b9c18f234019db4d87de6931b5fc9adced178b1ded73de4e5af86000.png" />

### share files between host(mac) and guest(ubuntu)

#### BEST-PRACTICE: use `vmhgfs-fuse` and auto-complete supported

```sh
sudo mkdir -p /mnt/hgfs
sudo vmhgfs-fuse .host:/ /mnt/hgfs -o subtype=vmhgfs-fuse,allow_other
```

ref:

- [linux - No /mnt/hgfs in Ubuntu guest under VMWare Fusion - Super User](https://superuser.com/questions/588304/no-mnt-hgfs-in-ubuntu-guest-under-vmware-fusion)

#### resolution 1. use `/mnt/~`

there are a few of disadvantages:

1. Every time, it needs to re-activate using `sudo vmhgfs-fuse .host:/ /mnt/` (although we can config it in the zsh/bash rc file)
2. It only supports to fetch the host files within the vmware, which means it's uneasy to directly operate on host (not equally designed, or maybe there is another way)
3. FIXME: When using in the vmware, I found there is no auto-completion for files on host.

#### mount host user folder to guest (transfer file from guest to host)

After a little of search, I found the easiest way is:

```sh
sudo vmhgfs-fuse .host:/ /mnt/
```

After this, there is one directory (my mac user folder `mark`) merging up under the ubuntu `/mnt` folder.

And then I can easily to transfer files from vmware to mac.

ref:

- [How do I mount shared folders in Ubuntu using VMware tools? - Ask Ubuntu](https://askubuntu.com/questions/29284/how-do-i-mount-shared-folders-in-ubuntu-using-vmware-tools)

- IMPROVE: the `git` resolution: [14.10 - Files missing in /mnt/hgfs on Ubuntu VM? - Ask Ubuntu](https://askubuntu.com/questions/591664/files-missing-in-mnt-hgfs-on-ubuntu-vm)

#### umount user folder in guest

```sh
sudo umount /mnt
```

Then the folders under `/mnt` would go.

ref:

- [VMware - How to change path to shared folder on ubuntu virtual machine - Stack Overflow](https://stackoverflow.com/questions/56472968/vmware-how-to-change-path-to-shared-folder-on-ubuntu-virtual-machine)

#### TODO: transfer file from host to guest

#### TODO: the `scp` resolution

ref:

- [How to SCP a file from Mac -> Ubuntu VirtualBox? - Ask Ubuntu](https://askubuntu.com/questions/48436/how-to-scp-a-file-from-mac-ubuntu-virtualbox)

## vmware bugfix

### vmware

感觉这个官方解决方案 ["An error occurred while consolidating disks" when deleting one or more snapshots or consolidate disks (2150414)](https://kb.vmware.com/s/article/2150414) 是合适的，就是不知道具体怎么弄：

resolution 1. Free up space on the datastore(s) holding the virtual machine configuration files and virtual disks.

resolution 2. Alternatively, increase the size of the datastore on which the virtual machine is located. For more information, see the vSphere Storage guide.

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vmware-howto-1644766564690-228334db85751f41c5ef2bd3ea4a00f8e8854d5803e5eea784bf235940c696b3.png)

---

基于 [Reclaiming disk space from thin provisioned VMDK files on ESXi (2136514)](https://kb.vmware.com/s/article/2136514) 尝试了一下，结果把磁盘给塞满了……

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vmware-howto-1644766450784-3a1b3ee342b1a2ef28f1dde5f7b4643804c087833d2abe636191d24da0d3d4b2.png)

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vmware-howto-1644766445912-769a5e30f80c70f04c69b781a2d34cc63ff17af74d72c8fb54b14c20e0e68aeb.png)

ref:

- 看似有用，但好似实际没什么用：[Expanding the size of the virtual disk in Workstation fails with the error: There is not enough space on the file system for the selected operation (2041556)](https://kb.vmware.com/s/article/2041556)

### :white_check_mark: `fuse: bad mount point 'mnt/hgfs': Transport endpoint is not connected`

受 [sshfs - fuse: bad mount point `/mnt': Transport endpoint is not connected - Ask Ubuntu](https://askubuntu.com/questions/1090715/fuse-bad-mount-point-mnt-transport-endpoint-is-not-connected) 启发，先取消挂载，再重新挂载即可。

```sh
sudo umount -l /mnt/hgfs
sudo vmhgfs-fuse .host:/ /mnt/hgfs
```

### vmware ubuntu filesystem startup

#### :white_check_mark: `initramfs` problem

problem:

![picture 166](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-bugfix-1643354758760-ad81de24848fdfdbcb4b14d280404f4f56a743a88becb981ea81ae7a91812dbe.png)

resoluton:

![picture 167](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-bugfix-1643354775857-63b6fb477a82a5fa5ff41fde21fe78f63501b7ce7e8047bc86e5a108aaf5a9c6.png)

1. 先用`fsck -yf /dev/sda1`自动修复文件系统
2. 再`exit`就可以重新登录了

oK:

![picture 165](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-bugfix-1643354743918-a663bf57d5e3cdb6cd4747194cd0bb7b859ae4a56b5cc33b2785390b769d3f94.png)

ref:

- core ref: [boot - Root file system requires manual fsck - Ask Ubuntu](https://askubuntu.com/questions/885062/root-file-system-requires-manual-fsck)

#### :white_check_mark: `Stuck at fsck "/dev/sda1: clean xxx/xxx files [...] " after upgrade to Ubuntu 16 from 14`

problem:

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-bugfix-1643439292142-86bee800c2dbb7fe4a6ee1906d669ee86016bc2e01545c41544917c8ed28e349.png)

reason:

disk is full, and we need to free some space.

resolution:

1. `Ctrl + Alt + F1 or F2` into `tty2 login`
2. `df -h` says `/dev/sda1` is 100% used
3. delete some files, e.g. I deleted android-8 dir of 100+ MB size
4. `reboot`, and the problem is gone.

ref:

- [boot - Stuck at fsck "/dev/sda1: clean xxx/xxx files [...] " after upgrade to Ubuntu 16 from 14 - Ask Ubuntu](https://askubuntu.com/questions/923899/stuck-at-fsck-dev-sda1-clean-xxx-xxx-files-after-upgrade-to-ubuntu-16)

### :white_check_mark: vmware change `super` key, so that the `command` key won't make the ubuntu react as 'showing all the active applications'

解决方案：直接把`command`键映射到`ctrl`键即可。

> ref

- [Enable or Disable Mac Host Shortcuts on the Keyboard and Mouse Preference Pane](https://docs.vmware.com/en/VMware-Fusion/12/com.vmware.fusion.using.doc/GUID-A50D0E3C-9549-43B5-AB57-070F805780A3.html)

### disk storage not enough since there are too many deleted versions

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642825099629-aec3eeb09c30c5fc864fcb14d5644833ae1dc7a191ee4ea018a596e771e34f64.png)

#### Step 0.1. enable usb driver disk manage (read/write permission)

```sh
defaults write com.apple.Finder AppleShowAllFiles TRUE
```

#### Step 0.2. umount driver

```sh
sudo umount /Volumes/T7
```

ref:

- [How to fix read-only usb drive? - Ask Ubuntu](https://askubuntu.com/questions/1004827/how-to-fix-read-only-usb-drive)

#### Step 0.3. unplug and plug driver

重新插拔 usb

#### Step 1. find and go to target driver

```sh
cd /Volumes/T7
```

#### Step 2. go to trash dir under driver

```sh
cd .Trashes/501
```

#### Step 3. list all the trash files and rm them (need permission)

```sh
sudo ls -la

sudo rm -rf ...
```

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/virtual-machine-howto-1642828955318-c584f6745ebbfd6cda042aaf83b2bc6e991923213708127e788084b44a6136d5.png)

## run emulator on ubuntu vmware

### FIXME: unable to run `emulator` after building AOSP

A possible resolution may be to `lunch full-eng && m` which is suggested in [Unable to run emulator after building AOSP](https://groups.google.com/g/android-building/c/YZOr5YCIQgo), and now I am testing this solution.

ref:

- [Unable to run emulator after building AOSP](https://groups.google.com/g/android-building/c/YZOr5YCIQgo)

- [Why I can't launch Android emulator after i make the source of Android 6.0? - Stack Overflow](https://stackoverflow.com/questions/36787229/why-i-cant-launch-android-emulator-after-i-make-the-source-of-android-6-0)

### FIXME: `emulator: WARNING: system partition size adjusted to match image file (3083 MB > 800 MB)`

A possible resolution:

```sh
 emulator -partition-size XXX # XXX is the desired size(MB)
```

However, maybe my system is limited since when the size exceeds 2048MB, another problem would arise up....

ref:

- [(23 条消息) 编译 android 源码四(常见错误)\_luhuajcdd 的专栏-CSDN 博客](https://blog.csdn.net/luhuajcdd/article/details/8786925)

### FIXME: `Error "context mismatch in svga_sampler_view_destroy" running GUI programs on Ubuntu in a VM`

In [vmware player - Error "context mismatch in svga_sampler_view_destroy" running GUI programs on Ubuntu in a VM - Stack Overflow](https://stackoverflow.com/questions/47150110/error-context-mismatch-in-svga-sampler-view-destroy-running-gui-programs-on-ub), it suggests me to set `SVGA_VGPU10=0` or to uncheck the `Accelerate 3D Graphics`, but all in vain...

### FIXME: `TSC frequency mismatch between VM and host`

ref:

- [android - TSC frequency mismatch between VM and host - Stack Overflow](https://stackoverflow.com/questions/57677258/tsc-frequency-mismatch-between-vm-and-host)

## BEST-PRACTICE: disable side channel mitigations for performance

1. power off virtual machine
2. disable side channel mitigations

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vmware-howto-1644888878677-624063d11f3c8f3cc0d4d1d098777847620cfc74000db104d5f59907719a7a7f.png)

ref:

- [VMs with side channel mitigations enabled may exhibit performance degradation (79832)](https://kb.vmware.com/s/article/79832)
