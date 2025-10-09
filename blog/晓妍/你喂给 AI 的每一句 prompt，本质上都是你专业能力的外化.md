

今天和好朋友晓妍约了一杯咖啡，感觉很有收获与共鸣，以下是一些 key insights，希望对大家有所帮助。

**对话者：**

- **南川:** 独立开发者，building lovpen.me，公众号 **手工川**
- **晓妍:** AWS 初创生态，前头部 VC 投资人，公众号 **taste.ai**

---

## 99%的人没有这个意识

**晓妍：** 一个 AI 生成的应用，要上到真正生产，或者变成一个真正稳定可靠的产品，你觉得中间还需要跨越什么样的步骤和 gap？

**南川：** 我昨天看了一句话特别好：“**你喂给 AI 的每一句 prompt，本质上都是你专业能力的外化**”。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/4191a82e37ef4dd61db9eca3d619f541.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以你说的这些东西不存在，你应该问我能不能商业化？我能不能做出一个万级、10 万级、100 万级（用户）的产品？因为 AI 是工具，是手段。

我给你举个最简单的例子。现在 AI 给你出了一个网页，但网页里面的内容，比如用户评价，都是 AI 自己写的。但真正的用户评价显然都在数据库里面，可能是几千条、上万条。你现在 AI 生成的产品，是直接在前端去渲染的，前端哪来的数据？是你自己造的数据。如果你的终点其实是从数据库里来的，那你为什么不第一天就从数据库里面拿呢？

所以在我的理解层面，是我先给 AI 一个模板，这个模板已经自带了数据获取的功能，我们会把数据库（的连接）获取过来。然后你用 AI coding，你不需要再一遍遍地造轮子了。你在这个轮子基础上，AI coding 的是两部分：第一，后端数据，你可以联合 AI 去操作数据库的读写。第二，前端这个内容的替换、渲染、展示。

这样的话，你这个代码是直接 production-level ready 的，生产级可用的。后面你要改的话就直接改数据库就行。那这个代码你发现它就不是个玩具（toy）了，鲁棒性特别强。

而这一点，其实我觉得 99%的人没有这个意识的。至少他们在用 Vibe Coding 的时候，暂时没有这个意识。

最近我看到一家公司挺有意思的，叫“迈氪锶”，他们主攻 AI 后端，前端就一套中台模板，据说不少大客户都有和他们合作。

**晓妍：** 那他是怎么做到的呢？就是让 AI 去做这个后端。

**南川：** 因为这块他做了一个很大的建模，他的工作流每一步是涉及到表、库，是一个数据库驱动的工作流。你知道 Flowith 吗？它是一个画布，对吧？他那个也是画布，只不过是以数据库为准的。你的每个需求，他会去拆解这个需求需要配什么数据库、什么表，然后再看你的需求如何。就他的 prompt 在 agent 层面就已经框定了，你每一步的代码都是后端联动的。

**晓妍：** 后端其实情况太复杂了，你前端稍稍一改，后端得跟着改。他能做到这一点吗？

**南川：** 这个我先说企业级实践怎么做的。你知道 Prisma 吗？它是一个数据库的 ORM 公司。它核心是什么？核心是每一步约定你的数据库迁移需要改哪些东西，然后你直接就是 migrate, migrate, migrate，然后他会生成记录文件。所以一个合格的 AI 产品，它可能这个迁移文件里面可能有一百多个，记录了你每一次迁移的历史，就是数据库改动的历史。这是符合敏捷开发方式的。

传统的软件工程，你觉得数据库写死之后再去改是很麻烦的事情，对吧？不是的。现在整个硅谷是非常认可这一套更敏捷的环节。所以你每次改的时候，只需要知道 migrate 哪个东西、哪个表就行了。比如加一个字段，修改一个字段，或者删除一个表，这个增量内容是很少的。所以你看，对AI来说，既然改前端不是很有压力，那在软件工程的指引下，改个后端也必然不会很有问题。

---

## 我真的不太在乎 Vibe Coding

**南川：** **我们应该区分一个需求什么环节更适合让 AI 去做，什么环节更适合自己去做，什么环节更适合让 AI 写个程序去做。**

