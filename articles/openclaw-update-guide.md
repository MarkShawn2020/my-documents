# OpenClaw 更新指南

## 手动更新

OpenClaw 通过 pnpm 全局安装，手动更新命令：

    pnpm update -g openclaw

验证更新：

    openclaw --version

## 自动更新

OpenClaw 内置更新检查机制，会定期检查最新版本并提示，但不会自动安装。

如需真正的自动更新，可设置 cron job：

    crontab -e

添加以下内容（每天凌晨 3 点自动更新）：

    0 3 * * * /Users/mark/Library/pnpm/pnpm update -g openclaw

## 当前版本信息

- 当前版本：2026.2.25
- 最新版本：2026.3.2
