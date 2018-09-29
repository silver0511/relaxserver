/*
 * file_name: BaseConfig.h
 * file_detail:base config,parse config file by json
 * created by silver0511
 */

#include "common/BaseConfig.h"
USING_RELAX_NAMESPACE

BaseConfig::BaseConfig():m_elapsed_time(0),
                         m_read_interval(30 * 1000),
                         m_read_file_name(""),
                         m_load_mode(INVALID_MODE)
{

}

BaseConfig::~BaseConfig()
{

}

bool BaseConfig::load_file(const char *file_name)
{
    if(NULL == file_name)
    {
        return false;
    }

    if(m_read_file_name.empty())
    {
        m_read_file_name = get_app_path();
        m_read_file_name += file_name;
        printf("\n[BaseConfig load] full_path: %s \n", m_read_file_name.c_str());
    }
    bool result = JsonParse::parse_file(m_document, m_read_file_name.c_str());
    if(!result || m_document.IsNull())
    {
        printf("\n[BaseConfig load] read config file %s invalid\n", m_read_file_name.c_str());
        return false;
    }

    m_load_mode = FILE_MODE;
    return true;
}

bool BaseConfig::load_memory(const string &data)
{
    if(data.empty())
    {
        return false;
    }

    bool result = JsonParse::parse(m_document, data.c_str());
    if(!result || m_document.IsNull())
    {
        printf("\n[BaseConfig load] read data %s invalid\n", data.c_str());
        return false;
    }

    m_load_mode = MEMORY_MODE;
    return true;
}

bool BaseConfig::check_event(int elapsed_time)
{
    if(m_load_mode != FILE_MODE)
    {
        return true;
    }

    m_elapsed_time += elapsed_time;
    if(m_elapsed_time > m_read_interval)
    {
        m_elapsed_time = 0;
        load_file(m_read_file_name.c_str());
        dynamic_read();
    }
    return true;
}


ServerConfig::ServerConfig()
{
    m_log_level = 1;

    m_nio_threads = 1;
    m_deal_threads = 1;
    m_max_con = 1024;
    m_white_ips = "";

    m_rpc_con = 1;
    m_rpc_con_threads = 1;
    m_rpc_recv_threads = 1;
    m_rpc_deal_threads = 1;
}

ServerConfig::~ServerConfig()
{

}

bool ServerConfig::read()
{
    if(m_document.IsNull())
    {
        printf("\n[BaseConfig read] config file not load\n");
        return false;
    }

    RJsonValue &child_log = JsonParse::get_child(m_document, "log_config");
    m_log_level = JsonParse::get<int>(child_log, "log_level");

    RJsonValue &child_server_side = JsonParse::get_child(m_document, "server_side_config");
    m_nio_threads = JsonParse::get<int>(child_server_side, "nio_threads");
    m_deal_threads = JsonParse::get<int>(child_server_side, "deal_threads");
    m_max_con = JsonParse::get<int>(child_server_side, "max_con");
    m_white_ips = JsonParse::get(child_server_side, "white_ips");

    RJsonValue &child_rpc_side = JsonParse::get_child(m_document, "rpc_side_config");
    m_rpc_con = JsonParse::get<int>(child_rpc_side, "rpc_con");
    m_rpc_con_threads = JsonParse::get<int>(child_rpc_side, "rpc_con_threads");
    m_rpc_recv_threads = JsonParse::get<int>(child_rpc_side, "rpc_recv_threads");
    m_rpc_deal_threads = JsonParse::get<int>(child_rpc_side, "rpc_deal_threads");
    return false;
}

bool ServerConfig::dynamic_read()
{
    RJsonValue &child_log = JsonParse::get_child(m_document, "log_config");
    m_log_level = JsonParse::get<int>(child_log, "log_level");
    return true;
}

void ServerConfig::get_dump()
{
    printf("[ServerConfig get_dump] log_level:%d, nio_threads:%d, deal_threads:%d, max_con:%d, "
                   "white_ips:%s, rpc_con:%d, rpc_con_threads:%d, rpc_recv_threads:%d, "
                   "rpc_recv_threads:%d\n\n", m_log_level, m_nio_threads,
           m_deal_threads, m_max_con, m_white_ips.c_str(), m_rpc_con, m_rpc_con_threads,
           m_rpc_recv_threads, m_rpc_deal_threads);
}
