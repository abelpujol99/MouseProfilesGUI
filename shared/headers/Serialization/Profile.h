#pragma once
#include <string>
#include <vector>

#include "Serialization/SubProfile.h"

struct Profile
{
    std::string name;
    bool isCurrentProfile;
    std::vector<SubProfile> subProfiles;
};