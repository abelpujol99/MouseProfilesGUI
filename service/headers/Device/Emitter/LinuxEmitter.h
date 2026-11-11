#pragma once

#include <thread>

#include "DeviceUsings.h"

class LinuxEmitter
{
public:

    LinuxEmitter(DeviceId deviceId);

    LinuxEmitter(const LinuxEmitter& other) = delete;
    LinuxEmitter& operator=(const LinuxEmitter& other) = delete;
    LinuxEmitter(LinuxEmitter&& other) = delete;
    LinuxEmitter& operator=(LinuxEmitter&& other) = delete;

    ~LinuxEmitter() = default;

    void StopEmitting();

private:

    void EmitterUpdate(DeviceId deviceId);

    uint8_t _inputsToRetrieve {0};

    std::atomic<bool> _keepLooping {true};

    std::thread _emitterThread;
};