#pragma once
#include "backend/Input/InputCommand.h"

#include <memory>


class ICommand;

class ButtonInputCommand : public InputCommand
{
public:

    ButtonInputCommand(std::unique_ptr<ICommand>&& commandOnPress, std::unique_ptr<ICommand>&& commandOnHold,
        std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis, Duration&& millisToRepeatInput);

    void Press() const;

    void Hold() const;

    void Release() const;

    bool HasHoldCommand() const;

private:

    std::unique_ptr<ICommand> _commandOnPress;
    std::unique_ptr<ICommand> _commandOnHold;
    std::unique_ptr<ICommand> _commandOnRelease;
};