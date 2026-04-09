#pragma once

#include <memory>

#include "Backend/Command/ICommand.h"

class WheelScrollInputCommand
{
public:

    WheelScrollInputCommand(std::unique_ptr<ICommand>&& command);

    ~WheelScrollInputCommand() = default;

    void ExecuteCommand() const;

private:

    std::unique_ptr<ICommand> _command;

};
