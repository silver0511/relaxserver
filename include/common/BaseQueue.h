/*
 * file_name: BaseQueue.h
 * file_detail:base link
 * created by silver0511
 */
#ifndef __RX_BASE_QUEUE_H__
#define __RX_BASE_QUEUE_H__

#include "common/platform.h"
#include "common/BaseFun.h"
#include "common/Lock.h"

RELAX_NAMESPACE_BEGIN

/*
 * max_cache_count: cache node size, default 0
 * thread_safe: need thread safe, add mutex lock, default true
 */
template <class T>
class Queue
{
public:
    struct S_QUEUE_NODE
    {
        byte m_cached;
        T *m_data;
        S_QUEUE_NODE *m_next;
        S_QUEUE_NODE()
        {
            m_cached = 0;
            m_data = NULL;
            m_next = NULL;
        }
    };

    inline Queue()
    {
        m_inited = false;
        m_safe = true;
        m_count = 0;
        m_max_cache_count = 0;
        m_head = NULL;
        m_tail = NULL;
        m_cache_node = NULL;
        m_safe = true;
    }

    inline ~Queue()
    {
        clear();
    }

    virtual void init(uint max_cache_count = RX_DEFAULT_CACHE_SIZE, bool thread_safe = true)
    {
        if(m_inited)
        {
            printf("\n Queue repeat inited\n");
            throw;
        }

        m_count = 0;
        m_max_cache_count = max_cache_count;
        m_safe = thread_safe;
        if(m_max_cache_count > 0)
        {
            for (int i = 0; i < m_max_cache_count; ++i)
            {
                S_QUEUE_NODE *node = new S_QUEUE_NODE;
                node->m_next = m_cache_node;
                node->m_cached = 1;
                m_cache_node = node;
            }
        }
        m_inited = true;
    }

    inline void clear()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            clear_impl();
        }
        else
        {
            clear_impl();
        }
    }

    inline bool push_back(T *value)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return push_back_impl(value);
        }

        return push_back_impl(value);
    }

    inline T *pop_front()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return pop_front_impl();
        }

        return pop_front_impl();
    }

    inline T *front()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return front_impl();
        }

        return front_impl();
    }

    inline int size()
    {
        uint l_count = 0;
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            l_count = m_count;
        }
        else
        {
            l_count = m_count;
        }

        return l_count;
    }

    //if is no cache
    inline bool is_full()
    {
        bool flag;
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            flag = (m_count >= m_max_cache_count);
        }
        else
        {
            flag = (m_count >= m_max_cache_count);
        }

        return flag;
    }

private:
    inline S_QUEUE_NODE* new_node()
    {
        S_QUEUE_NODE *node = m_cache_node;
        if(NULL == node)
        {
            //no cache
            node = new S_QUEUE_NODE;
        }
        else
        {
            m_cache_node = m_cache_node->m_next;
        }

        m_count++;
        return node;
    }

    inline void free_node(S_QUEUE_NODE *node)
    {
        if(node->m_cached != 1)
        {
            SAFE_DELETE(node);
        }
        else
        {
            node->m_next = m_cache_node;
            m_cache_node = node;
        }

        m_count--;
    }

    inline void clear_impl()
    {
        S_QUEUE_NODE *node = NULL;
        while(m_head != NULL)
        {
            node = m_head->m_next;
            SAFE_DELETE(m_head);
            m_head = node;
        }

        while(m_cache_node != NULL)
        {
            node = m_cache_node->m_next;
            SAFE_DELETE(m_cache_node);
            m_cache_node = node;
        }

        m_inited = false;

        m_safe = true;

        m_count = 0;
        m_max_cache_count = 0;

        m_head = NULL;
        m_tail = NULL;
        m_cache_node = NULL;
    }

    inline bool push_back_impl(T *value)
    {
        if(NULL == value)
        {
            return false;
        }

        S_QUEUE_NODE *node = new_node();
        node->m_next = NULL;
        node->m_data = value;
        if(m_head == NULL)
        {
            m_head = node;
            m_tail = node;
        }
        else
        {
            m_tail->m_next = node;
            m_tail = node;
        }
        return true;
    }

    inline T *pop_front_impl()
    {
        if(NULL == m_head)
        {
            return NULL;
        }

        T *obj = m_head->m_data;
        S_QUEUE_NODE *node = NULL;
        node = m_head->m_next;
        free_node(m_head);
        m_head = node;
        if(m_head == NULL)
        {
            m_tail = NULL;
        }

        return obj;
    }

    inline T *front_impl()
    {
        if(m_head == NULL)
            return NULL;
        return m_head->m_data;
    }
private:
    bool            m_inited;

    bool            m_safe;
    Lock            m_lock;

    uint            m_count;
    uint            m_max_cache_count;

    S_QUEUE_NODE    *m_head;
    S_QUEUE_NODE    *m_tail;
    S_QUEUE_NODE    *m_cache_node;
};

/*
* max_cache_count: cache node size, default 0
* thread_safe: need thread safe, add mutex lock, default true
*/
template <class T>
class DoubleQueue
{
public:
    struct S_DQUEUE_NODE
    {
        S_DQUEUE_NODE *m_next;
        S_DQUEUE_NODE *m_prev;
        T             *m_data;
        byte           m_cached;
        S_DQUEUE_NODE()
        {
            m_next = NULL;
            m_prev = NULL;
            m_data = NULL;
            m_cached = 0;
        }
    };

