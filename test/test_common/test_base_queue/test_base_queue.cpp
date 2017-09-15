/*
 * file_name: test_base_queue.cpp
 * file_detail:test BaseQueue.h interface
 * created by silver0511
 */

#include <vector>
#include "common/BaseQueue.h"
#include "common/System.h"
#include "common/MemCache.h"
#include "common/BaseThread.h"

USING_RELAX_NAMESPACE

class TestClass
{
public:
    TestClass()
    {
    }
    ~TestClass()
    {
    }

    void init()
    {
        int_value = 0;
        flag = false;
        str_val = "";
    }

public:
    int int_value;
    bool flag;
    string str_val;
};


Queue<TestClass>        m_g_safe_queue;
Queue<TestClass>        m_g_unsafe_queue;
DoubleQueue<TestClass>  m_g_safe_double_queue;
DoubleQueue<TestClass>  m_g_unsafe_double_queue;

CachePool<TestClass>  m_g_test_cache_pool;
CachePool_S<TestClass>  m_g_test_cache_pool_s;

static void test_thread_proc(void *ptr)
{
    int64 start_time = System::get_ms_time();
    int64 end_time = start_time;
    printf("test_thread_proc is running====%lld== \n", start_time);
    int delta_time = 1000;
    while(true)
    {
        end_time = System::get_ms_time();
        if((end_time - start_time) > delta_time)
        {
            start_time = end_time;
            delta_time += 10;
            {
                TestClass *p_test_class = m_g_test_cache_pool_s.malloc_cache();
                p_test_class->int_value = rand();
                p_test_class->str_val = "test";
                m_g_safe_queue.push_back(p_test_class);
                printf("thread safe m_g_safe_queue push:%d\n", p_test_class->int_value);
                if(m_g_safe_queue.is_full())
                {
                    printf("thread safe m_g_safe_queue is full:%d, size:%d\n", p_test_class->int_value,
                           m_g_safe_queue.size());
                }
            }
            {
                TestClass *p_test_class = m_g_test_cache_pool_s.malloc_cache();
                p_test_class->int_value = rand();
                p_test_class->str_val = "test";
                if(p_test_class->int_value % 2 == 0)
                {
                    m_g_safe_double_queue.push_back(p_test_class);
                    printf("thread safe m_g_safe_double_queue push_back:%d\n", p_test_class->int_value);
                }
                else
                {
                    m_g_safe_double_queue.push_front(p_test_class);
                    printf("thread safe m_g_safe_double_queue push_front:%d\n", p_test_class->int_value);
                }
                if(m_g_safe_double_queue.is_full())
                {
                    printf("thread safe m_g_safe_double_queue is full:%d, size:%d\n", p_test_class->int_value,
                           m_g_safe_double_queue.size());
                }
            }
        }
    }
}

static void test_thread_proc2(void *ptr)
{
    int64 start_time = System::get_ms_time();
    int64 end_time = start_time;
    printf("test_thread_proc is running====%lld== \n", start_time);
    int delta_time = 2000;
    while(true)
    {
        end_time = System::get_ms_time();
        if((end_time - start_time) > delta_time)
        {
            start_time = end_time;
            delta_time-=10;
            {
                if(m_g_safe_queue.size() <= 0)
                {
                    printf("thread safe m_g_safe_queue is empty\n");
                }
                TestClass *p_test_class = m_g_safe_queue.front();
                if(p_test_class == NULL)
                {
                    printf("thread safe m_g_safe_queue p_test_class is NULL\n");
                    continue;
                }
                printf("thread safe m_g_safe_queue front:%d\n", p_test_class->int_value);
                p_test_class = m_g_safe_queue.pop_front();
                printf("thread safe m_g_safe_queue pop_front:%d\n", p_test_class->int_value);
                m_g_test_cache_pool_s.free_cache(p_test_class);
            }
            {
                if(m_g_safe_double_queue.size() <= 0)
                {
                    printf("thread safe m_g_safe_double_queue is empty\n");
                }

                if(rand() % 2 == 0)
                {
                    TestClass *p_test_class = m_g_safe_double_queue.front();
                    if(p_test_class == NULL)
                    {
                        printf("thread safe m_g_safe_double_queue p_test_class is NULL\n");
                        continue;
                    }
                    printf("thread safe m_g_safe_double_queue front:%d\n", p_test_class->int_value);
                    p_test_class = m_g_safe_double_queue.pop_front();
                    printf("thread safe m_g_safe_double_queue pop_front:%d\n", p_test_class->int_value);
                    m_g_test_cache_pool_s.free_cache(p_test_class);
                }
                else
                {
                    TestClass *p_test_class = m_g_safe_double_queue.back();
                    if(p_test_class == NULL)
                    {
                        printf("thread safe m_g_safe_double_queue p_test_class is NULL\n");
                        continue;
                    }
                    printf("thread safe m_g_safe_double_queue back:%d\n", p_test_class->int_value);
                    p_test_class = m_g_safe_double_queue.pop_back();
                    printf("thread safe m_g_safe_double_queue pop_back:%d\n", p_test_class->int_value);
                    m_g_test_cache_pool_s.free_cache(p_test_class);
                }
            }
        }
    }
}

