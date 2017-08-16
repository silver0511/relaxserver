/*
 * file_name: ServerConst.h
 * file_detail:common server const define
 * created by silver0511
 */

#ifndef __RX__SERVER_CONST_H__
#define __RX__SERVER_CONST_H__
#include "stdafx.h"

RELAX_NAMESPACE_BEGIN

    enum E_SERVER_TYPE
    {
        TCP_COMET = 1,
        WS_COMET = 2,
        HTTP_COMET = 3,

        USER_SERVER = 10,
        GC_SERVER,
        SC_SERVER,
        FD_SERVER,
        DB_SERVER,
        EC_SERVER,
        OFFCIAL_SERVER,
        GROUP_SERVER,

        SC_ROUTE = 100,
        GC_ROUTE,
        PC_ROUTE,

        ALL_SERVER
    };

RELAX_NAMESPACE_END
#endif //__RX__SERVER_CONST_H__
