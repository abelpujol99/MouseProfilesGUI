#include "../../../headers/Device/VirtualDevice/LinuxVirtualDevice.h"

#include <iostream>
#include <unistd.h>
#include <linux/uinput.h>

#include "Input/Relative/RelativeInput.h"
#include "Managers/DevicesManager.h"

LinuxVirtualDevice::LinuxVirtualDevice(InputType inputType, int file) : BaseVirtualDevice(inputType), _writeFile(file)
{}

LinuxVirtualDevice::~LinuxVirtualDevice()
{
    LinuxVirtualDevice::Destroy();
}

void LinuxVirtualDevice::CreateProfile()
{

#define SUB_PROFILES 2

    /*std::unordered_map<Code, std::unique_ptr<IInputCommandStrategy>> profile;

    std::vector<std::unique_ptr<KeyInputCommand>> buttonLeftInputCommands;
    buttonLeftInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonLeftPressEmits;
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 1}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 0}));
    buttonLeftPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonLeftHoldEmits;
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 1}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_V, 0}));
    buttonLeftHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonLeftInputCommands.emplace_back(nullptr);

    buttonLeftInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonLeftPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonLeftHoldEmits)),
                nullptr, Duration(500), Duration(20)));

    std::vector<std::unique_ptr<KeyInputCommand>> buttonRightInputCommands;
    buttonRightInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonRightPressEmits;
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 1}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 0}));
    buttonRightPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonRightHoldEmits;
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 1}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_C, 0}));
    buttonRightHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonRightInputCommands.emplace_back(nullptr);

    buttonRightInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonRightPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonRightHoldEmits)),
                nullptr, Duration(500), Duration(20)));

    std::vector<std::unique_ptr<KeyInputCommand>> buttonBackInputCommands;
    buttonBackInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonBackPressEmits;
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));
    buttonBackPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    std::vector<EmitData> buttonBackHoldEmits;
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));
    buttonBackHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonBackInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonBackPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonBackHoldEmits)),
            nullptr, Duration(500), Duration(20)));

    buttonBackInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<KeyInputCommand>> buttonForwardInputCommands;
    buttonForwardInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonForwardPressEmits;
    buttonForwardPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 1}));
    buttonForwardPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 1}));

    std::vector<EmitData> buttonForwardHoldEmits;
    buttonForwardHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 2}));

    std::vector<EmitData> buttonForwardReleaseEmits;
    buttonForwardReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_W, 0}));
    buttonForwardReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTCTRL, 0}));

    buttonForwardInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardHoldEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonForwardReleaseEmits)), Duration(500), Duration(20)));

    buttonForwardInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<KeyInputCommand>> buttonSideInputCommands;
    buttonSideInputCommands.reserve(SUB_PROFILES);

    buttonSideInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateSwitchToProfileCommand(1), nullptr, nullptr, Duration(500), Duration(20)));

    buttonSideInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        nullptr, nullptr, CommandFactory::CreateSwitchToMainProfileCommand(), Duration(500), Duration(20)));

    std::vector<std::unique_ptr<KeyInputCommand>> buttonExtraInputCommands;
    buttonExtraInputCommands.reserve(SUB_PROFILES);

    buttonExtraInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateShutdownApplicationCommand(), nullptr, nullptr, Duration(500), Duration(20)));

    buttonExtraInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<KeyInputCommand>> buttonTaskInputCommands;
    buttonTaskInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> buttonTaskPressEmits;
    buttonTaskPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 1}));
    buttonTaskPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_R, 0}));

    std::vector<EmitData> buttonTaskHoldEmits;
    buttonTaskHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_K, 1}));
    buttonTaskHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_K, 0}));

    std::vector<EmitData> buttonTaskReleaseEmits;
    buttonTaskReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_L, 1}));
    buttonTaskReleaseEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_L, 0}));

    buttonTaskInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskPressEmits)), CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskHoldEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(buttonTaskReleaseEmits)), Duration(500), Duration(1000)));

    buttonTaskInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<KeyInputCommand>> buttonHiddenInputCommands;
    buttonHiddenInputCommands.reserve(SUB_PROFILES);

    buttonHiddenInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateShutdownApplicationCommand(), nullptr, nullptr, Duration(500), Duration(20)));

    buttonHiddenInputCommands.emplace_back(nullptr);

    profile.try_emplace(80, std::make_unique<KeyInputStrategy>(std::move(buttonHiddenInputCommands)));
    profile.try_emplace(81, std::make_unique<KeyInputStrategy>(std::move(buttonTaskInputCommands)));
    profile.try_emplace(82, std::make_unique<KeyInputStrategy>(std::move(buttonBackInputCommands)));
    profile.try_emplace(84, std::make_unique<KeyInputStrategy>(std::move(buttonForwardInputCommands)));
    profile.try_emplace(272, std::make_unique<KeyInputStrategy>(std::move(buttonLeftInputCommands)));
    profile.try_emplace(273, std::make_unique<KeyInputStrategy>(std::move(buttonRightInputCommands)));
    profile.try_emplace(275, std::make_unique<KeyInputStrategy>(std::move(buttonSideInputCommands)));
    profile.try_emplace(276, std::make_unique<KeyInputStrategy>(std::move(buttonExtraInputCommands)));

    std::vector<std::unique_ptr<KeyInputCommand>> wheelNegativeTiltInputCommands;
    buttonHiddenInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> wheelNegativeTiltPressEmits;
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 1}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 0}));
    wheelNegativeTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    std::vector<EmitData> wheelNegativeTiltHoldEmits;
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 1}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFT, 0}));
    wheelNegativeTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    wheelNegativeTiltInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(wheelNegativeTiltPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(wheelNegativeTiltHoldEmits)),
                nullptr, Duration(500), Duration(100)));

    wheelNegativeTiltInputCommands.emplace_back(nullptr);

    std::vector<std::unique_ptr<KeyInputCommand>> wheelPositiveTiltInputCommands;
    wheelPositiveTiltInputCommands.reserve(SUB_PROFILES);

    std::vector<EmitData> wheelPositiveTiltPressEmits;
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 1}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 0}));
    wheelPositiveTiltPressEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    std::vector<EmitData> wheelPositiveTiltHoldEmits;
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 1}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 1}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_RIGHT, 0}));
    wheelPositiveTiltHoldEmits.emplace_back(EmitData(KEYBOARD, {EV_KEY, KEY_LEFTALT, 0}));

    wheelPositiveTiltInputCommands.emplace_back(CommandFactory::CreateButtonInputCommand(
        CommandFactory::CreateEmitInputEventCommand(std::move(wheelPositiveTiltPressEmits)),
            CommandFactory::CreateEmitInputEventCommand(std::move(wheelPositiveTiltHoldEmits)),
                nullptr, Duration(500), Duration(100)));

    wheelPositiveTiltInputCommands.emplace_back(nullptr);

    profile.try_emplace(32, std::make_unique<KeyInputStrategy>(std::move(wheelNegativeTiltInputCommands)));
    profile.try_emplace(64, std::make_unique<KeyInputStrategy>(std::move(wheelPositiveTiltInputCommands)));

    std::unordered_map<unsigned long, std::unordered_set<int>> mouseCapableInputs;

    std::unordered_set<int> inputEvs;

    inputEvs.emplace(0);
    inputEvs.emplace(1);

    mouseCapableInputs.try_emplace(UI_SET_EVBIT, std::move(inputEvs));

    std::unordered_set<int> inputEvKeys;

    inputEvKeys.emplace(17);
    inputEvKeys.emplace(19);
    inputEvKeys.emplace(29);
    inputEvKeys.emplace(36);
    inputEvKeys.emplace(37);
    inputEvKeys.emplace(38);
    inputEvKeys.emplace(46);
    inputEvKeys.emplace(47);
    inputEvKeys.emplace(56);
    inputEvKeys.emplace(105);
    inputEvKeys.emplace(106);

    uinput_setup usetup {};
    snprintf(usetup.name, UINPUT_MAX_NAME_SIZE, "Virtual Keyboard");
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1b1c;
    usetup.id.product = 0x1b2d;

    mouseCapableInputs.try_emplace(UI_SET_KEYBIT, std::move(inputEvKeys));

    VirtualDeviceManager::GetInstance().CreateVirtualDevice(KEYBOARD, mouseCapableInputs, usetup);

    SetProfile(std::move(profile));*/
}

