#pragma once
#include "backend/Command/ICommand.h"

class ShutdownApplicationCommand : public ICommand
{
public:
    void Execute() override;
};
