#pragma once
#include "backend/Command/ICommand.h"

#include <memory>

class CommandDecorator : public ICommand
{
public:

    virtual void Execute() = 0;

protected:

    std::unique_ptr<ICommand> _command;

    CommandDecorator(std::unique_ptr<ICommand>&& command);
};
