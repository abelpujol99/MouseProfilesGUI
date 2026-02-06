#pragma once
#include "backend/Command/ICommand.h"

#include <vector>

#include "backend/Input/EmitData.h"

class EmitInputEventCommand : public ICommand
{
private:

    std::vector<EmitData> _emitsData;

public:

    EmitInputEventCommand(std::vector<EmitData>&& emitsData);

    void Execute() override;
};
