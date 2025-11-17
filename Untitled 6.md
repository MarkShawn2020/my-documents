# macOS 应用签名和分发 - 账号配置指南

你好！为了让 Lovmind 应用能够正常分发给用户使用，需要你在 Apple Developer 账号中完成以下配置。

需要完成的任务清单

1. ✅ 获取 Team ID

2. ✅ 创建 Developer ID Application 证书

3. ✅ 生成 App-specific password（应用专用密码）

4. ✅ 将证书和信息发给开发者

---

第一步：获取 Team ID

1. 访问  [https://developer.apple.com/account](https://developer.apple.com/account) 

2. 登录你的 Apple Developer 账号

3. 在页面顶部找到 Membership details（会员详情）或左侧菜单点击 Membership

4. 找到 Team ID（10个字符，类似 F2R98GKMH2）

5. 复制并记下这个 Team ID

---

第二步：创建 Developer ID Application 证书

2.1 在 Apple Developer 网站操作

1. 访问  [https://developer.apple.com/account/resources/certificates/list](https://developer.apple.com/account/resources/certificates/list) 

2. 点击右上角蓝色 ➕ 按钮（添加新证书）

3. 在证书类型列表中，找到并选择：

- Developer ID Application（用于在 Mac App Store 外分发应用）

1. 点击 Continue（继续）

2.2 生成证书签名请求（CSR）文件

接下来页面会提示你上传 CSR 文件。需要在 Mac 电脑上操作：

1. 打开 钥匙串访问 应用（Keychain Access）

- 在 Mac 上按 ⌘ + 空格 搜索 "钥匙串访问" 或 "Keychain Access"

1. 顶部菜单：钥匙串访问 → 证书助理 → 从证书颁发机构请求证书

2. 填写信息：

- 用户电子邮件地址：填写你的 Apple ID 邮箱

- 常用名称：填写你的名字（如 Yu PENG）

- CA 电子邮件地址：留空

- 选择 存储到磁盘

1. 点击 继续，保存文件（会生成一个 .certSigningRequest 文件）

2.3 上传 CSR 并下载证书

1. 回到浏览器，点击 Choose File，上传刚才保存的 .certSigningRequest 文件

2. 点击 Continue

3. 证书创建成功后，点击 Download 下载证书文件（.cer 文件）

4. 双击下载的 .cer 文件，会自动安装到钥匙串中

---

第三步：导出证书文件（给开发者使用）

1. 打开 钥匙串访问 应用

2. 左侧选择 登录 → 我的证书

3. 找到刚才安装的证书，名称是 Developer ID Application: 你的名字 (TEAM_ID)

4. 右键点击证书 → 选择 导出 "Developer ID Application: ..."

5. 保存设置：

- 文件格式选择：个人信息交换 (.p12)

- 设置一个密码（记住这个密码，需要告诉开发者）

- 保存文件

---

第四步：生成 App-specific password（应用专用密码）

这个密码用于自动化上传应用给 Apple 审核（公证）。

1. 访问  [https://appleid.apple.com](https://appleid.apple.com/) 

2. 登录你的 Apple ID

3. 在 安全 部分，找到 App-specific Passwords（应用专用密码）

4. 点击 Generate an app-specific password（生成应用专用密码）

5. 输入密码名称，例如：Lovmind Notarization

6. 点击 Create

7. 复制生成的密码（格式类似 xxxx-xxxx-xxxx-xxxx，只会显示一次！）

---

第五步：发送信息给开发者

请将以下信息发给开发者：

1. Team ID（第一步获取的）

2. 证书文件（.p12 文件，第三步导出的）

3. 证书密码（导出 .p12 时设置的密码）

4. Apple ID 邮箱（用于公证的邮箱）

5. App-specific password（第四步生成的密码）

---

常见问题

Q: 我找不到 "Developer ID Application" 选项？ A: 确认你的 Apple Developer 账号已付费（$99/年）。免费账号无法创建此类证书。

Q: 钥匙串中找不到证书？ A: 确保下载 .cer 文件后双击安装，并在"登录"钥匙串的"我的证书"分类中查找。

Q: App-specific password 忘记了怎么办？ A: 可以删除旧密码并重新生成一个。