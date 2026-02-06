#pragma once
#include "backend/Command/Decorators/BaseEmitInputEventCommandDecorator.h"

class EmitInputEventPosCommandDecorator : public BaseEmitInputEventCommandDecorator
{

public:

    EmitInputEventPosCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    void Execute() override;
};