void test_safe_queue()
{
    m_g_safe_queue.init(10);
    m_g_safe_double_queue.init(10);
    m_g_test_cache_pool_s.init(1000);

    ThreadHelper::begin_thread(test_thread_proc, NULL);
    ThreadHelper::begin_thread(test_thread_proc2, NULL);
}

void test_unsafe_queue()
{
    m_g_test_cache_pool.init(100);
    printf("test test_unsafe_queue thread unsafe start ============ \n");
    m_g_unsafe_queue.init(10, false);
    for(int i = 0; i < 12; i++)
    {
        TestClass *p_test_class = m_g_test_cache_pool.malloc_cache();
        p_test_class->int_value = rand();
        p_test_class->str_val = "test";
        m_g_unsafe_queue.push_back(p_test_class);
        printf("m_g_unsafe_queue push:%d\n", p_test_class->int_value);
        if(m_g_unsafe_queue.is_full())
        {
            printf("m_g_unsafe_queue is full:%d, size:%d\n", p_test_class->int_value,
            m_g_unsafe_queue.size());
        }
    }

    for(int i = 0; i < 15; i++)
    {
        if(m_g_unsafe_queue.size() <= 0)
        {
            printf("m_g_unsafe_queue is empty\n");
        }
        TestClass *p_test_class = m_g_unsafe_queue.front();
        if(p_test_class == NULL)
        {
            printf("m_g_unsafe_queue p_test_class is NULL\n");
            continue;
        }
        printf("m_g_unsafe_queue front:%d\n", p_test_class->int_value);
        p_test_class = m_g_unsafe_queue.pop_front();
        printf("m_g_unsafe_queue pop_front:%d\n", p_test_class->int_value);
        m_g_test_cache_pool.free_cache(p_test_class);
    }


    printf("test test_unsafe_double_queue thread unsafe start ============ \n");
    m_g_unsafe_double_queue.init(10, false);
    for(int i = 0; i < 12; i++)
    {
        TestClass *p_test_class = m_g_test_cache_pool.malloc_cache();
        p_test_class->int_value = rand();
        p_test_class->str_val = "test";
        if(i % 2 == 0)
        {
            m_g_unsafe_double_queue.push_back(p_test_class);
            printf("m_g_unsafe_queue push_back:%d\n", p_test_class->int_value);
        }
        else
        {
            m_g_unsafe_double_queue.push_front(p_test_class);
            printf("m_g_unsafe_queue push_front:%d\n", p_test_class->int_value);
        }

        if(m_g_unsafe_double_queue.is_full())
        {
            printf("m_g_unsafe_double_queue is full:%d, size:%d\n", p_test_class->int_value,
                   m_g_unsafe_double_queue.size());
        }
    }

    for(int i = 0; i < 15; i++)
    {
        if(m_g_unsafe_double_queue.size() <= 0)
        {
            printf("m_g_unsafe_double_queue is empty\n");
        }

        if(i % 2 == 0)
        {
            TestClass *p_test_class = m_g_unsafe_double_queue.front();
            if(p_test_class == NULL)
            {
                printf("m_g_unsafe_double_queue p_test_class is NULL\n");
                continue;
            }
            printf("m_g_unsafe_double_queue front:%d\n", p_test_class->int_value);
            p_test_class = m_g_unsafe_double_queue.pop_front();
            printf("m_g_unsafe_double_queue pop_front:%d\n", p_test_class->int_value);
            m_g_test_cache_pool.free_cache(p_test_class);
        }
        else
        {
            TestClass *p_test_class = m_g_unsafe_double_queue.back();
            if(p_test_class == NULL)
            {
                printf("m_g_unsafe_double_queue p_test_class is NULL\n");
                continue;
            }
            printf("m_g_unsafe_double_queue back:%d\n", p_test_class->int_value);
            p_test_class = m_g_unsafe_double_queue.pop_back();
            printf("m_g_unsafe_double_queue pop_back:%d\n", p_test_class->int_value);
            m_g_test_cache_pool.free_cache(p_test_class);
        }
    }
}

int main()
{
    test_unsafe_queue();
    test_safe_queue();
    getchar();
    return 1;
}