
TinyWebServer
===============
A lightweight C++ web server for Linux. It is meant to help beginners practice network programming and build a server of their own.

* Concurrency model: **thread pool + non-blocking sockets + epoll (both ET and LT) + event handling (both Reactor and a simulated Proactor)**
* A **state machine** parses HTTP requests, including **GET and POST**
* A server database backs web **registration and login**, and the server can serve **image and video files**
* A **synchronous / asynchronous logging** system records how the server is running
* Under WebBench it can exchange data across **tens of thousands of concurrent connections**


Preface
----
* While this project was being developed and maintained, many people offered donations. I declined every one. I am not packaging this project as a paid course, and I will not open any donation channel.
* Some people online sell courses built by wrapping this project, or You Shuang's project. Please look carefully at the C++ server projects on study and job-hunting sites, and do not pay blindly.
* Interviewers have found me inside their companies from this project's details, and many resumes list it. In interviews, though, `many candidates got started with this project but still know what the pieces do without knowing why. The fundamentals need more work`. These books are worth reading carefully:
    * *Advanced Programming in the UNIX Environment*
    * *UNIX Network Programming*
* Thank you to everyone who has recognized and supported this project. If it helps you get started, that is an honor.


Contents
-----

| [Overview](#overview) | [Architecture](#architecture) | [Demo](#demo) | [Stress test](#stress-test) |[Changelog](#changelog) |[Download](#download) | [Quick start](#quick-start) | [Custom run](#custom-run) | [Walkthrough](#walkthrough) | [C++11 implementation](#c11-implementation) |[Acknowledgements](#acknowledgements) |
|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|


Overview
----------

> * C/C++
> * Browser/server model
> * [Thread synchronization wrappers](https://github.com/qinguoyi/TinyWebServer/tree/master/lock)
> * [HTTP connection handler](https://github.com/qinguoyi/TinyWebServer/tree/master/http)
> * [Half-sync/half-reactor thread pool](https://github.com/qinguoyi/TinyWebServer/tree/master/threadpool)
> * [Timers for inactive connections](https://github.com/qinguoyi/TinyWebServer/tree/master/timer)
> * [Synchronous / asynchronous logging](https://github.com/qinguoyi/TinyWebServer/tree/master/log)  
> * [Database connection pool](https://github.com/qinguoyi/TinyWebServer/tree/master/CGImysql) 
> * [Synchronous registration and login checks](https://github.com/qinguoyi/TinyWebServer/tree/master/CGImysql) 
> * [Simple server stress test](https://github.com/qinguoyi/TinyWebServer/tree/master/test_presure)


Architecture
-------------
<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1ge0j1atq5hj30g60lm0w4.jpg" height="765"/> </div>

Demo
----------
> * Registration

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1ge0iz0dkleg30m80bxjyj.gif" height="429"/> </div>

> * Login

<div align=center><img src="https://github.com/qinguoyi/TinyWebServer/blob/master/root/login.gif" height="429"/> </div>

> * Requesting an image file (6M)

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1ge0juxrnlfg30go07x4qr.gif" height="429"/> </div>

> * Requesting a video file (39M)

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1ge0jtxie8ng30go07xb2b.gif" height="429"/> </div>


Stress test
-------------
With logging turned off, WebBench stress-tested the server. listenfd and connfd were each tried in ET and LT, and every combination reached tens of thousands of concurrent connections. The combined results are below.

> * Proactor, LT + LT, 93251 QPS

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gfjqu2hptkj30gz07474n.jpg" height="201"/> </div>

> * Proactor, LT + ET, 97459 QPS

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gfjr1xppdgj30h206zdg6.jpg" height="201"/> </div>

> * Proactor, ET + LT, 80498 QPS

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gfjr24vmjtj30gz0720t3.jpg" height="201"/> </div>

> * Proactor, ET + ET, 92167 QPS

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gfjrflrebdj30gz06z0t3.jpg" height="201"/> </div>

> * Reactor, LT + ET, 69175 QPS

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gfjr1humcbj30h207474n.jpg" height="201"/> </div>

> * Total concurrent connections: 10500
> * Time accessing the server: 5s
> * Every request succeeded

**Note:** If this project's webbench reports that the `webbench` command cannot be found, delete the `webbench` executable and compile it again.

Changelog
-------
- [x] Fixed the bug when requesting large files from the server
- [x] Added a page for requesting video files
- [x] Fixed a memory leak in the synchronous database check
- [x] Implemented non-blocking ET and LT triggering, and finished the stress tests
- [x] Completed the wrapper classes in `lock.h` and used that synchronization mechanism throughout
- [x] Improved the code structure and switched to a function-local Meyers singleton
- [x] Tuned the database connection pool semaphore and code structure
- [x] Used RAII to acquire and release database connections
- [x] Wrapped utility classes to cut down on global variables
- [x] One build is enough; command-line options make custom tests easier
- [x] Refactored and wrapped `main`
- [x] Added a command-line switch to turn logging off, and updated the stress-test results with logging off
- [x] Simplified the build so SQL settings are configured only once
- [x] Added Reactor mode and finished its stress test

Download
-------
There are two versions. Their code structure differs a lot, and so do the docs and how you run them. The refactored version is cleaner. The original version (`raw_version`) stays closer to You Shuang's code and is an easier place to start.

If a GitHub download fails or is too slow, use the links below. They stay in sync with the latest GitHub commit.

* Refactored version: [BaiduYun](https://pan.baidu.com/s/1PozKji8Oop-1BYcfixZR0g)
    *  Extraction code: vsqq
* Original version (`raw_version`): [BaiduYun](https://pan.baidu.com/s/1asMNDW-zog92DZY1Oa4kaQ)
    * Extraction code: 9wye
    * To run the original version, see the [original docs](https://github.com/qinguoyi/TinyWebServer/tree/raw_version)

Quick start
------------
* Server test environment
	* Ubuntu 16.04
	* MySQL 5.7.29
* Browser test environment
	* Windows or Linux
	* Chrome
	* FireFox
	* Other browsers have not been tested

* Confirm that MySQL is installed before testing

    ```C++
    // Create the yourdb database
    create database yourdb;

    // Create the user table
    USE yourdb;
    CREATE TABLE user(
        username char(50) NULL,
        passwd char(50) NULL
    )ENGINE=InnoDB;

    // Insert a row
    INSERT INTO user(username, passwd) VALUES('name', 'passwd');
    ```

* Edit the database settings in main.cpp

    ```C++
    // Database login name, password, and database name
    string user = "root";
    string passwd = "root";
    string databasename = "yourdb";
    ```

* Build with GCC inside WSL

    ```C++
    sh ./build.sh
    ```

    Or in Visual Studio Code: reopen this folder in WSL, install the CMake Tools extension, choose the **WSL GCC Debug** preset, and build the `server` target.

* Start the server from the project root

    ```C++
    ./build/server
    ```

* In the browser

    ```C++
    ip:9006
    ```

Custom run
------

```C++
./build/server [-p port] [-l LOGWrite] [-m TRIGMode] [-o OPT_LINGER] [-s sql_num] [-t thread_num] [-c close_log] [-a actor_model]
```

These flags are optional. You do not need to set all of them; combine the ones you need.

* -p, port
	* Default 9006
* -l, how logs are written; default is synchronous
	* 0, synchronous
	* 1, asynchronous
* -m, listenfd and connfd trigger combination; default is LT + LT
	* 0, LT + LT
	* 1, LT + ET
    * 2, ET + LT
    * 3, ET + ET
* -o, graceful close; off by default
	* 0, off
	* 1, on
* -s, number of database connections
	* Default 8
* -t, number of threads
	* Default 8
* -c, turn logging off; logging is on by default
	* 0, logging on
	* 1, logging off
* -a, concurrency model; default is Proactor
	* 0, Proactor
	* 1, Reactor

Example command and what it means

```C++
./build/server -p 9007 -l 1 -m 0 -o 1 -s 10 -t 10 -c 1 -a 1
```

- [x] Port 9007
- [x] Asynchronous logging
- [x] LT + LT
- [x] Graceful close
- [x] 10 connections in the database pool
- [x] 10 threads in the thread pool
- [x] Logging off
- [x] Reactor model

Walkthrough
------------
Recent versions have moved quickly. Most of the write-ups below follow the older `raw_version` code.

* [A beginner's guide to TinyWebServer](https://huixxi.github.io/2020/06/02/%E5%B0%8F%E7%99%BD%E8%A7%86%E8%A7%92%EF%BC%9A%E4%B8%80%E6%96%87%E8%AF%BB%E6%87%82%E7%A4%BE%E9%95%BF%E7%9A%84TinyWebServer/#more)
* [Web server project explained - 01 Thread synchronization wrappers](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=3&sn=5840ff698e3f963c7855d702e842ec47&chksm=83ffbefeb48837e86fed9754986bca6db364a6fe2e2923549a378e8e5dec6e3cf732cdb198e2&scene=0&xtrack=1#rd)
* [Web server project explained - 02 Half-sync/half-reactor thread pool (part 1)](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=4&sn=caa323faf0c51d882453c0e0c6a62282&chksm=83ffbefeb48837e841a6dbff292217475d9075e91cbe14042ad6e55b87437dcd01e6d9219e7d&scene=0&xtrack=1#rd)
* [Web server project explained - 03 Half-sync/half-reactor thread pool (part 2)](https://mp.weixin.qq.com/s/PB8vMwi8sB4Jw3WzAKpWOQ)
* [Web server project explained - 04 HTTP connection handling (part 1)](https://mp.weixin.qq.com/s/BfnNl-3jc_x5WPrWEJGdzQ)
* [Web server project explained - 05 HTTP connection handling (part 2)](https://mp.weixin.qq.com/s/wAQHU-QZiRt1VACMZZjNlw)
* [Web server project explained - 06 HTTP connection handling (part 3)](https://mp.weixin.qq.com/s/451xNaSFHxcxfKlPBV3OCg)
* [Web server project explained - 07 Timers for inactive connections (part 1)](https://mp.weixin.qq.com/s/mmXLqh_NywhBXJvI45hchA)
* [Web server project explained - 08 Timers for inactive connections (part 2)](https://mp.weixin.qq.com/s/fb_OUnlV1SGuOUdrGrzVgg)
* [Web server project explained - 09 Logging (part 1)](https://mp.weixin.qq.com/s/IWAlPzVDkR2ZRI5iirEfCg)
* [Web server project explained - 10 Logging (part 2)](https://mp.weixin.qq.com/s/f-ujwFyCe1LZa3EB561ehA)
* [Web server project explained - 11 Database connection pool](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274326&idx=1&sn=5af78e2bf6552c46ae9ab2aa22faf839&chksm=83ffbe8eb4883798c3abb82ddd124c8100a39ef41ab8d04abe42d344067d5e1ac1b0cac9d9a3&token=1450918099&lang=zh_CN#rd)
* [Web server project explained - 12 Registration and login](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274431&idx=4&sn=7595a70f06a79cb7abaebcd939e0cbee&chksm=83ffb167b4883871ce110aeb23e04acf835ef41016517247263a2c3ab6f8e615607858127ea6&token=1686112912&lang=zh_CN#rd)
* [Web server project explained - 13 Pitfalls and interview questions](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274431&idx=1&sn=2dd28c92f5d9704a57c001a3d2630b69&chksm=83ffb167b48838715810b27b8f8b9a576023ee5c08a8e5d91df5baf396732de51268d1bf2a4e&token=1686112912&lang=zh_CN#rd)
* Series complete

Star History
---------
[![Star History Chart](https://api.star-history.com/svg?repos=qinguoyi/TinyWebServer&type=Date)](https://star-history.com/#qinguoyi/TinyWebServer&Date)

C++11 implementation
------------
A cleaner C++11 version: [Webserver](https://github.com/markparticle/WebServer)


Acknowledgements
------------
*Linux High-Performance Server Programming*, by You Shuang.

Thanks to these friends for pull requests and help: [@RownH](https://github.com/RownH), [@mapleFU](https://github.com/mapleFU), [@ZWiley](https://github.com/ZWiley), [@zjuHong](https://github.com/zjuHong), [@mamil](https://github.com/mamil), [@byfate](https://github.com/byfate), [@MaJun827](https://github.com/MaJun827), [@BBLiu-coder](https://github.com/BBLiu-coder), [@smoky96](https://github.com/smoky96), [@yfBong](https://github.com/yfBong), [@liuwuyao](https://github.com/liuwuyao), [@Huixxi](https://github.com/Huixxi), [@markparticle](https://github.com/markparticle), [@blogg9ggg](https://github.com/Blogg9ggg).
