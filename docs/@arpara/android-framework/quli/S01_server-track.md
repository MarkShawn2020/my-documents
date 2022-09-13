# Sensitive Activities Track In Our AOSP Server(`192.168.1.242`)

## chore: cmake 3.10 --> 3.20

### motivation

the vim plugin of `YouCompleteMe` needs cmake to be >= 3.14.0

Considering that a higher version of cmake is POSSIBLE no side effects to current projects working on, I decided to just upgrade the cmake.

### resolution

installing:

```sh
## -- source: https://www.codegrepper.com/code-examples/shell/cmake+3.14+or+higher+is+required.+you+are+running+version+3.13.4 --

sudo apt remove cmake #Uninstall old version

sudo apt-get install build-essential libssl-dev
wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz

tar -zxvf cmake-3.20.0.tar.gz
cd cmake-3.20.0
./bootstrap
make
sudo make install

cmake --version 
```

installed result:

```txt
-- Installing: /usr/local/share/bash-completion/completions/cmake
-- Installing: /usr/local/share/bash-completion/completions/cpack
-- Installing: /usr/local/share/bash-completion/completions/ctest
cmake version 3.20.0

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## feat: speed up connection to github.com

### resolution 1, via project of github520

see: 

- recommended by 缪永俊：521xueweihan/GitHub520: 让你“爱”上 GitHub，解决访问时图裂、加载慢的问题。（无需安装）](https://github.com/521xueweihan/GitHub520)

### resolution 2, via manually config

1. visit [多个地点ping[github.com]服务器-网站测速-站长工具](https://ping.chinaz.com/github.com) and check the best server, e.g the russia one of `140.82.121.3`
2. wrote into hosts file: `echo '140.82.121.3 github.com # russia' | sudo tee -a /etc/hosts`

:::tip
This resolution is the most lightning one, and also works for `raw.githubcontent.com`, etc. 
:::


<!-- ARPARA-END -->

## bugfix: system perl config

### motivation

When we use `sudo apt install XXX`, we would catch the following warnings:

```txt
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
        LANGUAGE = "en_HK:en",
        LC_ALL = (unset),
        LC_CTYPE = "UTF-8",
        LC_TERMINAL_VERSION = "3.4.16",
        LC_TERMINAL = "iTerm2",
        LANG = "en_HK.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to a fallback locale ("en_HK.UTF-8").
locale: Cannot set LC_CTYPE to default locale: No such file or directory
locale: Cannot set LC_ALL to default locale: No such file or directory
```

### TODO: resolution
