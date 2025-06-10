---
epigraph: [世界曾温柔以待，,愿你邮件无阻。]
date: 2025-04-30
---

```insta-toc
---
title:
  name: 本文目录：
  level: 1
  center: false
exclude: ""
style:
  listType: dash
omit: []
levels:
  min: 1
  max: 6
---

# 本文目录：

- supabase 邮件难疑难点
    - 用户注册时的确认系统
    - Inbucket （内置的用于测试的邮箱服务）
    - 邮件发送的 Rate Limit
- 阿里云邮件推送服务
    - 1. 发信域名
    - 2. 发信地址
    - 3. 邮件标签
    - 4. 模板管理
    - 5. 收件人列表
    - 6. 发送邮件（控制台测试）
    - 7. 发送邮件（smtp）
- 邮箱测试
- 回调调试（这个坑很多）
```

## supabase 邮件难疑难点

### 用户注册时的确认系统


如果配置中没有开启确认的话，用户注册时数据会自动入表（**这意味着注册时不会发送验证邮件**），不太符合我们的常见做法，所以最好打开。


```toml
auth.email.enable_confirmations = true
```


### Inbucket （内置的用于测试的邮箱服务）

**这个在配置了真实生产环境的邮件服务时将不启用。**

测试邮箱由以下配置项控制：

```toml
[inbucket]
enabled = true
```
  
在用户点击注册的时候，需要确保以下是开启的，否则 inbucket 里是不会收到用户注册通知的（默认直接注册，入数据库）。

```toml
[auth.email]
enable_confirmations = true
```



