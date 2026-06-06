#include "Managers/Event/EventManager.h"

#include "Managers/Event/EventType.h"

std::unique_ptr<EventManager> EventManager::_eventManagerInstance {nullptr};

EventManager::EventManager()
{
    EventType eventTypeCount {EventType::COUNT};

    for (EventType i{}; i != eventTypeCount; ++i)
    {
        //_serviceStatus.AddEntry(i, [](bool value){return value;});
    }
}

EventManager& EventManager::GetInstance()
{
    if (_eventManagerInstance == nullptr)
    {
        _eventManagerInstance.reset(new EventManager());
    }

    return *_eventManagerInstance;
}

std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>> EventManager::Subscribe(std::function<void(std::vector<DeviceInfo>)>&& action)
{
    return _devices.Subscribe(std::move(action));
}

void EventManager::Unsubscribe(std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>>&& action)
{
    _devices.Unsubscribe(std::move(action));
}

void EventManager::UpdateDevices(std::vector<DeviceInfo>&& value)
{
    _devices.SetValue(std::move(value));
}

