
## overview

```sh
# show devices
adb start-server
adb devices

# stop device
adb kill-server

# restart system (warm reboot)
adb shell setprop ctl.restart.zygote

# start launcher (android 11, `.Launcher3` in android 10)
adb shell am start -n com.android.launcher3/.uioverrides.QuickstepLauncher

# start gallery
adb shell am start -n com.android.gallery3d/.app.GalleryActivity
```

- :sparkles::sparkles: 命令速查：[ADB Shell Commands | Android Developers](https://android-doc.github.io/tools/help/shell.html)

- [Android 调试桥 (adb)  |  Android 开发者  |  Android Developers](https://developer.android.com/studio/command-line/adb)

- [[HOWTO] New Hot Reboot Command!!!! | XDA Forums](https://forum.xda-developers.com/t/howto-new-hot-reboot-command.2325378/)

## fast push

```sh
# init
adb root
adb disable-verity
adb remount
```

```sh
CROOT=/home/mark/work@arpara/rock-android11
PRODUCT=rk3399_ROCKPI4B_Android11
MODULE=surfaceflinger
USE_SYMBOL=1

OUT_DIR=$CROOT/out/target/product/$PRODUCT$($USE_SYMBOL?"/symbols":"")/system

adb push $OUT_DIR/bin/$MODULE /system/bin/
adb push $OUT_DIR/lib/lib$MODULE.so /system/lib/
adb push $OUT_DIR/lib64/lib$MODULE.so /system/lib64/
```

## sys relative

### get android/sdk(API) version

```sh
# get android version
adb shell getprop ro.build.version.release

# get sdk version
adb shell getprop ro.build.version.sdk
```

ref:

- [shell - Get Android OS version of device connected via ADB - Stack Overflow](https://stackoverflow.com/questions/29968096/get-android-os-version-of-device-connected-via-adb)

### `dumpsys`

```sh
# list all the available services
adb shell dumpsys -l

# view the display service
adb shell dumpsys display
```

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/adb-howto-1644419106778-94d78504f27d81c9f142950f9c1559089970f905da3449feff0313a080f47d73.png)

> ref

- [dumpsys  |  Android 开发者  |  Android Developers](https://developer.android.com/studio/command-line/dumpsys)

### `getprop | setprop`

!!!warning the `getprop | setprop` is for global build props, not framework level!

    For example, I defined a sysprop under surfaceflinger, but I can not get it if I only push `surfaceflinger | libsurfaceflinger.so` into device.

```sh
# see whole list of props
adb shell getprop

# see the value of specific prop
adb shell getprop ro.build.version.sdk

# ambiguous search of specific prop
adb shell getprop | grep timezone
```

see: - [shell - Android ADB commands to get the device properties - Stack Overflow](https://stackoverflow.com/questions/21099301/android-adb-commands-to-get-the-device-properties?rq=1)

### TODO: `sysprop(api)`

- [添加系统属性  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/devices/architecture/configuration/add-system-properties#step3-add-levels-to-system)

- [将系统属性作为 API 实现  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/devices/architecture/sysprops-apis)

## log relative

### config log level

先这样屏蔽下，logcat 的负载会降下来 logcat 屏蔽冗余日志输出

```sh
SERVICE=log.tag.JniUsbDevice

# 屏蔽JniUsbDevice TAG显示
adb shell setprop $SERVICE ERROR

# 恢复某TAG显示
adb shell setprop $SERVICE VERBOSE
```

> ref

- [(1 条消息) 查看和设置 Android Log 等级和 Log.isLoggable 使用方法\_Sunxiaolin2016 的博客-CSDN 博客](https://blog.csdn.net/Sunxiaolin2016/article/details/103721945)

- [android - adb shell setprop log.tag.SOMETAG VERBOSE, how to get SOMETAG? - Stack Overflow](https://stackoverflow.com/questions/56444913/adb-shell-setprop-log-tag-sometag-verbose-how-to-get-sometag)

### bugfix: log datetime

android 的日志系统的时间，是基于系统时间，对于刚刷的模拟机来说，系统里是默认自动获取（从网络），但由于刚刷的模拟机也没设置无线网，所以导致时间可能就比较随意了（目测可能就是 build 起的时间）。

在连接无线网后，会自动更新时间；再配置时区为中国上海，这个时候 adb 的日志时间就正常了。

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/adb-howto-1644460841673-c1a83e998362f85db969e32abc7359af0de9e9238ab5e6a22dd1188a6b26f55f.png)

## package relative

```sh
function getPackageInfoFromApkFile() {aapt dump badging $1}

# use `perl` for non-greedy match
function getPackageNameFromApkFile() {aapt dump badging $1 | grep package | perl -pe "s/^.*name='(.*?)'.*$/\1/"}
```

## activity relative

### get activity name from specific package

```sh
function getActivitiesFromPackageName() {adb shell "dumpsys package | grep -i $1 | grep 'Activity' | sort | uniq"}
```

see:

- [android - Is there a adb shell command to know all activitynames of a package - Stack Overflow](https://stackoverflow.com/questions/28984772/is-there-a-adb-shell-command-to-know-all-activitynames-of-a-package)

### trigger an intent for choosing activity

```sh
adb shell am start -a android.intent.action.VIEW -d
```

ref:

- [android - Start youtube video with adb? - Stack Overflow](https://stackoverflow.com/questions/20534353/start-youtube-video-with-adb)

### play a video/movie/mp4

resolution 1:

```sh
adb push FILE /data/local/
FILE=/data/local/$FILE

# directly play the video using specific player
adb shell am start -n com.android.gallery3d/.app.MovieActivity -d $FILE
```

- [android - Launching movie playback via "am start" - Stack Overflow](https://stackoverflow.com/questions/8207548/launching-movie-playback-via-am-start)

resolution 2:

```sh
# use intent to select which player
adb shell am start -a android.intent.action.VIEW  -t video/mp4 -d $FILE
```

- [ADB commands for Music,Video and FM | by Roshni Tiwari | Medium](https://medium.com/@roshni.b.tiwari/adb-commands-for-music-video-and-fm-b02018219cd5)

### start/stop activity(package)

```sh
# start app(activity)
db shell am start -n PACKAGE/ACTIVITY

# kill app(package)
adb shell am force-stop PACKAGE
```

see: - [(1 条消息) adb kill app 进程及启动 app 方法\_蓝不蓝编程-CSDN 博客\_adb kill 应用](https://blog.csdn.net/yinxing2008/article/details/91434805)

### TODO: kill app/process/package

```sh
# kill background process
adb shell am kill XXX

# kill all background processes
adb shell am kill-all
```

- [Android ADB stop application command like "force-stop" for non rooted device - Stack Overflow](https://stackoverflow.com/questions/17829606/android-adb-stop-application-command-like-force-stop-for-non-rooted-device)

### list all package names

```sh
adb shell pm list packages | cut -c 8-
```

sample:

![picture 30](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/adb-howto-1644484544765-fd3435d784176f80025e6c44dfc1b204d31a3d10d08be0435af01b4ca462d2d5.png)

see: - [android - Get Application Name/ Label via ADB Shell or Terminal - Stack Overflow](https://stackoverflow.com/questions/16650765/get-application-name-label-via-adb-shell-or-terminal)

---

It may also be helpful if we use `adb shell dumpsys package`, while there are too much noise.

### find current activity names

```sh
adb shell dumpsys window windows | grep "Window #"
```

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/adb-howto-1644484220733-940dabfae4d51af0cb09b478c516881fa510640fb9d417de948ad3bc256aea3d.png)

see: - [android - Get Application Name/ Label via ADB Shell or Terminal - Stack Overflow](https://stackoverflow.com/questions/16650765/get-application-name-label-via-adb-shell-or-terminal)

## screen relative

### change window size

```sh
adb shell wm size 1920x1080

adb shell wm density 390

adb reboot
```

ref:

- [Change Screen Resolution via ADB and save Battery life on Android devices (without Root)](https://nerdschalk.com/change-screen-resolution-adb-android/)

### screenshot/screencap

```sh
# gen screenshot
adb shell screencap /sdcard/screen.png

# pull screenshot
adb pull /sdcard/screen.png
```

> ref

- [Android 调试桥 (adb)  |  Android 开发者  |  Android Developers](https://developer.android.com/studio/command-line/adb#screencap)

### layer 相关

ref:

- :sparkles: 这里提供了几个和 layer 操作有关的`adb`命令：[GLES 图层  |  Android NDK  |  Android Developers](https://developer.android.com/ndk/guides/rootless-debug-gles)

## permission

### 官方文档：权限控制

- [PermissionController  |  Android 开源项目  |  Android Open Source Project](https://source.android.com/devices/architecture/modular-system/permissioncontroller)

### adb 启用读写 SD 卡权限

```sh
adb shell pm grant PACKAGE android.permission.WRITE_EXTERNAL_STORAGE

adb shell pm grant PACKAGE android.permission.READ_EXTERNAL_STORAGE
```

ref:

- [Set write and read external storage permission prior to a test run so that a screenshot on fail listener can work on device targets running Android 6.0+](https://gist.github.com/RussellCollins/87e447183103fe6ca8b1)

## tool

### TODO: `autoadb`

- [rom1v/autoadb: Execute a command whenever a device is adb-connected](https://github.com/rom1v/autoadb)

### edit file in adb shell

```sh
adb shell
busybox vi /sdcard/Download/test.txt
```

ref:

- [editor - Can I edit files inside the Android ADB shell? - Stack Overflow](https://stackoverflow.com/questions/20258688/can-i-edit-files-inside-the-android-adb-shell)

## input

### input show `trackball`

```sh
adb shell input trackball tap X Y
```

ref:

- [android - How to use ADB to send touch events to device using sendevent command? - Stack Overflow](https://stackoverflow.com/questions/3437686/how-to-use-adb-to-send-touch-events-to-device-using-sendevent-command)

## debug

```sh

# find all activities of specific package

# find launchable activities of specific package
adb shell pm dump PACKAGE_NAME | grep -A 1 MAIN

# find activities in current windows
adb shell dumpsys window windows | grep "Window #"


# kill app, sample: `adbkill com.android.systemui`
alias adbkill='_adbkill(){ adb root;adb shell kill `adb shell ps | grep $1 | awk {'\''print $2'\''} | head -n 1`; }; _adbkill'

```

ref:

- [How to find out activity names in a package? android. ADB shell - Stack Overflow](https://stackoverflow.com/questions/33441138/how-to-find-out-activity-names-in-a-package-android-adb-shell)

- [android - get launchable activity name of package from adb - Stack Overflow](https://stackoverflow.com/questions/12698814/get-launchable-activity-name-of-package-from-adb/36255727)

- [android adb one line command kills the process according to the package name - Krybot](https://blog.krybot.com/a?ID=01750-cb7cddef-842d-48e9-aa32-e9a9747a2720)
