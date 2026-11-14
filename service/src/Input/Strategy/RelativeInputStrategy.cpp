#include "Input/Strategy/RelativeInputStrategy.h"

RelativeInputStrategy::RelativeInputStrategy(std::vector<std::unique_ptr<RelativeInputCommand const>>&& relativeInputCommands) :
        _relativeInputCommands(std::move(relativeInputCommands))
{}

void RelativeInputStrategy::ChangeProfile(uint8_t profileIndex)
{
    _currentRelativeInputCommand = _relativeInputCommands.at(profileIndex).get();
}

void RelativeInputStrategy::Trigger(DeviceId deviceId) const
{
    if (_currentRelativeInputCommand == nullptr)
    {
        return;
    }

    _currentRelativeInputCommand->ExecuteCommand(deviceId);
}
