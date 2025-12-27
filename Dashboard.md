---
title: 内容管理中心
---

# 内容管理中心

## 排期看板

### 待发布 (Scheduled)
```dataview
TABLE title as "标题", publish_date as "排期", platforms as "平台"
FROM "posts"
WHERE status = "scheduled"
SORT publish_date ASC
```

### 草稿 (Drafts)
```dataview
TABLE title as "标题", updated as "更新", tags as "标签"
FROM "posts"
WHERE status = "draft"
SORT updated DESC
LIMIT 20
```

---

## 灵感池

### 最新灵感
```dataview
TABLE title as "标题", created as "创建"
FROM "inbox"
SORT created DESC
LIMIT 10
```

### 需要处理的灵感 (>7天未处理)
```dataview
LIST
FROM "inbox"
WHERE date(now) - date(created) > dur(7 days)
SORT created ASC
```

---

## 系列进度

```dataview
TABLE length(rows) as "文章数",
  filter(rows, (r) => r.status = "published").length as "已发布",
  filter(rows, (r) => r.status = "draft").length as "草稿"
FROM "posts/series"
WHERE type = "series"
GROUP BY series
```

---

## 发布统计

### 本月发布
```dataview
TABLE title as "标题", publish_date as "发布日期"
FROM "posts"
WHERE status = "published" AND publish_date >= date(today) - dur(30 days)
SORT publish_date DESC
```

### 各平台状态
```dataview
TABLE
  platforms.wechat as "公众号",
  platforms.zhihu as "知乎",
  platforms.blog as "博客"
FROM "posts"
WHERE status = "published"
SORT publish_date DESC
LIMIT 10
```

---

## 快速操作

- [[templates/idea|新建灵感]]
- [[templates/post|新建文章]]
- [[inbox/|灵感池]]
- [[posts/standalone/|单篇文章]]
- [[posts/series/|系列文章]]
