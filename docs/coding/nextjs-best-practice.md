- rate-limiter
  collapsed:: true
	-
	- packages
		- rate-limit-redis - npm, https://www.npmjs.com/package/rate-limit-redis
	- ```ts
	    /**
	     * 2. 检查频率等相关
	     * note:
	     *  1. 因为我们已经有了用户系统，所以不需要检查频率了
	     *  2. 这个基于 KV 的对于大陆来说，太慢了，真要做，可以使用本地的 redis，参考：rate-limit-redis - npm, https://www.npmjs.com/package/rate-limit-redis
	     */
	    if (baseEnv.KV_REST_API_URL && baseEnv.KV_REST_API_TOKEN) {
	      const ip = req.headers.get("x-forwarded-for")
	      const ratelimit = new Ratelimit({
	        redis: kv,
	        // rate limit to 1 requests per 20 seconds
	        limiter: Ratelimit.slidingWindow(3, "10s"),
	      })
	  
	      const { success, limit, reset, remaining } = await ratelimit.limit(`ratelimit_${ip}`)
	  
	      if (!success) {
	        return NextResponse.json("您的速度太快啦，请慢点！", {
	          status: 429,
	          headers: {
	            "X-RateLimit-Limit": limit.toString(),
	            "X-RateLimit-Remaining": remaining.toString(),
	            "X-RateLimit-Reset": reset.toString(),
	          },
	        })
	      }
	      console.log("passed rate limiter")
	    }
	  ```
- openai streaming
	- version management
		- 教训：所以接第三方库真地还是谨慎，就算vercel这种公司的第三方库，也可能有bug，或者不满足需求，vercel的sdk里是一股脑塞messages给后端，但这样不但性能低，而且灵活性也不够，看chatgpt的前端实现，肯定是要维护一个conversation的，这样可以增量交互，不过chatgpt也鸡贼，它的网页访问速度那么快，除了基于edge之外，我猜就是做了暴力的rolling window，不然得数据库交互，就变慢了
		- at the beginning
		  ![image.png](../assets/image_1693667840442_0.png)
		- after ` yarn add langchain@latest`
		  ![image.png](../assets/image_1693667872670_0.png)
		- after `yarn add ai@latest`
		  ![image.png](../assets/image_1693667893080_0.png)
		-
		-
	- ```ts
	  import OpenAI from 'openai'
	  
	  // nodejs + edge
	  
	  const response = await new OpenAI({
	        apiKey: baseEnv.OPENAI_API_KEY,
	        timeout: 3000,
	        /**
	         *
	         * ref:
	         *  - https://github.com/openai/openai-node/tree/v4#configuring-an-https-agent-eg-for-proxies
	         *  - https://github.com/openai/openai-node/issues/85
	         *  - https://www.npmjs.com/package/https-proxy-agent
	         *
	         * edge 环境中 不支持 http / https-proxy-agent 等库
	         *
	         * 大陆服务器需要开启 clash tun mode !
	         */
	        httpAgent: undefined,
	      }).chat.completions.create({
	        model: modelType,
	        stream: true,
	        messages,
	        temperature: 0.7,
	      })
	  ```
	- ![image.png](../assets/image_1693667033047_0.png)
	- https://sdk.vercel.ai/docs/api-reference/openai-stream
	  ![image.png](../assets/image_1693667066209_0.png)
	-