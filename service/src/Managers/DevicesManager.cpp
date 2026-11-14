#include "Managers/DevicesManager.h"

#include <iostream>
#include <ranges>
#include <linux/input.h>
#include <linux/uinput.h>

#include "TimeDefines.h"
#include "Command/Macro.h"
#include "Command/ShutdownApplication.h"
#include "Command/SwitchToSubProfile.h"
#include "Factory/VirtualDeviceFactory.h"
#include "Device/VirtualDeviceData.h"
#include "Device/Profile/KeyProfile.h"
#include "Device/Profile/RelativeProfile.h"

DevicesManager::~DevicesManager() noexcept
{
    RemoveVirtualDevices();
}

DevicesManager& DevicesManager::GetInstance()
{
    static DevicesManager _devicesManagerInstance;

    return _devicesManagerInstance;
}

void DevicesManager::Start()
{

#define SUB_PROFILES 2

    std::unique_ptr<KeyProfile> keyProfile {std::make_unique<KeyProfile>()};

    std::vector<std::unique_ptr<KeyInputCommands const>> buttonLeftInputCommands;Now I need to distinguish between REL_WHEEL with value -1 and REL_WHEEL with value 1
    buttonLeftInputCommands.reserve(SUB_PROFILES);

    std::vector<InputEvent> buttonLeftPressInputEvents;
    buttonLeftPressInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 1);
    buttonLeftPressInputEvents.emplace_back(EV_KEY, KEY_V, 1);
    buttonLeftPressInputEvents.emplace_back(EV_KEY, KEY_V, 0);
    buttonLeftPressInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 0);

    std::vector<InputEvent> buttonLeftHoldInputEvents;
    buttonLeftHoldInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 1);
    buttonLeftHoldInputEvents.emplace_back(EV_KEY, KEY_V, 1);
    buttonLeftHoldInputEvents.emplace_back(EV_KEY, KEY_V, 0);
    buttonLeftHoldInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 0);

    buttonLeftInputCommands.emplace_back(nullptr);

    buttonLeftInputCommands.emplace_back(std::make_unique<KeyInputCommands const>(
        KeyStateCommands{std::make_unique<Macro>(std::move(buttonLeftPressInputEvents)),
        std::make_unique<HoldCommand>(std::make_unique<Macro>(std::move(buttonLeftHoldInputEvents)), Duration(500), Duration(20)),
        nullptr}));

    std::vector<std::unique_ptr<KeyInputCommands const>> buttonRightInputCommands;
    buttonRightInputCommands.reserve(SUB_PROFILES);

    std::vector<InputEvent> buttonRightPressInputEvents;
    buttonRightPressInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 1);
    buttonRightPressInputEvents.emplace_back(EV_KEY, KEY_C, 1);
    buttonRightPressInputEvents.emplace_back(EV_KEY, KEY_C, 0);
    buttonRightPressInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 0);

    std::vector<InputEvent> buttonRightHoldInputEvents;
    buttonRightHoldInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 1);
    buttonRightHoldInputEvents.emplace_back(EV_KEY, KEY_C, 1);
    buttonRightHoldInputEvents.emplace_back(EV_KEY, KEY_C, 0);
    buttonRightHoldInputEvents.emplace_back(EV_KEY, KEY_LEFTCTRL, 0);

    buttonRightInputCommands.emplace_back(nullptr);

    buttonRightInputCommands.emplace_back(std::make_unique<KeyInputCommands const>(
        KeyStateCommands{std::make_unique<Macro>(std::move(buttonRightPressInputEvents)),
        std::make_unique<HoldCommand>(std::make_unique<Macro>(std::move(buttonRightHoldInputEvents)), Duration(500), Duration(20)),
        nullptr}));

    std::vector<std::unique_ptr<KeyInputCommands const>> buttonSideInputCommands;
    buttonSideInputCommands.reserve(SUB_PROFILES);

    buttonSideInputCommands.emplace_back(std::make_unique<KeyInputCommands const>(
        KeyStateCommands{std::make_unique<SwitchToSubProfile>(1),nullptr, nullptr}));

    buttonSideInputCommands.emplace_back(std::make_unique<KeyInputCommands const>(KeyStateCommands{
        nullptr, nullptr, std::make_unique<SwitchToSubProfile>(0)}));

    std::vector<std::unique_ptr<KeyInputCommands const>> buttonExtraInputCommands;
    buttonExtraInputCommands.reserve(SUB_PROFILES);

    buttonExtraInputCommands.emplace_back(std::make_unique<KeyInputCommands const>(
        KeyStateCommands{std::make_unique<ShutdownApplication>(), nullptr, nullptr}));

    buttonExtraInputCommands.emplace_back(nullptr);

    keyProfile->inputs.try_emplace(BTN_LEFT, std::move(buttonLeftInputCommands));
    keyProfile->inputs.try_emplace(BTN_RIGHT, std::move(buttonRightInputCommands));
    keyProfile->inputs.try_emplace(BTN_SIDE, std::move(buttonSideInputCommands));
    keyProfile->inputs.try_emplace(BTN_EXTRA, std::move(buttonExtraInputCommands));

    std::forward_list<Code> keySubProfile0Codes;
    keySubProfile0Codes.emplace_front(BTN_SIDE);
    keySubProfile0Codes.emplace_front(BTN_EXTRA);

    std::forward_list<Code> keySubProfile1Codes;
    keySubProfile1Codes.emplace_front(BTN_LEFT);
    keySubProfile1Codes.emplace_front(BTN_RIGHT);
    keySubProfile1Codes.emplace_front(BTN_SIDE);

    keyProfile->subProfilesCodes.emplace(0, std::move(keySubProfile0Codes));
    keyProfile->subProfilesCodes.emplace(1, std::move(keySubProfile1Codes));

    std::unique_ptr<RelativeProfile> relativeProfile {std::make_unique<RelativeProfile>()};

    std::vector<std::unique_ptr<RelativeInputCommand const>> wheelNegativeTiltInputCommands;
    wheelNegativeTiltInputCommands.reserve(SUB_PROFILES);

    std::vector<InputEvent> wheelNegativeTiltInputEvents;
    wheelNegativeTiltInputEvents.emplace_back(EV_KEY, KEY_LEFTALT, 1);
    wheelNegativeTiltInputEvents.emplace_back(EV_KEY, KEY_LEFT, 1);
    wheelNegativeTiltInputEvents.emplace_back(EV_KEY, KEY_LEFT, 0);
    wheelNegativeTiltInputEvents.emplace_back(EV_KEY, KEY_LEFTALT, 0);

    wheelNegativeTiltInputCommands.emplace_back(std::make_unique<RelativeInputCommand>(
        std::make_unique<Macro>(std::move(wheelNegativeTiltInputEvents))));

    wheelNegativeTiltInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<RelativeInputCommand const>> wheelPositiveTiltInputCommands;
    wheelPositiveTiltInputCommands.reserve(SUB_PROFILES);

    std::unique_ptr<RelativeInputStrategy> wheelNegativeTiltInputStrategy {std::make_unique<RelativeInputStrategy>(std::move(wheelNegativeTiltInputCommands))};

    std::vector<InputEvent> wheelPositiveTiltInputEvents;
    wheelPositiveTiltInputEvents.emplace_back(EV_KEY, KEY_LEFTALT, 1);
    wheelPositiveTiltInputEvents.emplace_back(EV_KEY, KEY_RIGHT, 1);
    wheelPositiveTiltInputEvents.emplace_back(EV_KEY, KEY_RIGHT, 0);
    wheelPositiveTiltInputEvents.emplace_back(EV_KEY, KEY_LEFTALT, 0);

    wheelPositiveTiltInputCommands.emplace_back(std::make_unique<RelativeInputCommand const>(
        std::make_unique<Macro>(std::move(wheelPositiveTiltInputEvents))));

    wheelPositiveTiltInputCommands.emplace_back(nullptr);

    std::unique_ptr<RelativeInputStrategy> wheelPositiveTiltInputStrategy {std::make_unique<RelativeInputStrategy>(std::move(wheelPositiveTiltInputCommands))};

    relativeProfile->inputs.try_emplace(REL_HWHEEL, std::move(wheelNegativeTiltInputStrategy), std::move(wheelPositiveTiltInputStrategy));

    std::forward_list<RelativeCode> relativeSubProfile0Codes;
    relativeSubProfile0Codes.emplace_front(REL_HWHEEL, true, true);

    relativeProfile->subProfilesCodes.emplace(0, std::move(relativeSubProfile0Codes));
    relativeProfile->subProfilesCodes.try_emplace(1);

    std::unordered_set<int> inputEvs;

    inputEvs.emplace(EV_SYN);
    inputEvs.emplace(EV_KEY);
    inputEvs.emplace(EV_REL);
    inputEvs.emplace(EV_SYN);

    std::unordered_set<int> inputEvKeys;

    inputEvKeys.emplace(KEY_LEFTCTRL);
    inputEvKeys.emplace(KEY_C);
    inputEvKeys.emplace(KEY_V);
    inputEvKeys.emplace(KEY_LEFTALT);
    inputEvKeys.emplace(KEY_LEFT);
    inputEvKeys.emplace(KEY_RIGHT);

    inputEvKeys.emplace(BTN_LEFT);
    inputEvKeys.emplace(BTN_RIGHT);
    inputEvKeys.emplace(BTN_MIDDLE);
    inputEvKeys.emplace(BTN_SIDE);
    inputEvKeys.emplace(BTN_EXTRA);

    std::unordered_set<int> inputEvRels;

    inputEvRels.emplace(REL_X);
    inputEvRels.emplace(REL_Y);
    inputEvRels.emplace(REL_HWHEEL);
    inputEvRels.emplace(REL_WHEEL);

    std::unordered_set<int> inputEvMsc;
    inputEvMsc.emplace(MSC_SCAN);

    uinput_setup usetup {};
    snprintf(usetup.name, UINPUT_MAX_NAME_SIZE, "Virtual Mouse");
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1b1c;
    usetup.id.product = 0x1b2d;

    std::unordered_map<unsigned long, std::unordered_set<int>> deviceCapableInputs;

    deviceCapableInputs.try_emplace(UI_SET_EVBIT, std::move(inputEvs));

    deviceCapableInputs.try_emplace(UI_SET_KEYBIT, std::move(inputEvKeys));

    deviceCapableInputs.try_emplace(UI_SET_RELBIT, std::move(inputEvRels));

    deviceCapableInputs.try_emplace(UI_SET_MSCBIT, std::move(inputEvMsc));

    CreateVirtualDeviceWrapper(10, VirtualDeviceData{std::move(deviceCapableInputs), usetup}, {"/dev/input/event2"});

    _devicesWrapper.at(10).GetVirtualDevice().SetKeyProfile(std::move(keyProfile));

    _devicesWrapper.at(10).GetVirtualDevice().SetRelativeProfile(std::move(relativeProfile));
}

