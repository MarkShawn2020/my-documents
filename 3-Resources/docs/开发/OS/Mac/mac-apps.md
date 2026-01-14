# mac apps

1. [recommended apps](#recommended-apps)
   1. [Afloat](#afloat)
   2. [iTerm](#iterm)
   3. [cheatsheet: customize app shortcuts](#cheatsheet-customize-app-shortcuts)
2. [app:iTerm](#appiterm)
   1. [set selection with ":" for vim](#set-selection-with--for-vim)
3. [app:afloat](#appafloat)
4. [app:calculator](#appcalculator)
   1. [显示历史记录](#显示历史记录)
5. [安装历史](#安装历史)

## recommended apps

### Afloat

### iTerm

### cheatsheet: customize app shortcuts

## app:iTerm

### set selection with ":" for vim

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-apps-1645197907114-de8d9ca4e8ae371685f7c0c79dd9b6f6b01e0e10686a49faf020c6d09c0fc94f.png)

ref:

- [terminal - iTerm Double Click Text Selection - Ask Different](https://apple.stackexchange.com/questions/333474/iterm-double-click-text-selection)

## app:afloat

based on `SIMBL`

I followed the official instruction on how to install `afloat`:

```sh
# use vpn for `curl` to fetch `raw.githubusercontent.com`
IP=localhost
PORT=7890
export https_proxy=http://$IP:$PORT http_proxy=http://$IP:$PORT all_proxy=socks5://$IP:$PORT

curl https://raw.githubusercontent.com/rwu823/afloat/master/install.sh | sh
```

It tells me that the installation is successful:

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-apps-1644559863824-a93f95e9720b794c6979373295036f6e377af1f978aac24eccddffeadccc0644.png)

However, I can't see the `afloat` options in `Window` menu...

TODO: Maybe I need the `SIMBL`.

## app:calculator

### 显示历史记录

`Command + T`

ref:

-[macos - Enable calculation history on OS X Calculator app? - Ask Different](https://apple.stackexchange.com/questions/223543/enable-calculation-history-on-os-x-calculator-app)

## 安装历史

| date | item | operation | reason | note |
| --- | --- | --- | --- | --- |
| 2022-02-07 | `brew install npm` | install | for npm of `webtorrent-cli` | result: ![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/mac-install-history-1644223596619-f049e7c3d49f7351c4a98f8ee9ef4c242a08c995837530d919586ad9e763ff77.png) |
| 2022-02-07 | `brew install automake autoconf libusb` | install | for `rkdeveloptool` | source: <br/> - [Rockpi4/install/rockchip-flash-tools - Radxa Wiki](https://wiki.radxa.com/Rockpi4/install/rockchip-flash-tools#Part_three:_rkdeveloptool_on_macOS.28Intel_.26_Apple_Silicon.29) |
| 2022-02-07 | etcher | install | - | source: <br/> - [balenaEtcher 1.7.3 for Mac U 盘启动盘制作工具](https://macwk.com/soft/balenaetcher) |
| 2022-02-07 | vmware | install | - | source: <br/>- [VMware Fusion Pro 12.2.1 中文破解版 for Mac mac 虚拟机工具](https://macwk.com/soft/vmware-fusion) |
