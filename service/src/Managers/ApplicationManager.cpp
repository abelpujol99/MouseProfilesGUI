#include "Managers/ApplicationManager.h"

#include "Managers/SerializationManager.h"
#include "Managers/DevicesManager.h"

ApplicationManager::ApplicationManager() : _devices(SerializationManager::GetInstance().DeserializeDevicesProfiles())
{}

ApplicationManager& ApplicationManager::GetInstance()
{
    static ApplicationManager _applicationManagerInstance;

    return _applicationManagerInstance;
}

void ApplicationManager::Start()
{
//#ifdef NDEBUG

    DevicesManager& devicesManagerInstance {DevicesManager::GetInstance()};

    devicesManagerInstance.Start();

    devicesManagerInstance.Loop();

//#endif

    //SerializationManager::GetInstance().SerializeDevices(_devices);
}

void ApplicationManager::Shutdown()
{
    DevicesManager::GetInstance().RemoveVirtualDevices();
    DevicesManager::GetInstance().StopTriggering();
}

/*void ApplicationManager::SetEditingDeviceProfiles(std::string deviceName)
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

    _editingDeviceProfiles->profiles.emplace_back(profile);

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
}*/