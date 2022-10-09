# compile qcom after AOSP

## checksum

local project checksum:

```txt
➜  oem du -sh * --exclude sxr2130_apps
452K	A11B
8.0K	about.html
4.0K	bld_adsp.sh
4.0K	bld_aop.sh
8.0K	bld_boot.sh
4.0K	bld_cdsp.sh
4.0K	bld_common.sh
8.0K	bld_prj.sh
4.0K	bld_slpi.sh
4.0K	bld_tz.sh
3.7G	common
60K	contents.xml
4.0K	cpota.sh
5.5G	dir
4.0K	make_usf.sh
476K	NORMAL
4.0K	ota.py
1.4G	sxr2130_adsp
706M	sxr2130_adsp.bak
84M	sxr2130_aop
2.5G	sxr2130_boot      # the boot dir is quite different, which possibly leads to my failure, so I copied one 
935M	sxr2130_boot.bak
2.7M	sxr2130_btfm
3.5M	sxr2130_btfm_hsp
1.2G	sxr2130_cdsp
4.0M	sxr2130_cvp
4.9M	sxr2130_npu
985M	sxr2130_slpi
2.5M	sxr2130_spss
439M	sxr2130_tz
160M	sxr2130_tzapps
16M	sxr2130_video
28M	sxr2130_wigig
767M	sxr2130_wlan_hsp
183M	sxr2130_wlan_hst
572K	V02A
```

remote (arpara) checksum:

```txt
➜  oem du -sh * --exclude sxr2130_apps
448K	A11B
8.0K	about.html
4.0K	bld_adsp.sh
4.0K	bld_aop.sh
8.0K	bld_boot.sh
4.0K	bld_cdsp.sh
4.0K	bld_common.sh
8.0K	bld_prj.sh
4.0K	bld_slpi.sh
4.0K	bld_tz.sh
4.2G	common
60K	contents.xml
4.0K	cpota.sh
5.5G	dir
4.0K	make_usf.sh
468K	NORMAL
4.0K	ota.py
4.0K	rm_persist_tag.sh
1.4G	sxr2130_adsp
82M	sxr2130_aop
2.5G	sxr2130_boot
2.4M	sxr2130_btfm
3.4M	sxr2130_btfm_hsp
1.2G	sxr2130_cdsp
4.0M	sxr2130_cvp
4.8M	sxr2130_npu
974M	sxr2130_slpi
2.5M	sxr2130_spss
431M	sxr2130_tz
158M	sxr2130_tzapps
16M	sxr2130_video
28M	sxr2130_wigig
767M	sxr2130_wlan_hsp
183M	sxr2130_wlan_hst
564K	V02A
```
