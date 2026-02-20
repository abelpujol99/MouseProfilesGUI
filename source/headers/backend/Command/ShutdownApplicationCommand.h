#pragma once
#include "backend/Command/ICommand.h"

class ShutdownApplicationCommand : public ICommand
{
public:

    ~ShutdownApplicationCommand() override = default;

    void Execute() override;
};
