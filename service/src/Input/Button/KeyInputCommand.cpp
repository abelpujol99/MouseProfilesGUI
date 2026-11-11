#include "Input/Key/KeyInputCommand.h"

KeyInputCommand::KeyInputCommand(KeyStateCommands&& keyStateCommands, CommandDelay&& delayCommand) :
    _onPressCommand(std::move(keyStateCommands.onPress)), _onHoldCommand(std::move(keyStateCommands.onHold)),
    _onReleaseCommand(std::move(keyStateCommands.onRelease)), delayCommand(std::move(delayCommand))
{}

void KeyInputCommand::Press(DeviceId deviceId) const
{
    if (_onPressCommand == nullptr)
    {
        return;
    }

    _onPressCommand->Execute(deviceId);
}

void KeyInputCommand::Hold(DeviceId deviceId) const
{
    if (_onHoldCommand == nullptr)
    {
        return;
    }

    _onHoldCommand->Execute(deviceId);
}

void KeyInputCommand::Release(DeviceId deviceId) const
{
    if (_onReleaseCommand == nullptr)
    {
        return;
    }

    _onReleaseCommand->Execute(deviceId);
}