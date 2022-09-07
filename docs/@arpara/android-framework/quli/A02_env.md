
## path variables

```yaml
# premise
AF_SOURCE: ~/work@arpara/AF1020
AF_OEM: $AF_SOURCE/forluci/oem

# const
AF_ROOT: $AF_OEM/sxr2130_apps/LINUX/android
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
