#pragma once
#include "BaseVirtualDevice.h"

class WindowsVirtualDevice : public BaseVirtualDevice
{
public:

    WindowsVirtualDevice(InputType inputType);

    ~WindowsVirtualDevice() override = default;

    void CreateProfile() override;

    bool HasInputRegistered(InputEvent inputEvent) override;

    void ExecuteInput(DeviceId deviceId, InputEvent inputEvent) override;

    void Emit(InputEvent inputEvent) override;

    void Synchronize() override;

    void Destroy() override;

private:


};
