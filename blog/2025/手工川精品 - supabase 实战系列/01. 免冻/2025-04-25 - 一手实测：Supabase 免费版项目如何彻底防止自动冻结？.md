

> **导读**  
> Supabase 免费用户经常遇到“七天不访问即自动冻结”大坑，本文结合真实踩坑过程，梳理目前主流的保活方案、避坑要点及自动化运维最佳实践，附带 Docker + Cronicle 一键可视化方案，助你轻松守护业务在线！


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

- 1. 背景与痛点：Supabase 免费版老被冻<a name"painpoint"></a>
- 2. “保活”主流解法横评 <a name"solution-review"></a>
- 3. 实操踩坑记：每个方案优缺点 <a name"practical"></a>
    - 3.1 UptimeRobot 方案实测
        - 实践反馈
    - 3.2 curl + apikey 命令行极简方案
    - 3.3 Node.js/脚本方案
- 4. 全自动方案：Docker + Cronicle 部署全记录
    - 4.1 工具选择
    - 4.2 Docker 一键部署
    - 4.3 UI 配置与体验
- 5. 安全加固：Nginx 反向代理 + Basic Auth 配置
    - 配置步骤
- 6. 最佳实践 & 常见问题
    - Q1: log 文件越来越大怎么办？
    - Q2: 定时任务失败如何监控？
    - Q3: 多个 supabase 项目如何管理？
    - Q4: 免费额度不够怎么办？
- 7. 结语：开发者的“冻感”人生
```

---

## 1. 背景与痛点：Supabase 免费版老被冻<a name="painpoint"></a>

最近帮一个要给美国客户展示主页的项目，选了 Vercel + Supabase 组合。  
Vercel 前端体验极好，但后端用 Supabase 免费版后，授权和数据管理都很麻烦，最关键是遇到【七天无请求自动冻结】的经典问题。
![冻结提醒](https://poketto.oss-cn-hangzhou.aliyuncs.com/d1e6b15b484043775b0398a603601760.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

**真实痛点总结**：  
- 客户偶尔才查看演示主页，Supabase 随时休眠
- 数据库查看不便，授权流程繁琐
- 项目一旦被冻结，业务体验直接打折

---

## 2. “保活”主流解法横评 <a name="solution-review"></a>


一圈技术群友建议/网上方案汇总如下：

| 方案 | 成本 | 易用性 | 可维护性 | 风险/缺陷 |
|:-----|:-----|:-------|:---------|:---------|
| 私有化部署 Supabase | 高 | 复杂 | 可控 | 维护负担重 |
| 本地/服务器 Cron 脚本 | 低 | 一般 | 需手工维护 | 易忘，难统一管理 |
| 免费监控服务 (如 UptimeRobot) | 低 | 易用 | 依赖第三方 | 免费功能有限，监控体验差 |
| 可视化 Cron 管理工具（如 Cronicle） | 中 | 极佳 | 可视化运维 | 初次配置略复杂 |

> 技术亮点：本文着重介绍后两者，并实际踩坑总结优劣。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425105145.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

---

## 3. 实操踩坑记：每个方案优缺点 <a name="practical"></a>

### 3.1 UptimeRobot 方案实测

ChatGPT 推荐：  
> 用 UptimeRobot 定时 ping supabase API root，保持活跃。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425105318.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

#### 实践反馈
- 注册+配置流程很快
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425100516.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 直接填 API root，发现返回 404  
  
![UptimeRobot 404](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425103301.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
- 免费版不能自定义状态码，面板永远显示 down  

![monitor面板](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425102852.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
- Supabase 保活效果达成，但监控体验差（对强迫症极不友好）

**结论**：能用，但极不优雅，不推荐！

---

### 3.2 curl + apikey 命令行极简方案

直接用一行命令定时访问，supabase 必须带 apikey：

```shell
curl https://gxqhklwoivlpizypbtgp.supabase.co/rest/v1/uptimerobot?select=*-H "apikey: {your_key}"
````

返回 [] 即代表列表，说明请求成功，保活有效。

  

**优点**：极简，直接

**缺点**：需自己安排 cron/计划任务，长远维护和日志监控不方便。

---

### 3.3 Node.js/脚本方案

  

ChatGPT 提供 Node.js 示例：

