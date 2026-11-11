#include "Factory/VirtualDeviceFactory.h"

#include <fcntl.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>

#include "Device/VirtualDeviceData.h"
#include "Device/VirtualDevice/LinuxVirtualDevice.h"
#include "Device/VirtualDevice/WindowsVirtualDevice.h"

LinuxVirtualDevice VirtualDeviceFactory::CreateLinuxVirtualDevice(VirtualDeviceData&& virtualDeviceData)
{
    int virtualFile = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (virtualFile < 0)
    {
        std::__throw_runtime_error("Unable to create a Virtual Device");
    }

    for (auto& capableInput : virtualDeviceData.GetCapableInputs())
    {
        const unsigned long& inputType {capableInput.first};
        const std::unordered_set<int>& virtualDeviceCapableInputs {capableInput.second};

        for (auto& virtualDeviceCapableInput : virtualDeviceCapableInputs)
        {
            ioctl(virtualFile, inputType, virtualDeviceCapableInput);
        }
    }

    const DeviceData& deviceData {virtualDeviceData.GetDeviceData()};

    uinput_setup inputSetup
    {
        input_id{
            deviceData.GetBusType(),
            deviceData.GetVendor(),
            deviceData.GetProduct(),
            deviceData.GetVersion()
        }
    };

    ioctl(virtualFile, UI_DEV_SETUP, &inputSetup);
    ioctl(virtualFile, UI_DEV_CREATE);

    return {virtualDeviceData.GetInputType(), virtualFile};
}

WindowsVirtualDevice VirtualDeviceFactory::CreateWindowsVirtualDevice(VirtualDeviceData&& virtualDeviceData)
{
    return {virtualDeviceData.GetInputType()};
}
