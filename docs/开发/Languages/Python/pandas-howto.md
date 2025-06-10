# pandas howto

## how to use `query`

### use `query` to perform a `LIKE`

```py
# use `.str.contains`
df.query('column_a.str.contains("abc") or column_b.str.contains("xyz") and column_c>100', engine='python')

```

> ref

- [python - USING LIKE inside pandas.query() - Stack Overflow](https://stackoverflow.com/questions/31391275/using-like-inside-pandas-query)
