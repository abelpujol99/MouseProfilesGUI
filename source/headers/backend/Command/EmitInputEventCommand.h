#pragma once
#include <ICommand.h>

#include <vector>

#include <InputDevices.h>
#include <InputEvent.h>

#include "EmitData.h"

class EmitInputEventCommand : public ICommand
{
private:

    std::vector<EmitData> _emitsData;

public:

    EmitInputEventCommand(std::vector<EmitData>&& emitsData);

    void Execute() override;
};
