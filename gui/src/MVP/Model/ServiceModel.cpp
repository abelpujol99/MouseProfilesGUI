#include "MVP/Model/ServiceModel.h"

#include "Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"

ServiceModel::ServiceModel() : _readDevices(std::make_unique<ReadLinuxDevices>())
{}

void ServiceModel::RefreshDevicesList()
{
    _devices.SetValue(_readDevices->ReturnDevices());
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

    DeviceProfiles deviceProfiles;

    deviceProfiles.profiles.push_back(profile);

    _deviceProfiles.SetValue(deviceProfiles);
}

std::weak_ptr<std::function<void(DeviceProfiles)>> ServiceModel::SubscribeToDeviceProfiles(
    std::function<void(DeviceProfiles)>&& action)
{
    return _deviceProfiles.Subscribe(std::move(action));
}

void ServiceModel::UnsubscribeFromDeviceProfiles(std::weak_ptr<std::function<void(DeviceProfiles)>>&& action)
{
    _deviceProfiles.Unsubscribe(std::move(action));
}
