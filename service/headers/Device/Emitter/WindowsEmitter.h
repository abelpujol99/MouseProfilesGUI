#pragma once

#include "DeviceUsings.h"

class WindowsEmitter
{
public:

    ~WindowsEmitter() = default;

    void EmitterUpdate(DeviceId deviceId);

    void StopEmitter();

private:

    bool _keepLooping {false};
};