#include "Input/Key/KeyInputCommands.h"

KeyInputCommands::KeyInputCommands(KeyStateCommands&& keyStateCommands) : _onPressCommand(std::move(keyStateCommands.onPress)),
    _holdCommand(std::move(keyStateCommands.onHold)), _onReleaseCommand(std::move(keyStateCommands.onRelease))
{}

void KeyInputCommands::Press(DeviceId deviceId) const
{
    if (_onPressCommand == nullptr)
    {
        return;
    }

    _onPressCommand->Execute(deviceId);
}

const HoldCommand* KeyInputCommands::GetHoldCommand() const
{
    return _holdCommand.get();
}

void KeyInputCommands::Hold(DeviceId deviceId) const
{
    if (_holdCommand == nullptr)
    {
        return;
    }

    _holdCommand->ExecuteCommand(deviceId);
}

void KeyInputCommands::Release(DeviceId deviceId) const
{
    if (_onReleaseCommand == nullptr)
    {
        return;
    }

    _onReleaseCommand->Execute(deviceId);
}