bool LinuxVirtualDevice::HasInputRegistered(const InputEvent& inputEvent)
{
    const unsigned short& type {inputEvent.GetType()};

    if (type == EV_KEY)
    {
        return _keyProfile != nullptr &&
            _keyProfile->currentInputs.contains(inputEvent.GetCode());
    }

    if (type == EV_REL)
    {
        const int& value {inputEvent.GetValue() < 0 ? 0 : inputEvent.GetValue()};

        return _relativeProfile != nullptr &&
            _relativeProfile->currentInputs.contains(inputEvent.GetCode()) &&
                _relativeProfile->currentInputs.at(value).data();
    }

    return false;
}

void LinuxVirtualDevice::ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent)
{
    const unsigned short& type {inputEvent.GetType()};

    if (type == EV_KEY)
    {
        _keyProfile->inputs.at(inputEvent.GetCode()).RegisterValue(deviceId, inputEvent.GetValue());
        return;
    }

    if (type == EV_REL)
    {
        const RelativeInput& relativeInput {_relativeProfile->inputs.at(inputEvent.GetCode())};

        if (inputEvent.GetValue() < 0)
        {
            relativeInput.TriggerNegativeInput(deviceId);
        }
        else
        {
            relativeInput.TriggerPositiveInput(deviceId);
        }
    }
}

void LinuxVirtualDevice::Emit(const InputEvent& inputEvent)
{
    input_event event{};

    event.type = inputEvent.GetType();
    event.code = inputEvent.GetCode();
    event.value = inputEvent.GetValue();

    //std::cout << "Type: " << event.type << " Code: " << event.code << " Value: " << event.value << std::endl;

    gettimeofday(&event.time, nullptr);

    write(_writeFile, &event, sizeof(event));
}

void LinuxVirtualDevice::Synchronize()
{
    Emit({EV_SYN, SYN_REPORT, 0});
}

void LinuxVirtualDevice::Destroy()
{
    ioctl(_writeFile, UI_DEV_DESTROY);
    close(_writeFile);
}