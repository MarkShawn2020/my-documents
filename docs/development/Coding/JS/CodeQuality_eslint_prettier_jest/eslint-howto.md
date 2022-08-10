# eslint howto

[toc]

## `div` element with `onClick`

Although I can just attach a `onClick` method to a `div`'s property, It would cause a chain of eslint problems.

The first one is `no-static-element-interactions`, since `div` and `span` can not own 'semantic' behavior.

Then, the solution is to add a `role="button"` to make it clickable.

After then, it trigger a new eslint problem of `interactive-supports-focus`, which suggests me to add a `tabIndex` property for keyboard support.

However, I didn't intend to let my div capturing 'tab' behavior. Hence, I can add a `tabIndex=-1` to suppress it.

And next, another eslint problem of `click-events-have-key-events` occurred, which needs me to add a `aria-hidden` property.

At last, to make a `div`'s 'click' action qualified, I should change the `div` element into like this:

```jsx
<div
  onClick={requestReadFile}
  role={'button'}
  tabIndex={-1}
  aria-hidden
  // id={'upload-area'}
  // className={'flex justify-center items-center flex-col'}
  // style={{ width: 300, border: '2px dashed' }}
>{...}</div>
```

ref:

- [eslint-plugin-jsx-a11y/no-static-element-interactions.md at master · jsx-eslint/eslint-plugin-jsx-a11y](https://github.com/jsx-eslint/eslint-plugin-jsx-a11y/blob/master/docs/rules/no-static-element-interactions.md)
- [eslint-plugin-jsx-a11y/interactive-supports-focus.md at master · jsx-eslint/eslint-plugin-jsx-a11y](https://github.com/jsx-eslint/eslint-plugin-jsx-a11y/blob/master/docs/rules/interactive-supports-focus.md)
- [eslint-plugin-jsx-a11y/click-events-have-key-events.md at master · jsx-eslint/eslint-plugin-jsx-a11y](https://github.com/jsx-eslint/eslint-plugin-jsx-a11y/blob/master/docs/rules/click-events-have-key-events.md)

## Alias error

Use this will partially cause error, since the `_public` works well, while `_renderer` won't.

```json
// .eslintrc
  "settings": {
    "alias": {
        "map": [
            [ "_public", "./public" ],
            [ "_renderer", "./src/renderer" ]
        ]
      },
    "import/resolver": {
        "webpack": {
            "config": "./webpack.config.js"
        },
      }
    }
  },
```

However, if I just change the `config`'s value into `{}`, then everything goes well including `import/no-extraneous-dependencies`.

```json
// .eslintrc
  "settings": {
    "import/resolver": {
      "webpack": {
        "config": {
        }
      }
    }
  },
```

I don't know why, maybe it's a bug.

Here is my installed packages about `eslint`: <img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640339399635-eslint-bugfix-88b6064bdc55bf3495335674e1e254488ee1e239eec5324af609ac1586caddb8.png" width="480" />

Finally, I decided to give up the `xxx-webpack` choice:

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640340967469-eslint-bugfix-9f20bf6d6ac82d82634fef3e48e09adbf9bd2b77a5502bf8cbca2c33e3e0d2bd.png" width="480" />

refer:

- [Webpack alias not working · Issue #1851 · import-js/eslint-plugin-import](https://github.com/import-js/eslint-plugin-import/issues/1851)
- https://github.com/import-js/eslint-plugin-import
- https://github.com/johvin/eslint-import-resolver-alias
- https://github.com/import-js/eslint-plugin-import
