# cross-platform howto

1. [mouse/keyboard sharing solution: synergy](#mousekeyboard-sharing-solution-synergy)
2. [移动硬盘双系统](#移动硬盘双系统)
   1. [download url](#download-url)
   2. [make the usb driver](#make-the-usb-driver)
      1. [1. Erase](#1-erase)
      2. [2. Partition](#2-partition)
      3. [3. burn](#3-burn)
   3. [start up the driver](#start-up-the-driver)
      1. [1. security level](#1-security-level)
      2. [2. mouse and keyboard](#2-mouse-and-keyboard)

## 多机共享系统

### 使用 smb 共享 mac 与 ubuntu 的文件系统

在 ubuntu（虚拟机）上运行：`sudo apt-get install samba samba-common`

打开位于本机的文件资源管理器（mac、windows、ubuntu 都有），添加网络位置，输入我们的远程机地址：

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655278108373-60734b6ad29c56643846a3bd75f20cade1e216e2cd343fde51c352fc3a0933d3.png)

输入密码，点击永久保存：

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655278182241-0e3ffc90c4123f419716145613f655bf8e4fb4f38f0b402aa7016a143308dfc6.png)

然后就可以看到远程机的共享目录了，可以看到连我连接的外接磁盘都能访问：

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655278458372-7394dd8bd923691463a0dbac5cecfe6ee7d32f8d0171149f5d161e5605485256.png)

其中我的主工作文件夹`mark`的访问权限在 mac 上是在`Sharing`里配置的：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655278506883-75ee075f13b42d349c340c94efb21a1da251444ffcba0489ba00196d79a17031.png)

然后就可以传输数据了，但其实我实际体验下来，速度根本不够快，才 20 兆每秒，因为基于局域网所以传输速度上限取决于我的家庭带宽：

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655278575848-00f4104feb8932ae10fb751589267603907fbf59e1c3feeda6ae9b0b4f3c7d7f.png)

因此不如`hgfs`，因为它走的是本地磁盘系统，而我们使用的固态移动硬盘，传输速度可以达到 GB 每秒。

### 使用 hgfs 传输

#### 配置 hgfs

```sh
# default hgfs
sudo vmhgfs-fuse .host:/ /mnt/hgfs/ -o allow_other -o uid=1000

# specify shared path
sudo vmhgfs-fuse .host:/shared /mnt/hgfs/shared -o allow_other -o uid=1000
```

写入`~/.bash_profile`：

```sh
if [ -z "$(ls /mnt/hgfs)" ];
    then
        echo "exec: vmhgfs-fuse the host"
        sudo vmhgfs-fuse .host:/ /mnt/hgfs/ -o allow_other -o uid=1000
    # else echo "existed"
fi
```

#### 传输效果

咦？只比 smb 快一倍诶。。。还以为至少能有百兆……

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655280488730-9944a74431c1ca3d1c7259d18a06c9e62e89b22e85e3e817243d754ec40d3c23.png)

啊啊啊！起飞了！

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655280543387-2a2509fb82ecf63250d393b341d0c8933f1de22e3273c30c93b189608e922d64.png)

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/cross-platform-howto-1655280559961-3759d813d689599672712cfe219fa9d1a48fd7086feb487ff72e62821a67defd.png)

ref:

- [VMWARE + LINUX: How to share folder between host and VM | by Alexandre Rosseto | Medium](https://alexandrerosseto.medium.com/vmware-linux-how-to-share-folder-between-host-and-vm-62e63419ecbb)

## mouse/keyboard sharing solution: synergy

synergy download tutorial:

- [Synergy 软件下载和配置 - Wenshan's Blog](https://tianws.github.io/skill/2019/04/20/synergy/)

binary download (including mac, windows, ...)

- [Downloads [Free] | Synergy](https://www.brahma.world/synergy-stable-builds/)

:sparkles: synergy activate code generation url: cpp.sh/3njw3

synergy login

- [Account login](https://symless.com/synergy/account-login?redirect=https%3A%2F%2Fsymless.com%2Fsynergy%2Fdownload)

## 移动硬盘双系统

### download url

ref: [Ubuntu 18.04.6 LTS (Bionic Beaver)](https://releases.ubuntu.com/18.04/)

### make the usb driver

tutorial：

- [How to install Ubuntu on MacBook using USB Stick - Community Help Wiki](https://help.ubuntu.com/community/How%20to%20install%20Ubuntu%20on%20MacBook%20using%20USB%20Stick?_ga=2.41925025.2050799470.1642285216-1877619439.1642285216)

#### 1. Erase

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642279978284-4c597c9ff23897782129952d6c2039dcb0b1eb6382c7b656cbd28bd36948f76b.png" />

ref: https://apple.stackexchange.com/a/346795

#### 2. Partition

<img alt="picture 11" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642280156269-cfa1ebcb5c69800f8d82191e27a13e35d7f8d8ad5c240e6b485af635a2755e18.png" />

#### 3. burn

### start up the driver

#### 1. security level

#### 2. mouse and keyboard

In this [boot - Booting Ubuntu (or any other Linux) from MacBook Pro 2020 - Ask Different](https://apple.stackexchange.com/questions/393242/booting-ubuntu-or-any-other-linux-from-macbook-pro-2020), it introduced the same problem and provided some solutions:

1. paid version of `LivelyLinux` at link [Ubuntu Linux USB Installations | LivelyLinux](https://www.livelylinux.com/products.php) (a little slow)

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1642298074095-14dae567fd1daea8aba5506bf908e3ec3c44b4a2a481719cbde66a400c2349f4.png" />

2. dual boot at [seamusdemora.github.io/LinuxOnLate2011.md at master · seamusdemora/seamusdemora.github.io](https://github.com/seamusdemora/seamusdemora.github.io/blob/master/LinuxOnLate2011.md), but I can't understand it.