比如说，一个文件 10 万行，然后把里面每一个叫“南川”的名字改成“晓妍”，就这么简单一个事。你看大模型去做这个事情，你不是累死他吗？他得把这个（上下文）窗口全投进去。

（更好的方式是）你让他去写一个程序，给定一个文件，然后输入是“南川”，输出是“晓妍”，然后全局替换。写这个程序可能只要一百行，对吧？然后啪写完之后执行一下这个程序，准确无误。这种场景就应该适合让程序去做。

还有一个场景是变量重命名。你可能有 100 个文件，变量重命名是要跨文件去改的，这种也有很多 IDE 的工具，它能够全局批量地解决很多问题。所以如果你综合掌握什么时候用 AI coding，什么时候用手动，什么时候用程序化工具，它的能力只会比你强，而不会比你弱。

你看，下限一定超过我自己去写代码，然后上线又是对齐人类标准的，那就完全取决于我能不能做出产品。

**晓妍：** 对，大多数人现在用 Vibe Coding 就只能出一个 toy，一个玩具，一个 MVP。

**南川：** 对，他们没有软件工程（的思维）。

**晓妍：** 所以把软件工程的这个最佳实践和这个 AI 的 coding 的能力结合到一起，其实可以让他非常听话地去执行，而且做出来东西真的是（生产级的）。

**南川：** 而且有些场合确实比人效率更高。比如说我昨天在魔改 Dify 的过程中，突然发现网页上有块组件不见了。我们都知道，找 bug 是很恶心的，一般是打 log 对吧？然后我让他干嘛？我说，我正好有原仓库，我也有改过的仓库，你对比一下这两个仓库，我碰到什么问题，你给我找出什么原因。然后他啪，从前端找到后端，最后找出来了。

啪一改就好了。因为他的 diff 能力比我们人类强太多了。你说我们人同时打开两个文件去对比，这个事情就很恶心。程序员会用 vimdiff，但普通人怎么做？我打开两个文件还得一行行比对，woc，这个事情就非常不想做了。

所以你会发现，能够精准识别哪些场景是 AI 更有效的，哪些是人更有效的，这需要经验。**再往上则取决于你的认知、你的审美、你的品味**，最后是这块东西。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/889fd618ae4c5dcc41fbbb3674eac195.jpg?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)

所以你问我 Vibe Coding 对于我到底是什么？说实话，**我真的不太在乎 Vibe Coding**。我真正在乎的是，**能不能把 Vibe Coding 和企业级的这种开发工作流组合在一起**。你会发现最后可能不仅是 Vibe Coding 不行，软件工程这门年轻的学科可能也不 ready，**Vibe Coding 也在推着软件工程往前发展**。

---

## Vibe Coding 有点像航天工程

**晓妍：** 我原来是我的教育背景是学技术的，之前是在北邮读电子工程系本科，然后在清华读电子工程系的硕士。毕业之后我去了那个航天五院，当时做的是跟卫星相关的研发。

**南川：** 有想法的是不是一般都在研究院待不了太久？

**晓妍：** 对，就好像觉得你没有什么创新的空间，\* 也很少。那个时候你想做点什么新东西，然后领导总是说你不要放新的东西上来。因为卫星主要是要保成功，如果你有任何一点意外，总是要担责的。他就会说这个东西我们已经几十年都这么做了，你就一定要按照这个做，你千万不要动。

我们在航天里面有个词叫“归零”，就是一旦它出现了差池，你们整个这条线就要归零。然后你们要从头去检查到底是哪儿造成了这个差池和波动，然后你要定位到那个点，在那个点以后重新设置一个新的检查点或者一套新的规范。所以我们内部其实有特别多的文档，都是一些什么操作规范文档、测试文档、检查文档、流程文档、工艺文档，就是要保证每一个点都是被检测的，且不会发生变化的。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/a180e72fd3a1ac6a890620f98dc2d811.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)



