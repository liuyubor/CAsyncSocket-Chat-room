# CAsyncSocket Chat room

## 运行截图

![Servert and Client](./Server%20and%20%20Client.PNG "Servert and Client")

## 说明

服务器和客户端都使用用 CAsyncSocket 类来进行通信，所以发送消息时是异步的，不会造成阻塞。但是发送文件使用的是 CSocket 类，所以发送文件时，程序会阻塞，尤其是发送大文件时候。

> 发送文件缓冲设置为 4096 bytes，TCP MTU一般为1500字节左右。所以设置一个合理的缓冲区对阻塞时间十分重要。