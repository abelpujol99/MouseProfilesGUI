#pragma once
#include "TimeUsings.h"

class CommandDelay
{
public:

    CommandDelay(Duration&& firstDelayInMillis, Duration&& millisToRepeatCommand);

    [[nodiscard]] const Duration& GetFirstDelayInMillis() const;

    [[nodiscard]] const Duration& GetMillisToRepeatCommand() const;

private:

    const Duration _firstDelayInMillis;

    const Duration _millisToRepeatCommand;
};
