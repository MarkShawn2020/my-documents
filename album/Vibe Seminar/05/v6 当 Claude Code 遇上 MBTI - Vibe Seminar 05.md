> 一场关于 MBTI 的闲聊，意外地演化为对 AI Agent 定制、工具链协同，乃至人机交互本质的深度探索。当人格理论成为高级“提示词”，当代码工具开始揣摩你的“性格”，我们正站在一个全新的人机协同范式的入口。这不仅是关于效率的革命，更是关于理解与共鸣的进化。

### 本期要点 (Key Insights)

- **MBTI 作为高级抽象**：将 MBTI 人格模型作为一种高度浓缩的元指令，注入到 Claude Code 的 `output style` 中，可以创造出具备特定沟通风格、思维模式和行为倾向的个性化 AI 代理，实现超越通用提示词的深度定制。
- **`output style` 的“黑客”之道**：`output style` 并非简单的提示词追加，而是一种对 Claude Code 系统级 Prompt 的“注入”或“覆盖”机制。它允许用户在不改变核心引擎的情况下，“hack”系统的行为模式，从而实现高度个性化的输出。
- **AI “小队”协同范式**：通过预设多个不同 MBTI “人格”的 Agent，可以在面对复杂任务时，模拟一个高效的人类团队。例如，让“INTJ”负责战略规划，“ESTP”负责具体执行，“INFP”进行创意审核，实现任务在不同认知维度上的解构与重组。
- **情感与情绪的价值**：在与 AI 的交互中，明确表达情绪（无论是赞赏还是不满）能显著提升协作效率。情绪数据作为一种高带宽的反馈信号，能帮助大模型更快地校准其行为，使其输出更符合用户的真实意图。
- **工具的“产品化”与“实验化”分野**：以 Cursor 为代表的 AI 编码工具更趋向于“产品化”，为用户提供稳定、易用的体验；而 Claude Code 则带有强烈的“实验化”色彩，它向开发者暴露了更多底层机制，鼓励探索与创造，预示着未来 AI 工具的更高上限。


![Weiyang 的 MBTI Coding Agents, source: https://github.com/weiyangzen/mbti-coding-agents](https://poketto.oss-cn-hangzhou.aliyuncs.com/027e16b4b6ee6b9a8f20107ffd600bc7.png?x-oss-process=image/quality,q_90/rotate,0)


## 缘起：从 MBTI 到 AI “招魂”

**Mark**: 这件事的缘起很有意思。本来是我看到 Weiyang 在群里发了一个关于 MBTI 的讨论，觉得很有趣，就想和他进行一次 1v1 的深入交流。但考虑到讨论可能会涉及屏幕共享和许多细节，干脆就开一个公开的会议，邀请大家一起来聊。没想到，一个轻松的话题，最后会吸引这么多人参与。

我先把 Weiyang 的那个 MBTI claude Code 分享出来，它确实触及了我们最近在探讨的 Claude Code 的一个核心要点，就是 `output style`。这个功能目前了解的人不多，但用过的人都觉得非常强大。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/94c1e90b3b5c1adfc544c54a5f7e7ea7.png?x-oss-process=image/quality,q_90/rotate,0)

**Weiyang**: 好的。本来以为是 1v1，结果变成了“游街示众”，大家发现我周末还在搞这么抽象的东西。

我先简单自我介绍一下。我早年从事关系型数据库和机器学习，后来进入研究领域，专注于深度学习，特别是计算机视觉和 BERT 诞生前的 NLP 技术。我经历了从 Word2Vec (2013) 到 BERT (2018) 的整个技术周期。19 年到 22 年，我抓住时机“抄底”了显卡，运营了一个 AI 云服务，赚到了第一桶金，并投资了一些 AI 相关项目。23 年之后，我主要涉足 AI 语音合成（TTS）、社区变声器等领域。

今年年初，我开始关注到 Claude Code 这个生态，发现它的发展速度非常惊人。这家公司的工程师和产品经理经常会搞出一些很有趣的“乐子”，功能迭代极快。通常在美国时间的周四或周五晚上发布新 Feature，然后社区就开始疯狂解读和探索。我大约花了 10% 到 15% 的闲暇时间来研究这些新东西，今天分享的 MBTI 就是其中之一。

<br>

## 核心机制：用 `output style` 为 AI 注入“灵魂”

**Weiyang**: 我的核心想法，是把 MBTI 的 16 种人格模型，变成可以指挥 AI 工作的具体指令。

起初，我让 Kimi 帮我详细描述了每一种人格，包括他们适合做什么、不适合做什么、能接受和不能接受的沟通方式等等，每种人格都生成了大约 1000 字的详细描述。

