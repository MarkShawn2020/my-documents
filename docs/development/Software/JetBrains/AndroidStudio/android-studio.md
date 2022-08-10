# android-studio howto

## config

### stuck at `configure gradle project`

1. in `SDK manager` download target `NDK` and `cmake`
2. config `ndk.dir` using the downloaded NDK, which is `~/Android/sdk/ndk/XXX/`, in `local.properties`
3. invalidate cache and restart

ref:

- [Android studio, configure gradle project takes forever - Stack Overflow](https://stackoverflow.com/questions/21781569/android-studio-configure-gradle-project-takes-forever)
