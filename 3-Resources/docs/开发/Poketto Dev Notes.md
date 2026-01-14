- #flowgpt
	- upload: aNB-zlvB30vEIS-yuX-5J: uploaded to flowgpt: https://flowgpt.com/p/your-sole-poketto
- #prisma #global-fields
	- impossible now
	- ![Pasted image 20230814231604](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814231604.png), ref: https://github.com/prisma/prisma/discussions/7233
- #prisma #多态 #polymorphic-types
	- ![Pasted image 20230814220241](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814220241.png) ref: https://github.com/prisma/prisma/issues/2505#issuecomment-706748316
- #log #best-practice
	- frameworks:
		- winston
		- pino (试试这个) 【Pino + Logflare】
		- ...
	- Node.js logging best practices: The essential guide - LogRocket Blog, https://blog.logrocket.com/node-js-logging-best-practices-essential-guide/
	- Recommended logging package or framework · vercel/next.js · Discussion #13214, https://github.com/vercel/next.js/discussions/13214
	- https://github.com/Logflare/next-pino-logflare-logging-example/blob/main/logger/logger.js
	- A Complete Guide to Pino Logging in Node.js | Better Stack Community, https://betterstack.com/community/guides/logging/how-to-install-setup-and-use-pino-to-log-node-js-applications/
- #next-auth
	- discord 支持多个 callback：
	  ![Pasted image 20230814152440](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814152440.png)
	- github 也支持多个 callback:
	  ![Pasted image 20230814153327](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814153327.png)
- #typescript #prisma
	- extend client: https://www.prisma.io/docs/concepts/components/prisma-client/client-extensions#type-of-an-extended-client
	- generated model type
		- ref: https://github.com/prisma/prisma/discussions/10928#discussioncomment-1920961
		- example: 
		  ```typescript
		  import { Prisma } from '.prisma/client'  
		  import UserGetPayload = Prisma.UserGetPayload
		  export type UserWithRelations = UserGetPayload<{ include: { followedBy: true } }>
		  ```
	- allow relation in needs: https://github.com/prisma/prisma/issues/20211
		- solution 1: wait to be supported
		- solution 2: manually write generated type hint like the above
- #invitation #sql #relationship #prisma
	- mysql - How can I model this relationship? - Database Administrators Stack Exchange, https://dba.stackexchange.com/questions/4418/how-can-i-model-this-relationship
	-
- #nodejs #openai-edge
	- upgrade nodejs on ubuntu (since the openai-edge needs nodejs >=18): https://askubuntu.com/a/480642
- #best-practice #rate-limit #openai #vercel #awesome #save-life
	- 请参考这篇，太棒了： https://github.com/vercel-labs/ai/blob/main/examples/next-openai-rate-limits/README.md
- #lang-chain
	- Usage with langchain's ConversationalRetrievalQAChain · Issue #246 · vercel-labs/ai, https://github.com/vercel-labs/ai/issues/246
- #CSS #marquee #跑马灯
	- 代码：
	  ![Pasted image 20230813022844](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230813022844.png)
	  ![Pasted image 20230813023015](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230813023015.png)
	- #best-practice Tailwind Play, https://play.tailwindcss.com/VJvK9YXBoB?layout=horizontal
	- ![Pasted image 20230813014311](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230813014311.png)
	- ![Pasted image 20230813014314](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230813014314.png)
	-
- #javascript #auto-resize-font
	- #awesome Make text fit its parent size using JavaScript - DEV Community, https://dev.to/jankapunkt/make-text-fit-it-s-parent-size-using-javascript-m40
- #trpc #conditional #skip
	- 不支持，所以在后端多写一点空校验函数吧：feat: type-safe way to skip/disable useQuery · Issue #4252 · trpc/trpc, https://github.com/trpc/trpc/issues/4252
- #json #comment #json5
	- #best-practice 直接在 IDE 里松弛一下 json 的 inspection 即可：https://stackoverflow.com/a/57364906 ，这样就支持在 json 里注释了：
	- ![Pasted image 20230812130223](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812130223.png)
