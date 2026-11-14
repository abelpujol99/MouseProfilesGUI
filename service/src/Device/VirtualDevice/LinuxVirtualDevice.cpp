#include "Device/VirtualDevice/LinuxVirtualDevice.h"

#include <iostream>
#include <unistd.h>
#include <linux/uinput.h>

#include "Command/Macro.h"
#include "Input/Relative/RelativeInput.h"
#include "Managers/DevicesManager.h"

LinuxVirtualDevice::LinuxVirtualDevice(int file) : BaseVirtualDevice(), _writeFile(file)
{}

LinuxVirtualDevice::~LinuxVirtualDevice()
{
    LinuxVirtualDevice::Destroy();
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
        const int& value {inputEvent.GetValue()};

        const Code& code {inputEvent.GetCode()};

        const int& normalizedValue {value < 0 ? 0 : value};

        return _relativeProfile != nullptr &&
            _relativeProfile->currentInputs.contains(code) &&
                _relativeProfile->currentInputs.at(code).at(normalizedValue);
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

    std::cout << "Type: " << event.type << " Code: " << event.code << " Value: " << event.value << std::endl;

    gettimeofday(&event.time, nullptr);

    write(_writeFile, &event, sizeof(event));
}

void LinuxVirtualDevice::Synchronize()
{
    Emit({EV_SYN, SYN_REPORT, 0});
    std::cout << "Sync" << std::endl << "-------------------------------------------------" << std::endl;
}

void LinuxVirtualDevice::Destroy()
{
    ioctl(_writeFile, UI_DEV_DESTROY);
    close(_writeFile);
}