#!/usr/bin/env python3
"""Preview recent Claude Code chat messages from the latest session."""
import json, os, subprocess, sys

n = int(sys.argv[1]) if len(sys.argv) > 1 else 10
project_key = os.getcwd().replace("/", "-")
session_dir = os.path.expanduser(f"~/.claude/projects/{project_key}")
files = sorted(
    [f for f in os.listdir(session_dir) if f.endswith(".jsonl")],
    key=lambda f: os.path.getmtime(os.path.join(session_dir, f)),
    reverse=True,
)
if not files:
    print("No session found."); sys.exit(1)

session = os.path.join(session_dir, files[0])
print(f"Session: {files[0][:36]}\n")

msgs = []
with open(session) as f:
    for line in f:
        try:
            obj = json.loads(line)
            t = obj.get("type")
            content = obj.get("message", {}).get("content", "")
            if t == "user":
                if isinstance(content, list):
                    text = " ".join(c.get("text", "") for c in content if c.get("type") == "text").strip()
                else:
                    text = str(content).strip()
                if text and len(text) > 3:
                    if msgs and msgs[-1][0] == "U":
                        msgs[-1] = ("U", msgs[-1][1] + " " + text)
                    else:
                        msgs.append(("U", text))
            elif t == "assistant" and isinstance(content, list):
                parts = []
                for c in content:
                    if c.get("type") == "text" and c.get("text", "").strip():
                        parts.append(c["text"].strip().replace("\n", " ")[:80])
                    elif c.get("type") == "tool_use":
                        name = c["name"]
                        inp = c.get("input", {})
                        detail = inp.get("command", inp.get("file_path", inp.get("pattern", "")))[:40]
                        parts.append(f"[{name}] {detail}")
                if parts:
                    combined = " | ".join(parts)
                    if msgs and msgs[-1][0] == "A":
                        msgs[-1] = ("A", msgs[-1][1] + " | " + combined)
                    else:
                        msgs.append(("A", combined))
        except Exception:
            pass

try: W = os.get_terminal_size().columns
except: W = 120
for i, (role, text) in enumerate(msgs[-n:]):
    if role == "U" and i > 0:
        print()
    print(f"{role}: {text}"[:W])
