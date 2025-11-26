# Repository Guidelines

## Project Structure & Module Organization
- Content is topic-based: `claude-code-best-practice/` (best practices), `claude-code-skills/` (skills deep dives), `prompts/` (templates under `场景/` plus `reference/`), `discussion/` (vibe-seminar notes with `attachments/` images and `__archive__/` history), `speed-up-your-vibe-coding/`, `todo/` drafts, `what-vibe-coding-can-do/`, `why-claude-code-is-good/`, and `share/`.
- Add new pieces beside similar work; keep superseded drafts in `__archive__/` or numbered `v1/`, `v2/` folders rather than deleting.
- Store images next to the article inside an `attachments/` subfolder and link them with relative paths.

## Build, Test, and Development Commands
- Markdown-only repository; no build pipeline. Validate edits by reading locally.
- Search quickly with `rg "<keyword>"` and list docs with `rg --files -g '*.md'`.
- Check your worktree before/after edits: `git status -sb`.

## Coding Style & Naming Conventions
- Use Markdown headings (`#` → `###`) with short sections and bullet lists; avoid trailing whitespace.
- Include YAML front matter only when translating or annotating external sources; keep keys (`date`, `source`, `author`) consistent.
- File names follow descriptive phrases or numbered series (`01. topic/`, `v1.md`); match existing spacing/casing patterns in each folder.
- Keep prose concise and actionable; when mixing English and Chinese, mirror the surrounding tone.
- Prefer reference-style links and relative asset paths; avoid embedding large base64 images.

## Testing Guidelines
- Manual review: preview Markdown, verify internal links/anchors and image paths, and spell-check headers.
- For large rewrites, compare diffs to catch formatting drift; ensure code blocks include an info string when possible.

## Commit & Pull Request Guidelines
- Mirror existing history: short, imperative messages such as `chore: update vibe-coding` or `docs: add prompts/场景/会议`.
- In PRs, include a brief summary, list touched directories, note new assets, and link related discussions/issues; add screenshots when formatting or images change.
- Keep diffs focused; split unrelated edits into separate commits/PRs.
