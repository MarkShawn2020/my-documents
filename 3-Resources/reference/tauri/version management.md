这是一个非常好的问题。Tauri 项目的独特性在于它是一个“混合体”：前端通常是一个 Node.js 项目（由 `package.json` 管理），而后端核心是一个 Rust 项目（由 `Cargo.toml` 管理），同时 Tauri 自身还有一个配置文件（`tauri.conf.json`）。

这就导致了一个核心挑战：**如何保持这三个地方的版本号同步，并确立唯一的“事实来源（Source of Truth）”？**

如果不采用最佳实践，你可能会遇到版本号混乱、自动更新失败或者构建出的应用版本显示错误等问题。

以下是使用 Tauri 脚手架进行版本管理的最佳实践指南：

---

### 1. 核心原则：确立唯一的“事实来源”

在 Tauri 项目中，涉及到版本号的文件主要有三个：

1.  **`src-tauri/tauri.conf.json` (最重要):**
    *   位置: `package.version`
    *   作用: 这是最终打包出来的可执行文件、安装程序向操作系统展示的版本号，也是 Tauri 自动更新机制依赖的版本号。
    *   **结论: 这必须是你的“事实来源”。**

2.  **`src-tauri/Cargo.toml`:**
    *   位置: `package.version`
    *   作用: Rust 用于管理 crate 的版本。对于最终用户应用来说，它必须与 `tauri.conf.json` 保持一致，否则 `cargo tauri build` 可能会发出警告甚至错误。

3.  **`package.json` (根目录):**
    *   位置: `version`
    *   作用: 前端项目的版本。虽然它不直接影响最终的 Tauri 二进制文件，但为了项目的一致性，尤其是在团队协作或前端也单独部署为 Web 应用时，保持同步是很好的做法。

### 2. 遵循语义化版本控制 (SemVer)