void DevicesManager::Loop()
{
    while (_shouldKeepTriggering.load())
    {
        _triggerKeyHoldCommandEvent.Trigger();

        std::this_thread::sleep_for(Duration(THREAD_SLEEP_MILLIS));
    }
}

void DevicesManager::CreateVirtualDeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData,
    PlatformListenerData&& platformListenerData)
{
    _devicesWrapper.try_emplace(deviceId, deviceId, std::move(virtualDeviceData), std::move(platformListenerData));
    _deviceInputEventsStorage.try_emplace(deviceId);
    _devicesMutex.try_emplace(deviceId);
}

void DevicesManager::RegisterInputEvents(DeviceId deviceId, std::vector<InputEvent>&& inputEvents)
{
    PlatformVirtualDevice& virtualDevice {_devicesWrapper.at(deviceId).GetVirtualDevice()};

    std::vector<InputEvent> notRegisteredInputs;

    for (const auto& inputEvent : inputEvents)
    {
        if (virtualDevice.HasInputRegistered(inputEvent))
        {
            Emit(deviceId, std::move(notRegisteredInputs));
            notRegisteredInputs.clear();

            AppendInputEventToDevice(deviceId, {inputEvent});
            continue;
        }

        notRegisteredInputs.push_back(inputEvent);
    }

    Emit(deviceId, std::move(notRegisteredInputs));
}

