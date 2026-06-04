#include "Command/Decorator/EmitInputEventPosCommandDecorator.h"

EmitInputEventPosCommandDecorator::EmitInputEventPosCommandDecorator(std::unique_ptr<ICommand>&& command,
    std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand) :
        BaseEmitInputEventCommandDecorator(std::move(command), std::move(emitInputEventCommand))
{}

void EmitInputEventPosCommandDecorator::Execute()
{
    _command->Execute();
    _emitInputEventCommand->Execute();
}