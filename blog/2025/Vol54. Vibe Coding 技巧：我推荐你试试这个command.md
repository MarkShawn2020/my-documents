

最近发现 Claude Code 的 Slash Commands 功能挺有意思的，可以自定义命令。我和 Claude 一起做了个 `/checkpoint` 命令，专门用来管理项目状态和文档。

## 起因

我经常忘记更新 README。项目都快上线了，README 还是：

```
# [PROJECT_NAME]

TODO: Add project description
```

太尴尬了。

## Slash Commands 是什么

Claude Code 有一些内置命令，比如 `/compact` 压缩对话，`/doctor` 检查安装。

但你可以自己写命令。方法很简单：

```bash
# 创建命令文件
mkdir -p ~/.claude/commands
vim ~/.claude/commands/mycommand.md
```

写个 Markdown 文件，就能在 Claude Code 里用 `/mycommand` 执行了。

## 迭代过程

### 第一版：记录状态

最开始只是想看看项目状态：

```markdown
- 当前分支: !`git branch --show-current`
- 未提交变更: !`git status`
```

`!` 可以执行 Bash 命令，结果会传给 Claude。

### 第二版：加入历史

后来想知道"从上次到现在改了什么"：

```bash
# 找上次的 checkpoint commit
LAST_HASH=$(git log --grep="checkpoint.*Generated with.*Claude Code" --oneline -1)

# 看这期间的提交
git log --oneline $LAST_HASH..HEAD
```

### 第三版：自动维护文档

既然 Claude 知道项目状态，为什么不让它直接更新文档？

于是加了这些功能：

- 检测 README 是否过时（超过30天没更新）
- 发现是模板就自动更新
- 生成项目健康报告
- 创建有意义的 commit 信息

## 完整的 /checkpoint 命令

代码比较长，主要分几部分：

