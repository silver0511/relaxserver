/*
 * file_name: LogMacro.h
 * file_detail:macro definitions, provides for external calls
 * created by silver0511
 */
#ifndef __RX_LOGMACRO_H__
#define __RX_LOGMACRO_H__

#include "common/LogTrace.h"

#ifdef TRACE_LOG
extern RELAX_NAMESPACE::LogTrace g_log_trace;
#define LOG_INIT(a_type, a_level, a_app_name) \
    g_log_trace.init(a_type, a_level, a_app_name);

#define LOG_TRACE(a_level, a_value) \
    if(g_log_trace.get_level() >= a_level)\
    {\
        RELAX_NAMESPACE::S_LOG_BUFFER *l_buffer = g_log_trace.write_begin(a_level, __FUNCTION__, __FILE__, __LINE__);\
        if(NULL != l_buffer)\
        {\
            (*l_buffer) << a_value;\
            g_log_trace.write_end(l_buffer);\
        }\
    }

#define LOG_SET_LEVEL(a_level) g_log_trace.set_level(a_level);

#define LOG_CLOSE() g_log_trace.close();

#else
#define LOG_INIT(a_type, a_level, a_app_name)
#define LOG_TRACE(a_level, a_value)
#define LOG_SET_LEVEL(a_level)
#define LOG_CLOSE()
#endif


#endif //__RX_LOGMACRO_H__
