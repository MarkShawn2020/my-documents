## how to copy to clipboard

这篇提供了不少办法： https://stackoverflow.com/questions/3961859/how-to-copy-to-clipboard-in-vim#:~:text=In%20vim%20command%20mode%20press,and%20CMD%20%2B%20v%20to%20paste.

其中我最喜欢基于map的方案：https://stackoverflow.com/a/67890119/9422455

```vim
nnoremap Y "+y
vnoremap Y "+y
nnoremap yY ^"+y$
```

这个方案，在本地mac上测试通过，但是在公司服务器（ubuntu）上没有成功，就是没有进粘贴板，还没太明白。

## how to insert datetime

ref:

- [Insert current date or time | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Insert_current_date_or_time)