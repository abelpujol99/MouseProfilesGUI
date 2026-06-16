#include "Managers/ApplicationManager.h"

#include "Managers/ThreadsManager.h"
#include "Managers/ProfileManager.h"
#include "Managers/SerializationManager.h"
#include "Managers/VirtualDeviceManager.h"

std::unique_ptr<ApplicationManager> ApplicationManager::_applicationManagerInstance = nullptr;

ApplicationManager::ApplicationManager()
{
    _devices = SerializationManager::GetInstance().DeserializeDevicesProfiles();

    _shouldRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldRunObserver->SetValue(true);

    _shouldGUIRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldGUIRunObserver->SetValue(true);

    _scrollWheelModeHidrawPath = "/sys/class/hidraw/hidraw0/device/scroll_mode";
}

ApplicationManager& ApplicationManager::GetInstance()
{
    if (!_applicationManagerInstance)
    {
        _applicationManagerInstance.reset(new ApplicationManager());
    }

    return *_applicationManagerInstance;
}

void ApplicationManager::Start()
{
#ifdef NDEBUG
    ProfileManager::GetInstance().OnChangeApplicationFocus();

    VirtualDeviceManager::GetInstance().CreateListeners();

#endif

    ThreadsManager::GetInstance().Start();

    //SerializationManager::GetInstance().SerializeDevices(_devices);
}

std::string ApplicationManager::GetPathToSwitchScrollMode() const
{
    return _scrollWheelModeHidrawPath;
}

std::weak_ptr<std::function<void(bool)>> ApplicationManager::SubscribeToShouldRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldRunObserver->Subscribe(std::move(action));
}

void ApplicationManager::UnsubscribeToShouldRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldRunObserver->Unsubscribe(std::move(action));
}

void ApplicationManager::SwitchShouldRun() const
{
    _shouldRunObserver->SetValue(false);
}

bool ApplicationManager::ShouldRun() const
{
    return _shouldRunObserver->GetValue();
}

std::weak_ptr<std::function<void(bool)>> ApplicationManager::SubscribeToShouldGUIRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldGUIRunObserver->Subscribe(std::move(action));
}

void ApplicationManager::UnsubscribeToShouldGUIRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldGUIRunObserver->Unsubscribe(std::move(action));
}

void ApplicationManager::SetEditingDeviceProfiles(std::string deviceName)
{
    if (!_devices.devicesProfiles.contains(deviceName))
    {
        _devices.devicesProfiles.emplace(deviceName, DeviceProfiles{});
    }

    _editingDeviceProfiles = &_devices.devicesProfiles.at(deviceName);
}

std::string ApplicationManager::CreateProfile()
{
    std::string profileName {"Profile "};
    profileName += std::to_string(_editingDeviceProfiles->profiles.size() + 1);

    Profile profile{};

    profile.isCurrentProfile = false;

    _editingDeviceProfiles->profiles.emplace(profileName, profile);

    return profileName;
}

void ApplicationManager::DeleteProfile(std::string profileName)
{
    _editingDeviceProfiles->profiles.erase(profileName);
}

void ApplicationManager::SetEditingProfile(std::string profileName)
{
    _editingProfile = &_editingDeviceProfiles->profiles.at(profileName);
}

void ApplicationManager::CreateSubProfile()
{
    _editingProfile->subProfiles.emplace_back();
}

void ApplicationManager::DeleteSubProfile(uint8_t index)
{
    uint8_t count{0};

    auto itEnd {_editingProfile->subProfiles.cend()};

    for (auto it{_editingProfile->subProfiles.begin()}; it != itEnd; ++it)
    {
        if (count != index)
        {
            count++;
            continue;
        }

        _editingProfile->subProfiles.erase(it);
    }
}

void ApplicationManager::SetEditingSubProfile(uint8_t index)
{
    _editingSubProfile = &_editingProfile->subProfiles.at(index);
}

void ApplicationManager::CreateCodeRemap(Code code, CodeRemap codeRemap)
{
    _editingSubProfile->codesRemaps.emplace(code, codeRemap);
}

void ApplicationManager::DeleteCodeRemap(Code code)
{
    _editingSubProfile->codesRemaps.erase(code);
}

std::unordered_map<std::string, Profile> ApplicationManager::GetDeviceProfiles(std::string deviceName)
{
    if (_devices.devicesProfiles.contains(deviceName))
    {
        return _devices.devicesProfiles.at(deviceName).profiles;
    }

    return {};
}

void ApplicationManager::StartGUI()
{
    /*WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetInitialSize(1500, 700);
    windowManager.Start();
    windowManager.Update();*/
}

void ApplicationManager::TurnOnGUI() const
{
    _shouldGUIRunObserver->SetValue(true);
}

void ApplicationManager::TurnOffGUI() const
{
    _shouldGUIRunObserver->SetValue(false);
    SerializationManager::GetInstance().SerializeDevices(_devices);
}
