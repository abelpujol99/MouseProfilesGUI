#pragma once

#include "Serialization/DeviceProfiles.h"
#include "Strategies/ReadDevicesStrategy/IReadDevicesStrategy.h"
#include "Utilities/Event/SingleEventBus.h"
#include "Utilities/Structs/DeviceInfo.h"

class ServiceModel
{
public:

    ServiceModel();

    void RefreshDevicesList();

    void RetrieveDeviceProfiles(std::string deviceName);

    void AddProfile(Profile&& profile);

    void RefreshProfile(uint8_t profileIndex);

    void AddSubProfile(uint8_t profileIndex, SubProfile&& subProfile);

    void RefreshSubProfile(uint8_t profileIndex, uint8_t subProfileIndex);

    void AddCodeRemap(uint8_t profileIndex, uint8_t subProfileIndex, CodeRemap&& codeRemap);

    std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>> SubscribeToDevices(std::function<void(std::vector<DeviceInfo>)>&& action);
    void UnsubscribeFromDevices(std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>>&& action);

    std::weak_ptr<std::function<void(DeviceProfiles)>> SubscribeToDeviceProfiles(std::function<void(DeviceProfiles)>&& action);
    void UnsubscribeFromDeviceProfiles(std::weak_ptr<std::function<void(DeviceProfiles)>>&& action);

    std::weak_ptr<std::function<void(Profile)>> SubscribeToProfile(std::function<void(Profile)>&& action);
    void UnsubscribeFromProfile(std::weak_ptr<std::function<void(Profile)>>&& action);

    std::weak_ptr<std::function<void(std::string)>> SubscribeToProfileName(std::function<void(std::string)>&& action);
    void UnsubscribeFromProfileName(std::weak_ptr<std::function<void(std::string)>>&& action);

    std::weak_ptr<std::function<void(SubProfile)>> SubscribeToSubProfile(std::function<void(SubProfile)>&& action);
    void UnsubscribeFromSubProfile(std::weak_ptr<std::function<void(SubProfile)>>&& action);

    std::weak_ptr<std::function<void(CodeRemap)>> SubscribeToCodeRemap(std::function<void(CodeRemap)>&& action);
    void UnsubscribeFromCodeRemap(std::weak_ptr<std::function<void(CodeRemap)>>&& action);


private:

    std::unique_ptr<IReadDevicesStrategy> _readDevices;

    SingleEventBus<std::vector<DeviceInfo>> _devices;

    DeviceProfiles _deviceProfiles;

    SingleEventBus<DeviceProfiles> _deviceProfilesEvent;

    SingleEventBus<Profile> _profileEvent;

    SingleEventBus<std::string> _profileNameEvent;

    SingleEventBus<SubProfile> _subProfileEvent;

    SingleEventBus<CodeRemap> _codeRemapEvent;
};