网络编程
1对1网络编程
基于TCP的网络编程
基于UDP编程



回顾:
    信号量集//计数器组成的数组
    计数器用于控制访问共享资源的最大的并行进程总数;
    信号量集的编程步骤:
    1. ftok();
    2. semget();
    3. semctl(semid,index,SETVAL,value);
    4. semop();
    5. semctl(semid,0,IPC_RMID)

    网络常识
    IP地址和端口
        网络编程其实就是网络版的进程间通信(IPC);
        网络编程(socket)分本地通信(IPC)和网络通信
    常用的网络命令:
        ipconfig
        ifconfig/ping//查看IP/查看网络是否畅通

今天
    网络编程

网络编程
    Unix/Linux系统是作为服务器操作系统存在至今的,因此Unix的网络功能是非常全面和强大的;
    网络编程编程其实有很成熟的套路,并且windows也能通用;
    网络编程又叫socket编程,socket的本意是插座,用于网络交互;
    socket编程分为本地通信和网络通信;本地通信由于其他IPC的存在,已经较少使用;重点就是网络通信;
    网络编程至少要写两个程序,服务器端和客户端;因此编程时需要考虑两端的程序;
socket(套接字)编程步骤
1.服务器端
    1.1创建一个socket,使用函数socket();
    int socket(int domain, int type, int protocol);
        参数:
        domain域,用来选择协议簇
            PF_UNIX PF_LOCAL PF_FILE //本地通信IPC
            PF_INET //网络通信(IPv4)
            PF_INET6 //网络通信(IPv6)
            注上面的PF都可以写成AF
        type用于选择通信类型
            SOCK_STREAM //数据流(TCP)
            SOCK_DGRAM  //数据报(UDP)
        protocol参数已经没有意义,因为协议已经被前两个参数决定,所以给0就可以了;
        函数返回socket描述符,出错返回-1;
    1.2准备通信地址(文件/IP和端口)
    有三个通信地址相关的结构体:
    struct sockaddr    //不存数据,只做参数类型;
    struct sockaddr_un    //存储本地通信的数据;
    本地通信使用的是一个文件做IPC媒介,因此存储了socket文件(.sock);
        #include <sys/un.h>
        struct sockaddr_un { //un是unix的缩写
            int sun_family; //协议簇//sun是sockaddr_un的缩写
            char sun_path[]; //文件名(带路径);
        };
    struct sockaddr_in //存储网络通信的数据
        #include <netinet/in.h>
        struct sockaddr_in {
            int sin_family; //协议簇
            short sin_port; //端口号
            struct in_addr sin_addr; //IP地址//其实in_addr只有一个成员
        };
    1.3绑定(socket描述符和通信地址)
    int bind(int sockfd, const struct sockaddr *addr,
                    socklen_t addrlen);
        bind(sockfd, (sockaddr*)(地址), sizeof(addr));
        第2个参数需要强制类型转换为(sockaddr*);
        绑定其实就是服务器对外开放了一个端口
    1.4通信(read()/write())
        使用读写文件描述符的方式读写socket描述符
    1.5关闭socket描述符
2.客户端
    步骤与服务器端一样;只需把第3步bind()绑定换成connect()连接即可;
    注connect()的参数和bind()完全一样;
    但bind()中提供的是服务器的IP和端口,connect()提供的是服务器端的IP和端口;自己的IP和端口封装在数据中发给服务器端,连接服务器时自己是不设防的;
    如果服务器在读,客户端应该写;如果服务器端在写,客户端应该读;
    //读写交互;
```
/*
 * 本地通信服务器端
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
int main() {
    //1 用socket()获取描述符
    int sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2 准备通信地址
    struct sockaddr_un addr;
    addr.sun_family = PF_UNIX;    //本地通信
    strcpy(addr.sun_path, "a.sock");    //会新建a.sock文件
    //3 用bind()绑定
    int res = bind(sockfd,
               (struct sockaddr *)&addr,    //强制类型转换一下
               sizeof(addr));
    // 判断返回值,如果返回-1表示失败;
    if (res == -1) {
        perror("bind"), exit(-1);
    }
    //4 通信
    char buf[100] = { };
    int i = 0;
    for (i = 0; i <= 9; i++) {
        int len = read(sockfd, buf, sizeof(buf));
        printf("希望读取%lu字节,实际读取%d字节,内容:%s\n", sizeof(buf), len, buf);
        /* sleep(1); */
    }
    //5 关闭描述符
    close(sockfd);
    printf("读取结束\n");
    return 0;
}
```


