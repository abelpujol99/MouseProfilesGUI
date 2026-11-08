#pragma once

#include <memory>

#include "Command/ICommand.h"
#include "Command/CommandDelay.h"
#include "Input/Key/KeyStateCommands.h"

class KeyInputCommand
{
public:

    KeyInputCommand(KeyStateCommands&& keyStateCommands, CommandDelay&& delayCommand);

    ~KeyInputCommand() = default;

    void Press() const;

    void Hold() const;

    void Release() const;

private:

    const std::unique_ptr<ICommand const> _onPressCommand;
    const std::unique_ptr<ICommand const> _onHoldCommand;
    const std::unique_ptr<ICommand const> _onReleaseCommand;

    const CommandDelay delayCommand;
};