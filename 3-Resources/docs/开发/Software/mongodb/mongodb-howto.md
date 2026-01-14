# mongodb-howto

## install mongodb in Ubuntu

reference:

- [Install MongoDB Community Edition on Ubuntu — MongoDB Manual](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-ubuntu/)

In KeJie's ubuntu operating system, I saw that it's ` Ubuntu 18.04 (Bionic)` when I use the command `lsb_release -dc`， and I had to use this command ` echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu bionic/mongodb-org/5.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-5.0.list` as it suggested in the official reference.

Then, when I used `sudo apt-get install -y mongodb-org` to install mongodb, it's sad to find that the downloading speed is rather slow.

<img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640009669840-6e163a6cc996b2421f1d74b06f89a8f667f9be37f7141c9b35f1326b11f32ad8.png" width="480" />

Hence, I turned for help of a Chinese mongodb mirror which leads me to the Tsinghua mirror website at [mongodb | 镜像站使用帮助 | 清华大学开源软件镜像站 | Tsinghua Open Source Mirror](https://mirrors.tuna.tsinghua.edu.cn/help/mongodb/), then it booms~

<img alt="picture 19" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640009990786-daae46cd4a5b6f629181910c68a52f5444af3be25c6d91b73a04cc8cba857f3f.png" width="480" />

## configure mongodb remote connection via 0.0.0.0

```sh
sudo chown -R mongodb:mongodb /var/lib/mongodb
sudo chown mongodb:mongodb /tmp/mongodb-27017.sock
```

reference:

- [(20 条消息) Ubuntu 中防火墙的使用和开放、关闭端口\_willingtolove 的博客-CSDN 博客\_ubuntu 防火墙开放端口](https://blog.csdn.net/willingtolove/article/details/109863064)

- [mongodb 开启远程连接和账号密码登录（包括防火墙开启） | 老潘的博客](https://www.panyanbin.com/article/c602b9e2.html)
- [Setting up and connecting to a remote MongoDB database | by Mithilesh Said | Founding Ithaka | Medium](https://medium.com/founding-ithaka/setting-up-and-connecting-to-a-remote-mongodb-database-5df754a4da89)

- [MongoDB loads but breaks, returning status=14 - Ask Ubuntu](https://askubuntu.com/questions/823288/mongodb-loads-but-breaks-returning-status-14)

## Mongodb create superuser

```py
db.createUser({user:"admin", pwd:"admin",roles:[{role:"root","db":"admin"}]})
# db.createUser({user:"admin", pwd:"admin",roles:[{role:"root","db":"admin"}],authenticationRestrictions:[{clientSource:["127.0.0.1"]}]})
```

## Mongodb Auth JS

```ts
const {MongoClient} = require('mongodb');

const user = 'admin';
const pswd = 'admin';
const auth_db_name = 'admin';
const db_name = 'hjxh_express_match';
const coll_items_name = 'items';
const mongo_uri = '101.43.125.199:27017';

const uri = `mongodb://${user}:${pswd}@${mongo_uri}`;
const client = new MongoClient(uri);

// Function to connect to the server
async function run() {
  try {
    // Connect the client to the server
    await client.connect();
    // Establish and verify connection
    await client.db(db_name).command({ping: 1});
    console.log('Connected successfully to server');
  } finally {
    // Ensures that the client will close when you finish/error
    await client.close();
  }
}
run().catch(console.dir);
```

reference:

- [Authentication Mechanisms — Node.js](https://docs.mongodb.com/drivers/node/current/fundamentals/authentication/mechanisms/)

## Mongodb Auth PY

- [Authentication Examples — PyMongo 4.0.1 documentation](https://pymongo.readthedocs.io/en/stable/examples/authentication.html)

### approach 1

```py
from pymongo import MongoClient
uri = "mongodb://{user}:{pswd}@{host}/?authSource={auth_db}"
client = MongoClient(uri)
```

### approach 2

```py
import urllib.parse
username = urllib.parse.quote_plus('user')
password = urllib.parse.quote_plus('pass/words')
MongoClient('mongodb://%s:%s@127.0.0.1' % (username, password))
```

### approach 3

```py
client = MongoClient(
    'example.com',
    username='user',
    password='password',
    authSource='the_database',
)
```
