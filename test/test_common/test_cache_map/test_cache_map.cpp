/*
 * file_name: test_cache_map.cpp
 * file_detail:test CacheMap.h interface
 * created by silver0511
 */

#include <vector>
#include "common/CacheMap.h"
#include "common/System.h"
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

CacheMap<int, TestClass> m_g_cache_hash_map;
CacheMap<int, TestClass> m_g_cache_tree_map;
vector<int>              m_g_hash_key_vec;
Lock                     m_g_hash_key_lock;

vector<int>              m_g_tree_key_vec;
Lock                     m_g_tree_key_lock;

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
                TestClass *p_test_class = m_g_cache_hash_map.malloc_node();
                p_test_class->int_value = rand();
                p_test_class->str_val = "test";
                m_g_cache_hash_map.add(p_test_class->int_value, p_test_class);
                m_g_hash_key_lock.lock();
                m_g_hash_key_vec.push_back(p_test_class->int_value);
                m_g_hash_key_lock.unlock();
                printf("thread safe hash map add:%d\n", p_test_class->int_value);
            }
            {
                TestClass *p_test_class = m_g_cache_tree_map.malloc_node();
                p_test_class->int_value = rand();
                p_test_class->str_val = "test";
                m_g_cache_tree_map.add(p_test_class->int_value, p_test_class);
                m_g_tree_key_lock.lock();
                m_g_tree_key_vec.push_back(p_test_class->int_value);
                m_g_tree_key_lock.unlock();
                printf("thread safe tree map add:%d \n", p_test_class->int_value);
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
                int key_value = rand();
                if(!m_g_hash_key_vec.empty())
                {
                    m_g_hash_key_lock.lock();
                    int key_index = rand() % m_g_hash_key_vec.size();
                    vector<int>::iterator iter = m_g_hash_key_vec.begin();
                    iter += key_index;
                    key_value = (*iter);
                    m_g_hash_key_vec.erase(iter);
                    m_g_hash_key_lock.unlock();
                }
                TestClass *p_test_class = m_g_cache_hash_map.get(key_value);
                printf("thread safe hash map get:%d is 0x%llx...remove is %d \n", key_value, (uint64)p_test_class,
                       m_g_cache_hash_map.remove(key_value));
            }
            {
                int key_value = rand();
                if(!m_g_tree_key_vec.empty())
                {
                    m_g_tree_key_lock.lock();
                    int key_index = rand() % m_g_tree_key_vec.size();
                    vector<int>::iterator iter = m_g_tree_key_vec.begin();
                    iter += key_index;
                    key_value = (*iter);
                    m_g_tree_key_vec.erase(iter);
                    m_g_tree_key_lock.unlock();
                }

                TestClass *p_test_class = m_g_cache_tree_map.get(key_value);
                printf("thread safe tree map get:%d is 0x%llx...remove is %d \n", key_value, (uint64)p_test_class,
                       m_g_cache_tree_map.remove(key_value));
            }
        }
    }
}

void test_unsafe_map()
{

    printf("test m_g_cache_hash_map thread unsafe start ============ \n");
    m_g_cache_hash_map.init(10, HASH_MAP, ACTIVE_CACHE, false);
    for(int i = 0; i < 12; i++)
    {
        TestClass *p_test_class = m_g_cache_hash_map.malloc_node();
        p_test_class->int_value = rand();
        p_test_class->str_val = "test";
        m_g_cache_hash_map.add(p_test_class->int_value, p_test_class);
        m_g_hash_key_vec.push_back(p_test_class->int_value);
        printf("hash map add:%d\n", p_test_class->int_value);
    }

    for(int i = 0; i < 15; i++)
    {
        int key_value = rand();
        if(!m_g_hash_key_vec.empty())
        {
            int key_index = rand() % m_g_hash_key_vec.size();
            vector<int>::iterator iter = m_g_hash_key_vec.begin();
            iter += key_index;
            key_value = (*iter);
            m_g_hash_key_vec.erase(iter);
        }

        TestClass *p_test_class = m_g_cache_hash_map.get(key_value);
        printf("hash map get:%d is 0x%llx...remove is %d \n", key_value, (uint64)p_test_class,
               m_g_cache_hash_map.remove(key_value));

    }
    printf("test m_g_cache_hash_map thread unsafe end ============== \n");

    printf("test m_g_cache_tree_map thread unsafe start ============ \n");
    m_g_cache_tree_map.init(10, TREE_MAP, ACTIVE_CACHE, false);
    for(int i = 0; i < 12; i++)
    {
        TestClass *p_test_class = m_g_cache_tree_map.malloc_node();
        p_test_class->int_value = rand();
        p_test_class->str_val = "test";
        m_g_cache_tree_map.add(p_test_class->int_value, p_test_class);
        m_g_tree_key_vec.push_back(p_test_class->int_value);
        printf("tree map add:%d \n", p_test_class->int_value);
    }

    for(int i = 0; i < 15; i++)
    {
        int key_value = rand();
        if(!m_g_tree_key_vec.empty())
        {
            int key_index = rand() % m_g_tree_key_vec.size();
            vector<int>::iterator iter = m_g_tree_key_vec.begin();
            iter += key_index;
            key_value = (*iter);
            m_g_tree_key_vec.erase(iter);
        }

        TestClass *p_test_class = m_g_cache_tree_map.get(key_value);
        printf("tree map get:%d is 0x%llx...remove is %d \n", key_value, (uint64)p_test_class,
               m_g_cache_tree_map.remove(key_value));

    }
    printf("test m_g_cache_tree_map thread unsafe end ============== \n");
}

void test_safe_map()
{
    m_g_cache_hash_map.clear();
    m_g_cache_tree_map.clear();

    m_g_cache_hash_map.init(10, HASH_MAP, ACTIVE_CACHE);
    m_g_cache_tree_map.init(10, TREE_MAP, ACTIVE_CACHE, true);

    m_g_hash_key_vec.clear();
    m_g_tree_key_vec.clear();

    ThreadHelper::begin_thread(test_thread_proc, NULL);
    ThreadHelper::begin_thread(test_thread_proc2, NULL);
}


int main()
{
    test_unsafe_map();
    test_safe_map();
    getchar();
    return 1;
}