## track

| date       | item                                                                                        | status | reason      | detail                     |
| ---------- | ------------------------------------------------------------------------------------------- | ------ | ----------- | -------------------------- |
| 2022-06-20 | bug: adobe photoshop export                                                                 | closed | DISAPPEARED | [^ps-bug]                  |
| 2022-06-20 | chore: delete MP4 in git repo                                                               | closed | FIXED       | [^git-rm-mp4]              |
| 2022-02-04 | article: linux core intro                                                                   | closed | FINISHED    |                            |
| 2022-01-06 | feat: vscode md image upload                                                                | closed | FIXED       | [^vscode-md-img-upload]    |
|            | pr: ttf2bmf backend                                                                         | closed | NOT_FOCUSED | [^ttf2bmf-node]            |
|            | article: ASCII ART                                                                          | closed | NOT_FOCUSED |                            |
|            | feat: vscode markdown container support                                                     | closed | FIXED       |                            |
|            | bug: vscode lag when input                                                                  | closed | FIXED       | [^vscode-lag-when-input]   |
|            | feat: vscode md flex                                                                        | closed | FIXED       | [^vscode-md-flex]          |
|            | chore: sort out the best-practice of md workflow                                            | closed | ENOUGH      | [^vscode-md-best-practice] |
|            | book: frontend, backend to algo<br/> - coding 0-1, with lectures and videos                      | closed | TOO_EARLY   |                            |
|            | chore: control mkl repo size                                                                | closed | SOLVED      | [^git-control-repo-size]   |
|            | refactor: change `index.yaml` to be `index.md`                                              | closed | NOT_FOCUSED |                            |
|            | project: Legend of King Auto Simulate System                                                | closed | NOT_FOCUSED |                            |
|            | chore: add color support for `build/init.zsh`                                               | closed | NOT_FOCUSED |                            |
|            | article: Prisma is not suitable for electron                                                | closed | NOT_FOCUSED |                            |
|            | plugin: LinkToText                                                                          | closed | NOT_FOCUSED |                            |
|            | chore: change the default TOC config<br/> - `depth_from`: 1 -> 2,  `depth_to`: 6 -> 4 | closed | SOLVED      | [^config-md-toc-depth]     |
|            | article: shortcuts comparison                                                               | closed | FINISHED    |                            |

## ref

[^vscode-lag-when-input]: I find this problem is concerned with this plugin.

    <img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1640997398482-1e216ff6476599b4a7d53857572e02f0d4f8243efde1f2634f244e865ed10a14.png" width="480" />

    since, when it's enabled, the window would freeze if I input the '\`' and then `enter` or `back`.

    However, it seems this `auto-completion` is built-in.

    I would first try some time without it.

[^vscode-md-flex]:
    - [x] G1：选中两张 md 图片链接，实现右键加入 flex 布局的父级 div，以使图片并行显示

    - [x] \*G2：在 G1 的基础上提供更多细分子选项，以实现更精细的布局

    > :warning: 直接使用 snippet 完成了，写成 markdown 专用的即可，非常方便，第二点算了，没意思

    <img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640133252106-TODO-db31c81de8d77347593a369f183a66c571ae504c6d6a0e5a332c66ca76016da1.png" width="480" />

[^vscode-md-best-practice]:
    - [Markdown Basics](https://shd101wyy.github.io/markdown-preview-enhanced/#/markdown-basics?id=admonition)

    | preview | save to pdf | copy to mdnice | directly output pdf |
    | ------- | ----------- | -------------- | ------------------- |

[^config-md-toc-depth]: see:

    - [TOC](https://shd101wyy.github.io/markdown-preview-enhanced/#/toc)

    - [Configure the default parameters of TOC · Issue #712 · shd101wyy/markdown-preview-enhanced](https://github.com/shd101wyy/markdown-preview-enhanced/issues/712)

    - [可以更改 front-matter 的默认设置么？ · Issue #603 · shd101wyy/markdown-preview-enhanced](https://github.com/shd101wyy/markdown-preview-enhanced/issues/603)

[^ps-bug]: ![ps bug](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/readme-1641365174494-15af5de4688f278c90d3bd566d99d9a7542731e32038f18f56e5699d473f16c0.png)
[^git-rm-mp4]: see: https://htmlpreview.github.io/?https://github.com/newren/git-filter-repo/blob/docs/html/git-filter-repo.html
[^git-control-repo-size]: 使用`git filter-branch`把图片从历史汇总都删掉就可以，一共 400 多条 commit，每条删几百张图片，一分钟左右就差不多了（前提要都上传到图床，所以需要我们自己的图床批量上传脚本，具体见`~/coding/PycharmProjects/my-markdown-parser/src/main.py`。
[^vscode-md-img-upload]: see: script of md_img_handler (now maybe under image-playgrounds)
[^ttf2bmf-node]: project url: https://github.com/SilenceLeo/snowb-bmf
