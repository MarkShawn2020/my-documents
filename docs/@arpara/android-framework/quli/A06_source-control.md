
## enable `repo` for AOSP code without `git`

### 1. `repo init`

We cannot directly use `repo init`, which would catch `SyntaxError: invalid syntax` in `.repo/repo/main.py`.

[python - SyntaxError: invalid syntax to repo init in the AOSP code - Stack Overflow](https://stackoverflow.com/questions/65193998/syntaxerror-invalid-syntax-to-repo-init-in-the-aosp-code) suggested using the following resolution:


```sh
# change `/usr/bin/repo` to `~/bin/repo`
curl https://storage.googleapis.com/git-repo-downloads/repo-1 > ~/bin/repo
chmod a+x ~/bin/repo

# then repo init
python3 ~/bin/repo init -u git@....
```