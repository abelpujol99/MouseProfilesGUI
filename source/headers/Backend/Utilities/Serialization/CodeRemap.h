#pragma once
#include <cstdint>
#include <vector>

#include "Backend/Input/EmitData.h"
#include "Backend/Utilities/Serialization/CommandType.h"

struct CodeRemap
{
    CommandType commandType;
    std::vector<EmitData> emitsData;
    std::uint8_t subProfileIndex;
};