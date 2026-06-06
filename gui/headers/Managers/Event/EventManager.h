#pragma once

#include "Observer/ObserverMap.h"
#include "Observer/ObserverSingleValue.h"
#include "EventType.h"
#include "Utilities/Structs/DeviceInfo.h"

class EventManager
{
public:

    ~EventManager() = default;

    EventManager(const EventManager& other) = delete;
    EventManager& operator=(const EventManager& other) = delete;
    EventManager(EventManager&& other) = delete;
    EventManager& operator=(EventManager&& other) = delete;

    std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>> Subscribe(std::function<void(std::vector<DeviceInfo>)>&& action);
    void Unsubscribe(std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>>&& action);

    void UpdateDevices(std::vector<DeviceInfo>&& value);

private:

    EventManager();

    static EventManager& GetInstance();

    static std::unique_ptr<EventManager> _eventManagerInstance;

    ObserverSingleValue<std::vector<DeviceInfo>> _devices;
};
