#pragma once

#include "DeviceUsings.h"

class LinuxEmitter
{
public:

    ~LinuxEmitter() = default;

    void EmitterUpdate(DeviceId deviceId);

    void StopEmitting();

private:

    bool _keepLooping {true};
};