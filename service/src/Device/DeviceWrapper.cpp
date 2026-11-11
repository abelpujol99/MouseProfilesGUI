#include "Device/DeviceWrapper.h"

#include "Device/VirtualDeviceData.h"
#include "Factory/VirtualDeviceFactory.h"

DeviceWrapper::DeviceWrapper(DeviceId deviceId, VirtualDeviceData&& virtualDeviceData, PlatformListenerData&& platformListenerData) :
#ifdef __linux__
    _platformVirtualDevice(VirtualDeviceFactory::CreateLinuxVirtualDevice(std::move(virtualDeviceData))),
#elif defined(__WIN32)
    _platformVirtualDevice(VirtualDeviceFactory::CreateWindowsVirtualDevice(std::move(virtualDeviceData))),
#endif
    _platformListener(deviceId, std::move(platformListenerData)),
    _platformEmitter(deviceId)
{}

PlatformVirtualDevice& DeviceWrapper::GetVirtualDevice()
{
    return _platformVirtualDevice;
}

PlatformListener& DeviceWrapper::GetListener()
{
    return _platformListener;
}

PlatformEmitter& DeviceWrapper::GetEmitter()
{
    return _platformEmitter;
}

void DeviceWrapper::Destroy()
{
    _platformVirtualDevice.Destroy();
    _platformListener.StopListener();
    _platformEmitter.StopEmitting();
}