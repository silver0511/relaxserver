/*
 * file_name: LogTrace.cpp
 * file_detail:write log file
 * created by silver0511
 */

#include "common/LogTrace.h"

USING_RELAX_NAMESPACE

LogTrace::LogTrace() : m_cache_pool(DEF_LOG_TRACE_COUNT)
{
    clear();
}

LogTrace::~LogTrace()
{
    clear();
}

void LogTrace::clear()
{
    m_is_init = false;
    m_type = 0;
    m_level = 0;
    m_count = 0;
    m_record_count = 0;
    m_file_count = 0;
    zero_memory(m_file_name, sizeof(m_file_name));
}

void LogTrace::init(int type, int level, const char *file_name)
{
    if(m_is_init)
        return;

    m_is_init = true;

    m_buffer_queue.init(DEF_LOG_TRACE_COUNT);

    m_type = type;
    m_level = level;

    file_name = file_name ? file_name : "undefined_file";
    snprintf(m_file_name, FILE_NAME_LENGTH, "%s%s_", get_app_path().c_str(),
    "log/", file_name);

    strncpy(m_file_name, file_name, FILE_NAME_LENGTH);

    if(m_type != DEF_DISPLAY_TYPE_CONSOLE)
    {
        create_new_log_file();
    }
    else
    {
        cout<<endl;
    }

    begin_thread();
}

S_LOG_BUFFER *LogTrace::write_begin(int level, const char *func_name, const char *file_name, int line)
{
    if(m_buffer_queue.is_full())
        return NULL;

    S_LOG_BUFFER *l_buffer = m_cache_pool.malloc_cache();
    if(!l_buffer)
        return NULL;

    l_buffer->init();

    m_count++;

    char l_data[512 + 1] = {0};
    struct tm s_local_tm = {0};
    System::get_local_time(s_local_tm);
    int milli_time = System::get_ms_count();
    file_name = file_name ? file_name : "undefined_file";
    func_name = func_name ? func_name : "undefined_func";

    snprintf(l_data, 512, "%d %04d%02d%02d %02d:%02d:%02d-%03d %s:%03d",
             get_thread_id(),
             s_local_tm.tm_year + 1900, s_local_tm.tm_mon + 1, s_local_tm.tm_mday,
             s_local_tm.tm_hour, s_local_tm.tm_min, s_local_tm.tm_sec, milli_time,
             file_name, line);

    (*l_buffer) << m_count << " " << l_data << " " << get_str_level(level)
                << " " << func_name << " ";
    return l_buffer;
}

void LogTrace::write_end(S_LOG_BUFFER *buffer)
{
    if(!buffer)
        return;

    (*buffer) << "\n";
    if(!m_buffer_queue.push_back(buffer))
    {
        printf("\n too many log need to write\n");
        m_cache_pool.free_cache(buffer);
    }
}

void LogTrace::create_new_log_file()
{
    char l_file_name[FILE_NAME_LENGTH + 1] = {0};
    struct tm s_local_tm = {0};
    System::get_local_time(s_local_tm);

    snprintf(l_file_name, FILE_NAME_LENGTH, "%s_%4d%02d%02d_%02d:%02d:%02d_%d.log",
             m_file_name, (1900 + s_local_tm.tm_year),
             (1 + s_local_tm.tm_mon), s_local_tm.tm_mday,
             s_local_tm.tm_hour, s_local_tm.tm_min,s_local_tm.tm_sec,
             m_file_count++);
    if(m_log_stream.is_open())
        m_log_stream.close();

    m_log_stream.open(l_file_name);
    m_log_stream << endl;

    printf("create new log file:%s \n\r", l_file_name);
}

const char *LogTrace::get_str_level(int level)
{
    switch (level)
    {
        case LOG_EMERG:
            return "[EMERG]";
        case LOG_ALERT:
            return "[ALERT]";
        case LOG_CRIT:
            return "[CRIT]";
        case LOG_ERR:
            return "[ERROR]";
        case LOG_WARNING:
            return "[WARNING]";
        case LOG_NOTICE:
            return "[NOTICE]";
        case LOG_INFO:
            return "[INFO]";
        case LOG_DEBUG:
            return "[DEBUG]";
        case LOG_DEBUG_1:
            return "[DEBUG_1]";
        case LOG_DEBUG_2:
            return "[DEBUG_2]";
        default:
            return "[UNKNOWN]";
    }
}

void LogTrace::run()
{
    S_LOG_BUFFER *l_buffer = NULL;
    while(m_run)
    {
        l_buffer = m_buffer_queue.pop_front();
        if(NULL == l_buffer)
        {
            System::sleep(10);
            continue;
        }

        if(m_type != DEF_DISPLAY_TYPE_CONSOLE)
        {
            m_log_stream.write(l_buffer->m_log_buffer, l_buffer->m_cur_size);
            m_log_stream.flush();
        }
        else
        {
            cout << l_buffer->m_log_buffer;
            cout.flush();
        }


        m_record_count++;
        m_cache_pool.free_cache(l_buffer);
        if(m_type != DEF_DISPLAY_TYPE_CONSOLE)
        {
            if(m_record_count >= DEF_LOG_MAX_LINE)
            {
                m_record_count = 0;
                create_new_log_file();
            }
        }
    }
}

void LogTrace::release()
{
    BaseThread::release();
}

void LogTrace::stop()
{
    System::sleep(1000);
    BaseThread::stop();
    System::sleep(1000);
}
