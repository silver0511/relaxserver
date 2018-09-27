/*
 * file_name: SpinLock.h
 * file_detail:
 * created by silver0511
 */

#ifndef __RX_SPINLOCK_H__
#define __RX_SPINLOCK_H__

#include <atomic>
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

class SpinLock
{
public:
    SpinLock() : m_lock(false)
    {}

    void lock()
    {
        bool expect = false;
        while (!m_lock.compare_exchange_weak(expect, true))
        {
            expect = false;
        }
    }

    void unlock()
    {
        m_lock.store(false);
    }

private:
    std::atomic<bool> m_lock;
};

RELAX_NAMESPACE_END

#endif //__RX_SPINLOCK_H__
