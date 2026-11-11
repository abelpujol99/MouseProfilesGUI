#pragma once
#include "DeviceUsings.h"

class ICommand
{

public:

    virtual ~ICommand() = default;

    virtual void Execute(DeviceId deviceId) const = 0;
};
