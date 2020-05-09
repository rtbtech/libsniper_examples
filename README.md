## libsniper usage examples

## Build with docker

You could use Dockerfile to build examples:

1 Clone repository with dependencies 
```
git clone --recursive https://github.com/rtbtech/libsniper_examples.git
```

2 Run docker build and wait for a while
```
sudo docker build -t libsniper_examples .
```

3 Run hello_server app from docker container
```
docker run -it --net=host libsniper_examples /apps/hello_server
```

```
[2020-05-09 19:39:58.997] [info] hello_server: (May  9 2020, 19:36:55 UTC)
[2020-05-09 19:39:58.997] [info] hello_server starting...
[2020-05-09 19:39:58.998] [info] hello_server started
^C[2020-05-09 19:40:00.173] [warning] Stop signal. Exiting
[2020-05-09 19:40:00.173] [info] hello_server stopped
```

4 Test hello_server app

```$ ab -v 4 "http://127.0.0.1:8080/"```

```
   This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
   Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
   Licensed to The Apache Software Foundation, http://www.apache.org/
   
   Benchmarking 127.0.0.1 (be patient)...INFO: GET header == 
   ---
   GET / HTTP/1.0
   Host: 127.0.0.1:8080
   User-Agent: ApacheBench/2.3
   Accept: */*
   
   
   ---
   LOG: header received:
   HTTP/1.0 200 OK
   Access-Control-Allow-Origin: *
   Server: libsniper
   Connection: close
   Date: Sat, 09 May 2020 19:41:40 GMT
   Content-Length: 0
   
   
   LOG: Response code = 200
   ..done
   
   
   Server Software:        libsniper
   Server Hostname:        127.0.0.1
   Server Port:            8080
   
   Document Path:          /
   Document Length:        0 bytes
   
   Concurrency Level:      1
   Time taken for tests:   0.000 seconds
   Complete requests:      1
   Failed requests:        0
   Total transferred:      145 bytes
   HTML transferred:       0 bytes
   Requests per second:    4201.68 [#/sec] (mean)
   Time per request:       0.238 [ms] (mean)
   Time per request:       0.238 [ms] (mean, across all concurrent requests)
   Transfer rate:          594.96 [Kbytes/sec] received
   
   Connection Times (ms)
                 min  mean[+/-sd] median   max
   Connect:        0    0   0.0      0       0
   Processing:     0    0   0.0      0       0
   Waiting:        0    0   0.0      0       0
   Total:          0    0   0.0      0       0
```
