#pragma once
#include "Command/ICommand.h"

class ShutdownApplication : public ICommand
{
public:

    ~ShutdownApplication() override = default;

    void Execute(DeviceId deviceId) const override;
};
