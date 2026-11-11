#pragma once

#include "Device/VirtualDevice/LinuxVirtualDevice.h"
#include "Device/VirtualDevice/WindowsVirtualDevice.h"

class VirtualDeviceData;

class VirtualDeviceFactory
{
public:

    [[nodiscard]] static LinuxVirtualDevice CreateLinuxVirtualDevice(VirtualDeviceData&& virtualDeviceData);

    [[nodiscard]] static WindowsVirtualDevice CreateWindowsVirtualDevice(VirtualDeviceData&& virtualDeviceData);
};
