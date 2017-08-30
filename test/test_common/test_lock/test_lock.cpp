/*
 * file_name: test_lock.cpp
 * file_detail:test Lock.h interface
 * created by silver0511
 */
#include "common/System.h"
#include "common/BaseThread.h"
#include "common/Lock.h"

USING_RELAX_NAMESPACE

Lock m_g_lock;

class TestThread : public BaseThread
{
public:
    TestThread(){}
    ~TestThread(){}
    //inherit basethread
    virtual void run()
    {
        int64 start_time = System::get_ms_time();
        int64 end_time = start_time;
        printf("TestThread is running===%s==%lld== \n", (char *)m_user_data, start_time);
        m_g_lock.lock();
        while(m_run)
        {
            end_time = System::get_ms_time();
            if((end_time - start_time) > 1000 * 2)
            {
                start_time = end_time;
                printf("TestThread ready to stop====%s==%lld= \n", (char *)m_user_data, end_time);
                m_g_lock.unlock();
                break;
            }
        }
    }
    virtual void release()
    {
        BaseThread::release();
    }
    virtual void stop()
    {
        System::sleep(1000);
        BaseThread::stop();
        System::sleep(1000);
    }
};

static void test_thread_proc(void *ptr)
{
    int64 start_time = System::get_ms_time();
    int64 end_time = start_time;
    printf("test_thread_proc is running===%s==%lld== \n", (char *)ptr, start_time);
    m_g_lock.lock();
    while(true)
    {
        end_time = System::get_ms_time();
        if((end_time - start_time) > 1000 * 5)
        {
            start_time = end_time;
            printf("test_thread_proc ready to stop====%s==%lld=== \n", (char *)ptr, end_time);
            m_g_lock.unlock();
            break;
        }
    }
}

struct STRU_TRHEAD_CONTEXT
{
    void *m_this;
    int m_thread_index;
};

class TestThreadClass
{
public:
    TestThreadClass(){}
    ~TestThreadClass(){}

    static void TestThreadProc(void *ptr)
    {
        STRU_TRHEAD_CONTEXT *thread_context = (STRU_TRHEAD_CONTEXT *)ptr;
        TestThreadClass *p_test_thread2 = (TestThreadClass *)thread_context->m_this;
        p_test_thread2->TestThreadProc(thread_context->m_thread_index);
        SAFE_DELETE(thread_context);
    }

    void TestThreadProc(int index)
    {
        int64 start_time = System::get_ms_time();
        int64 end_time = start_time;
        printf("[TestThreadClass TestThreadProc] is running===%d==%lld== \n", index, start_time);
        m_lock.lock();
        while(true)
        {
            end_time = System::get_ms_time();
            if((end_time - start_time) > (1000 * (8 + index)))
            {
                start_time = end_time;
                printf("[TestThreadClass TestThreadProc] ready to stop====%d==%lld=== \n", index, end_time);
                m_lock.unlock();
                break;
            }
        }
    }

    void Init()
    {
        for(int i = 0; i < 5; i++)
        {
            STRU_TRHEAD_CONTEXT *thread_context = new STRU_TRHEAD_CONTEXT;
            thread_context->m_this = (void *)this;
            thread_context->m_thread_index = i;
            ThreadHelper::begin_thread(TestThreadProc, (void *)thread_context);
        }
    }
private:
    Lock m_lock;
};

int main()
{
    TestThread *test_thread1 = new TestThread;
    const char *thread_name1 = "test_thread1";
    test_thread1->begin_thread(true, NULL, (void *)thread_name1);
    TestThread test_thread2;
    const char *thread_name2 = "test_thread2";
    test_thread2.begin_thread(false, NULL, (void *)thread_name2);

    const char *thread_name3 = "test_thread3";
    ThreadHelper::begin_thread(test_thread_proc,(void *)thread_name3);

    TestThreadClass test_thread_class;
    test_thread_class.Init();

    Lock l_lock;
    LOCK_HELPER(l_lock);
    getchar();
    return 1;
}