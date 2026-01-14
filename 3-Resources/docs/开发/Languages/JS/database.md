1. [typeorm join table](#typeorm-join-table)
1. [:white_check_mark: join using id(string) other than Entity](#white_check_mark-join-using-idstring-other-than-entity)
1. [:x: join return flatted list other than nested](#x-join-return-flatted-list-other-than-nested)
1. [typeorm not null constraint failed](#typeorm-not-null-constraint-failed)
1. [PASS: better-sqlite3 `NODE_MODULE_VERSION` mismatch | rebuild failed](#pass--better-sqlite3-node_module_version-mismatch--rebuild-failed)
1. [PASS: better-sqlite3 ReferenceError: better_sqlite3_1 is not defined, both `jest` and `mocha`](#pass-better-sqlite3-referenceerror-better_sqlite3_1-is-not-defined-both-jest-and-mocha)
1. [mocha + ts + esm](#mocha--ts--esm)

## typeorm join table

### :white_check_mark: join using id(string) other than Entity

I have checked a lot of typeorm documentation and relative discussion, but to find they all use an extra column to specify the table to join.

For example, int the case below, the key of `user` in `Profile` refers to `User`, and the key of `profile` in `User` refers to `Profile`.

```ts
# Entity Profile
import {Entity, PrimaryGeneratedColumn, Column, OneToOne} from "typeorm";
import {User} from "./User";

@Entity()
export class Profile {

    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    gender: string;

    @Column()
    photo: string;

    @OneToOne(() => User, user => user.profile) // specify inverse side as a second parameter
    user: User;

}

# Entity User
import {Entity, PrimaryGeneratedColumn, Column, OneToOne, JoinColumn} from "typeorm";
import {Profile} from "./Profile";

@Entity()
export class User {

    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    name: string;

    @OneToOne(() => Profile, profile => profile.user) // specify inverse side as a second parameter
    @JoinColumn()
    profile: Profile;

}
```

However, in my own business scene, since I have two tables with the equal level and the same `id` property, it's redundant for me to specify an extra column named as `erpId` or `trdId` or `foreignId` or anything.

Besides, since the `trd` and the `erp` are saved into db not synchronously, the example listed on the documentation won't help to us.

Through my hard experiment and observation, I finally realized the join key is some kind of `id` (not real object) which means if only I specified the correct id, the join action then would be executed successfully.

That's it! Since we have already know the id of item to be join, which is directly the id of the item itself, then we can just let the id to be the joined key, like this:

```ts
# Entity Erp
import { Column, Entity, OneToOne, PrimaryColumn } from 'typeorm';
import { TrdModel } from './trd';

@Entity()
export class ErpModel {

  @OneToOne(() => TrdModel, trd => trd.id)
  @PrimaryColumn()
  id: string;

}

# Entity Trd
import { Column, Entity, JoinColumn, OneToOne, PrimaryColumn } from 'typeorm';
import { ErpModel } from './erp';

@Entity()
export class TrdModel  {
  @OneToOne(() => ErpModel, erp=>erp.id )
  @JoinColumn()
  @PrimaryColumn()
  id: string;
}
```

So I can use the following query to get a joined table:

```ts
// src/main/modules/queryDB/db.ts:40
// map erp into `id`, so `id` would go away
      getConnection()
        .leftJoinAndSelect('trd.id', 'erp')
        .skip(skip)
        .limit(limit)
        .getMany()
    );
```

<img alt="picture 3" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/database-1641883942426-5cfef08aace698977502e57644e78e6c3b45ccbc34d76978642b5337ff4068fa.png" />

```ts
// map erp into `erp`, so `id` still existed
      getConnection()
        .manager.createQueryBuilder(TrdModel, 'trd')
        .leftJoinAndMapOne('trd.erp', ErpModel, 'erp', 'erp.id = trd.id')
        .skip(skip)
        .limit(limit)
        .getMany()
    );
```

<img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/database-1641894903691-ecc5ca26d8438b8c4283055900d4d6e9680338e15d531190c167d64be121d66e.png" />

ref:

- [TypeORM - Amazing ORM for TypeScript and JavaScript (ES7, ES6, ES5). Supports MySQL, PostgreSQL, MariaDB, SQLite, MS SQL Server, Oracle, WebSQL databases. Works in NodeJS, Browser, Ionic, Cordova and Electron platforms.](https://typeorm.io/#/one-to-one-relations)

- [One-to-one relations - typeorm](https://orkhan.gitbook.io/typeorm/docs/one-to-one-relations)

- [NestJs 中使用 Typeorm 的问题总结 | Porschebz](https://www.porschebz.com/posts/42345.html)

### :x: join return flatted list other than nested

It's sad to find that it is impossible in typeorm, which reminds me the beauty of `pandas`, lol.

<img alt="picture 4" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/database-1641893492395-6a822246d22301f3fa6974058a567a005a69e234dc94da55a46c5b4d4a724ebb.png" />

So I should manually add one `map` to help finish this conversion.

ref: I spent a lot of time and finally thought of the search key of `flat`!

- [How to return a relation column as top level in response? · Issue #5111 · typeorm/typeorm](https://github.com/typeorm/typeorm/issues/5111)

## typeorm not null constraint failed

This is because I added new table columns into former model.

<img alt="picture 41" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/database-1641652378702-4275729e537afcacf2683f64ef62d2a483273f6bccf4bf5933ccb490b4abc8e9.png" />

Since I do not know the `source` is , or unnecessary, I would like to delete the table first.

I tried to delete table but not found the choice but the `dropDatabase()`. <img alt="picture 42" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/database-1641653005035-a9fb5d2adc9a4fd9188e9a5dee06581a59f5a084bcd29764250b5a5cd1bbef0e.png" />

## PASS: better-sqlite3 `NODE_MODULE_VERSION` mismatch | rebuild failed

<img alt="picture 12" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/best-sqlite3-1641545886362-5b85064baa519f5c06ecf28469b8462382162f0d792649670db6e0b1b3b77525.png" />

<img alt="picture 13" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/best-sqlite3-1641546347572-29a1230b8941634376b03ed20a25c09b9fd917dd49de0a823f68df13042a6613.png" />

## PASS: better-sqlite3 ReferenceError: better_sqlite3_1 is not defined, both `jest` and `mocha`

The author suggests us to use mocha: [A more robust testing framework (such as mocha, the one used in the better-sqlite3 repository), does not cause such an issue.](<https://github.com/JoshuaWise/better-sqlite3/issues/162#:~:text=A%20more%20robust%20testing%20framework%20(such%20as%20mocha%2C%20the%20one%20used%20in%20the%20better%2Dsqlite3%20repository)%2C%20does%20not%20cause%20such%20an%20issue.>)

ref:

- [SqliteErrors have wrong constructor in Jest environment · Issue #162 · JoshuaWise/better-sqlite3](https://github.com/JoshuaWise/better-sqlite3/issues/162)

### mocha + ts + esm

- [typescript with ts-node and ESM support · Issue #47 · mochajs/mocha-examples](https://github.com/mochajs/mocha-examples/issues/47)
