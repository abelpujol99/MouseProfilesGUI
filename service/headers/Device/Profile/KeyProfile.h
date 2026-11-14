#pragma once
#include <cstdint>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>

#include "CodeUsings.h"
#include "Input/Strategy/KeyInputStrategy.h"

struct KeyProfile
{
    std::unordered_map<Code, KeyInputStrategy> inputs;
    std::unordered_map<uint8_t, std::forward_list<Code>> subProfilesCodes;
    std::unordered_set<Code> currentInputs;
};
