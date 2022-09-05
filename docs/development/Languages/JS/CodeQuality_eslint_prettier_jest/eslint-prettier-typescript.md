# eslint prettier typescript

ref:

- [Install · Prettier](https://prettier.io/docs/en/install.html)
- [max-len - Rules - ESLint - Pluggable JavaScript linter](https://eslint.org/docs/rules/max-len)

## eslint - prettier difference

**use Prettier for formatting and linters for catching bugs!**

<img alt="picture 57" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640553743915-eslint---prettier---typescript-5e1406e71c2fafa81c4e2d1ac8b26fce729dff622e07b0862140d15bec0c2019.png" width="480" />

ref:

- [Prettier vs. Linters · Prettier](https://prettier.io/docs/en/comparison.html)

## eslint - prettier max-len

As the following screenshot shows, the first column (80) is the webstorm internal **visual guide**, and at the same time, the default value of prettier, eslint max-width. <img alt="picture 56" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640553374454-eslint---prettier---typescript-d7f88146f1ca5e89f84d84b9758e2371a4dfa481e5b5e00af06dff9532d28977.png" width="480" />

Now, I have set to 100 in `.eslintrc` configuration file but caused this error, telling me the problem is out of `prettier`.

But I didn't find a prettier file, then the solution to this is affirmed to be creating a prettier configuration file.
