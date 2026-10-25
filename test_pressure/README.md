Server stress test
===============
WebBench is a well-known website stress tool, developed by [Lionbridge](http://www.lionbridge.com).

> * Compare different services on the same hardware, and the same service on different hardware.
> * Reports two server figures: requests answered per second, and bytes transferred per second.




Test rules
------------
* Example

    ```C++
	webbench -c 500  -t  30   http://127.0.0.1/phpionfo.php
    ```
* Parameters

> * `-c` is the number of clients
> * `-t` is the duration


Test results
---------
WebBench stress-tested the server and reached tens of thousands of concurrent connections.
> * Total concurrent connections: 10500
> * Time accessing the server: 5s
> * Requests answered: 552852 pages/min
> * Data transferred: 1031990 bytes/sec
> * Every request succeeded

<div align=center><img src="https://github.com/twomonkeyclub/TinyWebServer/blob/master/root/testresult.png" height="201"/> </div>
