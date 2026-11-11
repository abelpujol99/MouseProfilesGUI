#include "../../../headers/Device/VirtualDevice/WindowsVirtualDevice.h"

WindowsVirtualDevice::WindowsVirtualDevice(InputType inputType) : BaseVirtualDevice(inputType)
{}

void WindowsVirtualDevice::CreateProfile()
{
}

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