严格遵守 [SemVer (语义化版本)](https://semver.org/lang/zh-CN/) 规范：`主版本号.次版本号.修订号` (例如 `1.2.3`)。

*   **主版本号 (Major):** 当你做了不兼容的 API 修改（对于桌面应用，通常指重大的功能变更或架构调整）。
*   **次版本号 (Minor):** 当你做了向下兼容的功能性新增。
*   **修订号 (Patch):** 当你做了向下兼容的问题修正。

Tauri 的自动更新机制高度依赖 SemVer 来判断是否需要更新。

### 3. 同步策略：自动化是关键

手动修改三个文件是容易出错的。最佳实践是引入自动化流程。

#### 方法 A：使用 Node.js 脚本（推荐，轻量级）

如果你主要在前端生态中工作，编写一个简单的 Node.js 脚本来处理版本升级是最灵活的方式。这个脚本会读取一个主版本号，然后更新其他文件。

**步骤示例：**

1.  在项目根目录创建一个脚本 `scripts/bump-version.js`：

```javascript
// scripts/bump-version.js
const fs = require('fs');
const path = require('path');
const execSync = require('child_process').execSync;

// 读取命令行参数，例如: node scripts/bump-version.js 1.2.3
const newVersion = process.argv[2];

if (!newVersion) {
  console.error('请提供新版本号，例如: node scripts/bump-version.js 1.2.3');
  process.exit(1);
}

// 1. 更新 package.json (作为事实来源的输入方便些，或者你可以反过来)
const packageJsonPath = path.resolve(__dirname, '../package.json');
const packageJson = require(packageJsonPath);
packageJson.version = newVersion;
fs.writeFileSync(packageJsonPath, JSON.stringify(packageJson, null, 2) + '\n');
console.log(`已更新 package.json 至 ${newVersion}`);

// 2. 更新 tauri.conf.json (关键!)
const tauriConfPath = path.resolve(__dirname, '../src-tauri/tauri.conf.json');
const tauriConf = require(tauriConfPath);
tauriConf.package.version = newVersion;
fs.writeFileSync(tauriConfPath, JSON.stringify(tauriConf, null, 2) + '\n');
console.log(`已更新 tauri.conf.json 至 ${newVersion}`);

// 3. 更新 Cargo.toml
// Cargo.toml 是 TOML 格式，不想引入 TOML 解析库的话，可以使用正则替换 (简单场景够用)
const cargoTomlPath = path.resolve(__dirname, '../src-tauri/Cargo.toml');
let cargoTomlContent = fs.readFileSync(cargoTomlPath, 'utf8');
// 替换 [package] 下的 version = "x.x.x"
cargoTomlContent = cargoTomlContent.replace(
  /^version = "[^"]+"$/m,
  `version = "${newVersion}"`
);
fs.writeFileSync(cargoTomlPath, cargoTomlContent);
console.log(`已更新 Cargo.toml 至 ${newVersion}`);

// 4. (可选) 创建 Git commit 和 tag
try {
    execSync(`git add .`);
    execSync(`git commit -m "chore: bump version to ${newVersion}"`);
    execSync(`git tag v${newVersion}`);
    console.log(`已创建 Git commit 和 tag v${newVersion}`);
} catch (e) {
    console.error('Git 操作失败，请手动提交。');
}

console.log('版本升级完成！');
```

2.  在 `package.json` 中添加快捷命令：

```json
"scripts": {
  "bump": "node scripts/bump-version.js"
}
```

3.  使用方式：运行 `npm run bump 1.0.1` 即可自动同步所有文件并打上 Git tag。

#### 方法 B：使用标准版本管理工具（如 `standard-version` 或 `release-it`）

这些工具通常用于 Node.js 项目，能够根据 conventional commits（约定式提交）自动生成 CHANGELOG.md 并决定下一个版本号。

如果使用这些工具，你需要配置它们以支持更新 Tauri 的文件。

以 `standard-version` 为例，你需要配置其 `bumpFiles` 选项。在 `package.json` 中添加配置：

```json
"standard-version": {
  "bumpFiles": [
    {
      "filename": "package.json",
      "type": "json"
    },
    {
      "filename": "src-tauri/tauri.conf.json",
      "type": "json",
      // 指定更新 tauri.conf.json 中的哪个字段
      "updater": {
          "readVersion": "version => version",
          "writeVersion": "(contents, version) => { const json = JSON.parse(contents); json.package.version = version; return JSON.stringify(json, null, 2); }"
      }
    },
    {
      "filename": "src-tauri/Cargo.toml",
      "updater": "scripts/update-cargo-toml.js" // 你需要编写一个简单的脚本来更新 TOML
    }
  ]
}
```
*注意：由于 Cargo.toml 是 TOML 格式，标准工具支持不如 JSON 好，可能需要像上面那样写自定义 updater 脚本。这使得配置稍微复杂了一些。*

#### 方法 C：使用 Rust 工具 (`cargo-release`)

如果你更偏向 Rust 生态，可以使用 `cargo-release`。它可以很好地处理 `Cargo.toml` 的更新和 Git 操作。

但是，它默认不会更新 `package.json` 或 `tauri.conf.json`。你需要配置它的 `pre-release-hook` 来执行脚本更新这两个 JSON 文件。这通常比方法 A 更复杂。

### 4. 与 CI/CD 集成 (GitHub Actions)

版本管理的最终目的是为了发布。在 CI/CD 中，流程通常是这样的：

1.  在本地开发，提交代码。
2.  准备发布时，在本地运行版本升级脚本（如上面的 方法 A），这会更新版本号并创建一个 Git Tag (例如 `v1.0.1`)。
3.  将代码和 Tag 推送到远程仓库 (`git push && git push --tags`)。
4.  GitHub Actions 监听 Tag 的推送事件，触发构建流程。

**推荐使用官方的 `tauri-apps/tauri-action`。**

它会自动读取 `src-tauri/tauri.conf.json` 中的版本号来命名构建产物，并创建 GitHub Release。

```yaml
# .github/workflows/release.yml 示例片段
name: Release
on:
  push:
    tags:
      - 'v*' # 当推送 v 开头的 tag 时触发

jobs:
  release:
    # ... 环境配置省略 ...
    steps:
      - uses: actions/checkout@v4
      
      # ... 安装 Node 和 Rust 依赖省略 ...

      - name: Build Tauri App
        uses: tauri-apps/tauri-action@v0
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
          # 如果配置了自动更新，需要签名密钥
          TAURI_PRIVATE_KEY: ${{ secrets.TAURI_PRIVATE_KEY }}
          TAURI_KEY_PASSWORD: ${{ secrets.TAURI_KEY_PASSWORD }}
        with:
          tagName: ${{ github.ref_name }} # 使用 tag 名称，例如 v1.0.1
          releaseName: 'App Name v__VERSION__' # __VERSION__ 会被自动替换为 tauri.conf.json 中的版本
          releaseBody: 'See the assets to download this version and install.'
          releaseDraft: true
          prerelease: false
```

### 总结：最佳实践流程图

1.  **开发阶段：** 专注于代码，遵循常规 git 提交流程。
2.  **准备发布：**
    *   决定新的 SemVer 版本号 (例如 `1.1.0`)。
    *   运行本地脚本 (例如 `npm run bump 1.1.0`)。
    *   该脚本自动同步 `tauri.conf.json`, `Cargo.toml`, `package.json`，并创建 Git Tag `v1.1.0`。
3.  **触发发布：**
    *   执行 `git push origin main --tags`。
4.  **CI/CD 自动化：**
    *   GitHub Actions 检测到 Tag。
    *   `tauri-action` 开始构建，它以 `tauri.conf.json` 中的 `1.1.0` 为准。
    *   构建完成，自动发布到 GitHub Releases，并上传带有版本号的安装包。