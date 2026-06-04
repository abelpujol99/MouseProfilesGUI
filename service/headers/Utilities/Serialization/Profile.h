#pragma once
#include <vector>

#include "Utilities/Serialization/SubProfile.h"

struct Profile
{
    bool isCurrentProfile;
    std::vector<SubProfile> subProfiles;
};