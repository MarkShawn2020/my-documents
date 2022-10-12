# Markshawn's Diary

## 2022-10-12, Wed

### finished

- enabled syncing mongodb database from local to remote
  - resolution: using `mongodbdump` and `mongodbrestore`
    - learned that `mongodbrestore` should use `--nsInclude "DB.*"` to restore all the collections under 'DB' database
- enabled changing aws-ec2-ubuntu-server's user password
  - solution: just using `sudo passwd $USER` is ok, which leads me to add a new passed (other than modify the raw one which even not initialized)
- enabled installing mongodb on remote server and enabled remote access with `0.0.0.0` bound and user authentication
  - ref:
    - install mongodb on ubuntu: https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/
    - enable remote access: https://medium.com/founding-ithaka/setting-up-and-connecting-to-a-remote-mongodb-database-5df754a4da89
      - 1. (the `mongo` is `mongosh` in our platform)
      - 2. install `mongosh`: https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/
  - fixed (or prevented) the dead error when we want to enable the remote access
