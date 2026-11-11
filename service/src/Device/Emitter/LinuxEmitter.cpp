#include "Device/Emitter/LinuxEmitter.h"

void LinuxEmitter::EmitterUpdate(DeviceId deviceId)
{
}

void LinuxEmitter::StopEmitting()
{
    _keepLooping = false;
}
