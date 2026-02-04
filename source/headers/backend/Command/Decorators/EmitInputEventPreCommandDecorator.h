#pragma once
#include <BaseEmitInputEventCommandDecorator.h>

class EmitInputEventPreCommandDecorator : public BaseEmitInputEventCommandDecorator
{

public:

    EmitInputEventPreCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    void Execute() override;
};
