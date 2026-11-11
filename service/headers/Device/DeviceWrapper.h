#pragma once

#include "Utilities/Usings/PlatformUsings.h"

class VirtualDeviceData;

class DeviceWrapper
{
public:
    DeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData, PlatformListenerData&& platformListenerData);

    [[nodiscard]] DeviceId GetDeviceId() const;

    [[nodiscard]] PlatformVirtualDevice& GetVirtualDevice();
    [[nodiscard]] PlatformListener& GetListener();
    [[nodiscard]] PlatformEmitter& GetEmitter();

    void Destroy();

private:

    DeviceId _deviceId;

    PlatformVirtualDevice _platformVirtualDevice;
    PlatformListener _platformListener;
    PlatformEmitter _platformEmitter;

};
