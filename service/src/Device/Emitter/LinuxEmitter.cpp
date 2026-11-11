#include "Device/Emitter/LinuxEmitter.h"

#include "TimeDefines.h"
#include "Managers/DevicesManager.h"

LinuxEmitter::LinuxEmitter(DeviceId deviceId) : _emitterThread(std::thread(&LinuxEmitter::EmitterUpdate, this, deviceId))
{
    DevicesManager::GetInstance().SubscribeToDeviceRegisterInput(deviceId, [&]()
    {
        _inputsToRetrieve++;
    });
}

void LinuxEmitter::EmitterUpdate(DeviceId deviceId)
{
    DevicesManager& devicesManagerInstance {DevicesManager::GetInstance()};

    while (_keepLooping.load())
    {
        if (_inputsToRetrieve == 0)
        {
            std::this_thread::sleep_for(Duration(THREAD_SLEEP_MILLIS));
            continue;
        }

        const InputEvent& inputEvent {devicesManagerInstance.GetDeviceInputEvent(deviceId)};

        _inputsToRetrieve--;

        devicesManagerInstance.ExecuteInputEvent(deviceId, inputEvent);
    }

    DevicesManager::GetInstance().UnsubscribeToDeviceRegisterInput(deviceId);
}

void LinuxEmitter::StopEmitting()
{
    _keepLooping.store(false);

    if (!_emitterThread.joinable())
    {
        return;
    }

    _emitterThread.join();
}
