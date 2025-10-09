
- 版本：1.1.1
- 日期：2025-07-30
- 编辑：南川
- 联系：17766091857

## 概要

本系统目前由 **微信小程序 + 微信云开发 + coze工作流** 三部分构成。

其中：
- 微信小程序部分的代码在 https://github.com/MarkShawn2020/2025-04-05_bpmaster ，环境变量 .env 文件单独发送，里面记载了coze 工作流所需的 token、id等。
- 微信云开发部分使用了小程序自带的云开发环境，**按月续费，每个月19元，8月29日到期**。如果过期不续费导致服务被吊销，重新建立的话需要：
	- 上传代码中云函数并部署
	- 创建数据表：`analysis_tasks | bp_files | reports | users`，权限均可设置为默认的 `所有用户可读，仅创建者可读写`
- coze bp 分析工作流（**bp_analysis_structured**）：
	- 编辑：https://www.coze.cn/work_flow?space_id=7465250504236089382&workflow_id=7488013332172193801
	- 发布后监控：https://www.coze.cn/space/7465250504236089382/publish/workflow/7488013332172193801
	- 调试：https://www.coze.cn/open/playground/workflow_stream_run
	- 获取token：https://www.coze.cn/open/docs/developer_guides/pat，**目前免费，不清楚用量限制，一个月（8月29日）到期**。
	

具体可以看代码里的 README.md 。

---

## Appendix

### 环境变量文件

```js {config.env.js}
// config.env.js
// ⚠️  DO NOT COMMIT THIS FILE TO VERSION CONTROL
// Add to .gitignore immediately

module.exports = {
  // Development environment
  dev: {
    coze: {
      API_URL: 'https://api.coze.cn/v1/workflow/stream_run',
      TOKEN: 'pat_3rj2Yex0Z2I9LxvkfezTxrhPv8wXH0vYx1y5sc1b4XO7kfC4V9iQfSc7Bilffkrl', // ⚠️  Replace with your actual token
      WORKFLOW_ID: '7488013332172193801'
    }
  },

  // Production environment
  prod: {
    coze: {
      API_URL: 'https://api.coze.cn/v1/workflow/stream_run',
      TOKEN: 'pat_3rj2Yex0Z2I9LxvkfezTxrhPv8wXH0vYx1y5sc1b4XO7kfC4V9iQfSc7Bilffkrl', // ⚠️  Replace with production token
      WORKFLOW_ID: 'your-prod-workflow-id'
    }
  }
};
```