- #todo #typescript #enum
	- 问题：enum 似乎不能像 interface 一样继承 或者 type 那样相等（似乎要分别对 type 和 value 做处理）
- #lets-encrypt #ssl #nginx
	- `sudo certbot certonly --agree-tos --email shawninjuly@gmail.com  --manual  --preferred-challenges=dns -d '*.cs-magic.com'  --server https://acme-v02.api.letsencrypt.org/directory`
	- `sudo certbot certonly --manual --preferred-challenges=dns --email 877210964@qq.com --server https://acme-v02.api.letsencrypt.org/directory -d cs-magic.cn -d '*.cs-magic.cn'`
	- ![Pasted image 20230812013914](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812013914.png)
	- ![Pasted image 20230812014204](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812014204.png)
	- 关于90天的探讨：How to extend the expiry date of domain certificate to one year - Feature Requests - Let's Encrypt Community Support, https://community.letsencrypt.org/t/how-to-extend-the-expiry-date-of-domain-certificate-to-one-year/67744
	- 自动刷新的机制：LetsEncrypt Certificates that Never Expire | by Joe Honton | Medium, https://joehonton.medium.com/letsencrypt-certificates-that-never-expire-e44c99dbd1cf
	- ![Pasted image 20230812014735](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812014735.png)
	- ![Pasted image 20230812015538](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812015538.png)
	- ![Pasted image 20230812015547](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812015547.png)
	-
- #godaddy
	- ![Pasted image 20230812011954](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812011954.png)
	-
- #dotenv #scrapy
	- `.env` 可以放在 `settigns.py` 的同级或者所有父级目录内，ref: https://stackoverflow.com/a/75435145
- #mongodb #search #partial #highlight
	- 这篇用于入门不错，讲了一点常识，以及高级功能需要基于 Atlas：Partial text search on Mongo - DEV Community, https://dev.to/sagnikbanerjeesb/partial-text-search-on-mongo-46j3
	- 这篇是 #reference: https://www.mongodb.com/docs/atlas/atlas-search/highlighting/
	- 这篇是 Atlas 官方教程：How to Run Partial Match Atlas Search Queries — MongoDB Atlas, https://www.mongodb.com/docs/atlas/atlas-search/tutorial/partial-match/
	- full text search Chinese 要用 `lucene.cjk` or `simple utf8 text`: https://www.mongodb.com/community/forums/t/full-text-search-for-chinese-text/7939
	- ![Pasted image 20230812003551](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812003551.png)
	- ![Pasted image 20230812003606](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812003606.png)
	- ![Pasted image 20230812003650](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230812003650.png)
	-
- #chat #open-source #选型
	- 本来想试试 `rocket.chat` 的，可惜它的 `Node` 竟然要强制版本 14…… 
	  ![Pasted image 20230811193720](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230811193720.png)
- #jetbrains #webstorm #index
	- ![Pasted image 20230811143606](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230811143606.png)
	-
- #nextjs #static-output #deploy
	- solution 1
		- 要修改 `next.config.js` 中 `output: "export"`，参考： https://nextjs.org/docs/pages/building-your-application/deploying/static-exports
		- 要修改 `next.config.js` 中 `assetPrefix: './'` ，如果涉及到 `fetch` 本地数据的话，参考： https://stackoverflow.com/a/54344495
		- 但是本地输出后，还是无法绕过 `file://` 的 schema 这一关
			- #todo 之后看看怎么解决  nextjs + static output + `file://` schema
	- solution 2
		- `sheetjs` load data: https://docs.sheetjs.com/docs/demos/static/nextjs/
		- 直接导入！ `import base64 from '@/data/sheetjs.xlsx';`
		- 是基于 `base64-loaded` 的，因此要 `yarn add base64-loader`，并且在 `next.config.js` 中配置 `webpack`: 
		  ```js
		  // next.config.js
		  
		  webpack: (config, context) => {
		  // ref: https://docs.sheetjs.com/docs/demos/static/nextjs/
		  /* add to the webpack config module.rules array */
		  config.module.rules.push({
		    /* `test` matches file extensions */
		    test: /\.(numbers|xls|xlsx|xlsb)/,
		    /* use the loader script */
		    use: [{ loader: "base64-loader" }],
		  });
		  return config;
		  },
		  ```
		- 这样，就可以在程序中导入并使用了！不过为了让编译器不爆红，可以再额外写一下声明文件：
		  ```ts
		  // src/global.d.ts
		  declare module "*.xlsx" {
		  export const content: string;
		  export default content;
		  }
		  ```
