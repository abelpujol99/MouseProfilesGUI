#pragma once
#include <cstdint>
#include <vector>

#include "Input/EmitData.h"
#include "Utilities/Serialization/CommandType.h"

struct CodeRemap
{
    CommandType commandType;
    std::vector<EmitData> emitsData;
    std::uint8_t subProfileIndex;
};