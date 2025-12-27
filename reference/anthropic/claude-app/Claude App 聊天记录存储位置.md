---
title: Claude App 聊天记录存储位置
slug: claude-code-1766139614440
source: https://www.google.com/search?q=claude+app+chat+history+location
datetime: 2025-12-19T10:20:14.440Z
---

Claude's chat history location depends on the app: for the web/desktop/mobile app, it's in the "Chats" sidebar on

claude.ai (cloud-based); for the local **[Claude Code](https://www.google.com/search?q=Claude+Code&mstk=AUtExfD4d6Y4NPadHuyQxQS_D42QA2CXfF92fVJKYeQXOjuvxcKwGjaQ9l2GHzFN6zB1RHmQE5Oyrv1xIQmofP2xXLXo5SNQKO_ugLQ1TXlXtOeKvNB4yo3f0FwlnWxErfB80fgvZUaVyaHL4GK3Dt3MjEY7niaCqyTetoAW5WTH2ywb3oTizoVKNPjHHGxoNchnAVojdw1gZj0y4l6SK-45v6wH8oIUgjcfKA-IlewqjkJiy2-UWNC_ZBS-cWspshzhmoI4GGGr8zA5QFTbgV0idZ5x&csui=3&ved=2ahUKEwjZx_fEtsmRAxXe8zgGHR_gANMQgK4QegQIARAB)** desktop app (VS Code, macOS), history is saved locally in your user folder, often under `~/.claude/projects/` as `.jsonl` files or within the `~/.claude.json` config file, allowing for local management and viewing. 

**For the Web/Standard Claude App (Mobile/Desktop Browser)** 

1.  **Access Chats:** Click the "Chats" icon on the left sidebar of the claude.ai https://claude.ai interface.
2.  **View/Manage:** Your conversations appear here, and you can delete them by selecting them and clicking "Delete Selected". 

**For the Local [Claude Code](https://www.google.com/search?q=Claude+Code&mstk=AUtExfD4d6Y4NPadHuyQxQS_D42QA2CXfF92fVJKYeQXOjuvxcKwGjaQ9l2GHzFN6zB1RHmQE5Oyrv1xIQmofP2xXLXo5SNQKO_ugLQ1TXlXtOeKvNB4yo3f0FwlnWxErfB80fgvZUaVyaHL4GK3Dt3MjEY7niaCqyTetoAW5WTH2ywb3oTizoVKNPjHHGxoNchnAVojdw1gZj0y4l6SK-45v6wH8oIUgjcfKA-IlewqjkJiy2-UWNC_ZBS-cWspshzhmoI4GGGr8zA5QFTbgV0idZ5x&csui=3&ved=2ahUKEwjZx_fEtsmRAxXe8zgGHR_gANMQgK4QegQIBBAB) App (macOS/VS Code)** 

-   **Local Storage:** Conversations are stored locally on your machine, typically in the `~/.claude/projects/` directory.
-   **Files:** Each chat session is often a `.jsonl` file (e.g., `~/.claude/history.jsonl`).
-   **Accessing:** Use the built-in history viewer or commands like `claude --resume` to see them, or manually navigate to the `~/.claude/` folder in your file explorer. 

**Key Differences** 

-   **Web App:** History is managed on Anthropic's servers (cloud) and accessible via your account.
-   **Claude Code:** History is stored on your computer, giving you direct file access and local control (and potential privacy benefits).