#pragma once
#include <CommandDecorator.h>

class EmitInputEventCommand;

class BaseEmitInputEventCommandDecorator : public CommandDecorator
{
protected:

    std::unique_ptr<EmitInputEventCommand> _emitInputEventCommand;

    BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

public:

    virtual void Execute() = 0;
};