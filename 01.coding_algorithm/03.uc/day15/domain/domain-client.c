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

