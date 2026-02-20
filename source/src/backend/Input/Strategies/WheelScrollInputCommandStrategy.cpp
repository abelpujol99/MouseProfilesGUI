#include "backend/Input/Strategy/WheelScrollInputCommandStrategy.h"

#include "backend/Input/Wheel/Scroll/WheelScrollInputCommand.h"
#include "backend/Command/ICommand.h"

WheelScrollInputCommandStrategy::WheelScrollInputCommandStrategy(std::vector<std::unique_ptr<WheelScrollInputCommand>>&& wheelNegativeInputCommands,
    std::vector<std::unique_ptr<WheelScrollInputCommand>>&& wheelPositiveInputCommands) : _wheelNegativeInputCommands(std::move(wheelNegativeInputCommands)),
        _wheelPositiveInputCommands(std::move(wheelPositiveInputCommands))
{}

void WheelScrollInputCommandStrategy::ChangeProfile(int profileIndex)
{
    _currentWheelNegativeInputCommand = _wheelNegativeInputCommands[profileIndex].get();
    _currentWheelPositiveInputCommand = _wheelPositiveInputCommands[profileIndex].get();
}

void WheelScrollInputCommandStrategy::RegisterValue(int value)
{
    if (value < 0)
    {
        _currentWheelNegativeInputCommand->ExecuteCommand();
    }
    else if (value > 0)
    {
        _currentWheelPositiveInputCommand->ExecuteCommand();
    }
}
