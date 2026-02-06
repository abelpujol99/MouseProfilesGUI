#pragma once
#include "backend/Command/Decorators/CommandDecorator.h"

class EmitInputEventCommand;

class BaseEmitInputEventCommandDecorator : public CommandDecorator
{
public:

    virtual void Execute() = 0;

protected:

    std::unique_ptr<EmitInputEventCommand> _emitInputEventCommand;

    BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);
};