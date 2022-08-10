# vim-howto

1. [BEST-PRACTICE: init/config vim](#best-practice-initconfig-vim)
   1. [vim plugin: `Vundle`](#vim-plugin-vundle)
   2. [color scheme: `monokai`](#color-scheme-monokai)
   3. [vim plugin: `file-line`: go/jump to line after name](#vim-plugin-file-line-gojump-to-line-after-name)
   4. [autocomplete support: `YouCompleteMe`](#autocomplete-support-youcompleteme)
      1. [bugfix: `No .ycm_extra_conf.py file detected. #415`](#bugfix-no-ycm_extra_confpy-file-detected-415)
   5. [Add custom input](#add-custom-input)
      1. [Add date input](#add-date-input)
      2. [Add arpara signature input](#add-arpara-signature-input)
   6. [Add edit control](#add-edit-control)
   7. [Add display control](#add-display-control)
2. [BEST-PRACTICE: diff2html](#best-practice-diff2html)
   1. [recommended html render solution of `diff2html-cli` based on `npm`](#recommended-html-render-solution-of-diff2html-cli-based-on-npm)
   2. [a simpler solution to have a look at basic html style (based on vim)](#a-simpler-solution-to-have-a-look-at-basic-html-style-based-on-vim)
   3. [gerrit render effect](#gerrit-render-effect)
      1. [under file list view](#under-file-list-view)
      2. [under file content view](#under-file-content-view)
3. [copy selected lines to clipboard](#copy-selected-lines-to-clipboard)
4. [how to delete from current position to the end of line](#how-to-delete-from-current-position-to-the-end-of-line)
5. [BEST-PRACTICE: vim force tab to be spaces (so that the git diff won't have errors)](#best-practice-vim-force-tab-to-be-spaces-so-that-the-git-diff-wont-have-errors)
6. [vim filter matched lines](#vim-filter-matched-lines)
   1. [resolution 1. just to display (no buffer)](#resolution-1-just-to-display-no-buffer)
   2. [resolution 2. write into current files](#resolution-2-write-into-current-files)
   3. [BEST-PRACTICE: resolution 3. open a new vim window](#best-practice-resolution-3-open-a-new-vim-window)
7. [vim resize height and width](#vim-resize-height-and-width)
   1. [resolution 1. use commands](#resolution-1-use-commands)
   2. [resolution 2. use mouse](#resolution-2-use-mouse)
8. [vim highlight line or column](#vim-highlight-line-or-column)
9. [vim mouse mode](#vim-mouse-mode)
10. [vimdiff](#vimdiff)
    1. [:white_check_mark: force `vimdiff` to wrap line](#white_check_mark-force-vimdiff-to-wrap-line)
    2. [TODO: vimdiff show only differences](#todo-vimdiff-show-only-differences)
11. [bookmarks](#bookmarks)
12. [files relative](#files-relative)
    1. [open other file](#open-other-file)
    2. [copy between two vim files](#copy-between-two-vim-files)
13. [how to update `vim`](#how-to-update-vim)
14. [multi-line insert under `visual mode`](#multi-line-insert-under-visual-mode)
15. [Copy-Paste in Vim](#copy-paste-in-vim)
    1. [copy paste of line](#copy-paste-of-line)
    2. [copy paste of selected](#copy-paste-of-selected)
16. [column selection](#column-selection)
17. [undo changes after file saved](#undo-changes-after-file-saved)
18. [search for selected text](#search-for-selected-text)
19. [BEST-PRACTICE: fold(collapse) and unfold(expand)](#best-practice-foldcollapse-and-unfoldexpand)

## BEST-PRACTICE: init/config vim

### vim plugin: `Vundle`

ref:

- [VundleVim/Vundle.vim: Vundle, the plug-in manager for Vim](https://github.com/VundleVim/Vundle.vim#about)

### color scheme: `monokai`

```sh
mkdir -p ~/.vim/colors
curl https://raw.githubusercontent.com/sickill/vim-monokai/master/colors/monokai.vim > ~/.vim/colors/monokai.vim

echo "syntax enable
colorscheme monokai" >> ~/.vimrc
```

ref:

- [sickill/vim-monokai: Monokai color scheme for Vim converted from Textmate theme](https://github.com/sickill/vim-monokai)

### vim plugin: `file-line`: go/jump to line after name

```vim
Bundle 'bogado/file-line'
```

ref:

- [bogado/file-line: Plugin for vim to enabling opening a file in a given line](https://github.com/bogado/file-line)

### autocomplete support: `YouCompleteMe`

```sh
# !IMPORTANT: config proxies for installing YouCompleteMe
PROXY=http://localhost:7890
HTTP_PROXY=$PROXY
HTTPS_PROXY=$PROXY
GOPROXY=$PROXY
NPM_CONFIG_PROXY=$PROXY
NPM_CONFIG_REGISTRY=http://registry.npmmirror.com

# mac only, or installing `macvim`
    brew install python # !IMPORTANT: change default python to be python3 under `/usr/local/bin` instead of python2 under `/usr/bin`, if it doesn't work with `python -V`, resetting `$PATH` may be helpful!

# linux only
    sudo apt install -y build-essential cmake vim-nox python3-dev
    sudo apt install -y mono-complete golang nodejs default-jdk npm

git clone https://github.com/ycm-core/YouCompleteMe ~/.vim/bundle/YouCompleteMe
cd ~/.vim/bundle/YouCompleteMe
git submodule update --init --recursive

python3 install.py --all --verbose

echo "Bundle 'ycm-core/YouCompleteMe'" >> ~/.vimrc
```

ref:

- [ycm-core/YouCompleteMe: A code-completion engine for Vim](https://github.com/ycm-core/YouCompleteMe#linux-64-bit)

- [VIM and Python – A Match Made in Heaven – Real Python](https://realpython.com/vim-and-python-a-match-made-in-heaven/)

- [YouCompleteMe unavailable: requires Vim compiled with Python (3.6.0+) support - Stack Overflow](https://stackoverflow.com/questions/65413685/youcompleteme-unavailable-requires-vim-compiled-with-python-3-6-0-support)

#### bugfix: `No .ycm_extra_conf.py file detected. #415`

problem: 用`vim`打开某个 C++文件时，最底部会有一行红的报错，提示`No .ycm_extra_conf.py file detected.`（但又不影响代码阅读，因为代码还是高亮的），然后操作鼠标或者键盘后，该行又消失。

resolution: 搜了一下，重新“安装”一下`YouCompleteMe`就好。

```sh
cd ~/.vim/bundle/YouCompleteMe
python3 install.py
```

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1644388458337-f8ebae2b904d32015e4ba9e346d1e8fbc69c176cc64e8021664c7988f7954b80.png)

see: - [No .ycm_extra_conf.py file detected. · Issue #415 · ycm-core/YouCompleteMe](https://github.com/ycm-core/YouCompleteMe/issues/415)

### Add custom input

#### Add date input

```vim
" https://stackoverflow.com/questions/56052/best-way-to-insert-timestamp-in-vim
nmap <F3> i<C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR><Esc>
imap <F3> <C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR>
```

#### Add arpara signature input

```vim
nmap <F3> i<C-R>=strftime("ARPARA:markshawn@%Y/%m/%d: ")<CR><Esc>
imap <F3> <C-R>=strftime("ARPARA:markshawn@%Y/%m/%d: ")<CR>
```

### Add edit control

```vim
filetype plugin indent on
" show existing tab with 4 spaces width
set tabstop=4
" when indenting with '>', use 4 spaces width
set shiftwidth=4
" On pressing tab, insert 4 spaces
set expandtab
```

ref:

- [whitespace - Tab key == 4 spaces and auto-indent after curly braces in Vim - Stack Overflow](https://stackoverflow.com/questions/234564/tab-key-4-spaces-and-auto-indent-after-curly-braces-in-vim)

### Add display control

```vim
" show tabs as characters
set list
```

ref:

- [whitespace - Displaying tabs as characters - Vi and Vim Stack Exchange](https://vi.stackexchange.com/questions/422/displaying-tabs-as-characters)

## BEST-PRACTICE: diff2html

ref: - [diff to html (diff2html) program - Stack Overflow](https://stackoverflow.com/questions/641055/diff-to-html-diff2html-program)

### recommended html render solution of `diff2html-cli` based on `npm`

ref: - [rtfpessoa/diff2html-cli: Pretty diff to html javascript cli (diff2html-cli)](https://github.com/rtfpessoa/diff2html-cli#readme)

```sh
# Step 1. install `diff2html-cli` based on `npm` (`npm` required)
npm i -g diff2html-cli

# Step 2. render

## usage 1. render `xxx.diff` file into temp file (auto open default)
FILE=xxx.diff
diff2html -i file -- $FILE

## usage 2. render `xxx.diff` file into local file (not auto open default)
FILE=xxx.diff
diff2html -i file -F $FILE.html -- $FILE
```

![picture 50](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642675231088-d30a62d110fb0f0941d0d8601182a9bc03a20b621d16fa7e10742ab4b990eb9e.png)

### a simpler solution to have a look at basic html style (based on vim)

```sh
FILE=xxx.diff
vim $FILE -c TOhtml -c ":saveas $FILE.vim.html" -c ":q" -c ":q"
```

![picture 49](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642675209354-2e7dee06903ff88753afee04849e1005761cecd00fdc928f84d62af78aec152d.png)

### gerrit render effect

#### under file list view

![picture 51](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642675340233-6864034ff6f2350ff6f70471f8b4dd7b24cf18cf68d405a5d9e978076e0df1d0.png)

ref: - [Change Ia9f7b656: merge from rk3399 | 192.168 Code Review](http://192.168.0.241:8080/#/c/479/)

#### under file content view

![picture 53](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642675389288-10245b48415620d42efb6e4edfbb25b00b8dbfd14fb38da334bf4c357cd3df58.png)

!!!tip Drawbacks of viewing diff on gerrit: 1. there is bug to scroll the page and affects the experience deeply. 2. since the list and the content view are separate, you need to manually switch between files, which is inflexible, comparing to the `diff2html-cli` solution of [recommended html render solution of `diff2html-cli` based on `npm`](#recommended-html-render-solution-of-diff2html-cli-based-on-npm)

ref: - [SurfaceFlinger.h | 192.168 Code Review](http://192.168.0.241:8080/#/c/479/1/services/surfaceflinger/SurfaceFlinger.h)

## copy selected lines to clipboard

In my mac, I can use `shift + V` then `:w !pbcopy`, but I found it invalid in ubuntu.

After a little search, I am suggested to install `xclip` and then I can use `shift + V` then `:w !xclip`.

TODO: Also, it introduced the GNU vim for ease, which deserves me to have a try 【允许我 yank 到全局剪切板，这样我按 y 就有了】.

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1644486762380-fdca0792afe1a0ca1626be95b18eb639cf2556f6528fb9106a24957f7b0b9f0d.png)

see:

- [How to copy selected lines to clipboard in vim - Stack Overflow](https://stackoverflow.com/questions/9166328/how-to-copy-selected-lines-to-clipboard-in-vim#:~:text=Press%20Shift%20v%20to%20enter%20visual%20mode.,-Press%20%E2%86%93%20to&text=Press%20Ctrl%20c%20to%20copy,system%20clipboard%20text%20to%20vim.)

- [How can I copy text to the system clipboard from Vim? - Vi and Vim Stack Exchange](https://vi.stackexchange.com/questions/84/how-can-i-copy-text-to-the-system-clipboard-from-vim)

## how to delete from current position to the end of line

```sh
# resolution 1. general
d$

# resolution 2. synonym
D
```

> ref

- [vim - Delete from cursor to end of line in `vi` - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/4415/delete-from-cursor-to-end-of-line-in-vi)

## BEST-PRACTICE: vim force tab to be spaces (so that the git diff won't have errors)

```vim
" ref: https://vim.fandom.com/wiki/Converting_tabs_to_spaces
" ref: https://stackoverflow.com/questions/234564/tab-key-4-spaces-and-auto-indent-after-curly-braces-in-vim
filetype plugin indent on
:set expandtab
:set tabstop=4
:set shiftwidth=4
```

## vim filter matched lines

ref:

- [search - How to show only matching lines? - Vi and Vim Stack Exchange](https://vi.stackexchange.com/questions/2280/how-to-show-only-matching-lines)

### resolution 1. just to display (no buffer)

```vim
:g/PATTERN
```

### resolution 2. write into current files

```vim
" `m` means move, `0` means the head
:g/PATTERN/m0

" `$` means the end
:g/PATTERN/m$
```

### BEST-PRACTICE: resolution 3. open a new vim window

```vim
" 1. `%` means the current file, other files are also supported
" 2. this command would open matched lines in a new vim window (hidden)
:vim PATTERN %

" 1. `cw` is short for `cwindow`
" 2. it means to open the vim window
" 3. close the window via `cclose` or `ccl` for short
" 4. reopen the closed window via `cw` again
" 5. switch between window via `ctrl + w` then input arrow keys
:cw
```

## vim resize height and width

### resolution 1. use commands

```vim
" set the height to be 20 rows
:resize 20

" set the height to be 5 rows more
:resize +5

" set the height to be 10 rows less
:resize -10

" reset the height, i.e. set the hight to be highest possible
:resize "highest possible"

FIXME: set the width (the following one not work)
:vertical resize 10
```

ref:

- [Resize splits more quickly | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Resize_splits_more_quickly#:~:text=To%20increase%20a%20window%20to,%2C%20use%20Ctrl%2Dw%20%7C%20.&text=In%20Gvim%20and%20vim%20in,it%20into%20the%20desired%20direction.)

### resolution 2. use mouse

```vim
:set mouse=n
:set ttymouse=xterm2
```

And then we can hold on the split edge using mouse, and drag it to resize.

> :sparkles: 这一点，就跟我当初做字幕网时思考的东西是一样的！

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1643510848559-46acbe9ae140b87fa1332bbee7325c9c908241dd17a2171453d1c9a7de252eec.png)

ref:

- [How do I change the current split's width and height? - Vi and Vim Stack Exchange](https://vi.stackexchange.com/questions/514/how-do-i-change-the-current-splits-width-and-height)

## vim highlight line or column

> :sparkles:
>
> 1. `ctermXX`, the another type is `gui`(vim started via `gvim`), `cterm` controls what behaviors like in a vim started by terminal
> 2. to highlight column is similar to line, just to change the `cursorline` to be `cursorcolumn`

```vim
:hi cursorline ctermbg=darkgreen
```

1. `:hi` means highlight
2. `cursorline` means the line where the cursor is, so that `:hi cursorline` means to highlight an entire line
3. `ctermbg`, controls the background color, the general color string is supported, and my favorite one is `darkgreen`

ref:

- [Highlight current line | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Highlight_current_line#:~:text=Simply%20putting%20%3Aset%20cursorline%20in,highlight%20as%20the%20cursor%20moves.&text=With%20the%20default%20backslash%20leader,scrolling%20in%20a%20large%20file.)

- [How to control/configure vim colors | alvinalexander.com](https://alvinalexander.com/linux/vi-vim-editor-color-scheme-syntax/)

- [vim - what is the difference between cterm color and gui color? - Stack Overflow](https://stackoverflow.com/questions/60590376/what-is-the-difference-between-cterm-color-and-gui-color)

## vim mouse mode

```vim

" normal mode, 只支持鼠标点选切换焦点，不支持拖选区域，不支持系统自带右键
set mouse=n

" visual mode, 不支持鼠标点选切换焦点，支持拖选区域，支持系统自带右键
set mouse=v

" insert mode, 测试下来同visual mode
set mouse=i

" nvi mode, 支持鼠标点选（立即切换焦点），支持拖选区域（基于新的焦点为起点或终点），不支持系统自带右键
set mouse=nvi

" all mode, 测试下来同nvi
set mouse=a
```

> :sparkles: 推荐在 vim 中用`:h mouse`这种命令打开帮助菜单，显示效果很友好的，如图： ![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1643504466441-ff5610fc4bf38095afcb08f2a2c89fc8a90e6228faf9a7f190e905b3af99e240.png)

ref:

- [Using the mouse for Vim in an xterm | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Using_the_mouse_for_Vim_in_an_xterm)

## vimdiff

### :white_check_mark: force `vimdiff` to wrap line

```vim
au VimEnter * if &diff | execute 'windo set wrap' | endif
```

ref:

- [vim - Forcing vimdiff to wrap lines? - Stack Overflow](https://stackoverflow.com/questions/16840433/forcing-vimdiff-to-wrap-lines)

### TODO: vimdiff show only differences

ref:

- [vimdiff / vim -d -- how to show only the differences and fold all identical lines? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/352199/vimdiff-vim-d-how-to-show-only-the-differences-and-fold-all-identical-line)

- [rickhowe/diffchar.vim: Highlight the exact differences, based on characters and words](https://github.com/rickhowe/diffchar.vim)

## bookmarks

```vim
" show all the marks (in normal mode)
:marks

" add mark (in normal mode)
mX

" jump mark (in normal mode)
`X

" delete marks (in normal mode, based on basic regex)
:delm X   " delm: delete marks

" clear all marks
:delmarks A-Z0-9
```

> usage

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1644488214846-29bd1b2b5195b21836c4920d0edd63d85f25209f91c0ff2f35203b4569372614.png)

see:

- [How To Add Bookmarks Inside Vim Editor](https://www.thegeekstuff.com/2009/02/how-to-add-bookmarks-inside-vi-and-vim-editor/)

## files relative

### open other file

```vim
" open new file from current file
:e FILE_PREFIX<TAB>

" list buffer files
:ls

" choose next buffer file
:bn  " bn: buffer next
```

see:

- [vi - How to effectively work with multiple files in Vim - Stack Overflow](https://stackoverflow.com/questions/53664/how-to-effectively-work-with-multiple-files-in-vim#:~:text=You%20can%20say%20%3Atabe%20%5Bfilename,Vim%20even%20has%20graphical%20tabs.)

### copy between two vim files

```vim
:e ANOTHER_FILE (auto-complete support)
```

ref:

- [vim - Copy and paste content from one file to another file in vi - Stack Overflow](https://stackoverflow.com/questions/4620672/copy-and-paste-content-from-one-file-to-another-file-in-vi)

## how to update `vim`

ref:

- [What is the command in the terminal to update Vim on Ubuntu? - Ask Ubuntu](https://askubuntu.com/questions/406111/what-is-the-command-in-the-terminal-to-update-vim-on-ubuntu)

## multi-line insert under `visual mode`

1. `ctrl + v` into 'visual block' mode
2. `shift + i` into 'visual block insert' mode
3. input whatever I want (while only can see the realtime effect on first line)
4. `ESC` mark the modification has been done
5. `Enter` make the modification work

ref: recommend

- [vim Tutorial => Insert text into multiple lines at once](https://riptutorial.com/vim/example/7301/insert-text-into-multiple-lines-at-once)

## Copy-Paste in Vim

### copy paste of line

```vim
# copy line (yank)
y

# cut line (delete)
d

# paste after cursor (small case)
p

# paste before cursor (upper case)
P
```

### copy paste of selected

```vim
# select word (small case)
v

# select whole line (upper case)
V

# block(rectangular) select
ctrl + v

```

more:

<img alt="picture 8" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640781801735-vim-howto-50dab5236eb50be3b5fa4f5ebe77788a4b069e631f70cd1107b5a692f7605b6d.png" width="480" />

> - [Copy, cut and paste | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Copy,_cut_and_paste)

- [meaning - Why does yank in vim mean copy? - English Language Learners Stack Exchange](https://ell.stackexchange.com/questions/14632/why-does-yank-in-vim-mean-copy)

## column selection

Vim Tip: Select Column Put cursor and beginning of text to select. Press **\<CTRL-V\>** to begin select of the column. When you reach the end of your select, type '**\<c\>** ' Type the new text. Note that this will only replace the first instance. Now hit **\<ESC\>** . All the text has been changed!

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640059460709-f67e7df1ab803b82453f6627d0ffcdf9292473d17cc2beb7b9a4a28a1d310951.png" width="480" />

ref:

https://sethmason.com/2007/09/27/vim-tip-select-column.html

## undo changes after file saved

There's persistent undo option in vim, :h persistent-undo Note: It was introduced in VIM 7.3 version, so for earlier versions, it will not work.

It can be turned on by placing following text in your `.vimrc`:

```vim
if has('persistent_undo')      "check if your vim version supports it
  silent !mkdir -p ~/.vim/undo
  set undofile                 "turn on the feature
  set undodir=$HOME/.vim/undo  "directory where the undo files will be stored
  endif
```

Note: Before enabling this option, whatever that was lost, remains lost. After enabling the option, you will be able to do subsequent undo/redo on whatever was added/deleted after enabling the option.

ref:

- [Vim undo: undo changes after file write - Stack Overflow](https://stackoverflow.com/questions/17936130/vim-undo-undo-changes-after-file-write)

## search for selected text

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1644419465555-edb2f35cbc0cb33369d80aa40b1e651236b790eaf2649a04ef971643d3bc2746.png)

see:

- [How to search for selected text in Vim? - Super User](https://superuser.com/questions/41378/how-to-search-for-selected-text-in-vim)

## BEST-PRACTICE: fold(collapse) and unfold(expand)

```vim
"~/.vimrc

set foldmethod=indent
set foldlevel=1
set foldclose=all
```

In-file Controls:

```yaml
zo: opens folds
zc: closes fold
zm: increases auto fold depth (collapse more)
zr: reduces auto fold depth (show more words)
zR: not fold (show the most words)
```

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vim-howto-1644419939860-514fca6230d26dbf50ebd84e81494241827fbacf78a6cea01c380fbd3e9360c0.png)

> ref

- [folding - Fold function in vim - Stack Overflow](https://stackoverflow.com/questions/2362914/fold-function-in-vim)

- [Folding | Vim Tips Wiki | Fandom](https://vim.fandom.com/wiki/Folding)
