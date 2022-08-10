# ts howto

1. [react 声明 state（`ReadOnly`）属性](#react声明statereadonly属性)
2. [TODO: research on `.d.ts`](#todo-research-on-dts)
3. [BEST-PRACTICE: how to define const array with types](#best-practice-how-to-define-const-array-with-types)
   1. [webstorm typescript live template](#webstorm-typescript-live-template)
   2. [sample source code](#sample-source-code)
   3. [a little reflection](#a-little-reflection)
4. [`htmlFor` in `label`](#htmlfor-in-label)
5. [private property in interface](#private-property-in-interface)
6. [[Give Up] typeorm find error types](#give-up-typeorm-find-error-types)
7. [instanceof --> istypeof ?](#instanceof----istypeof-)
8. [PASS: declare const array in d.ts](#pass-declare-const-array-in-dts)
9. [hwo to define `useImperativeHandler` interface](#hwo-to-define-useimperativehandler-interface)
   1. [ReturnType of a function](#returntype-of-a-function)
10. [how to design interface with default value](#how-to-design-interface-with-default-value)
11. [what's `TS_NODE_TRANSPILE_ONLY`](#whats-ts_node_transpile_only)
12. [TODO: cast enum to string](#todo-cast-enum-to-string)
13. [how to import `.md` like resources](#how-to-import-md-like-resources)
14. [how to check object's specific type when defined as a union type](#how-to-check-objects-specific-type-when-defined-as-a-union-type)

## react 声明 state（`ReadOnly`）属性

先`Props`，再`State`。

```ts
interface State {
  bar: number;
}

interface Props {
  baz: number;
}

class Foo extends React.Component<Props, State> {
  public state: State = {
    bar: 5,
  };
}
```

ref:

- [React.d.ts ReadOnly\<T\> in state and props · Issue #14250 · DefinitelyTyped/DefinitelyTyped](https://github.com/DefinitelyTyped/DefinitelyTyped/issues/14250)

## TODO: research on `.d.ts`

## BEST-PRACTICE: how to define const array with types

### webstorm typescript live template

```ts
export const $ConstVAR$ = '$VAR$';
export type $VAR$ = typeof $ConstVAR$;

$END$;
```

### sample source code

```ts
// sample of one unit
export const errorInvalidSuffix = 'ErrorInvalidSuffix';
export type ErrorInvalidSuffix = typeof errorInvalidSuffix;

export const errorUnknownEncoding = 'ErrorUnknownEncoding';
export type ErrorUnknownEncoding = typeof errorUnknownEncoding;

export const errorPreParsingRows = [
  errorInvalidSuffix, // 后缀
  errorUnknownEncoding, // 编码
] as const;
export type ErrorPreParsingRows = typeof errorPreParsingRows[number];

// sample of joining units
export const errorParsingFiles = [
  ...errorPreParsingRows, // 解析行之前的问题
  ...errorParsingRows, // 解析行时的问题
] as const;
export type ErrorParsingFile = typeof errorParsingFiles[number];
```

### a little reflection

After a little try of this camel case const varied types, I found it a bit inflexible.

So I finally turns into the usage of simple `const === type`, especially support for the use of redux actions.

## `htmlFor` in `label`

In materialUI, they used a custom element based on `input` with a `label`.

```ts
// https://mui.com/zh/components/buttons/#upload-button
const Input = styled('input')({
  display: 'none',
});

export default function UploadButtons() {
  return (
    <Stack direction="row" alignItems="center" spacing={2}>
      <label htmlFor="contained-button-file">
        <Input
          accept="image/*"
          id="contained-button-file"
          multiple
          type="file"
        />
        <Button variant="contained" component="span">
          Upload
        </Button>
      </label>
      ...
    </Stack>
  );
}
```

In this demo, the `label` has a property of `htmlFor`, which points to an element with id of `contained-button-file`, i.e the element of `Input` which accepts images.

However, this may cause the eslint problem since in eslint the label should points to an built-in element.

There are 2 solutions.

1. add the eslint configuration:

   refer to here: [Case: My label and input components are custom components.](https://github.com/jsx-eslint/eslint-plugin-jsx-a11y/blob/main/docs/rules/label-has-associated-control.md#case-my-label-and-input-components-are-custom-components), we can add the configuration of custom elements as the following:

   ```json
   // .eslintrc
   {
     "rules": {
       "jsx-a11y/label-has-associated-control": [
         2,
         {
           "labelComponents": ["CustomInputLabel"],
           "labelAttributes": ["label"],
           "controlComponents": ["CustomInput"],
           "depth": 3
         }
       ]
     }
   }
   ```

2. give up the custom elements if unnecessary

   In our demo, since MaterialUI just does one little work on the built-in element of `input`, i.e. adds the `display: 'none'` style onto the element.

   So if we don't have the requirement of re-using this element, we can avoid using custom elements, and re-write the codes like the following:

   ```ts
   export default function UploadButtons() {
     return (
       <Stack direction="row" alignItems="center" spacing={2}>
         <label htmlFor="contained-button-file">
           <input
             style={{display: 'none'}}
             accept="image/*"
             id="contained-button-file"
             multiple
             type="file"
           />
           <Button variant="contained" component="span">
             Upload
           </Button>
         </label>
         ...
       </Stack>
     );
   }
   ```

## private property in interface

I intended to make the property from interface into implemented class private, so that I can use methods to export those properties, but to find it's impossible.

```ts
// src/main/modules/parseFile/handler/parse_base.ts:16
export interface IParseResult {
  startTime: Date;
  parseEndTime: Date;
  dbEndTime: Date;
  parseMileSeconds: number;
  dbMileSeconds: number;
  nTotalRows: number;
  nSavedRows: number;
  nFailedValidation: number;
  sizePct: number;
  rowsPct: number;
}
```

And actually what I want to do is because I didn't catch really what an interface means, and how to design a robust interface with class.

The `IParseResult` is really what I want, that means, the exported data-structure.

However, I cannot use a class to implement directly on this interface, so that I operate the public methods inner the class to alter these properties.

The proper way is to define a class to store all or partial data properties of this interface, and do operations, and then, finally export those values.

If I do not want to export each time, since I want to use a variable like `parseResult` directly in the scope, then I can design a class with accepts the `parseResult` then alter its value by methods so that the changes happen in place.

In conclusion, we can define an interface, and the interface is for outer usage, rather than implemented by a class, which, if so, needs to be implemented like this:

```ts
interface IPipeParseResult {
  ...

  export: () => IParseResult
}

class ParseResult implements IPipeParseResult {
  ...

  public expo
  rt(): IParseResult {
    return {
      ...
    }
  }
}
```

Not like this, which has no meaning:

```ts
class ParseResult implements IParseResult {
  ....
}
```

So, to my former project, I gave it up, since no need to be that sophisticated then.

ref:

- [reactjs - How to define a private property when implementing an interface in Typescript? - Stack Overflow](https://stackoverflow.com/questions/37791947/how-to-define-a-private-property-when-implementing-an-interface-in-typescript)

## [Give Up] typeorm find error types

I intended to use error type to check the database execution result.

<img alt="picture 37" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-howto-1641639645599-589d5e5cc1ed8ab3620785ff64d7ccb7ff852a4680952c50f139af167e8b1fcf.png" />

However, I failed, since the specific error type is not provided by the `typeorm` instead of from third party library like `sqlite3-driver` or so.

The query result module is written at [typeorm/QueryBuilder.ts at beea2e1e4429d13d7864ebc23aa6e58fa01647ea · typeorm/typeorm](https://github.com/typeorm/typeorm/blob/beea2e1e4429d13d7864ebc23aa6e58fa01647ea/src/query-builder/QueryBuilder.ts), in which it just merges the third-party query result with typeorm's inner query result defined at [typeorm/QueryFailedError.ts at beea2e1e4429d13d7864ebc23aa6e58fa01647ea · typeorm/typeorm](https://github.com/typeorm/typeorm/blob/beea2e1e4429d13d7864ebc23aa6e58fa01647ea/src/error/QueryFailedError.ts).

Hence, unless we spent a lot of time to figure out what the lib is using and where the types of the lib defines, (and possibly we could find nothing since they may be written via `C/C++`).

So just let it go, and do more harding coding then. Those don't deserve.

## instanceof --> istypeof ?

No! In typescript, there is no api like `instanceof` to type check.

However, we can define a method which returns `a is A` to determine.

ref:

- [Typescript: Check "typeof" against custom type - Stack Overflow](https://stackoverflow.com/questions/51528780/typescript-check-typeof-against-custom-type/51529486)

- [Switch for specific type in TypeScript - Stack Overflow](https://stackoverflow.com/questions/50774790/switch-for-specific-type-in-typescript)

## PASS: declare const array in d.ts

<img alt="picture 5" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-howto-458f2e34b1a34244b59d092c885fa546ea1332db99544c578b388beee85b0cc9.png" width="480" />

temporary solution: use `enum` instead of `const array` <img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/ts-howto-868f836962d18cf399dcb6907ca148f017a737e0b41e4efac9c848d694ee5282.png" width="480" />

ref:

- [How to define a const array in typescript - Stack Overflow](https://stackoverflow.com/questions/51870736/how-to-define-a-const-array-in-typescript)

- [angular - Error: Initializers are not allowed in ambient contexts - Stack Overflow](https://stackoverflow.com/questions/43318178/error-initializers-are-not-allowed-in-ambient-contexts/43318374)

## hwo to define `useImperativeHandler` interface

It's quite clarified in this answer that when I define a `useImperativeHandler`, I need to make at least four steps.

<img alt="picture 76" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640676945341-ts-howto-ac842442a20aef4c0a0d173a73160bb58ac48cbc813bf78b87edfcfa882cfbc4.png" width="480" />

First, I should let the `useRef` know not only the component type (which initialized as `null`) but also the `Handler` type, in which defined the api interface, so that I can use `ref.current.doSomething()` and share the full auto-complement from IDE.

Second, how to define the `Handler` type? The easier way is derive it directly from the component using `typeof ForwardRefType`.

However, if we hadn't defined what's the `Handler` we are to use in our `ForwardRefType`, then those work still wouldn't work. It forced us to clearly define the `Handler` the `component` is using.

Nevertheless, I am not willing to write an interface which is totally equal to the type of function. So I struggled to find a `ReturnType` to help me auto complete this matter.

And I found a way to write like this: <img alt="picture 77" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640677820762-ts-howto-b6c2ccbe2d7ab156854085e816b35f52d5b0d2ca511fb67e06771bd28ecac7e4.png" width="480" />

First, I peeled off(剥离) the `imperativeHandler` api separately, and the cost is to use a function since the `Handler` depends the `ref`.

Then I use this `Handler` again, to let its `ReturnType` serve as the generic type of `forwardRef` (**this is the most important!**).

Finally, I use the type of `forwardRef` as the generic type of its father ref element, and then it would know what api to use. All things are done! <img alt="picture 78" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640678111109-ts-howto-32730e18ce87a235d7e1ca390bd6408000bd964a1dcf343bda41e6b0e1035320.png" width="480" />

There is a last problem about this approach, that is why I cannot make the ref init value work even with `null as unknown as ScrollToBottom`, which forced me to write like `ref?.current?.doScroll()` rather than `ref.current.doScroll()`.

But it's not so important yet now. Maybe I would turn back to solve this in the future need.

[TODO: why `null as unknown as ScrollToBottom` not work]

ref:

- [reactjs - declare type with React.useImperativeHandle() - Stack Overflow](https://stackoverflow.com/questions/62210286/declare-type-with-react-useimperativehandle)

### ReturnType of a function

```ts
function f1(s: string) {
  return {a: 1, b: s};
}
type T14 = ReturnType<typeof f1>; // { a: number, b: string }
```

ref:

- [(20 条消息) TS 中的条件类型(ReturnType)\_前端精髓-CSDN 博客\_ts 条件类型](https://blog.csdn.net/wu_xianqiang/article/details/115425818)

## how to design interface with default value

There has been quite a little of insightful solutions offered in this question [Typescript interface default values - Stack Overflow](https://stackoverflow.com/questions/35074365/typescript-interface-default-values).

And I finally choose the [factory function way](https://stackoverflow.com/a/64782269/9422455) since it's more straight-forward and can meet my need also.

Then my interface is designed into like this:

```ts
import {MsgFromMain, MsgLevel} from '../universal';

export interface ConsoleItem {
  text: string;
  time: Date;
  level: MsgLevel;
}

export const makeItemFromMain = (
  msg: MsgFromMain,
  func?: (any) => string,
): ConsoleItem => ({
  text: func ? func(msg.content) : msg.content,
  time: msg.sendTime,
  level: msg.level || MsgLevel.debug,
});

export const makeItemFromText = (
  text: string,
  level = MsgLevel.debug,
): ConsoleItem => ({
  text,
  time: new Date(),
  level,
});
```

In this interface, any of `text | time | level` can get a default value either from another input or so, and it frees me from redundant coding and allows me to write like this:

<img alt="picture 75" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640674249655-ts-howto-b52d01a09ae0d04bc148987d1ee8d9ba0957a78907f910a0cf0d0c490bafac72.png" width="480" />

Thank you!

ref:

- [Typescript interface default values - Stack Overflow](https://stackoverflow.com/questions/35074365/typescript-interface-default-values)

## what's `TS_NODE_TRANSPILE_ONLY`

In a word, `transpile_only` is used to fasten the transition speed from ts into js.

<img alt="picture 61" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640612737395-ts-howto-2f28d60ccf1f52f6920ebfd8c29de1925d2cb9c66475473e03da2007a2e76b30.png" width="480" />

ref:

- [TypeStrong/ts-node: TypeScript execution and REPL for node.js](https://github.com/TypeStrong/ts-node)

## TODO: cast enum to string

If I define a EnumType of `enum MenuKey {ERP="ERP", TRD="TRD"}` since I need a data structure to limit a variable domain.

Obviously in my case, they are all string, which means the real intension of me is something like `enum MenuKey {xxx} as string` so that I can put my `MenuKey` into an API which only accepts string, e.g: `slice`.

Hence, I can write like the following since ts would treat `mk` as a string so that has an api of `slice`:

```ts
const mk: MenuKey = 'ERP';
console.log(mk.slice(0, 2));
```

However, it doesn't.

The only way I can do is write like this:

```ts
console.log((mk as string).slice(0, 2));
```

Please read another example from the real business scene:

```ts
enum MenuKey {
  ERP = 'ERP',
  TRD = 'TRD',
}

// first realization, definitely not good since we need to write `as string` each time using it as a string
const [menuKey, setMenuKey] = useState(MenuKey.ERP);
console.log((menuKey as string).slice(0, 2)); // not good

// second realization, a little better
const [menuKey, setMenuKey] = useState(MenuKey.ERP as string);
console.log(menuKey.slice(0, 2));
```

I wonder if there is a built-in practice that allows me done this right.

Thanks.

## how to import `.md` like resources

Just declare it as a module.

```ts
// globals.d.ts
declare module '*.md';
```

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1640336624589-ts-howto-41d70e41b4f730bdf9428b5f12075eea653950d79253aa8f16db446ef644ccfe.png" width="480" />

ref:

- [angular - How to import markdown(.md) file in typescript - Stack Overflow](https://stackoverflow.com/questions/44678315/how-to-import-markdown-md-file-in-typescript)

## how to check object's specific type when defined as a union type

This problem may seem easy is many programming languages, e.g, you can use `isinstane(x, X)` in `python`.

However, it becomes tricky when things in TypeScript since so many that are close to complex concepts can be really hard for a newbie to find the right way.

I tried to scratch some useful info from the official TypeScript website but to find neither `union` nor `merge` can satisfy my requirements. The `combination` may be a little helpful if we do some hook on this one.

On StackOverFlow, a relative post [javascript - Is it possible to combine members of multiple types in a TypeScript annotation? - Stack Overflow](https://stackoverflow.com/questions/27325524/is-it-possible-to-combine-members-of-multiple-types-in-a-typescript-annotation) caught my eyesight but indeed almost none of the answers can meet my expectation -- an built-in and elegant(优雅的) solution rather than write redundant and vulnerable(脆弱的) functions.

Finally, I found a wonderful typescript handbook named as `typescript-cheatsheet` at [typescript-cheatsheet | A set of TypeScript related notes used for quick reference. The cheatsheet contains references to types, classes, decorators, and many other TypeScript related subjects.](https://rmolinamir.github.io/typescript-cheatsheet/#type-checking-for-interfaces) , where it's easy for me to locate into the target chapter: [typescript-cheatsheet | A set of TypeScript related notes used for quick reference. The cheatsheet contains references to types, classes, decorators, and many other TypeScript related subjects.](https://rmolinamir.github.io/typescript-cheatsheet/#type-checking-for-interfaces)

In this cheatsheet, it concludes two methods that can help me check an object's type, one by using `type-guards` which is best suitable for my current need, and the other one is by using `discriminators` which may be useful in the later projects.

If you are interested at `discriminators`, please move a step to [Typescript discriminator. Very often we have use-cases where we… | by Dixit Patel | Medium](https://medium.com/@dixitk13/typescript-discriminator-a3158f292ef0) for a better understanding since I am confused it with the javascript `properties` and typescript `decorators`.

Thanks to `typescript-cheatsheet`, it really helped me a lot and I can foresee that I will frequently seek for any typescript help from here rather than first searching on the stackoverflow.
