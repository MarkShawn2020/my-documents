### ssh 总是断开

```
# file: /etc/ssh/config
# ref: https://superuser.com/a/522099/1365851
TCPKeepAlive yes 
ServerAliveInterval 60
ServerAliveCountMax 120
```

然后重启（Mac）：

```shell
# ref: https://superuser.com/a/1777243/1365851
sudo launchctl kickstart -k system/com.openssh.sshd
```

同时服务端要配置 
```
# /etc/ssh/sshd_config
ClientAliveInterval 120
ClientAliveCountMax 5
```

然后重启（ubuntu）：

```shell
sudo systemctl restart sshd
```
