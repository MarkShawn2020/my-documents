# pycharm bugfix

## terminal 中的 venv-py 与 project 中的 venv-py 不同

### 问题复现

我在 A 工程中创建了一个 venv-py interpreter，at the beginning, it just runs well.

However, after when I closed this project and moved this project root to another place (i.e, changed the father structure position of the disk), my IDE couldn't recognize the project python interpreter any more.

### 解决方案

After a bit of search, I finally find a solution to this problem at: https://intellij-support.jetbrains.com/hc/en-us/community/posts/360003509599-Different-Python-version-in-Terminal-and-PyCharm-despite-using-the-very-same-venv-and-path, in which it suggests me to [delete venv directory, then create a new interpreter ](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360003509599-Different-Python-version-in-Terminal-and-PyCharm-despite-using-the-very-same-venv-and-path#:~:text=delete%20venv%20directory%2C%20then%20create%20a%20new%20interpreter)

I did accordingly, and then I managed to find it works!

here is a comparison of python path between two terminals before and after I did the 'delete and create':

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639759350204-938bc8262dfeac8e6436b3d3db29d73506d47d574e7e93822f0abc7825a92146.png" width="49%" />

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639759454502-fa2037523fcfbe6a0908189e0212e1b5af699ed84044bda3cacd112b8b22fe03.png" width="49%" />

Thanks!
