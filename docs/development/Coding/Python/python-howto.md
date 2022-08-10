# python howto

## module:log

> ref

- [python-logging 模块,程序日志模板 - 简书](https://www.jianshu.com/p/2439a27db7ae)

## module:hashlib

### md5

> implementation

```py
import hashlib

def get_md5(s):

    md5 = hashlib.md5()
    md5.update(s.encode('utf-8'))
    return md5.hexdigest()
```

> ref

- :sparkles::sparkles: 非常方便的一下全给你列出来各种加密值：[Hash 在线计算、md5 计算、sha1 计算、sha256 计算、sha512 计算 - 1024Tools](https://1024tools.com/hash)

- [hashlib - 廖雪峰的官方网站](https://www.liaoxuefeng.com/wiki/1016959663602400/1017686752491744)

## module:re

### multi-line match

In fact, the real multi-line match means:

1. allow match cross lines
2. allow `\n` to be `.`

So, there is two flags to set: `re.MULTIPLE` and `re.DOTALL` like this: <img alt="picture 82" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640714410831-python-howto-a6e3fddb60d94065878fe878967ad28066da464ebe1cb19574b0b59b7c7ad299.png" width="480" />

ref:

- [re — Regular expression operations — Python 3.10.1 documentation](https://docs.python.org/3/library/re.html#re.DOTALL)

- [python - ignoring newline character in regex match - Stack Overflow](https://stackoverflow.com/questions/52197413/ignoring-newline-character-in-regex-match)

- [python - Regular expression matching a multiline block of text - Stack Overflow](https://stackoverflow.com/questions/587345/regular-expression-matching-a-multiline-block-of-text)

- [python - What's the difference between re.DOTALL and re.MULTILINE? - Stack Overflow](https://stackoverflow.com/questions/41620093/whats-the-difference-between-re-dotall-and-re-multiline)

## module:typing

### TypedDict NotRequired VS Optional

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/python-howto-5c75c11d35acc67f67bf102a3b19e7ebc0be2dbbdc960a3efe67ddc064742270.png" width="480" />

Avoid using `NotRequired` and `Optional` <img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/python-howto-71ed352877e7d0e8bfdc221fe3fd8bf698c8e178116f654e633e18efff75712c.png" width="480" />

ref:

- [PEP 655 -- Marking individual TypedDict items as required or potentially-missing | Python.org](https://www.python.org/dev/peps/pep-0655/)

### TypedDict self-reference

Here is what I want:

```py
from typing import List, TypedDict

class TocItem(TypedDict):
    level: int
    title: str
    children: List[TocItem]

```

However, it doesn't work since one property can not fetch the outer class.

There are at least two remedies, and I recommend to add one line in the top:

```py
from __future__ import annotations
```

ref:

- [Self-reference or forward-reference of type annotations in Python - Stack Overflow](https://stackoverflow.com/questions/36193540/self-reference-or-forward-reference-of-type-annotations-in-python)

## module:virtualenv

### how to install and use virtualenv in python

```sh
# should use a local pip
pip install virtualenv

virtualenv YOUR/DIR
```

> ref

- [virtualenv - 廖雪峰的官方网站](https://www.liaoxuefeng.com/wiki/1016959663602400/1019273143120480)

- [python - Activating a virtual env not working - Stack Overflow](https://stackoverflow.com/questions/24011399/activating-a-virtual-env-not-working)

## conda

### change default startup behavior in zsh

```sh
# .zshrc
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/usr/local/anaconda3/bin/conda' 'shell.zsh' 'hook' 2> /dev/null)"
#if [ $? -eq 0 ]; then
#    eval "$__conda_setup"
#else
    if [ -f "/usr/local/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/usr/local/anaconda3/etc/profile.d/conda.sh"
    else
        export PATH="/usr/local/anaconda3/bin:$PATH"
    fi
#fi
unset __conda_setup
# # <<< conda initialize <<<
```

## how to print colorful text in terminal, mac and windows

### print in general operating system

use `termcolor`

### print in windows

```sh
pip install colorama
```

```py
from colorama import init

# call this when init, so that all the ascii color would be displayed in windows
init()
```

ref:

- [Why printing in color in a Windows terminal in Python does not work? - Stack Overflow](https://stackoverflow.com/questions/48445616/why-printing-in-color-in-a-windows-terminal-in-python-does-not-work)

## how to install specific python in mac

1. install `homebrew`
2. `brew install pyenv`
3. `pyenv install VERSION`
4. `pyenv global VERSION`

## how to print colored text to console/terminal in python

```py
from termcolor import colored

# `colored` return a `Text` object, which can be called by `print()`
text = colored('Hello, World!', 'red', attrs=['reverse', 'blink', "bold"])
print(text)
```

> :warning: 不过注意，这些彩色实现，其实都是基于 ascii 码的，也就是 `.\[\d+m`这样的一个正则字符，并且不可以被 markdown 解析渲染。因此如果不单单是往控制台输出，还想保存成文件的话，则需要做相应处理。
>
> 1. 最简单与直观的做法就是直接替换掉这些 ascii 标识，可以用`sed`很方便实现这一点，例如 `python xxx | sed -r "s|.\[\d+m||g"`。
> 2. 如果有多个输出目标，则可以考虑写两套文本生成算法，这个也比较推荐，尤其是生成 html 格式的彩色文本还是极其方便的，例如：`<p style="color: XXX">YYY</p>`
> 3. 还有一种，专属于 markdown 的 ascii 码渲染方案，基于 github 的`ascii2html`仓库，不过看 issue，貌似功能不够稳健，然后是基于 c 的，我不怎么会运行……

ref:

- A few of different solutions : [How to Print Colored Text in Python - Studytonight](https://www.studytonight.com/python-howtos/how-to-print-colored-text-in-python)
