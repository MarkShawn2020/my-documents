# markdown howto

[toc]

## markdown image

### naming

不能加空格，需要的话用`%20`代替，see: https://github.com/alanshaw/markdown-pdf/issues/54#issuecomment-103174459

### size

There are some recommended methods to add width property into markdown image, while doesn't work.

The following one would show the image as it is, ignoring the last bracket info (even showing the raw text).

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/markdown-howto-1644166436688-6da8fba57bab71137e2c6d56aaf6932eda6c72ab8c49f36a7353317dbd9ac6f3.png)

The following one would have no effect, even not showing the picture, neither in vscode, nor in github.

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/markdown-howto-1644166420169-fd08be178275d4663403c9358d72332b4acbab7e255dbe53bfcfaf19da32b457.png)

So, it turns out that almost none of methods are effective when we use markdown type of image rather than html type.

However, I didn't want to use html type, not only because it looks more complicated, but also since the vscode doesn't support the jump feature natively (maybe I can get the solution by some plugin, but I am just not willing to).

So, current solution: using markdown type image, not considering about the feature of image size specification.

PR: set markdown image size in markdown type image.

ref:

- [Changing image size in Markdown - Stack Overflow](https://stackoverflow.com/questions/14675913/changing-image-size-in-markdown)

## check box alternative

I noticed that `- [ ] / [x]` would sometimes not render if they are in headings and under preview mode, which is dependent with the package.

More specifically, in VSCode built-in render, it does; while in markdown-preview-enhanced, it not.

Then I found that using `:white_check_mark:` instead of `- [x]`, and using `:white_large_square:` instead of `- [ ]` is a better choice, which can guarantee its render.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640847795445-markdown-howto-c8be81bd2808a8055d513a68ace0cc787944492e4a4a5a86bff9103e3d3ae01e.png" width="480" />

And also, with a more fancy effect: <img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640847850974-markdown-howto-fedad67a6062686ad5ddaf2be18e7e55eb288cd09fe562ea3399b13997a1f0ee.png" width="480" />

ref:

- [How to draw checkbox or tick mark in GitHub Markdown table? - Stack Overflow](https://stackoverflow.com/questions/47344571/how-to-draw-checkbox-or-tick-mark-in-github-markdown-table/55523035)

### update: use `:white_circle:` instead of `:white_large_square:`

I again found that `:white_large_square:` can not be rendered in pdf outputted.

I checked the markdown emojis in github, but to find there is no this one in the list indeed.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640849077393-markdown-howto-9d48e6caaa8016138d4f29d903d8714591f69c74d9a03d83dd529c8f24bd8ad2.png" width="480" />

After a quick glimpse at the emoji list, I suppose the `:white_circle` is a good alternative since it looks nice and write easy to remember. <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640849010186-markdown-howto-00381ae256eff1a5b64ad826fa92d3c1f341e2280be9b57876352d777644840d.png" width="480" />

ref:

- [Complete list of github markdown emoji markup](https://gist.github.com/rxaviers/7360908)

### recommended emojis

#### numbers

:zero: :one: :two: :three: ... :nine:

#### tips

:o: :x: :heavy_exclamation_mark: :bangbang: (this is not so fancy as to github)

### checks

:heavy_check_mark: :ballot_box_with_check: :white_check_mark:

### emotions

:smiley:

ref:

- [Complete list of github markdown emoji markup](https://gist.github.com/rxaviers/7360908)
