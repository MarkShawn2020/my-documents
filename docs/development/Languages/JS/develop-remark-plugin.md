1.  [develop own markdown parser or renderer](#develop-own-markdown-parser-or-renderer)
    1. [where does code fence define](#where-does-code-fence-define)
    2. [re-read `remark-parse`](#re-read-remark-parse)
    3. [from 'remark-parse' to 'madst-util-from-markdown'](#from-remark-parse-to-madst-util-from-markdown)
    4. [from 'mdast-util-directive' to 'remark-util-directive'](#from-mdast-util-directive-to-remark-util-directive)
    5. [codes](#codes)
2.  [For markdown plugin develop, what I installed...](#for-markdown-plugin-develop-what-i-installed)
3.  [add plugin of `remark-admonitions`](#add-plugin-of-remark-admonitions) micromark +-----------------------------------------------------------------------------------------------+ | +------------+ +-------+ +-------------+ +---------+ | | -markdown->+ preprocess +-chunks->+ parse +-events->+ postprocess +-events->+ compile +-html- | | +------------+ +-------+ +-------------+ +---------+ | +-----------------------------------------------------------------------------------------------+

## develop own markdown parser or renderer

<img alt="picture 39" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640534835564-develop-remark-pulgin-53d15886abb4e96df53e8dd633818aace151b554f07c9f82e9d68827b4981e2c.png" width="480" />

<img alt="picture 40" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640534849836-develop-remark-pulgin-fe8329f439e5bd5b23ae887bd35cca9196ab3174f5da692ff109b105ba9db908.png" width="480" />

<img alt="picture 41" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640535067245-develop-remark-pulgin-125972fad0bafd18f6d30d389588a614a8d5e1af6f5b11125dd7421a128cc929.png" width="480" />

### where does code fence define

<img alt="picture 42" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640535550983-develop-remark-pulgin-91953f2402b316961585fc0d36c29ab6bfb4624dc9172c6f81c9a36df3c57579.png" width="480" />

```text
graveAccent: '`'
```

<img alt="picture 43" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640535610458-develop-remark-pulgin-c0a04e05910e60778e0e7285e1d89173e1a7776f73c52c255b8e0650d38adcef.png" width="480" />  
ref: https://github.com/micromark/micromark/blob/1b378e72675b15caff021f957a824d1f01420774/packages/micromark-util-symbol/values.js

<img alt="picture 44" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640535975633-develop-remark-pulgin-f46fd886e5f2fa678d5602db467e55435da9a745382aa4c11bb3280aba8aa695.png" width="480" />  
ref: https://github.com/micromark/micromark/blob/1b378e72675b15caff021f957a824d1f01420774/packages/micromark-core-commonmark/dev/lib/code-fenced.js

### re-read `remark-parse`

<img alt="picture 45" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640536201826-develop-remark-pulgin-1d4d57f6541d2939d8d67275c6fe5fd0e78e16fd367b7dededf3a8ec6c496443.png" width="480" />

<img alt="picture 47" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640536341787-develop-remark-pulgin-7c68078f8db11f6cb96515d1d7cb4235bc1952e3e01cf1ce55d3097534ac2849.png" width="480" />

<img alt="picture 48" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640536429419-develop-remark-pulgin-1e41b15b1c6e53bd3bd6e305ba181a9e382904a213cbf3b08424193a45db5db2.png" width="480" />

what's micromarkExtensions <img alt="picture 49" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640536520719-develop-remark-pulgin-a4d866acb9b4ac9afc5f36bfae9f4f7449a2ca221d84ff04b27344c8bd0fdbc8.png" width="480" />

found block sign! <img alt="picture 50" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640536648776-develop-remark-pulgin-b100cd6b8014ff9e86ead4d8299b0987851226170b4e6da3222d5f971a9f4c47.png" width="480" />  
ref: https://github.com/micromark/micromark-extension-directive

### from 'remark-parse' to 'madst-util-from-markdown'

<img alt="picture 51" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640540654644-develop-remark-pulgin-54bfad5fd02ca4f174ca8b127baf9a877ba76f2ee8fe0cb5868d35c29a5ed75f.png" width="480" />

<img alt="picture 53" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640542150793-develop-remark-pulgin-a57c943a08b8fae7954ac1b3aa3aefe38e4802bdbeaa628995bf1b47a85f5e1a.png" width="480" />

<img alt="picture 52" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640542124402-develop-remark-pulgin-55718c8af6c06e2e1d700bc1a327031901c070b39db7205f45799fc26247c054.png" width="480" />

<img alt="picture 54" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640542514584-develop-remark-pulgin-a449642c210f1374cbcc8c53768f1b359aabc172f5d702b83f9f8ebfce0ab8d5.png" width="480" />

### from 'mdast-util-directive' to 'remark-util-directive'

### codes

- [micromark/code-fenced.js at main · micromark/micromark](https://github.com/micromark/micromark/blob/main/packages/micromark-core-commonmark/dev/lib/code-fenced.js)

the base of parse

- [micromark/micromark: the smallest commonmark (optionally gfm) compliant markdown parser that exists; new basis for @unifiedjs (hundreds of projects w/ billions of downloads for dealing w/ content)](https://github.com/micromark/micromark)

<img alt="picture 37" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640533690391-develop-remark-pulgin-33eda7fa976522971c92fffb2b5206f90c9262c29f7b0474eb838fc9850f8c94.png" width="480" />

`mdast` uses many interfaces from `mdast`

- [mdast-util-from-markdown/index.js at main · syntax-tree/mdast-util-from-markdown](https://github.com/syntax-tree/mdast-util-from-markdown/blob/main/dev/lib/index.js)

The only thing `remark-parse` does is to call `mdast-util-from-markdown`

- [remark/index.js at main · remarkjs/remark](https://github.com/remarkjs/remark/blob/main/packages/remark-parse/lib/index.js)

- [unified/index.d.ts at 6b060c2a229049e1bc0e7ea51920b36efb069f9f · unifiedjs/unified](https://github.com/unifiedjs/unified/blob/6b060c2a229049e1bc0e7ea51920b36efb069f9f/index.d.ts)

## For markdown plugin develop, what I installed...

<img alt="picture 58" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640561256909-develop-remark-pulgin-7ffbdae57a305e6f05bdf4c974093415c5ec83b20376ccd8e9bf203fe928b3d5.png" width="480" />

In fact, I need none of them except:

```json
{
  "remark": "^13.0.0",
  "remark-directive": "^2.0.1",
  "remark-parse": "^10.0.1"
}
```

refer: gatsby

- [Creating a Remark Transformer Plugin | Gatsby](https://www.gatsbyjs.com/tutorial/remark-plugin-tutorial/)

handbook

- [unifiedjs/handbook: [WIP] A handbook on the unified ecosystem, including supported syntaxes, ASTs, and guides on how to use the libraries](https://github.com/unifiedjs/handbook)

⭐️⭐️⭐️ An AAAAAAAAAAwesome adn detailed tutorial from real practice of building a beautiful block code

- [Pedro Duarte — Code blocks, but better](https://ped.ro/blog/code-blocks-but-better)

An AAAAAwesome tutorial, except a bit easy and old

- [How to Modify Nodes in an Abstract Syntax Tree - CSS-Tricks](https://css-tricks.com/how-to-modify-nodes-in-an-abstract-syntax-tree/)

An awesome video tutorial

- [Create a remark Plugin to Modify Markdown Headings | egghead.io](https://egghead.io/lessons/javascript-create-a-remark-plugin-to-modify-markdown-headings)

source code of msat

- [https://npmdoc.github.io/node-npmdoc-remark/build/apidoc.html#apidoc.tableOfContents](https://npmdoc.github.io/node-npmdoc-remark/build/apidoc.html#apidoc.tableOfContents)

official remark plugins list

- [remark/plugins.md at main · remarkjs/remark](https://github.com/remarkjs/remark/blob/main/doc/plugins.md)

official mdast reference

- [syntax-tree/mdast: Markdown Abstract Syntax Tree format](https://github.com/syntax-tree/mdast)

a loaders intro of chinese

- [loader 知识点 - 知乎](https://zhuanlan.zhihu.com/p/386474371)

webpack remark loader homepage

- [remark-loader | webpack 中文文档](https://webpack.docschina.org/loaders/remark-loader/)

A good article except not so detailed

- [How to build a Remark plugin to supercharge your static site | Swizec Teller](https://swizec.com/blog/how-to-build-a-remark-plugin-to-supercharge-your-static-site/)

A deeper article based on Asynchronous plugin

- [Writing plugins for remark and gatsby-transformer-remark (part 3) | huy.dev](https://www.huy.dev/2018-05-remark-gatsby-plugin-part-3/)

A plugin based on `visit block`

- [remcohaszing/remark-mermaidjs: A remark plugin to render mermaid diagrams using puppeteer](https://github.com/remcohaszing/remark-mermaidjs)

## add plugin of `remark-admonitions`

refer: rehype

- [rehypejs/rehype: HTML processor powered by plugins part of the @unifiedjs collective](https://github.com/rehypejs/rehype)

- [elviswolcott/remark-admonitions: Add admonitions support to Remarkable](https://github.com/elviswolcott/remark-admonitions)
