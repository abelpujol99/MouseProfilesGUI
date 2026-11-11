#include "Device/VirtualDevice/BaseVirtualDevice.h"

BaseVirtualDevice::BaseVirtualDevice(InputType inputType)
{
    if (HasInputType(inputType, InputType::KEY))
    {
        _keyProfile = std::make_unique<KeyProfile>();
    }

    if (HasInputType(inputType, InputType::RELATIVE))
    {
        _relativeProfile = std::make_unique<RelativeProfile>();
    }
}

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

    _allSubProfilesCodes.try_emplace(1, codes);

    CreateProfile();*/
}

void BaseVirtualDevice::SetProfile(std::unordered_map<Code, KeyInputStrategy>&& keyInputsProfile,
    std::unordered_map<Code, RelativeInput>&& relativeInputsProfile)
{
    if (_keyProfile != nullptr)
    {
        _keyProfile->inputs = std::move(keyInputsProfile);
    }

    if (_relativeProfile != nullptr)
    {
        _relativeProfile->inputs = std::move(relativeInputsProfile);
    }

    ChangeCurrentSubProfile(0);
}

void BaseVirtualDevice::ChangeCurrentSubProfile(uint8_t subProfileIndex)
{
    _currentSubProfileIndex = subProfileIndex;

    UpdateCodesBindings();
}

void BaseVirtualDevice::UpdateCodesBindings() const
{
    const bool& keyProfileExists {_keyProfile != nullptr};
    const bool& relativeProfileExists {_keyProfile != nullptr};

    const std::forward_list<Code>& keyCodes {_keyProfile->subProfilesCodes.at(_currentSubProfileIndex)};
    const std::forward_list<RelativeCode>& relativeCodes {_relativeProfile->subProfilesCodes.at(_currentSubProfileIndex)};

    if (keyProfileExists)
    {
        _keyProfile->currentInputs.clear();
    }

    if (relativeProfileExists)
    {
        _relativeProfile->currentInputs.clear();
    }

    if (keyProfileExists)
    {
        for (auto& code : keyCodes)
        {
            _keyProfile->currentInputs.emplace(code);

            _keyProfile->inputs.at(code).ChangeProfile(_currentSubProfileIndex);
        }
    }

    if (relativeProfileExists)
    {
        for (auto& relativeCode : relativeCodes)
        {
            std::array<bool, 2> inputFlags {relativeCode.hasNegativeInput, relativeCode.hasPositiveInput};

            _relativeProfile->currentInputs.emplace(relativeCode.code, inputFlags);

            _relativeProfile->inputs.at(relativeCode.code).ChangeProfile(_currentSubProfileIndex);
        }
    }
}
