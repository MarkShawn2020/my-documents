

> **MOSS：由马斯洛驱动的AI协作架构**

一套用于极端环境下人类与AI共生实验的系统化解决方案。该系统由独立开发者 markshawn2020 在一次行为实验中设计与构建，目标是探索 AI 在满足人类多层次需求中的角色与边界，最终形成一个具备可扩展性、可复用性、可观察性的完整AI生存系统。



![A0021AAF-9D49-4169-94BF-5DFD0EB6F9D9.PNG](https://poketto.oss-cn-hangzhou.aliyuncs.com/A0021AAF-9D49-4169-94BF-5DFD0EB6F9D9.PNG?x-oss-process=image/resize,w_400/quality,q_100#center)

 z

---

## 一、设计理念：以马斯洛需求为基础

基于马斯洛需求层次理论，MOSS 被划分为五个层级，每层通过AI模块来支持相应人类状态：

| 层级 | 模块代号 | 模块名称 | 功能 |
|------|-----------|-----------|------|
| 生理需求 | F | EatPlanner | 智能推荐食物与饮食结构（预算+情绪驱动） |
|          | B | EnvMonitor | 监控行为频率、情绪波动、环境状态 |
| 安全需求 | G | SurvivalManual | 各类状态对应的行为应对策略库 |
|          | C | AIPet | 情绪陪伴、语音交互、人格陪护AI |
| 社交需求 | A | NoteSystem | 私密+公开笔记系统，记录体验并可结构化输出 |
| 尊重需求 | E | TimeCapsule | 每日生成信件、贴纸等“意识胶囊” |
| 自我实现 | Z | ChallengeGenerator | AI生成创意挑战推动创作极限 |
| 总结模块 | H | SummaryOrchestrator | 汇总行为记录，输出PPT/图谱/语录 |

---

## 二、系统大脑：Orchestrator协调框架

MOSS 的核心为一个实时运行的 Orchestrator 系统，具备如下功能：

- **状态感知器**：持续读取情绪、行为频率、时间与环境光照
- **策略调度器**：根据状态与节奏触发对应AI模块操作
- **行为记录器**：记录模块运行情况与用户反馈形成行为图谱
- **输出引擎**：为总结模块H提供可视化数据与内容资产

模块间逻辑关系：
```
            [ Orchestrator ]
                  ↓
 ┌────────────┬─────────────┬─────────────┐
 │ EnvMonitor │  EatPlanner │  AIPet      │
 └────┬───────┴────┬────────┴────┬─────────┘
      ↓            ↓             ↓
  NoteSystem    TimeCapsule   ChallengeGenerator
       ↓             ↓               ↓
               SummaryOrchestrator
```

---

## 三、行为艺术框架 + 系统化开发

MOSS 不仅是一套AI生存系统，更是一种**可执行的行为剧本**，其中每个模块既是工具也是情境触发器。

- 每天由系统推送挑战、感知行为、记录反馈
- 每晚生成意识胶囊+AI日记总结
- 所有行为与系统交互自动写入系统日志，可用于后期传播/分析

---

## 四、使用说明（开发中）

```bash
# 克隆项目
https://github.com/markshawn2020/MOSS

# 安装依赖并启动系统
pnpm install
pnpm build
pnpm start
```

---

## 五、未来应用

- 数字庇护所 / 孤独陪护系统 / 空间站人机交互
- AI心理疗愈系统原型 / 高强度创作者自我调度引擎
- 可复用的 AI 自调度架构 SDK（开发中）

---

## 作者信息

项目作者：[AI手工川](https://github.com/markshawn2020)  
系统名：MOSS：Maslow-Orchestrated Survival System  
项目时间：2025年4月

---

> “MOSS：由马斯洛驱动的AI协作架构”

