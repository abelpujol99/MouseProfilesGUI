#pragma once
#include "../../../../shared/headers/Input/InputCommand.h"

#include <memory>

#include "Command/ICommand.h"

class ButtonInputCommand : public InputCommand
{
public:

    ButtonInputCommand(std::unique_ptr<ICommand>&& commandOnPress, std::unique_ptr<ICommand>&& commandOnHold,
        std::unique_ptr<ICommand>&& commandOnRelease, Duration&& firstDelayInMillis, Duration&& millisToRepeatInput);

    ~ButtonInputCommand() = default;

    void Press() const;

    void Hold() const;

    void Release() const;

    bool HasHoldCommand() const;

private:

    std::unique_ptr<ICommand> _commandOnPress;
    std::unique_ptr<ICommand> _commandOnHold;
    std::unique_ptr<ICommand> _commandOnRelease;
};
