# aosp compile bugfix

1. [error: `soong bootstrap failed with: exit status 1`](#error-soong-bootstrap-failed-with-exit-status-1)
2. [`Killed`, such as when building `Metalava`](#killed-such-as-when-building-metalava)
3. [FIXED: build error of `build/core/ninja.mk:148: recipe for target 'ninja_wrapper' **failed`](#fixed-build-error-of-buildcoreninjamk148-recipe-for-target-ninja_wrapper-failed)
4. [FIXED: build error of `java`](#fixed-build-error-of-java)
   1. [conclusion of installing java openjdk-8](#conclusion-of-installing-java-openjdk-8)
   2. [detail (learned from hbw)](#detail-learned-from-hbw)
5. [FIXED: jack-server error](#fixed-jack-server-error)
6. [FIXED: 去除本地化编译](#fixed-去除本地化编译)
7. [FIXED: `libclang_rt.scudo-aarch64-android.so: No such file or directory`](#fixed-libclang_rtscudo-aarch64-androidso-no-such-file-or-directory)
   1. [solution: `make clean`](#solution-make-clean)
   2. [failed try](#failed-try)
8. [FIXME: `FAILED: ** android.test.mock.docs.system_removed.txt`](#fixme-failed--androidtestmockdocssystem_removedtxt)

## error: `soong bootstrap failed with: exit status 1`

试一下在编译前执行`export LC_ALL=C`，修改 `build/soong/java/config/config.go` 将`pctx.StaticVariable("JavacHeapSize", "2048M")`的 2048 改为你虚拟机内存大小的一半。再编译。

ref:

- [Android 源码编译报错 - H:华硕(tinkerboard/tinikerboard S) - 深圳风火轮科技 - Powered by Discuz!](https://www.smartfire.cn/thread-5520-1-1.html)

## `Killed`, such as when building `Metalava`

problem:

![picture 86](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643245472132-c33793acb397b841dac7407d7db9adfb8e49c9f76aba37117579fbc859b65ea3.png)

![picture 85](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643245447603-ffd15cce966a259b69970e9c92dc3b8f67110ba62822d1a537a15c96e9cf734b.png)

reason: `Metalava` needs more memory to build.

![picture 84](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643245399476-129bf2e8c98f0e65d7baa1027057f339eb945cb75577febdd92bc403b1d6a40f.png)

solution: use a smaller `j`:

![picture 87](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643246001438-1bfcaa1ddfbdf70aa5c22c4273a6ad9e6269a2319d89f51a8b3d563f56f395da.png)

ref:

- [android - AOSP ninja build stopped: subcommand failed - Stack Overflow](https://stackoverflow.com/questions/58886407/aosp-ninja-build-stopped-subcommand-failed)

## FIXED: build error of `build/core/ninja.mk:148: recipe for target 'ninja_wrapper' **failed`

error scene:

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643010572471-a9f3bdf4834792c7817d2ac8de58f96efa3e38c00be4f0866ad3ecd624430bae.png)

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643010743857-1a71e002fa5d44c8fde20d0972b3da44cfb1bc5e85c637b639160be44dfbdb09.png)

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643011164016-79b647aae33990fd2d5d544a3b3159d11a59e1a47bc49e143776d665dc2b36b5.png)

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643011240375-f21552ffdfac7dfa8638bfbe106a218c54427008855e534b0c0f659c7c1e3c81.png)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643044506432-90fd7ec3ea979dcb61aa80be3396e41cac0676a824f56f0a1fe8dcca6e4f3648.png)

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643050346260-77c9c49942962ca3378103f6da75f52281d9a5c12538ffb25110eb441f85c0d0.png)

ref:

- core: [Ubuntu18.04 编译问题 · 大专栏](https://www.dazhuanlan.com/pucool/topics/969735)

- [android - recipe for target 'ninja_wrapper' failed / flex core dumps - Stack Overflow](https://stackoverflow.com/questions/54547246/recipe-for-target-ninja-wrapper-failed-flex-core-dumps)

- [AOSP 16.03 Building from source troubles - Products Support / HiKey - 96Boards Forum](https://discuss.96boards.org/t/aosp-16-03-building-from-source-troubles/742/2)

- :x: not solved: [(23 条消息) build/core/ninja.mk:148: recipe for target 'ninja*wrapper' failed*韦访的专栏-CSDN 博客](https://blog.csdn.net/rookie_wei/article/details/87428820)

- [AOSP 16.03 Building from source troubles - Products Support / HiKey - 96Boards Forum](https://discuss.96boards.org/t/aosp-16-03-building-from-source-troubles/742)

- [(23 条消息) 解决 /bin/bash: xmllint: command not found_liangtianmeng 的专栏-CSDN 博客](https://blog.csdn.net/liangtianmeng/article/details/85911485)

## FIXED: build error of `java`

### conclusion of installing java openjdk-8

```sh
sudo apt install openjdk-8-jdk
```

### detail (learned from hbw)

1. use `apt search` to list all the possible packages
2. use `apt install` to install the specific package

```sh
[2:16:14]:~/android-7.1.2_r1$ sudo apt search openjdk-8
Sorting... Done
Full Text Search... Done
libreoffice/bionic-updates,bionic-security 1:6.0.7-0ubuntu0.18.04.10 amd64
  office productivity suite (metapackage)

openjdk-8-dbg/bionic-updates,bionic-security 8u312-b07-0ubuntu1~18.04 amd64
  Java runtime based on OpenJDK (debugging symbols)

openjdk-8-demo/bionic-updates,bionic-security 8u312-b07-0ubuntu1~18.04 amd64
  Java runtime based on OpenJDK (demos and examples)

openjdk-8-doc/bionic-updates,bionic-updates,bionic-security,bionic-security 8u312-b07-0ubuntu1~18.04 all
  OpenJDK Development Kit (JDK) documentation

openjdk-8-jdk/bionic-updates,bionic-security,now 8u312-b07-0ubuntu1~18.04 amd64 [installed]
  OpenJDK Development Kit (JDK)

openjdk-8-jdk-headless/bionic-updates,bionic-security,now 8u312-b07-0ubuntu1~18.04 amd64 [installed,automatic]
  OpenJDK Development Kit (JDK) (headless)

openjdk-8-jre/bionic-updates,bionic-security,now 8u312-b07-0ubuntu1~18.04 amd64 [installed,automatic]
  OpenJDK Java runtime, using Hotspot JIT

openjdk-8-jre-dcevm/bionic 8u112-2 amd64
  Alternative VM for OpenJDK 8 with enhanced class redefinition

openjdk-8-jre-headless/bionic-updates,bionic-security,now 8u312-b07-0ubuntu1~18.04 amd64 [installed,automatic]
  OpenJDK Java runtime, using Hotspot JIT (headless)

openjdk-8-jre-zero/bionic-updates,bionic-security 8u312-b07-0ubuntu1~18.04 amd64
  Alternative JVM for OpenJDK, using Zero/Shark

openjdk-8-source/bionic-updates,bionic-updates,bionic-security,bionic-security 8u312-b07-0ubuntu1~18.04 all
  OpenJDK Development Kit (JDK) source files

uwsgi-plugin-jvm-openjdk-8/bionic-updates,bionic-security 2.0.15-10.2ubuntu2.2 amd64
  Java plugin for uWSGI (OpenJDK 8)

uwsgi-plugin-jwsgi-openjdk-8/bionic-updates,bionic-security 2.0.15-10.2ubuntu2.2 amd64
  JWSGI plugin for uWSGI (OpenJDK 8)

uwsgi-plugin-ring-openjdk-8/bionic-updates,bionic-security 2.0.15-10.2ubuntu2.2 amd64
  Closure/Ring plugin for uWSGI (OpenJDK 8)

uwsgi-plugin-servlet-openjdk-8/bionic-updates,bionic-security 2.0.15-10.2ubuntu2.2 amd64
  JWSGI plugin for uWSGI (OpenJDK 8)

[2:16:35]:~/android-7.1.2_r1$ sudo apt install openjdk8-jdk
```

## FIXED: jack-server error

1. config jack-server TLS algos
2. restart jack-server

```sh
sudo sed -i.bak "s|TLSv1, TLSv1.1, ||"  /etc/java-8-openjdk/security/java.security
./prebuilts/sdk/tools/jack-admin kill-server
./prebuilts/sdk/tools/jack-admin start-server
```

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643046227111-7c974e4e0802cc33cc1519446ee285dc9ab9d188e5af0017f765add150992429.png)

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643046485457-72cfc9d4e73b0c76abb7bebe50f8307055f8deb088906f6384384c7efb51bd7a.png)

It worked:

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643046600047-0a024694ae1cc03b8014b975e96acd11fe54fe109118c74d4e15b3251f604461.png)

ref:

- [Fixing the issue: Communication error with Jack server (35) when building AOSP | David Dong’s Blog](https://dqdongg.com/android/linux/2021/05/08/Android-jack-issue.html)

## FIXED: 去除本地化编译

```sh
export LC_ALL=C
m
```

> :warning: （未证实）不能写入`~/.bashrc`，否则会导致终端内中文显示为数字(应该是对应的编码)

ref:

- [Ubuntu 18.04 编译 AOSP 问题总结 - 简书](https://www.jianshu.com/p/c3bb9d86fd22)

## FIXED: `libclang_rt.scudo-aarch64-android.so: No such file or directory`

### solution: `make clean`

![picture 81](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643199076739-e1b41875796a01079805fb5e5be9f75c138246c0765287ee17c86d0cc7aa3869.png)

### failed try

![picture 77](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643196021087-2ecbf607dc36427b50a87c4b0167300d0efce8ccbe19b21bac843305f24120ee.png)

download all the `.so` files, and move to the target folder.

![picture 78](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643197084892-b7447c939a0bfe0a3f0b73c9f4e8dec99a033114a483fd5d52f04f0e76f37a74.png)

![picture 79](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-notes-1643197597215-9d24f33962f39ac369b7b1c53ae1afda2ba5aeaf25a7c7712697067111e392e4.png)

## FIXME: `FAILED: ** android.test.mock.docs.system_removed.txt`

problem:

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-complie-bugfix-1643541430510-80416b0ca9a980f5a1f49477f73ee65b466e1c94b55ab2df33914151188dfc1b.png)

一般这种情况，看到图中有 `//libcore/mmodules/core_platform_api:core-platform-api-stubs Metalava Check API`的，应该是需要更新 api：

resolution:

```sh
make update-api
```

result:

stuck at here, but doesn't matter:

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-complie-bugfix-1643541546114-2668f1e45da3ccc4985af198c932cb1fe7a4c97d83cb3a7c652c5da8c36ddc80.png)

And then re-make:

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/aosp-complie-bugfix-1643543101317-e0bc9024165318b8ff37e0295c9d0ce0335aebec1c8e0dfb963172f1cb289adb.png)
