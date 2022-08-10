# bjjkb forge

## TODO: 了解小程序的运行逻辑

## 方案分析

| seq | title                              | detail |
| --- | ---------------------------------- | ------ |
| 1   | 基于电脑端的抓包软件修改返回包     | yyy    |
| 2   | 基于 vpn 在服务端修改返回包        | 1      |
| 3   | 使用移动端网络框架修改返回包       | 1      |
| 4   | 使用移动端数据修改工具修改本机数据 | 1      |
| 5   | 原生仿制开发一款小程序或者 app     | 1      |

## 接口

### 核酸检测 （hsjc）

### 疫苗接种 （ymjz）

response:

```json
{
  "data": {
    "hideIdCard": "32**************19",
    "hideName": "?**",
    "size": "0",
    "vaccComFlag": "-1"
  },
  "errcode": "BIS:10200",
  "errmsg": null
}
```

其中`vaccComFlag`字段就是接种信息，-1、0 都是未接种，1 是普通接种，2 及以上是加强接种。

更改如下：

## 方案一：基于电脑端的抓包软件修改返回包

## 方案二：基于 vpn 在服务端修改返回包

### mitmproxy

#### 版本不够：`http module has no Response`

看了一下版本，python 3.6，mitmproxy 5 点几，而我 mac 上 python 是 3.9，mitmproxy 8.1.1……

```text
(.pyenv) 2022/07/10 00:20:54 (base) ➜  mark_keeps_learning git:(master) ✗ mitmdump --version
Mitmproxy: 8.1.1
Python:    3.9.12
OpenSSL:   OpenSSL 3.0.3 3 May 2022
Platform:  macOS-10.16-x86_64-i386-64bit
```

差太大了，所以应该升级一下。

#### centos 安装 `python 3.9`

see: [使用国内镜像下载地址，编译安装 Python3.9 最新版](https://www.51jiejue.com/ops/python3-install-by-url-from-china.html)

```sh
yum install gcc openssl-devel bzip2-devel libffi-devel -y

cd /tmp
VERSION=3.9.13
wget https://mirrors.huaweicloud.com/python/${VERSION}/Python-${VERSION}.tgz
tar -zxvf Python-${VERSION}.tgz

cd Python-${VERSION}
./configure --enable-optimizations
make altinstall

# 检查安装状态
python3.9 -V
#Python ${VERSION}
```

#### json 响应里中文乱码

现象：

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jkb_bj_forge-howoto-1657381608253-1f3a7bc810a0dac61f572da490348ed7bb56dfb40eb3f121e2476b55b2241c6b.png)

解决方案：

```sh
# 1. 检查系统的编码种类
locale -a

# 2. 找到其中最合适的utf-8相关的编码，并配置（如果不行，多来回配几次，并重新启动mitmproxy，检查里面的中文响应，我是这样成功的）
export LC_CTYPE=zh_CN.utf8
```

相关参考：

- 这是一篇直接描述这个问题的官方 issue，然而并没有什么答案：[Response json mode with chinese character display as ?? · Issue #3231 · mitmproxy/mitmproxy](https://github.com/mitmproxy/mitmproxy/issues/3231)
- 在考虑到可能是 terminal 编码的问题后，搜索到了：[macOS setlocale: LC_CTYPE: cannot change locale (UTF-8): No such file or directory - nixCraft](https://www.cyberciti.biz/faq/os-x-terminal-bash-warning-setlocale-lc_ctype-cannot-change-locale/)，遂得以解决

#### 被肉鸡扫描

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jkb_bj_forge-howoto-1657377946136-4e62c67bbf690801346632552ccf299483d39c58f56b942f69731c75e3e83731.png)

### squid

请求成功，但是 https 被挡住的示例：

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jkb_bj_forge-howoto-1657353248542-766768e825d021d3faf164c0cdb7ba9a3eb1af89c2bd821064e071a511ab23d0.png)

### OpenVpn

在 ubuntu 上创建 openvpn server 的教程：[Ubuntu 18.04 LTS Set Up OpenVPN Server In 5 Minutes - nixCraft](https://www.cyberciti.biz/faq/ubuntu-18-04-lts-set-up-openvpn-server-in-5-minutes/)

讨论在 openvpn 上劫持流量的可行性：

- [intercept traffic on an OpenVpn Server? · Issue #1017 · mitmproxy/mitmproxy](https://github.com/mitmproxy/mitmproxy/issues/1017)
- [OpenVPN Modify incoming traffic or payload with custom script - Server Fault](https://serverfault.com/questions/1077489/openvpn-modify-incoming-traffic-or-payload-with-custom-script)
- [https - Modify request from Open VPN server - Stack Overflow](https://stackoverflow.com/questions/65122190/modify-request-from-open-vpn-server)

## 方案三：使用移动端网络框架修改返回包

结论：此路不通，我们不可以通过开发一个 app 去劫持其他 app 的通信包。

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/jkb_bj_forge-howoto-1657343165295-7a7cdc5425dfd81dad3800b2af2f636148356428002078a4e07c6f8b8120c2d9.png)

介绍`NSURLProtocol`:

- [iOS 网络请求劫持\_uweiyuan 的博客-CSDN 博客\_ios 网络请求拦截](https://blog.csdn.net/forwardto9/article/details/60764870)
- [iOS 中 NSURLProtocol 黑魔法的使用 - 简书](https://www.jianshu.com/p/ae5e8f9988d8)
- [使用 NSURLProtocol 拦截 APP 内的网络请求 - 掘金](https://juejin.cn/post/6844903473671077895)
- [NSURLProtocol 全攻略 - 简书](https://www.jianshu.com/p/02781c0bbca9)

一个貌似封装了 NS 的专门用于劫持 http 的 ios 框架：

- [A little and powerful iOS framework for intercepting HTTP/HTTPS Traffic](https://iosexample.com/a-little-and-powerful-ios-framework-for-intercepting-http-https-traffic/)

## 方案四：使用移动端数据修改工具修改本机数据

## 方案五：原生仿制开发一款小程序或者 app
