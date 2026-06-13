#include "MVP/Model/ServiceModel.h"

#include "Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"

ServiceModel::ServiceModel() : _readDevices(std::make_unique<ReadLinuxDevices>())
{}

void ServiceModel::RefreshDevicesList()
{
    _devices.SendValue(_readDevices->ReturnDevices());
}

void ServiceModel::RetrieveDeviceProfiles(std::string deviceName)
{
    //TODO RETRIEVE PROFILES FROM GIVEN DEVICE

    std::vector<EmitData> emitsData;

    emitsData.emplace_back(EmitData{MOUSE, {0, 256, 1}});

    CodeRemap codeRemap {32, CommandType::SWITCH_TO_SUB_PROFILE, emitsData, 1};

    SubProfile subProfile;

    subProfile.codesRemaps.push_back(codeRemap);

    Profile profile;

    profile.name = "Profile 1";

    profile.isCurrentProfile = false;

    profile.subProfiles.push_back(subProfile);

    _deviceProfiles.profiles.push_back(profile);

    _deviceProfilesEvent.SendValue(_deviceProfiles);
}

void ServiceModel::AddProfile(Profile&& profile)
{
    _deviceProfiles.profiles.push_back(std::move(profile));

    _deviceProfilesEvent.SendValue(_deviceProfiles);
}

void ServiceModel::RefreshProfile(uint8_t profileIndex)
{
    _profileEvent.SendValue(_deviceProfiles.profiles.at(profileIndex));

    _profileNameEvent.SendValue(_deviceProfiles.profiles.at(profileIndex).name);
}

void ServiceModel::AddSubProfile(uint8_t profileIndex, SubProfile&& subProfile)
{
    Profile& profile {_deviceProfiles.profiles.at(profileIndex)};

    profile.subProfiles.push_back(std::move(subProfile));

    _profileEvent.SendValue(profile);
}

void ServiceModel::RefreshSubProfile(uint8_t profileIndex, uint8_t subProfileIndex)
{
    _subProfileEvent.SendValue(_deviceProfiles.profiles.at(profileIndex).subProfiles.at(subProfileIndex));
}

void ServiceModel::AddCodeRemap(uint8_t profileIndex, uint8_t subProfileIndex, CodeRemap&& codeRemap)
{
    SubProfile& subProfile {_deviceProfiles.profiles.at(profileIndex).subProfiles.at(subProfileIndex)};

    subProfile.codesRemaps.push_back(std::move(codeRemap));

    _subProfileEvent.SendValue(subProfile);
}

std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>> ServiceModel::SubscribeToDevices(
    std::function<void(std::vector<DeviceInfo>)>&& action)
{
    return _devices.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromDevices(std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>>&& action)
{
    _devices.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(DeviceProfiles)>> ServiceModel::SubscribeToDeviceProfiles(
    std::function<void(DeviceProfiles)>&& action)
{
    return _deviceProfilesEvent.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromDeviceProfiles(std::weak_ptr<std::function<void(DeviceProfiles)>>&& action)
{
    _deviceProfilesEvent.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(Profile)>> ServiceModel::SubscribeToProfile(std::function<void(Profile)>&& action)
{
    return _profileEvent.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromProfile(std::weak_ptr<std::function<void(Profile)>>&& action)
{
    _profileEvent.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(std::string)>> ServiceModel::SubscribeToProfileName(
    std::function<void(std::string)>&& action)
{
    return _profileNameEvent.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromProfileName(std::weak_ptr<std::function<void(std::string)>>&& action)
{
    _profileNameEvent.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(SubProfile)>> ServiceModel::SubscribeToSubProfile(
    std::function<void(SubProfile)>&& action)
{
    return _subProfileEvent.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromSubProfile(std::weak_ptr<std::function<void(SubProfile)>>&& action)
{
    _subProfileEvent.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(CodeRemap)>> ServiceModel::SubscribeToCodeRemap(
    std::function<void(CodeRemap)>&& action)
{
    return _codeRemapEvent.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromCodeRemap(std::weak_ptr<std::function<void(CodeRemap)>>&& action)
{
    _codeRemapEvent.Unsubscribe(std::move(action));
}