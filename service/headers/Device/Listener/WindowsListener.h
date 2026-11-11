#pragma once
#include "DeviceUsings.h"

class WindowsListener
{
public:

    ~WindowsListener() = default;

    void ListenerUpdate(DeviceId deviceId);

    void StopListener();

private:

    bool _keepLooping {true};
};