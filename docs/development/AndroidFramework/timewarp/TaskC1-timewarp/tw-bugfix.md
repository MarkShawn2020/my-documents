# atw bugfix

1. [atw sdk](#atw-sdk)
   1. [:white_check_mark: sdk not found](#white_check_mark-sdk-not-found)
   2. [:white_check_mark: ndk not found](#white_check_mark-ndk-not-found)
   3. [FIXME: `error: use of undeclared identifier 'IVR_LOG_VERBOSE'`](#fixme-error-use-of-undeclared-identifier-ivr_log_verbose)

## atw sdk

### :white_check_mark: sdk not found

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/env-config-1642064391680-7f2a42e0856a7cbca2a1771efe2b683fa7dee1e8660c80c3ff8047de8c92d3c5.png" />

solution:

```sh
brew info doxygen
brew install doxygen
```

ref:

- [macos - Could not find Doxygen (missing: DOXYGEN_EXECUTABLE) in Mac OS X - Stack Overflow](https://stackoverflow.com/questions/29846214/could-not-find-doxygen-missing-doxygen-executable-in-mac-os-x)

### :white_check_mark: ndk not found

```yaml
// local.properties
## This file must *NOT* be checked into Version Control Systems,
# as it contains information specific to your local configuration.
#
# Location of the SDK. This is only used by Gradle.
# For customization when using a Version Control System, please read the
# header note.
#Thu Jan 13 16:59:10 CST 2022
sdk.dir=/Users/mark/Library/Android/sdk
ndk.dir=/Users/mark/Library/Android/sdk/ndk-bundle
#ndk.dir=D\:\\Android\\SDK\\ndk-bundle

```

### FIXME: `error: use of undeclared identifier 'IVR_LOG_VERBOSE'`

通过 grep 先定位到其他 LOG 定义的地方：

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-bugfix-1645086229023-9c3f9e84989c0d2dc923dea71905947437c65ada29e98358cf75676ed9428142.png)

观察发现缺少 VERBOSE 和 DEBUG 的定义。

补上。

cpppp #define IVR_LOG_VERBOSE(...) ((void)**android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, **VA_ARGS**)) #define IVR_LOG_DEBUG(...) ((void)**android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, **VA_ARGS**))

```

---

错误，上面的不行，会找不到 `ANDROID_LOG_VERBOSE` 和 `ANDROID_LOG_DEBUG`。

虽然根据官方 [include/android/log.h - platform/system/core - Git at Google](https://android.googlesource.com/platform/system/core/+/jb-dev/include/android/log.h) 里，这两个不过是数字而已：

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-bugfix-1645086845294-0fe867d270e1436fff630527034a4aefbcde23ebd9234d3a4b7748a01b8b9c2b.png)

不过我们又看到源代码里其实是有定义的：

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/tw-bugfix-1645086787864-5c88f9d0cd92b46abdc1964f7d5b7a9d1f7b16f41a2cafbc087ebee63ed75202.png)

那就用他们的定义好了！再写一遍被！

```
