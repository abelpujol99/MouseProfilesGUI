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

    std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>> SubscribeToDevices(std::function<void(std::vector<DeviceInfo>)>&& action);
    void UnsubscribeFromDevices(std::weak_ptr<std::function<void(std::vector<DeviceInfo>)>>&& action);

    void RetrieveDeviceProfiles(std::string deviceName);

    std::weak_ptr<std::function<void(DeviceProfiles)>> SubscribeToDeviceProfiles(std::function<void(DeviceProfiles)>&& action);
    void UnsubscribeFromDeviceProfiles(std::weak_ptr<std::function<void(DeviceProfiles)>>&& action);

private:

    std::unique_ptr<IReadDevicesStrategy> _readDevices;

    SingleEventBus<std::vector<DeviceInfo>> _devices;

    SingleEventBus<DeviceProfiles> _deviceProfiles;

};