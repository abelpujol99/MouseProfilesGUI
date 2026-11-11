#pragma once
#include "BaseVirtualDevice.h"

class WindowsVirtualDevice : public BaseVirtualDevice
{
public:

    WindowsVirtualDevice(InputType inputType);

    ~WindowsVirtualDevice() override = default;

    void CreateProfile() override;

    bool HasInputRegistered(const InputEvent& inputEvent) override;

    void ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent) override;

    void Emit(const InputEvent& inputEvent) override;

    void Synchronize() override;

    void Destroy() override;

private:


};