- #screenshot
  ![Pasted image 20230810125426](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230810125426.png)
- #lucide-react
	- ref: https://github.com/shadcn-ui/ui/issues/1132 要 `yarn add lucide-react@0.263.1`
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691513815823_0.png)
	-
- #astro
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691419127702_0.png){:height 477, :width 748}
		-
- #robot #hash #avatar
	- https://robohash.org/
- #resource #illustration #popsy.co
	- illustration: https://popsy.co/illustrations/
- #openai #chatgpt #nodejs
	- 官网有讲用法： https://github.com/openai/openai-node ， 其中还讲到了 `stream` 怎么写: https://github.com/openai/openai-node/issues/18#issuecomment-1369996933
	- 旋即发现，这里面
- #trpc #suspense
	- not supported yet: When will using <Suspense /> with Next.js be supported? · trpc/trpc · Discussion #1677, https://github.com/trpc/trpc/discussions/1677
- #trpc #nextjs #starter
	- ref: Setup tRPC Server and Client in Next.js 13 App Directory 2023, https://codevoweb.com/setup-trpc-server-and-client-in-nextjs-13-app-directory/
- #github #copilot #webstorm
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691365012056_0.png){:height 964, :width 748}
	-
- #webstorm #activation #version-mismatch
	- 果然，很多type hint 有问题，是因为 webstorm 的版本太低了，升级到 2023 后就没问题了（之前是2022.4）
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691361215212_0.png)
	- 不过有意思的是，这个之前在 2022 年破解成功的激活方式，在装完 2023.1 后，一点问题都没有，关键是还显示订阅截止日期是今年7月2号，而现在都已经8月7号了，2333（应该是破解脚本直接把关键通信机制给断掉了）
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691361126676_0.png)
	- 然后这里好像能用，看直到近日都陆续有人发可以用： Jetbrains IntelliJ Activation Code, https://gist.github.com/ihabhamad/3fc931475b1fcc4528ec43be6fae624e?permalink_comment_id=4434499
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691361692258_0.png)
	- 可能是，webstorm 被 vscode 打趴地不行，放松了打压破解的力度了吧。。。再打，估计没人再用 jetbrains 了。。。:)
	- ![Pasted image 20230814115354](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814115354.png)
	- ![Pasted image 20230814115400](https://poketto.oss-cn-hangzhou.aliyuncs.com/Pasted%20image%2020230814115400.png)
- #敏感词 #需求文档
	- ```typescript
	  // 我们需要一个敏感词判别函数，下面定义其输入输出数据结构
	  
	  interface ISensitivityInput {
	    content: string
	    meta?: {
	      userId？: sting // 后期要支持对用户进行微调，前期无所谓
	    }
	  }
	  
	  const GLOBAL_SENSITIVITY_LEVEL = 0.8 // 对任意用户来说，默认情况下，当判别超过 .8 时拒绝
	  interface ISensitivitiyOutput {
	    isSensitive: boolean // 前端根据这个判定是否敏感
	    meta?: {
	  	level?: number // 0 <= level <= 1
	    }
	  }
	  
	  // 下面是正常测例
	  const input: ISensitivityInput = {
	    content: "我今天很爱国",
	    meta: { userId: "markshawn" }
	  }
	  
	  const output = callSensitivity(input)
	  
	  assert(output === {
	    isSensitivity: false,
	    meta: { level: 0.01 }
	  })
	  
	  // 下面是危险测例
	  const input: ISensitivityInput = {
	    content: "伟大是不能被计划的",
	    meta: { userId: "markshawn" }
	  }
	  
	  const output = callSensitivity(input)
	  
	  assert(output === {
	    isSensitivity: true,
	    meta: { level: 0.82 }
	  })
	  
	  ```
- #aws #ses #best-practice
	- Sending email using Amazon SES - AWS SDK for JavaScript, https://docs.aws.amazon.com/sdk-for-javascript/v3/developer-guide/ses-examples-sending-email.html#ses-examples-sendmail
	-
- #stripe #pay
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691268706174_0.png){:height 619, :width 748}
	-
