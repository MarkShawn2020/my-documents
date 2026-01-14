# npm/yarn bugfix

## FIXME: npm i version +1 problem

### problem and background

Here: [](https://npm.taobao.org/mirrors/electron/) is a list of electron packages can install.

After you specify the `electron_mirror=https://npm.taobao.org/mirrors/electron/` in the `~/.npmrc` or via `npm config set ...`, the installation of electron would auto point to the taobao mirror.

```sh
➜  mark_keeps_learning git:(master) ✗ cat ~/.npmrc
#registry=http://npm.tuna.tsinghua.edu.cn/registry
electron_mirror=https://npm.taobao.org/mirrors/electron/
```

However, what happened is that the installation would be one version exceeds the max version if you do not specify the specified version.

For example, if you specify the electron version to be `electron: "^13.0.0"`, then the npm would scan the electron_mirror, and find the final one is `13.6.6` while try to install `13.6.7`, so that a not-found error spawns.

![picture 1](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-bugfix-1642838253858-d8d2a591339f95d05887f49cd675c699b1e78f959be21654e0dfdabf8c83d9bb.png)

![picture 2](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-bugfix-1642838398834-6285785f59473faaf7861213616536dd4cba4a9515280fe0f652c727474dd327.png)

How would it be? And how to solve this problem.

### My current solution: specify the detailed version

Specify the version available such as `electron: "13.6.6"` and I can use npm to install it correctly.

![picture 3](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/npm_yarn-bugfix-1642838585994-d65bf05c337f6b3e423796f240579965137be868190d1ea332f02f25754b1fb9.png)

However, there could be a deeper problem about my `npm` and a more reasonable approach to solving out this problem.
