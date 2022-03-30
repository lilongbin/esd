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

