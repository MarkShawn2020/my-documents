# js-bugfix

1. [prettier](#prettier)
   1. [prettier plugin not work](#prettier-plugin-not-work)
   2. [recommend prettier plugins](#recommend-prettier-plugins)
2. [eslint](#eslint)
   1. [eslint google or standard](#eslint-google-or-standard)
3. [tailwindcss autocompletion](#tailwindcss-autocompletion)
   1. [enable tailwindcss autocompletion](#enable-tailwindcss-autocompletion)
   2. [fasten tailwindcss autocompletion](#fasten-tailwindcss-autocompletion)

## prettier

### prettier plugin not work

Check all the prettier packages, configs.

For Example, if the `packages.json` has a `prettier` key, then maybe it would have effect on the final result.

There is a list concluding the places prettier may exist:

1. `prettier.json`, `prettier.config.js`, `.prettierrc` files under project root
2. `prettier` key in `packages.json`
3. prettier file in Webstorm or VSCode
4. prettier config file in webpack
5. prettier config in sub modules.
6. prettier with eslint, typescript.

### recommend prettier plugins

1. sort import

2. The plugin of `prettier-plugin-sort-imports` can help sort into groups according our preset regex. https://github.com/trivago/prettier-plugin-sort-imports

## eslint

### eslint google or standard

I usually think the google may be the best for me to lint my code quality. However, maybe I am too innocent.

After when I initialized my eslint using `yarn run eslint --init`, and chose the `google` standard eslint style, I suffered from a `jsdoc comment` eslint error which forced me to use `Return` rather than `Returns` as the `return type` keyword.

I searched the jetbrains and eslint official website and shocked to found that they all use `Returns` rather than "google's" `Return`, which obviously means they have slightly different coding style and maybe have more.

Hence, as a newbie to the eslint, I 'gave up the road to the Google', and embraced the eslint standard, which won't force me to use `Return` rather than `Returns`.

Hmm.......

Fine, the real reason is that WebStorm doesn't give me much choice to change the default jsdoc comment action, unless I add some hard-to-remember (usually more and more) eslint rules to suppress this error, which seems not worth it.

By the way, I almost forget why I mentioned the eslint for that the WebStorm keeps warning me the `TypeError: this.cliEngineCtor is not a constructor`, and I tried almost every way to change the package, the configuration file, and so on, but in vain.

Finally, I tried to search by the condition in the recent one year, and I came to the answer: THIS IS A BUG, AND IT WON'T APPEAR IF YOU UPGRADE UP TO VERSION 2021.2.

Hmm.......

Easy but I am really so tied....

## tailwindcss autocompletion

### enable tailwindcss autocompletion

It sucks!

It costed me almost all night to solve it just by `yarn add -D tailwindcss@2.0.1-compat` according to this feedback: - [Tailwind class completion doesn't work with version "npm:@tailwindcss/postcss7-compat@2.2.4" : WEB-51405](https://youtrack.jetbrains.com/issue/WEB-51405)

I want to cry ... How deep I love WebStorm is even when the VSCode can run tailwindcss so well!

### fasten tailwindcss autocompletion

just open my `activity monitor` and close a bit of applications those of who is CPU large-occupied (e.g. PyCharm), then the autocompletion boost into fly !

That means, I am always wondering if the `antd` is dragging my IDE's leg, in fact, it doesn't if only my PC keeps running under a healthy pressure.
