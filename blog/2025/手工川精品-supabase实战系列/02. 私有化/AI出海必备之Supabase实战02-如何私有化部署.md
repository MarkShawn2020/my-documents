
![supabase 架构](https://poketto.oss-cn-hangzhou.aliyuncs.com/9ca1f39b9e1e88745355ae943fe7d2f6.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

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
  max: 2
---

# 本文目录：

- 一言不合先上配置文件
- 两种办法
- 几大模块
- 几个最佳实践
```


## 一言不合先上配置文件

```ad-important
参考 https://supabase.com/docs/guides/local-development/cli/config

之前忽视了这个配置文档，在配置邮件发送频率时吃了大跟头，最后还是基于 claude 的对话得到启示从而去仔细寻找配置的。（它的回答没有给出最终标准答案，但很接近，比我 google 得到的答案要好）
```


```toml
# For detailed configuration reference documentation, visit:
# https://supabase.com/docs/guides/local-development/cli/config
# A string used to distinguish different Supabase projects on the same host. Defaults to the
# working directory name when running `supabase init`.
project_id = "2025-02-04_KeyBox"

[api]
enabled = true
# Port to use for the API URL.
port = 50425
# Schemas to expose in your API. Tables, views and stored procedures in this schema will get API
# endpoints. `public` and `graphql_public` schemas are included by default.
schemas = ["public", "graphql_public"]
# Extra schemas to add to the search_path of every request.
extra_search_path = ["public", "extensions"]
# The maximum number of rows returns from a view, table, or stored procedure. Limits payload size
# for accidental or malicious requests.
max_rows = 1000

[api.tls]
# Enable HTTPS endpoints locally using a self-signed certificate.
enabled = false

[db]
# Port to use for the local database URL.
port = 54322
# Port used by db diff command to initialize the shadow database.
shadow_port = 54320
# The database major version to use. This has to be the same as your remote database's. Run `SHOW
# server_version;` on the remote database to check.
major_version = 15

[db.pooler]
enabled = false
# Port to use for the local connection pooler.
port = 54329
# Specifies when a server connection can be reused by other clients.
# Configure one of the supported pooler modes: `transaction`, `session`.
pool_mode = "transaction"
# How many server connections to allow per user/database pair.
default_pool_size = 20
# Maximum number of client connections allowed.
max_client_conn = 100

[db.seed]
# If enabled, seeds the database after migrations during a db reset.
enabled = true
# Specifies an ordered list of seed files to load during db reset.
# Supports glob patterns relative to supabase directory: "./seeds/*.sql"
sql_paths = ["./seed.sql"]

[realtime]
enabled = true
# Bind realtime via either IPv4 or IPv6. (default: IPv4)
# ip_version = "IPv6"
# The maximum length in bytes of HTTP request headers. (default: 4096)
# max_header_length = 4096

[studio]
enabled = true
# Port to use for Supabase Studio.
port = 54323
# External URL of the API server that frontend connects to.
api_url = "http://127.0.0.1"
# OpenAI API Key to use for Supabase AI in the Supabase Studio.
openai_api_key = "env(OPENAI_API_KEY)"

# Email testing server. Emails sent with the local dev setup are not actually sent - rather, they
# are monitored, and you can view the emails that would have been sent from the web interface.
[inbucket]
enabled = true
# Port to use for the email testing server web interface.
port = 54324
# Uncomment to expose additional ports for testing user applications that send emails.
# smtp_port = 54325
# pop3_port = 54326
# admin_email = "admin@email.com"
# sender_name = "Admin"

[storage]
enabled = true
# The maximum file size allowed (e.g. "5MB", "500KB").
file_size_limit = "50MiB"

# Image transformation API is available to Supabase Pro plan.
# [storage.image_transformation]
# enabled = true

# Uncomment to configure local storage buckets
# [storage.buckets.images]
# public = false
# file_size_limit = "50MiB"
# allowed_mime_types = ["image/png", "image/jpeg"]
# objects_path = "./images"

[auth]
enabled = true
# The base URL of your website. Used as an allow-list for redirects and for constructing URLs used
# in emails.
site_url = "http://127.0.0.1:3000"
# A list of *exact* URLs that auth providers are permitted to redirect to post authentication.
additional_redirect_urls = ["https://127.0.0.1:3000"]
# How long tokens are valid for, in seconds. Defaults to 3600 (1 hour), maximum 604,800 (1 week).
jwt_expiry = 3600
# If disabled, the refresh token will never expire.
enable_refresh_token_rotation = true
# Allows refresh tokens to be reused after expiry, up to the specified interval in seconds.
# Requires enable_refresh_token_rotation = true.
refresh_token_reuse_interval = 10
# Allow/disallow new user signups to your project.
enable_signup = true
# Allow/disallow anonymous sign-ins to your project.
enable_anonymous_sign_ins = false
# Allow/disallow testing manual linking of accounts
enable_manual_linking = false
# Passwords shorter than this value will be rejected as weak. Minimum 6, recommended 8 or more.
minimum_password_length = 6
# Passwords that do not meet the following requirements will be rejected as weak. Supported values
# are: `letters_digits`, `lower_upper_letters_digits`, `lower_upper_letters_digits_symbols`
password_requirements = ""

[auth.rate_limit]
email_sent = 1000 # 每小时可发送的邮件数量

[auth.email]
# Allow/disallow new user signups via email to your project.
enable_signup = true
# If enabled, a user will be required to confirm any email change on both the old, and new email
# addresses. If disabled, only the new email is required to confirm.
double_confirm_changes = true
# If enabled, users need to confirm their email address before signing in.
enable_confirmations = true
# If enabled, users will need to reauthenticate or have logged in recently to change their password.
secure_password_change = false
# Controls the minimum amount of time that must pass before sending another signup confirmation or password reset email.
max_frequency = "1s"
# Number of characters used in the email OTP.
otp_length = 6
# Number of seconds before the email OTP expires (defaults to 1 hour).
otp_expiry = 3600

# Use a production-ready SMTP server
# [auth.email.smtp]
# enabled = true
# host = "smtp.sendgrid.net"
# port = 587
# user = "apikey"
# pass = "env(SENDGRID_API_KEY)"
# admin_email = "admin@email.com"
# sender_name = "Admin"

# Uncomment to customize email template
# [auth.email.template.invite]
# subject = "You have been invited"
# content_path = "./supabase/templates/invite.html"

[auth.sms]
# Allow/disallow new user signups via SMS to your project.
enable_signup = false
# If enabled, users need to confirm their phone number before signing in.
enable_confirmations = false
# Template for sending OTP to users
template = "Your code is {{ .Code }}"
# Controls the minimum amount of time that must pass before sending another sms otp.
max_frequency = "5s"

# Use pre-defined map of phone number to OTP for testing.
# [auth.sms.test_otp]
# 4152127777 = "123456"

# Configure logged in session timeouts.
# [auth.sessions]
# Force log out after the specified duration.
# timebox = "24h"
# Force log out if the user has been inactive longer than the specified duration.
# inactivity_timeout = "8h"

# This hook runs before a token is issued and allows you to add additional claims based on the authentication method used.
# [auth.hook.custom_access_token]
# enabled = true
# uri = "pg-functions://<database>/<schema>/<hook_name>"

# Configure one of the supported SMS providers: `twilio`, `twilio_verify`, `messagebird`, `textlocal`, `vonage`.
[auth.sms.twilio]
enabled = false
account_sid = ""
message_service_sid = ""
# DO NOT commit your Twilio auth token to git. Use environment variable substitution instead:
auth_token = "env(SUPABASE_AUTH_SMS_TWILIO_AUTH_TOKEN)"

# Multi-factor-authentication is available to Supabase Pro plan.
[auth.mfa]
# Control how many MFA factors can be enrolled at once per user.
max_enrolled_factors = 10

# Control MFA via App Authenticator (TOTP)
[auth.mfa.totp]
enroll_enabled = false
verify_enabled = false

# Configure MFA via Phone Messaging
[auth.mfa.phone]
enroll_enabled = false
verify_enabled = false
otp_length = 6
template = "Your code is {{ .Code }}"
max_frequency = "5s"

# Configure MFA via WebAuthn
# [auth.mfa.web_authn]
# enroll_enabled = true
# verify_enabled = true

# Use an external OAuth provider. The full list of providers are: `apple`, `azure`, `bitbucket`,
# `discord`, `facebook`, `github`, `gitlab`, `google`, `keycloak`, `linkedin_oidc`, `notion`, `twitch`,
# `twitter`, `slack`, `spotify`, `workos`, `zoom`.
[auth.external.apple]
enabled = false
client_id = ""
# DO NOT commit your OAuth provider secret to git. Use environment variable substitution instead:
secret = "env(SUPABASE_AUTH_EXTERNAL_APPLE_SECRET)"
# Overrides the default auth redirectUrl.
redirect_uri = ""
# Overrides the default auth provider URL. Used to support self-hosted gitlab, single-tenant Azure,
# or any other third-party OIDC providers.
url = ""
# If enabled, the nonce check will be skipped. Required for local sign in with Google auth.
skip_nonce_check = false

# Use Firebase Auth as a third-party provider alongside Supabase Auth.
[auth.third_party.firebase]
enabled = false
# project_id = "my-firebase-project"

# Use Auth0 as a third-party provider alongside Supabase Auth.
[auth.third_party.auth0]
enabled = false
# tenant = "my-auth0-tenant"
# tenant_region = "us"

# Use AWS Cognito (Amplify) as a third-party provider alongside Supabase Auth.
[auth.third_party.aws_cognito]
enabled = false
# user_pool_id = "my-user-pool-id"
# user_pool_region = "us-east-1"

[edge_runtime]
enabled = true
# Configure one of the supported request policies: `oneshot`, `per_worker`.
# Use `oneshot` for hot reload, or `per_worker` for load testing.
policy = "oneshot"
# Port to attach the Chrome inspector for debugging edge functions.
inspector_port = 8083

# Use these configurations to customize your Edge Function.
# [functions.MY_FUNCTION_NAME]
# enabled = true
# verify_jwt = true
# import_map = "./functions/MY_FUNCTION_NAME/deno.json"
# Uncomment to specify a custom file path to the entrypoint.
# Supported file extensions are: .ts, .js, .mjs, .jsx, .tsx
# entrypoint = "./functions/MY_FUNCTION_NAME/index.ts"
# Specifies static files to be bundled with the function. Supports glob patterns.
# For example, if you want to serve static HTML pages in your function:
# static_files = [ "./functions/MY_FUNCTION_NAME/*.html" ]

[analytics]
enabled = true
port = 54327
# Configure one of the supported backends: `postgres`, `bigquery`.
backend = "postgres"

# Experimental features may be deprecated any time
[experimental]
# Configures Postgres storage engine to use OrioleDB (S3)
orioledb_version = ""
# Configures S3 bucket URL, eg. <bucket_name>.s3-<region>.amazonaws.com
s3_host = "env(S3_HOST)"
# Configures S3 bucket region, eg. us-east-1
s3_region = "env(S3_REGION)"
# Configures AWS_ACCESS_KEY_ID for S3 bucket
s3_access_key = "env(S3_ACCESS_KEY)"
# Configures AWS_SECRET_ACCESS_KEY for S3 bucket
s3_secret_key = "env(S3_SECRET_KEY)"

```




## 两种办法

supabase 理论上有两种私有化部署。

官方最推荐的是基于 docker，参考 [Self-Hosting with Docker | Supabase Docs](https://supabase.com/docs/guides/self-hosting/docker)。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/028bc7fde6b14d90f97df802e039ea22.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)




### 方法一：基于 Docker


```shell
# Get the code
git clone --depth 1 https://github.com/supabase/supabase

# Make your new supabase project directory
mkdir supabase-project

# Tree should look like this
# .
# ├── supabase
# └── supabase-project

# Copy the compose files over to your project
cp -rf supabase/docker/* supabase-project

# Copy the fake env vars
cp supabase/docker/.env.example supabase-project/.env

# Switch to your project directory
cd supabase-project

# Pull the latest images
docker compose pull

# Start the services (in detached mode)
docker compose up -d
```

这会启动一个本地 docker 的 supabase，并跑在 8000 端口，访问 http://localhost:8000 即可。

其中，如果你想改配置，只需要修改 `.env` 文件即可，完了重新跑一下。

```shell
docker compose down
docker compose up -d
```


具体怎么改配置呢？

**请参考官方教程 [Self-Hosting with Docker | Supabase Docs](https://supabase.com/docs/guides/self-hosting/docker#advanced) 改，不要自己乱改，因为各个配置项之间可能存在关联。**


```ad-warning
supabase 默认的 postgresql 跑在端口 5432，如果我们的服务器本地已经跑了一个 postgresql，且端口是默认的 5432，则会冲突报错：

	```shell
	Error response from daemon: failed to set up container networking: driver failed programming external connectivity on endpoint supabase-pooler (93159d3457469fa122ea62b16619ad56185fd43c993c4921d8bcd35240628f0a): failed to bind host port for 0.0.0.0:5432:172.18.0.8:5432/tcp: address already in use
	```


这个时候我们只需要修改 `.env` 里的 5432，改成例如 5433、5434 即可。

或者直接关掉本地的 postgresql，如果你是新手，你的 postgresql 没有在跑业务的话。
```


**官网的 self-host 教程真地写地很好，建议从头到尾跟着跑一遍**。（上一次看到教程写这么好的还是 几年前的 fastapi，如今也已经 80+ k star 了）

相信川哥的技术审美，作为在任何一家公司都呆不超过两个月的攻城狮，能让我 follow 的，都有几把刷子。

毕竟。

**It's all about taste**。

### 方法二：二开

如果你希望修改 supabase 的一些逻辑，二开是一种方式，具体参考：[Local Development & CLI | Supabase Docs](https://supabase.com/docs/guides/local-development)。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/eb21f5b9f572a80a2772aa8eaf4b04e3.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


```ad-important
值得注意的是，如果你让大模型在你的项目里集成 supabase，它们往往会采用二开的方式，但其实，直接拉一个 docker，然后与项目解耦的运行，是最稳妥的。
```

二开有个潜在的坑，那就是 基于 supabase cli 生成的代码，配置文件是用的 `toml`，而非 self-host docker 版本的环境变量，这中间有些互换成本。

anyway，都二开了，不用我教了，欢迎遇到坑了一起交流（我已经发现不少了）。

## 几大模块

###  Studio 主面板


根据教程（[Self-Hosting with Docker | Supabase Docs](https://supabase.com/docs/guides/self-hosting/docker#dashboard-authentication)），默认的 supabase dashboard 的用户信息是：

```
- Username: `supabase`
- Password: `this_password_is_insecure_and_should_be_updated`
```

它在我们的 `.env` 的开头就有，要自己修改。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/97258186dff9fd29120de73e0602d70e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


我们可以直接在 nginx 里配置好 8000 的反向代理，我反向代理到了 `supabase-studio.cs-magic.cn`，这样公网即可访问。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/202bfdc61fddeaa64e82ac65c93fbbff.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

登录成功。
![](https://poketto.oss-cn-hangzhou.aliyuncs.com/42e1ef9b9c19583b26e010e258db453e.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


### 数据库

数据库可以直接在 Studio 内查看与管理。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425171620.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

数据库的用户名和密码稍微复杂一点，参考教程（[Self-Hosting with Docker | Supabase Docs](https://supabase.com/docs/guides/self-hosting/docker#accessing-postgres)）分两种，一种是基于会话，一种是基于连接池。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/e9d54527bf8fb8f814e86e8e5ec04774.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



这两种在连接上的写法差异仅在端口，一个 5432，一个 6543。

**但要注意，默认用户名是 `postgres.your-tenant-id` 而非 `postgres`，这个要注意，很容易犯错。**

这个信息可以在配置里改。

```ad-warning
不过要谨慎，我尝试只修改 `POSTGTRES_PASSWORD`，会导致 `Container supabase-analytics` 无法启动，查看后台，原因是账号密码不对。

`23:38:21.220 [error] Postgrex.Protocol (#PID<0.151.0>) failed to connect: ** (Postgrex.Error) FATAL 28P01 (invalid_password) password authentication failed for user "supabase_admin"`

具体修改办法还在研究。
```

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/efca073b6f454a6cfcaada6a87e26b1a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)




### API（基于 KONG 的后端服务）

这个关乎着很多后端的服务。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425171750.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


## 几个最佳实践

### 数据库保活

参考我之前写的文章：[一手实测：Supabase 免费版项目如何彻底防止自动冻结？](https://mp.weixin.qq.com/s/4ensX3InHcBaEdXnmbtZOQ)


### 配置远程 RDS 数据库？

**这是一个艰难的话题，个人建议不要。**

也就是说，只要用 supabase，就默认数据库是 postgresql，并且嵌在了服务里。

参考：
- [Can I use AWS RDS database URL instead of Supabase URL in hosted Supabase? · supabase · Discussion #21081](https://github.com/orgs/supabase/discussions/21081)
- [自托管和解耦数据库：r/Supabase --- Self Hosting and decouple database : r/Supabase](https://www.reddit.com/r/Supabase/comments/169oexl/self_hosting_and_decouple_database/)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/12e6b40ff5153dc4f6091ee30426a888.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

### 开发过程（重要）

从我过往打交道的很多团队中抽象来看，即便是看起来很先进的公司、团队，他们在先进技术的理解上往往止步于一知半解，可能是出于业务上线的压力，也可能是出于国内技术栈与海外的差异，等等。

在前两年我看知名的 prompt 社区 flowgpt 这样一款年轻的产品，就在用 trpc 的技术（尽管随着 nextjs app router 的流行，trpc 已经显得没有那么必要，但那个时候，它的开发体验还是很棒的）；以及知名的图像生成社区 civitai 的源码时，发现他们采用了 prisma，并且有非常详细完整的 migration 记录；而我在前司却发现光是 migrate 这样的一个操作他们很多人都是没有按照规范去操作，甚至是基于传统 DBA 的思路去修改数据库的。

更不用说跨区、跨表、跨 schema 等细节问题了。

当然，这里面真地很复杂了。

话说回来，supabase 由于是一整套 BAAS 的解决方案，它的复杂性比 prisma 还要再上一个层级。

我目前能想到的有几种模式。

第一种是用 docker 创建一个独立的 supabase 作为统一的后端，然后不同的前端 app 都共享这样的一个 supabase。

第二种是每个 app 一个内嵌的独立的 supabase。

代码上以上都比较简单，但在 migrate 的时候，则会非常头疼。

这边我就直接摘抄 gpt-4o 的回复了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/8aa9c90e6a90079eada2fab7c824cb62.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)


但除此之外，还涉及到一个细节。

那就是我们在使用 cli 进行 migrate 的时候，是有默认不同的操作逻辑的。

一套主要用于本地，比如 `start | stop | status` 之类。

一套主要用于 supabase 云端，比如 `link` 等。

还有一套两类场景都支持，比如 `push` 等。

这个很微妙，我是查了大量资料，才最终摸索出一种最佳实践如下：

1. 在项目目录基于 supabase cli 启动默认的 54322 端口的 supabase 作为开发环境高速迭代
2. 同时在系统根目录基于 docker 启动默认的 5432 端口的 supabase 作为生产环境（关掉系统postgres）
3. 当需要将开发环境同步给生产环境时，只需 `supabase db push --db-url "postgres://postgres.your-tenant-id:your-super-secret-and-long-postgres-password@localhost:5432/postgres"`

```ad-tip
这里的 `--db-url` 是一个关键，它会识别出目标数据库是在本地亦或云端（默认）。

如果不加的话，它会报错：`Cannot find project ref. Have you run supabase link?`。

这不是我们本地化部署想要的答案，这是个陷阱。

btw，注意最好使用 postgres 数据库，而非其他，gpt 告诉我的，我还需要 verify 这条 principle，参考：https://chatgpt.com/share/680ec90f-3e58-800b-868e-38deaa90717b
```




---

以上就是本期 supabase 私有化的全部记录，希望对你有所帮助。


下期我们会系统提一提自定义 SMTP 邮箱集成的问题与踩过的坑，下期我们再会！

