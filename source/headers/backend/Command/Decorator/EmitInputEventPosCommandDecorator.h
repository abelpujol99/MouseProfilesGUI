#pragma once
#include "backend/Command/Decorator/BaseEmitInputEventCommandDecorator.h"

class EmitInputEventPosCommandDecorator : public BaseEmitInputEventCommandDecorator
{

public:

    EmitInputEventPosCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    ~EmitInputEventPosCommandDecorator() = default;

    void Execute() override;
};
