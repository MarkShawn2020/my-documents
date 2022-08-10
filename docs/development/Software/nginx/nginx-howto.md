# nginx-howto

## nginx config file

reference:

- [Full Example Configuration | NGINX](https://www.nginx.com/resources/wiki/start/topics/examples/full/)

## how to install and configure nginx on Ubuntu

- [How To Install Nginx on Ubuntu 18.04 | DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-ubuntu-18-04)

## configure for fastapi

- [Deploy FastAPI Application on Ubuntu with Nginx, Gunicorn and Uvicorn - DEV Community](https://dev.to/shuv1824/deploy-fastapi-application-on-ubuntu-with-nginx-gunicorn-and-uvicorn-3mbl)

## configure for react, so the react app lies on the domain

- [How To Deploy a React Application with Nginx on Ubuntu 20.04 | DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-deploy-a-react-application-with-nginx-on-ubuntu-20-04)

## break through the default max size limit (1m)

add this line in `http`, be cautious if you occur problem because nested application.

```text
; nginx.conf
client_max_body_size 200m;
```

reference:

- [(20 条消息) nginx 出现 413 Request Entity Too Large 问题的解决方法\_傲雪星枫-CSDN 博客\_large](https://blog.csdn.net/fdipzone/article/details/45544497)

- [nginx: [emerg] "http" directive is not allowed here in /etc/nginx/sites-enabled/default:1 - Stack Overflow](https://stackoverflow.com/questions/43643829/nginx-emerg-http-directive-is-not-allowed-here-in-etc-nginx-sites-enabled)