```
/*
 * 本地通信客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
int main() {
    //1 用socket()获取描述符
    int sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2 准备通信地址
    struct sockaddr_un addr;
    addr.sun_family = PF_UNIX;    //本地通信
    strcpy(addr.sun_path, "a.sock");    //会新建a.sock文件
    //3 用connect()连接
    int res = connect(sockfd,
              (struct sockaddr *)&addr,    //强制类型转换一下
              sizeof(addr));
    // 判断是否出错
    if (res == -1) {
        perror("connect"), exit(-1);
    }
    //4 读写
    int i = 0;
    for (i = 0; i <= 9; i++) {
        int len = write(sockfd, "hello", 5);
        printf("写入%d字节,%d\n", len, i);
        sleep(1);
    }
    //5 关闭描述符
    close(sockfd);
    printf("发送完毕\n");
    return 0;
}
```


另一个示例

```
/*****************************************
 * Copyright (C) 2021 * Ltd. All rights reserved.
 *******************************************/
//#pragma once
#ifndef __DOMAIN_SOCKET_H__
#define __DOMAIN_SOCKET_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <sys/types.h>

#define socket_path "/tmp/domain_server.socket"

    enum {
        eCmd_PreferredScanOutPlaneId = 1,
        eCmd_ScanOutPlaneDisplayEnable,
        eCmd_Invalid,
    };

    typedef struct DmSockMsgHeader_T {
        uint16_t seqId;
        uint16_t cmdId;
        uint32_t plLen;
    } DmSockMsgHeader_T;

#ifdef __cplusplus
}
#endif
#endif //__DOMAIN_SOCKET_H__
```


```
/*
 * domain socket server
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <signal.h>

#include "domain_socket.h"

int socket_read(int fd, char buf[], const int size) {
    fd_set rset;
    struct timeval tval;
    int ready = 0;
    int readLen = 0;
    int readRet = 0;

    do {
        FD_ZERO(&rset);
        FD_SET(fd, &rset);

        tval.tv_sec = 30;
        tval.tv_usec = 0;

        ready = select(fd+1, &rset, NULL, NULL, &tval);
        if (ready < 0) {
            //select error
            perror("select");
            break;
        } else if (ready == 0) {
            //timeout
            break;
        } else {
            if (!FD_ISSET(fd, &rset)) {
                continue;
            }
        }

        readRet = read(fd, buf+readLen, size);
        printf("read %d bytes\n", readRet);
        if (readRet > 0) {
            readLen += readRet;
        } else {
            if (readRet < 0 && (errno == EAGAIN || errno == EINTR)) {
                printf("%s readRet %d with EAGAIN or EINTR, try again\n", __func__, readRet);
                continue; /* can try again */
            }
            if (readRet == 0) {
                readLen = 0;
                break; /* peer shutdown, to close socket */
            } else {
                readLen = -1;
                break; /* read error, to close socket */
            }
        }

    } while (readLen < size);

    printf("read return %d\n", readLen);
    return readLen;
}

int main() {
    int ret = 0;
    printf("server socket pid = %d\n", getpid());

    //1 socket
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0); //用SOCK_STREAM//TCP
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }

    //2 add addr
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socket_path);

    //3 bind()
    unlink(socket_path);
    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("bind"), exit(-1);
    }
    printf("bind ok\n");

    //4 listen()
    ret = listen(sockfd, 3);
    if (ret == -1) {
        perror("listen"); exit(-1);
    }

    while (1) {
        //5 accept()
        struct sockaddr_un from;
        socklen_t len = sizeof(from);

        int fd = accept(sockfd, (struct sockaddr *)&from, &len);
        if (fd == -1) {
            perror("accept");
            continue;
        }
        printf("%s connected\n", from.sun_path);

        //6 read/write
        char buf[100] = { };
        DmSockMsgHeader_T header;
        int readLen = 0;
        int value = 0;

        do {
            memset(&header, 0, sizeof(header));
            memset(buf, 0, sizeof(buf));
            //read header
            readLen = socket_read(fd, buf, sizeof(DmSockMsgHeader_T));
            if (readLen == 0) {
                printf("the peer is shutdown\n");
                break;
            }

            if (readLen != sizeof(DmSockMsgHeader_T)) {
                printf("read header error\n");
                break;
            }

            memcpy(&header, buf, sizeof(header));
            if ((header.cmdId == 0)
                    && (header.seqId == 0)) {
                printf("read error, invalid header\n");
                break;
            }

            //read payload
            readLen = socket_read(fd, buf+sizeof(header), header.plLen);
            if (readLen != header.plLen) {
                printf("read data error, expect len:%d, actually:%d\n", header.plLen, readLen);
                break;
            }
            memcpy(&value, buf+sizeof(header), sizeof(value));
            printf("received client:%s> cmd:%d, data:0x%x\n", from.sun_path, header.cmdId, value);

            sprintf(buf, "received %d bytes", readLen);
            write(fd, buf, strlen(buf));
        } while (1);

        //7 close
        close(fd);
    }

    close(sockfd);
    unlink(socket_path);
    return 0;
}
```


