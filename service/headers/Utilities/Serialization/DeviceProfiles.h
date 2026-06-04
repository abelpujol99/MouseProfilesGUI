#pragma once
#include <string>
#include "Utilities/Serialization/Profile.h"

struct DeviceProfiles
{
    std::unordered_map<std::string, Profile> profiles;
};
