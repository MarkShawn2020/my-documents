这是个很实际的问题，我分享几个优化思路：

## 1. 在 CLAUDE.md 中预置常用 skill 路径

在项目根目录的 `CLAUDE.md` 中直接写明常用 skill 的位置，Claude Code 就不需要每次都去搜索：

```markdown
## 常用 Skills
- 创建文档: /mnt/skills/public/docx/SKILL.md
- 生成PPT: /mnt/skills/public/pptx/SKILL.md
- 前端设计: /mnt/skills/public/frontend-design/SKILL.md
```

## 2. 精简 SKILL.md 内容

skill 文件越长，解析越慢。保持 SKILL.md 简洁：

- 核心指令放最前面
- 示例代码用最小可运行版本
- 把详细文档拆分到子文件，按需读取

## 3. 使用明确的触发词

在提示词中用精确的关键词，比如：

- ❌ "帮我做个表格文件"
- ✅ "用 xlsx skill 创建一个表格"

## 4. 自定义 skill 放在固定位置

把自己写的 skill 统一放在 `/mnt/skills/user/` 下，并在 CLAUDE.md 中建立索引，避免 Claude Code 到处找。

## 5. 合并相关 skills

如果经常组合使用多个 skill（比如生成图片+插入文档），可以写一个聚合 skill，一次读取搞定。

---

你现在主要是在哪个场景下觉得慢？是 skill 发现阶段还是执行阶段？我可以针对性给更具体的建议。