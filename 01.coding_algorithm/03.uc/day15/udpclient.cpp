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
    servaddr.sin_port = htons(PEERPORT);	//host to network hostshort
    servaddr.sin_addr.s_addr = inet_addr(PEERIP);
    //servaddr.sin_addr = "172,17.5.3"; //类型不兼容,不可以
    //servaddr.sin_addr.s_addr = inet_addr("172.17.5.3");/* 取结构中的成员转换函数 */

    /* bind绑定本地地址,client非必须 */
    int res = 0;
    int reuseAddrOn = 1;
    struct sockaddr_in localaddr;
    localaddr.sin_family = PF_INET;
    localaddr.sin_port = htons(LOCALPORT);	//client port
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

