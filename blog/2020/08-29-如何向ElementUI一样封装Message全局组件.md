
## 需求分析

我首先使用`Element-UI`完成了一个头像和登录框的设计，当我点击头像的时候，就会跳出一个登录框，它通过读取`vuex`进行一些登录注册相关的操作。

但这仅仅是一个独立的组件，我可以把我的头像放在任意的页面中，当我点击头像，登录框就会弹出。

现在的需求是，我将在一个新的位置调取登录框，比如在用户未登录的情况下触发评论系统。这意味着，登录将会有新的逻辑，比如点击某个地方，然后跳出登录框。

虽然这依旧可以通过局部组件实现，就像头像与登录框的互动一样，但难免麻烦。因为我们已经注意到，这个登录框有复用的价值。

既然`Element-UI`的弹窗可以通过`.$elert | .$message`等方法便捷地实现，我们为什么不也试着实现一个类似的呢？

## 代码分析

在本地的工程项目中导航到安装的`element-ui`，如下所示。

![image-20200824103134434](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/typora/typora-user-images/image-20200824103134434.png)

<tip>或者也可以通过直接下载`element-ui`源代码进行查看。</tip>

经过分析，`element-ui`的`js`代码是在`packages`文件夹下，我们打开`node_modules/element-ui/packages/message/src/main.js`对`message`全局组件进行分析。

### UI 组件分析

第二行导入`Main`UI 组件，即`Message`。

```js {2}
import Vue from 'vue';
import Main from './main.vue';
import {PopupManager} from 'element-ui/src/utils/popup';
import {isVNode} from 'element-ui/src/utils/vdom';
```

我们简单看一下`Message`的 UI 组件。

```html
<template>
  <transition name="el-message-fade" @after-leave="handleAfterLeave">
    <div
      :class="[
        'el-message',
        type && !iconClass ? `el-message--${ type }` : '',
        center ? 'is-center' : '',
        showClose ? 'is-closable' : '',
        customClass
      ]"
      :style="positionStyle"
      v-show="visible"
      @mouseenter="clearTimer"
      @mouseleave="startTimer"
      role="alert">
      <i :class="iconClass" v-if="iconClass"></i>
      <i :class="typeClass" v-else></i>
      <slot>
        <p v-if="!dangerouslyUseHTMLString" class="el-message__content">
          {{ message }}
        </p>
        <p v-else v-html="message" class="el-message__content"></p>
      </slot>
      <i
        v-if="showClose"
        class="el-message__closeBtn el-icon-close"
        @click="close"></i>
    </div>
  </transition>
</template>
```

在`Message`的 UI 组件里，主要是在`transition`组件（可能是内部封装的一个全局组件）内对一些`data`进行条件渲染。

全部的`data`如下，没有`prop`。

```js
data() {
    return {
        visible: false,
        message: '',
        duration: 3000,
        type: 'info',
        iconClass: '',
        customClass: '',
        onClose: null,
        showClose: false,
        closed: false,
        verticalOffset: 20,
        timer: null,
        dangerouslyUseHTMLString: false,
        center: false
    };
},
```

注意这里的触发显示的方式，是通过`visible`控制的，所以当注册该组件为全局组件时，我们关心是如何将`visible`变为`true`的。

这里暂时先不看`Message`UI 组件里的`js`逻辑，我们回到外部的`main.js`。

### 组件注册分析

在下面的代码里，主要分`instance`和`instances`两块，因为`Message`可以多次调用，所以使用数组的形式。

```js {1,3,21-23,29-30,36,39}
let MessageConstructor = Vue.extend(Main);

let instance;
let instances = [];
let seed = 1;

const Message = function (options) {
  if (Vue.prototype.$isServer) return;
  options = options || {};
  if (typeof options === 'string') {
    options = {
      message: options,
    };
  }
  let userOnClose = options.onClose;
  let id = 'message_' + seed++;

  options.onClose = function () {
    Message.close(id, userOnClose);
  };
  instance = new MessageConstructor({
    data: options,
  });
  instance.id = id;
  if (isVNode(instance.message)) {
    instance.$slots.default = [instance.message];
    instance.message = null;
  }
  instance.$mount();
  document.body.appendChild(instance.$el);
  let verticalOffset = options.offset || 20;
  instances.forEach((item) => {
    verticalOffset += item.$el.offsetHeight + 16;
  });
  instance.verticalOffset = verticalOffset;
  instance.visible = true;
  instance.$el.style.zIndex = PopupManager.nextZIndex();
  instances.push(instance);
  return instance;
};
```

我们主要看`instance`块，我们去除用户输入判断与关闭逻辑，剩下来的核心注册逻辑如下。

```js
let MessageConstructor = Vue.extend(Main);

let instance;

const Message = function (options) {
  options = options || {};

  instance = new MessageConstructor({
    data: options,
  });

  instance.$mount();

  document.body.appendChild(instance.$el);

  instance.visible = true;

  return instance;
};

export default Message;
```

1. 首先使用`Vue.extend`扩展原来的`UI`组件
2. 然后使用`new MessageConstructor`构造一个新的组件，`options`输入到`data`属性内
3. 使用`\$mount()`挂载组件
4. 将组件置入浏览器中`document.body.append...`
5. 将组件的`visible`状态打开
6. 最后导入该组件

基于以上的代码，我们可以很容易的全局引入一个组件，如官网所示，在`Vue`启动前，只需要引入这几句就可以：

```js
import Vue from 'vue';
import Message from 'element-ui';

// 不能使用Vue.use(Message)
Vue.prototype.$message = Message;
```
