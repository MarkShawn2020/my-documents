# ubuntu 18.04.6 LTS 虚拟机指南

## 1. 配置网络

比画面更要先配置，因为配置其他的大多数都要网络

测试网络通畅：（不要用`ping`，`ping`不等于实际网络效果，直接用火狐打开百度、谷歌测试）

### vpn桥接

只要把主机ip地址（`localhost`不行）与端口配置在http即可

![picture 3](.imgs/full-guide_ubuntu-in-vmware-1663146396647-0cd496b89408bfd8ddf553bc9233d09fcd5f8e2ecc63e246910ef58d63a3ce0c.png)  
 
如果不行的话，还要确定 vpn 软件是否开启了局域网

![picture 4](.imgs/full-guide_ubuntu-in-vmware-1663146484586-64c7c7e1e95d8e889ddae155ff73fea200f9edc0cc08c8b0a0df721585c0603b.png)  

如此可以通过火狐上网。

### 环境变量配置

配置成 自动（wifi）模式后，再配置一下 proxy 和 deb source，即可使用apt

![picture 5](.imgs/full-guide_ubuntu-in-vmware-1663147163153-878049e7a6ed2afef9fa8c9a70114c5089d4bf8129b3862750e9403f6f9d603b.png)  

```sh
# change apt sources to speed up apt
sudo sed -i.bak -r  "s|deb \S+|deb http://mirrors.yun-idc.com/ubuntu/|g" /etc/apt/sources.list
```

```sh
# change proxy envs
export PROXY=192.168.1.246:7890
export proxy=$PROXY
export https_proxy=$PROXY

sudo apt update
sudo apt upgrade
```

## 配置界面

首先是虚拟机界面，确保开启了 retina 选项：

![picture 6](.imgs/full-guide_ubuntu-in-vmware-1663148898692-00b615c34a41ef0ef8ba1b8374e7f2157d7621c6b05af956f304384ceac825a0.png)  

其次retina一般要对应放缩比例（为2），但启用这个需要重新装一下 `vm-tools`：

```sh
# ref: https://askubuntu.com/a/824341/1629991
sudo apt install open-vm-tools-desktop
```

:::tip
设置界面的这个 `(Re)Install Vmware Tools` 是没用的，可以无视

![picture 7](.imgs/full-guide_ubuntu-in-vmware-1663148956529-97f8f8a8252409f88f27c1b59bf149ff08ebd5f6c707e23aecc54b03f2fb811b.png)  

重要的是要在命令行里安装 `open-vm-tools-desktop`
:::

理论上无需重启，不然的话，再配置一下以下，然后重启：

```sh
# ref: https://askubuntu.com/a/1313971/1629991
gsettings set org.gnome.desktop.interface scaling-factor 2

# ref: https://askubuntu.com/a/1369571/1629991
gsettings set org.gnome.mutter experimental-features "['scale-monitor-framebuffer']"
```

## 配置复制粘贴

尽管我们已经在设置里启动了沙箱隔离里复制粘贴、拖拽选项：

![picture 9](.imgs/full-guide_ubuntu-in-vmware-1663149079265-d849ee71f1dfe67ff1a7104bf74b878111e68ab3981ea93556543efff5ac75ae.png)  

但我们实际上还是不能正常使用剪切板等功能的（即使是在安装了`open-vm-tools-desktop`之后）：

![picture 8](.imgs/full-guide_ubuntu-in-vmware-1663149059174-ce02766e69bd39fbc246729e331844381d983ca61445d2d42b20a830280019b6.png)  

解决办法是在安装了`open-vm-tools-desktop`之后，重启一下！（这个必须重启了）

![picture 10](.imgs/full-guide_ubuntu-in-vmware-1663149214216-eebb1047ac3585c2a439ddc484647ab6bfcc00c500da671e8c2152f47d8d0c3a.png)  

## 配置sudo免密

```sh
echo "$USER ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee -a /etc/sudoers.d/$USER
```

## 安装常用命令行

```sh
sudo apt install -Y git curl wget terminator zsh vim tmux htop
```

### 配置 `oh-my-zsh`

```sh
# `curl, git` needs
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

### 配置 `vim-plug`

TODO: 

## 磁盘共享

### from host to remote

- best recommended: https://askubuntu.com/a/1051620/1629991
- more fundamental one: https://kb.vmware.com/s/article/60262

### TODO: from remote to host

see:

- [via ` Disk Internal's Linux Reader (windows only)`](https://superuser.com/a/1077650/1365851)
- https://superuser.com/questions/67636/vmware-workstation-how-to-access-the-virtual-disk-from-the-host-system

## 性能优化

### 磁盘：关闭测通道缓冲

![picture 11](.imgs/full-guide_ubuntu-in-vmware-1663150798868-7fbad6712c34b901a220e3f19164c2d76ff9d5f012f696dbfd962f2a3bce72c2.png)  

### 磁盘：开启 `IOMMU`

![picture 12](.imgs/full-guide_ubuntu-in-vmware-1663150811861-9351c760199bea9ae5bfaa9a42f8a3c416261b494d5e69868a487178a4eff2e1.png)  