    inline DoubleQueue()
    {
        m_inited = false;
        m_safe = true;
        m_count = 0;
        m_max_cache_count = 0;
        m_head = NULL;
        m_tail = NULL;
        m_cache_node = NULL;
    }

    inline ~DoubleQueue()
    {
        clear();
    }

public:
    inline void init(uint max_cache_count = RX_DEFAULT_CACHE_SIZE, bool thread_safe = true)
    {
        if(m_inited)
        {
            printf("\n DoubleQueue repeat inited\n");
            throw;
        }

        m_count = 0;
        m_max_cache_count = max_cache_count;
        m_safe = thread_safe;
        if(m_max_cache_count > 0)
        {
            for(int i = 0; i < (int)max_cache_count; ++i)
            {
                S_DQUEUE_NODE *node = new S_DQUEUE_NODE;
                node->m_next = m_cache_node;
                node->m_prev = NULL;
                node->m_cached = 1;
                m_cache_node = node;
            }
        }

        m_inited = true;
    }

    inline void clear()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            clear_impl();
        }
        else
        {
            clear_impl();
        }
    }

    inline T *back()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return back_impl();
        }

        return back_impl();
    }
    inline T *pop_back()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return pop_back_impl();
        }

        return pop_back_impl();
    }
    inline bool push_back(T *value)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return push_back_impl(value);
        }

        return push_back_impl(value);
    }

    inline T *front()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return front_impl();
        }

        return front_impl();
    }
    inline T *pop_front()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return pop_front_impl();
        }

        return pop_front_impl();
    }
    inline bool push_front(T *&data)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return push_front_impl(data);
        }

        return push_front_impl(data);
    }
public:
    inline int size()
    {
        uint l_count = 0;
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            l_count = m_count;
        }
        else
        {
            l_count = m_count;
        }

        return l_count;
    }

    //if is no cache
    inline bool is_full()
    {
        bool flag;
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            flag = (m_count >= m_max_cache_count);
        }
        else
        {
            flag = (m_count >= m_max_cache_count);
        }

        return flag;
    }

private:
    inline T *front_impl()
    {
        if(NULL == m_head)
            return NULL;

        return m_head->m_data;
    }
    inline T *pop_front_impl()
    {
        if(NULL == m_head)
            return NULL;

        S_DQUEUE_NODE *l_node = m_head;
        T *l_data = l_node->m_data;
        if(m_head != m_tail)
        {
            m_head = l_node->m_next;
            m_head->m_prev = NULL;
        }
        else
        {
            m_head = NULL;
            m_tail = NULL;
        }

        free_node(l_node);

        return l_data;
    }
    inline bool push_front_impl(T *&data)
    {
        if(NULL == data)
        {
            return false;
        }

        S_DQUEUE_NODE *l_node = new_node();

        l_node->m_data = data;
        l_node->m_next = m_head;
        l_node->m_prev = NULL;
        if(NULL == m_head)
            m_tail = l_node;
        else
            m_head->m_prev = l_node;

        m_head = l_node;

        return true;
    }

    inline T *back_impl()
    {
        if(NULL == m_tail)
            return NULL;

        return m_tail->m_data;
    }
    inline T *pop_back_impl()
    {
        if(NULL == m_tail)
            return NULL;

        S_DQUEUE_NODE *l_node = m_tail;
        T *l_data = l_node->m_data;

        if(m_tail != m_head)
        {
            m_tail = l_node->m_prev;
            m_tail->m_next = NULL;
        }
        else
        {
            m_tail = NULL;
            m_head = NULL;
        }

        free_node(l_node);

        return l_data;
    }
    inline bool push_back_impl(T *&data)
    {
        if(NULL == data)
        {
            return false;
        }

        S_DQUEUE_NODE *l_node = new_node();

        l_node->m_data = data;
        l_node->m_prev = m_tail;
        l_node->m_next = NULL;

        if(NULL == m_tail)
            m_head = l_node;
        else
            m_tail->m_next = l_node;

        m_tail = l_node;

        return true;
    }

private:
    inline void clear_impl()
    {
        S_DQUEUE_NODE *l_node;
        while(NULL != m_head)
        {
            l_node = m_head;
            m_head = m_head->m_next;
            free(l_node);
        }

        m_tail = NULL;
        m_count = 0;
    }

    inline S_DQUEUE_NODE *new_node()
    {
        S_DQUEUE_NODE *node = m_cache_node;
        if(NULL == node)
        {
            //no cache
            node = new S_DQUEUE_NODE;
        }
        else
        {
            m_cache_node = m_cache_node->m_next;
        }

        m_count++;
        return node;
    }
    inline void free_node(S_DQUEUE_NODE *node)
    {
        if(node->m_cached != 1)
        {
            SAFE_DELETE(node);
        }
        else
        {
            node->m_next = m_cache_node;
            m_cache_node = node;
        }
        m_count--;
    }
protected:
    bool                m_inited;

    bool                m_safe;
    Lock                m_lock;

    uint                m_count;
    uint                m_max_cache_count;

    S_DQUEUE_NODE       *m_head;
    S_DQUEUE_NODE       *m_tail;
    S_DQUEUE_NODE       *m_cache_node;
};

RELAX_NAMESPACE_END

#endif //__RX_BASE_QUEUE_H__
