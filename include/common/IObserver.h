/*
 * file_name: IObserver.h
 * file_detail:observer mode interface
 * created by silver0511
 */

#ifndef __RX_IOBSERVER_H__
#define __RX_IOBSERVER_H__

#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

class IObserver
{
public:
    virtual ~IObserver();
    virtual void on_change(const uint event_id, void *param1, void *param2) == 0;
};

RELAX_NAMESPACE_END

#endif //__RX_IOBSERVER_H__
