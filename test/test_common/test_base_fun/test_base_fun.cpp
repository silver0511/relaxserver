/*
 * file_name: test_base_fun.cpp
 * file_detail:test BaseFun.h interface
 * created by silver0511
 */

#include "common/BaseFun.h"

USING_RELAX_NAMESPACE

int main()
{
    printf("test inc_index():%d \n", inc_index(11, 1, 10));
    printf("test dec_index():%d \n", dec_index(12, 1, 10));
    const char *src = "你好啦啦啦";
    char des[1024] = {0};
    bool result = memcpy_safe((char *)src, strlen(src), des, 1024);
    printf("test memcpy_safe() result:%d, src:%s, des:%s \n", result, src, des);
    printf("test get_app_path():%s \n", get_app_path().c_str());
    printf("test get_full_path():%s \n", get_full_path("test_full_path.txt").c_str());
    printf("test get_thread_id():%d \n", get_thread_id());
    printf("test get_cur_proc_id():%d \n", get_cur_proc_id());
    printf("test get_ip_str():%s \n", get_ip_str(inet_addr("192.168.131.31")).c_str());
    printf("test get_ip_by_host():%d \n", get_ip_by_host("www.baidu.com"));
    printf("test get_intranet_ip():%s \n", get_intranet_ip().c_str());
    return 1;
}