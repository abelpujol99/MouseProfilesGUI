#include "../../../headers/Device/VirtualDevice/WindowsVirtualDevice.h"

WindowsVirtualDevice::WindowsVirtualDevice(InputType inputType) : BaseVirtualDevice(inputType)
{}

void WindowsVirtualDevice::CreateProfile()
{
}

bool WindowsVirtualDevice::HasInputRegistered(InputEvent inputEvent)
{
    return true;
}

void WindowsVirtualDevice::ExecuteInput(DeviceId deviceId, InputEvent inputEvent)
{
}

void WindowsVirtualDevice::Emit(InputEvent inputEvent)
{

}

void WindowsVirtualDevice::Synchronize()
{

}

void WindowsVirtualDevice::Destroy()
{

}
