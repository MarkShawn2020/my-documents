
## set zsh as the default terminal (need re-login)

```sh
chsh -s $(which zsh)
```

https://askubuntu.com/questions/131823/how-to-make-zsh-the-default-shell

### FIXED: can't work even after re-login

change the `/bin/bash` to be `/bin/zsh` in `/usr/passwd` file:

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1645459032382-ceba5154e950cfb7b53912c52e3504f52c828b3a88b152e38382831edec01859.png)

ref:

- [linux - chsh: PAM authentication failed - Server Fault](https://serverfault.com/questions/500865/chsh-pam-authentication-failed)

## zsh check where alias/env comes from

```sh
zsh -ixc : 2>&1 | grep thingToSearchHere
```
see more: https://stackoverflow.com/a/58224674/9422455

