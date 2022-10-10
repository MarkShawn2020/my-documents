
## create a ubuntu 18.04.6 in a vmware

see: [full-guide_ubuntu-in-vmware](../../../development/OS/virtual-machine/full-guide_ubuntu-in-vmware.md)

## path variables

```yaml
# premise
AF_SOURCE: ~/work@arpara/AF1020
AF_OEM: $AF_SOURCE/forluci/oem

# const
AF_ROOT: $AF_OEM/sxr2130_apps/LINUX/android
```

## get source codes

### resolution 1, via `192.168.1.2/backup/luci_origin`

```sh
rsync -avP mark@$ARPARA_AOSP_SERVER:/backup/origin_sources/luci_origin_0829.tar.gz .
```

validate:

```sh
2022/09/27 14:27:27 ➜  sources md5sum luci_origin_0829.tar.gz
77dab5573b41a499fa2c8f32690a425e  luci_origin_0829.tar.gz
```

unzip:

```txt
2022/09/27 14:29:32 ➜  sources pv luci_origin_0829.tar.gz | tar -xz
luci/external/kotlinc/LICENSE: Can't replace existing directory with non-directory                           ]  1% ETA 2:17:54
 179GiB 0:42:12 [72.7MiB/s] [==============================================================================>] 100%
tar: Error exit delayed from previous errors.

2022/09/27 15:12:00 ➜  sources du -sh luci
214G	luci
```

### (depreciated since failed to validate) resolution 2, via smb to `zhifeiji-pc`

```sh
sudo apt install smbclient

cd $AF_SOURCE

# 29.15G，解压后61G
smbget smb://x:y@zhifeiji-pc/QVR/forluci_20220813.tar.gz

# output `forluci` dir
pv forluci_20220813.tar.gz | tar -xz
sources du -sh forluci --exclude out
# out: 61G	forluci


# 10.46G
smbget smb://x:y@zhifeiji-pc/QVR/pkg.zip

sha256sum luci_origin_0829.tar.gz 
# file on Disk1
# out: ad85efb339f32c8cdd5e6aaf25a2e149859f3eb9ed069efa3070d1543c413dc5  luci_origin_0829.tar.gz

# 193.03G
# unnecessary to store (if disk shortage)
# since we can directly view the origin via ssh in bcomp
smbget smb://x:y@zhifeiji-pc/QVR/luci_origin_0829.tar.gz
```

## project structure of OEM

```txt
➜  oem tree -L 2
.
├── A11B
│   ├── BATTERY.PROVISION.A11B
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.e11
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   └── logo1.bmp
├── NORMAL
│   ├── BATTERY.PROVISION
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   ├── logo1.bmp
│   ├── pm_config_pam.c
│   ├── pm_config_target.c
│   ├── por.py
│   ├── railway_config.c
│   └── slpi
├── V02A
│   ├── BATTERY.PROVISION.V02A
│   ├── ChargerExProtocol.c
│   ├── DisplayUtils.c
│   ├── MDPPlatformLib.c
│   ├── MDPPlatformLibPanelCommon.c
│   ├── QUPAC_Access.c
│   ├── QcomChargerConfig_VbattTh.cfg
│   ├── bdwlan.e11
│   ├── bdwlan.elf
│   ├── htnv10.bin
│   ├── htnv20.bin
│   ├── logo1.bmp
│   ├── pm_config_pam.c
│   ├── pm_config_target.c
│   ├── pm_sbl_boot_oem.c
│   ├── por.py
│   ├── railway_config.c
│   └── slpi
├── about.html          // 基线信息都在这（趣立）
├── bld_adsp.sh
├── bld_aop.sh
├── bld_boot.sh
├── bld_cdsp.sh
├── bld_common.sh
├── bld_prj.sh
├── bld_slpi.sh
├── bld_tz.sh
├── common
│   ├── Core
│   ├── build
│   ├── config
│   ├── core_qupv3fw
│   └── sectools
├── contents.xml
├── cpota.sh
├── dir
│   ├── dir.zip
│   └── ufs
├── make_usf.sh
├── ota.py
├── sxr2130_adsp
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.adsp.prodQ.json
│   └── adsp_proc
├── sxr2130_aop
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_AAAAANAZO.json
│   └── aop_proc
├── sxr2130_apps
│   └── LINUX
├── sxr2130_boot
│   ├── BuildProducts.txt
│   └── boot_images
├── sxr2130_btfm
│   └── btfm_proc
├── sxr2130_btfm_hsp
│   └── btfm_proc
├── sxr2130_cdsp
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.cdsp.prodQ.json
│   └── cdsp_proc
├── sxr2130_cvp
│   ├── cvp_proc
│   └── manifest.xml
├── sxr2130_npu
│   └── npu_proc
├── sxr2130_slpi
│   ├── BuildProducts.txt
│   ├── VariantImgInfo_8250.slpi.prodQ.json
│   └── slpi_proc
├── sxr2130_spss
│   └── spss_proc
├── sxr2130_tz
│   ├── BuildProducts.txt
│   └── trustzone_images
├── sxr2130_tzapps
│   └── qtee_tas
├── sxr2130_video
│   ├── manifest.xml
│   └── venus_proc
├── sxr2130_wigig
│   ├── BuildProducts.txt
│   └── wigig_proc
├── sxr2130_wlan_hsp
│   └── wlan_proc
└── sxr2130_wlan_hst
    └── wlan_proc

47 directories, 71 files
```

