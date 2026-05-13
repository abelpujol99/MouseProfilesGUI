#include "Backend/Managers/VirtualDeviceManager.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "Backend/Managers/ProfileManager.h"
#include "Backend/Managers/ThreadsManager.h"
#include "Backend/Listener/EvdevListener.h"
#include "Backend/Listener/HidrawListener.h"
#include "Backend/Profile/FileCodes.h"

std::unique_ptr<VirtualDeviceManager> VirtualDeviceManager::_virtualDeviceManagerInstance = nullptr;

VirtualDeviceManager::VirtualDeviceManager()
{
    std::unordered_map<unsigned long, std::unordered_set<int>> mouseCapableInputs;

    std::unordered_set<int> inputEvs;

    inputEvs.emplace(0);
    inputEvs.emplace(1);
    inputEvs.emplace(2);
    inputEvs.emplace(4);

    mouseCapableInputs.try_emplace(UI_SET_EVBIT, std::move(inputEvs));

    std::unordered_set<int> inputEvKeys;

    inputEvKeys.emplace(272);
    inputEvKeys.emplace(273);
    inputEvKeys.emplace(275);
    inputEvKeys.emplace(276);

    mouseCapableInputs.try_emplace(UI_SET_KEYBIT, std::move(inputEvKeys));

    std::unordered_set<int> inputEvRels;

    inputEvRels.emplace(0);
    inputEvRels.emplace(1);
    inputEvRels.emplace(6);
    inputEvRels.emplace(11);
    inputEvRels.emplace(12);

    mouseCapableInputs.try_emplace(UI_SET_RELBIT, std::move(inputEvRels));

    std::unordered_set<int> inputEvMsc;
    inputEvMsc.emplace(4);

    mouseCapableInputs.try_emplace(UI_SET_MSCBIT, std::move(inputEvMsc));

    struct uinput_setup usetup {};
    snprintf(usetup.name, UINPUT_MAX_NAME_SIZE, "Virtual Razer Mouse");
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor  = 0x1532;
    usetup.id.product = 0x0099;

    CreateVirtualDevice(MOUSE, mouseCapableInputs, usetup);
}

VirtualDeviceManager& VirtualDeviceManager::GetInstance()
{
    if (!_virtualDeviceManagerInstance)
    {
        _virtualDeviceManagerInstance.reset(new VirtualDeviceManager());
    }

    return *_virtualDeviceManagerInstance;
}

void VirtualDeviceManager::CreateVirtualDevice(InputDevices inputDevice, std::unordered_map<unsigned long, std::unordered_set<int>> capableInputs,
    uinput_setup inputSetup)
{
    int virtualFile = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (virtualFile < 0)
    {
        std::__throw_runtime_error("Unable to create a Virtual Device");
    }

    for (auto& capableInput : capableInputs)
    {
        const unsigned long& virtualDeviceType {capableInput.first};
        const std::unordered_set<int>& virtualDeviceCapableInputs {capableInput.second};

        for (auto& virtualDeviceCapableInput : virtualDeviceCapableInputs)
        {
            ioctl(virtualFile, virtualDeviceType, virtualDeviceCapableInput);
        }
    }

    ioctl(virtualFile, UI_DEV_SETUP, &inputSetup);
    ioctl(virtualFile, UI_DEV_CREATE);

    _virtualDevices.try_emplace(inputDevice, virtualFile);
}

void VirtualDeviceManager::CreateListeners()
{
    //TODO PROCESS PARAMETER DATA

    std::forward_list<FileCodes> evdevFilesCodes;
    evdevFilesCodes.emplace_front(FileCodes{"/dev/input/by-id/usb-Razer_Razer_Basilisk_V3-event-mouse", {8, 272, 273, 275, 276}});
    ThreadsManager::GetInstance().CreateListenersThreads<EvdevListener>(std::move(evdevFilesCodes));

    std::forward_list<FileCodes> hidrawFilesCodes;
    hidrawFilesCodes.emplace_front(FileCodes{"/dev/hidraw0", {32, 64}});
    //hidrawFilesCodes.emplace_front(FileCodes{"/dev/hidraw1", {80, 81, 82, 84}});
    ThreadsManager::GetInstance().CreateListenersThreads<HidrawListener>(std::move(hidrawFilesCodes));
}

void VirtualDeviceManager::RegisterEvdevInputEvent(InputEvent inputEvent) const
{
    if (!ProfileManager::GetInstance().IsCodeInUse(inputEvent.GetCode()))
    {
        Emit(MOUSE, inputEvent);
        return;
    }

    ProfileManager::GetInstance().RegisterInput(inputEvent.GetCode(), inputEvent.GetValue());
}

void VirtualDeviceManager::RegisterHidrawInputEvent(unsigned char code, int value)
{
    if (!ProfileManager::GetInstance().IsCodeInUse(code))
    {
        return;
    }

    ProfileManager::GetInstance().RegisterInput(code, value);
}

void VirtualDeviceManager::Emit(InputDevices inputDevice, InputEvent inputEvent) const
{
    input_event event{};

    event.type = inputEvent.GetType();
    event.code = inputEvent.GetCode();
    event.value = inputEvent.GetValue();

    //std::cout << "Type: " << event.type << " Code: " << event.code << " Value: " << event.value << std::endl;

    gettimeofday(&event.time, nullptr);

    write(_virtualDevices.at(inputDevice), &event, sizeof(event));
}

void VirtualDeviceManager::DestroyVirtualFiles()
{
    for (auto& virtualDevice : _virtualDevices)
    {
        int& virtualFile {virtualDevice.second};

        ioctl(virtualFile, UI_DEV_DESTROY);
        close(virtualFile);
    }
}