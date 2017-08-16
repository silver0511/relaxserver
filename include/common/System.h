/*
 * file_name: System.h
 * file_detail:base system tool
 * created by silver0511
 */


#ifndef __RX__SYSTEM_H__
#define __RX__SYSTEM_H__
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

    class System
    {
    public:
        System();
        ~System();
        //millisecond
        static void sleep(ulong ms_time);
        //microsecond
        static int64 get_micro_time();
        //millisecond
        static int64 get_ms_time();
        //second
        static time_t get_time();
        //milli count
        static int get_ms_count();
        //localtime
        static void get_local_time(tm &s_local_time);
        //random seed
        static void init_random();
    private:
    };

RELAX_NAMESPACE_END

#endif //__RX__SYSTEM_H__
