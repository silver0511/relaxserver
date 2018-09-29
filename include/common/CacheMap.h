/*
 * file_name: CacheMap.h
 * file_detail:cached map
 * created by silver0511
 */
#ifndef __RX_CACHEMAP_H__
#define __RX_CACHEMAP_H__

#include <map>
#include "common/platform.h"
#include "common/MemCache.h"
#include "common/Lock.h"
#include "common/BaseQueue.h"

RELAX_NAMESPACE_BEGIN

enum E_MAP_TYPE
{
    TREE_MAP,
    HASH_MAP
};

enum E_CACHE_TYPE
{
    ACTIVE_CACHE,
    PASSITIVE_CACHE
};

template<typename T_ID, class T_VALUE>
class CacheMap
{
public:
    //return value: [need break]
    typedef function<bool(T_VALUE *)> IProcessInterface;
public:
    typedef class rx_hash_map<T_ID, T_VALUE*> RefHashMap;
    typedef typename rx_hash_map<T_ID, T_VALUE*>::iterator RefHashMapIter;

    typedef class std::map<T_ID, T_VALUE*> RefTreeMap;
    typedef typename std::map<T_ID, T_VALUE*>::iterator RefTreeMapIter;

    CacheMap()
    {
    }

    virtual ~CacheMap()
    {
        clear();
    }

    virtual void init(uint max_size = RX_DEFAULT_CACHE_SIZE, E_MAP_TYPE map_type = HASH_MAP,
                  E_CACHE_TYPE cache_type = ACTIVE_CACHE, bool safe_thread = true)
    {
        LOCK_HELPER(m_lock);
        m_hash_map.clear();
        m_tree_map.clear();
        m_map_type = map_type;
        m_cache_type = cache_type;
        m_safe = safe_thread;
        if(m_cache_type == ACTIVE_CACHE)
        {
            m_cache_pool.init(max_size);
        }
        else
        {
            m_cache_queue.init(max_size, false);
        }
        assert(m_map_type == HASH_MAP || m_map_type == TREE_MAP);
        assert(m_cache_type == ACTIVE_CACHE || m_cache_type == PASSITIVE_CACHE);
    }

    virtual void clear()
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

    virtual void reset()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            reset_impl();
        }
        else
        {
            reset_impl();
        }
    }

    T_VALUE *malloc_node()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return malloc_node_impl();
        }

        return malloc_node_impl();
    }

    inline bool add(const T_ID &ref_id, T_VALUE *ref_value)
    {
        assert(NULL != ref_value);
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return add_impl(ref_id, ref_value);
        }
        else
        {
            return add_impl(ref_id, ref_value);
        }
    }

    inline bool remove(const T_ID &ref_id)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return remove_impl(ref_id);
        }
        else
        {
            return remove_impl(ref_id);
        }
    }

    inline T_VALUE *get(const T_ID &ref_id)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return get_impl(ref_id);
        }
        else
        {
            return get_impl(ref_id);
        }
    }

    inline uint size()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return size_impl();
        }
        else
        {
            return size_impl();
        }
    }

    inline void process_value(IProcessInterface process_interface)
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            process_value_impl(process_interface);
        }
        else
        {
            process_value_impl(process_interface);
        }
    }

    inline vector<T_VALUE *> values()
    {
        if(m_safe)
        {
            LOCK_HELPER(m_lock);
            return values_impl();
        }
        else
        {
            return values_impl();
        }
    }

