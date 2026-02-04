#pragma once
#include <ICommand.h>

class ShutdownApplicationCommand : public ICommand
{
public:
    void Execute() override;
};
