/*
 * file_name: BaseFun.h
 * file_detail:base fun
 * created by silver0511
 */

#ifndef __RX_BASE_FUN_H__
#define __RX_BASE_FUN_H__
#include "common/platform.h"
#include <linux/unistd.h>
using namespace std;

RELAX_NAMESPACE_BEGIN

#ifdef __NR_gettid
    //syscall0(int, gettid)
    inline int gettid ()
    {
        return syscall(__NR_gettid);
    }
#else
    inline int gettid()
    {
        return -ENOSYS;
    }
#endif /* __NR_gettid */

    inline int inc_index(int index, int count, int size)
    {
        return (index + count) % size;
    }

    inline int dec_index(int index, int count, int size)
    {
        uint temp = (index + size);
        return (int)(temp - count) % size;
    }

    //支持memcpy的边界检查
    inline bool memcpy_safe(char* src, int src_len, char* des, int des_len)
    {
        if(src_len > des_len)
        {
            return false;
        }
        else
        {

            memcpy((void* )des, (void* )src, (size_t)src_len);
            return true;
        }
    }

    inline std::string get_app_path()
    {
        char l_app_path[256] = {0};
        char l_full_path[256] = {0};

        sprintf(l_app_path, "/proc/%d/exe", getpid());
        readlink(l_app_path, l_full_path, 255);

        int i = 0;
        for(i = strlen(l_full_path); i >= 0; i--)
        {
            if (l_full_path[i] == '/')
            {
                l_full_path[i] = '\0';
                break;
            }
        }

        std::string l_ret_path = l_full_path;
        l_ret_path += "/";

        return l_ret_path;
    }

    inline std::string get_full_path(char *file_name)
    {
        if(NULL == file_name)
        {
            return "";
        }

        string l_app_path = get_app_path();
        string l_full_path = l_app_path + file_name;
        return l_full_path;
    }

    inline void *load_lib(const char *lib_name)
    {
        if(NULL == lib_name)
        {
            return NULL;
        }

        void *l_handle = dlopen(lib_name, RTLD_LAZY);
        if(NULL != dlerror())
        {
            printf("\n load_lib %s failed: %s", lib_name, dlerror());
            return NULL;
        }

        return l_handle;
    }

    inline bool free_lib(void *handle)
    {
        if(NULL == handle)
        {
            return FALSE;
        }

        bool result = (bool)dlclose(handle);

        return result;
    }

    inline void *get_func(void *handle, const char *func_name)
    {
        if(NULL == handle || NULL == func_name || 0 >= strlen(func_name))
        {
            return NULL;
        }

        void *l_func = dlsym(handle, func_name);
        if(NULL != dlerror())
        {
            printf("\n get_func %s failed: %s", func_name, dlerror());
            return NULL;
        }

        return l_func;
    }

    inline ulong get_thread_id()
    {
        return (ulong)gettid();
    }

    inline pid_t get_cur_proc_id()
    {
        return getpid();
    }

    inline string get_ip_str(unsigned int ip)
    {
        struct  in_addr addr;
        memset(&addr,0,sizeof(struct in_addr));
        addr.s_addr = ip;
        return inet_ntoa(addr);
    }

    inline IPTYPE get_ip_by_host(const char *host_name)
    {//
        if (NULL == host_name)
            return 0;

        hostent *l_hostent=NULL;
        try
        {
            l_hostent = ::gethostbyname(host_name);
        }
        catch (...)
        {
            return 0;
        }
        if(NULL == l_hostent)
            return 0;
        struct in_addr *l_addr=((struct in_addr *)l_hostent->h_addr);
        return l_addr->s_addr;
    }


    //support ipv4
    inline string get_intranet_ip()
    {
        struct ifaddrs *stru_if_addr = NULL;
        void * addr_ptr = NULL;

        getifaddrs(&stru_if_addr);

        while (stru_if_addr!=NULL)
        {

            if (stru_if_addr->ifa_addr->sa_family == AF_INET)
            {
                addr_ptr = &((struct sockaddr_in *)stru_if_addr->ifa_addr)->sin_addr;
                char addr_buff[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, addr_ptr, addr_buff, INET_ADDRSTRLEN);
                string intranet_ip = addr_buff;
                string head_ip = intranet_ip.substr(0,3);
                if(head_ip == "172" ||
                   head_ip == "10." ||
                   head_ip == "192")
                {
                    printf("address ip name:%s ip:%s\n", stru_if_addr->ifa_name, addr_buff);
                    if(strcmp(stru_if_addr->ifa_name,"eth0") == 0 ||
                       strcmp(stru_if_addr->ifa_name,"eth1") == 0 ||
                       strcmp(stru_if_addr->ifa_name,"em1") == 0 ||
                       strcmp(stru_if_addr->ifa_name,"em2") == 0)
                    {
                        printf("address ip get name:%s ip:%s\n", stru_if_addr->ifa_name, addr_buff);
                        return intranet_ip;
                    }
                }
            }

//		else if (stru_if_addr->ifa_addr->sa_family == AF_INET6)
//		{
//			addr_ptr=&((struct sockaddr_in *)stru_if_addr->ifa_addr)->sin_addr;
//			char addr_buff[INET6_ADDRSTRLEN];
//			inet_ntop(AF_INET6, addr_ptr, addr_buff, INET6_ADDRSTRLEN);
//			printf("%s IPV6 Address %s\n", stru_if_addr->ifa_name, addr_buff);
//		}

            stru_if_addr = stru_if_addr->ifa_next;
        }

        return "";
    }


RELAX_NAMESPACE_END

#endif //__RX_BASE_FUN_H__
