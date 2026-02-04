#include <BaseEmitInputEventCommandDecorator.h>

#include <EmitInputEventCommand.h>

BaseEmitInputEventCommandDecorator::BaseEmitInputEventCommandDecorator(std::unique_ptr<ICommand>&& command,
    std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand) : CommandDecorator(std::move(command)),
        _emitInputEventCommand(std::move(emitInputEventCommand))
{}