**南川：** 说实话这个东西跟 Vibe Coding 还有点像是，它是 bug 驱动的。我这个 Vibe Coding 出来网页哪一部分感觉不合预期，然后回去改那一部分。它是倒推的，完全不是按第一原理去做的。

**晓妍：** 对对对，是这个意思。

---

## 他要从底层解决问题

**晓妍：** 我前段时间刚跟威廉聊过，他现在在 XX（粤港澳某研究院）做一个叫 YY （AI专用编程语言）的东西。

他认为现在这些白热化的 AI 编程工具，都只是从模型上面加 tool，没有碰到最底层的东西。**他们重新写了一套编程语言，再基于这套语言去做上面的 Vibe Coding**。

他的意思就是说，他这样做的话可以全栈做优化。未来如果你真的想一句话就把软件产生出来，一定不只是上面的模型调度，一定是从底下的编程语言、工具链、代码组织形式去做优化。

他说模型有时候会傻，解决不了的问题，他们甚至于可以直接从编程语言那个层面去做一些改动，让这个编程语言跟模型能配合得更好。他要从这种方式去解决问题，这样他们就是通透了，这叫全栈了，从底层解决问题。

**南川：** 听起来是个伟大的愿景！不过从我目前的角度来看，我只要能够把常见的开发方式封装一下就行了。比如一个需求进来，我能够自动拆解成几个原子组分，有涉及到后端、前端、测试，就是 MVC。你每一个需求变成一个 MVC，每一个需求都是可调试、可验证的一个最佳实践。我觉得这样也可以，而且扩展空间也很好。

**晓妍：** 但我也感觉也挺恐惧的。你看他们这种 general agent 已经能力这么强了，比如 Manus 的 Wide Research。

【manus：wide research】

<section class="custom_select_card_wrp channels_iframe_wrp" nodeleaf=""><mp-common-videosnap class="js_uneditable custom_select_card channels_iframe videosnap_video_iframe mp_common_widget" data-pluginname="mpvideosnap" data-url="https://findermp.video.qq.com/251/20304/stodownload?encfilekey=rjD5jyTuFrIpZ2ibE8T7Ym3K77SEULgkiaD2RibiaqjEC4yPxIIzzZaneEmDOshqzOHkOa0duL934R1eq5rYFhibZ3KJtthh72Oob6pO0ibvvEpbDZjgajdsgtvg&amp;token=ic1n0xDG6aw9ICadnOC7gHLGKnaPqWRIDEHvh91p8k28LQN6uapOtXV3C6dHgmSHpPedxWQJgTl5esjtW0eSUfyIcgic38jfPIbcy9ODmVuQGG8cNy52C5dlbmTT16WXqpyliaPfzxwZhcMfticIUzF1NEsLBMJTibuzWPCyLgxkc8jg&amp;idx=1&amp;hy=SZ&amp;m=&amp;scene=2&amp;uzid=1" data-headimgurl="http://wx.qlogo.cn/finderhead/VzQsdzsGScNLYwDrRL9n4Khfwkrxibib7icfLvjDZ9qWDcUHQiaDZpw8eq3rqYjfkHgTFmBZ5lHIph4/0" data-username="v2_060000231003b20faec8c6ea8b1ac5d4c703ed31b0770171679a58f29c151ede4104b620e970@finder" data-nickname="潜云思绪" data-desc="隆重介绍 Manus Wide Research，新的里程碑。" data-nonceid="15023890989797534029" data-width="1920" data-height="1080" data-type="video" data-id="export/UzFfAgtgekIEAQAAAAAAbDMx0_Nb4AAAAAstQy6ubaLX4KHWvLEZgBPEr6NsdjkVf_2PzNPgMIuHk8jTAaAezn7dhNWF6PMb" contenteditable="false" data-is-hover="1"></mp-common-videosnap><img class="ProseMirror-separator" alt=""><br class="ProseMirror-trailingBreak"></section>

那你想，这个 general agent 其实已经如此强大了，如果我们想做一个 vertical agent，怎么才能跟这种这么强大的 general agent 去打呢？我相信市场上百分之七八十的一些任务，其实他都可以完成。那你要做一个 vertical agent，你能做出什么东西来是它不能覆盖的呢？

