# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Type

Personal knowledge base and documentation repository. Content includes AI methodology (Vibe Coding), blog posts (2020-2025), tutorials, algorithms, and travel journals. NOT a software project - no build pipeline, no tests.

## Core Philosophy

- KISS, YAGNI - over-engineering is the enemy of good
- Context engineering > complex multi-agent systems
- "Like water" - AI flows through requirements, humans architect the container

## Repository Structure

| Directory | Purpose |
|-----------|---------|
| `ai/vibe-coding/` | Core Vibe Coding knowledge base and methodology |
| `ai/prompts/场景/` | AI prompt templates organized by scenario |
| `blog/` | Blog posts organized by year (2020-2025) |
| `docs/` | Tutorials and educational content |
| `TODO/` | Task backlog and drafts |
| `__archive__/` | Superseded content (don't delete, archive) |

## Commands

```bash
# Search content
rg "<keyword>"
rg --files -g '*.md'

# Check worktree
git status -sb
```

## Content Guidelines

- Topic-based organization, not file-type based
- Store images in `attachments/` subfolder with relative paths
- Archive superseded versions rather than deleting
- Markdown headings (`#` → `###`), short sections, bullet lists
- Mixed English/Chinese - match surrounding tone

## Commit Style

Short imperative messages: `chore: update vibe-coding`, `docs: add prompts/场景/会议`

## Key Reference

See `ai/vibe-coding/CLAUDE.md` for detailed Vibe Coding methodology and patterns.
