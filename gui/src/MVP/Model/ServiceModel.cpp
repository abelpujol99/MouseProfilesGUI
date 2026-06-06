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
