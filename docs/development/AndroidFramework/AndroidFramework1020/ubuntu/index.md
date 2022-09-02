## basic info 

```yaml
version: 18.04.6
```

## init configuration / utilities

### feat: enable back/front search commands

```sh
echo '"\e[A": history-search-backward     # arrow up      --> backward
"\e[B": history-search-forward      # arrow down    --> forward' >> ~/.inputrc

# reload ~/.inputrc, ref: https://superuser.com/a/1064223/1365851
bind -f ~/.inputrc
```

### change apt sources to speed up package installation

```sh
APT_SOURCES_LIST_FILE=/etc/apt/sources.list
APT_SOURCE="http://mirrors.yun-idc.com/ubuntu/"

# backup & change source file
sudo sed -i.bak -E  "s|deb \S+|deb $APT_SOURCE|g" $APT_SOURCES_LIST_FILE

# update source (要保持网络顺畅)
sudo apt update
sudo apt upgrade
``` 