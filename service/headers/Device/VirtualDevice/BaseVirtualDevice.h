#pragma once

#include "Input/InputEvent.h"
#include "DeviceUsings.h"
#include "Device/Profile/KeyProfile.h"
#include "Device/Profile/RelativeProfile.h"
#include "Input/Strategy/KeyInputStrategy.h"

class RelativeInput;

class BaseVirtualDevice
{

public:

    BaseVirtualDevice() = default;

    BaseVirtualDevice(const BaseVirtualDevice& other) = delete;
    BaseVirtualDevice& operator=(const BaseVirtualDevice& other) = delete;

    BaseVirtualDevice(BaseVirtualDevice&& other) noexcept;
    BaseVirtualDevice& operator=(BaseVirtualDevice&& other) noexcept;

    virtual ~BaseVirtualDevice() = default;

    void OnChangeApplicationFocus();

    void SetKeyProfile(std::unique_ptr<KeyProfile>&& keyProfile);

    void SetRelativeProfile(std::unique_ptr<RelativeProfile>&& relativeProfile);

    void ChangeCurrentSubProfile(uint8_t subProfileIndex);

    virtual bool HasInputRegistered(const InputEvent& inputEvent) = 0;

    virtual void ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent) = 0;

    virtual void Emit(const InputEvent& inputEvent) = 0;

    virtual void Synchronize() = 0;

    virtual void Destroy() = 0;

protected:

    void UpdateCodesBindings() const;

    void UpdateKeyCodesBindings() const;

    void UpdateRelativeCodesBindings() const;

    std::unique_ptr<KeyProfile> _keyProfile {nullptr};

    std::unique_ptr<RelativeProfile> _relativeProfile {nullptr};

    uint8_t _currentSubProfileIndex {0};
};