```
/*
 * domain socket client
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "domain_socket.h"

int main() {
    int ret = 0;

    //1 socket
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }

    // bind
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    sprintf(addr.sun_path, "/tmp/domain_client-%05d.socket", getpid());
    unlink(addr.sun_path);
    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind");
        exit(-1);
    }

    //2 add addr
    struct sockaddr_un srv;
    memset(&srv, 0, sizeof(srv));
    srv.sun_family = AF_UNIX;
    strcpy(srv.sun_path, socket_path);

    //3 connect
    ret = connect(sockfd, (struct sockaddr *)&srv, sizeof(srv));
    if(ret == -1) {
        perror("connect");
        exit(-1);
    }

    //4 read/write
    char buf[100];
    memset(buf, 0, sizeof(buf));
    DmSockMsgHeader_T header;
    int cmdId = 0;
    int value = 0;
    memset(&header, 0, sizeof(header));

    header.seqId = 1;
    printf("please type your cmd id:\n");
    scanf("%d", &cmdId);
    printf("please type cmd value:\n");
    scanf("%d", &value);
    header.cmdId = cmdId;
    header.plLen = sizeof(value);
    memcpy(buf, &header, sizeof(header));
    memcpy(buf+sizeof(header), &value, sizeof(value));

    //write
    write(sockfd, buf, sizeof(header)+sizeof(value));
    printf("send: cmdid:%d, value:0x%x\n", cmdId, value);

    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("server:%s\n", buf);

    //5 close
    close(sockfd);
    unlink(addr.sun_path);
    return 0;
}
```


```
#target: prerequisites 
#	command
####################################################
# Author      : longbin
# Created date: 2020-02-19 15:25:14
####################################################

all:
	gcc domain-server.c -o server
	gcc domain-client.c -o client

clean:
	-rm -v server client
```

注使用网络编程时,网络通信地址中的IP和端口都需要使用转换函数
    需要包含sys/socket.h和arpa/inet.h与netinet/in.h
    in_addr_t inet_addr(const char *cp);
        /* 点分十进制的IP转换为整数IP;  */
    char *inet_ntoa(struct in_addr in);
        /* 整数转为点分十进制的函数 */

    端口转换函数
    #include <arpa/inet.h>
    uint32_t htonl(uint32_t hostlong);
    uint16_t htons(uint16_t hostshort); /* 端口,本机格式转换为网络格式host to network hostshort; */
    uint32_t ntohl(uint32_t netlong);
    uint16_t ntohs(uint16_t netshort);

/*
 * UDP网络编程服务端
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LOCALIP "127.0.0.1"
#define LOCALPORT 50015
#define PEERIP "127.0.0.1"
#define PEERPORT 50014

int main() {
    /* 1获取socket描述符 */
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }

    /* 2准备通信地址 */
    struct sockaddr_in servaddr;
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(LOCALPORT);    //host to network hostshort
    servaddr.sin_addr.s_addr = inet_addr(LOCALIP);
    //servaddr.sin_addr = "172,17.5.3"; //类型不兼容,不可以
    //servaddr.sin_addr.s_addr = inet_addr("172.17.5.3");/* 取结构中的成员转换函数 */

    /* 3绑定 */
    //bind IP地址为本服务器IP
    int res = 0;
    res = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (res == -1) { perror("bind"), exit(-1);}
    printf("bind ok\n");

    char buf[100] = { };
    char arr[100] = { };
    int len = 0;
    int iloop = 0;

