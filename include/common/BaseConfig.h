/*
 * file_name: BaseConfig.h
 * file_detail:base config,parse config file by json
 * created by silver0511
 */

#ifndef __RX__BASE_CONFIG_H__
#define __RX__BASE_CONFIG_H__
#include "common/platform.h"
#include "common/BaseFun.h"
#include "rjson/JsonParser.h"

RELAX_NAMESPACE_BEGIN

    class BaseConfig
    {
    public:
        BaseConfig();
        virtual ~BaseConfig();
        virtual bool load(const char *file_name);
        //elapsed_time(ms)
        virtual bool check_event(int elapsed_time);
    public:
        virtual bool dynamic_read() = 0;
        virtual bool read() = 0;
    protected:
        RJDocument  m_document;
    private:
        int m_elapsed_time;                         //current elapsed time(ms)
        int m_read_interval;                        //read interval time(ms)
        const char *m_read_file_name;               //config file absolutely path
    };

    class ServerConfig : public BaseConfig
    {
    public:
        ServerConfig();
        ~ServerConfig();
        virtual bool read();
        virtual bool dynamic_read();
    public:
        //log related parameters
        int m_log_level;

        //server side(listen) related parameters
        int m_nio_threads;                           //recv() function process thread count
        int m_deal_threads;                          //process user logic thread count
        int m_max_con;                               //pre-allocated max connect count
        string m_white_ips;                          //while list split by ','

        //rpc side(connect) related parameters
        int m_rpc_con;                               //back server connect count
        int m_rpc_con_threads;                       //back server connect thread counts
        int m_rpc_recv_threads;                      //back server recv() function process thread count
        int m_rpc_deal_threads;                      //back server process user logic thread count
    };
RELAX_NAMESPACE_END

#endif //__RX__BASE_CONFIG_H__