void DevicesManager::AppendInputEventToDevice(DeviceId deviceId, InputEvent inputEvent)
{
    std::mutex& deviceMutex {_devicesMutex.at(deviceId)};

    deviceMutex.lock();
    _deviceInputEventsStorage.at(deviceId).push(inputEvent);
    deviceMutex.unlock();

    _onDeviceRegisterInput.at(deviceId).Trigger();
}

InputEvent DevicesManager::GetDeviceInputEvent(DeviceId deviceId)
{
    std::mutex& deviceMutex {_devicesMutex.at(deviceId)};

    deviceMutex.lock();
    const InputEvent& inputEvent {_deviceInputEventsStorage.at(deviceId).front()};

    _deviceInputEventsStorage.at(deviceId).pop();
    deviceMutex.unlock();

    return inputEvent;
}

void DevicesManager::ExecuteInputEvent(DeviceId deviceId, const InputEvent& inputEvent)
{
    _devicesWrapper.at(deviceId).GetVirtualDevice().ExecuteInput(deviceId, inputEvent);
}

void DevicesManager::Emit(DeviceId deviceId, std::vector<InputEvent>&& inputEvents)
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

std::weak_ptr<std::function<void()>> DevicesManager::SubscribeToDeviceRegisterInput(DeviceId deviceId, std::function<void()>&& action)
{
    auto [it, inserted] = _onDeviceRegisterInput.try_emplace(deviceId);
    return it->second.Subscribe(std::move(action));
}

void DevicesManager::UnsubscribeToDeviceRegisterInput(DeviceId deviceId)
{
    _onDeviceRegisterInput.at(deviceId).UnsubscribeAll();
    _onDeviceRegisterInput.erase(deviceId);
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

void DevicesManager::StopTriggering()
{
    _shouldKeepTriggering.store(false);
}

void DevicesManager::RemoveVirtualDevice(DeviceId deviceId)
{
    _devicesWrapper.erase(deviceId);
}

void DevicesManager::RemoveVirtualDevices()
{
    for (const auto& deviceId : _devicesWrapper | std::views::keys)
    {
        _devicesWrapper.erase(deviceId);

        std::mutex& deviceMutex {_devicesMutex.at(deviceId)};

        deviceMutex.lock();
        _deviceInputEventsStorage.erase(deviceId);
        deviceMutex.unlock();
    }
}