#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <linux/uinput.h>

#include "../../../shared/headers/Input/InputDevices.h"
#include "Input/InputEvent.h"

class VirtualDeviceManager
{
public:

    ~VirtualDeviceManager() = default;

    VirtualDeviceManager(const VirtualDeviceManager& other) = delete;
    VirtualDeviceManager& operator=(const VirtualDeviceManager& other) = delete;

    static VirtualDeviceManager& GetInstance();

    void CreateVirtualDevice(InputDevices inputDevice, std::unordered_map<unsigned long, std::unordered_set<int>> capableInputs,
        uinput_setup inputSetup);

    void CreateListeners();

    void RegisterEvdevInputEvent(InputEvent inputEvent) const;

    static void RegisterHidrawInputEvent(unsigned char code, int value);

    void Emit(InputDevices inputDevice, InputEvent inputEvent) const;

    void DestroyVirtualFiles();

private:

    VirtualDeviceManager();

    static std::unique_ptr<VirtualDeviceManager> _virtualDeviceManagerInstance;

    std::unordered_map<InputDevices, int> _virtualDevices;
};