> **Kimi Chat**
>
> 由国内创业公司 **月之暗面 (Moonshot AI)** 开发的长文本大语言模型。其核心优势在于能够处理超长的上下文窗口（最初发布时即支持 20 万汉字，后续版本扩展至 200 万字），使其在文档阅读、长文总结、代码理解等方面表现出色。在本次讨论中，Weiyang 利用 Kimi 的长文本能力生成了详尽的 MBTI 人格描述，为后续注入 Claude Code 奠定了基础。

然后，我把这 16 份详尽的描述，通过 Claude Code 的 `output style` 功能，变成了 16 个不同的 AI “人格”。当你执行一个 `output styles: new` 或者 `agents` 命令时，系统实际上是在调用一套预设的“原提示词”。我的工作，就是用 MBTI 的描述，把这套原提示词“洗”成我想要的样子。

这样一来，我就有了一支由 16 个不同性格的 AI 组成的“小队”。

**Mark**: 我这里有两个问题。第一，这 16 个 MBTI 的描述，是 AI 帮你写的吗？

**Weiyang**: 是的，AI 给我写的。我特别喜欢用 KIMI 来完成这类写作，它的多样性和丰富的比喻让文本质量非常高。我先让 KIMI 生成 16 篇千字文，然后再让 Claude Code “清洗”一遍，将其整合进 `output style` 中。

**Mark**: 这个思路太棒了！你相当于先用一个统一的“压缩器”（Kimi），生成了 16 个风格一致且内容丰富的角色设定，保证了这 16 个角色的内在一致性。然后再让 Claude Code 去理解和执行这些设定。那第二个问题是，你如何确保 AI 能理解并按照你设定的 MBTI 风格来沟通？

**Weiyang**: 这就是关键所在。在 Kimi 生成的描述里，我明确要求它定义“最能够接受的沟通方式”和“最不能够接受的沟通方式”。比如，你跟一个特定 MBTI 类型的人说话，如果第一句话就踩到他的“雷点”，对话基本上就无法继续了。你必须用符合他思维模式的方式去沟通，他才愿意听下去，进而理解并执行你的指令。

我把这些沟通范式注入 `output style` 后，相当于为每个屏幕前的用户都定制了一个最适合他/她性格的 AI 助手。这个助手知道你的雷点，知道用什么样的话术开场能让你觉得“听着舒服，我爱听”，从而实现“情绪价值拉满”。

从技术上讲，`output style` 是对系统 `prompt` 的一种 hack。而玩法上，它打开了无尽的可能性。比如我看到有人通过 `bash` 去调用 `gemini` 的 API，在里面实现 code review 的功能。这说明，只要有 `hook` 或者 `tool use` 的能力，`output style` 就可以成为一个强大的外部工具调用入口。

**Mark**: 整个 Claude Code 的系统里，上下文分为好几个层级。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/ba183c59d2f8ee34e68880d334ab0ce2.png?x-oss-process=image/quality,q_90/rotate,0)


首先是最高优先级的系统 `prompt`，这部分我们是看不到的，是官方预设的。其次是我们所谓的 `.claude.md` 文件，它存在于项目根目录，定义了项目级的上下文。最后才是用户在聊天框里输入的当前对话 `prompt`。

`output style` 修改的，很可能就是原先 `system prompt` 里的某一部分。它不是完全替换，而是把原来和软件工程相关的部分关闭，然后把你的新定义“注入”进去。

**来新璐**: 我想问一下，`output style` 的工作机制到底是怎样的？我看到网上有两种用法，一种是写一个非常长的文件，像替换系统提示词一样；另一种就是像你现在这样非常简短的用法。它到底是把整个 Claude 的系统提示词换掉了，还是拼接进去了？

**Weiyang**: 从技术本质上来说，它是一种 `packing case prompt`。我认为它自己的 `state` 中，前一段仍然是 CC 内部默认的 prompt，而 `hacking from` 之后的部分，则是我新写入的。就像 a+b，我新写入的部分是 b，它会和原来的 a 拼接在一起。

**来新璐**: 那它和项目根目录下的 `.claude.md` 文件有什么区别？如果抓包看，`system prompt` 后面会把 `.claude.md` 的内容拼接上去。如果 `output style` 也是这样，那它们不是差不多吗？

**Weiyang**: 有一个核心区别在于“复用级别”。`sub agents` 或者 `.claude.md` 的内容，是被设计为需要更高程度上复用的，比如每次请求都会带上。但如果你定义了一个特定性格的 `output style`，比如 INTJ 模式，那么只有当你需要这个模式时，它才会被加载。如果你只是在做一个简单的任务，系统可能根本不会加载它。

