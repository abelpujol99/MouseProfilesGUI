#pragma once

#include <vector>

#include "Frontend/Utilities/Structs/DeviceInfo.h"

class IReadDevicesStrategy
{
public:
    virtual ~IReadDevicesStrategy() = default;

    [[nodiscard]] virtual std::vector<DeviceInfo> ReturnDevices() = 0;
};