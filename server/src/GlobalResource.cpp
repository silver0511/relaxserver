/*
 * file_name: GlobalResource.h
 * file_detail:global variable
 * created by silver0511
 */

#include "GlobalResource.h"

string g_project_name = "";

time_t g_local_time = 0;

void set_g_local_time(time_t local_time)
{
    g_local_time = local_time;
}

time_t get_g_local_time()
{
    return g_local_time;
}