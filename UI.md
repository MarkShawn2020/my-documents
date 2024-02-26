- #emoji #message
	- 类似github这样的表情就不错！ 
	  ![[Pasted image 20230820163621.png]]
	-
- #github #dashboard #profile-page #awesome
	- ![[Pasted image 20230814140839.png]]
- #screen
	- 最小 375
	- ![[Pasted image 20230813142145.png]]
- #chat #detail
	- ![[Pasted image 20230811203105.png]]
	- ![[Pasted image 20230811203128.png]]
	- ![[Pasted image 20230811203135.png]]
	- ![[Pasted image 20230811203141.png]]
	- ![[Pasted image 20230811203149.png]]
- #chat
	- ![[Pasted image 20230811202158.png]]
	  #awesome ref: https://dribbble.com/shots/21173383-Eternal-AI-Chat 
	  #idea 可以搞一个树洞/黑洞一样的背景
	- ![[Pasted image 20230811180633.png]] ref: https://dribbble.com/shots/21097468-Web-Chat-UI #awesome
	- ![[Pasted image 20230811181104.png]]
	  ref: https://dribbble.com/shots/21183813-AI-Conversational-Chatbot-App #awesome
		- ![[Pasted image 20230811181354.png]]
		  ref :https://dribbble.com/shots/20909323-ChatGPT-AI-Concept-Redesign
	- ![[Pasted image 20230811181710.png]]
	  ref: https://dribbble.com/shots/20928432-Brainwave-AI-UI-Kit
