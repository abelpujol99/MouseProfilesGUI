#pragma once
#include <cstdint>
#include <vector>

#include "Input/EmitData.h"
#include "Serialization/CommandType.h"

struct CodeRemap
{
    Code code;
    CommandType commandType;
    std::vector<EmitData> emitsData;
    std::uint8_t subProfileIndex;
};