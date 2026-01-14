# go howto

## download and install

ref:

- [Download and install - The Go Programming Language](https://go.dev/doc/install)

### BEST-PRACTICE: how to install `go` in ubuntu

```sh
cd ~
curl -O https://dl.google.com/go/go1.10.3.linux-amd64.tar.gz

tar xvf go1.10.3.linux-amd64.tar.gz

sudo chown -R root:root ./go
sudo mv go /usr/local

GOPATH=$HOME/my-go

cat <<EOF >> ~/.profile
export GOPATH=$GOPATH
export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
EOF

mkdir -p GOPATH
source ~/.profile
```

ref:

- [How To Install Go on Ubuntu 18.04 | DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-install-go-on-ubuntu-18-04)

- [gopls command - golang.org/x/tools/gopls - pkg.go.dev](https://pkg.go.dev/golang.org/x/tools/gopls#section-readme)

### how to update `go` on ubuntu

```sh
# remove
sudo apt-get remove golang-go
sudo apt-get remove --auto-remove golang-go
sudo rm -rvf /usr/local/go

# install
VERSION=1.15.5
wget https://golang.org/dl/go${VERSION}.linux-amd64.tar.gz
sudo tar -xvf go${VERSION}.linux-amd64.tar.gz
sudo mv go /usr/local
cat <<EOF >> ~/.profile
export GOPATH=$HOME/go
export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
EOF
```

ref:

- [How to Upgrade Go on Ubuntu - buildVirtual](https://buildvirtual.net/how-to-upgrade-go-on-ubuntu/)

## config go env

### config proxy for go

resolution 1. use env variable:

```sh
# resolution 1. use env variable
GOPROXY=$PROXY
```

resolution 2. use alias:

```sh
alias go='http_proxy=$PROXY https_proxy=$PROXY no_proxy=localhost,127.0.0.0/8,::1 go'
```

see: - [How do I configure go command to use a proxy? - Stack Overflow](https://stackoverflow.com/questions/10383299/how-do-i-configure-go-command-to-use-a-proxy)

### resolution 1: `go env -w`

> :warning: `go env -w` needs go version >= 1.13

```sh
go env -w GOPROXY=https://goproxy.io,direct
# Set environment variable allow bypassing the proxy for selected modules
go env -w GOPRIVATE=*.corp.example.com
go env -w GO111MODULE=on
```

### resolution 2: config `~/.profile`

```sh
cat << EOF >> ~/.profile
# Enable the go modules feature
export GO111MODULE=on
# Set the GOPROXY environment variable
export GOPROXY=https://goproxy.io
EOF
```

ref:

- [使用 Go env 命令设置 Go 的环境 - 掘金](https://juejin.cn/post/6844903986529566728)
