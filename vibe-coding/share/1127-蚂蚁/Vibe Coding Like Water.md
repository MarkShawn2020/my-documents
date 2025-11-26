### 演讲主题
**主标题：** **Vibe Coding Like Water (像水一样 Vibe Coding)**
**副标题：** 在 AI 编程时代，如何构建“流动”的工程流与“有形”的上下文
**演讲者风格：** 哲学思考 + 硬核实战 (Handmade Chuan Style)

---

### 演讲结构大纲

#### 0. 开场：Be Water (引子)
*   **Hook：** 播放李小龙的经典片段 "Empty your mind, be formless, shapeless, like water."
*   **破题：** 2025 年的编程不再是“搬砖”（堆砌固定的砖块），而是“治水”（引导流动的算力）。
*   **现状：** 我们不再一行行写代码（Solid），我们在管理代码生成的流向（Liquid）。
*   **核心论点：** Vibe Coding 的最高境界，就是让 AI 像水一样流过你的需求，而你负责构建河道（Context & Constraints）。

---

#### 1. The Container: 容器决定形状 (Context Engineering)
> *"Water can flow or it can crash." 水能载舟，亦能覆舟。取决于你给它什么容器。*

*   **核心痛点：** 为什么 AI 会产生幻觉（Spill out）？因为你的容器（Context）漏了，或者形状不对。
*   **实战心法（源自 File 02 & Note）：**
    *   **收拢容器：** 介绍 **`code-inspector`** 和 **`.claude.md`**。不要把大海（整个 Repo）倒给 AI，要用精密管道（精准定位文件）喂给它。
    *   **清洗容器：** 强调 **`/compact`** 和 **`/clear`**。脏水（污染的上下文）生不出好鱼（好代码）。
    *   **案例：** 展示你如何通过“手动喂料”让 AI 解决那个卡了三天的 Bug，而不是让它自己瞎猜。

#### 2. The Flow: 顺势而为 (The Flow State & Agents)
> *"Water flows." 水往低处流，顺势而为。*

*   **CLI 即心流（源自 File 04）：**
    *   **观点：** 为什么选择 CLI (Claude Code) 而非 GUI？因为 CLI 是流动的，GUI 是阻断的。展示你在终端里“秒速进入心流”的状态。
    *   **读写分离：** 像水流一样，AI 负责在终端里“冲刷”出代码，你在 IDE 里负责“观测”河床的变化。
*   **Agent 协作流（源自 File 02 - SDD）：**
    *   **SDD (规范驱动开发)：** 水流需要引导。
    *   **演示：** **Requirement -> Design -> Plan -> Task** 的瀑布流。
    *   **Sub-Agent 策略：** 展示你如何用 `kiro-plan` Agent 生成 Task List，然后让 `executor` Agent 顺着列表像水流一样逐个击破任务。

#### 3. The Form: 随物赋形 (Persona & Prompt Strategy)
> *"You put water into a cup, it becomes the cup." 入杯即杯。*

*   **模型即容器（源自 File 05 - MBTI）：**
    *   **观点：** 不同的模型/人设是不同的容器。
    *   **实战：** 
        *   **"Linus Torvalds" 模式：** 当你需要极简、高效的代码时，注入 Linus 人设（KISS, YAGNI），AI 就会变得“冷峻、犀利”。
        *   **"Squad" 模式：** 组建你的 AI 小队。INTJ 负责架构，ESFP 负责文案。让水适应不同的形状。
*   **Prompt 位置学（源自 Note 11-23）：**
    *   **细节：** 强调 Prompt 的物理位置（一级位置 vs 二级位置）对 AI 行为的塑造作用。

#### 4. The Crash: 滴水穿石 (Model Strategy & Debugging)
> *"Water can crash." 水滴石穿，冲击障碍。*

*   **逆境应对（源自 Note 11-23）：**
    *   当水流被堵住（Bug 无法解决）时，不要死磕，要改变水的“压强”。
    *   **切换重炮：** 讲述 **Codex (GPT-5.1)** 掰回一局的故事。当 Claude (CC) 的柔性水流冲不开时，换用 Codex 的高压水枪。
*   **分流战术 (The Diff Strategy)：**
    *   **绝招：** 当旧河道（屎山代码）淤泥太深，AI 越改越错时，**开辟新河道**。
    *   **操作：** 在空 Repo 里让 AI 实现功能，然后对比差异（Diff）。这是“治水”的高级智慧——**改道分流**。

#### 5. 结语：Be the Riverbank (做河岸，不做水)
*   **总结：** 
    *   Token 成本会像自来水一样便宜（引用 File 04），算力会像洪水一样泛滥。
    *   **我们的角色：** 我们不再是产水的人，我们是修筑堤坝、规划河道（Context）、决定水流方向（Architecture）的人。
*   **L3 现实：** 目前我们还是 L3 级的领航员，必须时刻盯着水流，防止决堤（Review & Test）。
*   **Call to Action:** **"Empty your mind. Be formless. Vibe coding like water."**

---

### 视觉设计建议 (Visual Vibe)

*   **配色：** 使用 **深邃蓝 (Deep Blue)** + **黑客绿 (Terminal Green)** + **流体渐变**。
*   **PPT 元素：**
    *   **液体流动动画：** 背景使用极简的流体动画，暗示 Token 的生成。
    *   **对比图：** 左边是固态的 IDE 界面（Blocks），右边是流动的 CLI 终端（Stream）。
    *   **代码瀑布：** 展示 Log 或 Diff 时，使用黑客帝国式的代码瀑布效果。

### 核心金句 (Quotes for Slides)

1.  **"Don't code blocks, direct the flow."** (不要堆砌代码块，去引导流向。)
2.  **"Context is the cup. Without it, intelligence spills everywhere."** (上下文就是杯子。没有它，智能会洒得到处都是——即幻觉。)
3.  **"When the flow gets stuck, switch the pressure."** (当流不动时，切换压强——指切换模型。)
4.  **"The code is liquid; the architecture is solid."** (代码是液态的，架构是固态的。)