#if 0
    /* 4通信 read/write(client connected) recvfrom/sendto */
    len = read(sockfd, buf, sizeof(buf));
    if (len == -1) {
        perror("read"), exit(-1);
    }
    printf("want to read %lu bytes, actrually read %d bytes:%s\n", sizeof(buf), len, buf);

    for (iloop=0; iloop<10; iloop++) {
        snprintf(arr, sizeof(arr), "fromserver#%d", iloop);
        len = write(sockfd, arr, strlen(arr)); //will return error for udp server
        if (len == -1) {
            printf("errno %d:%s\n", errno, strerror(errno));
            perror("write");
        }
        printf("%d write: %s\n", len, arr);
        sleep(1);
    }

#else

    /* 4通信 read/write(client connected) recvfrom/sendto */
    struct sockaddr cliaddr;
    socklen_t clilen = sizeof(cliaddr); /* cannot set to 0 */
    memset(&cliaddr, 0, sizeof(cliaddr)); /* should memset */
    len = recvfrom(sockfd, buf, sizeof(buf), 0, &cliaddr, &clilen);
    char *from = inet_ntoa(((struct sockaddr_in *)&cliaddr)->sin_addr);
    int fromport = ntohs(((struct sockaddr_in *)&cliaddr)->sin_port);
    printf("%d recvfrom %s:%d %s\n", len, from, fromport, buf);

    for (iloop=0; iloop<500; iloop++) {
        snprintf(arr, sizeof(arr), "fromserver#%d", iloop);
    # if 1
        struct sockaddr_in repaddr;
        socklen_t replen = sizeof(struct sockaddr); /* cannot set to 0 */
        memset(&repaddr, 0, sizeof(struct sockaddr)); /* should memset */

        repaddr.sin_family = PF_INET;
        repaddr.sin_port = htons(PEERPORT);//client port
        repaddr.sin_addr.s_addr = inet_addr(PEERIP); //client ip
        len = sendto(sockfd, arr, strlen(arr), 0, (const struct sockaddr *)&repaddr, replen);
    # else
        len = sendto(sockfd, arr, strlen(arr), 0, (const struct sockaddr *)&cliaddr, clilen);
    # endif
        if (len == -1) {
            printf("errno: %d\n", errno);
            perror("sendto");
        }
        printf("%d sendto: %s\n", len, arr);
        /* sleep(1); */
        usleep(20000); /* 20ms */
    }
#endif

    //5关闭socket描述符
    close(sockfd);
    return 0;
}


/*
 * UDP网络编程客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LOCALIP "127.0.0.1"
#define LOCALPORT 50014
#define PEERIP "127.0.0.1"
#define PEERPORT 50015

int main() {
    /* 1获取socket描述符 */
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }

    /* 2准备通信地址 */
    struct sockaddr_in servaddr;
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(PEERPORT);    //host to network hostshort
    servaddr.sin_addr.s_addr = inet_addr(PEERIP);
    //servaddr.sin_addr = "172,17.5.3"; //类型不兼容,不可以
    //servaddr.sin_addr.s_addr = inet_addr("172.17.5.3");/* 取结构中的成员转换函数 */

    /* bind绑定本地地址,client非必须 */
    int res = 0;
    int reuseAddrOn = 1;
    struct sockaddr_in localaddr;
    localaddr.sin_family = PF_INET;
    localaddr.sin_port = htons(LOCALPORT);    //client port
    localaddr.sin_addr.s_addr = inet_addr(LOCALIP);
    res = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddrOn, sizeof(reuseAddrOn));
    if (res == -1) { printf("set SO_REUSEADDR error %d:%s", errno, strerror(errno)), exit(-1); }

    res = bind(sockfd, (struct sockaddr *)&localaddr, sizeof(struct sockaddr));
    if (res == -1) { perror("bind"), exit(-1);}

    char buf[100] = "fromclient";
    int len = 0;
    int iloop = 0;
    int cnt = 0;

#if 0
    /* 3连接 connect to server */
    /* connect can improve efficiency for udp client data recv/send */
    //connect to server ip
    res = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (res == -1) { perror("connect"), exit(-1);}

    /* 4通信 read/write(connected) recvfrom/sendto */
    len = write(sockfd, buf, strlen(buf));
    printf("%d write:%s\n", len, buf);

    for (iloop=0; iloop<10; iloop++) {
        len = read(sockfd, buf, sizeof(buf));
        if (len == -1) {
            printf("%d errno:%d\n", len, errno);
            perror("read");
        } else {
            buf[len] = '\0';
            printf("%d read: %s\n", len, buf);
            cnt += 1;
        }
    }

