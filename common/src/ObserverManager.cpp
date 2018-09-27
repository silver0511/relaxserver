/*
 * file_name: ObserverManager.cpp
 * file_detail:implementation ObserverManager
 * created by silver0511
 */

#include "common/ObserverManager.h"

USING_RELAX_NAMESPACE

ObserverManager::ObserverManager()
{

}

ObserverManager::~ObserverManager()
{

}

void ObserverManager::subscribe(const uint &event_id, IObserver *observer)
{
    assert(NULL != observer);
    auto l_iter = m_observer_map.find(event_id);
    if(l_iter == m_observer_map.end())
    {
        set<IObserver *> l_observer_set;
        m_observer_map.insert(make_pair(event_id, l_observer_set));
    }

    m_observer_map[event_id].insert(observer);
}

void ObserverManager::unsubscribe(const uint &event_id, IObserver *observer)
{
    assert(NULL != observer);
    auto l_iter = m_observer_map.find(event_id);
    if(l_iter == m_observer_map.end())
    {
        return;
    }

    m_observer_map[event_id].erase(observer);
}

void ObserverManager::notify(const uint &event_id, void *param1, void *param2)
{
    map<uint, set<IObserver *> >::iterator l_iter = m_observer_map.find(event_id);
    if(l_iter == m_observer_map.end())
    {
        return;
    }

    set<IObserver *> &l_observer_set = l_iter->second;
    for(auto l_observer : l_observer_set)
    {
        l_observer->on_change(event_id, param1, param2);
    }
}