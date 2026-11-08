#pragma once

#include <forward_list>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_set>

#include "CodeUsings.h"
#include "Input/InputEvent.h"
#include "Input/Relative/RelativeInput.h"
#include "Input/Strategy/IInputCommandStrategy.h"
#include "Input/Strategy/KeyInputStrategy.h"
#include "Trigger/TriggerBus.h"
#include "Serialization/RelativeCode.h"

class IMouseInputState;

class ProfileManager
{
public:

    ~ProfileManager() = default;

    ProfileManager(const ProfileManager& other) = delete;
    ProfileManager& operator=(const ProfileManager& other) = delete;
    ProfileManager(ProfileManager&& other) = delete;
    ProfileManager& operator=(ProfileManager&& other) = delete;

    static ProfileManager& GetInstance();

    void OnChangeApplicationFocus();

    void ChangeCurrentSubProfile(uint8_t subProfileIndex);

    bool CanRegisterInput(InputEvent inputEvent);

    std::weak_ptr<std::function<void()>> SubscribeToTriggerKeyHoldCommand(std::function<void()>&& action);

    void UnsubscribeToTriggerKeyHoldCommand(std::weak_ptr<std::function<void()>>&& action);

private:

    ProfileManager();

    void CreateProfile();

    void SetProfile(std::unordered_map<Code, KeyInputStrategy>&& keyInputsProfile,
        std::unordered_map<Code, RelativeInput>&& relativeInputsProfile);

    void UpdateCodesBindings();

    void TriggerHoldCommands();

    std::unordered_map<Code, KeyInputStrategy> _keyInputs;

    std::unordered_map<Code, RelativeInput> _relativeInputs;

    std::unordered_map<uint8_t, std::forward_list<Code>> _subProfilesKeyCodes;

    std::unordered_map<uint8_t, std::forward_list<RelativeCode>> _subProfilesRelativeCodes;

    std::unordered_set<Code> _currentKeyInputs;

    std::unordered_map<Code, bool[2]> _currentRelativeInputs;

    uint8_t _currentSubProfileIndex;

    TriggerBus _triggerKeyHoldCommandEvent;

    mutable std::mutex _mutex;
};