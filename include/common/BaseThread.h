/*
 * file_name: BaseThread.h
 * file_detail:thread class
 * created by silver0511
 */

#ifndef __RX_BASE_THREAD_H__
#define __RX_BASE_THREAD_H__

#include<stdlib.h>
#include <pthread.h>
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN
    class BaseThread
    {
    public:
        BaseThread();
        ~BaseThread();

        bool begin_thread(bool release_thread = false, void (*start_func)(void *) = NULL, void *param = NULL);
        void terminate()
        {
            if(0 != m_handle)
                pthread_cancel(m_handle);
        }

        bool is_run(){return m_run;}

    public:
        virtual void run();
        virtual void release();
        virtual void stop();

    private:
        static void *thread_proc(void *ptr);

    protected:
        bool m_run;

    private:
        pthread_t       m_handle;
        void            *m_user_data;
        void            (*m_thread_func)(void *);
        bool            m_release_thread;
    };

    class ThreadHelper
    {
    public:
        static bool begin_thread(void (*start_func)(void *), void *param);
    private:
    };

RELAX_NAMESPACE_END

#endif //__RX_BASE_THREAD_H__
