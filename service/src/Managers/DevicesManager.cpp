#include "Managers/DevicesManager.h"

#include <iostream>
#include <linux/input.h>
#include <linux/uinput.h>

#include "Factory/VirtualDeviceFactory.h"
#include "Managers/ThreadsManager.h"
#include "Device/VirtualDeviceData.h"

DevicesManager::DevicesManager()
{
    ThreadsManager::GetInstance().SetDevicesHoldAction([&]()
    {
        TriggerHoldCommands();
    });

    std::unordered_map<unsigned long, std::unordered_set<int>> capableInputs;

    std::unordered_set<int> inputEvs;

    inputEvs.emplace(0);
    inputEvs.emplace(1);
    inputEvs.emplace(2);
    inputEvs.emplace(4);

    capableInputs.try_emplace(UI_SET_EVBIT, std::move(inputEvs));

    std::unordered_set<int> inputEvKeys;

    inputEvKeys.emplace(272);
    inputEvKeys.emplace(273);
    inputEvKeys.emplace(275);
    inputEvKeys.emplace(276);

    capableInputs.try_emplace(UI_SET_KEYBIT, std::move(inputEvKeys));

    std::unordered_set<int> inputEvRels;

    inputEvRels.emplace(0);
    inputEvRels.emplace(1);
    inputEvRels.emplace(6);
    inputEvRels.emplace(11);
    inputEvRels.emplace(12);

    capableInputs.try_emplace(UI_SET_RELBIT, std::move(inputEvRels));

    std::unordered_set<int> inputEvMsc;
    inputEvMsc.emplace(4);

    capableInputs.try_emplace(UI_SET_MSCBIT, std::move(inputEvMsc));

    struct uinput_setup usetup {};
    snprintf(usetup.name, UINPUT_MAX_NAME_SIZE, "Virtual Razer Mouse");
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor  = 0x1532;
    usetup.id.product = 0x0099;

    const DeviceId deviceId {10};

    CreateVirtualDeviceWrapper(deviceId, VirtualDeviceData{InputType{InputType::KEY & InputType::RELATIVE}, std::move(capableInputs),
        DeviceData{usetup.id.bustype, usetup.id.vendor, usetup.id.product, usetup.id.version}}, {});
}

DevicesManager::~DevicesManager() noexcept
{
    RemoveVirtualDevices();
}

DevicesManager& DevicesManager::GetInstance()
{
    static DevicesManager _devicesManagerInstance;

    return _devicesManagerInstance;
}

void DevicesManager::CreateVirtualDeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData,
    PlatformListenerData&& platformListenerData)
{
    _devicesWrapper.try_emplace(deviceId, deviceId, std::move(virtualDeviceData), std::move(platformListenerData));
}

void DevicesManager::RegisterInputEvents(DeviceId deviceId, std::vector<InputEvent>&& inputEvents)
{
    PlatformVirtualDevice& virtualDevice {_devicesWrapper.at(deviceId).GetVirtualDevice()};

    std::vector<InputEvent> notRegisteredInputs;
    notRegisteredInputs.reserve(inputEvents.size());

    for (const auto& inputEvent : inputEvents)
    {
        if (virtualDevice.HasInputRegistered(inputEvent))
        {
            Emit(deviceId, notRegisteredInputs);
            notRegisteredInputs.clear();

            virtualDevice.ExecuteInput(deviceId, inputEvent);
            continue;
        }

        notRegisteredInputs.push_back(inputEvent);
    }

    Emit(deviceId, notRegisteredInputs);
}

void DevicesManager::Emit(DeviceId deviceId, const std::vector<InputEvent>& inputEvents)
{
    PlatformVirtualDevice& virtualDevice {_devicesWrapper.at(deviceId).GetVirtualDevice()};

    for (const auto& inputEvent : inputEvents)
    {
        virtualDevice.Emit(inputEvent);
    }

    virtualDevice.Synchronize();
}

void DevicesManager::ChangeDeviceCurrentSubProfile(DeviceId deviceId, uint8_t subProfileIndex)
{
    _devicesWrapper.at(deviceId).GetVirtualDevice().ChangeCurrentSubProfile(subProfileIndex);
}

std::weak_ptr<std::function<void()>> DevicesManager::SubscribeToTriggerKeyHoldCommand(std::function<void()>&& action)
{
    return _triggerKeyHoldCommandEvent.Subscribe(std::move(action));
}

void DevicesManager::UnsubscribeToTriggerKeyHoldCommand(std::weak_ptr<std::function<void()>>&& action)
{
    _triggerKeyHoldCommandEvent.Unsubscribe(std::move(action));
}

void DevicesManager::TriggerHoldCommands()
{
    _triggerKeyHoldCommandEvent.Trigger();
}

void DevicesManager::RemoveVirtualDevice(DeviceId deviceId)
{
    _devicesWrapper.at(deviceId).Destroy();
    _devicesWrapper.erase(deviceId);
}

void DevicesManager::RemoveVirtualDevices()
{
    for (auto& [deviceId, deviceWrapper] : _devicesWrapper)
    {
        deviceWrapper.Destroy();
        _devicesWrapper.erase(deviceId);
    }
}