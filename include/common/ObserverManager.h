/*
 * file_name: ObserverManager.h
 * file_detail:manager IObserver
 * created by silver0511
 */

#ifndef __RX_OBSERVERMANAGER_H__
#define __RX_OBSERVERMANAGER_H__

#include "common/platform.h"
#include "IObserver.h"
#include "const/EventConstDef.h"

RELAX_NAMESPACE_BEGIN

class ObserverManager
{
private:
    ObserverManager();
    ObserverManager(const ObserverManager &);
    ObserverManager &operator = (const ObserverManager &);
public:
    ~ObserverManager();

    static ObserverManager &Instance()
    {
        static ObserverManager instance;
        return instance;
    }
public:
    void subscribe(const uint &event_id, IObserver *observer);
    void unsubscribe(const uint &event_id, IObserver *observer);
    void notify(const uint &event_id, void *param1, void *param2);

private:
    map<uint, set<IObserver *> > m_observer_map;
};

RELAX_NAMESPACE_END

#endif //__RX_OBSERVERMANAGER_H__
