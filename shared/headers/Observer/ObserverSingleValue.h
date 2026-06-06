#pragma once
#include "Observer/IObserver.h"

#include <functional>
#include <list>
#include <memory>

template<typename T>
class ObserverSingleValue : public IObserver
{

	using TEventHandler = std::function<void(T)>;
	using TEventList = std::list<std::shared_ptr<TEventHandler>>;
	using TEventListIterator = typename TEventList::iterator;
	using TEventListConstIterator = typename TEventList::const_iterator;

	using TAction = std::function<T(T)>;

public:

	ObserverSingleValue();
	ObserverSingleValue(T data);
	ObserverSingleValue(TAction action);
	ObserverSingleValue(T data, TAction action);

	~ObserverSingleValue() override;

	void SetAction(TAction action);

	T GetValue() const;
	void SetValue(T data);

	std::weak_ptr<TEventHandler> Subscribe(TEventHandler action);
	void Unsubscribe(const std::weak_ptr<TEventHandler>& weakAction);
	void UnsubscribeAll() override;

private:

	T _data;
	TEventList _events;
	TAction _action;
};

template<typename T>
ObserverSingleValue<T>::ObserverSingleValue() : _action([](T data){return data;})
{}

template<typename T>
ObserverSingleValue<T>::ObserverSingleValue(T data) : _data(data), _action([](T data){return data;})
{}

template <typename T>
ObserverSingleValue<T>::ObserverSingleValue(TAction action) : _data({}), _action(action)
{}

template<typename T>
ObserverSingleValue<T>::ObserverSingleValue(T data, TAction action) : _data(data), _action(action)
{}

template <typename T>
ObserverSingleValue<T>::~ObserverSingleValue()
{
	ObserverSingleValue<T>::UnsubscribeAll();
}

template <typename T>
void ObserverSingleValue<T>::SetAction(TAction action)
{
	_action = action;
}

template <typename T>
T ObserverSingleValue<T>::GetValue() const
{
	return _data;
}

template <typename T>
void ObserverSingleValue<T>::SetValue(T data)
{
	T previousData {_data};
	_data = _action(data);

	if (previousData == _data)
	{
		return;
	}

	TEventListConstIterator itEnd{_events.cend()};

	for (TEventListIterator it{_events.begin()}; it != itEnd; ++it)
	{
		(**it)(_data);
	}
}

template <typename T>
std::weak_ptr<typename ObserverSingleValue<T>::TEventHandler> ObserverSingleValue<T>::Subscribe(TEventHandler action)
{
	std::shared_ptr<TEventHandler> sharedAction {std::make_shared<TEventHandler>(action)};
	_events.push_back(sharedAction);
	return sharedAction;
}

template <typename T>
void ObserverSingleValue<T>::Unsubscribe(const std::weak_ptr<TEventHandler>& weakAction)
{
	if (const auto action {weakAction.lock()})
	{
		TEventListConstIterator itEnd {_events.cend()};

		for (TEventListIterator it {_events.begin()}; it != itEnd; ++it)
		{
			if (*it != action)
			{
				continue;
			}
			_events.erase(it);
			return;
		}
	}
}

template <typename T>
void ObserverSingleValue<T>::UnsubscribeAll()
{
	_events.clear();
}