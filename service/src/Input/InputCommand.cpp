#include "Input/InputCommand.h"

InputCommand::InputCommand(Duration&& firstDelayInMillis, Duration&& millisToRepeatInput) : _firstDelayInMillis(std::move(firstDelayInMillis)),
    _millisToRepeatInput(std::move(millisToRepeatInput))
{}

const Duration& InputCommand::GetFirstDelayInMillis() const
{
    return _firstDelayInMillis;
}

const Duration& InputCommand::GetMillisToRepeatInput() const
{
    return _millisToRepeatInput;
}