**南川：** 如果是做 vertical agent，那肯定是 general agent 的一个子集能力。我们现在没在做 vertical agent，我们做的是 vertical product。Product 是 agent 加上工程，这个工程有很多场景才能弄好。

从长远来看，一个超级 general 的 agent 是有能力在每一项上都能做到一个人类的水准。但是技术只是一部分，还有商业。商业的话就会讲到谁做得快，谁做得好，谁能给客户提供情绪价值。这些东西通用 AI 目前还做不到。所以会有一个窗口期，在所谓的 AGI 真正到来之前，有一些场景值得让创业者去做深，来积累很多工程基础。

**晓妍：** 就相当于你其实在这个领域、这个烟囱里面，有暂时领先于它的势能。因为 general agent 在这个里面做得还不够深，然后你可以暂时利用这个势能去迭代，构建一些商业上的用户基础和壁垒。

---

## 颗粒度到顶了

**南川：** 我之前有一个 idea，一直想做的就是“原子化 Prompt”。你现在看到的做 prompt 的一些产品，他们是有一个地方有很多比较好的 prompt 集合，对不对？然后每个 prompt 巨长，少则一百行，长则一千行。

但问题是，很多时候我们其实只会去改一两行 prompt 来增强这个约束。所以你发现，你需要的不是一个大而全、一劳永逸的东西，而是一个很灵活的一套框架。在这框架上说，我们有多少条原则？其实你看，每一条原则就是一个 prompt。所以我一直比较喜欢的是原子化的这种设计。

这样的话，我们网站里面可能有 1000 条原则，然后 1000 条原则里面可能会组合成 100 种比较好的设计模式。

**晓妍：** 一旦它原子化了之后，它其实就足够灵活了。

**南川：** 对，它就更普适了。在目前我们前端的状态管理这个领域里面，以前有一个东西叫 Redux，非常的臃肿，很复杂。所以后来有一个人，他写了三套状态管理库，其中一个叫 Jotai，就是自下而上的，它是原子化的。每个 primitive 有一个原则。

你发现如果你每一句话的影响都这么大的时候，那你是不是该把这个 prompt 每一条，都把它当作一条“圣经”、“箴言”这种级别去管理？而不是一上来一坨一千个字你都看不下去的东西。

**晓妍：** 那你有想过把你这套原子化 prompt 的思想，把它做成一个产品吗？

**南川：** 最近有一个小项目也符合这个思想。大家会很多时候会写一些前端的模板，对吧？所有人做完模板之后，第一时间是干嘛？改 logo，改公司名称，改源码，对吧？其实有一个很好的方式，我为什么不能在前端直接改呢？

我直接在前端有个对话框，说“我这个不满意”，直接改这个界面，比如“这个名字改成那个”。他直接能够改网页的源代码。因为有一个东西叫 source map（源码映射），我们再结合框选技术，一旦框选它就知道是哪个元素，然后我们发到对话框里面，AI 就可以改那个源代码。你就直接在前端，就能把这个模板改成你想要的样子，不需要在后端去改。

AI native 的核心是，你的最底层的系统能够让 AI 去操作。就有点像威廉说的，我这个编程语言是 AI 可以去改的。

**晓妍：** 对，所以你的每一个原子化的组件，或者原子化的命令，它都是可以被 AI 操作去改的。那其实整个的这套系统就是非常可操作，它的控制力度就足够细。

**南川：** 这样它的这个颗粒度就百分之百了，到顶了，没法再顶了。因为我们把颗粒度先做到最细，做到百分之百，我们就可以向下兼容。

---

## 我希望给每个创作者配一个“AI 内容制作团队”

**晓妍：** 我其实也想做一个类似的东西，但可能更偏视频。我的产品思路就是说，怎么样让高质量、高制作成本的视频，把它的创意、内容创作和生产的环节加速，并且把门槛降低。

