#pragma once
#include "backend/Command/ICommand.h"

#include <vector>

#include "backend/Input/EmitData.h"

class EmitInputEventCommand : public ICommand
{
public:

    EmitInputEventCommand(std::vector<EmitData>&& emitsData);

    void Execute() override;

private:

    std::vector<EmitData> _emitsData;
};
