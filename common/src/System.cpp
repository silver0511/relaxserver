/*
 * file_name: System.cpp
 * file_detail:base system tool
 * created by silver0511
 */

#include "common/System.h"

USING_RELAX_NAMESPACE

System::System()
{

}

System::~System()
{

}

void System::sleep(ulong ms_time)
{
    ms_time = ms_time << 10; //*1024
    usleep(ms_time);
}

int64 System::get_micro_time()
{
    struct timeval now;
    gettimeofday(&now,NULL);
    return now.tv_sec * 1000000 + now.tv_usec;
}

int64 System::get_ms_time()
{
    return (System::get_micro_time() / 1000);
}

time_t System::get_time()
{
    return time(NULL);
}

int System::get_ms_count()
{
    struct timeval now;
    gettimeofday(&now,NULL);
    return now.tv_usec / 1000;
}

void System::get_local_time(tm &s_local_time)
{
    time_t t_now = time(NULL);
    localtime_r(&t_now, &s_local_time);
}

void System::init_random()
{
    int l_value = System::get_time();
    srand(l_value);
    int l_temp_rand = (rand() + l_value) % 16 + 8;
    for(int i = 0; i < l_temp_rand; i++)
        rand();
}