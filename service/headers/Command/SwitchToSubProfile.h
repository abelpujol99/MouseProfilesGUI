#pragma once

#include <cstdint>

#include "Command/ICommand.h"

class SwitchToSubProfile : public ICommand
{
public:

    SwitchToSubProfile(uint8_t subProfileIndex);

    ~SwitchToSubProfile() override = default;

    void Execute() const override;

private:

    uint8_t _subProfileIndex;
};