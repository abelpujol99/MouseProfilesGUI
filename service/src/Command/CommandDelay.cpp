#include "Command/CommandDelay.h"

CommandDelay::CommandDelay(Duration&& firstDelayInMillis, Duration&& millisToRepeatCommand) :
    _firstDelayInMillis(firstDelayInMillis), _millisToRepeatCommand(millisToRepeatCommand)
{}

const Duration& CommandDelay::GetFirstDelayInMillis() const
{
    return _firstDelayInMillis;
}

const Duration& CommandDelay::GetMillisToRepeatCommand() const
{
    return _millisToRepeatCommand;
}
