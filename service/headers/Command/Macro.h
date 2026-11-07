#pragma once
#include "Command/ICommand.h"

#include <vector>

#include "Input/EmitData.h"

class Macro : public ICommand
{
public:

    Macro(std::vector<EmitData>&& emitsData);

    ~Macro() override = default;

    void Execute() const override;

private:

    std::vector<EmitData> _emitsData;
};
