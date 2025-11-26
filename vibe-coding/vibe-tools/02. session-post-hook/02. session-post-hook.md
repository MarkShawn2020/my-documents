

这两天配置 Claude Code 的时候，突然意识到一个问题。

我把任务扔给 AI 之后，就得坐那干等着。

盯着屏幕，看它一行行输出代码，看它一个个调用工具，看它思考、编辑、提交。

整个人就像个监工，生怕它出错，又不敢走开。

这特么不对啊。

AI 不就是让我们解放双手的吗？结果我现在比以前还累。

直到我发现了 Claude Code 的 **Stop Hook**。

## 什么是 Stop Hook？

简单说，就是当 Claude Code 完成任务时，自动触发一个脚本。

你可以让它：
- 发通知
- 播放声音
- 发邮件
- 发微信
- 甚至直接启动下一个任务

**核心逻辑就是：AI 干完活了，主动来找你。**

而不是你守在那，等它干完。

## 我的配置

我配了个最简单的：**通知 + 声音**。

当 Claude Code 完成任务时：
1. macOS 通知中心弹屏
2. 播放 Hero 提示音（那个欢快的上升音阶）
3. 通知里显示我最后问的问题（前 80 字符）

效果就是，我可以：
- 去倒杯咖啡
- 去看会儿视频
- 去刷会儿推特
- 甚至去开个会

等 AI 干完活，它会主动通知我。

## 配置代码

**1. 编辑 `~/.claude/settings.json`**
```json
{
  "hooks": {
    "Stop": [
      {
        "hooks": [
          {
            "type": "command",
            "command": "~/.claude/hooks/stop_notify.sh"
          }
        ]
      }
    ]
  }
}
```

**2. 创建 `~/.claude/hooks/stop_notify.sh`**
```bash
#!/bin/bash

# 读取输入并提取信息
input=$(cat)
transcript_path=$(echo "$input" | jq -r '.transcript_path' | sed "s|^~|$HOME|")

[ ! -f "$transcript_path" ] && exit 0

# 提取任务信息
last_msg=$(tail -n 100 "$transcript_path" | jq -r 'select(.type == "message" and .role == "user") | .content[] | select(.type == "text") | .text' | tail -n 1 | head -c 80)
notification_body="${last_msg:-任务已完成}"

# 发送通知
afplay /System/Library/Sounds/Hero.aiff &
osascript -e "display notification \"$notification_body\" with title \"Claude Code 完成\" sound name \"Hero\""
```

**3. 赋予执行权限**
```bash
chmod +x ~/.claude/hooks/stop_notify.sh
```

搞定。

## 一个坑

配完之后，我发现通知根本不弹屏。

只出现在通知中心，需要手动打开才能看到。

我还以为是配置错了，折腾了半天 terminal-notifier、权限、各种参数。

最后发现。

**是专注模式。**

macOS 的专注模式默认会把所有通知静音。

而且，Claude Code 不在"允许的 App"候选列表里。

**解决办法：**

系统设置 → 专注模式 → 选择当前模式 → 取消勾选"将通知静音"

或者，在"已静音的 App"中排除你的通知工具。

搞定这个，世界清净了。

## 自定义声音

Hero 是我的选择，你可能不喜欢。

**试听所有声音：**
```bash
afplay /System/Library/Sounds/Hero.aiff
```

**可选声音：**
- **Hero** - 欢快上升音阶（我用这个）
- **Purr** - 柔和三连音
- **Tink** - 清脆短促
- **Pop** - 轻快弹跳
- **Glass** - 经典提示音
- **Ping** - 简洁单音
- **Submarine** - 声呐回声

找到喜欢的，改脚本里的两处 `Hero` 就行。

## 为什么这个功能重要

以前用 AI 编程，我的工作流是这样的：

1. 提问题
2. 等 AI 输出
3. 检查结果
4. 继续提问题
5. 继续等
6. 继续检查

整个过程，我就是个**同步阻塞**的人肉线程。

AI 在干活，我也不能干别的。

现在有了 Stop Hook：

1. 提问题
2. 切走，干别的
3. 听到提示音，切回来
4. 检查结果
5. 继续提问题
6. 继续切走

我变成了**异步非阻塞**的。

AI 干活的时候，我的时间被释放了。

这不是小优化。

这是质变。

## 更多玩法

Stop Hook 不只能发通知。

你可以让它：

**自动提交代码：**
```bash
cd $PROJECT_DIR && git add . && git commit -m "AI: 完成任务"
```

**自动运行测试：**
```bash
cd $PROJECT_DIR && npm test
```

**自动部署：**
```bash
cd $PROJECT_DIR && ./deploy.sh
```

**发送到手机：**
```bash
# 用 Bark、Pushover、Telegram Bot 等
curl "https://api.day.app/YOUR_KEY/Claude完成任务"
```

甚至，你可以串联多个 AI 任务。

A 任务完成后，自动触发 B 任务。

形成一个完整的 AI 工作流。

---

Claude Code 的 Hook 系统，本质上是把 AI 从一个**同步工具**变成了**异步服务**。

你不再需要守着它。

你只需要定义好"干完活要做什么"，然后放心去做别的。

这才是 AI 应该有的样子。

工具为人服务，而不是人为工具服务。

---

**以上，如果觉得有用，随手点个赞、在看、转发三连吧。我会持续更新 Claude Code 的使用技巧，我们下次再见。**
