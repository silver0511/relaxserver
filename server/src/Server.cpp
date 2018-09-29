/*
 * file_name: Server.cpp
 * file_detail:main file
 * created by silver0511
 */

#include <signal.h>
#include "common/platform.h"
#include "common/LogMacro.h"
#include "GlobalResource.h"

USING_RELAX_NAMESPACE

volatile bool g_running = true;

static void sig_1(int code)
{
    //exit
}

static void sig_2(int code)
{
    //exit
    LOG_TRACE(LOG_CRIT, "session sig_2:" << code)
}

static void sig_quit(int code)
{
    //exit
    g_running = false;
    LOG_TRACE(LOG_CRIT, "session sig_quit:" << code)
}

int main(int argc, char *argv[])
{
    signal(SIGPIPE, sig_1);
    signal(SIGHUP, sig_2);
    signal(SIGTERM, sig_quit);

    if(argc < 2)
    {
        printf("argv is invalid \n");
        return 1;
    }

    g_project_name = "server.1.1.100";
#ifdef TRACE_LOG
    std::string l_log_file_name = g_project_name;
    LOG_INIT(DEF_DISPLAY_TYPE_THREAD, LOG_DEBUG_2, l_log_file_name.c_str());
#endif
    System::init_random();
    while (g_running)
    {
        System::sleep(10);
    }

    LOG_TRACE(LOG_ALERT, "exit server......")
    LOG_CLOSE()
    return 0;
}