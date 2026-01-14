# Apple 开发者证书与密钥体系科普

## 一、证书类型

### 1. **Development Certificate（开发证书）**

- **用途**：在真机上调试测试应用
- **数量限制**：个人账号最多 2 个
- **有效期**：1 年

### 2. **Distribution Certificate（发布证书）**

#### **App Store Distribution（应用商店发布）**

- 用于提交到 App Store
- 个人账号最多 3 个
- 有效期：1 年

#### **Ad Hoc Distribution（临时分发）**

- 用于内部测试，最多 100 台设备
- 不需要单独证书，使用 Distribution 证书

#### **Developer ID（macOS 专用）**

- 用于在 App Store 外分发 macOS 应用
- 需要公证（Notarization）

### 3. **Push Notification Certificate**

- 用于发送推送通知
- 分为开发和生产环境

---

## 二、密钥体系

### **1. 私钥（Private Key）**

```
📱 Mac 钥匙串中存储
🔐 创建证书时自动生成
⚠️ 绝对不能泄露！
```

### **2. 证书签名请求（CSR）**

- 包含公钥
- 用于向 Apple 申请证书

### **3. .p12 文件**

- 证书 + 私钥的导出格式
- 用于在多台 Mac 间共享

---

## 三、配置文件（Provisioning Profiles）

|类型|用途|设备限制|
|---|---|---|
|**Development**|开发调试|需注册设备 UDID|
|**Ad Hoc**|内部测试|最多 100 台|
|**App Store**|正式发布|无限制|

---

## 四、是否能给第三方合作伙伴？

### ✅ **可以分享的**

1. **App Store Connect 访问权限**
    
    - 通过"用户和访问"添加成员
    - 分配不同角色（开发者、营销等）
2. **Provisioning Profiles**
    
    - 可以分享配置文件
    - 对方无法用于其他项目
3. **TestFlight 测试**
    
    - 邀请外部测试人员
    - 无需分享证书

### ❌ **不建议分享的**

1. **私钥和 .p12 文件**
    
    - 对方可以冒充你发布应用
    - 可以访问你的所有项目
    - 存在安全风险
2. **Apple ID 账号密码**
    
    - 完全控制权，极度危险

---

## 五、安全建议

### **与第三方合作的正确方式：**

#### **方案 1：App Store Connect 团队协作**（推荐）

```
1. 登录 App Store Connect
2. 用户和访问 → 添加用户
3. 分配适当角色权限
4. 对方用自己的 Apple ID 登录
```

#### **方案 2：CI/CD 自动化**

- 使用 Fastlane + Match
- 证书存储在加密仓库
- 团队成员统一管理

#### **方案 3：临时协作**

- 只分享特定项目的 Provisioning Profile
- 开发完成后立即撤销
- 定期更换证书

### **⚠️ 关键原则：**

```
❌ 永远不要分享：Apple ID 密码、私钥原文
✅ 使用平台功能：App Store Connect 权限管理
🔐 定期审查：检查证书使用情况
```

---

## 六、证书管理工具

1. **Xcode**：自动管理（Automatically manage signing）
2. **Fastlane Match**：团队证书同步
3. **Apple Developer Portal**：手动管理

---

## 七、常见问题

**Q: 证书过期了怎么办？** A: 重新创建即可，不影响已发布的应用

**Q: 私钥丢失了怎么办？** A: 需要撤销证书并重新创建

**Q: 个人账号能转成公司账号吗？** A: 不能直接转换，需要重新申请

需要我详细解释某个特定部分吗？