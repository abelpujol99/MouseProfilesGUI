#pragma once

#include "backend/Command/ICommand.h"

class SwitchToProfileCommand : public ICommand
{
private:

    int _profileIndex;

public:

    SwitchToProfileCommand(int profileIndex);

    void Execute() override;
};