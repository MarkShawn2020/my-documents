## speed up AOSP building

### 1. using `CCACHE`

see the discussion on whether to use `CCACHE`: https://groups.google.com/g/android-building/c/EI-w1WX-e90/m/wnaJ8IXfDQAJ 
![picture 1](.imgs/index-1662103609140-177fa4e1be90623764fa295e3677ca085a9ff22be10a977a87581a9285e3a4d0.png)  


### 2. adding `/tmp`

### 3. adding `swp`

### 4. increase threads as many as possible

## utilize AOSP building

### SSD不够

解决办法：

可以考虑将 `out` 软链接到外部机械盘。

注意要点：

1. 软链接时要用绝对路径

副作用：

可能最终会编译不过（进度80+时，-j88一个半小时后）。

相关记录：

`$CROOT/logs/build_09-02T12:29.log` 就是使用 out 软链接进行编译，最后报错的，当时out的对象是 `$MY-OUT-SLOW/out_0902_with_grp_failed//`（注意多了个`/`）。

接着重新链接到 `$MY-OUT-SLOW/out_0902_wo_extra_slash/`，继续编译，log文件为`$CROOT/logs/build_09-02T16:08.log`

参考：

- [Android高版本P/Q/R源码编译指南_IT先森的博客-CSDN博客_android p编译](https://blog.csdn.net/tkwxty/article/details/111684291)
