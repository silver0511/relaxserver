/*
 * file_name: test_log_trace.h
 * file_detail:test log trace interface
 * created by silver0511
 */

#include <pthread.h>
#include "common/LogMacro.h"
USING_RELAX_NAMESPACE

volatile bool g_is_run;
void *thread_func(void* p)
{
    int64 start_time = System::get_ms_time();
    while(true)
    {
        int64 end_time = System::get_ms_time();
        if((end_time - start_time) > 1000 * 5)
        {
            LOG_SET_LEVEL(LOG_CRIT)
            LOG_TRACE(LOG_INFO, "i'm log info")
            LOG_TRACE(LOG_EMERG, "i'm log emerg")
            g_is_run = false;
            break;
        }
    }

    return NULL;
}


int main(int argc, char* argv[])
{
    //端口参数
    if(argc < 2)
    {
        printf("argv is invalid missing port");
        return 1;
    }

    LOG_INIT(atoi(argv[1]), LOG_DEBUG_2, "test_log_trace")
    int int_value = -65537;
    uint uint_value = 65537;
    void *void_value = &int_value;
    char *char_value = (char *)"我是 char *";
    const char * const_char_value = "i'm const char *";

    wchar_t *wchar_t_value = (wchar_t *)L"我是 wchar_t* 类型";
    const wchar_t *const_wchar_t_value = L"我是 const wchar_t* 类型";

    bool bool_value = true;
    byte byte_value = -29;
    ubyte ubyte_value = 29;
    short short_value = -259;
    ushort ushort_value = 259;
    int64 int64_value = -548392012;
    uint64 uint64_value = 548392012;
    long long_value = -12345677;
    ulong ulong_value = 12345677;
    float float_value = -12345677.2321;
    double double_value = -3424243423123.4232;
    string string_value = "i'm string value";
    const string const_string_value = "i'm const string value";
    wstring wstring_value = L"我是 wstring value 类型";
    const wstring const_wstring_value = L"我是 const wstring value 类型";

    LOG_TRACE(LOG_DEBUG_2, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_DEBUG_1, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_DEBUG, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_INFO, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_NOTICE, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_ERR, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_CRIT, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_ALERT, "value is:" << int_value << "===" << uint_value << "==="
                                       << void_value << "===" << char_value << "==="
                                       << const_char_value << "===" << wchar_t_value << "==="
                                       << const_wchar_t_value << "===" << bool_value << "==="
                                       << byte_value << "===" << ubyte_value << "==="
                                       << short_value << "===" << ushort_value << "==="
                                       << int64_value << "===" << uint64_value << "==="
                                       << long_value << "===" << ulong_value << "==="
                                       << float_value << "===" << double_value)

    LOG_TRACE(LOG_EMERG, "value is:" << int_value << "===" << uint_value << "==="
                                     << void_value << "===" << char_value << "==="
                                     << const_char_value << "===" << wchar_t_value << "==="
                                     << const_wchar_t_value << "===" << bool_value << "==="
                                     << byte_value << "===" << ubyte_value << "==="
                                     << short_value << "===" << ushort_value << "==="
                                     << int64_value << "===" << uint64_value << "==="
                                     << long_value << "===" << ulong_value << "==="
                                     << float_value << "===" << double_value)

    g_is_run = true;
    pthread_t lthread;
    pthread_create(&lthread, NULL, thread_func, NULL);
    while(g_is_run)
    {
    }
    printf("test log trace finished ======\n");
    getchar();
    LOG_CLOSE()
    return 1;
}
