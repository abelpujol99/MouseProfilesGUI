#pragma once

#include <thread>

#include "DeviceUsings.h"

class WindowsEmitter
{
public:

    WindowsEmitter(DeviceId deviceId);

    ~WindowsEmitter() = default;

    void StopEmitter();

private:

    void EmitterUpdate(DeviceId deviceId);

    uint8_t _inputToRetrieve {0};

    std::atomic<bool> _keepLooping {false};

    std::thread _emitterThread;
};