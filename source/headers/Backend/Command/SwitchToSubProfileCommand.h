#pragma once

#include "Backend/Command/ICommand.h"

class SwitchToSubProfileCommand : public ICommand
{
public:

    SwitchToSubProfileCommand(int profileIndex);

    ~SwitchToSubProfileCommand() override = default;

    void Execute() override;

private:

    int _profileIndex;
};