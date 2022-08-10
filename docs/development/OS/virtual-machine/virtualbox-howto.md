# virtualbox

1. [盘符切换（盘已满）](#盘符切换盘已满)
2. [:white_check_mark: 分辨率切换](#white_check_mark-分辨率切换)
3. [:white_check_mark: Fixed: `Develop on a Linux computer that supports VT-x or SVM`](#white_check_mark-fixed-develop-on-a-linux-computer-that-supports-vt-x-or-svm)
4. [:white_check_mark: Fixed: `emulator: ERROR: Can't get kernel version from the kernel image file: '/home/mark/android/prebuilts/qemu-kernel/arm/ranchu/kernel-qemu'`](#white_check_mark-fixed-emulator-error-cant-get-kernel-version-from-the-kernel-image-file-homemarkandroidprebuiltsqemu-kernelarmranchukernel-qemu)
5. [启用 Hypervisor(虚拟机加速)](#启用hypervisor虚拟机加速)
6. [运行模拟器](#运行模拟器)

## 盘符切换（盘已满）

在解压 android 源码过程中，发现 windows 宿主机的 C 盘空间急剧减少，说明当时安装 virtualbox 的默认位置在 C 盘，但是我的 C 盘只有 200 多 G。

查询了一点文章后，发现只要把`vdi`文件转移即可。

于是我找到了 C 盘目录下的 virtualbox 文件夹，然后将它整体移到 D 盘，并且修改 virtualbox 中所有和路径相关的属性。

## :white_check_mark: 分辨率切换

在虚拟机内，点击`设备 | 安装增强功能`，装完之后，在桌面上会有个挂载，实际上是在`/media/mark/`下。

然后进入文件夹，`sudo sh VBoxLinuxAdditions.run`，就能自动安装相关增强工具，接着在虚拟机右上角点击重启即可。

之后虚拟机的界面就可以手动拉升了，并且不损失分辨率，否则基于系统内置的显示，只可以缩放，会很模糊。

## :white_check_mark: Fixed: `Develop on a Linux computer that supports VT-x or SVM`

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642426586567-5dd5004fa15434f9f54bbbaba0c464a62e21654e1922b3cf51b50e0886e6bbf5.png)

Solution: 关闭虚拟机，然后启用 virtualbox 里的虚拟选项即可：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642477539269-0c2cf882af6d4dc2287d208df41471648a21a4759a39bf0c0bf3b4fffe158e5b.png)

Evidence: 打开 Android studio 里的 avd，已经不提示虚拟化报错了：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642477595429-2294709782ed8ec7740920ff48eb0660e561c223fc302d874464678b4158d6bb.png)

ref:

- [virtualbox.org • View topic - VT-x error This computer does not support Intel Virtualizati](https://forums.virtualbox.org/viewtopic.php?f=6&t=69076)

- [How to enable Intel VTx and AMD SVM for QNAP NAS? | QNAP](https://www.qnap.com/en/how-to/faq/article/how-to-enable-intel-vtx-and-amd-svm-for-qnap-nas)

- [linux - Enabling the VT-x inside a virtual machine - Stack Overflow](https://stackoverflow.com/questions/24340272/enabling-the-vt-x-inside-a-virtual-machine)

## :white_check_mark: Fixed: `emulator: ERROR: Can't get kernel version from the kernel image file: '/home/mark/android/prebuilts/qemu-kernel/arm/ranchu/kernel-qemu'`

You should download one emulator first, such as in the android studio AVD.

## 启用 Hypervisor(虚拟机加速)

```sh
$ ~/Android$ ./Sdk/emulator/emulator -accel-check
accel:
0
KVM (version 12) is installed and usable.
```

```sh
➜  Android ./Sdk/emulator/emulator -accel-check
ProbeKVM: This user doesn\'t have permissions to use KVM (/dev/kvm).
The KVM line in /etc/group is: [kvm:x:998:mark]

If the current user has KVM permissions,
the KVM line in /etc/group should end with ":" followed by your username.

If we see LINE_NOT_FOUND, the kvm group may need to be created along with permissions:
    sudo groupadd -r kvm
    # Then ensure /lib/udev/rules.d/50-udev-default.rules contains something like:
    # KERNEL=="kvm", GROUP="kvm", MODE="0660"
    # and then run:
    sudo gpasswd -a $USER kvm

If we see kvm:... but no username at the end, running the following command may allow KVM access:
    sudo gpasswd -a $USER kvm

You may need to log out and back in for changes to take effect.

accel:
11
This user doesn\'t have permissions to use KVM (/dev/kvm).
The KVM line in /etc/group is: [kvm:x:998:mark]

If the current user has KVM permissions,
the KVM line in /etc/group should end with ":" followed by your username.

If we see LINE_NOT_FOUND, the kv
accel
```

ref:

- [为 Android 模拟器配置硬件加速  |  Android 开发者  |  Android Developers](https://developer.android.com/studio/run/emulator-acceleration#hypervisors)

## 运行模拟器

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642484534629-67ed469bdcfb204bdd23a52bdf55d2b1fa6239641dfa8b0165070dd834aecbf1.png)
