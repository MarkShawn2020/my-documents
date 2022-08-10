# clion howto

## FIXED: `file does not belong to any project target, code insight features might not work properly`

### resolution 1. mark project dir as sources and headers

1. ` Mark directory as | Library Files/Project Sources and Headers.`
2. restart IDE!

ref:

- [c++ - In CLion, header only library: file "does not belong to any project target, code insight features might not work properly" - Stack Overflow](https://stackoverflow.com/questions/46245738/in-clion-header-only-library-file-does-not-belong-to-any-project-target-code)

- [this file does not belong to any project 解决 - 知乎](https://zhuanlan.zhihu.com/p/138557224)

### BEST-PRACTICE: resolution 2. reset cache and build

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/clion-howto-1645109229853-d82751b03f172c6125bc1f92b7ff4d7c0a5d1095d9c7584af9487b06193df670.png)

## how to jump to implementation from virtual interface

1. double click the world (for selection)
2. `Ctrl + N` to trigger the `Generate` action, and we can see a list of all the implementations.

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/clion-howto-1644609201736-8d892efc7790d3c0810a7f9b0fb4914ef9671d77e9fa9649994175c6deeff52d.png)

see: - [Implement functions | CLion](https://www.jetbrains.com/help/clion/implementing-methods-of-an-interface.html#file_template)