- #stripe #version-mismatch
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691265227600_0.png)
	- v11.18.0 不支持 paypal 应该，因为官网文档有了，但是包里没有
	- 果然，升级到 12 后就有了
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691265287699_0.png)
	- 不过paypal 是不支持的
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691265371483_0.png)
	-
- #借记卡 #CVC
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691264423801_0.png)
	- https://www.cbibank.com/wiki/cvc/
- #postgresql
	- install: https://www.digitalocean.com/community/tutorials/how-to-install-postgresql-on-ubuntu-20-04-quickstart
	- change-password: https://stackoverflow.com/a/12721095
- #postmark
	- #dns https://account.postmarkapp.com/signature_domains/2684838
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691250464905_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691250536837_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691250746923_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691250785175_0.png)
	-
- #github #auth
	- https://github.com/settings/applications ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691248879181_0.png)
	- 可以修改回调地址为本地：
	  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691254366715_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691254385222_0.png)
	-
	-
- #pnpm #mismatch
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691248502812_0.png) , ref: https://github.com/pnpm/pnpm/issues/6424#issuecomment-1515748464
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691248488671_0.png)
	- use `npm` first to upgrade `pnpm`: ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691248566631_0.png)
	- then finally use `pnpm` to install the whole project: ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691248593321_0.png)
	-
