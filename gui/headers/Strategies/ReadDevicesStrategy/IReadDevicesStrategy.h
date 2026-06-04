#pragma once

#include <vector>

#include "Utilities/Structs/DeviceInfo.h"

class IReadDevicesStrategy
{
public:
    virtual ~IReadDevicesStrategy() = default;

    [[nodiscard]] virtual std::vector<DeviceInfo> ReturnDevices() = 0;
};