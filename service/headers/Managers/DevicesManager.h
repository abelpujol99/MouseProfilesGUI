#pragma once

#include <list>
#include <memory>
#include <queue>
#include <unordered_map>

#include "DeviceUsings.h"
#include "Device/DeviceData.h"
#include "Device/DeviceWrapper.h"
#include "Input/InputEvent.h"
#include "Notification/NotificationBus.h"
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

    void Loop();

    void CreateVirtualDeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData, PlatformListenerData&& platformListenerData);

    void RegisterInputEvents(DeviceId deviceId, std::vector<InputEvent>&& inputEvents);

    void AppendInputEventToDevice(DeviceId deviceId, InputEvent inputEvent);

    InputEvent GetDeviceInputEvent(DeviceId deviceId);

    void ExecuteInputEvent(DeviceId deviceId, const InputEvent& inputEvent);

    void Emit(DeviceId deviceId, std::vector<InputEvent>&& inputEvents);

    void ChangeDeviceCurrentSubProfile(DeviceId deviceId, uint8_t subProfileIndex);

    std::weak_ptr<std::function<void()>> SubscribeToDeviceRegisterInput(DeviceId deviceId, std::function<void()>&& action);

    void UnsubscribeToDeviceRegisterInput(DeviceId deviceId);

    std::weak_ptr<std::function<void()>> SubscribeToTriggerKeyHoldCommand(std::function<void()>&& action);

    void UnsubscribeToTriggerKeyHoldCommand(std::weak_ptr<std::function<void()>>&& action);

    void StopTriggering();

private:

    DevicesManager();

    void TriggerHoldCommands();

    void RemoveVirtualDevice(DeviceId deviceId);

    void RemoveVirtualDevices();

    std::unordered_map<DeviceId, DeviceWrapper> _devicesWrapper;

    std::unordered_map<DeviceId, std::queue<InputEvent>> _deviceInputEventsStorage;

    std::unordered_map<DeviceId, TriggerBus> _onDeviceRegisterInput;

    TriggerBus _triggerKeyHoldCommandEvent;

    std::atomic<bool> _shouldKeepTriggering {true};
};