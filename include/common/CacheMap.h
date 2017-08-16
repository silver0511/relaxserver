//
// Created by shiyunjie on 2017/6/26.
//

#ifndef __RX__CACHEMAP_H__
#define __RX__CACHEMAP_H__
#include "common/platform.h"
#include "common/MemCache.h"
#include "common/Lock.h"

RELAX_NAMESPACE_BEGIN

    template<typename T_ID, class T_VALUE>
    class CacheMap
    {
    public:
        typedef class rx_hash_map<T_ID, T_VALUE*> RefCacheMap;
        typedef typename rx_hash_map<T_ID, T_VALUE*>::iterator RefCacheIter;

        CacheMap()
        {
        }

        CacheMap(uint max_size)
        {
            init(max_size);
        }

        virtual ~CacheMap()
        {
            clear();
        }

        virtual void init(uint max_size = RX_DEFAULT_CACHE_SIZE)
        {
            LOCK_HELPER(m_lock);
            m_cache_pool.init(max_size);
            m_map.clear();
        }

        virtual void clear()
        {
            LOCK_HELPER(m_lock);
            m_map.clear();
            m_cache_pool.clear();
        }

        T_VALUE *malloc_node()
        {
            LOCK_HELPER(m_lock);
            T_VALUE *value = m_cache_pool.malloc_cache();
            return value;
        }

        inline bool add(const T_ID ref_id, T_VALUE *ref_value)
        {
            assert(NULL != ref_value);
            LOCK_HELPER(m_lock);
            RefCacheIter iter = m_map.find(ref_id);
            if(iter != m_map.end())
                return false;

            m_map.insert(make_pair(ref_id, ref_value));
        }

        inline bool remove(const T_ID &ref_id)
        {
            LOCK_HELPER(m_lock);
            RefCacheIter iter = m_map.find(ref_id);
            if(iter == m_map.end())
                return false;

            T_VALUE *value = iter->second;
            m_map.erase(value);
            assert(NULL != value);

            m_cache_pool.free_cache(value);

            return true;
        }

        inline T_VALUE *get(const T_ID &ref_id)
        {
            LOCK_HELPER(m_lock);
            RefCacheIter iter = m_map.find(ref_id);
            if(iter == m_map.end())
                return NULL;

            return iter->second;
        }

        inline uint size()
        {
            return static_cast<uint>(m_map.size());
        }

    protected:
        Lock                    m_lock;
        RefCacheMap             m_map;
    private:
        CachePool<T_VALUE>      m_cache_pool;           //not thread safe
    };

RELAX_NAMESPACE_END

#endif //__RX__CACHEMAP_H__
