# regex-howto

- [lookahead / lookbehind](#lookahead--lookbehind)
  - [conclusion](#conclusion)
  - [detail](#detail)

## lookahead / lookbehind

### conclusion

```sh

A(?=B)  # positive lookahead
A(?!B)  # negative lookahead

(?<=A)B # positive lookbehind
(?<!A)B # negative lookbehind

```

So, the `=` means positive, and the `!` means negative, the `?` means look, the `<` means back.

ref:

- [lookaround - Regex lookahead, lookbehind and atomic groups - Stack Overflow](https://stackoverflow.com/questions/2973436/regex-lookahead-lookbehind-and-atomic-groups)

### detail

I want to match the url in the image tag, but except those online ones.

There are quite a lot ways to help me finish this.

For example, I first matched an img, and extract the url, then test if the url starts with `http`.

But it's a bit slow, and needs a little more codes. (i.e. not atomic)

I also came up with an 折中的 idea, i.e. just to match those start with '.', which indicates a local url.

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/regex-howto-1641481848735-da3cba87127642a07899bfd8ff28099fd6b3ce8ddb5d288bec6c64d8115b988b.png" />

However, I want a step further.

I know then it's so-called lookahead or lookbehind.

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/regex-howto-1641481913666-09b0273a2affd25e0a506a295b407c753d21923024e07e95b4b0d09e79d0f10d.png" />

So I did a quite hard search, and finally I derived my answer from here:

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/regex-howto-1641481976244-17bf47ac15cd5d173964bdc0b150e47520a99cdaecd6dabfb6e9aacfce663d85.png" />

And then I am surprised to find what I wanna to realize can be easily finished via `look-ahead` based on `src="` rather than `look-behind` based on a `ANYTHING`.

How 巧妙的 this is!

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/regex-howto-1641481602130-279ac258672698cf3433101191c25b323bf9e4eb463d0b33969196a4e5ba362b.png" />

core ref:

- [regex101: build, test, and debug regex](https://regex101.com/r/9jSpQ2/1)

Thanks for YuanHao

- [正则表达式：可读性是什么？能吃吗？ – 小麦冬](http://www.xiaomaidong.com/?p=426)

- [regex - RegExp matching string not starting with my - Stack Overflow](https://stackoverflow.com/questions/2116328/regexp-matching-string-not-starting-with-my)

- [pcre - RegEx for combining "match everything" and "negative lookahead" - Stack Overflow](https://stackoverflow.com/questions/55881745/regex-for-combining-match-everything-and-negative-lookahead?noredirect=1&lq=1)

ref:

it seems ok but indeed not.

- [Regex match string not starting with - Stack Overflow](https://stackoverflow.com/questions/46162605/regex-match-string-not-starting-with/46162688)

- [Regular Expressions Reference Table of Contents](https://www.regular-expressions.info/refflavors.html)

A detailed tutorial of a professional regex website

- [Regex Tutorial - Lookahead and Lookbehind Zero-Length Assertions](https://www.regular-expressions.info/lookaround.html)

- [無聊技術研究: RegExp 應用： lookahead , lookbehind](http://darkk6.blogspot.com/2017/03/regexp-lookahead-lookbehind.html)

- [Regex to match not start of line - Stack Overflow](https://stackoverflow.com/questions/6451452/regex-to-match-not-start-of-line)

- [regex - Regular expression for a string that does not start with a sequence - Stack Overflow](https://stackoverflow.com/questions/899422/regular-expression-for-a-string-that-does-not-start-with-a-sequence)
