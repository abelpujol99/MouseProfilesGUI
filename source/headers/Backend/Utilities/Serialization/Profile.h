#pragma once
#include <vector>

#include "Backend/Utilities/Serialization/SubProfile.h"

struct Profile
{
    bool isCurrentProfile;
    std::vector<SubProfile> subProfiles;
};