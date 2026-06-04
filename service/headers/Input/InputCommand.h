#pragma once
#include "TimeUsings.h"

class InputCommand
{
public:

    InputCommand(Duration&& firstDelayInMillis, Duration&& millisToRepeatInput);

    ~InputCommand() = default;

    [[nodiscard]] const Duration& GetFirstDelayInMillis() const;

    [[nodiscard]] const Duration& GetMillisToRepeatInput() const;

private:

    const Duration _firstDelayInMillis;
    const Duration _millisToRepeatInput;

};