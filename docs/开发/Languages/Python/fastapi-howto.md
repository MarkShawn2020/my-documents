# fastapi-howto

## when `root_path` meets with `doc_url`

it seems easy when we read the introduction of `root_path` at [Behind a Proxy - FastAPI](https://fastapi.tiangolo.com/advanced/behind-a-proxy/) however things go different when we combine this 'sugar' with `no_doc_url`.

I think it is because that the `doc_url` would all be diy by ourselves when we use the offline url settings, which deserves our special attention since I spent a bit of time suffering from it.

Finally, always remember `root_path` is just a 'proxy' prefix rather than the real one!

reference:

- [代理背后 - FastAPI](https://fastapi.tiangolo.com/advanced/behind-a-proxy/#check-the-docs-ui)

## How to save uploaded files

At present, I'd love to use `aiofiles` to help me solve this problem.

```py
with awiat aiofiles.open(OUT_FILE_PATH, "wb") as f:
    while content := IN_FILE_OBJECT.read(1024):
        await f.write(content)
```

reference:

- [python - How to save UploadFile in FastAPI - Stack Overflow](https://stackoverflow.com/questions/63580229/how-to-save-uploadfile-in-fastapi)

## How to write unit test?

using pytest.

reference:

- [Step 3. Test your first Python application | PyCharm](https://www.jetbrains.com/help/pycharm/testing-your-first-python-application.html)
- [pytest: helps you write better programs — pytest documentation](https://docs.pytest.org/en/6.2.x/)
- [Testing - FastAPI](https://fastapi.tiangolo.com/tutorial/testing/?h=test)

## uvicorn deployment

reference:

- [Deployment - Uvicorn](https://www.uvicorn.org/deployment/)
