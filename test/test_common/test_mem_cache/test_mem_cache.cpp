/*
 * file_name: test_mem_cache.cpp
 * file_detail:test MemCache.h interface
 * created by silver0511
 */
#include "common/System.h"
#include "common/BaseThread.h"
#include "common/MemCache.h"
#include <vector>
#include <queue>

USING_RELAX_NAMESPACE


class TestClass
{
public:
    TestClass()
    {
        printf("TestClass() \n");
    }
    ~TestClass()
    {
        printf("~TestClass() \n");
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

CachePool<TestClass>  m_g_test_cache_pool;
CachePool_S<TestClass>  m_g_test_cache_pool_s;
queue<TestClass*>   m_g_queue;
Lock                m_g_lock;

static void test_thread_proc(void *ptr)
{
    int64 start_time = System::get_ms_time();
    int64 end_time = start_time;
    printf("test_thread_proc is running====%lld== \n", start_time);
    while(true)
    {
        end_time = System::get_ms_time();
        if((end_time - start_time) > 0)
        {
            start_time = end_time;
            TestClass *p_test_class = m_g_test_cache_pool_s.malloc_cache();
            m_g_lock.lock();
            m_g_queue.push(p_test_class);
            m_g_lock.unlock();
        }
    }
}

static void test_thread_proc_2(void *ptr)
{
    int64 start_time = System::get_ms_time();
    int64 end_time = start_time;
    printf("test_thread_proc_2 is running====%lld== \n", start_time);
    while(true)
    {
        end_time = System::get_ms_time();
        if((end_time - start_time) > 0)
        {
            start_time = end_time;
            if(!m_g_queue.empty())
            {
                m_g_lock.lock();
                TestClass *p_test_class = m_g_queue.front();
                m_g_queue.pop();
                m_g_lock.unlock();
                m_g_test_cache_pool_s.free_cache(p_test_class);
            }
        }
    }
}

int main()
{
    vector<TestClass *> l_test_class_vec;
    const uint CACHE_SIZE = 10;
    printf("CachePool test start============\n");
    m_g_test_cache_pool.init(CACHE_SIZE);
    for(int i = 0; i < CACHE_SIZE/2; ++i)
    {
        TestClass *p_test_class = m_g_test_cache_pool.malloc_cache();
        p_test_class->init();
        l_test_class_vec.push_back(p_test_class);
    }
    printf("CachePool malloc_cache ========%d====\n", CACHE_SIZE/2);
    TestClass *p_test_class = l_test_class_vec[0];
    m_g_test_cache_pool.free_cache(p_test_class);
    printf("CachePool free_cache ========%d====\n", 1);

    for(int i = 0; i < CACHE_SIZE; ++i)
    {
        TestClass *p_test_class = m_g_test_cache_pool.malloc_cache();
        p_test_class->init();
        l_test_class_vec.push_back(p_test_class);
    }
    printf("CachePool malloc_cache ========%d====\n", CACHE_SIZE);
    for(int i = 0; i < l_test_class_vec.size(); ++i)
    {
        TestClass *p_test_class = l_test_class_vec[i];
        m_g_test_cache_pool.free_cache(p_test_class);
    }
    printf("CachePool free_cache ========%d====\n", l_test_class_vec.size());
    printf("CachePool test end============\n\n\n");


    printf("CachePool_S test start============\n");
    m_g_test_cache_pool_s.init(CACHE_SIZE);
    ThreadHelper::begin_thread(test_thread_proc, NULL);
    ThreadHelper::begin_thread(test_thread_proc_2, NULL);

    getchar();
    return 1;
}