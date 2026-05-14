#pragma once
#include "Backend/Utilities/Serialization/CodeRemap.h"

struct SubProfile
{
    std::unordered_map<Code, CodeRemap> codesRemaps;
};