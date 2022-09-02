# vmware

## feat: config wifi

1. 在虚拟机外部设置里，选择 wifi（不要用`share with my mac`选项），这样可以获得一个局域网内的ip身份
2. 虚拟机内部 `Settings - Network - Network Proxy` 里设置对应的 clashx vpn （TODO: 具体步骤）

## feat: enabled host sharing

直接参考： [Enabling HGFS Shared Folders on Fusion or Workstation hosted Linux VMs for open-vm-tools (74650)](https://kb.vmware.com/s/article/74650)

## feat: fixed Ubuntu resolution and copy/paste shortcuts in vmware

resolution:

```sh
sudo apt-get install open-vm-tools-desktop
```

see: - [Copy and paste between Mac and Ubuntu using keyboard shortcuts via VMware Fusion - Ask Ubuntu](https://askubuntu.com/questions/615637/copy-and-paste-between-mac-and-ubuntu-using-keyboard-shortcuts-via-vmware-fusion)