- #nextjs #documentation
	- ## Learn More
	  
	  To learn more about Next.js, take a look at the following resources:
	- [Next.js Documentation](https://nextjs.org/docs) - learn about Next.js features and API.
	- [Learn Next.js](https://nextjs.org/learn) - an interactive Next.js tutorial.
	  
	  You can check out [the Next.js GitHub repository](https://github.com/vercel/next.js/) - your feedback and contributions
	  are welcome!
	- ## Deploy on Vercel
	  
	  The easiest way to deploy your Next.js app is to use
	  the [Vercel Platform](https://vercel.com/new?utm_medium=default-template&filter=next.js&utm_source=create-next-app&utm_campaign=create-next-app-readme)
	  from the creators of Next.js.
	  
	  Check out our [Next.js deployment documentation](https://nextjs.org/docs/deployment) for more details.
- #react-map-gl
	- onMouseDown / onMouseUp 无法触发 easeTo 效果， onMouseEnter / onClick 才行
- #react-map-gl #hover
	- 厉害了，原来人家的 hover 是基于鼠标坐标位置（`point:{x, y}`），而非实际hover……，这样就可以避免产生遮挡（以及后续的闪烁）问题了, ref: react-map-gl/examples/geojson/src/app.tsx at 7.1-release · visgl/react-map-gl, https://github.com/visgl/react-map-gl/blob/7.1-release/examples/geojson/src/app.tsx
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691149764535_0.png)
	-
- #zustand #best-practice
	- slice-pattern + typescript: https://github.com/pmndrs/zustand/issues/508#issuecomment-955722581
	- slice-pattern + immer + typescript: https://github.com/pmndrs/zustand/discussions/1796#discussioncomment-5826280
	- best practice #zustand #typescript #slice-pattern  #middlewares #immer #persist #devtool
	  ```typescript
	  // in slice
	  
	  export type FirstSlice = {}
	  
	  export const createFirstSlice: StoreSlice<FirstSlice> = (set, get) => ({})
	  
	  // 原生支持
	  setValueColIndex: (valueColIndex) => set((state) => ({ ...state, valueColIndex })), 
	  
	  // 需要启用 immer middleware
	  setValueColIndex: (v) => set((state) => {state.valueColIndex = v}), 
	  
	  // 语句级别 immer，但是会失去 ts hint （或者在其他地方搞个声明，但还不知道在哪搞）
	  setValueColIndex: (v) => set(immer.produce((state) => {state.valueColIndex = v})),
	  ```
	  ```typescript
	  // in store
	  
	  import { create, StateCreator } from 'zustand'
	  import { createInputSlice_Immer, InputSlice } from '@/store/slice/input'
	  import { createVisualizationSlice_Immer, VisualizationSlice } from '@/store/slice/visualization'
	  import { devtools, persist } from 'zustand/middleware'
	  import { immer } from 'zustand/middleware/immer'
	  
	  export type StoreState = InputSlice & VisualizationSlice
	  
	  export type StoreSlice<T> = StateCreator<StoreState,
	  	[
	  		['zustand/devtools', never],
	  		['zustand/persist', unknown], // ref: https://github.com/pmndrs/zustand/blob/main/docs/guides/typescript.md#middlewares-and-their-mutators-reference
	  		['zustand/immer', never],
	  	],
	  	[],
	  	T>
	  
	  export const useStore = create<StoreState>()(
	  	devtools(
	  		persist(
	  			immer(
	  				(...a) => ({
	  					...createInputSlice_Immer(...a),
	  					...createVisualizationSlice_Immer(...a),
	  				}),
	  			), { name: 'zustand' },
	  		),
	  	),
	  )
	  ```
	-
	-
- #nextjs #typescript
	- #todo open `ignoreBuildErrors: true,`
- #zustand
	- #persistence
		- ref: 我感觉 mount 是最佳实践： `persist` middleware `Content Mismatch` error with Next.js · Issue #510 · pmndrs/zustand, https://github.com/pmndrs/zustand/issues/510
	- #merge-router #todo
- #cluster #filter
	- 去除了筛选功能，因为觉得分组后，只是为了筛地图上的 marker 没有太大意义，真正牛逼的应该是可以根据 cluster 的值去筛，或者本质上，cluster就不适合筛选，散点图才适合
- #sheetjs #xlsx #excel
	- read data by column, ref: #1729 - Can we read data Column Wise in XLSX File using SheetJs? - sheetjs - SheetJS, https://git.sheetjs.com/sheetjs/sheetjs/issues/1729
- #jina.ai #极纳科技
	- #ui #logout
		- ``![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691070297820_0.png)
	-
- #auth #wechat
	- https://open.weixin.qq.com/connect/qrconnect?appid=wx22b81214a7e515ca&redirect_uri=https://api.hubble.jina.ai/v2/oidc/idpAuthorized&response_type=code&scope=snsapi_login&state=a53850c66d695d704f8b42cfb140af91&lang=cn#wechat_redirect
	  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1691069670716_0.png)
	-
- #use-supercluster  #use-deep-compare-effect
	- 由于 use-suupercluster 底层用了 use-deep-compare-effect，所以当接收了一个匿名函数作为关键字时，会导致无限触发
		- 尝试解决方案
			- 使用 已经命名的外部函数
- #react #useCallback #useRef
	- useCallback Might Be What You Meant By useRef & useEffect | by Vitali Zaidman | Welldone Software | Medium, https://medium.com/welldone-software/usecallback-might-be-what-you-meant-by-useref-useeffect-773bc0278ae
- #mapbox
	- `mapboxAccessToken` 而非 `mapboxApiAccessToken` !
	- marker漂移研究
		- 首先坐标其实没有漂移
			- {
			      "id": 382,
			      "pos": "[115.04745483398438,34.72016869311106]"
			  }
			- {
			      "id": 382,
			      "pos": "[115.04745483398438,34.72016869311106]"
			  }
		- 最后搜索知道原来是需要加 css …… (万恶的CSS！)
			- ```
			  import 'mapbox-gl/dist/mapbox-gl.css';
			  ```
			  https://stackoverflow.com/a/68109348
- #mapbox
	- projection
		- 给 elle 姐（正常人）看，最好应该是 conic (`albers`) 把
		- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690947511097_0.png)
		-
- #ella #map-visualization
	- config
		- mapbox
			- token: https://account.mapbox.com/
			- style: https://studio.mapbox.com/styles/markshawn2020/clks332uh00bg01o867252fve/
	- codes
		- add control: https://visgl.github.io/react-map-gl/docs/api-reference/use-control
	- ref
		- 教程: Next.js 13, Mapbox, Deck.gl Hexagon Layer step by step. | by PiotrDev |
		  Medium, https://medium.com/@pether.maciejewski/next-js-13-mapbox-deck-gl-hexagon-layer-step-by-step-5528e7366750
		- 选型
			- Top 5 Map Libraries for React in 2021 | Bits and
			  Pieces, https://blog.bitsrc.io/top-5-map-libraries-for-react-in-2021-20a37ff5234
			- 15 Best React Chart Libraries in 2023 | Technostacks, https://technostacks.com/blog/react-chart-libraries/
			- SimpleLineChart | Recharts, https://recharts.org/en-US/examples
			- ECharts for React - 全网开发者下载量最高的 ECharts 的 React 组件封装, https://git.hust.cc/echarts-for-react/
			- javascript - 关于echarts显示中国部分省份地图 - SegmentFault 思否, https://segmentfault.com/q/1010000015716477
			- 静态地图-API文档-开发指南-Web服务 API|高德地图API, https://lbs.amap.com/api/webservice/guide/api/staticmaps
			- Examples - Apache ECharts, https://echarts.apache.org/examples/en/index.html
			- desk.gl 案例
				- (28 封私信 / 86 条消息) 如何将特定数据与中国地图结合起来？ -
				  知乎,  https://www.zhihu.com/question/367046094/answer/1030393040
- #cluster #supercluster
	- 在这里讨论 mapbox-gl 不支持基于函数聚合分组数据，Support property aggregation on clustered features · Issue #2412 · mapbox/mapbox-gl-js, https://github.com/mapbox/mapbox-gl-js/issues/2412 ，然后其中有一个post了基于supercluster实现的案例： Mapbox GL JS - Cluster Property Aggregation with Supercluster, https://gist.github.com/ryanbaumann/01b2c7fc0ddb7b27f6a72217bd1461ad
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690922338817_0.png)
	
- #vis.gl
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690915246327_0.png)
	
