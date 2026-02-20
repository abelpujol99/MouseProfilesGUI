#pragma once

#include <memory>

class ICommand;

class WheelScrollInputCommand
{
public:

    WheelScrollInputCommand(std::unique_ptr<ICommand>&& command);

    ~WheelScrollInputCommand() = default;

    void ExecuteCommand() const;

private:

    std::unique_ptr<ICommand> _command;

};