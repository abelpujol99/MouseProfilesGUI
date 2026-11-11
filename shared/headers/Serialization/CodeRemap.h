#pragma once
#include <cstdint>
#include <vector>

#include "CodeUsings.h"
#include "Input/InputEvent.h"
#include "Serialization/CommandType.h"

struct CodeRemap
{
    Code code;
    CommandType commandType;
    std::vector<InputEvent> inputEvents;
    std::uint8_t subProfileIndex;
};