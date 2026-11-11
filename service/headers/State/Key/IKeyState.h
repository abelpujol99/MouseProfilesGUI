#pragma once

#include "DeviceUsings.h"

class IKeyState
{
public:

    virtual ~IKeyState() = default;

    virtual void OnInput(DeviceId deviceId) = 0;
};
