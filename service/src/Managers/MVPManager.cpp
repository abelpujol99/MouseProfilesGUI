#include "Managers/MVPManager.h"

#include "Managers/ThreadsManager.h"
#include "Managers/ProfileManager.h"
#include "Managers/SerializationManager.h"
#include "Managers/VirtualDeviceManager.h"

std::unique_ptr<MVPManager> MVPManager::_applicationManagerInstance = nullptr;

MVPManager::MVPManager()
{
    _devices = SerializationManager::GetInstance().DeserializeDevicesProfiles();

    _shouldRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldRunObserver->SetValue(true);

    _shouldGUIRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldGUIRunObserver->SetValue(true);

    _scrollWheelModeHidrawPath = "/sys/class/hidraw/hidraw0/device/scroll_mode";
}

MVPManager& MVPManager::GetInstance()
{
    if (!_applicationManagerInstance)
    {
        _applicationManagerInstance.reset(new MVPManager());
    }

    return *_applicationManagerInstance;
}

void MVPManager::Start()
{
#ifdef NDEBUG
    ProfileManager::GetInstance().OnChangeApplicationFocus();

    VirtualDeviceManager::GetInstance().CreateListeners();

#endif

    ThreadsManager::GetInstance().Start();

    //SerializationManager::GetInstance().SerializeDevices(_devices);
}

std::string MVPManager::GetPathToSwitchScrollMode() const
{
    return _scrollWheelModeHidrawPath;
}

std::weak_ptr<std::function<void(bool)>> MVPManager::SubscribeToShouldRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldRunObserver->Subscribe(std::move(action));
}

void MVPManager::UnsubscribeToShouldRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldRunObserver->Unsubscribe(std::move(action));
}

void MVPManager::SwitchShouldRun() const
{
    _shouldRunObserver->SetValue(false);
}

bool MVPManager::ShouldRun() const
{
    return _shouldRunObserver->GetValue();
}

std::weak_ptr<std::function<void(bool)>> MVPManager::SubscribeToShouldGUIRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldGUIRunObserver->Subscribe(std::move(action));
}

void MVPManager::UnsubscribeToShouldGUIRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldGUIRunObserver->Unsubscribe(std::move(action));
}

void MVPManager::SetEditingDeviceProfiles(std::string deviceName)
{
    if (!_devices.devicesProfiles.contains(deviceName))
    {
        _devices.devicesProfiles.emplace(deviceName, DeviceProfiles{});
    }

    _editingDeviceProfiles = &_devices.devicesProfiles.at(deviceName);
}

std::string MVPManager::CreateProfile()
{
    std::string profileName {"Profile "};
    profileName += std::to_string(_editingDeviceProfiles->profiles.size() + 1);

    Profile profile{};

    profile.isCurrentProfile = false;

    _editingDeviceProfiles->profiles.emplace(profileName, profile);

    return profileName;
}

void MVPManager::DeleteProfile(std::string profileName)
{
    _editingDeviceProfiles->profiles.erase(profileName);
}

void MVPManager::SetEditingProfile(std::string profileName)
{
    _editingProfile = &_editingDeviceProfiles->profiles.at(profileName);
}

void MVPManager::CreateSubProfile()
{
    _editingProfile->subProfiles.emplace_back();
}

void MVPManager::DeleteSubProfile(uint8_t index)
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

void MVPManager::SetEditingSubProfile(uint8_t index)
{
    _editingSubProfile = &_editingProfile->subProfiles.at(index);
}

void MVPManager::CreateCodeRemap(Code code, CodeRemap codeRemap)
{
    _editingSubProfile->codesRemaps.emplace(code, codeRemap);
}

void MVPManager::DeleteCodeRemap(Code code)
{
    _editingSubProfile->codesRemaps.erase(code);
}

std::unordered_map<std::string, Profile> MVPManager::GetDeviceProfiles(std::string deviceName)
{
    if (_devices.devicesProfiles.contains(deviceName))
    {
        return _devices.devicesProfiles.at(deviceName).profiles;
    }

    return {};
}

void MVPManager::StartGUI()
{
    /*WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetInitialSize(1500, 700);
    windowManager.Start();
    windowManager.Update();*/
}

void MVPManager::TurnOnGUI() const
{
    _shouldGUIRunObserver->SetValue(true);
}

void MVPManager::TurnOffGUI() const
{
    _shouldGUIRunObserver->SetValue(false);
    SerializationManager::GetInstance().SerializeDevices(_devices);
}
