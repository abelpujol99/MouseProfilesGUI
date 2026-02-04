#pragma once

#include <memory>

class ICommand;

class WheelScrollInputCommand
{
private:

    std::unique_ptr<ICommand> _command;

public:

    WheelScrollInputCommand(std::unique_ptr<ICommand> command);

    void ExecuteCommand() const;
};