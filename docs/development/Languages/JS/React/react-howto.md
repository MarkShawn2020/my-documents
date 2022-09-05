- [`forceUpdate`](#forceupdate)
- [component and re-render](#component-and-re-render)
- [IMPORTANT ⭐️ function as hook, the async understanding](#important-️-function-as-hook-the-async-understanding)
- [get host](#get-host)
- [configure fs node](#configure-fs-node)
- [configure proxy pass](#configure-proxy-pass)
- [how to always scroll bottom](#how-to-always-scroll-bottom)

## `forceUpdate`

```ts
const [_, forceUpdate] = useReducer((x) => x + 1, 0);
// usage
<button onClick={forceUpdate}>Force update</button>;
```

ref: https://stackoverflow.com/a/59602379/9422455

## component and re-render

I came to realize it today that if I put the hook under some specific component, then when I switch the top component, the sub component would stop rendering, lose their hook data and need re-rerendering again.

<img alt="picture 43" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/react-howto-1641697284624-d357e3cba5c0b2913428cacb34ded477858c6ca1710d0721b71db58df7f7e6ab.png" />

Hence, to solve the problem, we need to consider about what level the data is sharing between components.

For example, in my programme, the console data, uploading progress should be shared across tabs, which means though the console, progress are all under the same tab, but the data needs to be across tabs.

**So the data should be defined outside the component (move out or using `redux`) then, or to be persistent (saving to file and read) then, or something others.**

## IMPORTANT ⭐️ function as hook, the async understanding

```ts
/**
 * 这里很有意思的点：
 * 1. 若写成 `setMsgs([...msgs, msg])`，则`requestReadFile`函数中只会在request函数整个结束后才会更新一次消息，并且漏掉了"selecting file"
 * 2. 若写成 `setMsgs(() => [...msgs, msg])`，则`requestReadFile`函数中`selecting file`会显示，但是等`once`结束时会覆盖它
 * 3. 只有写成 `setMsgs(msgs => [...msgs, msg])`，才会让`selecting file`和`once`都能更新并显示信息
 *
 * 分析：
 * 这背后应该是异步更新的原因~ `once`是一个异步函数，联想`redux`里的`dispatch`不难想到，它们也是用函数进行更新的，也就是：
 * f => g => h
 * @param msg
 */
const pushMsg = (msg: ConsoleItem) => {
  if (!refReadingItems.current) {
    // 没有在读取读取文件
    setMsgs((msgs) => [...msgs.slice(msgs.length === 100 ? 1 : 0), msg]);
    refScroll?.current?.doScroll();
  } else {
    // 正在读取文件
    setMsgs((msgs) => [...msgs.slice(0, msgs.length - 1), msg]);
  }
};
```

## get host

```js
// will return the host name and port, like: "localhost:3000"
var host = window.location.host;
```

https://stackoverflow.com/a/6042031/9422455

In fact, the react frontend is served on the web client, and hence can only achieve some special environments exposed by react backend, in which we can't see those variables like HOST, PORT, etc.

## configure fs node

```js
// cpponfig.js
  // Some libraries import Node modules but don't use them in the browser.
  // Tell Webpack to provide empty mocks for them so importing them works.
  node: {
    dgram: 'empty',
    fs: 'empty',
    net: 'empty',
    tls: 'empty',
    child_process: 'empty',
  },
```

- [Can't use native node modules like fs · Issue #3074 · facebook/create-react-app](https://github.com/facebook/create-react-app/issues/3074)

## configure proxy pass

```json
// package.json
"proxy":"http://localhost:5000"
```

reference: https://www.jianshu.com/p/4286eaf0425d#:~:text=%22proxy%22%3A%22http%3A//localhost%3A5000%22

## how to always scroll bottom

The main scene is a console in frontend, and we need to keep the content in this console scrolled to the bottom.

In fact, all the content may lay in one container, and then the problem simplified into how to scroll each time when new item comes into the content container.

First, how to scroll.

It's easy to do that in react just to specify a `ref` element (suppose name it as `refEle`), and call the following method:

```js
refEle.current.scrollIntoView({
  behavior: 'smooth',
  block: 'end',
  inline: 'nearest',
});
```

And keep in mind that we need to put this `relEle` to the end of the inside of the container like this: <img alt="picture 64" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640625572054-react-howto-5dd3bcef6a3d965d2b4a7b701b9642a18374fd93202c71f9d3718e77429ae930.png" width="480" />

ref:

- [reactjs - How to scroll to bottom in react? - Stack Overflow](https://stackoverflow.com/questions/37620694/how-to-scroll-to-bottom-in-react)
