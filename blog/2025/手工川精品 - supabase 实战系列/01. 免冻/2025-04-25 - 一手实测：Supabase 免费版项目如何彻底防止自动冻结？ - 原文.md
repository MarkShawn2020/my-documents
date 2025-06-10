
近期给一位需要给美国客户展示公司主页的客户采用了 supabase + vercel 的方案，vercel 很舒服，毕竟是对公的，supabase 在后端，给他授权账号麻烦，他查看数据库也麻烦，更糟糕的是，supabase 免费版的项目如果七天之内没有服务请求，将会自动冻结。

![supabase 数据库被冻结](https://poketto.oss-cn-hangzhou.aliyuncs.com/d1e6b15b484043775b0398a603601760.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

这是个已知问题，之前我自己的项目也碰到过。

我的技术群友们当时给了一些方案，比如**私有化部署自己的 supabase，或者写一个 cron 后台进程**。

![技术群内关于私有化部署相关的交流](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425105145.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


当时那个项目不是很急，就没上心。

这次要给客户服务好，就下决心处理一下。

---

先问了 ChatGPT，看看有没有什么“大众捷径”。

![ChatGPT 关于 supabase 冻结的解决方案](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425105318.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


ChatGPT 推荐使用 免费的 UptimeRobot 定期访问 supabase，以阻止 supabase 休眠。

这似乎是可行的，我很快注册并且创建了一个 monitor 服务，监控我的 supabase 项目，地址为：https://gxqhklwoivlpizypbtgp.supabase.co （supabase api root）

![supabase 的主界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425100516.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但直接填 supabase api root 会 404。

![supabase api 请求结果](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425103301.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

不过 ChatGPT 说是 OK 的。

![ChatGPT 关于 supabase 404 的解释](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425103354.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

而 UptimeRobot 免费版不支持修改我们默认有效的状态码。

![UptimeRobot 的状态码设置](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425102852.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


所以这种办法不优雅。

因为在 monitor 面板里服务永远是 down 的。

但 supabase 那里是 ok 的。

这就很 subtle。

有些人应该会喜欢。

但不是我。

---

ChatGPT 还说可以设置公开的匿名访问表。

![ChatGPT 关于 supabase 匿名访问的表设置](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425103005.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但我测试之后依旧是不行的，需要加上 apikey 才行。


![supabase 的表策略设置](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425101215.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


![supabase 的三种认证策略](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425101754.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


```shell
➜  ~ curl https://gxqhklwoivlpizypbtgp.supabase.co/rest/v1/UptimeRobot\?select\=\*
{"message":"No API key found in request","hint":"No `apikey` request header or url param was found."}%
```

而在 UptimeRobot 里，修改 header 也是付费功能。

![UptimeRobot 关于 header 的设置](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425103859.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

完败！

---


所以最简单的方案是啥？

带 apikey 的一个命令行直接搞定：

```shell
➜  ~ curl https://gxqhklwoivlpizypbtgp.supabase.co/rest/v1/uptimerobot\?select\=\*-H "apikey: eyJhbGciOiJI***EJNeHXsrecqi98UpU"
[]%
```

返回是 `[]` 说明是个列表，说明就 ok 了。

ChatGPT 给的是一个 nodejs 的方案，也可以：

```js
// 用 node-schedule 之类包每天定时运行
import { createClient } from '@supabase/supabase-js'

const supabase = createClient(
  'https://xxx.supabase.co',
  'public-anon-key'
);

async function keepAwake() {
  const { data, error } = await supabase
    .from('your_table')
    .select('id')
    .limit(1);
  console.log('Supabase keep awake', data, error);
}

keepAwake();
```

就是还要搞一个 cron，还要维护，不方便管理，比较麻烦。

不过也许有比较好的方案，比如可视化管理 cron 的。

--- 

ChatGPT 说确实有，还很多，比如 Webmin、Cronicle、Crontab UI、GoCrontab、Terminator等。

![ChatGPT 关于 cron 的可视化工具推荐](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425112133.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


我喜欢极简，所以优先尝试 Crontab UI。

---

我希望 nginx 反向到我们的服务器 cron.cs-magic.cn ，以及 http端口希望是 50425，以防冲突，crontab-ui 希望是 docker 启动。

它给了建议：

```bash
docker run -d \
  --name crontab-ui \
  -p 50425:8000 \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v /etc/crontabs:/crontab-ui/crontabs \
  --restart unless-stopped \
  alseambusher/crontab-ui
```

但我们的 docker 在拉取 `https://registry-1.docker.io/v2/` 里的镜像时有问题，最后通过配置腾讯的镜像搞定：

```json { /etc/docker/daemon.json}
{
  "registry-mirrors": ["https://mirror.ccs.tencentyun.com"]
}
```

>它一开始推荐的镜像站是 https://hub-mirror.c.163.com/v2/ ，但实测不行。

好地，再配置一下 nginx，进行反向代理。

由于我自己的 nginx 已经做了高度的模块化，所以新增服务只需要加一行即可：

```
~^cron\.(.*)$ 50425;
```

接着就可以打开 cron.cs-magic.cn 就可以访问 cron 管理面板了。

在 crontab-ui 里可以非常方便地创建任务，它是把命令与控制解耦的。

![crontab-ui 的任务新建](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425114112.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

甚至还支持配置自己的邮箱服务。

![crontab-ui 支持邮件配置](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425114203.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


以及 hooks，不过还没做完。

![crontab-ui 计划支持 hooks](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425114222.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

这样我们就搞定了每天凌晨 3 点半自动请求 supabase 以防冻结了。

![crontab-ui 的任务列表界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425114344.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---

但 crontab-ui 默认是不需要密码访问的，这不安全。

因此我们还需要加个简单的管理员登录系统。

根据 ChatGPT 提示，我们可以直接采用以下脚本配置用户名与密码：

```shell
sudo apt update && sudo apt install -y apache2-utils
sudo htpasswd -c /etc/nginx/.htpasswd 你的用户名
```

然后修改我们的 nginx 配置。

因为我的 nginx 配置是基于 map 的，ChatGPT 还给了我一种条件判断写法（感觉非常美丽）：

```nginx
 if ($host = "cron.cs-magic.cn") {

        auth_basic "Cron Admin Only";

        auth_basic_user_file /etc/nginx/.htpasswd;

    }
```

但是实测会报错：`"auth_basic" directive is not allowed here in /etc/nginx/sites-enabled/default:82 （是不是版本问题哦~）

所以还是老老实实单独写了个 server 块，有 nginx 大佬看看可否给我优化思路。

```nginx
server {
    listen 443 ssl;
    server_name cron.example.com;

    # SSL 配置（路径换成你自己证书的实际路径）
    ssl_certificate     /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    ssl_session_timeout 1d;
    ssl_session_cache   shared:SSL:50m;
    ssl_protocols       TLSv1.2 TLSv1.3;
    ssl_ciphers         HIGH:!aNULL:!MD5;
    ssl_prefer_server_ciphers off;

    # 访问日志（可按需设置）
    access_log /var/log/nginx/cron-ui.log detailed_debug;

    location / {
        # Basic Auth 配置（密码文件路径仅示例，需用命令生成自己的账号密码）
        auth_basic "Cron Admin Only";
        auth_basic_user_file /etc/nginx/.htpasswd;

        # 反向代理配置，端口换成你 crontab-ui 的实际监听端口
        proxy_pass http://127.0.0.1:50425;
        proxy_ssl_verify off;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection $connection_upgrade;
        proxy_buffering off;
        proxy_cache off;
        proxy_set_header Connection '';
        chunked_transfer_encoding off;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        proxy_read_timeout 300s;
        proxy_connect_timeout 75s;
    }
}

```

最后重新启动 nginx：

```shell
# 提示输入密码，完成后重载 nginx
sudo nginx -t && sudo nginx -s reload
```

刷新我们网站 cron.cs-magic.cn 看看效果：

![nginx auth 的登录界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425115935.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

ok，果然有登录系统了！

值得注意的是：

- **crontab-ui** 没有内置用户认证，所以页面上只有“设置/重载/日志”等按钮，没有登录/登出流程。
    
- 如果我们加了 nginx basic auth，**登出操作是浏览器级的**，不是应用级的。

而：
- HTTP Basic Auth 的登录状态**不是**由 cookies、localStorage、sessionStorage 控制的。
    
- 它的认证信息（用户名+密码）被浏览器**保存在内存**，只要浏览器窗口/标签页没关，**每次请求会自动带上 Authorization header**。
    
- 只有**关闭所有该站点的标签页**，或**重启浏览器**，才会真正清除（部分浏览器在无痕模式下更明显）。

因此我们一般需要退出浏览器，再重新打开，才会触发重新登录我们的系统，这个是和基于 session 的正常网站不太一样的用户机制。

---

但 crontab-ui 似乎有 bug，点了 Run now 之后还是没反应。

![crontab-ui 点击 run 但是没有反应的 bug](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425122213.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


而且始终都没能在服务器本地验证 ok。

再看一下代码，已经是三年前的了：[alseambusher/crontab-ui: Easy and safe way to manage your crontab file](https://github.com/alseambusher/crontab-ui)


果断弃坑。

![crontab-ui 上次更新已经是三年前](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425122807.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---

下一位选手是：[jhuckaby/Cronicle: A simple, distributed task scheduler and runner with a web based UI.](https://github.com/jhuckaby/Cronicle)。

![cronicle 的界面展示](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425122933.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

代码竟然是 12 小时前更新的！

![cronicle 上次更新是在 12 小时前](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425123009.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

 但是它自身不支持 docker，我拉了半天，以为是镜像和梯子问题：

```shell
➜ ~ sudo docker pull jhuckaby/cronicle Using default tag: latest Error response from daemon: Get "[https://registry-1.docker.io/v2/](https://registry-1.docker.io/v2/)": net/http: request canceled while waiting for connection (Client.Timeout exceeded while awaiting headers)
```

最后检查仓库确实没有，然后 Claude 基于 jina mcp 告诉我有 docker 的仓库是叫：[bluet/docker-cronicle-docker: Scheduling dockerized Cronicle cron jobs run in docker container.](https://github.com/bluet/docker-cronicle-docker)。

```shell
sudo docker run -v /var/run/docker.sock:/var/run/docker.sock -v /tmp:/tmp \
--hostname localhost -p 50425:3012 --name cronicle bluet/cronicle-docker:latest
```

>其中 -v /tmp:/tmp 是把服务器与容器的目录打通；50425 是我们希望对外暴露的服务器端口，3012 是程序本身的端口。



部署后打开是这样：

![cronicle 的启动界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425143452.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

稍等片刻：

![cronicle 启动后的登录界面](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425143517.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
我在官网没找到用户名密码在哪里配置，不过 Claude 告诉我都是 admin，登录之后可以修改密码：

![cronicle 的用户配置页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425143919.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

甚至还可以修改头像（基于 WordPress）🤔……

在 Croncile 里创建 schedule 的交互要比 crontab-ui 复杂，但没有按分钟的，只可以自定义一个个勾选。

我们创建一个测试任务，往服务器某个文件每分钟输出当前时间：

```shell
#!/bin/sh

# Enter your shell script code here
echo "$(date)" >> /tmp/cronicle-health.log 2>&1
```

![cronicle 的任务配置页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425145848.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



创建成功了。

交互也是 ok 的，不像 crontab-ui 点了没反应……

![cronicle 的任务列表页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425144355.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


它说已经运行两次任务了。

![cronicle 的任务历史页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425144512.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
结果里看不出啥。

![cronicle 的任务分析页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425145816.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但本地确实已经有结果了。

```shell
➜  ~ cat /tmp/cronicle-health.log
Fri Apr 25 06:55:19 UTC 2025
Fri Apr 25 06:56:00 UTC 2025
Fri Apr 25 06:57:00 UTC 2025
Fri Apr 25 06:58:00 UTC 2025
Fri Apr 25 06:59:00 UTC 2025
```

那我们就放心了。


---

现在我们正式创建一个对 supabase 的定时请求服务。

>先设置每分钟一次，ok 后再改成每天。

![cronicle 的任务配置详情](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425150300.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

运行查看结果，确实有效，返回码是 200。
![cronicle 的任务运行详情](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425150351.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

打开 supabase 的 log 菜单，可以看到每分钟的第一秒确实收到了一个 head 请求，说明一切都通了。

![supabase API 请求的数据分析页](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425150552.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

这样，我们改回按天，一切服务均已就绪，任务圆满完成。

现在我们把 supabase 的定时任务改回每天凌晨 3 点执行。

以及 test（心跳） 的任务也由原先的按分钟改成按小时，否则 log 文件越来越大，不利于后续的维护。

但即便如此，体积也是会越来越大。对于这个潜在问题，你觉得该用什么办法干净地解决呢？欢迎交流👏🏻

>我曾经在一个团队亲眼见到一个 log 文件 10 个 G，对年少的我造成了不小的心理阴影。



