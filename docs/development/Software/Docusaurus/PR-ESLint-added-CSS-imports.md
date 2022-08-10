# enhance: added ESLint ruler for CSS import

## Pre-flight checklist

- [x] I have read the [Contributing Guidelines on pull requests](https://github.com/facebook/docusaurus/blob/main/CONTRIBUTING.md#pull-requests).
- [x] **If this is a code change**: I have written unit tests and/or added dogfooding pages to fully verify the new behavior.
- [x] **If this is a new API or substantial change**: the PR has an accompanying issue (closes #0000) and the maintainers have approved on my working plan.

## Motivation

In previous PR #7849, I found there is a bug when importing a `CSS` file after importing a type from `@docusaurus/type`.

At first, we (with the maintainer) are guessing the problem is caused by my system environment. But later I did a lot of checks, and came to realize that it's not.

In fact, the solution is rather simple, i.e. forcing CSS imported at last, with just one extra line configuration in `.eslintrc.js` file:

```js
{
  pattern: '*.css', // or '*.+(css|sass|less|scss|pcss|styl)' for general match
  patternOptions: {matchBase: true},
  group: 'unknown',
  position: 'after',
}
```

You can get more info from the following references:

- official documentation of `eslint-plugin-import`: https://github.com/import-js/eslint-plugin-import/blob/v2.26.0/docs/rules/order.md
- a discussion on how to import css at last (and I sorted out the best practice for our project from it): https://github.com/import-js/eslint-plugin-import/issues/1239

## Other Solutions

I'd think it unnecessary although it may works well using an extra plugin of [`eslint-plugin-css-import-order`](https://www.npmjs.com/package/eslint-plugin-css-import-order).

## Test (tested both in WebStorm and VSCode)

As mentioned from #7849, we can do a simple test.

TIPS:

- `grep -irE "import.*\.css" packages | cut -d ':' -f 1 | uniq` can list all the files with css files imported.
- the target type file is at `packages/docusaurus-types/src/index.d.ts`

Take the `packages/docusaurus-theme-common/src/components/Details/index.tsx` as an example, we can easily get the warning if we import types from `@docusaurus/types` before css file.

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pr-eslint-1659195319887-8770459de59c7347cb5845f23368115d7be11115ef6c6aa5aaa99d726a26612c.png)

However, if we omitted the imported default variable, then the warning would go away immediately (but would cause the later reference problems):

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/pr-eslint-1659195545529-b436263301a97afed1c705136cdcfe6a14ffce1e3f1b224b09304eb973ee688a.png)

## Essential

The problem is indeed rather simple, i.e. the plugin of `eslint-plugin-import` has no default type check for file extensions, so:

| grammar                       | group interpreated |
| ----------------------------- | ------------------ |
| `import css from 'xx.css'`    | `internal`         |
| `import css from './xx.css'`  | `sibling`          |
| `import css from '../xx.css'` | `parent`           |
| `import '../xx.css'`          | `unknown`(maybe)   |

Hence, in normal situation, those `internal | sibling | parent` would be ranked in front of `type`, except we explictly declaring the module order, just like what the former work has been done:

```js
...
{pattern: '@theme/**', group: 'internal'},
{pattern: '@site/**', group: 'internal'},
{pattern: '@theme-init/**', group: 'internal'},
{pattern: '@theme-original/**', group: 'internal'},
...
```

All those variables, as well as types, would be intepreted before any css-like imports.

But then, not so lucky for those types imported from `@docusaurus/types`.

## Other Problems

Also, if we do not rectify this problem, each time when we commited, the eslint fix would force the local files changed into like this, which is not expected:

```ts
import styles from './styles.module.css';

import type {Config} from '@docusaurus/types';
```

## Related issues/PRs

#7849