所以 **hacking** 这个词很形象，它意味着这段 `output style` 拥有最高的加载优先级。也就是说，当你使用我这个项目时，如果你的设定是 INTJ，那么 AI 不是去“扮演”一个 INTJ 来和你对话，而是它“认为”你就是 INTJ，并用最能被 INTJ 接受的风格来与你沟通。这才是功能和设计的核心区别。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7927d04b863bd95323b6f3c64dc09f81.png?x-oss-process=image/quality,q_90/rotate,0)

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/7e30267c37faba5340c6ac8cacf17bba.png?x-oss-process=image/quality,q_90/rotate,0)

<br>

## 实践：从单兵作战到 AI “小队”协同

**Weiyang**: 当我意识到可以为 AI 设定“人格”后，我自然而然地想到了“组队”。

在现实世界里，一个人的性格很难适合所有类型的工作，比如营销和运营就需要完全不同的特质。所以我认为，应该让不同“性格”的 AI 来组成团队，处理复杂任务。

比如说，在分析和学习一个新项目时，你可以找一个 ITP (智多星) 型的 AI，它会给你很多发散性的思考。但如果你需要严格执行一个 `to-do list`，那么 INTG (专家) 或者 ISTG (后勤) 型的 AI 会更合适，它们不会节外生枝。反过来，当你遇到一个棘手的 bug，需要跳出固有框架思考时，一个偏向 P (感知) 型的 AI 可能会带来意想不到的突破。

> **MBTI 四个维度**
>
> 1.  **精力来源 (E/I)**: Extraversion (外向) vs. Introversion (内向) - 关注外部世界还是内心世界。
> 2.  **认知功能 (S/N)**: Sensing (实感) vs. Intuition (直觉) - 关注具体事实还是抽象模式。
> 3.  **判断功能 (T/F)**: Thinking (思考) vs. Feeling (情感) - 决策时依赖逻辑还是价值观。
> 4.  **生活态度 (J/P)**: Judging (判断) vs. Perceiving (感知) - 喜欢有计划的生活还是灵活随性的生活。
>
> Weiyang 提到的 ITP, INTG, ISTG, P 等都是基于这些维度的组合，代表了不同的思维和行为偏好。