```
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

结合 node-schedule/crontab 可以自动化执行。

  

**优点**：更灵活、易集成

**缺点**：需要 node 环境和服务器，脚本管理需自理

---

## 4. 全自动方案：Docker + Cronicle 部署全记录

  

### **4.1 工具选择**

- crontab-ui：简单但有 bug，run now 无反应，代码年久失修，**不推荐！**
  
![crontab-ui hero image](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425152551.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

    
- **Cronicle**：功能强大，UI 管理定时任务，社区活跃
    
![cronicle hero image](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425152615.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

  

### **4.2 Docker 一键部署**

  

部署命令：

```
sudo docker run -v /var/run/docker.sock:/var/run/docker.sock -v /tmp:/tmp \
--hostname localhost -p 50425:3012 --name cronicle bluet/cronicle-docker:latest
```

> -v /tmp:/tmp 是为日志/任务文件留通道，50425 是外部访问端口

  

### **4.3 UI 配置与体验**

- 浏览器访问管理面板，默认 admin/admin，登录后可自行更改

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425143919.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 可视化创建定时任务（如：curl supabase，写日志），支持分钟/小时/每天等灵活调度
    
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425145848.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 任务输出一目了然，支持健康检查和失败通知
    
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425152806.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

  

**实测效果**：

- 按设定频率自动执行，Supabase 日志每分钟都能收到请求

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425150552.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

- 最终保活任务设置为**每日凌晨 3:00**
    
![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250425152840.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

**优点**：极致可视化、无需命令行、权限/通知都很方便

**建议**：心跳（健康检查任务）可按小时/每天设置，避免日志爆炸

---

## 5. 安全加固：Nginx 反向代理 + Basic Auth 配置

  

管理面板不能裸奔，务必加认证！

>crontab-ui 需要，因为没有默认的管理员系统。
>
>但 cronicle 是有的，所以不需要。
  

### **配置步骤**

1. 创建用户名和密码：
    

```
sudo apt update && sudo apt install -y apache2-utils
sudo htpasswd -c /etc/nginx/.htpasswd 你的用户名
```

    
2. Nginx 配置 server 块，启用 Basic Auth 和反向代理
    

```
server {
    listen 443 ssl;
    server_name cron.example.com;
    ssl_certificate     /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    ...
    location / {
        auth_basic "Cron Admin Only";
        auth_basic_user_file /etc/nginx/.htpasswd;
        proxy_pass http://127.0.0.1:50425;
        ...
    }
}
```


3. 重启 nginx：
    

```
sudo nginx -t && sudo nginx -s reload
```


    
4. 刷新管理面板，成功弹出登录验证窗口
    

> **温馨提示**

> Basic Auth 的认证状态依赖浏览器内存，只有关掉所有该站点标签页/重启浏览器才会清空。

---

## 6. 最佳实践 & 常见问题

  

### **Q1: log 文件越来越大怎么办？**

- 建议用定期清理脚本或 logrotate 管理日志
    
- 可以设置历史日志自动归档/删除，避免空间爆炸
    
  

> 亲眼见过团队 log 文件 10G+，一定要及时处理！

  

### **Q2: 定时任务失败如何监控？**

- Cronicle 支持任务失败自动通知邮箱/钉钉/自定义 webhook，推荐配置
    
- 也可用“任务日志+健康检查”双保险
    

  

### **Q3: 多个 supabase 项目如何管理？**

- 建议每个项目单独设置一个定时任务，并按命名分组，便于维护
    

  

### **Q4: 免费额度不够怎么办？**

- 适时升级付费套餐，或考虑迁移私有部署/其他数据库
    

---

## 7. 结语：开发者的“冻感”人生

  

**踩坑感悟**：

- Supabase 免费版虽然香，但冷不丁就自动“冻人”，作为开发者必须提前规划保活方案
    
- Docker + Cronicle 目前是性价比与维护体验兼备的最佳实践
    

  

**欢迎留言互动**：

  

> 你遇到过 supabase 冻结的奇葩坑吗？有更优雅的保活骚操作？评论区等你分享经验，互相成就更强的独立开发生态！

---

**原创/手工川 - AI 版**

欢迎关注公众号，获取更多独立开发实战与高效自动化秘籍！