- #deck.gl #hexagon-layer
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690914401617_0.png)
	  原来是按照数量来的
	
- #webstorm #javascript #zen-html `col` 不要补全成 `<col>`
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690911611899_0.png)

- #mustache #模板字符串
	- Minimal templating with {{mustaches}} in JavaScript: https://github.com/janl/mustache.js/
- #SVG
	- SVGR Playground - SVGR, https://react-svgr.com/playground/?jsxRuntime=automatic&svgProps=color&typescript=true
	- #best-practice #SVGR
		- https://frontend-digest.com/how-to-import-svgs-into-nextjs-8ec6100e613f
		- https://react-svgr.com/docs/next/
		- 支持直接导入 SVG，然后改颜色、大小 ！
	- #failed
		- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690778730351_0.png)
		- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690778718110_0.png)
	
- #framer-motion #useTransform
	- 参考： https://codesandbox.io/s/framer-motion-usetransform-w-multiple-values-forked-r3zcrn?file=/src/App.js:811-823
- #translate3d
	- 之后：
	  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690758668424_0.png)
	- 之前：
	  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690758693009_0.png)
	
- #TODO #padlocal #wechaty
	- 让俐慧再搞个七天的账号 http://pad-local.com/#/
- #TODO #nextjs #font
	- 研究如何避免硬编码地导入 font
