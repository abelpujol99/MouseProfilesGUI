#pragma once
#include "Backend/Command/Decorator/BaseEmitInputEventCommandDecorator.h"

class EmitInputEventPreCommandDecorator : public BaseEmitInputEventCommandDecorator
{

public:

    EmitInputEventPreCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    ~EmitInputEventPreCommandDecorator() = default;

    void Execute() override;
};
