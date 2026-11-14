#include "Device/VirtualDevice/BaseVirtualDevice.h"

BaseVirtualDevice::BaseVirtualDevice(BaseVirtualDevice&& other) noexcept
{
    _keyProfile = std::move(other._keyProfile);
    _relativeProfile = std::move(other._relativeProfile);
    _currentSubProfileIndex = other._currentSubProfileIndex;
}

BaseVirtualDevice& BaseVirtualDevice::operator=(BaseVirtualDevice&& other) noexcept
{
    if (this != &other)
    {
        _keyProfile = std::move(other._keyProfile);
        _relativeProfile = std::move(other._relativeProfile);
        _currentSubProfileIndex = other._currentSubProfileIndex;
    }

    return *this;
}

void BaseVirtualDevice::OnChangeApplicationFocus()
{
    //TODO POPULATE ALL SUB PROFILE CODES

    //TODO CATCH ON APPLICATION FOCUS FOR EACH LINUX ENVIRONMENT

    //TODO READ CONFIG FILE

    /*_allSubProfilesCodes.clear();

    std::forward_list<Code> codes;

    //codes.emplace_front(8); //SCROLL
    codes.emplace_front(32); //LEFT TILT
    codes.emplace_front(64); //RIGHT TILT
    codes.emplace_front(80); //HIDDEN BUTTON
    codes.emplace_front(81); //TASK BUTTON
    codes.emplace_front(82); //BACK BUTTON
    codes.emplace_front(84); //FORWARD BUTTON
    codes.emplace_front(275); //SIDE BUTTON
    codes.emplace_front(276); //EXTRA BUTTON

    _allSubProfilesCodes.try_emplace(0, codes);

    codes.clear();

    codes.emplace_front(272); //LEFT BUTTON
    codes.emplace_front(273); //RIGHT BUTTON
    codes.emplace_front(275); //SIDE BUTTON

    _allSubProfilesCodes.try_emplace(1, codes);*/
}

void BaseVirtualDevice::SetKeyProfile(std::unique_ptr<KeyProfile>&& keyProfile)
{
    _keyProfile = std::move(keyProfile);

    UpdateKeyCodesBindings();
}

void BaseVirtualDevice::SetRelativeProfile(std::unique_ptr<RelativeProfile>&& relativeProfile)
{
    _relativeProfile = std::move(relativeProfile);

    UpdateRelativeCodesBindings();
}

void BaseVirtualDevice::ChangeCurrentSubProfile(uint8_t subProfileIndex)
{
    _currentSubProfileIndex = subProfileIndex;

    UpdateCodesBindings();
}

void BaseVirtualDevice::UpdateCodesBindings() const
{
    if (_keyProfile != nullptr)
    {
        UpdateKeyCodesBindings();
    }

    if (_relativeProfile != nullptr)
    {
        UpdateRelativeCodesBindings();
    }
}

void BaseVirtualDevice::UpdateKeyCodesBindings() const
{
    _keyProfile->currentInputs.clear();

    const std::forward_list<Code>& keyCodes {_keyProfile->subProfilesCodes.at(_currentSubProfileIndex)};

    for (auto& code : keyCodes)
    {
        _keyProfile->currentInputs.emplace(code);

        _keyProfile->inputs.at(code).ChangeProfile(_currentSubProfileIndex);
    }
}

void BaseVirtualDevice::UpdateRelativeCodesBindings() const
{
    const std::forward_list<RelativeCode>& relativeCodes {_relativeProfile->subProfilesCodes.at(_currentSubProfileIndex)};

    for (auto& relativeCode : relativeCodes)
    {
        std::array<bool, 2> inputFlags {relativeCode.hasNegativeInput, relativeCode.hasPositiveInput};

        _relativeProfile->currentInputs.emplace(relativeCode.code, inputFlags);

        _relativeProfile->inputs.at(relativeCode.code).ChangeProfile(_currentSubProfileIndex);
    }
}
