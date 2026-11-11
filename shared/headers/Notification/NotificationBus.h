#pragma once

#include <functional>
#include <vector>
#include <memory>

template<typename T>
class NotificationBus
{
    using TEvent = std::function<void()>;

    using TEventVector = std::vector<std::shared_ptr<TEvent>>;
    using TEventVectorIterator = typename TEventVector::iterator;
    using TEventVectorConstIterator = typename TEventVector::const_iterator;

    using TEventMap = std::unordered_map<T, TEventVector>;
    using TEventMapIterator = typename TEventMap::iterator;
    using TEventMapConstIterator = typename TEventMap::const_iterator;

public:

    NotificationBus() = default;
    NotificationBus(TEventMap notifications);
    ~NotificationBus() noexcept;

    void AddEntry(T notification);
    void RemoveEntry(T notification);

    void TriggerNotification(T notification);

    std::weak_ptr<TEvent> Subscribe(T notification, TEvent&& action);
    void Unsubscribe(T notification, std::weak_ptr<TEvent>&& weakAction);
    void UnsubscribeAllNotification(T notification);
    void UnsubscribeAll();

private:

    TEventMap _notifications;

};

template <typename T>
NotificationBus<T>::NotificationBus(TEventMap notifications) : _notifications(notifications)
{}

template <typename T>
NotificationBus<T>::~NotificationBus() noexcept
{
    UnsubscribeAll();
}

template <typename T>
void NotificationBus<T>::AddEntry(T notification)
{
    _notifications.emplace(notification, TEventVector{});
}

template <typename T>
void NotificationBus<T>::RemoveEntry(T notification)
{
    _notifications.erase(notification);
}

template <typename T>
void NotificationBus<T>::TriggerNotification(T notification)
{
    TEventVectorConstIterator itEnd {_notifications.at(notification).cend()};

    for (TEventVectorIterator it {_notifications.at(notification).begin()}; it != itEnd; ++it)
    {
        (**it)();
    }
}

template <typename T>
std::weak_ptr<typename NotificationBus<T>::TEvent> NotificationBus<T>::Subscribe(T notification, TEvent&& action)
{
    std::shared_ptr<TEvent> sharedAction {std::make_shared<TEvent>(action)};
    _notifications.at(notification).push_back(sharedAction);
    return sharedAction;
}

template <typename T>
void NotificationBus<T>::Unsubscribe(T notification, std::weak_ptr<TEvent>&& weakAction)
{
    if (const auto action {weakAction.lock()})
    {
        TEventMapConstIterator itMapEnd {_notifications.cend()};

        for (TEventMapIterator itMap {_notifications.begin()}; itMap != itMapEnd; ++itMap)
        {
            if (itMap->first != notification)
            {
                continue;
            }

            TEventVectorConstIterator itValueEnd {itMap->second.cend()};

            for (TEventVectorIterator itValue {itMap->second.begin()}; itValue != itValueEnd; ++itValue)
            {
                if (*itValue != action)
                {
                    continue;
                }

                _notifications.at(itMap->first).erase(itValue);
                return;
            }
        }
    }
}

template <typename T>
void NotificationBus<T>::UnsubscribeAllNotification(T notification)
{
    _notifications.at(notification).clear();
}

template <typename T>
void NotificationBus<T>::UnsubscribeAll()
{
    TEventMapConstIterator itMapEnd {_notifications.cend()};

    for (TEventMapIterator itMap {_notifications.begin()}; itMap != itMapEnd; ++itMap)
    {
        UnsubscribeAllNotification(itMap->first);
    }
}
