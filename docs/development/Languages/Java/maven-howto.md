# maven-howto

- [use mirrors for repositories](#use-mirrors-for-repositories)
- [config mysql in `application.yml`](#config-mysql-in-applicationyml)
- [config mysql in pom](#config-mysql-in-pom)

## use mirrors for repositories

```xml
<!-- format -->

<settings>
  ...
  <mirrors>
    <mirror>
      <id>other-mirror</id>
      <name>Other Mirror Repository</name>
      <url>https://other-mirror.repo.other-company.com/maven2</url>
      <mirrorOf>central</mirrorOf>
    </mirror>
  </mirrors>
  ...
</settings>
```

ref:

- [Maven – Guide to Mirror Settings](https://maven.apache.org/guides/mini/guide-mirror-settings.html)

下载速度： **华为云**>阿里云>腾讯云用户体验： 华为云>腾讯云>阿里云

- [Java 开发者必备神器 Maven 国内镜像加速深度测试 - SegmentFault 思否](https://segmentfault.com/a/1190000022529672)

这帖有一些争论，莫衷一是，需要自己测试。 TODO: 测试是否正在使用 maven 镜像，测试其速度。

- [将 maven 源改为国内阿里云镜像 - 知乎](https://zhuanlan.zhihu.com/p/71998219)

- [Maven 配置阿里云镜像 - SegmentFault 思否](https://segmentfault.com/a/1190000039280184)

## config mysql in `application.yml`

```yaml
spring:
  datasource:
    type: com.alibaba.druid.pool.DruidDataSource
    druid:
      url: jdbc:mysql://localhost:3306/RoyalTtiger
      username: root
      password: XXXXX
      driver-class-name: com.mysql.cj.jdbc.Driver # old: com.mysql.jdbc.Driver
  servlet:
    multipart:
      max-file-size: 300MB
      max-request-size: 800MB
```

ref:

- [Getting Started | Accessing data with MySQL](https://spring.io/guides/gs/accessing-data-mysql/)

- [java - How to use Spring Boot with MySQL database and JPA? - Stack Overflow](https://stackoverflow.com/questions/27981789/how-to-use-spring-boot-with-mysql-database-and-jpa)

## config mysql in pom

```xml
<dependency>
 <groupId>mysql</groupId>
 <artifactId>mysql-connector-java</artifactId>
</dependency>
```

ref:

- [java - Maven Dependencies SpringBoot and MySQL - Stack Overflow](https://stackoverflow.com/questions/46995281/maven-dependencies-springboot-and-mysql)

- [Add MySQL Support to Spring Boot Web App - Apps Developer Blog](https://www.appsdeveloperblog.com/add-mysql-support-to-spring-boot-web-app/)