- #摩斯电码
	- http://www.zhongguosou.com/zonghe/moersicodeconverter.aspx
- #tailwindcss #TODO #UI
	- 可以加一个 new
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690650058521_0.png)
	- 这个底栏更好
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690650095534_0.png)
	
- #character.ai #todo #UI
	- 感觉不错啊，比flowgpt要简洁很多
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690649849556_0.png)
	
- #postgresql #intro
	- install and start:
		- commands:
		  ```shell
		  sudo apt update
		  sudo apt upgrade
		  sudo apt install postgresql postgresql-contrib
		  sudo systemctl start postgresql.service
		  ```
		- ref: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-postgresql-on-ubuntu-20-04
	- change password (if necessary)
		- in ubuntu shell:
		  ```shell
		  sudo -u postgres psql
		  ```
		  then in postgresql terminal:
		   ```postgresql
		  ALTER USER postgres PASSWORD 'myPassword';
		  ```
		-
		- ref: https://chartio.com/resources/tutorials/how-to-set-the-default-user-password-in-postgresql/
		-
- #prisma #api
	- 可以看很多CRUD都已经直接生成了，Prisma Client API (Reference), https://www.prisma.io/docs/reference/api-reference/prisma-client-reference#findfirst
- #prisma #webstorm
	- 竟然正好不支持我的，我的是 2022.2，prisma 的 plugin 最低要求是 2022.3
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690633258625_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690633249555_0.png)
	-
- #auth #jwt #jsonwebtoken
	- Error: secretOrPrivateKey must be an asymmetric key when using ES256 · Issue #898 · auth0/node-jsonwebtoken, https://github.com/auth0/node-jsonwebtoken/issues/898
	-
- #bug #fixed #jsonwebtoken
	- 从 V9 开始，rsa 秘钥至少要 2048位
		- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690620813895_0.png)
		-
- #nextjs #best-practice
	- custom app props
		- not ok: ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690617378900_0.png)
		- ok: ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690617399695_0.png)
		-
- #bug #alfred #fixed
	- 'auto paste on return' not work
	-
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690609032694_0.png)
	- Clipboard: 'Auto paste on return' stopped working - Discussion & Help - Alfred App Community Forum, https://www.alfredforum.com/topic/10481-clipboard-auto-paste-on-return-stopped-working/
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690609069590_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690610104394_0.png)
	-
- #选型 #chat #TODO
	- https://freefrontend.com/tailwind-chats/
	- https://www.npmjs.com/package/react-chat-elements
- #tailwindcss #居中
	- 参考： https://stackoverflow.com/a/66926329
- #flowgpt #ui 这个会话标志真地很不错，类似 openai，很舒服
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690591323238_0.png)
	-
- #js #选型 #日期
	- 参考：Moment.js | Docs, https://momentjs.com/docs/
	- 我选：dayjs
	- #todo star比较
- #TODO 主页按照cynthia的设计来
	- #TODO tailwindcss 里的 columns 不是按照横向排布的
- #UI #pinterest #masonry
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690573985227_0.png)
	- #TODO 为什么好像空隙不一样啊？是随机加的，还是基于某种 AspectRatio 呢
-
- #资源 图库：#Unsplash
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690572897585_0.png)
-
- #UI 定价按钮可以用 
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690572593877_0.png)
	- 参考：https://flowbite.com/docs/getting-started/introduction/
