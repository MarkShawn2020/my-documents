---
title: Quick Start
slug: quick-start-1765965739003
source: https://docs.zenmux.ai/guide/quickstart.html
datetime: 2025-12-17T10:02:19.003Z
---

# Quick Start [​](#quick-start)

Welcome to **[ZenMux](https://docs.zenmux.ai/about/intro.html)**! This guide will help you get started quickly and shows how to call the ZenMux API in three different ways.

💡 Get started in 4 steps

You can start using ZenMux in just four simple steps:

1.  **Sign in to ZenMux**: Visit the **[ZenMux login page](https://zenmux.ai/login)** and sign in using any of the following:
    
    -   Email
    -   GitHub account
    -   Google account
2.  **Get an API key**: After signing in, go to your **[User Console > API Keys](https://zenmux.ai/settings/keys)** page and create a new API key.
    
3.  **Choose an integration method**: We recommend using the OpenAI SDK or Anthropic SDK in compatibility mode, or you can call the ZenMux API directly.
    
4.  **Make your first request**: Copy the code example below, replace your API key, and run it.
    

* * *

How to Obtain Model Slugs

Each model on the ZenMux platform has a unique slug. You can find model slugs on the [Models page](https://zenmux.ai/models): ![model-slug](https://cdn.marmot-cloud.com/storage/zenmux/2025/10/21/AQG0SIr/model-slug.png) Or on the [model detail page](https://zenmux.ai/anthropic/claude-sonnet-4.5): ![model-slug](https://cdn.marmot-cloud.com/storage/zenmux/2025/10/21/dWYxJnq/model-slug-3.png)

## Method 1: Using the OpenAI SDK [​](#method-1-using-the-openai-sdk)

Compatibility

ZenMux endpoints are fully compatible with the OpenAI API. You only need to change two parameters to switch seamlessly.

### Code Examples [​](#code-examples)

PythonTypeScript

python

```
from openai import OpenAI

# 1. Initialize the OpenAI client
client = OpenAI(
    # 2. Point the base URL to the ZenMux endpoint
    base_url="https://zenmux.ai/api/v1", 
    # 3. Replace with the API key from your ZenMux console
    api_key="<your ZENMUX_API_KEY>", 
)

# 4. Make the request
completion = client.chat.completions.create(
    # 5. Specify the model you want to use in the format "provider/model-name"
    model="openai/gpt-5", 
    messages=[
        {
            "role": "user",
            "content": "What is the meaning of life?"
        }
    ]
)

print(completion.choices[0].message.content)
```

ts

```
import OpenAI from "openai";

// 1. Initialize the OpenAI client
const openai = new OpenAI({
  // 2. Point the base URL to the ZenMux endpoint
  baseURL: "https://zenmux.ai/api/v1", 
  // 3. Replace with the API key from your ZenMux console
  apiKey: "<your ZENMUX_API_KEY>", 
});

async function main() {
  // 4. Make the request
  const completion = await openai.chat.completions.create({
    // 5. Specify the model you want to use in the format "provider/model-name"
    model: "openai/gpt-5", 
    messages: [
      {
        role: "user",
        content: "What is the meaning of life?", 
      },
    ],
  });

  console.log(completion.choices[0].message);
}

main();
```

* * *

## Method 2: Using the Anthropic SDK [​](#method-2-using-the-anthropic-sdk)

Compatibility

ZenMux fully supports the Anthropic API protocol and integrates seamlessly with tools like Claude Code and Cursor. You only need to change two parameters.

Note: For the Anthropic protocol, use base\_url="[https://zenmux.ai/api/anthropic](https://zenmux.ai/api/anthropic)".

Anthropic Protocol Model Support

Models compatible with the Anthropic protocol are being adapted in batches. You can view the currently supported models by filtering for Anthropic API Compatible on the [official model list](https://zenmux.ai/models): ![anthropic-support](https://cdn.marmot-cloud.com/storage/zenmux/2025/10/16/602FqX9/anthropic-support.png) You can also check on the [model detail page](https://zenmux.ai/anthropic/claude-haiku-4.5): ![anthropic-support](https://cdn.marmot-cloud.com/storage/zenmux/2025/10/16/I9JHS8b/detail-anthropic-support.png)

### Code Examples [​](#code-examples-1)

PythonTypeScript

python

```
from anthropic import Anthropic

# 1. Initialize the Anthropic client
client = Anthropic(
    # 2. Point the base URL to the ZenMux endpoint
    base_url="https://zenmux.ai/api/anthropic", 
    # 3. Replace with the API key from your ZenMux console
    api_key="<your ZENMUX_API_KEY>", 
)

# 4. Make the request
message = client.messages.create(
    # 5. Specify the model you want to use in the format "provider/model-name"
    model="anthropic/claude-sonnet-4.5", 
    max_tokens=1024,
    messages=[
        {
            "role": "user",
            "content": "What is the meaning of life?"
        }
    ]
)

print(message.content[0].text)
```

ts

```
import Anthropic from "@anthropic-ai/sdk";

// 1. Initialize the Anthropic client
const client = new Anthropic({
  // 2. Point the base URL to the ZenMux endpoint
  baseURL: "https://zenmux.ai/api/anthropic", 
  // 3. Replace with the API key from your ZenMux console
  apiKey: "<your ZENMUX_API_KEY>", 
});

async function main() {
  // 4. Make the request
  const message = await client.messages.create({
    // 5. Specify the model you want to use in the format "provider/model-name"
    model: "anthropic/claude-sonnet-4.5", 
    max_tokens: 1024,
    messages: [
      {
        role: "user",
        content: "What is the meaning of life?", 
      },
    ],
  });

  console.log(message.content[0].text);
}

main();
```

* * *

## Method 3: Calling the ZenMux API Directly [​](#method-3-calling-the-zenmux-api-directly)

Python (httpx)TypeScript (fetch)Shell (cURL)

python

```
import httpx

# Prepare request data
api_key = "<your ZENMUX_API_KEY>"
headers = {
    "Authorization": f"Bearer {api_key}", 
}
payload = {
    "model": "openai/gpt-5", 
    "messages": [
        {
            "role": "user",
            "content": "What is the meaning of life?"
        }
    ]
}

# Send a POST request
response = httpx.post(
    "https://zenmux.ai/api/v1/chat/completions", 
    headers=headers,
    json=payload,
    timeout=httpx.Timeout(60.0)
)

# Optionally check whether the request succeeded
response.raise_for_status()

# Print the JSON response returned by the server
print(response.json())
```

typescript

```
fetch("https://zenmux.ai/api/v1/chat/completions", {
  method: "POST",
  headers: {
    Authorization: "Bearer <your ZENMUX_API_KEY>", 
    "Content-Type": "application/json",
  },
  body: JSON.stringify({
    model: "openai/gpt-5", 
    messages: [
      {
        role: "user",
        content: "What is the meaning of life?", 
      },
    ],
  }),
})
  .then((response) => response.json())
  .then((data) => console.log(data))
  .catch((error) => console.error("Error:", error));
```

bash

```

curl https://zenmux.ai/api/v1/chat/completions
  -H "Content-Type: application/json"
  -H "Authorization: Bearer $ZENMUX_API_KEY"
  -d '{
    "model": "openai/gpt-5",
    "messages": [
      {
        "role": "user",
        "content": "What is the meaning of life?"
      }
    ]
  }'
```

* * *

## Advanced Usage [​](#advanced-usage)

For more details on advanced usage, refer to the Advanced Usage section.

Contact Us

If you encounter any issues during use or have suggestions and feedback, feel free to contact us:

-   **Official Website**: [https://zenmux.ai](https://zenmux.ai)
-   **Technical Support**: [support@zenmux.ai](mailto:support@zenmux.ai)
-   **Business Inquiries**: [bd@zenmux.ai](mailto:bd@zenmux.ai)
-   **Twitter**: [@ZenMuxAI](https://twitter.com/ZenMuxAI)
-   **Discord Community**: [http://discord.gg/vHZZzj84Bm](http://discord.gg/vHZZzj84Bm)

For more contact options and details, please visit our [Contact Us page](/help/contact.html).