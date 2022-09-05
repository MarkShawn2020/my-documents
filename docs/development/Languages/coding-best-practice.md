# coding best practice

## check usb type 2/3

Open the mac system information via click Apple icon while holding `option` key, and check the usb column info:

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-best-practice-1642404010602-5facf07131372260eb518b0dbb667289ad00f4e7aecb5d4b302e155df0cec33e.png" />

ref:

- [How do I identify a USB 1.0 or 2.0 or 3.0 pen drive? - Quora](https://www.quora.com/How-do-I-identify-a-USB-1-0-or-2-0-or-3-0-pen-drive)

## test read/write (IO) speed of hard drivers

for windows:

- [Crystal Dew World [en] -](https://crystalmark.info/en/)

for mac:

- [AmorphousDiskMark for macOS - measures storage read/write performance](https://www.katsurashareware.com/amorphousdiskmark/)

test mac of inner:

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-best-practice-1642398423739-aeb613de151fdeecf8160b66e35b72b74bc0c733d9b3a08afff73868ac9c75c7.png" />

test mac of usb driver:

<img alt="picture 2" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-best-practice-1642398440076-be3751b352a97834196179e80cb08130d269112654d9cc4afb2723c5db81f199.png" />

test windows of lixiang:

<img alt="picture 1" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/coding-best-practice-1642398173837-8929dfd56f84fef3a79174ce9dd6e5238a6c2c68918d03adc6e15226fda7fe57.png" />

ref:

- [7 Free Tools To Test SSD Speed And Hard Drive Performance](https://www.geckoandfly.com/23934/ssd-hdd-effective-read-write-speed/)

## the cost to compat Chinese

The definition before:

```ts
export const COL_ID = 'id';
export type COL_ID = typeof COL_ID;

export const COL_AREA = 'area';
export type COL_AREA = typeof COL_AREA;

export const COL_WEIGHT = 'weight';
export type COL_WEIGHT = typeof COL_WEIGHT;

export const COL_DATE = 'date';
export type COL_DATE = typeof COL_DATE;

export const COL_CP_NAME = 'cp';
export type COL_CP_NAME = typeof COL_CP_NAME;

export const erpCols = [
  COL_ID,
  COL_DATE,
  COL_WEIGHT,
  COL_AREA,
  COL_CP_NAME,
] as const;
export type ErpCols = typeof erpCols[number];
```

The definition after:

```ts
export const COL_ID = '单号';
export type COL_ID = typeof COL_ID;

export const COL_AREA = '地区';
export type COL_AREA = typeof COL_AREA;

export const COL_WEIGHT = '重量';
export type COL_WEIGHT = typeof COL_WEIGHT;

export const COL_DATE = '日期';
export type COL_DATE = typeof COL_DATE;

export const COL_CP_NAME = '公司';
export type COL_CP_NAME = typeof COL_CP_NAME;

export const erpCols = [
  COL_ID,
  COL_DATE,
  COL_WEIGHT,
  COL_AREA,
  COL_CP_NAME,
] as const;
export type ErpCols = typeof erpCols[number];
```

The usage before:

```ts
export const validateErpItem = (data: IErpItem): IErpItem => {
  return {
    id: validateId(data.id),
    weight: validatePositive(data.weight as unknown as string),
    date: validateDate(data.date),
    area: validateArea(data.area),
    cp: validateCpName(data.cp),
  };
};
```

The usage after:

```ts
// src/main/modules/parseFile/handler/validators/index.ts:13
export const validateErpItem = (data: IErpItem): IErpItem => {
  return {
    [COL_ID]: validateId(data[COL_ID]),
    [COL_WEIGHT]: validatePositive(data[COL_WEIGHT] as unknown as string),
    [COL_DATE]: validateDate(data[COL_DATE]),
    [COL_AREA]: validateArea(data[COL_AREA]),
    [COL_CP_NAME]: validateCpName(data[COL_CP_NAME]),
  };
};
```

## API design

In this following api, there is `error | content | level`, and at the same time, the `error` and `content` are both omittable, which seems a well-thoughtful design.

```ts
// src/main/base/response.ts:28
export interface IResBase {
  error?: {
    type: ErrorType;
    msg?: string;
  };
  content?: any;
  level: LogLevel;
  sendTime: Date;
}
```

However, when put into practice and communicating between back and frond, we found it hard to manage, since too arbitrary.

Look again this design, we can know the information of `LogLevel` has something to do with `error`, and since the `level` is required, then no need to put the `error` as a super level field.

After my attempt, maybe a more suitable design is to put `error` into `content` when its' an error api.

```ts
export interface IResBase {
  content?: any;
  level: LogLevel;
  sendTime: Date;
}

export interface IResError {
  level: LogLevel.Warning | LogLevel.Error;
  content: {
    errorType: ErrorType;
    errorMsg: string;
  };
}
```

And then the sate becomes easier to differentiate and manage.
