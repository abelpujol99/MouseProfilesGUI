#pragma once
#include <forward_list>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "Input/InputEvent.h"
#include "DeviceUsings.h"
#include "../InputType.h"
#include "Input/Strategy/KeyInputStrategy.h"
#include "Input/Relative/RelativeInput.h"
#include "Serialization/RelativeCode.h"

class RelativeInput;

class BaseVirtualDevice
{
private:

    struct KeyProfile
    {
        std::unordered_map<Code, KeyInputStrategy> inputs;
        std::unordered_map<uint8_t, std::forward_list<Code>> subProfilesCodes;
        std::unordered_set<Code> currentInputs;
    };

    struct RelativeProfile
    {
        std::unordered_map<Code, RelativeInput> inputs;
        std::unordered_map<uint8_t, std::forward_list<RelativeCode>> subProfilesCodes;
        std::unordered_map<Code, std::array<bool, 2>> currentInputs;
    };

public:

    BaseVirtualDevice(InputType inputType);

    BaseVirtualDevice(const BaseVirtualDevice& other) = delete;
    BaseVirtualDevice& operator=(const BaseVirtualDevice& other) = delete;

    BaseVirtualDevice(BaseVirtualDevice&& other) noexcept;
    BaseVirtualDevice& operator=(BaseVirtualDevice&& other) noexcept;

    virtual ~BaseVirtualDevice() = default;

    void OnChangeApplicationFocus();

    void SetProfile(std::unordered_map<Code, KeyInputStrategy>&& keyInputsProfile,
        std::unordered_map<Code, RelativeInput>&& relativeInputsProfile);

    virtual void CreateProfile() = 0;

    void ChangeCurrentSubProfile(uint8_t subProfileIndex);

    virtual bool HasInputRegistered(const InputEvent& inputEvent) = 0;

    virtual void ExecuteInput(DeviceId deviceId, const InputEvent& inputEvent) = 0;

    virtual void Emit(const InputEvent& inputEvent) = 0;

    virtual void Synchronize() = 0;

    virtual void Destroy() = 0;

protected:

    void UpdateCodesBindings() const;

    std::unique_ptr<KeyProfile> _keyProfile {nullptr};

    std::unique_ptr<RelativeProfile> _relativeProfile {nullptr};

    uint8_t _currentSubProfileIndex {0};
};