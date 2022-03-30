/*****************************************
 * Copyright (C) 2021 * Ltd. All rights reserved.
 *
 * File name   : domain_socket.h
 * Author      : longbin
 * Created date: 2021-06-15 14:35:54
 * Description : 
 *
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

