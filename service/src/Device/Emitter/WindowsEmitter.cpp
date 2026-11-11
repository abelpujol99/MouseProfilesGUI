#include "Device/Emitter/WindowsEmitter.h"

#include "Managers/DevicesManager.h"

WindowsEmitter::WindowsEmitter(DeviceId deviceId) : _emitterThread(std::thread(&WindowsEmitter::EmitterUpdate, this, deviceId))
{
    DevicesManager::GetInstance().SubscribeToDeviceRegisterInput(deviceId, [&]()
    {
        _inputToRetrieve++;
    });
}

void WindowsEmitter::EmitterUpdate(DeviceId deviceId)
{
}

void WindowsEmitter::StopEmitter()
{
    _keepLooping = false;

    if (!_emitterThread.joinable())
    {
        return;
    }

    _emitterThread.join();
}
