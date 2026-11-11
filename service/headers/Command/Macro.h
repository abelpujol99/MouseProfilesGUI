#pragma once
#include "Command/ICommand.h"

#include <vector>

#include "Input/InputEvent.h"

class Macro : public ICommand
{
public:

    Macro(std::vector<InputEvent>&& inputEvents);

    ~Macro() override = default;

    void Execute(DeviceId deviceId) const override;

private:

    std::vector<InputEvent> _inputEvents;
};
