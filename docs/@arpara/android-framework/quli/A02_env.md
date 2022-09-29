
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
