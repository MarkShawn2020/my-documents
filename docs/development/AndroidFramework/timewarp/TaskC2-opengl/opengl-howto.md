# opengl howto

1. [documentation](#documentation)
2. [config `opengl | glfw | glad`](#config-opengl--glfw--glad)
3. [`glUniform*`](#gluniform)
4. [shader language](#shader-language)
   1. [FIXED: `glGetUniformLocation() returning -1 even though used in vertex shader`](#fixed-glgetuniformlocation-returning--1-even-though-used-in-vertex-shader)

## documentation

- :sparkles::sparkles::sparkles: 英文原版代码库： [JoeyDeVries/LearnOpenGL: Code repository of all OpenGL chapters from the book and its accompanying website https://learnopengl.com](https://github.com/JoeyDeVries/LearnOpenGL)

- :sparkles::sparkles::sparkles: 中文最新版教程翻译：[你好，三角形 - LearnOpenGL CN](https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/)

- :sparkles::sparkles:: 中文最新版 github 翻译： [LearnOpenGL-CN/LearnOpenGL-CN: http://learnopengl.com 系列教程的简体中文翻译](https://github.com/LearnOpenGL-CN/LearnOpenGL-CN)

- 这个人的博客很精致： [Hawkhai | 图形学笔记 -- GLSL ES 语法详解](https://blog.hawkhai.com/blog/2020/12/12/shader-OpenGL-ES-syntax#varying-%E9%99%90%E5%AE%9A%E7%AC%A6)

## config `opengl | glfw | glad`

- 配置 glad 地址： [https://glad.dav1d.de](https://glad.dav1d.de/)

ref:

- [Ubuntu 下 Clion 配置、使用 glfw,glad 开发 OpenGL 项目 · Ginger's blog](https://1-riverfish.github.io/2018/10/27/Ubuntu%E4%B8%8BClion%E9%85%8D%E7%BD%AE%E3%80%81%E4%BD%BF%E7%94%A8Glfw-Glad%E5%BC%80%E5%8F%91OpenGL%E9%A1%B9%E7%9B%AE/)

- [ubuntu16.04+glfw3+glad+glm+assimp - 知乎](https://zhuanlan.zhihu.com/p/89549290)

## `glUniform*`

ref:

1. [glUniform - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml)
2. [(1 条消息) OpenGL——glUniform1i 用法\_一梦十年-CSDN 博客\_gluniform1i](https://blog.csdn.net/mumuzi_1/article/details/62047112)

## shader language

### FIXED: `glGetUniformLocation() returning -1 even though used in vertex shader`

要保证两点：

1. 在任意一个 shader 中的定义的变量要被使用
2. !IMPORTANT: 在 `vertexShader` 中输出的变量需要在 `fragmentShader` 中使用，否则该变量就会被优化

所以我们当时碰到这个问题，是因为晓研说 `fragmentShader` 不需要，但实际是需要的。

ref:

- [c++ - glGetUniformLocation() returning -1 even though used in vertex shader - Stack Overflow](https://stackoverflow.com/questions/23319288/glgetuniformlocation-returning-1-even-though-used-in-vertex-shader)
