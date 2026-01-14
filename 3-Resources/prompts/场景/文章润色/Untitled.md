刚帮 Claude Code 提了个 bug：https://github.com/anthropics/claude-code/issues/13453
软链接的 slash command 又挂了

2.0.28 版本修过一次
2.0.62 又复现了
典型的回归 bug

复现很简单
先看下我的命令目录：
- t.md -> think.md
- tt.md -> think-hard.md
- ttt.md -> think-harder.md
- tttt.md -> think-ultra.md

四个软链接 指向四个真实文件
就是图省事 搞个快捷方式

装 2.0.61 跑一下：

```
npm install -g @anthropic-ai/claude-code@2.0.61
claude -p --output-format stream-json --verbose "/tt say 1" | jq 'select(.slash_commands) | .slash_commands | map(select(test("^t")))'
```

输出：
["think-ultra","tt","think","think-harder","tttt","t","ttt","think-hard"]

8 个命令 全认出来了
软链接和真实文件一视同仁

换 2.0.62：
```
npm install -g @anthropic-ai/claude-code@2.0.62
```

同样的命令 输出变了：
["think-ultra","think","think-harder"]

只剩 3 个
t tt ttt tttt 全没了
软链接直接被无视

用 Claude Code 查 Claude Code 的 bug
有点黑色幽默
从定位到提 issue 不到 20 分钟

临时方案：回退 2.0.61
或者把软链接换成真实文件拷贝

开源项目就这样
修了又坏 坏了又修
但至少能提 issue 能复现
比闭源黑箱强