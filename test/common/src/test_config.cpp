/*
 * file_name: test_config.h
 * file_detail:test base config interface
 * created by silver0511
 */

#include <pthread.h>
#include "common/BaseConfig.h"
#include "common/System.h"

USING_RELAX_NAMESPACE

ServerConfig server_config;
int64 start_time = 0;

void *thread_func(void* p)
{
    int64 end_time = System::get_ms_time();
    if((end_time - start_time) > 1000 * 5)
    {
        start_time = end_time;
        server_config.check_event((end_time - start_time));
        server_config.get_dump();
    }
}

int main()
{
    start_time = System::get_micro_time();
    server_config.load("./config/test/common/test_config.json");
    server_config.read();
    server_config.get_dump();
    pthread_t lthread;
    pthread_create(&lthread, NULL, thread_func, NULL);
    getchar();
    return 0;
}