我想给每一个 creator 配一个 AI 内容制作团队。你从一个 idea 进来，我有一个 sub-agent 帮你去做 deep research，去做内容的延展和创新；然后有一个 agent 帮你把内容生成故事脚本；还有一个 sub-agent 帮你针对脚本切分镜；你拍完上传上来，有一个 sub-agent 帮你剪辑成片；再有一个帮你发不同平台；再有一个帮你回收数据，分析哪个视频反馈好，我们再依靠这个 pattern 去扩量。

**南川：** 你这个意思我大概理解了。这个事情对于我来说感觉更像是 workflow，是良好定义的一个工作流，每一步该做什么。

**晓妍：** 但这个未必就是把用户量局限住。因为你其实可以把你已经写死的 workflow 给那些完全没有这个 workflow 的小白用。但实际上，你这个上面可以定义很多 custom 的 agent，或者让博主自己构建 agent 的能力，让他自己去定义这个 workflow。

**南川：** 那就涉及到原子化的 agent 层。我们在里面定义了一套模板，就是“采访模板”，一个 workflow 有五个 step，这里面调用了多少 agent。然后你也可以基于我们的 agent，你自己去定义新的 workflow。这个产品就上去了，这个比剪映牛逼。

**晓妍：** 对对对！就相当于你是个小白，我让你在我这儿能够更快的去上手。但是我对于你上层的这些创作者，我其实给了你非常好的能力，去创建你自己的 agent，创建你自己想要的 workflow。

**南川：** **未来的 AI 产品是不是就可以所有产品都可以模块化，像乐高一样？**

**晓妍：** 对对对！

**南川：** 就是有一个 library，里面是所有的 agent 集合。比如这个 agent 是专门用于提炼字幕的，那个是专门做花样字幕的。然后上层有一个 template 层，这个模板定义了要调用哪几个 agent。然后最上层，如果你是特别懂行的，你可以自己去组合。这样，小白用户、专业生产者、还有开发者，这三层就全部有了。

**晓妍：** 对，这个是我很认可的，我其实就是想做你说的这种。**让创作者有自己的创作能力，且他还可以把自己的 template 或者自己的创作的东西变现。**

**南川：** 这个我投了:)

**晓妍**：谢谢，就是这样的一个东西，这是我想做的。

<section class="custom_select_card_wrp mp_profile_iframe_wrp" nodeleaf=""><mp-common-profile class="js_uneditable custom_select_card mp_profile_iframe" data-pluginname="mpprofile" data-nickname="手工川 - AI版" data-from="0" data-headimg="http://mmbiz.qpic.cn/sz_mmbiz_png/2niaYkVLHpnHrib4AVjPtsDtX5NBicQhzw8NI8V1bDIhJboJmQ64yiaPb9ianoORa4hhLQTWQJHBb0Os8ia7WyDSLn0w/0?wx_fmt=png" data-signature="南川，男，乙亥年生，南京市民。 幼守寒门，少年早慧。十八西征，志逾凌云。 独闯川藏，生死一念。穷游九州，人生何安。 三迁四徙，深居道口。醉文精码，踽踽独行。 逝者如斯，成败皆然。但求本真，亦正亦诞。" data-id="Mzg2OTg5NDg3Mg==" data-is_biz_ban="0" data-service_type="1" data-verify_status="1" data-is-hover="1"></mp-common-profile><br class="ProseMirror-trailingBreak"></section>


<section class="custom_select_card_wrp mp_profile_iframe_wrp" nodeleaf=""><mp-common-profile class="js_uneditable custom_select_card mp_profile_iframe" data-pluginname="mpprofile" data-nickname="Taste.ai" data-alias="xiaoyan_tech" data-from="0" data-headimg="http://mmbiz.qpic.cn/mmbiz_png/HWFJ23afNW2K0uggYWk9H4ISiaxbpnEaMWibpGDZ8In6woj7LmHyeDZZPl6Ogx3eL11PMdm1aIv3dxIxVJvqicuYw/0?wx_fmt=png" data-signature="AI builder的精神家园" data-id="MzI5OTQ1ODIzMQ==" data-is_biz_ban="0" data-service_type="1" data-verify_status="0" data-is-hover="1"></mp-common-profile><br class="ProseMirror-trailingBreak"></section>