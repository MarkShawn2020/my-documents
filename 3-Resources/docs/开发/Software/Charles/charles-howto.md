# charles howto

## config

### install root certificate

我在选择 `Login Item` 后发现无法装入 certificate，但可以选择 `System` 或者 `Login`。显然，`System`级别更高，我们装这个就可以。不过要注意两点，第一点就是在这里要点 trust。

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/charles-howto-1646061342760-94a519c6c19f44acbd24ff11457d32886e5922c5f603ca2e566ebd20079c9224.png)

第二点，还没完，在 `KeyChains` 里搜索 charles，然后找到我们的`System` charles，再 trust 一下：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/charles-howto-1646063051006-191958465c1eace4940c7491679cd4ae3fed99eaec8a4c6640f7ed4fc1205af1.png)

接下来参照 [Charles mac 版本进行 https 抓包的配置方法\_chirpmonster 的博客-CSDN 博客\_charles mac ssl](https://blog.csdn.net/chirpmonster/article/details/121905952) 只需要保证我们的 proxy settings 里面 http 选项是打钩的就可以（其实貌似也是默认设置了）：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/charles-howto-1646063139400-08250f60b7083184aae4beb8c3d6df700974eece18d9bea809d0a7d736e72558.png)

## charles and vpn

目标就是实现在访问外网的同时还能使用 charles。

其实我中途配起来过，结果以为不行，这里之所以会有这个原因，实际上是两个只能有其中一个当做系统代理，很显然，我们应该把 charles 当做系统代理，毕竟它是枢纽，但是这个时候回导致 vpn（clashx）图标变灰，以为不生效，但实际上如果我们访问一个网页，会发现 clashx 后面会有网速显示，另外我们也可以通过打开谷歌测试，发现确实是起作用的。这是容易让人迷惑的一点，即 clashx 灰了（没有作为系统代理），但实际依旧起作用。

具体做法很简单，就是在 charles 中配置外部代理，我这里配的是 clashx 的局域网地址，但实际上由于在同一个网下，配成 localhost 也是可以的。另外，直接配 socks proxy 就可以，http 都不用（因为 socks 更高级）。

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/charles-howto-1646063867092-50082661443651f70cf6e3d5219735e6234a303ddb6b2654121ac6df80756af4.png)

ref:

- [Charles 与 Shadowsocks 共存 - 51Testing 软件测试网](http://www.51testing.com/html/19/n-3727219.html)
