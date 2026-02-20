#pragma once
#include "backend/Command/Decorator/BaseCommandDecorator.h"

class EmitInputEventCommand;

class BaseEmitInputEventCommandDecorator : public BaseCommandDecorator
{
public:

    virtual ~BaseEmitInputEventCommandDecorator() = default;

protected:

    BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    std::unique_ptr<EmitInputEventCommand> _emitInputEventCommand;
};