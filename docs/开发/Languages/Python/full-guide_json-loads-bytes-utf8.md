
## convert utf8 (`"\xe5\xbb\x96*"`) to chinese (`"廖*"`)


```py
def x2utf8(s):
  """
  将 "\\x" 的 utf8 字符转为可读文字
  example: "\\xe5\\xbb\\x96*" --> "廖*"
  source: https://blog.csdn.net/YungGuo/article/details/110197818
  """
  return urllib.parse.unquote(s.encode('unicode_escape').decode('utf-8').replace('\\x', '%'))
```


## convert bytes-string (`"b'sample'"`) to bytes (`b'sample'`)

### via `ast.literal_eval` (partial ok)

ref: [How to convert Python bytes string representation to bytes? - Stack Overflow](https://stackoverflow.com/questions/59777657/how-to-convert-python-bytes-string-representation-to-bytes)

cons: it only supports ascii transfer.

sample:

```py
import ast

b1 = b'{"name":"mark"}'
s1 = """b'{"name":"mark"}'"""

b2 = b'{"name":"\xe5\xbb\x96*"}'
s2 = """b'{"name":"\xe5\xbb\x96*"}'"""

# ok
assert ast.literal_eval(s1) == b1

# fail, since `ast.literal_eval` doesn't support utf-8
assert ast.literal_eval(s2) == b2
```
