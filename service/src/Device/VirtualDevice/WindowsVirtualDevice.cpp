#include "Device/VirtualDevice/WindowsVirtualDevice.h"

bool WindowsVirtualDevice::HasInputRegistered(const InputEvent& inputEvent)
{
    return true;
}

void WindowsVirtualDevice::ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent)
{
}

void WindowsVirtualDevice::Emit(const InputEvent& inputEvent)
{

}

void WindowsVirtualDevice::Synchronize()
{

}

void WindowsVirtualDevice::Destroy()
{

}