#else

    /* 4通信 read/write(connected) recvfrom/sendto */
    len = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (len == -1) {
        printf("%d errno:%d\n", len, errno);
        perror("sendto");
    }
    printf("%d sendto: %s\n", len, buf);

    int readRet = 0;
    int readLen = 0;
    int select_ret = 0;
    struct timeval tval;
    fd_set rset;
    struct sockaddr repaddr;
    /* for (iloop=0; iloop<10; iloop++) { */
    do {
        FD_ZERO(&rset);
        FD_SET(sockfd, &rset);

        tval.tv_sec = 10; /* seconds */
        tval.tv_usec = 0;
        readRet = 0;

        /* monitor sockfd and wait until socket is readable or timeout */
        select_ret = select(sockfd+1, &rset, NULL, NULL, &tval);
        if (0 == select_ret)
        {
            printf("select rset timeout\n");
            break; /* timeout, to close socket */
        }
        if (true != ((0 < select_ret) && FD_ISSET(sockfd, &rset)))
        {
            /* received event but its not sockfd readable, ignore it */
            continue;
        }

        memset(&repaddr, 0, sizeof(struct sockaddr));
        socklen_t replen = sizeof(struct sockaddr);
        /* readRet = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);//dont care from addr */
        readRet = recvfrom(sockfd, buf, sizeof(buf), 0, &repaddr, &replen);
        if (readRet > 0) {
            buf[readRet] = '\0';
            readLen += readRet;
            cnt += 1;
            /* char *inet_ntoa(struct in_addr in); */
            char *from = inet_ntoa(((struct sockaddr_in *)&repaddr)->sin_addr);
            int fromport = ntohs(((struct sockaddr_in *)&repaddr)->sin_port);
            printf("%d recvfrom %s:%d %s\n", readRet, from, fromport, buf);
        }
        else {
            if (readRet < 0 && (errno == EAGAIN || errno == EINTR))
            {
                /* can try again */
                continue;
            }
            if (readRet == 0)
            {
                readLen = 0;
                printf("the peer connection is closed.\n");
                break; /* peer shutdown, to close socket */
            }
            else
            {
                /* read returnt error and cannot retry again */
                readLen = -1;
                printf("recv data error, errno=%d:%s\n", errno, strerror(errno));
                break; /* read error, to close socket */
            }

        }
    } while (1);
    /* } while (0); */
    printf("total recv %d packets\n", cnt);
    if (readLen <= 0) {
        /* close socket */
        /* sockfd disconnected */
        printf("sockfd disconnected\n");
    }

#endif

    //5关闭socket描述符
    close(sockfd);
    return 0;
}


    以上写的是典型的1对1的模式,商业开发更多使用的是基于TCP和基于UDP的开发模式;

基于TCP协议的网络编程
    TCP是有连接协议,所有操作基于客户端和服务器端且保持连接,会重发一切的错误数据;
TCP协议一对多编程步骤
1.服务器端//在以前基础上添加两步;
    1.socket()获取一个socket描述符;
    2.准备通信地址;
    3.bind()绑定;
    4.listen()监听;//可以设置当多个客户端同时访问时,只能操作一个,其他的放入队列中;listen()用于设置队列的最大长度;
    5.等待客户端连接accept();
    int accept(int sockfd, sockaddr* addr, socklen_t* addrlen);
        参数:
        sockfd 就是第一步的返回值;
        addr是用于接收连接的客户端通信地址;
        addrlen是传入传出参数;
            先传入通信地址的大小,再传出获取到的客户端通信地址的大小;
        返回新的描述符,用于和客户端的读写通信;
    6.读写;对于第5步返回的描述符;
    7.关闭两个socket描述符;//socket()和accept()各自返回的描述符;
