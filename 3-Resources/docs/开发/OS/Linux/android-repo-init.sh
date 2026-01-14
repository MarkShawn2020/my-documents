'
version: 0.0.4
features:
    1. allow you to pre-config username, email of git
    2. allow you to pre-config android version
    3. allow you to pre-config the chinese mirror of aosp
    4. considered the repo errors caused by python version 2/3
version changes:
    1. revise the combo from "aosp-arm64_eng" to "aosp_arm64-eng"
    2. add main bugfixs in build progress, including apks and jack-server problem
'

GIT_NAME="MarkShawn2020"
GIT_EMAIL="shawinjuly@gmail.com"
VERSION="android-10.0.0_r1"
AOSP_MIRROR="https://mirrors.tuna.tsinghua.edu.cn/git/AOSP/"

### --- step 1. config ---

git config --global user.name $GIT_NAME
git config --global user.email $GIT_EMAIL
git config --global url.${AOSP_MIRROR}.insteadof https://android.googlesource.com

echo "# IMPRTANT: prepare anything which could make sync become smoother
# improve the post buffer higher in case of the problem of 'error: RPC failed; curl 56 GnuTLS recv error (-9): A TLS packet with unexpected length was received.'"
git config --global http.postBuffer 1048576000
# at the same time, you may disable the ssl verification (not tested) suggested from [ubuntu - How to fix git error: RPC failed; curl 56 GnuTLS - Stack Overflow](https://stackoverflow.com/questions/38378914/how-to-fix-git-error-rpc-failed-curl-56-gnutls/46302190#46302190)
git config --global http.sslVerify false

### --- step 2. directory ---

echo "creating directory of $VERSION and enter the directory so that download all the codes in this directory"
mkdir $VERSION
cd $VERSION

### --- step 3. init ---

# install repo
sudo apt install -y repo

# repo init (just a try, then would occur the problem concerning with python2)

sudo sed -i '1s/python3/python/' /usr/bin/repo # change back for re-run
echo "y" | repo init -u https://android.googlesource.com/platform/manifest -b $VERSION

# repo init again
sudo sed -i '1s/python/python3/' /usr/bin/repo # change default python from 2 to 3 (dont run this before first repo init, otherwise causing another problem)"
echo "y" | repo init -u https://android.googlesource.com/platform/manifest -b $VERSION

### --- step 4. sync ---

# repo sync
# choice 1(for bad  net): repo sync -j12
# choice 2(for good net): repo sync -j12 && source build/envsetup.sh && lunch aosp-arm64_eng && m
repo sync -j12 && source build/envsetup.sh && lunch aosp_arm64-eng 

### --- step 5. prebuild ---

## install packages if necessary, see: [aosp packages to install](../../markk_work.md#aosp-packages-to-install)
sudo apt install -y make 
sudo apt install -y make-guile
sudo apt install -y openjdk-8-jdk m4 bison g++-multilib gcc-multilib lib32ncurses5-dev lib32z1-dev curl libxml2-utils

## solve jack-server problems
sudo sed -i.bak "s|TLSv1, TLSv1.1, ||"  /etc/java-8-openjdk/security/java.security
./prebuilts/sdk/tools/jack-admin kill-server
./prebuilts/sdk/tools/jack-admin start-server

### --- step 6. make ---
LC_ALL=C m # LC_ALL=C 去除本地化设置