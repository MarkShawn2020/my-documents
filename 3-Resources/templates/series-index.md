---
title: {{title}}
created: {{date}}
updated: {{date}}
status: draft
tags: []
type: series-index
description:
target_audience:
---

## 系列简介

{{cursor}}

## 文章列表

```dataview
TABLE series_order as "序号", title as "标题", status as "状态"
FROM this.file.folder
WHERE type = "series"
SORT series_order ASC
```

## 写作计划

| 序号 | 主题 | 状态 |
|------|------|------|
| 1 | | |
| 2 | | |
| 3 | | |