- #css Understanding min-content, max-content, and fit-content in CSS - LogRocket Blog, https://blog.logrocket.com/understanding-min-content-max-content-fit-content-css/
-
- #tailwindcss #overflow #multi-line下载 `@tailwindcss/line-clamp` https://postsrc.com/code-snippets/how-to-multi-line-trucate-text-in-tailwindcss
- #UI #civitai #search #todo 这个搜索结果非常棒：
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690471286747_0.png)
-
- #frontend #UI #Library 前端库指引[非常不错]： https://backlight.dev/mastery/best-react-component-libraries-for-design-systems ，其中 Radix-UI 是 Unstyled Components 中排第一个的，Mantine 在 Fully Styled Components 里
-
- #supabase #radix-ui #slogan #TODO 可以向supabase学习产品简介
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690467993416_0.png)
- #linear #radix-ui #ui #issue #TODO 可以用作新建聊天的弹出界面 ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690466851190_0.png){:height 351, :width 554}
  ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690467197078_0.png)
-
-
- #composer #radix-ui #ui 团队页挺酷：https://www.radix-ui.com/case-studies/composer
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690466691348_0.png)
	-
- #basement #radix-ui #ui 官网很酷炫：https://www.radix-ui.com/case-studies/basement-studio
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690466509068_0.png)
- #basedash #radix-ui #UI
	- #about-us about-us里可以写一封信，加签名会比较有意思 ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690465599128_0.png)
	- #customer-service ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690465927586_0.png)
	-
	-
- #discord #ui #human-verification
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690451082301_0.png)
	-
- #leonardo.ai #UI #login
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690450738863_0.png)
	-
- #postgresql start: https://stackoverflow.com/a/70941627
- #Term-Of-Service #civitai
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690406200738_0.png)
- #UI #login #civitai
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690406252999_0.png)
- #civitai #mature-content
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690406346264_0.png)
	-
- #TODO RoadMap Timeline
	- codes
		- 参考研究： https://blog.logrocket.com/comparing-best-react-timeline-libraries/
		- 目标库： https://github.com/prabhuignoto/react-chrono
	- 事件
		- 3.30 CS魔法社正式成立
		- 4.2 CS魔法社第一版网站上线
		- 4.25 CS魔法社美国公司主体成立
		- 5.25 CS魔法社第一次国际会议
		- 6.1 CS魔法社核心团队重组
		- 6.12 CS魔法社申请奇绩创业营
		- 6.20 Lara加入CS魔法社
		- 7.25 CS魔法社参加奇绩面试
	-
	-
- #logseq #bug #TODO logsq输入「」的bug
	- see: https://github.com/logseq/logseq/issues/4029
- #typescript #react 如何更好地声明带 children 的 props
	- solution: 使用 `PropsWithChildren`，参考: https://blog.logrocket.com/using-react-children-prop-with-typescript/
	-
- #nextjs #i18n 如何直接在 `_document.ts` 下使用 `t.Translation`
	- solution: 尽管有办法( #TODO )，但不推荐，参考：[# Translation of content inside _document.js](https://github.com/i18next/next-i18next/issues/734)
- #tailwindcss #drop-shadow 对 clotho 的成员角色使用 drop-shadow，默认的 tw 没有颜色等信息，需要手动实现
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690041688901_0.png)
	- ![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/image_1690041701016_0.png)
	-
- #separator #tailwindcss 目前有两种办法
	- 基于 tw 的 divider (针对border)，参考： https://tailwindcss.com/docs/divide-width ，它的高度/长度是基于整个元素的border高度/长度
	  ![Screenshot 2023-07-23 at 03.08.44.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/Screenshot_2023-07-23_at_03.08.44_1690053248006_0.png){:height 336, :width 524}
	- 基于 `shadcdn` 的 Separator，参考： https://ui.shadcn.com/docs/components/separator ，它的高度/长度是基于 `full`
	  ![Screenshot 2023-07-23 at 03.08.34.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/Screenshot_2023-07-23_at_03.08.34_1690053254833_0.png){:height 336, :width 524}
	- 实际测试下来，感觉 `shadcdn` 的效果更好一些
- #tailwindcss #plugin `matchutility`
	- 参考
		- 纯value： https://www.hyperui.dev/blog/text-shadow-with-tailwindcss
		- 递归（高级， #TODO 看看有没有啥最佳实践 ）： https://stackoverflow.com/a/70788915
	-
-