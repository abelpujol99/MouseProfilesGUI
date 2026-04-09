#pragma once

#include "Backend/Command/ICommand.h"

class SwitchToProfileCommand : public ICommand
{
public:

    SwitchToProfileCommand(int profileIndex);

    ~SwitchToProfileCommand() override = default;

    void Execute() override;

private:

    int _profileIndex;
};