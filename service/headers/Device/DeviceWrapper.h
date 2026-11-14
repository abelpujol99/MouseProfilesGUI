#pragma once

#include "Utilities/Usings/PlatformUsings.h"

class VirtualDeviceData;

class DeviceWrapper
{
public:

    DeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData, PlatformListenerData&& platformListenerData);

    [[nodiscard]] PlatformVirtualDevice& GetVirtualDevice();
    [[nodiscard]] PlatformListener& GetListener();
    [[nodiscard]] PlatformEmitter& GetEmitter();

    ~DeviceWrapper();

private:

    void Destroy();

    PlatformVirtualDevice _platformVirtualDevice;
    PlatformListener _platformListener;
    PlatformEmitter _platformEmitter;

};
