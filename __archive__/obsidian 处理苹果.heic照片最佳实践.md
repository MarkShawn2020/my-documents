# obsidian 处理苹果.heic照片最佳实践

刚刚二开了 obsidian 的图片上传插件，以支持苹果格式 .heic 的图片处理，有需求的可以参考：
https://github.com/MarkShawn2020/obsidian-image-auto-upload-plugin

另外，参考我们之前的文章（ 保姆级教程 | 专业创作者都在用的 Obsidian + PicGO + 七牛云全自动工作流, https://mp.weixin.qq.com/s/xyDVwPrjbo1dAYZRXuRlxg ），如果搭配picgo的话，建议安装convert-heic插件，这样我们直接复制heic照片到obsidian时，obsidian会把图片传给picgo，经过convert-heic转成jpg，再传给自己的图床，拿回公网可访的jpg文件，如果不安装该插件则拿回的.heic后缀图片是不支持在obsidian内渲染（同样也不支持在其他平台，例如微信公众号渲染的）