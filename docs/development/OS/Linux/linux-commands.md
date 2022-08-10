# linux common commands

## command:zip/unzip

### add file into zipped file

```sh
zip -g FILE_FROM ZIPPED_FILE_TO
```

![picture 4](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643974724220-c464b615c61181efdf667825a2858f811d63c7d7f747acb22a144e65888c8b31.png)

> ref

- [linux how to add a file to a specific folder within a zip file - Stack Overflow](https://stackoverflow.com/questions/9289734/linux-how-to-add-a-file-to-a-specific-folder-within-a-zip-file)

### list structure of zipped file

```sh
unzip -l ZIPPED_FILE
```

> ref

- [View list of files in ZIP archive on Linux - Super User](https://superuser.com/questions/216617/view-list-of-files-in-zip-archive-on-linux)

#### TODO:list structure of zipped file with limited level

## command:tar

```sh
# x: extract, f: file
tar -xf FILE

# v: verbose, logging output, careful when extracting big files, e.g. AOSP
tar -vxf FILE
```

ref:

- [How to Extract (Unzip) Tar Gz File | Linuxize](https://linuxize.com/post/how-to-extract-unzip-tar-gz-file/)

## command:find

### find and show file size

| command | sorted | has size | size is human readable |
| --- | --- | --- | --- | --- | --- | --- |
| `find . -exec ls -lh {} \;` | N | Y | Y |
| `find . -type f -exec ls -al {} \; | sort -k 5 -n | sed 's/ \+/\t/g' | cut -f 9` | Y | Y | N |
| `find -type f -exec du -sm {} \; | sort -nk1` | Y | N | Y |
| TODO: ??? | Y | Y | Y |

> sample

![picture 91](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644146425265-52c44c84a4ac041340c2069e2b1d952b385b64b67d62c34a35024f62314600a2.png)

> ref

- [shell - How sort find result by file sizes - Stack Overflow](https://stackoverflow.com/questions/22598205/how-sort-find-result-by-file-sizes/22598250)

- [unix - How do I get the find command to print out the file size with the file name? - Stack Overflow](https://stackoverflow.com/questions/64649/how-do-i-get-the-find-command-to-print-out-the-file-size-with-the-file-name)

### how to ignore case in find

```sh
find -iname
```

ref:

- [Find command: how to ignore case? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/32155/find-command-how-to-ignore-case)

### how to specify search type

Use `-type` to specify the search type (default is `c` for `file`), here I used `d` for `directory`, ref: [find type](https://man7.org/linux/man-pages/man1/find.1.html#:~:text=true%20%20Always%20true.-,%2Dtype%20c,-File%20is%20of)

And then, when I search directory, it would search all the sub-folders with '/' concatenated, so I need to specify `-d 1` in order to only search the top current directory.

```sh
➜  Application Support find . -name '*electron*' -type d -d 1
./electron-react-boilerplate
./electron-react-typescript
➜  Application Support rm -rf electron-react-boilerplate
➜  Application Support rm -rf electron-react-typescript
```

### how to exclude dir

TODO: in fact, I really can't catch why `-prune` is combined with `-o` (or)

```sh
# 1. use `-not -path`
find -name "*.js" -not -path "./directory/*"

# 2. use `-path xx -prune`
find . -path ./misc -prune -o -name '*.txt' -print

# 3. use multiple prune (need to add escaped bracket)
find . -type d \( -path ./dir1 -o -path ./dir2 -o -path ./dir3 \) -prune -o -name '*.txt' -print

# 4. use regex prune (-name)
find . -type d -name node_modules -prune -o -name '*.json' -print
```

ref:

- [linux - How to exclude a directory in find . command - Stack Overflow](https://stackoverflow.com/questions/4210042/how-to-exclude-a-directory-in-find-command)

### TODO: how to find file with time used

### tip: find efficiency comparison

Use a specified directory is the best and fastest;

If not, limit the `maxdepth` to a number small enough is also ok;

And then consider the directory prune.

Finally bared run is the worst.

```sh
➜  hjxh_express_match git:(main) time find .imgs  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find .imgs -name   0.00s user 0.00s system 52% cpu 0.005 total

➜  hjxh_express_match git:(main) time find . -maxdepth 3  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 3 -name   0.01s user 0.05s system 70% cpu 0.079 total

---

➜  hjxh_express_match git:(main) time find . -maxdepth 4  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 4 -name   0.06s user 0.69s system 87% cpu 0.854 total

➜  hjxh_express_match git:(main) time find . -maxdepth 5  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 5 -name   0.14s user 1.86s system 93% cpu 2.137 total

➜  hjxh_express_match git:(main) time find . -maxdepth 6  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -maxdepth 6 -name   0.26s user 3.21s system 94% cpu 3.683 total

---

➜  hjxh_express_match git:(main) time find .  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -name   0.44s user 5.85s system 51% cpu 12.172 total

➜  hjxh_express_match git:(main) time find . -path './.imgs/*'  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -path './.imgs/*' -name   0.46s user 5.93s system 51% cpu 12.299 total

➜  hjxh_express_match git:(main) time find . -path './.imgs/*'  ! -path "**/node_modules/*"  -name readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
./.imgs/readme-1641287704584-613d44afa250b17be45e5b366487d1dbd42939da44543700b5e7fbd7f6a8ca9e.png
find . -path './.imgs/*' ! -path "**/node_modules/*" -name   0.46s user 5.91s system 51% cpu 12.268 total

```

## command:grep

!!!tip 1. use `grep -n` rather than `grep` to get line number always! 2. the zsh/bash has done an alias for grep adding the `--color-auto` option

### only display file name

```sh
grep -l
```

ref:

- [How can I use grep to show just filenames on Linux? - Stack Overflow](https://stackoverflow.com/questions/6637882/how-can-i-use-grep-to-show-just-filenames-on-linux)

### display lines before or after or surround specific lines

```sh
# A: after
grep -A 3 XXX

# B: before
grep -B 3 XXX

# C: context
grep -C 3 XXX
```

ref:

- [15 Practical Grep Command Examples In Linux / UNIX](https://www.thegeekstuff.com/2009/03/15-practical-unix-grep-command-examples/)

### skip binary files

```sh
grep -I
```

see: - [linux - How to suppress binary file matching results in grep - Stack Overflow](https://stackoverflow.com/questions/25853722/how-to-suppress-binary-file-matching-results-in-grep)

### good articles of grep relative

> ref

- [Grep usage examples](https://queirozf.com/entries/grep-usage-examples#search-for-raw-string)

### how to match raw string

use `-F`.

!!!warning But if the raw string begins with `-`, then we need to use `-e` to force `grep` recognizing the following string as a pattern otherwise it would catch errors.

    sample:

    ```sh
    grep -F "xxx" <<< "xxxyyy"
    # ok

    grep -F -e "-xxx" <<< "-xxxxyyy"
    # ok

    grep -F "-xxx" <<< "-xxxx"
    # error
    ```

> ref

- [bash - Is there an easy way to pass a "raw" string to grep? - Stack Overflow](https://stackoverflow.com/questions/11856054/is-there-an-easy-way-to-pass-a-raw-string-to-grep)

### how to combine `grep` with `if`

using `-q`.

```sh
if  grep -q hello a.txt ; then echo yes;else echo no; fi
# yes

if grep -q word a.txt; then echo yes; else echo no; fi
# no
```

> ref

- [grep -q 用于 if 逻辑判断\_六六哥的博客-CSDN 博客\_grep if](https://blog.csdn.net/leoufung/article/details/48971557)

### how to exclude pattern

```sh
# `-v`: `--invert-match`, not match/contain specific string
grep -v XXX

# `-w`: word
# `-wv`: not match specific word
grep -wv XXX

# `-E`: extended regular script
grep -Ewv "AAA|BBB"
```

> ref

- very good: [How to Exclude in Grep | Linuxize](https://linuxize.com/post/grep-exclude/)

### how to exclude dir (`--exclude-dir=dir`)

Recent versions of GNU Grep (>= 2.5.2) provide:

`--exclude-dir=dir`

which excludes directories matching the pattern dir from recursive directory searches.

So you can do:

```sh
# exclude one dir
grep -R --exclude-dir=node_modules 'some pattern' /path/to/search

# exclude multi dirs
grep -R --exclude-dir={AAA,BBB,CCC}  xxxx
```

ref:

- [linux - How can I exclude directories from grep -R? - Stack Overflow](https://stackoverflow.com/questions/6565471/how-can-i-exclude-directories-from-grep-r)

### how to limit depth (`-maxdepth`)

```sh
find . -maxdepth 4 -type f -exec grep "11.0.0_r1" {}  \;
```

ref:

- [How to do max-depth search in ack and grep? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/111722/how-to-do-max-depth-search-in-ack-and-grep)

### tip: grep by lines context is MUCH FASTER than grep by words context, and even better for output

```sh
➜  erb git:(main) ✗ time (cat release/build/mac/皇家小虎快递分析系统.app/Contents/Resources/app/dist/main/main.js | tr ";" "\n" | grep --context=3 'fake-database')
# var n=this&&this.__importDefault||function(e){return e&&e.__esModule?e:{default:e}}
# Object.defineProperty(t,"__esModule",{value:!0}),t.isDbFinished=t.initDbUpdateResult=t.initDbInsertResult=t.DB_UPDATE_DECLINED=t.DB_UPDATED=t.DB_INSERT_DUPLICATED=t.DB_INSERT_SUCCESS=t.DB_UNKNOWN=t.DB_TIMEOUT=t.DB_TABLE_NOT_EXISTED=t.prisma=void 0
# const i=r(72298),a=`file:${n(r(71017)).default.join(i.app.getPath("userData"),"express_match.sqlite.db")}?connection_limit=1`
# process.env.DATABASE_URL=a,console.log({__dirname,rawDBPath:"file:dev.db?connection_limit=1",newDBPath:a}),t.prisma={erp:{create:()=>{console.log("fake-database: creating one")},findMany:()=>{console.log("fake-database: finding many")},upsert:()=>{console.log("fake-database: upserting one")}}},t.DB_TABLE_NOT_EXISTED="DB_TABLE_NOT_EXISTED",t.DB_TIMEOUT="DB_TIMEOUT",t.DB_UNKNOWN="DB_UNKNOWN",t.DB_INSERT_SUCCESS="DB_INSERT_SUCCESS",t.DB_INSERT_DUPLICATED="DB_INSERT_DUPLICATED",t.DB_UPDATED="DB_UPDATED",t.DB_UPDATE_DECLINED="DB_UPDATE_DECLINED"
# t.initDbInsertResult=()=>({nTotal:0,nInserted:0,nDuplicated:0,nTimeout:0,nUnknown:0,nTableNotExist:0})
# t.initDbUpdateResult=()=>({nTotal:0,nUpdated:0,nDropped:0,nTimeout:0,nUnknown:0,nTableNotExist:0})
# t.isDbFinished=e=>{let t=0
( cat  | tr ";" "\n" | grep --color=auto  --context=3 'fake-database'; )  0.20s user 0.01s system 121% cpu 0.169 total
```

```sh
➜  erb git:(main) ✗ time ( grep -iEo '.{255}fake-database.{255}' release/build/mac/皇家小虎快递分析系统.app/Contents/Resources/app/dist/main/main.js | tr ';' '\n' )
# =`file:${n(r(71017)).default.join(i.app.getPath("userData"),"express_match.sqlite.db")}?connection_limit=1`
# process.env.DATABASE_URL=a,console.log({__dirname,rawDBPath:"file:dev.db?connection_limit=1",newDBPath:a}),t.prisma={erp:{create:()=>{console.log("fake-database: creating one")},findMany:()=>{console.log("fake-database: finding many")},upsert:()=>{console.log("fake-database: upserting one")}}},t.DB_TABLE_NOT_EXISTED="DB_TABLE_NOT_EXISTED",t.DB_TIMEOUT="DB_TIMEOUT",t.DB_UNKNOWN="DB_UNKNOWN",t.DB_INSERT_SUCCESS="D
( grep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox} -iEo  t)  3.27s user 0.01s system 99% cpu 3.279 total

```

### tip: grep by negative captured group needs to use `ggrep`

Examples Given the string foobarbarfoo:

```sh
bar(?=bar)     # finds the 1st bar ("bar" which has "bar" after it)
bar(?!bar)     # finds the 2nd bar ("bar" which does not have "bar" after it)
(?<=foo)bar    # finds the 1st bar ("bar" which has "foo" before it)
(?<!foo)bar    # finds the 2nd bar ("bar" which does not have "foo" before it)
```

You can also combine them:

```sh
# finds the 1st bar ("bar" with "foo" before it and "bar" after it)
(?<=foo)bar(?=bar)
```

ref:

- [lookaround - Regex lookahead, lookbehind and atomic groups - Stack Overflow](https://stackoverflow.com/questions/2973436/regex-lookahead-lookbehind-and-atomic-groups)

```sh
grep -Pio '(?<=heads\/)(.*?)(?=\n)' text.txt # P option instead of E
```

ref: https://stackoverflow.com/a/45534127/9422455

### grep filter in/out files via `l | v | L`

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643974557449-75508ca3181f85ec0044b1cc5810b346cc73251e03d00d384a911833bd4584c9.png)

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643974532913-692eec2dec71c671c3321546be18bc319276d95bc71edde0fc99401c1d54b833.png)

> ref

- [Is 'grep -v -l' equivalent to 'grep -L'? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/339619/is-grep-v-l-equivalent-to-grep-l)

## command:tree

### 筛选文件

#### 法一：标准做法是使用`--prune -P PATTERN`

!!! warning 注意这里的 PATTERN 不是标准的正则，具体可以见`man tree`内关于`-P`的说明： `` text -P pattern List only those files that match the wild-card pattern. You may have multiple -P options. Note: you must use the -a option to also consider those files beginning with a dot `.' for matching. Valid wildcard operators are `*' (any zero or more characters), `**` (any zero or more characters as well as null /'s, i.e. /**/ may match a single /), `?' (any single character), `[...]' (any single character listed between brackets (optional - (dash) for character range may be used: ex: [A-Z]), and `[^...]' (any single character not listed in brackets) and `|' separates alternate patterns. A '/' at the end of the pattern matches directories, but not files.  ``

```text
2022/07/04 11:55:46 (base) ➜  2.0b4.0.9 git:(master) ✗ tree --prune -P "*.db" | head -n 5
.
├── 1d35a41b3adb8b335cc59362ad55ee88
│   ├── Account
│   │   └── Beta.db
│   ├── ChatSync
```

#### 法二：基于 grep

可以使用`tree -f`打印完整路径再使用 grep：

```text
2022/07/04 11:59:24 (base) ➜  2.0b4.0.9 git:(master) ✗ tree -f | grep -E "\.db$" | head -n 5
│   │   ├── ./1d35a41b3adb8b335cc59362ad55ee88/Account/Beta.db
│   │   ├── ./1d35a41b3adb8b335cc59362ad55ee88/ChatSync/ChatSync.db
│   │   ├── ./1d35a41b3adb8b335cc59362ad55ee88/Contact/wccontact_new2.db
│   │   ├── ./1d35a41b3adb8b335cc59362ad55ee88/Favorites/favorites.db
│   │   ├── ./1d35a41b3adb8b335cc59362ad55ee88/FileStateSync/filestatesync.db
```

也可以使用`find`打印完整路径再使用 grep:

```text
2022/07/04 11:59:31 (base) ➜  2.0b4.0.9 git:(master) ✗ find . | grep -E "\.db$" | head -n 5
./KeyValue/1d35a41b3adb8b335cc59362ad55ee88/KeyValue.db
./Backup/1d35a41b3adb8b335cc59362ad55ee88/A2158f8233bc48b5/Backup.db
./Backup/1d35a41b3adb8b335cc59362ad55ee88/F10A43B8-5032-4E21-A627-F26663F39304/Backup.db
./1d35a41b3adb8b335cc59362ad55ee88/solitaire/solitaire_chat.db
./1d35a41b3adb8b335cc59362ad55ee88/Stickers/stickers.db
```

也可以直接摆烂，不打印路径，从而呈现一定的文件夹结构：

```text
2022/07/04 12:00:04 (base) ➜  2.0b4.0.9 git:(master) ✗ tree | grep -E "\.db$" | head -n 5
│   │   ├── Beta.db
│   │   ├── ChatSync.db
│   │   ├── wccontact_new2.db
│   │   ├── favorites.db
│   │   ├── filestatesync.db
```

总体来看，这三者都不如法一。

### how to display chinese (`-N`)

```sh
tree -N
```

ref:

- [(23 条消息) linux 下 tree 命令中文字符乱码解决方案\_cxrsdn 的博客-CSDN 博客\_linux tree 中文](https://blog.csdn.net/cxrsdn/article/details/100006348)

### how to exclude dir(`-I`)

```sh
# use `|` to split choices

# exclude
tree -I "XXX|YYY"   # maybe it means 'ignore'
```

ref:

- [tree command for multiple includes and excludes - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/61074/tree-command-for-multiple-includes-and-excludes)

### how to change default char style

see: - ["tree" command output with "pure" (7-bit) ASCII output - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/127063/tree-command-output-with-pure-7-bit-ascii-output)

使用 `--charset` 选项：

```text
<!-- default -->
2022/07/04 11:52:36 (base) ➜  2.0b4.0.9 git:(master) ✗ tree --prune -P "*.db"
.
├── 1d35a41b3adb8b335cc59362ad55ee88
│   ├── Account
│   │   └── Beta.db
│   ├── ChatSync
│   │   └── ChatSync.db

<!-- ascii -->
2022/07/04 11:53:14 (base) ➜  2.0b4.0.9 git:(master) ✗ tree --prune -P "*.db" --charset ascii
.
|-- 1d35a41b3adb8b335cc59362ad55ee88
|   |-- Account
|   |   `-- Beta.db
|   |-- ChatSync
|   |   `-- ChatSync.db

```

## command:head/tail

### head basic usage

head 这个命令行其实没有什么要讲的，用法非常简单。

```sh
# output the first 5 lines (default)
head FILE

# output the first N lines (replace "N")
head -n "N" FILES
```

### BEST-PRACTICE: skip lines

```sh
# limit 5
| head -n 5

# skip 5
| tail -n -5

# skip 5 and limit 5
| tail -n -5 | head -n 5
```

> sample

I used this to perform a page switch action.

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644169940990-2f5bc57e556e4ce8c297fd7ce371dd96c2e5965e908e102d802da75fc52fe457.png)

> ref

- [linux - Print a file, skipping the first X lines, in Bash - Stack Overflow](https://stackoverflow.com/questions/604864/print-a-file-skipping-the-first-x-lines-in-bash)

- [sorting - Is there a way to ignore header lines in a UNIX sort? - Stack Overflow](https://stackoverflow.com/questions/14562423/is-there-a-way-to-ignore-header-lines-in-a-unix-sort)

- [Bash: Skipping lines at the top or bottom of a stream – Fabian Lee : Software Engineer](https://fabianlee.org/2020/01/18/bash-skipping-lines-at-the-top-or-bottom-of-a-stream/)

- [linux - How to skip first line of a file and read the remaining lines as input of a C program? - Stack Overflow](https://stackoverflow.com/questions/40120747/how-to-skip-first-line-of-a-file-and-read-the-remaining-lines-as-input-of-a-c-pr)

### how to exclude the last k rows

但是今天 2022-01-26 碰到了一个问题，就是要获取前 n-1 行，然后试了 stackoverflow 上的方案好像都不对。

```sh
head -n -1 FILE
```

后来才知道，是因为 mac 的原因，要用`ghead`才行……

```sh
brew install coreutils
ghead -n -4 main.m
```

而 `ghead` 是在 `coreutils` 里面，这个名字一看我就有，所以也不用装了。

ref:

- [shell - head command to skip last few lines of file on MAC OSX - Stack Overflow](https://stackoverflow.com/questions/16206507/head-command-to-skip-last-few-lines-of-file-on-mac-osx)

### discuss: use `head` or `sed`

今天之所以用到 head 其实是因为我想对一个流做 sed 处理，但略去最后一行。

我一开始想用 sed 里的范围标识（地址），但一直没试出来。

后来我把地址标识换成最简单的`1,4s/find/replace/`之后才意识到，我的思路是不对的。

`1,4`是一个确实被处理的范围选择，但结果就是，N 行中，前四行都被 sed 替换了，但是后面的行尽管没替换依旧会打印出来，而这正是 sed 的默认行为，它是一个流转换器。

那如果纯粹基于 sed，进行转换，并且去掉最后一行，就要用到`-o`结合好像是`/p`的 identifier，具体我也记不大清了。意思就是输出所有被匹配的行，但如果这样的话被匹配的行就会输出两遍了（两遍不必相同（NOT-SURE），一个是转换前，一个是转换后），所以另一个标识符就是阻止原内容的输出，这样就只输出匹配的行的处理结果。

所以，这个思路其实有问题，它可以对，也可以不对，它如果保证匹配 n-1 行，则对；否则就不满足需求了，我们的需求是处理前 n-1 行，并且不管匹配不匹配，都要输出，尽管实际上是都匹配的。

总之，理解到这层后，既可以用纯 sed 的方案，也可以用 head+sed 的方案，一个负责改，一个负责删即可，至于先后，结果都一样，也许 head 在前效率会更高一些。

所以，还是挺有意思的，这个。

## command:top

Today(2022-01-27) I finally understood how to use the command of `top` (though `htop` is better for display but possibly more costly).

![picture 88](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643248016619-b1ac7d3bcd2a9eb546a53a0e5da199d11d573f85a61a9317d679d002d98012fa.png)

I can switch the display format of memory usage when `top` has gone to the interactive interface.

The first option I can use is `E`, which allows to switch memory unit between `KiB | MiB | GiB | TiB`.

And the second option I can use is `m`, which switches the memory display type between pure text, columns graph and block graph.

> :warning:
>
> 1. 不可以在命令行中直接用 `top -M` （显示以`MB`为单位的内存使用量），因为`top -h`的帮助中写的很清楚，只支持部分选项。在 stackoverflow 上有 `top -M` 的建议(see: [linux - How to display meminfo in megabytes in top? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/105908/how-to-display-meminfo-in-megabytes-in-top))，但可能我的版本（Ubuntu 18）不支持。正确的做法，是先进入`top`交互界面，然后按`E`，这样就会切换单位，比如按两次切换到`GB`单位。另外，独立的，还可以按`m`去切换内存的显示样式，比如像`htop`那种竖条状！
> 2. 以上只在 ubuntu 上测试通过，在 mac 上我刚试了，不行！所以到底怎么用命令，还得根据平台自身！
> 3. 具体的，可以通过 `COMMAND -h`去看简洁版的帮助页面，或者`man COMMAND` (e.g. [Ubuntu Manpage: top - display Linux processes](https://manpages.ubuntu.com/manpages/bionic/en/man1/top.1.html)) 去看完整版的帮助页面！

## command:cat|tac

### reverse order of lines

```sh
| tac
```

> ref

- [How to Reverse the Order of Lines in a File in Linux | Baeldung on Linux](https://www.baeldung.com/linux/reverse-order-of-file-lines)

### how to write raw string into file using `cat`

```sh
# example
GOPATH=$HOME/my-go
cat <<EOF >> ~/.profile
export GOPATH=$GOPATH
export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
EOF
```

ref:

- [linux - How does "cat \<\< EOF" work in bash? - Stack Overflow](https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash)

### usage: how to know what's the bash string

When using `bash` or `zsh`, we are supposed to use the function of `bindKey`.

However, the key we typed are always hard to remember, e.g. what's the `ctrl` key?

Luckily, there's a super easy (and also interactive) way for us to know it via `cat`, just to type `cat` followed by `enter` in terminal, and then the terminal would display what the character would be when we typing them.

E.g. here is what's the result when we combine `control | option | command` with arrow left and arrow right would be:

![picture 114](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1643287045491-0d652ec4cf50fd00bdfe265d1bcbc4df4482ffc562e30624d26218fd2d841adf.png)

## command:zip|unzip|gunzip

### (g)unzip a gzip file

failed to unzip a gzip file(empty):

![picture 6](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644230005139-8ec53f8ed3f2ba873c2fdafb30ed57003d97f7440148f4722db8935cc41bae2b.png)

successfully (g)unzipped a gzip file(empty):

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644230034864-05ea639250d3fa8366d3a5663bb7e8bcb6b1be8a62d0ceb6343b2dc46bf8428a.png)

> ref

- [Bash – How to check if a gzipped file is empty – iTecTec](https://itectec.com/unixlinux/bash-how-to-check-if-a-gzipped-file-is-empty/)

### how to unzip to specific directory

```sh
unzip file.zip -d TARGET_DIR
```

ref:

- [bash - How to unzip into a given directory - Ask Ubuntu](https://askubuntu.com/questions/994611/how-to-unzip-into-a-given-directory)

## command:kill

```sh
 ps aux  |  grep -i  electron |  awk '{print $2}'  |  xargs sudo kill -9
```

ref:

https://stackoverflow.com/a/30486159/9422455

## command:scp

```sh
sudo chown -R USER_NAME REMOTE_FOLDER
sudo chmod 777 REMOTE_FOLDER
```

the `-R` means "recursively" since there may be file deeply in the target folder that won't allow you to write.

Hence, you can know, you can specifically claim your authority on the file or directory, since it would not automatically transfer.

Thus, a flexible approach is that just add a `-R` flag.

reference: https://unix.stackexchange.com/a/347412

## command:lsof

check status of port occupation

```sh
lsof -i:8888
```

## command:ufw

```sh
# check status
sudo ufw status

# enable
sudo ufw enable

# white list
sudo ufw allow 9000

# reload
sudo ufw reload

```

ref:

- [(20 条消息) Ubuntu 防火墙的开启，关闭，端口的打开，查看\_jiaochiwuzui 的博客-CSDN 博客\_ubuntu 查看防火墙开启的端口](https://blog.csdn.net/jiaochiwuzui/article/details/80907521)

## command:time

I can directly using `time ( COMMAND_1 | COMMAND_2 )`, so that it can calculate the final time of this pipe.

However, time calculation is a little more sophisticated than what would I have thought, refer more to: [bash - How can I time a pipe? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/364156/how-can-i-time-a-pipe/364157)

## command:tr

It's useful to split line to lines.

```sh
$ echo "111;222;333" | tr ';' '\n'
111
222
333
```

```sh
# use `nl` to add the line number
cat main.js | tr ';' '\n' | nl -ba | head -6
```

## command:cd

### usage: a superb scene using `cd .`

<img alt="picture 10" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-howto-1641284537356-d66d64fc07918dc1e98e62dd2dd70454a9ff16b2b2cc6da39fe18cbc6a5b07a1.png" width="480" />

ref:

- [linux - How do I refresh directory in BASH? - Super User](https://superuser.com/questions/702402/how-do-i-refresh-directory-in-bash)

## command:sed

> ref

- [:sparkles::sparkles::sparkles: sed, a stream editor:sparkles::sparkles::sparkles:](https://www.gnu.org/software/sed/manual/sed.html)

- [Sed - An Introduction and Tutorial](https://www.grymoire.com/Unix/Sed.html)

- [sed man page - General Commands | ManKier](https://www.mankier.com/1/sed)

a good start:

- [Sed Command in Linux/Unix with examples - GeeksforGeeks](https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/)

### how to replace a couple of files

```sh
SED_COMMAND `PIPED_FILES`
```

sample: replace all the files under a specific folder

```sh

sed -i "s/find/replace/g" `grep -rl find folder`
```

see:

- [linux sed 批量查找并替换文件夹下所有文件的内容 - sucre_tan - 博客园](https://www.cnblogs.com/sucretan2010/p/11898107.html)

### how to ignore case in sed

`/i`

see: - [sed Case Insensitive Search Matching and Replacement - nixCraft](https://www.cyberciti.biz/faq/unixlinux-sed-case-insensitive-search-replace-matching/)

### how to print only matched lines

1. `-n` means "No automatically print the each line"
2. `/p` means "Print the processed line"

```sh
# print only the matched lines
sed -n "s|find|replace|p"

# don't print any line (so useless)
sed -n "s|find|replace|"

# print all the line each, with matched line again(twice, and it's the same)
sed "s|find|replace|p"

# TODO: print the processed, and apply function on it.
```

ref:

- [regex - sed: print only matching group - Stack Overflow](https://stackoverflow.com/questions/17511639/sed-print-only-matching-group)

### :sparkles: how to increment version number

#### resolution 1: use `echo` based on `//e`

special thanks to: https://stackoverflow.com/a/14348899/9422455

#### resolution 2: answer

```sh
gsed -i -E 's|(.*)"version": "([0-9]+)\.([0-9]+)\.([0-9]+)"|echo "\1\\"version\\": \\"\2.\3.$((\4+1))\\""|e' package.json
```

> test what happened using `//pe`

```sh
➜  erb_sqlite git:(main) head -3 release/app/package.json                                                                                                                                           [7-01-22 | 4:18:17]
{
  "name": "mark.hjxh.express_match",
  "version": "0.2.2",


➜  erb_sqlite git:(main) gsed -E 's|(.*)"version": "([0-9]+)\.([0-9]+)\.([0-9]+)"|echo "\1\\"version\\": \\"\2.\3.$((\4+1))\\""|pe' release/app/package.json                                        [7-01-22 | 4:08:57]
{
  "name": "mark.hjxh.express_match",
echo "  \"version\": \"0.2.$((2+1))\"",
  "version": "0.2.3",
```

> explanation

In fact, the ` "version": "0.2.2",` is changed into `echo " \"version\": \"0.2.$((2+1))\"",`.

And then the `e` syntax indicates run this sequency string as a command, so that it finally turns into ` "version": "0.2.3",`

> attention

1. the `"` needs to be escaped, and to escape `"`, we need to use a `\`, and to let the `\` work in the `echo` function, we need to escape it again, that is to be `\\"`
2. `sed` will match all line (including the leading space), and the `e` would execute all line. So if I just replace the version number part into `echo "\\"0.2.3\\""`, then all the line would turns into ` "version": echo "\\"0.2.3\\""`, which is certainly unwanted and deserves reflection.

> core ref

[bash - How to find/replace and increment a matched number with sed/awk? - Stack Overflow](https://stackoverflow.com/questions/14348432/how-to-find-replace-and-increment-a-matched-number-with-sed-awk)

`perl | awk` alternative

- [bash - How to increment version number in a shell script? - Stack Overflow](https://stackoverflow.com/questions/8653126/how-to-increment-version-number-in-a-shell-script)

> official hack way (but I failed)

```sh
#!/usr/bin/sed -f

/[^0-9]/ d

# replace all trailing 9s by _ (any other character except digits, could
# be used)
:d
s/9\(_*\)$/_\1/
td

# incr last digit only.  The first line adds a most-significant
# digit of 1 if we have to add a digit.

s/^\(_*\)$/1\1/; tn
s/8\(_*\)$/9\1/; tn
s/7\(_*\)$/8\1/; tn
s/6\(_*\)$/7\1/; tn
s/5\(_*\)$/6\1/; tn
s/4\(_*\)$/5\1/; tn
s/3\(_*\)$/4\1/; tn
s/2\(_*\)$/3\1/; tn
s/1\(_*\)$/2\1/; tn
s/0\(_*\)$/1\1/; tn

:n
y/_/0/
```

- [sed, a stream editor](https://www.gnu.org/software/sed/manual/sed.html#Increment-a-number)

### how to match digits (`[0-9]` or `:digit:`)

> ref:

thanks for the direction to sed official documentation in this post.

- [regex - Why doesn't `\d` work in regular expressions in sed? - Stack Overflow](https://stackoverflow.com/questions/14671293/why-doesnt-d-work-in-regular-expressions-in-sed)

### how to insert text before first line of file

suppose the text is:

```text
@tailwind base;
@tailwind components;
@tailwind utilities;
```

and the file is `public/style.css`

first, export this variable for better understanding of commands:

```sh
T='@tailwind base;
@tailwind components;
@tailwind utilities;'
F='public/style.css'
```

and copy file as a backup:

```sh
cp $F ${F}_
```

then the reset command is:

```sh
cp ${F}_ $F
```

#### resolution 1: use `cat` and `;`

The `cat` approach meets our intuition, but needs a temp file.

First, we dump the `T` into `temp` file, then append `F` into temp, finally replace `F` with temp, that is:

```sh
echo $T > temp; cat $F >> temp; mv temp $F
```

Be careful about the second operator of `>>` since it means `append` otherwise the `$T` would be flushed, then `$F` keeps unchanged.

refer:

- [What are the shell's control and redirection operators? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)

#### resolution 2: use `cat` and `|`

In last solution, we used 2 ';', and there is an easy way to change it to just 1 ';'.

```sh
echo $T | cat - $F > temp; mv temp $F
```

In this solution, the `$T` echoed into second pipe, and `cat` used `-` to capture it then joined with `$F` and dumped into temp, which surely is faster.

refer:

- [linux - What does the last "-" (hyphen) mean in options of `bash`? - Super User](https://superuser.com/questions/1388584/what-does-the-last-hyphen-mean-in-options-of-bash)

- [shell - Usage of dash (-) in place of a filename - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/16357/usage-of-dash-in-place-of-a-filename)

#### resolution 3: use sed s-command

In the above 2 solutions, we both need an IO, i.e. first saving into a 'temp' file and move to override the raw file, which could be low-efficiently and not elegant.

There's a way allowing us to finish the 'join' action just in the pipe and finally leads to inplace-modify target file. That is "sed's s-command".

<img alt="picture 24" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379168300-linux-howto-90b435ef191284a35f21cb8cac698769b8548bfe2b3f90db2be5ea988a56c636.png" width="480" />

<img alt="picture 25" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379622241-linux-howto-e51b228ec26d453924d9731bc86f94185eccbc8ea4d43954698c4217845ca262.png" width="480" />

When using `s-command`, we can easily apply regex grammar to achieve what we want.

<img alt="picture 26" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640379819166-linux-howto-c717ac5a605fb416fa2f472e202a74949ed8b34c3556d06ca6b70c8202d70901.png" width="480" />

Like this, we can easily insert text in front of a sequency of text based on regex of '^', which means the beginning of text.

And then, since the basic grammar of how to insert text before specific line of an input file in `sed` is `sed -i 'Ni TEXT' $F` , the problem then converts to how to join '1i' with $T. That is what we just learned can be put into practice:

<img alt="picture 27" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640380337394-linux-howto-d8bfb544ab1b2db098a1fd9138401997b9b11814af6cbf639243453526a91c02.png" width="480" />

You see, now all the commands have nothing to do with the io, and the principle behind this command chain is straightforward: join into `1i $T` then use it as `sed -i`’s parameter (via `-f-` which is the former pipe).

#### resolution 4: use sed e-command

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375147417-linux-howto-e0475887ff34e4a4a0be217c3596e054d2bdfa01f28f360f2459123e0b2175f7.png" width="480" />

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375169955-linux-howto-57609e425971259dd89c05c571047e701cb2c44dcc4deac43b0724a7295d8f44.png" width="480" />

I'd think the e-command is quite confusing, but does good job.

I made some tests on the e-command to help myself understand.

In the above introduction, it indicates that if 'without parameters, the e command executes the command that is found in space and replace the pattern space with the output'.

suppose we have `a='aaa\necho "bbb" \nccc'`, then if we runs `echo $a | gsed '2e'`, that's to say run the second line as a command and let others stay as what they are: <img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640375663511-linux-howto-18fd2906bf27a739476740fbe2c713a3c42b40de5865cebd14c08e696ed0b39a.png" width="480" />

However, 'if a parameter is specified, instead, the e command interprets it as a command and sends its output to the output stream.'

I made an example which may help us to understand what's the mechanism of `gsed 'ne xxx`, in which `xxx` is the so-called 'parameter'.

<img alt="picture 19" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640376208972-linux-howto-5309698b6833082cf93b3b0f69cda3616678ad00d3e5141895bcec14b8684f57.png" width="480" />

You can see, as the following shows, since a is a three-line text and sent into the pipe as stream, so first line shows 'aaa', and second line shows 'echo "bbb"', as what we preset.

The most notable point is that since `gsed` sets a `3e` command which means 'it will execute following commands at 3rd row of stream'. Thus, the following commands `xxx\n echo "yyy"...` are executed as separate commands split by lines.

Obviously, neither `xxx` nor `zzz` is a valid command and turned into an error. Plus, since the level of error usually is a bit higher than normal output, the error of `zzz` came before `yyy` and then is `AAA`.

Finally, when all the commands were executed, the next stream in pipe came, i.e. `ccc`, and all the sequences came into end.

ref:

[sed e-command](https://www.gnu.org/software/sed/manual/sed.html#:~:text=by%20standard%20seds.-,e%20%5Bcommand%5D,-This%20command%20allows)

Still, we had other topics to talk about.

<img alt="picture 20" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377292421-linux-howto-27ab701a1d1cca335a1476e71b742a60b9f6817b5d08521c70c766bfae21290d.png" width="480" />

<img alt="picture 22" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377315692-linux-howto-ea510349e79dd47d4ca01d17200defcf7e8b8b8ebda0b0785c1833ba932c625d.png" width="480" />

We can know the classic usage of `sed` is `sed SCRIPT INPUTFILE`, and if `-e` option is used to specify a script, with all non-option parameters taken as input files.

So what would happen when we combine the `-e` and an input file.

Back to what we covered the above, we can move a step further now.

<img alt="picture 23" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640377647537-linux-howto-8099c8c4212b90dd4f7fa22449dc22ef8135c485c97674a561b87769121c750b.png" width="480" />

In this example, we can see that `gsed` first read one line from `../temp` file which is `AAA`, and then paused since the `2e` flag to execute `cat -` command which shows all the input stream from `echo $a`, and finally continued to read the remaining rows of `BBB` and `CCC`.

So what about if we specify a `-i` option, which means `change in position`?

It's easy to understand, that is all the output would be sent into `../temp`, so that `../temp` changes to the output just like the result in this example shows.

Hence, we can derive from our conclusion: if we use the following command:

```sh
echo $T | gsed -i '1e cat -'  $F
```

then the goal of inserting text before first line can be achieved just on the fly~

How amazing and beautiful it is!

ref:

- [gsed overview](https://www.gnu.org/software/sed/manual/sed.html#:~:text=sed%20%C2%A0%20%5BContents%5D%5BIndex%5D-,2.1%20overview,-Normally%20sed%20is)

> conclusion

G1. To insert lines at the beginning of one file:

```sh
# 1. dump, dump, and move
echo $T > temp; cat $F >> temp; mv temp $F;

# 2. join, dump, and move
echo $T | cat - $F > temp; mv temp $F;

# 3. [sed s-command] concat-string, inplace-insert
echo $T | gsed '1s/^/1i /' | gsed -i -f- $F

# 4. [sed e-command] ... hard to conclude
echo $T | gsed -i '1e cat -' $F
```

G2. To insert lines at specific line:

```sh
# 1. if text is single line, refer: https://stackoverflow.com/a/6537587/9422455
gsed -i 'Ni $T' $F

# 2. if text is multi lines, refer:
echo $T | gsed -i 'Ne cat -' $F
```

FIXME: (failed) G3. To insert content after matched position:

```sh
# 1. [sed r-command]
echo $T | gsed -i '$P/r -' $F #  the '-' is same for '/dev/stdin'
```

G4. To insert multi lines manually:

```sh
# 1, when lines are already multiplied, just add `\` after each line, refer: https://askubuntu.com/a/702693

# 2, when lines are in one, using `\n`, refer: https://askubuntu.com/a/702690
```

G5. To insert lines after matched line with the same leading space format:

> :warning: 嵌套 sed 正则注意事项
>
> 1. 输入的文本不能与分隔符相同，否则需要转义。比如本次为了在代码中加入注释`//`，就不方便用`/`当分隔符
> 2. 嵌套正则的时候，为了能分清一级与二级，可以应用不同的分隔符，比如本次更新用了`|`作为一级，`_`作为二级

```sh
# 1. [sed s-command] leading space align with $P
# failed at 2022-01-25
# echo $T | gsed 's/^.*$/s\/(^.*?)($P.*$)\/\\1\\2\\n\0\//' | gsed -E -f- $F

# updated at 2022-01-25
echo $T | gsed 's|^.*$|s_^(.*?)('$P'.*)$_\\1\\2\\n\\1\0_|' | gsed -E -f- $F | grep --context=3 $T

# FIXME: (failed) 2. [sed s-command with named-pipe] [more straightforward]
cat <(echo -n "s/(^.*?)($P.*?$)/\1\2\\\\n\1" & echo -n $T & echo -n "/") | gsed -E -f- $F
```

<img alt="picture 29" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640385997938-linux-howto-41e634caf1122f991d08d485202adfb56ab71cdfdb7d5ad76ad4f57ca751cbaa.png" width="480" />

ref:

- [shell - How do I join two named pipes into single input stream in linux - Server Fault](https://serverfault.com/questions/171095/how-do-i-join-two-named-pipes-into-single-input-stream-in-linux)

### how to replace multi-lines

use `perl`!

see: [how to use perl to replace multi-lines](#how-to-use-perl-to-replace-multi-lines)

### how to trim line

> mark: There is no `trim` command in linux, and it can be pretty easy/clear to be finished via `sed`.

```sh
| gsed -r 's/\s*(.*?)\s*$/\1/'
```

> ref

- [How do I trim lines read from standard input on bash? - Stack Overflow](https://stackoverflow.com/questions/4422491/how-do-i-trim-lines-read-from-standard-input-on-bash)

## command:perl

### only print matched lines

```sh
# 1. `-n`: not print all
# 2. `print if `: print conditional lines
perl -ne 'print if s/.*?((\d{1,3}\.){3}\d{1,3}).*/\1/'
```

> ref

- [Only print matching lines in perl from the command line - Stack Overflow](https://stackoverflow.com/questions/5098884/only-print-matching-lines-in-perl-from-the-command-line/5103270)

### how to use perl to replace multi-lines

```sh
perl -0pe 's/search/replace/gms' file
```

1. `-0`: without the `-0` argument, Perl processes data line-by-line, which causes multiline searches to fail.
2. `-p`: loop over all the lines of a file
3. `-e`: execute the following arg as a perl script
4. `/s`: changes the behavior of the dot metacharacter `.` so that it matches any character at all. Normally it matches anything except a newline "\n", and so treats the string as a single line even if it contains newlines.
5. `/m`: modifies the caret `^` and dollar `$` metacharacters so that they match at newlines within the string, treating it as a multi-line string. Normally they will match only at the beginning and end of the string.
6. `/g`: global replace(not sure)

ref:

- explaining `-0`: [Multiline search replace with Perl - Stack Overflow](https://stackoverflow.com/questions/1030787/multiline-search-replace-with-perl)

- explaining `/m | /s`: [regex - Understanding Perl regular expression modifers /m and /s - Stack Overflow](https://stackoverflow.com/questions/22962588/understanding-perl-regular-expression-modifers-m-and-s)

special thanks to: [Not sure if you know, but sed has a great feature where you do not need to use a / as the separator.](https://unix.stackexchange.com/a/378991)

- [perl man page - perl-interpreter - General Commands](https://www.mankier.com/1/perl#Description)

- [perl - Replace multi line string with multi line string without escaping by hand - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/555948/replace-multi-line-string-with-multi-line-string-without-escaping-by-hand)

- [Perl 正则表达式 | 菜鸟教程](https://www.runoob.com/perl/perl-regular-expressions.html)

- [quoting - find and replace with sed with slash in find and replace string - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/378990/find-and-replace-with-sed-with-slash-in-find-and-replace-string)

## command:xargs

### `xargs` for `cp` to copy from stdin

```sh

( $SH_GEN_FILES; $SH_GEN_DIR ) | xargs cp
```

> ref

- [cygwin - How to use cp from stdin? - Stack Overflow](https://stackoverflow.com/questions/1610089/how-to-use-cp-from-stdin)

## command:history

### how to not display the number of `history` output

```sh
# resolution 1. combine with `cut`
history | cut -c 8-

# FAILED: resolution 2. using `-w`
# it failed on my MacOS, the problem maybe corresponds with GNU version
history -w /dev/stdout
```

> ref

- [How To Display Bash History Without Line Numbers - OSTechNix](https://ostechnix.com/how-to-display-bash-history-without-line-numbers/)

## command:cut

### cut column of list from XX to YY

```sh
echo "a/b/c/d/e/f/g/" | cut -d "/" -f 3
# c

echo "a/b/c/d/e/f/g/" | cut -d "/" -f -3
# a/b/c

echo "a/b/c/d/e/f/g/" | cut -d "/" -f 3-
# c/d/e/f/g/
```

> ref

- [bash - Cut from column to end of line - Stack Overflow](https://stackoverflow.com/questions/19437199/cut-from-column-to-end-of-line)

## command:sort/uniq

### sort by column/key

```sh
sort -k X
```

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1645714473713-4a87e8b7dcc8276eb690d0ad89957bea50f32c2d7ce1ca0e981f301d7ebb39f4.png)

ref:

- [files - Sort based on the third column - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/104525/sort-based-on-the-third-column)

### drop duplicated

```sh
PIPE-LINES | sort | uniq
```

> ref

- [bash - What is the difference between "sort -u" and "sort | uniq"? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/76049/what-is-the-difference-between-sort-u-and-sort-uniq)

## command:nl

```sh
# add line number for each line of output
| nl

# format with dot
| nl -w2 -s". "
```

> sample

![picture 58](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644084555960-a0d240a985b2cb12697f1d43febc4d85fdc2a98148ddfa816f71d446bcc2c74f.png)

> ref

- [nl command in Linux with Examples - GeeksforGeeks](https://www.geeksforgeeks.org/nl-command-in-linux-with-examples/)

- [How to add line numbers in every line using shell command? - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/222218/how-to-add-line-numbers-in-every-line-using-shell-command)

### FIXME: why there is extra spaces

![picture 60](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644084903604-20480d2f455d05cb8e22ca9472a1fb64307b0f2fa9514cc21614311beed60d7d.png)

## gnu:command:rename

:::tip

1. install it first via `brew install rename`
2. it's the easiest way to use `rename`, although the `sed` and other approaches may also be helpful...
3. A more straightforward way is to use `for` script :::

```sh
# rename files of pattern "F0000*" to be "F000*"
rename s/0000/000/ F0000*

# rename files, change the `$` to be empty, 注意name和rename都要转义，并且rename里要转义两次（应该是两层正则，就像我以前写的sed的两层正则一样）
find .imgs -name "*\$*" | rename s/\\$//g
```

> sample

![picture 5](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644169348968-2e3b52bed6e0cc8dc6f892576dc934305c1dbc797ddcfce1dd832a8769db28cf.png)

> ref

- [bash - Using sed to mass rename files - Stack Overflow](https://stackoverflow.com/questions/2372719/using-sed-to-mass-rename-files)

- [shell - Pipe xargs to sed and mv command - Stack Overflow](https://stackoverflow.com/questions/59314595/pipe-xargs-to-sed-and-mv-command)

- [regex - Rename files using sed and mv - Stack Overflow](https://stackoverflow.com/questions/5671773/rename-files-using-sed-and-mv)

## mac:command:iostat

> usage

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644213659674-ed8ee263fd80547d527236a8db9bd49bda9f3ba3c5b05a05e881d7bedd542ece.png)

> sample

![picture 7](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644213617305-07f0fb441c9fca5538d89367ddbcfc4ff75e6954379aec78235ab94bf48e24f4.png)

> ref

- [macos - Monitor disk I/O for specific drive in OS X - Super User](https://superuser.com/questions/404989/monitor-disk-i-o-for-specific-drive-in-os-x)

## command:less|more|most|vim

1. `most` 适合大文本（比如 log），因为它默认不换行
2. `less` 有其他几个没有的一个功能: mark，只要按`m`加某个字母就可以打书签，然后按引号`"`再按字母就可以回去，非常快
3. `more` 很适合翻页浏览，可以敲空格直接翻页
4. 前三者都可以按`v`进入`nano`的编辑博士，我发现竟然有语法高亮
5. `vim` 因为我装了各种插件，自然是最屌的了，尤其是语法高亮

> ref

- [Differences Between more, less, and most in Linux | Baeldung on Linux](https://www.baeldung.com/linux/more-less-most-commands)

## command:echo|printf

```sh {cmd=true}
# echo with newline
echo "------\nhello"

# echo without newline
echo -n world

# printf without new line
printf "I have no new line\nhhh"

# printf to re-print current line
printf "\rThis is one"
printf "\rThis is two"
```

![picture 47](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/linux-commands-1644421602875-3f1a65a50a34d7613c9b77bcf8025649e472ae2cd30fe740f5c00f0e0e5371f2.png)

> ref

- [linux - Print something in console in the same place of the previous echo, with a sort of negative echo - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/464357/print-something-in-console-in-the-same-place-of-the-previous-echo-with-a-sort-o)

- [How To Echo Without Newline](https://www.alphr.com/echo-without-newline/#:~:text=In%20the%20case%20of%20Bash,the%20'%2Dn'%20option.)

## command:updatedb|locate

```sh
# install
sudo apt update && sudo apt install locate

# usage
sudo updatedb
locate eigen3
```

ref:

- [No updatedb or locate in Ubuntu 20. : Ubuntu](https://www.reddit.com/r/Ubuntu/comments/j71qlv/no_updatedb_or_locate_in_ubuntu_20/)
