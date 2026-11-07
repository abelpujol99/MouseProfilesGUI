#include "Input/Key/KeyInputCommand.h"

KeyInputCommand::KeyInputCommand(KeyStateCommands&& keyStateCommands, CommandDelay&& delayCommand) :
    _onPressCommand(std::move(keyStateCommands.onPress)), _onHoldCommand(std::move(keyStateCommands.onHold)),
    _onReleaseCommand(std::move(keyStateCommands.onRelease)), delayCommand(std::move(delayCommand))
{}

void KeyInputCommand::Press() const
{
    if (_onPressCommand == nullptr)
    {
        return;
    }

    _onPressCommand->Execute();
}

void KeyInputCommand::Hold() const
{
    if (!HasHoldCommand())
    {
        return;
    }

    _onHoldCommand->Execute();
}

void KeyInputCommand::Release() const
{
    if (_onReleaseCommand == nullptr)
    {
        return;
    }

    _onReleaseCommand->Execute();
}

bool KeyInputCommand::HasHoldCommand() const
{
    return _onHoldCommand != nullptr;
}