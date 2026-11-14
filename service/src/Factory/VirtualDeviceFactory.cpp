#include "Factory/VirtualDeviceFactory.h"

#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>

#include "Device/VirtualDeviceData.h"
#include "Device/VirtualDevice/LinuxVirtualDevice.h"
#include "Device/VirtualDevice/WindowsVirtualDevice.h"
#include "Utilities/Usings/PlatformUsings.h"

LinuxVirtualDevice VirtualDeviceFactory::CreateLinuxVirtualDevice(VirtualDeviceData&& virtualDeviceData)
{
    int virtualFile = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (virtualFile < 0)
    {
        std::__throw_runtime_error("Unable to create a Virtual Device");
    }

    for (const auto& [inputType, virtualDeviceCapableInputs] : virtualDeviceData.GetCapableInputs())
    {
        for (auto& virtualDeviceCapableInput : virtualDeviceCapableInputs)
        {
            ioctl(virtualFile, inputType, virtualDeviceCapableInput);
        }
    }

    const PlatformDeviceData& platformDeviceData {virtualDeviceData.GetDeviceData()};

    if (ioctl(virtualFile, UI_DEV_SETUP, &platformDeviceData))
    {
        perror("UI_DEV_CREATE");
        close(virtualFile);
        throw std::runtime_error("Unable to create virtual file");
    }

    if (ioctl(virtualFile, UI_DEV_CREATE))
    {
        perror("UI_DEV_SETUP");
    }

    return {virtualFile};
}

WindowsVirtualDevice VirtualDeviceFactory::CreateWindowsVirtualDevice(VirtualDeviceData&& virtualDeviceData)
{
    return {};
}
