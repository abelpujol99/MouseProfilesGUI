#pragma once
#include <IObserver.h>

#include <functional>
#include <list>
#include <memory>

template<typename TKey, typename TValue>
class ObserverMap : public IObserver
{

	using TEvent = std::function<void(TValue)>;

	using TEventList = std::list<std::shared_ptr<TEvent>>;
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

	ObserverMap() = default;
	ObserverMap(TActionMap actions);
	~ObserverMap() override;

	void AddAction(TKey key, TAction action);
	void RemoveAction(TKey key);
	void SetAction(TKey key, TAction action);

	TValue GetValue(TKey key) const;
	void SetValue(TKey key, TValue data);

	std::weak_ptr<TEvent> Subscribe(TKey key, TEvent action);
	void Unsubscribe(TKey key, std::weak_ptr<TEvent> weakAction);
	void UnsubscribeAllKey(TKey key);
	void UnsubscribeAll() override;


private:

	std::unordered_map<TKey, TValue> _data;
	TEventMap _events;
	TActionMap _actions;

};

template <typename TKey, typename TValue>
ObserverMap<TKey, TValue>::ObserverMap(TActionMap actions)
{
	TActionMapConstIterator itMapEnd {actions.cend()};

	for (TActionMapIterator itMap {actions.begin()}; itMap != itMapEnd; ++itMap)
	{
		AddAction(itMap->first, itMap->second);
	}
}

template <typename TKey, typename TValue>
ObserverMap<TKey, TValue>::~ObserverMap()
{
	ObserverMap<TKey, TValue>::UnsubscribeAll();
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::AddAction(TKey key, TAction action)
{
	_data.try_emplace(key, TValue{});
	_actions.try_emplace(key, action);
	_events.try_emplace(key, TEventList{});
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::RemoveAction(TKey key)
{
	UnsubscribeAllKey(key);
	_actions.erase(key);
	_data.erase(key);
	_events.erase(key);
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::SetAction(TKey key, TAction action)
{
	_actions.at(key) = action;
}

template <typename TKey, typename TValue>
TValue ObserverMap<TKey, TValue>::GetValue(TKey key) const
{
	return _data.at(key);
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::SetValue(TKey key, TValue data)
{
	_data.at(key) = _actions.at(key)(data);

	TEventListConstIterator itEnd {_events.at(key).cend()};

	for (TEventListIterator it {_events.at(key).begin()}; it != itEnd; ++it)
	{
		(**it)(_data.at(key));
	}
}

template <typename TKey, typename TValue>
std::weak_ptr<typename ObserverMap<TKey, TValue>::TEvent> ObserverMap<TKey, TValue>::Subscribe(TKey key, TEvent action)
{
	std::shared_ptr<TEvent> sharedAction {std::make_shared<TEvent>(action)};
	_events.at(key).push_back(sharedAction);
	return sharedAction;
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::Unsubscribe(TKey key, std::weak_ptr<TEvent> weakAction)
{
	if (const auto action {weakAction.lock()})
	{
		TEventMapConstIterator itMapEnd {_events.cend()};

		for (TEventMapIterator itMap {_events.begin()}; itMap != itMapEnd; ++itMap)
		{
			if (*itMap->first != key)
			{
				continue;
			}

			TEventListConstIterator itValueEnd {*itMap->second.cend()};

			for (TEventListIterator itValue {*itMap->second}; itValue != itValueEnd; ++itValue)
			{
				if (*itValue != action)
				{
					continue;
				}

				_events.at(*itMap->first).erase(action);
				return;
			}
			return;
		}
	}
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::UnsubscribeAllKey(TKey key)
{
	_events.at(key).clear();
}

template <typename TKey, typename TValue>
void ObserverMap<TKey, TValue>::UnsubscribeAll()
{
	TEventMapConstIterator itMapEnd {_events.cend()};

	for (TEventMapIterator itMap {_events.begin()}; itMap != itMapEnd; ++itMap)
	{
		UnsubscribeAllKey(itMap->first);
	}
}