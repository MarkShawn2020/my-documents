# Mysql howto

1. [FIXED: mysql command not found](#fixed-mysql-command-not-found)
2. [login](#login)
3. [mysql change password](#mysql-change-password)
   1. [Step 1. login](#step-1-login)
   2. [Step 2. change password](#step-2-change-password)

## FIXED: mysql command not found

The mysql bin folder position is at: `/usr/local/mysql/bin`.

```yaml
# ~/.zshrc
export PATH=$PATH:/usr/local/mysql/bin
```

ref:

- [Mac 安装 mysql 问题之-bash: mysql: command not found - 简书](https://www.jianshu.com/p/ba2216596569)

## login

```sh
/usr/local/mysql/bin/mysql -u root -p
```

!!!warning It won't work if we directly use `mysql` command before it is added to PATH.

ref:

- [macos - Mac install and open mysql using terminal - Stack Overflow](https://stackoverflow.com/questions/14235362/mac-install-and-open-mysql-using-terminal)

## mysql change password

### Step 1. login

```sql
mysql -u root -p
```

ref: [login](#login)

### Step 2. change password

```sql
ALTER USER 'user-name'@'localhost' IDENTIFIED BY 'NEW_USER_PASSWORD';
FLUSH PRIVILEGES;
```

ref:

- [How to Change MySQL User Password | Linuxize](https://linuxize.com/post/how-to-change-mysql-user-password/)
