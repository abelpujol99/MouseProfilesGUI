#pragma once
#include "backend/Command/Decorators/BaseEmitInputEventCommandDecorator.h"

#include <memory>

#include "backend/Command/ICommand.h"

class EmitInputEventPreCommandDecorator : public BaseEmitInputEventCommandDecorator
{

public:

    EmitInputEventPreCommandDecorator(std::unique_ptr<ICommand>&& command,
        std::unique_ptr<EmitInputEventCommand>&& emitInputEventCommand);

    void Execute() override;
};
