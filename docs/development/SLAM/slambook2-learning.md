## 3rdparty

### fetch submodules of 3rdparty

```sh
git submodule update --init --recursive
```

### `Pangolin`

#### build Pangolin

```sh
cd Pangolin
mkdir build
cd build
cmake ..

# may have errors
cmake --build .
```

ref:

- [stevenlovegrove/Pangolin at 1ec721d59ff6b799b9c24b8817f3b7ad2c929b83](https://github.com/stevenlovegrove/Pangolin/tree/1ec721d59ff6b799b9c24b8817f3b7ad2c929b83)

#### fixed: `fatal error: Python.h: No such file or directory`

```sh

# on Ubuntu 20.04, this helped:
sudo apt install python2.7-dev

# if conflict, purge first:
sudo apt purge "libpython2*"
```

ref:

- [fatal error: Python.h: No such file or directory · Issue #494 · stevenlovegrove/Pangolin](https://github.com/stevenlovegrove/Pangolin/issues/494)

- [apt - Ubuntu 18.04.2 install python2.7, unmet dependency - Ask Ubuntu](https://askubuntu.com/questions/1174213/ubuntu-18-04-2-install-python2-7-unmet-dependency)

### `Sopus`

#### build Sopus

#### fixed: compile error

![picture 59](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/slambook2_learning-1648521425098-067ba99e50c1fe29e7e52fae49a27f8ae51f48d5caa1484b35b76b9aeb08ef5b.png)

### opencv

#### fixed: `make`: `stdlib.h: No such file or directory`

- [gcc - Error compiling OpenCV, fatal error: stdlib.h: No such file or directory - Stack Overflow](https://stackoverflow.com/questions/40262928/error-compiling-opencv-fatal-error-stdlib-h-no-such-file-or-directory)

#### !!! fixed: `unmet`

核心是用`apititude`去自动处理升降级的问题！

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/slambook2_learning-1650972485847-c2d01f7d6194b56e04bbc57dacc8ce4680bfda835f51224fe35e4016c76f90ee.png)

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/slambook2_learning-1650972496813-47c055d381221b64ea905fd3e32ba0beca35ce719efbac20e6c39bdb4625c893.png)

ref:

- [(5 条消息) 解决 Unable to Correct Problems ‘You have Held Broken Packages’\_pyxiea 的博客-CSDN 博客](https://blog.csdn.net/xpy870663266/article/details/94742491)

#### pre-install

```sh
sudo apt-get install qt5-qmake qt5-default libqglviewer-dev-qt5 libsuitesparse-dev libcxsparse3 libcholmod3
```

## business problems

## review
