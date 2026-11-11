#include "Device/Listener/WindowsListener.h"

WindowsListener::WindowsListener(DeviceId deviceId) : _listenerThread(std::thread(&WindowsListener::ListenerUpdate, this, deviceId))
{
}

void WindowsListener::ListenerUpdate(DeviceId deviceId)
{
}

void WindowsListener::StopListener()
{
    _keepLooping = false;

    if (!_listenerThread.joinable())
    {
        return;
    }

    _listenerThread.join();
}
