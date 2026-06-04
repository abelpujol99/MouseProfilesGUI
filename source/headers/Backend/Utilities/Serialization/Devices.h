#pragma once

#include "Backend/Utilities/Serialization/DeviceProfiles.h"

struct Devices
{
    std::unordered_map<std::string, DeviceProfiles> devicesProfiles;
};