2.客户端不需要做任何更改;
/*
 * TCP网络编程服务端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
int main() {
    printf("服务器 pid = %d\n", getpid());
    //1 获取socket描述符
    int sockfd = socket(PF_INET, SOCK_STREAM, 0); //用SOCK_STREAM//TCP
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2 准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);
    /* addr.sin_addr.s_addr = inet_addr("172.17.5.3"); */
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //解决地址被占用的问题address already in use
    int reuseaddr = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
            sizeof(reuseaddr));
    //3 bind()
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        perror("bind"), exit(-1);
    }
    printf("bind ok\n"); //bind()成功是一个里程碑,意味着服务器对外开放
    //4 listen()
    listen(sockfd, 100); //最多可以监听100+1个;
    //5 accept()
    struct sockaddr_in from; //用来存放连接到的客户端地址
    socklen_t len = sizeof(from);
    int fd = accept(sockfd, (struct sockaddr *)&from, &len);
    //会等待客户端的连接;//accept()是阻塞函数
    //如果客户端没有连接会一直等待;
    if (fd == -1) {
        perror("accept"), exit(-1);
    }
    printf("%s连接上了\n", inet_ntoa(from.sin_addr));
    //6 读写
    char buf[100] = { }, buf1[100] = { };
    res = read(fd, buf, sizeof(buf));
    if (res == -1) {
        return -1;
    }
    printf("希望读取%lu字节,实际读取%d字节from client>%s\n", sizeof(buf), res, buf);
    strcpy(buf1, "welcome");
    write(fd, buf1, strlen(buf1)); //回发数据;
    //7 关闭两个描述符
    close(sockfd);
    close(fd);
    //close(sockfd);
    return 0;
}
/*
 * TCP网络编程客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    //1获取socket描述符
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr = "";//不可以
    //addr.sin_addr.s_addr = inet_addr("172.17.5.3");    //取结构中的成员转换函数
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //IP地址为连接目标
    //3连接
    int res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    //if(res == -1){perror("bind"),exit(-1);}
    //4通信
    printf("请输入一个字符串\n");
    char buf[100] = { };
    scanf("%s", buf);
    write(sockfd, buf, sizeof(buf));
    printf("已经写入\n");
    read(sockfd, buf, sizeof(buf));
    printf("server:%s\n", buf);
    //5关闭socket描述符
    close(sockfd);
    return 0;
}
    
练习1
    改良服务器端的代码,改成可以为多个客户端服务的版本
    加无限循环,退出时用信号2;
    因为listen()负责监听,所以把listen()之后改为无限循环;

练习2
    改良程序,客户端要求能多次输入(scanf),并把客户端的每次输入发给服务器端,服务器端做转发(就是把客户端的输入发回给客户端);客户端输入bye退出;
    客户端加循环,服务器也随之加;
    客户端退出交互循环,服务器也退出交互循环;
/*
 * TCP网络编程服务端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
int sockfd;
void fa(int signo) {
    printf("捕获到信号%d\n", signo);
    if (signo == 2) {
        printf("服务器即将关闭\n");
        close(sockfd); //回收资源时释放sockfd;
        sleep(1);
        exit(0);
    }
}
int main() {
    signal(SIGINT, fa);
    printf("按Ctrl+C退出服务器\n");
    printf("服务器已启动 pid = %d\n", getpid());
    //1 获取socket描述符
    sockfd = socket(PF_INET, SOCK_STREAM, 0);    //用SOCK_STREAM//TCP
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2 准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);
    addr.sin_addr.s_addr = inet_addr("172.17.5.3");
    //解决地址被占用的问题address already in use
    int reuseaddr = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
           sizeof(reuseaddr));
    //3 bind()
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        perror("bind"), exit(-1);
    }
    printf("bind ok\n");
    //4 listen()
    listen(sockfd, 100);
    while (1) {
        //5 accept()
        struct sockaddr_in from;
        socklen_t len = sizeof(from);
        int fd = accept(sockfd, (struct sockaddr *)&from, &len);
        //会等待客户端的连接;//accept()是阻塞函数
        if (fd == -1) {
            perror("accept"), exit(-1);
        }
        pid_t pid = fork();    //支持多进程
        if (pid == 0) {
            printf("%s已连接\n", inet_ntoa(from.sin_addr));
            //6 读写
            char buf[100] = { }, buf1[100] = {
            };
            while (1) {
                res = read(fd, buf, sizeof(buf));
                if (res == -1) {
                    break;
                }
                printf("接收到内容:\nclient>%s\n", buf);
                if (!strcmp(buf, "bye")) {
                    break;
                }
                strcpy(buf1, buf);
                write(fd, buf1, strlen(buf1));
                //write(fd,buf1,strlen(buf1)+1);//可以不用清空
                memset(buf, 0, strlen(buf));    //清零
                memset(buf1, 0, strlen(buf1));    //清零
            }
            //7 关闭两个描述符
            close(fd);    //关闭子进程fd
        }
        close(fd);    //关闭父进程fd
        printf("服务器 pid = %d\n", getpid());
    }
    //close(sockfd);
    return 0;
}
/*
 * TCP网络编程客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    //1获取socket描述符
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr = "";//不可以
    addr.sin_addr.s_addr = inet_addr("172.17.5.3");    //取结构中的成员转换函数
    //IP地址为连接目标
    //3连接
    int res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    //if(res == -1){perror("bind"),exit(-1);}
    //4通信
    char buf[100] = { };
    char ret[100] = { };
    while (1) {
        printf("请输入聊天信息:>");
        printf("如退出请输入bye,否则按enter键:\n>");
        scanf("%s", buf);
        scanf("%*[^\n]");
        scanf("%*c");
        write(sockfd, buf, sizeof(buf));
        if (!strcmp(buf, "bye")) {
            break;
        }
        printf("已发送%s\n", buf);
        read(sockfd, ret, sizeof(ret));
        printf("服务器返回内容:\n>>%s\n", ret);
        memset(buf, 0, strlen(buf));    //清0
        memset(ret, 0, strlen(ret));
    };
    //5关闭socket描述符
    close(sockfd);
    printf("客户端已退出\n");
    return 0;
}


UDP的编程
    UDP协议是无连接协议,不保持连接;因此UDP不保证数据的完整和正确,因为不会重发错误数据;
    TCP占用资源大,但能保证数据的正确完整;
    UDP占用资源小,但不保证数据的正确完整;
    UDP虽然是无连接协议,但是也可以建立UDP连接;
    QQ是基于UDP的,大部分网络程序也是基于UDP的;

    SOCK_STREAM    //数据流(用于TCP);卖自来水
    SOCK_DGRAM    //数据报(用于UDP);卖瓶装矿泉水

    UDP不需要connect(),它使用不同的数据发送函数和接收函数;
    sendto()//发送,相当于connect()和write()的结合
    ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                    const struct sockaddr* dest_addr, socklen_t addrlen);
        成功返回发送数据的大小,失败返回-1;
    sendto(sockfd, buf1, sizeof(buf1), 0,
            (struct sockaddr*)&from, sizeof(from));
    recvfrom()//接收
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
        成功返回接收到的数据大小,失败返回-1;
    socklen_t len = sizeof(from);
    recvfrom(sockfd, buf, sizeof(buf), 0,
                (struct sockaddr*)&from, &len);
    //注意最后一个参数与sendto的最后一个参数类型不同
    无连接的UDP发送数据时无法使用write(),而接收数据时如不需要保留发送方通信地址可以使用read(),如果向直到发送方是谁需要使用recvfrom();
/*
 * UDP网络编程服务端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    //1获取socket描述符
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr.s_addr = inet_addr("172.17.5.3");    //取结构中的成员转换函数
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //IP地址为本服务器IP
    //3绑定
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    //if(res == -1){perror("bind"),exit(-1);}
    //4通信
    printf("通信已建立\n");
    char buf[100] = { }, buf1[100] = { };
    //int res1 = read(sockfd, buf, sizeof(buf));
    //如果还要得到客户端的地址,需要用recvfrom();
    struct sockaddr_in from;
    socklen_t len = sizeof(from);
    int res1 = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);    //接收     
    strcpy(buf1, buf);
    if (res1 == -1) {
        perror("read"), exit(-1);
    }
    printf("已经读取%d字节,\n内容:%s\n", res1, buf);
    sendto(sockfd, buf1, sizeof(buf1), 0, (struct sockaddr *)&from, sizeof(from));    //发送
    printf("已返回%s\n", buf1);
    //5关闭socket描述符
    close(sockfd);
    return 0;
}
/*
 * UDP网络编程客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    //1获取socket描述符
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr.s_addr = inet_addr("172.17.5.3");    //取结构中的成员转换函数
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //IP地址为连接目标
    //3连接//无连接的UDP不需要connect()
    //int res = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    //if(res == -1){perror("bind"),exit(-1);}
    //4通信
    printf("请输入一个字符串\n");
    char buf[100] = { }, buf1[100] = { };
    scanf("%s", buf);
    //write(sockfd,buf,sizeof(buf));//write()发送不了无连接的UDP
    sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr,
           sizeof(addr));
    //sendto()相当于connect()与write()的结合;
    printf("已经写入\n");
    read(sockfd, buf1, sizeof(buf1));
    printf("服务器返回:%s\n", buf1);
    //5关闭socket描述符
    close(sockfd);
    return 0;
}

使用UDP做时间服务器
/*
 * UDP做时间服务器
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
int sockfd;
void fa(int signo) {
    printf("\nserver down...\n");
    sleep(1);
    printf("...\n");
    close(sockfd);
    exit(0);
}
int main() {
    printf("请按Ctrl+C退出系统\n");
    signal(SIGINT, fa);
    printf("本服务器已启动pid = %d\n", getpid());
    //1获取socket描述符
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr.s_addr = inet_addr("172.17.5.3");    //取结构中的成员转换函数
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("本服务器IP为%s\n", inet_ntoa(addr.sin_addr));
    //IP地址为本服务器IP
    //3绑定
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    //if (res == -1) { perror("bind"), exit(-1); }
    //4通信
    printf("通信已建立...\n");
    char buf[100] = { }, buf1[100] = { };
    //int res1 = read(sockfd, buf, sizeof(buf));
    struct sockaddr_in from;
    socklen_t len = sizeof(from);
    while (1) {
        int res1 = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);    //接收     
        if (res1 == -1) {
            perror("read"), exit(-1);
        }
        strcpy(buf1, buf);
        printf("%s已连接\n", inet_ntoa(from.sin_addr));
        printf("已经读取%d字节:%s\n", res1, buf);
        /* 取系统时间 */
        time_t cur_time = time(0);
        struct tm *cur = localtime(&cur_time);
        //strcpy(buf1, ctime(&cur_time));//自动转换格式的时间
        sprintf(buf1, "系统时间是%4d-%02d-%02d %02d:%02d:%02d",
            cur->tm_year + 1900, cur->tm_mon + 1, cur->tm_mday,
            cur->tm_hour, cur->tm_min, cur->tm_sec);
        //变长的buf要清0,定长的buf不用清0;
        sendto(sockfd, buf1, strlen(buf1), 0, (struct sockaddr *)&from, sizeof(from));    //发送
        printf("已返回%s\n", buf1);
    }
    //5关闭socket描述符
    //close(sockfd);
    return 0;
}
/*
 * UDP时间服务客户端
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    //1获取socket描述符
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket"), exit(-1);
    }
    //2准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2222);    //host to network hostshort
    //addr.sin_addr = "";//不可以
    char ip_addr[20] = { };
    printf("请输入一个IP地址:\n>>");
    scanf("%s", ip_addr);
    //addr.sin_addr.s_addr = inet_addr("172.17.5.3");
    addr.sin_addr.s_addr = inet_addr(ip_addr);    //取结构中的成员转换函数
    //IP地址为连接目标
    //3连接//无连接的UDP不需要connect()
    //int res = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    //if(res == -1){perror("bind"),exit(-1);}
    //4通信
    printf("请输入一个字符串\n");
    char buf[100] = { }, buf1[100] = {
    };
    scanf("%s", buf);
    //write(sockfd,buf,sizeof(buf));//发送不了无连接的UDP
    sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr,
           sizeof(addr));
    //sendto()相当于connect()与write()的结合;
    printf("已经写入\n");
    read(sockfd, buf1, sizeof(buf1));
    printf("服务器返回:>>>>>>%s\n", buf1);
    //5关闭socket描述符
    close(sockfd);
    return 0;
}

从sockaddr中取得Ip地址和端口号
    在socket编程中,服务器端accept()等待一个客户端的连接,当连接成功后,accept拷贝客户端的地址信息到sin_addr里面,我们如何从sin_addr取得此客户端的Ip地址和端口号呢?
　　实际上,当sockaddr_in.sin_family = AF_INET时,sockaddr = sockaddr_in;
　　据此,我们可以做一下转换,就可以利用inet_ntoa()来得到ip地址和端口号:
　　int new_fd = accept(sock, &clientAddr, &sin_size);
　　if (new_fd < 0) {
        printf("accept error\n");
　　} else {
        //将sockaddr强制转换为sockaddr_in
    　　sockaddr_in sin;
    　　memncpy(&sin, &clientAddr, sizoef(sin));
    　　//取得ip和端口号
    　　sprintf(info.ip, inet_ntoa(sin.sin_addr));
    　　info.port = sin.sin_port;
    　　info.sock = new_fd;
　　}