private:
    T_VALUE* malloc_node_impl()
    {
        T_VALUE *value = NULL;
        if(m_cache_type == ACTIVE_CACHE)
        {
            value = m_cache_pool.malloc_cache();
        }
        else
        {
            value = m_cache_queue.pop_front();
        }
        return value;
    }

    void free_node_impl(T_VALUE *value)
    {
        if(NULL == value)
            return;

        if(m_cache_type == ACTIVE_CACHE)
        {
            m_cache_pool.free_cache(value);
        }
        else
        {
            if(!m_cache_queue.is_full())
            {
                value->~T_VALUE();
                m_cache_queue.push_back(value);
            }
            else
            {
                SAFE_DELETE(value);
            }
        }
    }

    void clear_impl()
    {
        m_hash_map.clear();
        m_tree_map.clear();
        m_cache_pool.clear();
        T_VALUE *l_value = m_cache_queue.pop_front();
        while (NULL != l_value)
        {
            SAFE_DELETE(l_value);
            l_value = m_cache_queue.pop_front();
        }
        m_cache_queue.clear();
    }

    void reset_impl()
    {
        if(m_map_type == HASH_MAP)
        {
            RefHashMapIter iter = m_hash_map.begin();
            while(iter != m_hash_map.end())
            {
                free_node_impl(iter->second);
                ++iter;
            }
        }
        else
        {
            RefTreeMapIter iter = m_tree_map.begin();
            while(iter != m_tree_map.end())
            {
                free_node_impl(iter->second);
                ++iter;
            }
        }

        m_hash_map.clear();
        m_tree_map.clear();
    }

    inline bool add_impl(const T_ID &ref_id, T_VALUE *ref_value)
    {
        if(m_map_type == HASH_MAP)
        {
            RefHashMapIter iter = m_hash_map.find(ref_id);
            if(iter != m_hash_map.end())
                return false;

            m_hash_map.insert(make_pair(ref_id, ref_value));
        }
        else
        {
            RefTreeMapIter iter = m_tree_map.find(ref_id);
            if(iter != m_tree_map.end())
                return false;

            m_tree_map.insert(make_pair(ref_id, ref_value));
        }

        return true;
    }

    inline bool remove_impl(const T_ID &ref_id)
{
        T_VALUE *value = NULL;
        if(m_map_type == HASH_MAP)
        {
            RefHashMapIter iter = m_hash_map.find(ref_id);
            if(iter == m_hash_map.end())
                return false;

            value = iter->second;
            assert(NULL != value);
            m_hash_map.erase(iter);
        }
        else
        {
            RefTreeMapIter iter = m_tree_map.find(ref_id);
            if(iter == m_tree_map.end())
                return false;

            value = iter->second;
            assert(NULL != value);
            m_tree_map.erase(iter);
        }

        free_node_impl(value);
        return true;
    }

    inline T_VALUE *get_impl(const T_ID &ref_id)
    {
        if(m_map_type == HASH_MAP)
        {
            RefHashMapIter iter = m_hash_map.find(ref_id);
            if(iter == m_hash_map.end())
                return NULL;

            return iter->second;
        }
        else
        {
            RefTreeMapIter iter = m_tree_map.find(ref_id);
            if(iter == m_tree_map.end())
                return NULL;

            return iter->second;
        }
    }

    inline uint size_impl()
    {
        int size = 0;
        if(m_map_type == HASH_MAP)
        {
            size = static_cast<uint>(m_hash_map.size());
        }
        else
        {
            size = static_cast<uint>(m_tree_map.size());
        }
        return size;
    }

    inline void process_value_impl(IProcessInterface process_interface)
    {
        if(m_map_type == HASH_MAP)
        {
            for (RefHashMapIter iter = m_hash_map.begin(); iter != m_hash_map.end(); ++iter)
            {
                if(process_interface(iter->second))
                {
                    break;
                }
            }
        }
        else
        {
            for (RefTreeMapIter iter = m_tree_map.begin(); iter != m_tree_map.end(); ++iter)
            {
                if(process_interface(iter->second))
                {
                    break;
                }
            }
        }
    }

    inline vector<T_VALUE *> values_impl()
    {
        vector<T_VALUE *> l_vec;
        if(m_map_type == HASH_MAP)
        {
            l_vec.reserve(m_hash_map.size() + 1);
            for (RefHashMapIter iter = m_hash_map.begin(); iter != m_hash_map.end(); ++iter)
            {
                l_vec.push_back(iter->second);
            }
        }
        else
        {
            l_vec.reserve(m_tree_map.size() + 1);
            for (RefTreeMapIter iter = m_tree_map.begin(); iter != m_tree_map.end(); ++iter)
            {
                l_vec.push_back(iter->second);
            }
        }

        return l_vec;
    }
protected:
    bool                    m_safe;
    Lock                    m_lock;
    E_MAP_TYPE              m_map_type;
    E_CACHE_TYPE            m_cache_type;
    RefHashMap              m_hash_map;
    RefTreeMap              m_tree_map;
private:
    CachePool<T_VALUE>      m_cache_pool;           //not thread safe
    Queue<T_VALUE>          m_cache_queue;          //not thread safe
};

RELAX_NAMESPACE_END

#endif //__RX_CACHEMAP_H__
