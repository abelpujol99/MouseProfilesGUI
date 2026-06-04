#include "Command/Decorator/BaseEmitInputEventCommandDecorator.h"

#include "Command/EmitInputEventCommand.h"

BaseEmitInputEventCommandDecorator::BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
    std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand) :
        BaseCommandDecorator(std::move(command)), _emitInputEventCommand(std::move(emitInputEventCommand))
{}
