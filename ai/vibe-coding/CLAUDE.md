# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Type

Documentation and research repository on Claude Code best practices and Vibe Coding methodology. NOT a software project - no build commands, no tests, no package.json.

## Core Philosophy

- "Like water" - AI flows through requirements, humans architect the container (context, constraints, feedback)
- KISS principle, YAGNI - over-engineered is the enemy of good
- Context engineering > complex multi-agent systems
- Single main loop (one branch max, never complex agent meshes)

## Repository Structure

- `/claude-code-best-practice/` - Core best practices including Anthropic's official guide
- `/prompts/reference/` - System prompt extractions and KIRO spec framework
- `/why-claude-code-is-good/` - Deep analysis of Claude Code architecture
- `/speed-up-your-vibe-coding/` - Optimization techniques (code-inspector, session hooks, flow state)

## Key Documents

| Path | Content |
|------|---------|
| `claude-code-best-practice/official.md` | Anthropic's definitive Claude Code guide |
| `prompts/reference/claide-code.md` | Complete system prompt extraction (9400+ tokens) |

## Key Patterns in This Repository

- Heavy use of markdown structure and XML tags (`<good-example>`, `<bad-example>`)
- Tool hierarchy: low-level (Bash) → mid-level (Grep/Glob) → high-level (Task)
- Use smaller models (Haiku) for 50%+ of support tasks
- LLM-native search via ripgrep/jq instead of RAG
- CLAUDE.md pattern for context management
