#pragma once

#include <cstdint>

#include "Command/ICommand.h"

class SwitchToSubProfileCommand : public ICommand
{
public:

    SwitchToSubProfileCommand(uint8_t subProfileIndex);

    ~SwitchToSubProfileCommand() override = default;

    void Execute() override;

private:

    uint8_t _subProfileIndex;
};