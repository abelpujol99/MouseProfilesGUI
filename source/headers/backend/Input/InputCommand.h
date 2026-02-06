#pragma once
#include "TimeUsings.h"

class InputCommand
{
public:

    InputCommand(Duration&& firstDelayInMillis, Duration&& millisToRepeatInput);

    ~InputCommand() = default;

    const Duration& GetFirstDelayInMillis() const;

    const Duration& GetMillisToRepeatInput() const;

private:

    const Duration _firstDelayInMillis;
    const Duration _millisToRepeatInput;

};