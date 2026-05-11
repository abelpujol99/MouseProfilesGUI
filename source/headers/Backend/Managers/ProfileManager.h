#pragma once

#include <forward_list>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_set>

#include "Backend/CodeUsings.h"
#include "Backend/Input/Strategy/IInputCommandStrategy.h"

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

    void ChangeCurrentProfile(unsigned char profileIndex);

    void ChangeMouseInputState(IMouseInputState* mouseInputState);

    bool IsCodeInUse(Code code) const;

    void RegisterInput(Code code, int value) const;

    void UnsubscribeToActionsOnChangeProfile(const std::weak_ptr<std::function<void()>>& weakActionOnChangeProfile);

private:

    ProfileManager();

    void CreateProfile();

    void SetProfiles(std::unordered_map<Code, std::unique_ptr<IInputCommandStrategy>>&& inputStrategies);

    void UpdateCodesBindings();

    void MouseInputStateLoop(std::shared_ptr<bool> shouldKeepRun);

    static std::unique_ptr<ProfileManager> _profileManagerInstance;

    std::unordered_map<Code, std::unique_ptr<IInputCommandStrategy>> _inputStrategies;

    std::unordered_map<unsigned char, std::forward_list<Code>> _allProfilesCodes;

    std::unordered_set<Code> _currentProfileCodes;

    unsigned char _currentProfileIndex;

    IMouseInputState* _mouseInputState;

    std::vector<std::shared_ptr<std::function<void()>>> _actionsOnChangeProfile;

    mutable std::mutex _mutex;

    std::shared_ptr<bool> _shouldMouseInputLoopRun;
};