#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "DeviceUsings.h"
#include "Device/DeviceData.h"
#include "Device/DeviceWrapper.h"
#include "Input/InputEvent.h"
#include "Trigger/TriggerBus.h"
#include "Utilities/Usings/PlatformUsings.h"

class VirtualDeviceData;

class DevicesManager
{
public:

    ~DevicesManager() noexcept;

    DevicesManager(const DevicesManager& other) = delete;
    DevicesManager& operator=(const DevicesManager& other) = delete;

    static DevicesManager& GetInstance();

    void CreateVirtualDeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData, PlatformListenerData&& platformListenerData);

    void RegisterInputEvents(DeviceId deviceId, std::vector<InputEvent>&& inputEvents);

    void Emit(DeviceId deviceId, const std::vector<InputEvent>& inputEvents);

    void ChangeDeviceCurrentSubProfile(DeviceId deviceId, uint8_t subProfileIndex);

    std::weak_ptr<std::function<void()>> SubscribeToTriggerKeyHoldCommand(std::function<void()>&& action);

    void UnsubscribeToTriggerKeyHoldCommand(std::weak_ptr<std::function<void()>>&& action);

private:

    DevicesManager();

    void TriggerHoldCommands();

    void RemoveVirtualDevice(DeviceId deviceId);

    void RemoveVirtualDevices();

    std::unordered_map<DeviceId, DeviceWrapper> _devicesWrapper;

    TriggerBus _triggerKeyHoldCommandEvent;
};