## Android Project

### structure

```log
➜  android git:(master) ✗ ll
total 32K
lrwxrwxrwx 1 mark mark   19 Sep  5 16:34 Android.bp -> build/soong/root.bp
-r--r--r-- 1 mark mark   92 Aug 25 17:25 Makefile
drwxrwxr-x 1 mark mark  692 Aug 25 17:25 art
-rwxrwxr-x 1 mark mark  199 Sep  5 16:33 auto-build.sh
drwxrwxr-x 1 mark mark  360 Aug 25 17:26 bionic
drwxrwxr-x 1 mark mark   36 Aug 25 17:23 bootable
lrwxrwxrwx 1 mark mark   26 Sep  5 16:34 bootstrap.bash -> build/soong/bootstrap.bash
drwxrwxr-x 1 mark mark  160 Sep  5 16:34 build
lrwxrwxrwx 1 mark mark   48 Sep  5 16:34 build.sh -> vendor/qcom/opensource/core-utils/build/build.sh
drwxrwxr-x 1 mark mark  384 Aug 25 17:25 cts
drwxrwxr-x 1 mark mark  212 Aug 25 17:26 dalvik
drwxrwxr-x 1 mark mark   34 Aug 25 17:24 developers
drwxrwxr-x 1 mark mark  222 Aug 25 17:23 development
drwxrwxr-x 1 mark mark  104 Aug 25 17:26 device
drwxrwxr-x 1 mark mark   20 Sep  5 16:34 disregard
drwxrwxr-x 1 mark mark 5.1K Aug 25 17:25 external
drwxrwxr-x 1 mark mark  134 Aug 25 17:23 frameworks
drwxrwxr-x 1 mark mark  138 Aug 25 17:24 hardware
drwxrwxr-x 1 mark mark   86 Sep  5 16:34 kernel
drwxrwxr-x 1 mark mark  814 Aug 25 17:26 libcore
drwxrwxr-x 1 mark mark  422 Aug 25 17:26 libnativehelper
drwxrwxr-x 1 mark mark  846 Sep  6 06:34 logs
drwxrwxr-x 1 mark mark    8 Sep  3 10:24 logs.bak
drwxrwxr-x 1 mark mark 1.8K Sep  5 16:34 out
drwxrwxr-x 1 mark mark  124 Aug 25 17:26 packages
drwxrwxr-x 1 mark mark   38 Aug 25 17:26 pdk
drwxrwxr-x 1 mark mark  112 Aug 25 17:25 platform_testing
drwxrwxr-x 1 mark mark  400 Aug 25 17:25 prebuilts
-rw-rw-r-- 1 mark mark  101 Sep  2 11:33 readme.md
drwxrwxr-x 1 mark mark  500 Aug 25 17:24 sdk
drwxrwxr-x 1 mark mark  110 Aug 25 17:24 shortcut-fe
-rwxrwxr-x 1 mark mark 4.5K Aug 25 17:24 sync.sh
drwxrwxr-x 1 mark mark  566 Aug 25 17:23 system
drwxrwxr-x 1 mark mark   94 Aug 25 17:26 test
drwxrwxr-x 1 mark mark   42 Aug 25 17:26 toolchain
drwxrwxr-x 1 mark mark  288 Aug 25 17:24 tools
drwxrwxr-x 1 mark mark   50 Aug 25 17:26 vendor
```
### size

```yaml
without out: ~60G
out: 184.2G
with out: 240+G
```

```sh
$ ncdu --exclude out

--- /opt/aosp/xingjian/oem/sxr2130_apps/LINUX/android -------------------------------------------------------------------------------------------
   27.2 GiB [##########] /prebuilts
   11.9 GiB [####      ] /vendor
    8.4 GiB [###       ] /external
    2.7 GiB [          ] /frameworks
    1.7 GiB [          ] /kernel
    1.6 GiB [          ] /tools
    1.4 GiB [          ] /cts
    1.2 GiB [          ] /packages
  523.2 MiB [          ] /logs
  519.7 MiB [          ] /system
  454.8 MiB [          ] /developers
  428.9 MiB [          ] /test
  403.0 MiB [          ] /logs.bak
  306.1 MiB [          ] /device
  246.0 MiB [          ] /bootable
  152.7 MiB [          ] /development
  105.9 MiB [          ] /toolchain
   99.8 MiB [          ] /hardware
   92.0 MiB [          ] /libcore
   85.4 MiB [          ] /art
   46.4 MiB [          ] /bionic
   30.6 MiB [          ] /sdk
   28.1 MiB [          ] /dalvik
   17.1 MiB [          ] /build
    6.1 MiB [          ] /platform_testing
  860.5 KiB [          ] /pdk
  464.5 KiB [          ] /shortcut-fe
  413.5 KiB [          ] /libnativehelper
   92.5 KiB [          ] /.git
   24.5 KiB [          ]  .usecase_cache
    8.5 KiB [          ]  sync.sh
    4.5 KiB [          ]  auto-build.sh
    4.5 KiB [          ]  readme.md
    4.5 KiB [          ]  Makefile
    4.5 KiB [          ]  .gitignore
    1.0 KiB [          ] /disregard
 Total disk usage:  59.6 GiB  Apparent size:  54.8 GiB  Items: 994935
```