```markdown
---
description: 项目检查点：历史感知 + 主动文档维护 + 智能提交
allowed-tools: Bash(git add:*), Bash(git status:*), Bash(git commit:*), Bash(git branch:*), Bash(git log:*), Bash(git diff:*), Edit, Write, Read, Glob
---

# Checkpoint - 项目检查点命令

## 环境分析

### 1. Checkpoint 历史记录
- 检查点日志: !`test -f .checkpoint_log && echo "发现历史记录" && tail -1 .checkpoint_log || echo "首次执行"`
- CLAUDE.md记录: !`grep -A 5 "## Checkpoint 记录" CLAUDE.md 2>/dev/null | tail -5 || echo "无记录"`
- 上次提交哈希: !`git log --grep="checkpoint.*Generated with.*Claude Code" --oneline -1 | awk '{print $1}' || echo "未找到"`
- 上次执行时间: !`git log --grep="checkpoint.*Generated with.*Claude Code" --format="%cd" --date=short -1 || echo "首次"`

### 2. 项目文档现状
- README文件: !`find . -maxdepth 2 -iname "readme*" -type f | head -1`
- 主要配置: !`find . -maxdepth 2 -name "package.json" -o -name "pyproject.toml" -o -name "Cargo.toml" | head -1`
- 文档时效: !`README_FILE=$(find . -maxdepth 2 -iname "readme*" -type f | head -1); if [ -n "$README_FILE" ]; then stat -f "%Sm" -t "%Y-%m-%d" "$README_FILE" 2>/dev/null || stat -c "%y" "$README_FILE" 2>/dev/null | cut -d' ' -f1; else echo "无README"; fi`
- 变更日志: !`find . -maxdepth 2 -iname "changelog*" -o -iname "history*" | head -1 || echo "无"`

### 3. Git 当前状态
- 工作区状态: !`git status --porcelain`
- 当前分支: !`git branch --show-current`
- 暂存区: !`git diff --cached --name-only | wc -l | tr -d ' '`
- 未提交变更: !`git diff --stat`

### 4. Git 历史分析
- 期间提交: !`LAST_HASH=$(git log --grep="checkpoint.*Generated with.*Claude Code" --oneline -1 | awk '{print $1}'); if [ -n "$LAST_HASH" ]; then git log --oneline $LAST_HASH..HEAD; else git log --oneline -5; fi`
- 期间变更: !`LAST_HASH=$(git log --grep="checkpoint.*Generated with.*Claude Code" --oneline -1 | awk '{print $1}'); if [ -n "$LAST_HASH" ]; then git diff --name-status $LAST_HASH..HEAD; else git diff --name-status HEAD~3..HEAD 2>/dev/null || echo "无历史记录"; fi`
- 最近提交: !`git log --oneline -3`

### 5. 其他有用资料
- 项目规模: !`find . -name "*.js" -o -name "*.ts" -o -name "*.py" -o -name "*.go" -o -name "*.rs" | wc -l | tr -d ' '`
- 依赖状况: !`CONFIG_FILE=$(find . -maxdepth 2 -name "package.json" -o -name "requirements.txt" -o -name "Cargo.toml" | head -1); if [ -n "$CONFIG_FILE" ]; then echo "配置文件: $CONFIG_FILE"; else echo "无标准配置"; fi`
- 文档目录: !`find . -maxdepth 2 -type d -name "docs" -o -name "documentation" | head -1 || echo "无"`

## 执行流程

### 1. 历史轨迹分析
- 优先读取自身历史记录（.checkpoint_log、CLAUDE.md）了解项目演进
- 对比当前文档与历史记录，识别变化趋势
- 分析期间Git提交，理解开发活动类型和强度
- 检查文档与代码的同步程度
- 基于历史轨迹评估项目发展阶段和健康度

### 2. 主动文档维护

#### README.md 自动更新（满足条件时）
**触发条件**：
- 包含模板占位符（`[PROJECT_NAME]`、`TODO`等）
- 文档落后代码超过30天
- 与配置文件信息不一致

**更新内容**：
    # 项目名称
    
    项目简介
    
    ## 安装
    npm install  # 或相应的安装命令
    
    ## 使用
    基于入口文件的使用说明
    
    ## 开发
    npm run dev  # 基于package.json scripts
    
    ## 贡献
    标准贡献指南

#### 其他文档维护
- **CHANGELOG.md**：项目有版本但缺少变更记录时自动创建
- **package.json**：同步description字段
- **配置文档**：更新环境变量说明

### 3. 检查点记录

#### 更新 CLAUDE.md
    ## Checkpoint 记录
    
    项目: [项目名]
    时间: [时间戳]
    里程碑: [当前节点]
    
    ### 技术状态
    - 代码质量: [评估]
    - 架构健康: [评估]
    
    ### 文档维护
    - [x] README.md: [更新摘要]
    - [x] 配置同步: [同步状态]
    
    ### 建议行动
    [下步建议]
    
    Git提交: [哈希]

#### 更新 .checkpoint_log
    {
      "timestamp": "ISO时间",
      "project_name": "项目名",
      "branch": "分支名",
      "previous_checkpoint": {
        "timestamp": "上次时间",
        "commit_hash": "上次哈希"
      },
      "period_analysis": {
        "commits_since_last": ["提交列表"],
        "development_phase": "开发阶段",
        "activity_intensity": "高/中/低"
      },
      "documentation_status": {
        "readme_updated": true,
        "sync_gap_days": 5,
        "update_urgency": "低"
      },
      "checkpoint_status": {
        "milestone": "里程碑",
        "health_score": 8,
        "trajectory": "上升/稳定/下降",
        "recommendations": ["建议列表"]
      }
    }

### 4. 智能提交

**首次执行**：
    [项目名]: initial project checkpoint
    
    Project: [项目名]
    Milestone: [里程碑]
    Health: [评分]/10
    
    🔍 checkpoint | Generated with [Claude Code](https://claude.ai/code)
    
    Co-Authored-By: Claude <noreply@anthropic.com>

**有历史时**：
    [项目名]: [智能描述] (checkpoint)
    
    Period: [时间段]
    Development: [主要活动]
    Progress: [提交数] commits
    Health trend: [趋势]
    
    🔍 checkpoint | Generated with [Claude Code](https://claude.ai/code)
    
    Co-Authored-By: Claude <noreply@anthropic.com>

## 文档更新规则

### 自动更新触发
- README包含`[PROJECT_NAME]`、`TODO`、`template`等占位符
- 文档修改时间比代码落后30天+
- 项目名与package.json不匹配
- 缺少基本章节（安装、使用等）

### 项目类型适配
- **前端项目**：安装、开发、构建指令
- **后端项目**：API文档、环境配置
- **通用项目**：基于代码结构的功能说明

## 预期输出

    🎯 Checkpoint 执行完成！
    
    📋 项目: [项目名] | 分支: [分支名]
    🎖️  里程碑: [当前节点] | 健康度: [评分]/10
    
    📊 历史轨迹:
       ⏱️  上次检查点: [时间/首次]
       📈 期间提交: [数量]个 ([活动强度])
       🎯 主要活动: [类型]
       📈 发展趋势: [上升/稳定/下降]
    
    📋 文档维护:
       📄 README: [已更新/最新/需处理]
       📚 其他文档: [维护状态]
       
    ✅ 本次操作:
       • [实际更新1]
       • [实际更新2]
    
    🔮 发展建议: [基于分析的具体建议]

基于项目环境和历史，开始执行检查点流程...
```


## 怎么使用

1. 把上面的代码保存到 `~/.claude/commands/checkpoint.md`
2. 在项目目录运行：

```bash
claude
> /checkpoint
```

## 实际效果

在 LACQA 项目中使用后，`/checkpoint` 做了这些事：

- 分析了 20 个提交的变化
- 发现 README 过时，自动更新
- 创建了项目健康报告
- 生成了详细的 commit 信息

[查看实际的 commit](https://github.com/MarkShawn2020/LACQA/commit/587abc7a84d68d90d841825f776faab302ca2eab)


## 还能做什么

基于这个思路，可以做更多命令：

- `/release` - 自动发版
- `/review` - 代码审查
- `/refactor` - 重构建议

## 总结

`/checkpoint` 让项目管理变简单了。不用手动检查文档是否过时，不用想着写 commit 信息，定期跑一下命令就行。

Claude Code 的 Slash Commands 是个很有潜力的功能，可以根据自己的需求定制各种命令。

如果你也做了有意思的命令，欢迎交流（公众号：手工川）。

---

_相关链接：[Claude Code 文档](https://docs.anthropic.com/en/docs/claude-code/slash-commands)_