#pragma once
#include <cstdint>
#include <forward_list>
#include <unordered_map>

#include "CodeUsings.h"
#include "Input/Relative/RelativeInput.h"
#include "Serialization/RelativeCode.h"

struct RelativeProfile
{
    std::unordered_map<Code, RelativeInput> inputs;
    std::unordered_map<uint8_t, std::forward_list<RelativeCode>> subProfilesCodes;
    std::unordered_map<Code, std::array<bool, 2>> currentInputs;
};
