#pragma once

#include <memory>

#include "Command/ICommand.h"

class RelativeInputCommand
{

public:

    RelativeInputCommand(std::unique_ptr<ICommand const>&& command);

    ~RelativeInputCommand() = default;

    void ExecuteCommand() const;

private:

    const std::unique_ptr<ICommand const> _command;

};