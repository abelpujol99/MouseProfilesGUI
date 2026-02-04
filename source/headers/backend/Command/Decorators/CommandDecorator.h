#pragma once
#include <ICommand.h>

#include <memory>

class CommandDecorator : public ICommand
{
protected:

    std::unique_ptr<ICommand> _command;

    CommandDecorator(std::unique_ptr<ICommand>&& command);

public:

    virtual void Execute() = 0;
};
