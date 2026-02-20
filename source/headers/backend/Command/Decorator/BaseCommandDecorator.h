#pragma once
#include "backend/Command/ICommand.h"

#include <memory>

class BaseCommandDecorator : public ICommand
{
public:

    virtual ~BaseCommandDecorator() = default;

protected:

    BaseCommandDecorator(std::unique_ptr<ICommand>&& command);

    std::unique_ptr<ICommand> _command;
};
