#pragma once
#include <string>
#include <unordered_set>

#include "Device/VirtualDevice/BaseVirtualDevice.h"
#include "Profile/LinuxFileCodes.h"

class LinuxVirtualDevice : public BaseVirtualDevice
{
public:

    LinuxVirtualDevice(InputType inputType, int file);

    LinuxVirtualDevice(const LinuxVirtualDevice& other) = delete;
    LinuxVirtualDevice& operator=(const LinuxVirtualDevice& other) = delete;

    LinuxVirtualDevice(LinuxVirtualDevice&& other) noexcept = default;
    LinuxVirtualDevice& operator=(LinuxVirtualDevice&& other) noexcept = default;

    ~LinuxVirtualDevice() override;

    void CreateProfile() override;

    bool HasInputRegistered(const InputEvent& inputEvent) override;

    void ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent) override;

    void Emit(const InputEvent& inputEvent) override;

    void Synchronize() override;

    void Destroy() override;

private:

    bool _keepLooping {true};

    std::string _filePath;

    std::unordered_set<Code> _codes;

    int _writeFile;
};
