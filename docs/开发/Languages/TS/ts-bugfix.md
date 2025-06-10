# ts

1. [PASS: TS1259: Module '"path"' can only be default-imported using the 'esModuleInterop' flag](#pass-ts1259-module-path-can-only-be-default-imported-using-the-esmoduleinterop-flag)
2. [:white_check_mark: tsc not work, `tsc -b --clean` not work too](#white_check_mark-tsc-not-work-tsc--b---clean-not-work-too)
3. [:ballot_box_with_check: TS4023 error of using (Database) name from external module (pass)](#ballot_box_with_check-ts4023-error-of-using-database-name-from-external-module-pass)

## PASS: TS1259: Module '"path"' can only be default-imported using the 'esModuleInterop' flag

In my `tsconfig.json` file, there is already one flag of `esModuleInterop` set to be true.

However, this error still arises up when I use `tsc`.

## :white_check_mark: tsc not work, `tsc -b --clean` not work too

1. The most important key causing this problem(indeed: a 假象) is `outDir`, since when it is set, all the compiled files would go to there, thus gives us an illusion that nothing happened.
2. Besides, since tsc is possible to create many files, the IDE would not show there in time, you should use `reload` on the target output directory if necessary.
3. When using `tsc -b --clean`, it also concerns with the `outDir`, and only have effects on this, the one difference is that the command would delete files, but except directories, so an empty directories construct would be shown.

<img alt="picture 25" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-bugfix-1641579809565-05b4464e9e325b2a85557b5ad13fa2b166bdb35e42ed2e330fc900483c6e9460.png" />

## :ballot_box_with_check: TS4023 error of using (Database) name from external module (pass)

I am pretty a newbie to typescript so I wonder what does this error mean and how to solve it?

<img alt="picture 17" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-bugfix-1641465035835-ca290e02026061fda09c879469ce6d1e7f3a7b42d4b37b6e8c0883d3c484d86e.png" />

I tried to modify source code of `better-sqlite3`, and it works -- the error goes.

<img alt="picture 16" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-bugfix-1641464990672-b9e739cda8ce989d517d66f04d2b6b0a6ce30646a375744b314abc4a2e9f68a4.png" />

Although both circumstances would have no effect on the codes run, I do wanna run with no compile warning or errors.

And even `// @ts-ignore` can not suppress this...

<img alt="picture 18" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-bugfix-1641465253076-8c4c68e090e10b3ab58a8276efa6304e81a5c4da7d5314ba1121680f84cbd81d.png" />

If the only solution is to modify the source code of `better-sqlite3`, please do it!

And if in case I missed something, or do things not right, please correct me!

Much thanks!
