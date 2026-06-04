#pragma once
#include <unordered_map>
#include "Utilities/Serialization/CodeRemap.h"

struct SubProfile
{
    std::unordered_map<Code, CodeRemap> codesRemaps;
};