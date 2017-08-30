/*
 * file_name: test_system.cpp
 * file_detail:test System.h interface
 * created by silver0511
 */

#include "common/System.h"

USING_RELAX_NAMESPACE

int main()
{
    printf("before sleep start================================= \n");
    System::init_random();
    printf("test init_random() rand:%d \n", rand());
    printf("test get_micro_time():%lld \n", System::get_micro_time());
    printf("test get_ms_time():%lld \n", System::get_ms_time());
    printf("test get_time():%d \n", System::get_time());
    struct tm s_local_tm = {0};
    System::get_local_time(s_local_tm);
    int milli_time = System::get_ms_count();
    printf("test get_local_time() and get_ms_count() %04d%02d%02d %02d:%02d:%02d-%03d \n",
             s_local_tm.tm_year + 1900, s_local_tm.tm_mon + 1, s_local_tm.tm_mday,
             s_local_tm.tm_hour, s_local_tm.tm_min, s_local_tm.tm_sec, milli_time);
    printf("before sleep  end================================= \n");

    System::sleep(1000 * 5);

    printf("after sleep ================================= \n");
    System::init_random();
    printf("test init_random() rand:%d \n", rand());
    printf("test get_micro_time():%lld \n", System::get_micro_time());
    printf("test get_ms_time():%lld \n", System::get_ms_time());
    printf("test get_time():%d \n", System::get_time());
    s_local_tm = {0};
    System::get_local_time(s_local_tm);
    milli_time = System::get_ms_count();
    printf("test get_local_time() and get_ms_count() %04d%02d%02d %02d:%02d:%02d-%03d \n",
           s_local_tm.tm_year + 1900, s_local_tm.tm_mon + 1, s_local_tm.tm_mday,
           s_local_tm.tm_hour, s_local_tm.tm_min, s_local_tm.tm_sec, milli_time);

    printf("after sleep ================================= \n");
    return 1;
}