	最近经常有打开vscode然后复制行号回cc的需求，起初是想在行号位置进行右键复制，结果我把vscode所有复制行相关的十几个插件全装了一遍，都不支持，他们基本都只支持在编辑器内右键或者用cmd+shift+P面板，我觉得这实在太无法令人接受了，于是尝试使用cc二开
	
	 ezforo 的「Copy Relative Path and Line Numbers」插件的面板描述copy with line numbers是复数，比较深得我心，所以打算基于它魔改，恰好它还有27747个安装量（仅次于yassh的28741），16个五星star，可惜它没有给出github repo的链接；无奈，我选取了qishan233的copy-path-with-line-number，它有315个安装量，1个五星star，体验也还不错
	
	二开时，我和cc研讨了复制文件行路径这个需求的一些产品设计建议，最终得出以下的产品优化方案：
	1. 插件无需支持仅复制路径选项，因为这是vscode自带（比如在文件树或者窗口tab上右键），支持后会导致右键膨胀，用户选择成本增高
	2. 要支持在行号区域、编辑区内（未选中、选中单行、选中多行）等四个场景下的右键复制动作，复制包含相对路径/绝对路径+行号的两个选项，且都处于一级菜单，极致效率
	3. 语义化上，cc说条件显示line/lines比较困难，最终给出 File:Path 的程序化描述，考虑到我们的用户肯定也有一些程序基础，我觉得make sense
	
	最后发布在了github，release成了visx供大家下载安装，暂时没有很多动力（大概要花费半小时）折腾去发布到vscode仓库，欢迎大家star、pr：https://github.com/MarkShawn2020/copy-path-with-line-number