## locales of hyphen （中折线）

要用 `zh-CN` 而非 `zh-cn`，否则客户端读取 Resource 时会失败（不过服务器端没问题），从而引发 hydration mismatch error!

- [8.0.0-beta.6] Unable to read translation of locale with hyphen · Issue #963 · i18next/next-i18next, https://github.com/i18next/next-i18next/issues/963

## todo: type hint

ref: 
- https://github.com/i18next/next-i18next/issues/1732#issuecomment-1484030343
- https://github.com/i18next/next-i18next/discussions/2029

目前解决方案，先降级，降级后暂时不爆红了，但是依旧是没有自动提示的：

ref: https://github.com/i18next/next-i18next/issues/2040#issuecomment-1571752803