- #responsive #breakpoints
	- 总结
		- [微软](https://learn.microsoft.com/en-us/windows/apps/design/layout/screen-sizes-and-breakpoints-for-responsive-design)是 640 / 1007 / -，
		- [tailwind](https://tailwindcss.com/docs/screens) 默认是 640, 768, 1024, 1280, 1536
		- 但我作为个人全站开发工程师，其实不太喜欢 tailwind 这种，因为中间感觉有点密集了，太细了，会导致个人的前端工作量增高
		- 我觉得微软的就很好，不过就按照 tailwind 的来吧，648 之后直接 flex / grid 搞定
	- ![[Pasted image 20230811110419.png]]
	- ![[Pasted image 20230811110514.png]]
	- ![[Pasted image 20230811110439.png]]
	- https://www.freecodecamp.org/news/css-media-queries-breakpoints-media-types-standard-resolutions-and-more/
	- ![[Pasted image 20230811110448.png]]
	- ![[Pasted image 20230811110507.png]]
- #devices #mock
	- https://codesandbox.io/s/react-phone-mockup-slider-wsdy5?file=/src/index.js:275-286
	- https://github.com/picturepan2/devices.css
	- https://devicescss.xyz/
	  ![[Pasted image 20230811085459.png]]
- #font #未来荧黑
	- [未来荧黑](https://www.100font.com/thread-145.htm) (感谢@lara) 确实不错，而且按样式和粗细分的很专业，尽管和 `tailwindcss` 的分类有点出入，其对照如下：
	  ```typescript
	  export const FontWeightGlowSansSC = [  
	  'Thin', 'ExtraLight', 'Light',  
	  'Regular', 'Book', 'Medium',  
	  'Bold', 'ExtraBold', 'Heavy',  
	  ]  
	  export const FontWeightTailwind = [  
	  'thin', 'extralight', 'light',  
	  'normal', 'medium', 'semibold',  
	  'bold', 'extrabold', 'black',  
	  ]```
	- 考虑到字体很大（每个十兆，有每种样式9个，共有5种），因此我们要做一些筛选：
		- 简单测试对比了 `Normal` 和 `Wide` 两个样式，个人觉得 `Normal` 就可以了，其他样式的字体要么太宽要么太紧，而且可以大致基于 `tracking-` 去调整字间距（尽管这里的样式调整的应该是字的内部宽度？）
		- 基于`Normal`，再同时对比了九种粗细的字体，结论是
		  	1. 不会改变英文的粗细
		  	2. normal = 400 较为中正，light = 300 较为精致，extralight = 200 精致到了孱弱，medium = 500 有点喧嚣
	- 因此，我感觉 normal + light 是最好的，然后只要导入 nomral + [300-500] （算了，还是把 normal 都导入吧，指不定哪里会冒出需要调整粗细的特殊 case 。。）感觉就足够了，这样也不大
	- 以下是对比图：https://arc.net/e/2F2F222E-12CE-469A-9C70-B376B0F82BEF
	    ![[Pasted image 20230810210632.png]]
- #排序
	- 学习  [postman](https://www.postman.com/explore/collections) 将排序放到了右边
	- ![[Pasted image 20230810183659.png]]
	- ![[Pasted image 20230810183610.png]]
	- ![[Pasted image 20230810183746.png]]
- #radix-ui #shadcn-ui #TODO
	- 为什么 `shadcn-ui` 里的 `select` `navigation-menu` 等加了 `transition-all` 之后会闪屏，但是 `radix-ui` 里的官方 demo 却不会
- #sidebar
	- 感觉还是有点中二。。。以及不够直接明了（干扰太多）
	- ![[Pasted image 20230810135438.png]]
	-
- #icon #radix-ui #tabler
	- radix-ui 的 icon 要比 tabler 更精致一些，二者都可以根据字体颜色变化，但是不可以变化大小，需要通过 className 去调
	- ![[Pasted image 20230810125004.png]]
	-
- #flowgpt
	- #charge #account
	- ![image.png](image_1691335343172_0.png)
	-
- #stripe #plugin
	- ![image.png](image_1691267598748_0.png)
	-
- #TODO #github #card
  card-last-interval:: -1
  card-repeats:: 1
  card-ease-factor:: 2.5
  card-next-schedule:: 2023-08-24T16:00:00.000Z
  card-last-reviewed:: 2023-08-24T08:11:31.174Z
  card-last-score:: 1
	- card ui 真地直接抄 github 的就可以了啊
	- ![image.png](image_1691246322120_0.png)
	-
- #TODO #popover #shadcn
	- 预期：从元素本身缓慢弹出来
	- 实际：从顶部飞下来
	- 可能解决方案：https://www.radix-ui.com/docs/primitives/components/popover#origin-aware-animations
- #wechaty #contributor #backer
	- ref: Wechaty - Open Collective, https://opencollective.com/wechaty#backers
	- ![image.png](image_1691208728197_0.png)
	-
- #logseq #plugin #TODO #sidebar
	- ![image.png](image_1691207177404_0.png)
- #obsidian #settings
	- ![image.png](image_1691207211856_0.png)
	-
	-
- #todo #react 这个examples区域很不错
	- ![image.png](image_1690996403815_0.png)
	-
- #midjourney #workspace
	- ![image.png](image_1690867347659_0.png)
	-
- #bricks.js #masonry
	- ![image.png](../assets/image_1690744944916_0.png)
	- ![image.png](../assets/image_1690744961516_0.png)
	- http://callmecavs.com/bricks.js/
	- https://github.com/callmecavs/bricks.js
- #carousal
	- flowgpt 没有 carousal，强调用户输入： ![image.png](image_1690712316730_0.png)
	- 无界AI的carousal 太野蛮了： ![image.png](image_1690712231421_0.png)
	- 直接加入瀑布流比较小气： ![image.png](image_1690712139156_0.png)
	- B站的carousal比较小： ![image.png](image_1690712149206_0.png)
	-
- #finished #emergent 手机版navbar
- #anthropic logo会变，挺有意思的： https://www.anthropic.com/index/introducing-claude
- #AIGC便利店 #cover
	- 还不错， https://aigclist.com/
	- ![image.png](image_1690665839916_0.png)
	-