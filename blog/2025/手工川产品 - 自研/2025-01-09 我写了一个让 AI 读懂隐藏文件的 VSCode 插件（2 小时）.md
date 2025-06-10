

今天跟大家分享一个有趣的开发经历，用了两小时写了个小插件，解决了 AI 编程时的一个烦恼。

> - 代码： https://github.com/markshawn2020/vscode-index-hidden-files
> - VSCode Marketplace（支持 VSCode、Cursor）： https://marketplace.visualstudio.com/items?itemName=markshawn2020.vscode-index-hidden-files
> - Open VSX Registry（支持 Windsurf）： https://open-vsx.org/extension/markshawn2020/vscode-index-hidden-files

## 问题的由来

事情是这样的——今早我正在用 Windsurf 开发项目，架构设计需要使用 `.` 开头的隐藏文件夹。

当然，这其实是个老大难问题，之前就有朋友问过我，只不过一直没去研究。

![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250109083712.png)


今早恰好有心情，心想要不解决一下，先是配了各种 `exclude` ，发现不行，查阅[文档](https://docs.codeium.com/context-awareness/local-indexing)后发现，Windsurf 的索引引擎默认会忽略：

- `gitignore` 中指定的路径
- `node_modules` 中的文件
- 以 `.` 开头的隐藏路径

这就意味着，隐藏文件夹里的代码无法被正确索引，AI 也就无法理解这部分上下文了。

但调试时我发现一个有趣的现象：只要文件被打开过，就会自动纳入索引范围。这个发现让我灵光一闪——如果有个工具能自动批量打开再关闭文件，岂不是可以曲线救国？

## 两小时开发之旅

有了这个想法，我立刻着手开发一个 VSCode 插件。在 AI 的协助下，选择了最直观的交互方式：在文件导航栏右键唤起功能。整个过程异常顺利，很快实现了核心功能：

- 🔍 递归扫描目录下的全部文件
- 📖 自动打开并关闭文件（带进度提示）
- ⚡ 支持配置打开延迟
- 🚫 智能过滤不需要索引的文件

下图可以看到，一开始我们 at 后是无法检索到 `.idea` 文件夹的，但是我们右键选中 `Index...`后，它就会快速地遍历打开所有子文件并关闭，完了，再 at 就可以检索了，神奇吧！

![Screen Recording 2025-01-09 at 06.55.00.gif](https://poketto.oss-cn-hangzhou.aliyuncs.com/Screen%20Recording%202025-01-09%20at%2006.55.00.gif)


## 技术细节

插件的核心逻辑其实很简单：

```typescript
// 递归扫描目录
async function* walkDirectory(dir: vscode.Uri): AsyncGenerator<vscode.Uri> {
  const files = await vscode.workspace.fs.readDirectory(dir);
  for (const [name, type] of files) {
    const uri = vscode.Uri.joinPath(dir, name);
    if (type === vscode.FileType.Directory) {
      yield* walkDirectory(uri);
    } else {
      yield uri;
    }
  }
}

// 打开并关闭文件
async function indexFile(uri: vscode.Uri) {
  const doc = await vscode.workspace.openTextDocument(uri);
  await vscode.window.showTextDocument(doc, { preview: true });
  await new Promise(r => setTimeout(r, 100)); // 短暂延迟
  await vscode.commands.executeCommand('workbench.action.closeActiveEditor');
}
```

## 一点思考

开发这个小插件让我有几点感悟：

1. 解决问题不一定要硬刚，找个巧妙的迂回路线反而更高效
2. AI 确实能大大提升开发效率，尤其是在快速验证想法的阶段
3. 很多看似复杂的问题，往往都有相对简单的解决方案


未来优化：

- 更精细的文件类型过滤配置
- 更友好的进度展示
- 自定义索引策略

## 上周更新

12 月 31 号我发布了 [Oh My Commit](https://oh-my-commit.github.io/changelog/) 插件第一版，今天同步发布第二版，欢迎大家感兴趣地下载使用：


![image.png](https://poketto.oss-cn-hangzhou.aliyuncs.com/20250109084453.png)

