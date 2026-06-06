#pragma once
#include "IEventBus.h"

#include <functional>
#include <vector>
#include <memory>

template<typename T>
class SingleEventBus : public IEventBus
{
    using TEventHandler = std::function<void(T)>;
    using TEventList = std::vector<std::shared_ptr<TEventHandler>>;
    using TEventListIterator = typename TEventList::iterator;
    using TEventListConstIterator = typename TEventList::const_iterator;

    using TAction = std::function<T(T)>;

public:

    SingleEventBus();
    SingleEventBus(TAction action);

    ~SingleEventBus() override;

    void SetAction(TAction action);

    void SetValue(T data);

    std::weak_ptr<TEventHandler> Subscribe(TEventHandler action);
    void Unsubscribe(const std::weak_ptr<TEventHandler>& weakAction);
    void UnsubscribeAll() override;

private:

    TEventList _events;
    TAction _action;
};

template <typename T>
SingleEventBus<T>::SingleEventBus() : _action([](T data){return data;})
{}

template <typename T>
SingleEventBus<T>::SingleEventBus(TAction action) : _action(action)
{}

template <typename T>
SingleEventBus<T>::~SingleEventBus()
{
    SingleEventBus<T>::UnsubscribeAll();
}

template <typename T>
void SingleEventBus<T>::SetAction(TAction action)
{
    _action = action;
}

template <typename T>
void SingleEventBus<T>::SetValue(T data)
{
    T value {_action(data)};

    TEventListConstIterator itEnd{_events.cend()};

    for (TEventListIterator it{_events.begin()}; it != itEnd; ++it)
    {
        (**it)(value);
    }
}

template <typename T>
std::weak_ptr<typename SingleEventBus<T>::TEventHandler> SingleEventBus<T>::Subscribe(TEventHandler action)
{
    std::shared_ptr<TEventHandler> sharedAction {std::make_shared<TEventHandler>(action)};
    _events.push_back(sharedAction);
    return sharedAction;
}

template <typename T>
void SingleEventBus<T>::Unsubscribe(const std::weak_ptr<TEventHandler>& weakAction)
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
void SingleEventBus<T>::UnsubscribeAll()
{
    _events.clear();
}