#include <EmitInputEventPreCommandDecorator.h>

#include "EmitInputEventCommand.h"


EmitInputEventPreCommandDecorator::EmitInputEventPreCommandDecorator(std::unique_ptr<ICommand>&& command,
                                                                     std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand)
        : BaseEmitInputEventCommandDecorator(std::move(command), std::move(emitInputEventCommand))
{}

void EmitInputEventPreCommandDecorator::Execute()
{
    _emitInputEventCommand->Execute();
    _command->Execute();
}