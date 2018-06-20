/*
 * file_name: BaseThread.cpp
 * file_detail:thread class
 * created by silver0511
 */

#include "common/BaseThread.h"
USING_RELAX_NAMESPACE

BaseThread::BaseThread()
{
    m_handle = 0;
    m_thread_func = NULL;
    m_user_data = NULL;
}

BaseThread::~BaseThread()
{
    m_handle = 0;
    m_thread_func = NULL;
    m_user_data = NULL;
}

bool BaseThread::begin_thread(bool release_thread, void (*start_func)(void *), void *param)
{
    int result = 0;
    m_thread_func = start_func;
    m_user_data = param;
    m_release_thread = release_thread;
    result = pthread_create(&m_handle, NULL, thread_proc, this);
    if(0 != result)
    {
        printf("\n<< Create Thread >> Create Thread Fail .Error %d,last error %d :%s\n" ,
               result, errno, strerror(result));
        return false;
    }

    printf("\n<< Create Thread >> Create Thread OK \n");
    return true;
}

void BaseThread::run()
{
    assert(m_thread_func != NULL);
    m_thread_func(m_user_data);
}

void BaseThread::release()
{
    m_handle = 0;
    m_thread_func = NULL;
    m_user_data = NULL;
}

void BaseThread::stop()
{
    m_run = false;
}

void* BaseThread::thread_proc(void *ptr)
{
    printf("\n BaseThread::thread_proc \n");
    BaseThread *p_this = (BaseThread *)ptr;
    if(NULL == p_this)
        return NULL;

    p_this->m_run = true;
    p_this->run();
    p_this->m_run = false;
    p_this->release();

    if(p_this->m_release_thread)
    {
        SAFE_DELETE(p_this)
    }

    return NULL;
}

bool ThreadHelper::begin_thread(void (*start_func)(void *), void *param)
{
    BaseThread *base_thread = new BaseThread();
    base_thread->begin_thread(true, start_func, param);
}