/*
 * file_name: Lock.h
 * file_detail:lock class
 * created by silver0511
 */

#ifndef __RX_LOCK_H__
#define __RX_LOCK_H__
#include <pthread.h>
#include <unistd.h>
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

    class Lock
    {
    public:
        inline Lock()
        {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            int result = pthread_mutex_init(&m_mutex, &attr);
            if(0 != result)
            {
                printf(" Lock pthread_mutex_init error %d \n\r",result);
            }
        }

        inline ~Lock()
        {
            pthread_mutex_destroy(&m_mutex);
        }

        inline void lock()
        {
            pthread_mutex_lock(&m_mutex);
        }

        inline void unlock()
        {
            pthread_mutex_unlock(&m_mutex);
        }
    private:
        pthread_mutex_t m_mutex;
    };

    class LockHelper
    {
    public:
        inline LockHelper(Lock &lock):m_lock(lock)
        {
            m_lock.lock();
        }

        inline ~LockHelper()
        {
            m_lock.unlock();
        }

        inline LockHelper &operator=(const LockHelper &rhs)
        {
            m_lock = rhs.m_lock;
        }
    private:
        Lock &m_lock;
    };


#define LOCK_HELPER(T)\
LockHelper l_lock_helper(T)

RELAX_NAMESPACE_END

#endif //__RX_LOCK_H__