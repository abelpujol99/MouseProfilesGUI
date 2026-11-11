#pragma once
#include <atomic>
#include <thread>

#include "DeviceUsings.h"

class WindowsListener
{
public:

    WindowsListener(DeviceId deviceId);

    ~WindowsListener() = default;

    void StopListener();

private:

    void ListenerUpdate(DeviceId deviceId);

    std::atomic<bool> _keepLooping {true};

    std::thread _listenerThread;
};