# Never be a C learner. 

1. OS
~~~
➜  ~ docker images ubuntu
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              trusty              67759a80360c        7 months ago        221MB

➜  ~ docker run --name=ubuntu --rm -it registry.docker-cn.com/library/ubuntu

root@bb365acc9d79:/idiotwithc# cat /etc/os-release
NAME="Ubuntu"
VERSION="16.04.3 LTS (Xenial Xerus)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 16.04.3 LTS"
VERSION_ID="16.04"
HOME_URL="http://www.ubuntu.com/"
SUPPORT_URL="http://help.ubuntu.com/"
BUG_REPORT_URL="http://bugs.launchpad.net/ubuntu/"
VERSION_CODENAME=xenial
UBUNTU_CODENAME=xenial
~~~

2. install essential packages

~~~
root@bb365acc9d79:/idiotwithc# apt-get update && apt-get install git curl libcurl4-openssl-dev build-essential
~~~


3. clone source code

~~~
root@bb365acc9d79:/# git clone https://github.com/liangzuobin/idiotwithc.git
~~~

4. make & run

~~~
root@bb365acc9d79:/idiotwithc# make
......

root@bb365acc9d79:/idiotwithc# ./main
uuid = a397a255-53be-41fc-996b-521413e9e22d
ex = 75947738A61E77D768A914761C1C692B3F660A1B52706420D87695CE4AB06E39
ch = 75947738A61E77D768A914761C1C692B3F660A1B52706420D87695CE4AB06E39
equals 0
{"message":"请求参数不合法","status":"BAD_REQUEST","data":{}}
~~~