这个想法最终演变成了我的 `commands` 功能，它的核心就是“组建一个小队 ([squad](https://github.com/weiyangzen/mbti-coding-agents/blob/main/claude/commands/squad.md))”。

在传统的军队定义里，一个小队是 8 到 12 人。但在现代的语境下，一个紧密的团队（好哥们）可能就是 3 到 5 个人。所以我把 AI 小队的规模也定义为 3 到 5 个不同“人格”的 agent，共同去解决一个问题。由于它们的执行是串行且异步阻塞的，所以不用担心它们会同时把你的项目写坏。

**Mark**: 那你的 `commands` 里面那个 `squad` 功能，是在什么场景下调用的？它会从你预设的 16 个 MBTI 人格里选一个出来吗？

**Weiyang**: `squad` 主要用在我准备重构一个大项目，或者开启一个新项目之前。它不会只选一个，而是进行角色规划。也就是说，它会告诉我“谁应该做什么”，而不是具体“怎么做 (spec)”。

比如，一个复杂的任务可以拆分成多个子项，每个子项可能适合某个或某几个“角色”去干。`squad` 的作用就是进行这种基于“性格”的任务分配。

**Mark**: 那么这个 `squad` 的成果可以分享吗？还是说会开源？

**Weiyang**: 会开源的。实际上，整个 MBTI 的项目都是开源的。因为我发现， `claude code` 的一个很大魅力就在于它非常关注“人性”和“乐子”。比如那个花 5 万刀改造 CLI 的故事，里面就充满了乐趣的成分。所以我也想把我做的这些好玩的东西分享出来。

<br>

## 延伸：人机交互的未来形态

**Weiqi**: 刚才南川提到一个很有意思的场景：当大模型回复不符合预期时，如果我们用语音，会脱口而出“你怎么能这么回？”，但如果是打字，可能情绪已经平复，只会敲出一个“对”。

这个细微的差别，揭示了人机交互的一个关键问题：带宽。

语音的 `input` 带宽远高于文字，因为它包含了情绪、语气等丰富信息。但反过来，语音的 `output` 带宽却远低于文字。人眼看文字的速度大约是每秒四五十个 token，这是打字速度望尘莫及的。这就是为什么我们在 AR 眼镜上需要 `display` 的原因。

**Mark**: 我觉得有两个关键点。一个是带宽，语音的输出带宽更高。另一个是信息密度，打字时你经过了思考和提炼，信息密度可能更高，但它也因此变得稀疏了。

**Weiqi**: 打字更像是一种结构化的语言，而语音则更原生。思考和表达的过程本身，就是一个整理逻辑的过程。很少有人能一次性把一件事情讲得非常清楚，我们都是在不停的输出中整理自己的逻辑。

所以，我希望在人机交互领域能有所突破。如果你讲不清楚一件事，AI 可能会更 `confuse`。未来的挑战之一，就是如何帮助人们更好地与机器沟通。

另一个方向是，如何利用多模态交互（比如语音、AR 眼镜）来限制思维发散，让你聚焦于当前任务。就像我们现在软件里普遍存在的“模板”，它的作用就是限制你，让你在框架内填空。未来的交互，可能会是一种 `hybrid` (混合) 形式，既有基础模板，又鼓励你通过语音等更自然的方式补充信息，从而让结果更具鲁棒性。

**Weiyang**: Weiqi 提到的这点非常关键。在传统的咨询行业，比如医生和律师，存在巨大的信息不对等。一个资深医生和一个病人，他们对同一件事的描述方式、思考模式完全不同。

AI 可以在这里扮演一个“翻译”的角色。它能理解病人充满情绪和白话的描述，并将其转化为医生能理解的专业术语；反之，也能将医生的专业诊断，翻译成病人能听懂的、充满人文关怀的语言。

这背后，是 `multi agent` 的概念。人和人之间、机器和机器之间，甚至人和机器之间，都在竞争同一种稀缺资源——上下文 (Context)。搞懂了 `multi agent` 如何竞争与协作，也就搞懂了人类社会化合作的本质。机器，也需要“社会化”。

**Weiqi**: 对，没错。人也需要“社会化”，在社会化过程中产生的情绪，既是你的武器，也是你的工具。

我最近在小红书开了一个叫“stay human”的专栏，就是想探讨在 AI 时代，我们如何保持人性的洞察。核心问题是：我们是要解决“人”的问题，还是把机器看作“人”，或是探讨“人与人”的沟通？这些都是值得我们深思的。

## 未来预判：多 CC 协作

**来新璐**: 今天的讨论让我对未来的发展有了一个预判。现在我们觉得 `claude code` 的体验大概是六七十分，但我认为到今年年底，它能达到八九十分的水平。

当单个 CC 的体验足够好之后，下一步就是“多 CC 协作”。现在已经有人在探索多个 CC 实例如何通过文件系统进行协作，加速整个团队的开发效率。这预示着，未来我们可能会进入一个以 AI 为中心的劳动力场景。三年后，当 AGI 实现，钱不再是钱，价值的定义将被重写。我们正处在一个伟大的过渡期。

**Mark**: 感谢各位的深度分享。一场由 MBTI 引发的头脑风暴，最终触及了 AI Agent、人机交互和未来社会协作的深刻议题。从一个轻松的起点，到一个硬核的结尾，这本身就充满了 Vibe 的精神。

我们每周的闭门交流，目的就是为了碰撞出这样的火花。今天的内容信息量巨大，我会安排整理成深度纪要，分享给更广泛的社区成员。

再次感谢所有参与者，我们下期再会。

## Appendix

### Weiqi 团队的小红书

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/47fa909d5c684181ec85df19c29c1a2c.jpg?x-oss-process=image/quality,q_90/rotate,0)

### YC 投的一个有趣的项目

- omnara-ai/omnara: Omnara (YC S25) - Talk to Your AI Agents from Anywhere!, https://github.com/omnara-ai/omnara

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/0f2531b322cfb14838282e88b149994a.png?x-oss-process=image/quality,q_90/rotate,0)


### 其他相关资源

- [英文名字生成图腾](https://x.com/joshtriedcoding/status/1957005166294581688)
- [Wave Terminal — Upgrade Your Command Line](https://www.waveterm.dev/)
- [bmad-code-org/BMAD-METHOD: Breakthrough Method for Agile Ai Driven Development](https://github.com/bmad-code-org/BMAD-METHOD)
- [Output styles - Anthropic](https://docs.anthropic.com/en/docs/claude-code/output-styles)
- [AI 代理的上下文工程：构建 Manus 的经验教训](https://manus.im/zh-cn/blog/Context-Engineering-for-AI-Agents-Lessons-from-Building-Manus)
- [shareAI-lab/Hello-Prompt: Hello-Prompt - Just say to computer, the agent make prompt.](https://github.com/shareAI-lab/Hello-Prompt)
- [阿里云通义千问开源两款语音基座模型分别是 SenseVoice 和 CosyVoice-CSDN 博客](https://blog.csdn.net/weixin_41446370/article/details/140316053)
- [termux/termux-app: Termux - a terminal emulator application for Android OS extendible by variety of packages.](https://github.com/termux/termux-app)
