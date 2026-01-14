# feat(theme-common): added interface for locale char mapping

<!--
Thank you for sending the PR! We appreciate you spending the time to work on these changes.
You can learn more about contributing to Docusaurus here: https://github.com/facebook/docusaurus/blob/main/CONTRIBUTING.md
Happy contributing!
-->

## Pre-flight checklist

- [x] I have read the [Contributing Guidelines on pull requests](https://github.com/facebook/docusaurus/blob/main/CONTRIBUTING.md#pull-requests) .
- [x] **If this is a code change**: I have written unit tests and/or added dogfooding pages to fully verify the new behavior.
- [x] **If this is a new API or substantial change**: the PR has an accompanying issue (closes #0000) and the maintainers have approved on my working plan.

<!--
Please also remember to sign the CLA, although you can also sign it after submitting the PR. The CLA is required for us to merge your PR.
If this PR adds or changes functionality, please take some time to update the docs. You can also write docs after the API design is finalized and the code changes have been approved.
-->

## Motivation

<!-- Help us understand your motivation by explaining why you decided to make this change. Does this fix a bug? Does it close an issue? -->

In order to solve the problem of classifying non-eng blog tags mentioned in #7843 , considering about the efficiency and extensibility, I finally managed to add an interface naming `charMap` in `I18nLocaleConfig` which is integrated with the current API nicely.

The work of updating documentation is also acceptable if this PR could be accepted.

## Demo

In order to use this new API, we need to provide the initial `charMap` in our app level manually. Here is a demo for someone need:

```js
// docusaurus.config.js

// the charMap you can easily find at e.g. https://github.com/guoyunhe/pinyin-json/blob/master/hanzi-pinyin-table.json
// attention to our interface is `one char --> one string` (so you need to convert `string[]` to `string` manually if you use the above data)
/** @type {import("@docusaurus/types/src/i18n").CharMap} */
const charMap = {
  测: 'ce',
  试: 'shi',
};

/** @type {import('@docusaurus/types').Config} */
module.exports = {
  i18n: {
    defaultLocale: 'zh-Hans',
    locales: ['zh-Hans'],
    localeConfigs: {
      'zh-Hans': {
        charMap,
      },
    },
  },
};
```

Then you can got the ideal effect when you open your blog tags page at: http://localhost:3000/blog/tags

<img width="1165" alt="image" src="https://user-images.githubusercontent.com/33591398/181509388-3b2e7581-059e-4cee-9061-a52765cc7a11.png"/>

## Related issues/PRs

<!-- If you haven't already, link to issues/PRs that are related to this change. This helps us develop the context and keep a rich repo history. If this PR is a continuation of a past PR's work, link to that PR. If the PR addresses part of the problem in a meta-issue, mention that issue. -->

- #7843
