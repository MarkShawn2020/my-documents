# vscode-bugfix

[toc]

## FIXED: vscode auto indent using 2 spaces

It's because the file of `.editorconfig`!

![picture 8](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1644513820228-8fa771242ad8b35a92dca099ea051f971bcef8158764eef42d8dfe11ae5c4055.png)

And I am surprised to find there are a lot of `.editorconfig`

![picture 9](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1644514000138-cd33bb79f7c6aac8828b334778a18f0f79a55f0be645f273bba0a7cd908193ed.png)

Then I changed two of them about the indent size of markdown files: `~/homebrew/.editorconfig`, and `~/.oh-my-zsh/.editorconfig`

## FIXED: `Vscode "Unable to open [file]: Unable to read file"`

I caught this error since I **create relative soft links** incorrectly.

The right way to create relative soft links is to first `cd` into the target directory, then create the relative soft links so that the target soft link can be correctly find.

Otherwise, we'd better create the absolute soft links.

> ref

- [c++ - Vscode "Unable to open [file]: Unable to read file" message when clicking on an error - Stack Overflow](https://stackoverflow.com/questions/60472084/vscode-unable-to-open-file-unable-to-read-file-message-when-clicking-on-an)

## git clone repo as workspace

It needs the vscode to have `git` pre-installed.

If you use windows, you can download the installed version from [Git - Downloading Package](https://git-scm.com/download/win); otherwise can install `git` from command line such as `brew install git` on MacOS and `sudo apt install git` on Ubuntu.

## about markdown image link not display

### be careful about soft-link

At the very beginning, I thought it's because vscode doesn't support refer to image file outside project.

But then I realized not.

The main reason is I used to create oen soft-link from `hjxh_express_match` to `erb`.

And then when I use relative reference, the path join algo would goes wrong.

### absolute path refer only works in src

And another problem is about absolute path reference.

We can see it below that the absolute reference only works when we are using html tag rather than markdown link.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1641384502297-a8a3c0593ee630c0782df35ad5927feaa90cff7e18a7dd2e127bd54400982d1f.png" width="480" />

## 1. why markdown `.ts` link rendered as a video (but cannot open, since it's not)

I first thought of disabling plugins, and it does work: the problem is owing to the plugin of `markdown extended` which recognize `.ts` as a video url since it's a `mp2s` file in general.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1640972522085-f8ee9a85475971814ae7dfa624529c97b98bcbe9364d1d7df29be3575cbbbe18.png" width="480" />

Then I tried to figure out what can be configured in `markdown extended` so that I can read my `.ts` link normally, i.e. to make it under control. But I failed since it didn't provide me even any options.

Afterwards, what the hell this plugin can do to me becomes important.

Sadly, only the `toc` feature is what I need now (update 2022-01-01 : no, actually the feature of `toc` is powered by `all in markdown`), and the other one I used is `container` while I actually used another alternative.

I came to the conclusion: uninstall `markdown extended` and install `markdown table of content` singly.

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1640973326942-79f0eba6adc0c8472b5762b21e9e503424fb7db43732a04d4ec98a345380977b.png" width="480" />

However, when I settled to use a new `TOC` plugin, I tried an one, but not satisfying, since it would change my heading, adding `<a></a>` in it, which caused my heading not readable any more, and the jump actually not work, which means it did nothing but negative work.

Meanwhile, I found not only `markdown-extended` would change the default behavior of `.ts` url render, but also another plugin would: `markdown-preview-extended`.

But luckily, I found the configuration option in it, which is really helpful.

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1640974017560-fba8fdf0ef0dabda3c584a55389b1c79fdad8c57f33b5d6d990944e9f1ab1e9f.png" width="480" />

The solution is rather easy: just to uncheck the option of `HTML5 Embed Use Link Syntax`. And you can see, there are at least two options for us to set the behavior of markdown link, one is for `![]()`, and another one for `[]()`. Since if I set a link as `![]()`, I usually recognize it as an image or so, which indicates that a `![]()` is more likely to be an `audio/video` than a `[]()`. Thanks this plugin for giving me these considerate choices.

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/vscode-bugfix-1640974045226-8f3bbff74d6d1e6b911d5fc9de83cd78b0f64549117a7a17c5212673985e283f.png" width="480" />
