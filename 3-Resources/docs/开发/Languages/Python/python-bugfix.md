# python bugfix

1. [FIXME: `Python is deprecating distutils.cfg`](#fixme-python-is-deprecating-distutilscfg)
2. [FIXED: `virtualenv` not work](#fixed-virtualenv-not-work)
3. [FIXED: `pip` not work](#fixed-pip-not-work)
4. [BEST-PRACTICE: move the virtual python environment then not working](#best-practice-move-the-virtual-python-environment-then-not-working)
5. [pip freeze wield path](#pip-freeze-wield-path)
6. [python virtualenv conflicts with anaconda](#python-virtualenv-conflicts-with-anaconda)

## FIXME: `Python is deprecating distutils.cfg`

> ref

- [DEPRECATION: Configuring installation scheme with distutils config files is deprecated and will no\_王驭停-CSDN 博客](https://blog.csdn.net/qq_43332010/article/details/122285805)

- [Python is deprecating `distutils.cfg` · Issue #76621 · Homebrew/homebrew-core](https://github.com/Homebrew/homebrew-core/issues/76621)

## FIXED: `virtualenv` not work

When using `pip install virtualenv`, the `virtualenv` command may not work if your `pip` is from system-wide `python`.

The best idea is to use a USER-LEVEL python, e.g:

```sh
brew install python
which python

pip install virtualenv
virtualenv -h
```

Then it may work.

## FIXED: `pip` not work

Run the following, and it would replace the old pip package with the new one.

```sh
# replace to your target python if need
# and it may be a little slow, but do work
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && python3 get-pip.py && rm get-pip.py
```

> ref

- [python - ImportError: cannot import name 'PackageFinder' - Stack Overflow](https://stackoverflow.com/questions/59887436/importerror-cannot-import-name-packagefinder)

## BEST-PRACTICE: move the virtual python environment then not working

reason:

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/python-bugfix-1643561947145-ccd01f0ff16cd596ef65b93574d405e0ddb0c7ab1297de5b64e80061f433bdd2.png)

resolution:

The activate line in `bin/activate` is not changed when the directory has moved.

So just change it to the new correct place and source it, then ok!

## pip freeze wield path

```sh
 pip list --format=freeze > requirements.txt
```

reference: https://stackoverflow.com/a/62886215/9422455

## python virtualenv conflicts with anaconda

reference: https://stackoverflow.com/a/38226816/9422455
