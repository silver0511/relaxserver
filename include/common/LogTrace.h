/*
 * file_name: LogTrace.h
 * file_detail:write log file
 * created by silver0511
 */

#ifndef __RX_LOGTRACE_H__
#define __RX_LOGTRACE_H__

#include "common/platform.h"
#include "const/LogConst.h"
#include "common/Lock.h"
#include "common/MemCache.h"
#include "common/BaseQueue.h"
#include "common/BaseThread.h"
#include "common/System.h"

RELAX_NAMESPACE_BEGIN

    struct S_LOG_BUFFER
    {
    public:
        S_LOG_BUFFER()
        {
        }

        S_LOG_BUFFER(int type)
        {
            init(type);
        }

        inline void init(int type = DEF_DISPLAY_TYPE_THREAD)
        {
            zero_memory(m_log_buffer, sizeof(m_log_buffer));
            zero_memory(m_trans_buffer, sizeof(m_trans_buffer));
            m_cur_size = 0;
            m_type = type;
        }

        inline S_LOG_BUFFER &operator <<(void *value)
        {
                long l_value =(long)(value);
                snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "0x%lx", l_value);
                return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(char *value)
        {
            if(NULL == value)
                return *this;

            return operate_string((const char*)value);
        }
        inline S_LOG_BUFFER &operator <<(const char *value)
        {
            if(NULL == value)
                return *this;

            return operate_string(value);
        }
        inline S_LOG_BUFFER &operator <<(wchar_t *value)
        {
            if(NULL == value)
                return *this;

            return operate_wstring((const wchar_t*)value);
        }
        inline S_LOG_BUFFER &operator <<(const wchar_t *value)
        {
            if(NULL == value)
                return *this;

            return operate_wstring(value);
        }
        inline S_LOG_BUFFER &operator <<(bool value)
        {
            if(false == value)
                *this << "false";
            else
                *this << "true";

            return *this;
        }
        inline S_LOG_BUFFER &operator <<(byte value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%d",(int)value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(short value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%d", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(int value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%d", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(int64 value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%lld", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(ubyte value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%u", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(ushort value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%u", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(uint value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%u", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(uint64 value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%llu", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(long value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%ld", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(ulong value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%lu", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(float value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%f", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(double value)
        {
            snprintf(m_trans_buffer, DEF_MAX_TRANS_BUFFER-1, "%lf", value);
            return operate_string(m_trans_buffer);
        }
        inline S_LOG_BUFFER &operator <<(string & value)
        {
            return operate_string(value.c_str());
        }
        inline S_LOG_BUFFER &operator <<(const string & value)
        {
            return operate_string(value.c_str());
        }
        inline S_LOG_BUFFER &operator <<(wstring & value)
        {
            return operate_wstring(value.c_str());
        }
        inline S_LOG_BUFFER &operator <<(const wstring &value)
        {
            return operate_wstring(value.c_str());
        }

    private:
        inline S_LOG_BUFFER &operate_string(const char *value)
        {
            if(m_cur_size >= DEF_ONCE_LOG_BUFFER_SIZE)
                return *this;

            int l_size = (int)strlen(value);
            if(l_size <= 0 || l_size + m_cur_size > DEF_ONCE_LOG_BUFFER_SIZE)
                return *this;

            memcpy(m_log_buffer + m_cur_size, value, l_size);
            m_cur_size += l_size;

            return *this;
        }

        inline S_LOG_BUFFER &operate_wstring(const wchar_t *value)
        {
            if(m_cur_size >= DEF_ONCE_LOG_BUFFER_SIZE)
                return *this;

            int l_size = wcslen(value) * sizeof(wchar_t);
            if(l_size <= 0 || l_size + m_cur_size > DEF_ONCE_LOG_BUFFER_SIZE)
                return *this;
//            wcout << value << endl;
            int ret = wcstombs(m_log_buffer + m_cur_size, value, l_size);
            if(ret > 0)
                m_cur_size += ret;

            return *this;
        }
    private:
        int m_type;
        char m_trans_buffer[DEF_MAX_TRANS_BUFFER];
    public:
        int m_cur_size;
        char m_log_buffer[DEF_ONCE_LOG_BUFFER_SIZE];
    };

    class LogTrace : public BaseThread
    {
    public:
        LogTrace();
        virtual ~LogTrace();

        void init(int type, int level, const char *file_name);
        void close(){stop();}

        S_LOG_BUFFER *write_begin(int level, const char *func_name,
                                  const char *file_name, int line);
        void write_end(S_LOG_BUFFER *buffer);
        void create_new_log_file();

        inline int get_level(){return m_level;}
        inline void set_level(int level)
        {
            if(m_level == level)
                return;
            m_level = level;
        };

    private:
        const char *get_str_level(int level);
        void clear();
    public:
        //inherit basethread
        virtual void run();
        virtual void release();
        virtual void stop();
    private:
        bool            m_is_init;
        int             m_type;
        int             m_level;
        ulong           m_count;
        ulong           m_record_count;
        int             m_file_count;
        char            m_file_name[FILE_NAME_LENGTH + 1];
        ofstream        m_log_stream;

        CachePool_S<S_LOG_BUFFER>   m_cache_pool;
        Queue<S_LOG_BUFFER>       m_buffer_queue;
    };

RELAX_NAMESPACE_END

#endif //__RX_LOGTRACE_H__
