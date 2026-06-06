#pragma once
#include "IEventBus.h"

#include <functional>
#include <vector>
#include <memory>

template<typename TKey, typename TValue>
class MapEventBus : public IEventBus
{
    using TEvent = std::function<void(TValue)>;

    using TEventList = std::vector<std::shared_ptr<TEvent>>;
    using TEventListIterator = typename TEventList::iterator;
    using TEventListConstIterator = typename TEventList::const_iterator;

    using TEventMap = std::unordered_map<TKey, TEventList>;
    using TEventMapIterator = typename TEventMap::iterator;
    using TEventMapConstIterator = typename TEventMap::const_iterator;

    using TAction = std::function<TValue(TValue)>;

    using TActionMap = std::unordered_map<TKey, TAction>;
    using TActionMapIterator = typename TActionMap::iterator;
    using TActionMapConstIterator = typename TActionMap::const_iterator;

public:

    MapEventBus() = default;
    MapEventBus(TActionMap actions);
    ~MapEventBus() noexcept override;

    void AddEntry(TKey key, TAction&& action);
    void RemoveAction(TKey key);
    void SetAction(TKey key, TAction&& action);

	void SetValue(TKey key, TValue data);

    std::weak_ptr<TEvent> Subscribe(TKey key, TEvent&& action);
    void Unsubscribe(TKey key, std::weak_ptr<TEvent>&& weakAction);
    void UnsubscribeAllKey(TKey key);
    void UnsubscribeAll() override;

private:

    TEventMap _events;
    TActionMap _actions;

};

template <typename TKey, typename TValue>
MapEventBus<TKey, TValue>::MapEventBus(TActionMap actions)
{
    TActionMapConstIterator itMapEnd {actions.cend()};

    for (TActionMapIterator itMap {actions.begin()}; itMap != itMapEnd; ++itMap)
    {
        AddEntry(itMap->first, itMap->second);
    }
}

template <typename TKey, typename TValue>
MapEventBus<TKey, TValue>::~MapEventBus() noexcept
{
    MapEventBus<TKey, TValue>::UnsubscribeAll();
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::AddEntry(TKey key, TAction&& action)
{
    _actions.try_emplace(key, action);
    _events.try_emplace(key, TEventList{});
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::RemoveAction(TKey key)
{
    UnsubscribeAllKey(key);
    _actions.erase(key);
    _events.erase(key);
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::SetAction(TKey key, TAction&& action)
{
    _actions.at(key) = action;
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::SetValue(TKey key, TValue data)
{
    TValue value {_actions.at(key)(data)};

    TEventListConstIterator itEnd {_events.at(key).cend()};

    for (TEventListIterator it {_events.at(key).begin()}; it != itEnd; ++it)
    {
        (**it)(value);
    }
}

template <typename TKey, typename TValue>
std::weak_ptr<typename MapEventBus<TKey, TValue>::TEvent> MapEventBus<TKey, TValue>::Subscribe(TKey key,
    TEvent&& action)
{
    std::shared_ptr<TEvent> sharedAction {std::make_shared<TEvent>(action)};
    _events.at(key).push_back(sharedAction);
    return sharedAction;
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::Unsubscribe(TKey key, std::weak_ptr<TEvent>&& weakAction)
{
    if (const auto action {weakAction.lock()})
    {
        TEventMapConstIterator itMapEnd {_events.cend()};

        for (TEventMapIterator itMap {_events.begin()}; itMap != itMapEnd; ++itMap)
        {
            if (itMap->first != key)
            {
                continue;
            }

            TEventListConstIterator itValueEnd {itMap->second.cend()};

            for (TEventListIterator itValue {itMap->second.begin()}; itValue != itValueEnd; ++itValue)
            {
                if (*itValue != action)
                {
                    continue;
                }

                _events.at(itMap->first).erase(itValue);
                return;
            }
            return;
        }
    }
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::UnsubscribeAllKey(TKey key)
{
    _events.at(key).clear();
}

template <typename TKey, typename TValue>
void MapEventBus<TKey, TValue>::UnsubscribeAll()
{
    TEventMapConstIterator itMapEnd {_events.cend()};

    for (TEventMapIterator itMap {_events.begin()}; itMap != itMapEnd; ++itMap)
    {
        UnsubscribeAllKey(itMap->first);
    }
}