![inbuckt 没有邮件时](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425171914.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

![inbucket 有邮件时](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425172746.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---



### 邮件发送的 Rate Limit

参考 [Rate limits | Supabase Docs](https://supabase.com/docs/guides/auth/rate-limits)，supabase 对内置的邮箱服务的频控卡的很死，以前是一小时 4 封，现在改成了一小时 2 封。

```ad-diss
值得注意的是，即使是在开发环境下，一小时 2 封邮件，那也是不够测试的！
```


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/79029806b49499a2c070d4c6b0095e12.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以我们要考虑使用自定义的 smtp 服务，因为**自定义的 smtp 服务的 rate limit 不受 supabase 的限制**。

本案我们选用了阿里云，这是阿里云的 rate limit 规则，**默认是每天 2000 封**（2 级起步），折合每小时 100 封。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5b81b4333f582070a369caf8d7c34663.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


目前，我们的参数里设置了每小时 1000 封，这样可以保证测试期比较畅通，而在用户数激增的时候通过联系服务商升级也能相对保障系统的稳定性。

```toml
[auth.rate_limit]
email_sent = 1000 # 每小时可发送的邮件数量
```

```ad-info
用户数一万对于创业公司已经是很不小的量，按 AI 产品榜最新 2025 年 3 月份的日活数据看，排名前几的也不过几百万。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2daec6975b5f5aa73067b45ddd9c173a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

```


## 阿里云邮件推送服务

尝试配置真实邮箱。

访问阿里云邮件推送控制台：https://dm.console.aliyun.com/#/directmail/Domain/cn-hangzhou

### 1. 发信域名

增加一个域名。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/%E9%98%BF%E9%87%8C%E4%BA%91%E9%82%AE%E7%AE%B1%E4%B8%8E%20DNS%20%E9%85%8D%E7%BD%AE.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


~~尽管上面都 ok 了，但是回到概览页，验证是没有反应的。~~

上面的条目里（尤其是一个 TXT 的 mail，一个 MX 的 mail）需要在 dns 配置里都配置完，最后在概览页一次性地点击验证。

```ad-tip


不行地话就多试几次。
```



![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5b8c9c674d9748502d44877dc03de761.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

验证成功后如下。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a99d8f0c385b17a879f5f3ac07d92509.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---

### 2. 发信地址

新建发新地址。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d5ec84013e86d18f26bdc03cc79b3af4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


验证回信地址。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/6f8c968a1a252ad52f929e4e7d88976e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

验证成功。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/eb64a2b5c6c57dbe5d226e925d4abc56.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


**配置 smtp 密码**，否则的话无法使用 smtp 服务，参考：[如何使用SMTP发送邮件,有发送邮件的示例吗_邮件推送(Direct Mail)-阿里云帮助中心](https://help.aliyun.com/zh/direct-mail/user-guide/send-emails-using-smtp)。


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/68abb19ffc83ed148336674fccf382ed.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


```ad-tip
title: 吐槽

阿里云 smtp 密码的限制有点奇怪，竟然至少需要 2 个大写字母，从未见过这类规则。
```

### 3. 邮件标签

我也不知道有什么用，填了再说，不然不给发送。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a75f28876ba230eca0fae01837b34869.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


### 4. 模板管理

新建邮件模板。

直接截图让 chatgpt 4o 填写即可。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e91c47db72db9e18f6baf2d9c0017a27.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

然后简单修改修改。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5f25ff139115a868d6cfce09eeb036c9.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

我最终修改的邮件内容为：

```
尊敬的{NickName}{Gender}：



您好！



感谢您注册并使用我们的服务。您的账号已成功注册并激活，现已可以正常登录与使用。

如有任何疑问，欢迎随时联系我们的客服团队。



【账号信息】


用户昵称：{NickName}

邮箱账号：{EAddr}

手机号：{Mobile}



请妥善保管您的账号信息。如您未进行注册操作，请及时联系我们处理。



祝您体验愉快！



飞脑客服

（本邮件为系统自动发送，请勿直接回复。）


```

最后别忘了提交审核一下，秒过。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/dbf1c2faec2e5540316c4da17bd295ba.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---



---

### 5. 收件人列表

上传收件人。

下载阿里官方的 csv 模板：https://aliyundm.oss.aliyuncs.com/example/example.csv?spm=5176.2020520150.106.4.1e5e7528khu0oM&file=example.csv

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/6192e943e9bba1effc86746754e8dca8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/372b9affa58410cc23cbdb24d09a47df.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

修改后上传。

不过出现了中文乱码。~~不过问题不大~~

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/1759f451169d318c84372a1c1d456da7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
需要修改正确，否则邮件发送后是乱码。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9af9ee387d1eac0847986be9d79f4434.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


经过测试发现是导出时的编码问题，要用 utf16。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e65258007e7d3fc7146259dcc57fcc3d.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


```ad-note
类似 GBK 之类的中文格式应该是没问题的，但 utf 更通用。
```

重新上传，现在 ok 了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/75c6a5ba90ff065ce347479bd0aaac49.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但是 Gender 部分错了，应该只要后缀，不要加名字。

重新修改。

重新上传。

现在终于 ok 了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/41e912faaca69bb153596951c3df4da7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


---


### 6. 发送邮件（控制台测试）

测试发送邮件，最后一步了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d4205bd78a1dfb382ca3e85410662985.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

先测试控制台发送。

全部勾上。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/9d102db89da22fb0a056039af7934ab8.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

显示发送成功。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/885f0c8c87217d972c703f66e584d6d0.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

登录邮箱看看。

完美。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/acc4f2f20704ab22ffbf93a04ef670e1.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


### 7. 发送邮件（smtp）

回到概览，找到 smtp 的文档。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ad5c1913e5e88087be792672bdab819a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


回到我们 supabase 的服务，邮箱配置环节。

```toml
# Use a production-ready SMTP server
# [auth.email.smtp]
enabled = true
host = "smtpdm.aliyun.com"
port = 465
user = "mark@mail.cs-magic.cn"
pass = "XXXX"
admin_email = "mark@mail.cs-magic.cn"
sender_name = "飞脑客服"
```


## 邮箱测试

点击注册登录，见证奇迹的时刻。
![](https://poketto.oss-cn-hangzhou.aliyuncs.com/60f63a589daa8e9e874334d4d26ac422.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

值得注意的是这个邮件地址，可以鼠标悬浮查看一下，比如我们的是： `https://supabase.cs-magic.cn/auth/v1/verify?token=pkce_**4a7&type=signup&redirect_to=https://keybox.cs-magic.cn/auth/callback`


![](https://poketto.oss-cn-hangzhou.aliyuncs.com/f911b182c57b002f1fcf92d2903b3c71.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

主要关注：
1. 主域名地址，这个其实是我们前端控制的，前端可以选择使用哪个 supabase 项目，它就会打到哪个 supabase 项目里的 auth 服务

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/dcd901181bbc209298cc4cc7becaba87.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


## 回调调试（这个坑很多）

回调配置，参考 supabase 官方文档 [Redirect URLs | Supabase Docs](https://supabase.com/docs/guides/auth/redirect-urls)，需要在程序里指定。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/d196ba69ad695bf2dc1c8a6511e7acc7.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

尤其注意由于我们的回调地址是 `https://keybox.cs-magic.cn/auth/callback`，所以为了不写死一般要用通配符（**要用两个\*号，用以表示任意长度路径**），这个路径要写在 docker 环境变量的 **`ADDITIONAL_REDIRECT_URLS`** 下，并且是个数组（**用`,`切分**）：

```toml
## General
#SITE_URL=http://localhost:3000
SITE_URL=https://cs-magic.cn
ADDITIONAL_REDIRECT_URLS="https://keybox.cs-magic.cn/**"
```

另外，程序里也要注意。

```ts {./app/auth/callback/route.ts}
import { createClient } from "@/utils/supabase/server";
import { NextResponse } from "next/server";

export async function GET(request: Request) {
  // The `/auth/callback` route is required for the server-side auth flow implemented
  // by the SSR package. It exchanges an auth code for the user's session.
  // https://supabase.com/docs/guides/auth/server-side/nextjs
  const requestUrl = new URL(request.url);
  
  // Always use the environment's SITE_URL if available, otherwise fall back to request origin
  // This ensures we redirect to the proper domain even if the request comes from localhost
  const siteUrl = process.env.NEXT_PUBLIC_SITE_URL || requestUrl.origin;

  console.log("auth/callback details: ", {
    // 因为 nginx 的配置问题，这里的 origin 始终显示为 http://localhost:xxx
    origin: requestUrl.origin,
    // 但 siteUrl 是 ok 的，所以应该用这个
    siteUrl, 
  });
  
  const code = requestUrl.searchParams.get("code");
  
  const redirectTo = requestUrl.searchParams.get("redirect_to")?.toString();

  if (code) {
    const supabase = await createClient();
    await supabase.auth.exchangeCodeForSession(code);
  }

  if (redirectTo) {
    console.log({redirectTo});
    
    return NextResponse.redirect(`${siteUrl}${redirectTo}`);
  }

  // URL to redirect to after sign up process completes
  return NextResponse.redirect(`${siteUrl}/`);
}

```

---

总之，配置邮箱是个细节活，尤其是在我们本地化部署的时候。

```ad-tip
其他你可能需要参考的是其 auth 部分的代码实现：[supabase/auth: A JWT based API for managing users and issuing JWT tokens](https://github.com/supabase/auth)，它里面的环境变量都是以 `GOTRUE_` 开头的。

此外，supabase docker 版本的环境变量要考虑两个地方，一个是 `.env` 文件，一个是 `docker-compose.yml`，它会先读 `.env`，再送进 `compose.yml`，所以有一些变量注意被覆盖的关系。

最后还有一些，可能需要去翻源代码，总之，私有化部署确实是坑比较多的，加油！祝你好运！
```

大致如上，收！
