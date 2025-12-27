在前几天我们陆续做了几期关于 claude code slash command 的科普，包括：

- [Vol 52. Claude Code Command：被严重低估的效率神器](https://mp.weixin.qq.com/s/KzrkXnR3nrq-oIxFHU8xmw)
- [Vol54. /checkpoint 命令增强项目管理](https://mp.weixin.qq.com/s/P5OmJH8gwr7dq8RQv0MZmQ)

尽管我们在文中提到，创建一个 slash command 是非常容易的，一句话搞定：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/5c7e34ccedc6936e02e28a29c2561a35.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

但实际上，这种写法并不是很稳健。

今天早上我在尝试创建一个命令时就出现了问题：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/f6835c570012f573e12545b3ec454bd4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

其实我这个 prompt 说的已经够清楚了，开头就亮明：“实现 slash command”。

然而，它很显然并没有很理解，并且把当前工作区理解为待实现工作区，这是危险操作，我立即 ESC 喊停了。

---

基于这样的问题，我意识到我们应该创建一个创建slash command的slash command，也就是 meta slash commad。

话不多说，直接先上干货，把以下命令复制存储到 `~/.claude/commands/generate-command.md` 即可。

```
---
allowed-tools: Write(*), Read(*), Bash(mkdir:*), Bash(ls:*), Bash(echo:*), Bash(cp:*), Bash(date:*)
description: Generate a new slash command with version management support
version: "2.0.0"
author: markshawn2020
---

# Generate Slash Command with Version Management

You are creating a new slash command with built-in version management. Based on the user's requirements in $ARGUMENTS, generate a complete slash command file with version control.

## Version Management Features

This command supports:
- **Semantic versioning** (MAJOR.MINOR.PATCH)
- **Automatic backup creation** when updating existing commands
- **Version history tracking** in YAML frontmatter
- **Changelog generation** for updates

## Instructions:

1. **Parse the arguments**: The format should be `<command-name> "<description>" [project|user] [version] [additional-requirements]`
   - command-name: The name of the slash command (without /)
   - description: What the command does
   - scope: "project" (`.claude/commands/`) or "user" (`~/.claude/commands/`) - defaults to "user"
   - version: Semantic version (defaults to "1.0.0" for new commands)
   - additional-requirements: Any special features needed

2. **Version Management Process**:
   - Check if command file already exists
   - If exists: Create backup with current version number
   - Update version number (increment appropriately)
   - Add changelog entry to frontmatter

3. **Create the appropriate directory structure**:
   - For project commands: `.claude/commands/`
   - For user commands: `~/.claude/commands/`
   - Create `versions/` subdirectory for backups if needed

4. **Generate the command file** with enhanced YAML frontmatter:
	```yaml
	---
	allowed-tools: [appropriate tools]
	description: [command description]
	version: "X.Y.Z"
	created: "YYYY-MM-DD"
	updated: "YYYY-MM-DD"
	changelog:
	 - version: "X.Y.Z"
	   date: "YYYY-MM-DD"
	   changes: ["Initial version" or specific changes]
	---
	```

5. **Backup Strategy**:
   - Before updating: `cp command-name.md command-name.v[old-version].md`
   - Keep backup files for rollback capability
   - Optional: Move backups to `versions/` subdirectory

6. **Consider these features based on requirements**:
   - Git operations: Include git-related allowed-tools
   - File operations: Include Read, Write, Edit tools
   - GitHub operations: Include Bash(gh:*) tools
   - Web operations: Include WebFetch, WebSearch tools
   - Directory operations: Include LS, Glob, Grep tools

## Example allowed-tools patterns:
- `Bash(git:*)` - for git commands
- `Bash(gh:*)` - for GitHub CLI commands  
- `Read(*)`, `Write(*)`, `Edit(*)` - for file operations
- `LS(*)`, `Glob(*)`, `Grep(*)` - for directory/search operations
- `WebFetch(*)`, `WebSearch(*)` - for web operations

## Command arguments: $ARGUMENTS

Create the slash command file now with version management, ensuring it follows best practices for Claude Code slash commands.
```

实战效果：

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/02f957c0418b05f8e5b0cb4cd80b8801.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

比如我们希望cc能够干活更积极一些（**拒绝降智，从你做起**）。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/0a938e9bb4609eb18b67013669719d8d.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

一分钟内他就嘎嘎肝完了。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/00818ef5928b7eeb67eb9068d49aaa8a.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

我们体验一下它这个命令质量到底如何~

`claude -c` 打开想要提升工作质量的cc工作区，然后输入 `/happi...`（具体看它生成了啥命令，因为我们没有约束它的文件名）

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/f4f77d754a62c6f8ffe3a4656b304beb.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

Tab键确认选择。

然后cc就把自己之前的工作嘎嘎夸了一顿（也许它自己都信了：）

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/06970b4dac197cc75194f62a82dc3ab4.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

怎么样，还行吧~

---

但如果我们只是说到这，你可能还是不太能感受到这玩意的强大威力。

甚至会觉得这篇文章有点标题党，就这，还顶级Vibe Coder？你也配？我呸！

但是。

请你仔细想一想。

高手之间的普遍共性是什么？

是会总结，是会复利。

他们会把所有有用的经验、技巧、教训都总结在一个“小本本”上，为的就是建立自己的思维认知的高速公路，降低自己的熵。

想象一下，一个通过自己的meta slash command 创建了一堆自己的魔法 slash command的顶级vibe coder，你觉得他像谁？

是不是比邓布利多还哈利波特？？

它是真正掌握魔法的男人！

所以，你的cc和别人的cc一样吗？

那一定是不一样的。

但你会了我们的meta slash command后。

也许，你每天都可以比昨天的自己更优秀一些。

至少，你不再是麻瓜了，你随时拥有通往霍格沃兹的秘钥！

