/*
 * file_name: MemCache.h
 * file_detail:memory cache pool
 * created by silver0511
 */

#ifndef __RX_MEMCACHE_H__
#define __RX_MEMCACHE_H__

#include "common/platform.h"
#include "common/BaseFun.h"
#include "common/Lock.h"
using namespace std;

RELAX_NAMESPACE_BEGIN

    template<typename T>
    class CachePool
    {
    public:
        CachePool()
        {
            m_max_count = 0;
            m_count = 0;
            m_head_index = 0;
            m_data_list = NULL;
        }

        CachePool(int max_count)
        {
            init(max_count);
        }

        ~CachePool()
        {
            clear();
        }

        inline void init(uint max_count = RX_DEFAULT_CACHE_SIZE)
        {
            if(NULL != m_data_list)
            {
                printf("\n init CachePool is not null exsists memory leak.\n");
            }

            m_max_count = max_count;
            m_count = 0;
            m_head_index = 0;
            m_data_list = new T*[m_max_count];
            if(NULL == m_data_list)
                throw;

            zero_memory(m_data_list, m_max_count* sizeof(T*));
            for(int index = 0; index < m_max_count; index++)
            {
                T *data = malloc_buffer();
                push_back(data);
            }
        }

        void clear()
        {
            if(NULL == m_data_list)
            {
                return;
            }

            for (int index = 0; index < m_count; ++index)
            {
                if(NULL == m_data_list[m_head_index])
                    continue;

                this->free_buffer(m_data_list[m_head_index]);
                m_data_list[m_head_index] = NULL;
                m_head_index = inc_index(m_head_index, 1, m_max_count);
            }

            SAFE_DELETE_ARRAY(m_data_list);
            m_head_index = 0;
            m_count = 0;
            m_max_count = 0;
        }

        inline T *malloc_cache()
        {
            T *data = this->pop_front();
            if(NULL == data)
            {
                data = malloc_buffer();
            }

            if(inc_buffer(data) != 1)
            {
                assert(false && "CachePool malloc_cache one buffer more than one times");
            }

            return data;
        }

        inline bool free_cache(T *value)
        {
            if(NULL == value)
            {
                return false;
            }

            if(dec_buffer(value) != 0)
            {
                assert(false && "CachePool free_cache one buffer more than one times");
                return false;
            }

            if(!push_back(value))
            {
                //printf("\ncache pool is full so free\n");
                free_buffer(value);
            }
        }
        inline int size(){return m_count;}
        inline int max_size(){return m_max_count;}
        inline int remain_count(){return (m_max_count - m_count);}
    private:
        inline byte inc_buffer(T *value)
        {
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer -  1;
            return ++(*buffer);
        }
        inline byte dec_buffer(T *value)
        {
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer -  1;
            return --(*buffer);
        }
        inline T *malloc_buffer()
        {
            uint l_size = sizeof(byte) + sizeof(T);
            char* l_buffer = new char[l_size];
            l_buffer[0] = 0;
            T *data = reinterpret_cast<T *>(l_buffer + 1);
            new( data ) T;
            return data;
        }
        inline void free_buffer(T *value)
        {
            value->~T();
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer - 1;
            SAFE_DELETE_ARRAY(buffer);
        }
        inline T *pop_front()
        {
            if(m_count < 0)
            {
                return NULL;
            }

            T *value = m_data_list[m_head_index];
            m_data_list[m_head_index] = NULL;
            m_count--;
            m_head_index = inc_index(m_head_index, 1, m_max_count);

            return value;
        }

        inline bool push_back(T *value)
        {
            if(NULL == value)
            {
                return false;
            }

            if(m_count >= m_max_count)
            {
                return false;
            }

            m_data_list[inc_index(m_head_index, m_count, m_max_count)] = value;
            m_count++;
            return true;
        }
    private:
        uint    m_count;
        uint    m_max_count;
        uint    m_head_index;
        T       **m_data_list;
    };

    template<typename T>
    class CachePool_S
    {
    public:
        CachePool_S()
        {
            m_max_count = 0;
            m_count = 0;
            m_head_index = 0;
            m_data_list = NULL;
        }

        CachePool_S(int max_count)
        {
            init(max_count);
        }

        ~CachePool_S()
        {
            clear();
        }

        inline void init(uint max_count = RX_DEFAULT_CACHE_SIZE)
        {
            if(NULL != m_data_list)
            {
                printf("\n init CachePool is not null exsists memory leak.\n");
            }

            m_max_count = max_count;
            m_count = 0;
            m_head_index = 0;
            m_data_list = new T*[m_max_count];
            if(NULL == m_data_list)
                throw;

            zero_memory(m_data_list, m_max_count* sizeof(T*));
            for(int index = 0; index < m_max_count; index++)
            {
                T *data = malloc_buffer();
                push_back(data);
            }
        }

        void clear()
        {
            LOCK_HELPER(m_lock);
            if(NULL == m_data_list)
            {
                return;
            }

            for (int index = 0; index < m_count; ++index)
            {
                if(NULL == m_data_list[m_head_index])
                    continue;

                this->free_buffer(m_data_list[m_head_index]);
                m_data_list[m_head_index] = NULL;
                m_head_index = inc_index(m_head_index, 1, m_max_count);
            }

            SAFE_DELETE_ARRAY(m_data_list);
            m_head_index = 0;
            m_count = 0;
            m_max_count = 0;
        }

        inline T *malloc_cache()
        {
            T *data = this->pop_front();
            if(NULL == data)
            {
                data = malloc_buffer();
            }

            if(inc_buffer(data) != 1)
            {
                assert(false && "CachePool_S malloc_cache one buffer more than one times");
            }

            return data;
        }

        inline bool free_cache(T *value)
        {
            if(NULL == value)
            {
                return false;
            }

            if(dec_buffer(value) != 0)
            {
                assert(false && "CachePool_S free_cache one buffer more than one times");
                return false;
            }

            if(!push_back(value))
            {
                //printf("\ncache pool is full so free\n");
                free_buffer(value);
            }
        }
        inline int size(){return m_count;}
        inline int max_size(){return m_max_count;}
        inline int remain_count(){return (m_max_count - m_count);}
    private:
        byte inc_buffer(T *value)
        {
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer -  1;
            return ++(*buffer);
        }
        byte dec_buffer(T *value)
        {
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer -  1;
            return --(*buffer);
        }
        inline T *malloc_buffer()
        {
            uint l_size = sizeof(byte) + sizeof(T);
            char* l_buffer = new char[l_size];
            l_buffer[0] = 0;
            T *data = reinterpret_cast<T *>(l_buffer + 1);
            new( data ) T;
            return data;
        }
        void free_buffer(T *value)
        {
            value->~T();
            byte *buffer = reinterpret_cast<byte *>(value);
            buffer = buffer - 1;
            SAFE_DELETE_ARRAY(buffer);
        }
        inline T *pop_front()
        {
            LOCK_HELPER(m_lock);
            if(m_count < 0)
            {
                return NULL;
            }

            T *value = m_data_list[m_head_index];
            m_data_list[m_head_index] = NULL;
            m_count--;
            m_head_index = inc_index(m_head_index, 1, m_max_count);

            return value;
        }

        inline bool push_back(T *value)
        {
            if(NULL == value)
            {
                return false;
            }

            LOCK_HELPER(m_lock);

            if(m_count >= m_max_count)
            {
                return false;
            }

            m_data_list[inc_index(m_head_index, m_count, m_max_count)] = value;
            m_count++;
            return true;
        }
    private:
        Lock    m_lock;
        uint    m_count;
        uint    m_max_count;
        uint    m_head_index;
        T       **m_data_list;
    };

RELAX_NAMESPACE_END

#endif //__RX_MEMCACHE_H__
