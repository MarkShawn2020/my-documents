# mongodb-bugfix

## mongodb killed by OS

To avoid mongodb to be killed by the OS, we can set its memory use limit down to a criterion which is lower than the `free -h` capacity.

```sh
free -h
#               total        used        free      shared  buff/cache   available
# Mem:           3.7G        1.3G        665M        6.7M        1.7G        2.1G
# Swap:            0B          0B          0B
```

You see, there is only 665M for free in ZKJ's server since he is running a background jupyter and doing some sophisticated data analysis and machine learning.

then I can add this into mongodb's config file:

```yaml
# /etc/mongodb.conf
wiredTiger:
  engineConfig:
    cacheSizeGB: 0.25
```

reference:

- [storage Options](https://docs.mongodb.com/manual/reference/configuration-options/#:~:text=ldapUserCacheInvalidationInterval%3A%20%3Cint%3E-,storage%20options)

- [解决 MongoDB 占用内存过大频繁死机的方法详解*MongoDB*脚本之家](https://www.jb51.net/article/180230.htm)

- [ubuntu - MongoDB stops unknown reason - Stack Overflow](https://stackoverflow.com/questions/39994553/mongodb-stops-unknown-reason)

- [WiredTiger Storage Engine — MongoDB Manual](https://docs.mongodb.com/manual/core/wiredtiger/#wiredtiger-ram)

## brew can't restart mongod

```sh
brew services stop -dv mongodb-community
brew services start -dv mongodb-community
```

Pay Attention to the parameter of `-dv`, it's key important.

Otherwise, I can't restart it!

reference: https://github.com/Homebrew/homebrew-core/issues/22924#issuecomment-357989567
