/*
 * file_name: GlobalResource.h
 * file_detail:global variable
 * created by silver0511
 */

#ifndef __RX_GLOBALRESOURCE_H__
#define __RX_GLOBALRESOURCE_H__

#include "common/platform.h"

USING_RELAX_NAMESPACE

extern time_t   g_local_time;
extern string   g_project_name;

void set_g_local_time(time_t local_time);
time_t get_g_local_time();


#endif //__RX_GLOBALRESOURCE_H__
