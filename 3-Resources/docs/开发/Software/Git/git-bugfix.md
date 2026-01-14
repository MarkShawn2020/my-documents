# git-bugfix

1. [FIXED: `Fatal: Not possible to fast-forward, aborting`](#fixed-fatal-not-possible-to-fast-forward-aborting)
   1. [conclusion](#conclusion)
   2. [BEST-PRACTICE: git branch/lola](#best-practice-git-branchlola)
2. [FIXME: `git-fls` not found](#fixme-git-fls-not-found)
3. [cannot git pull since file path invalid](#cannot-git-pull-since-file-path-invalid)

## FIXED: `Fatal: Not possible to fast-forward, aborting`

### conclusion

```sh

# Step 1: pull rebase
git pull --rebase

# Step 2: modify the conflicting files (Accept local or remote)

# Step 3: add update
git add .

# Step 4. rebase continue
git rebase --continue

# Step 5. push
git push # or TODO: git commit -a; git push

```

ref:

- [Fatal: Not possible to fast-forward, aborting - 简书](https://www.jianshu.com/p/5f4772dc60c2)

- [Git: "Not currently on any branch." Is there an easy way to get back on a branch, while keeping the changes? - Stack Overflow](https://stackoverflow.com/questions/4735556/git-not-currently-on-any-branch-is-there-an-easy-way-to-get-back-on-a-branch)

### BEST-PRACTICE: git branch/lola

```sh
# show branches, with graph
glola # alias | grep graph; i.e. `glola='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ar) %C(bold blue)<%an>%Creset'\'' --all'`

# show branches, and where is now
git branch

# delete branch
git branch -d XXX

# switch branch
git checkout XXX
```

## FIXME: `git-fls` not found

```sh
git-lfs filter-process: git-lfs: command not found
fatal: the remote end hung up unexpectedly
```

```sh
brew install git-lfs
```

## cannot git pull since file path invalid

It is mainly caused by the 系统之间的兼容问题，specific file/folder names are not supported on some platforms, for example the `:*` and trailing spaces are not supported on Windows platform.

Rename those files are always a good choice, otherwise you need to learn to write a little complicated configurations for git (and rarely used).

ref:

- [windows - Git pull error: unable to create file (Invalid argument) - Stack Overflow](https://stackoverflow.com/questions/26097568/git-pull-error-unable-to-create-file-invalid-argument)

- [github/git Checkout Returns 'error: invalid path' on Windows - Stack Overflow](https://stackoverflow.com/questions/63727594/github-git-checkout-returns-error-invalid-path-on-windows)
