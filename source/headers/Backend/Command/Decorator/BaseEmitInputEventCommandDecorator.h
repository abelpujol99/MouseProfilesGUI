#pragma once
#include "Backend/Command/Decorator/BaseCommandDecorator.h"

#include "Backend/Command/EmitInputEventCommand.h"

class BaseEmitInputEventCommandDecorator : public BaseCommandDecorator
{
public:

    virtual ~BaseEmitInputEventCommandDecorator() = default;

protected:

    BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    std::unique_ptr<EmitInputEventCommand> _emitInputEventCommand;
};