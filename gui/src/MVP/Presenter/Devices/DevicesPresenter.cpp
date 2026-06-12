#include "MVP/Presenter/Devices/DevicesPresenter.h"

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

DevicesPresenter::DevicesPresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{
    DevicesNotifications devicesNotificationsCount {DevicesNotifications::COUNT};

    for (DevicesNotifications i{DevicesNotifications::DEVICES_UPDATE}; i != devicesNotificationsCount; ++i)
    {
        _devicesNotifications.AddEntry(i);
    }

    _serviceModel.SubscribeToDevices([&](std::vector<DeviceInfo> devices)
    {
        _devices = std::move(devices);

        _recyclerViewPresenter.SetListLength(_devices.size());

        _devicesNotifications.TriggerNotification(DevicesNotifications::DEVICES_UPDATE);
    });
}

void DevicesPresenter::Restart()
{
    _recyclerViewPresenter.Reset();
}

void DevicesPresenter::SetRecyclerViewHeight(float recyclerViewHeight)
{
    _recyclerViewPresenter.SetRecyclerViewHeight(recyclerViewHeight);
}

void DevicesPresenter::SetViewsPerRow(uint8_t viewsPerRow)
{
    _recyclerViewPresenter.SetViewsPerRow(viewsPerRow);
}

void DevicesPresenter::SetItemHeight(float itemHeight)
{
    _recyclerViewPresenter.SetItemHeight(itemHeight);
}

void DevicesPresenter::SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _recyclerViewPresenter.SetRecycleViewVisibleItemsCount(visibleItemsCount);
}

void DevicesPresenter::SetRecyclerViewBufferRows(uint8_t bufferRows)
{
    _recyclerViewPresenter.SetRecyclerViewBufferRows(bufferRows);
}

void DevicesPresenter::OnScroll(float scrollValue)
{
    _recyclerViewPresenter.OnScroll(scrollValue);

    _devicesNotifications.TriggerNotification(DevicesNotifications::SCROLL_UPDATE);
}

float DevicesPresenter::GetCurrentScroll() const
{
    return _recyclerViewPresenter.GetCurrentScroll();
}

std::vector<ButtonInfo> DevicesPresenter::GetVisibleButtons() const
{
    std::vector<uint8_t> visibleItemsIndex {_recyclerViewPresenter.GetVisibleItemsIndex()};

    size_t visibleItemsIndexCount {visibleItemsIndex.size()};

    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(visibleItemsIndexCount);

    for (size_t i{0}; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        buttonsInfo.emplace_back(_devices.at(index).name, index);
    }

    return buttonsInfo;
}

bool DevicesPresenter::IsFirstItemPresent() const
{
    return _recyclerViewPresenter.IsFirstItemPresent();
}

bool DevicesPresenter::IsLastItemPresent() const
{
    return _recyclerViewPresenter.IsLastItemPresent();
}

void DevicesPresenter::OnPressReloadButton() const
{
    _serviceModel.RefreshDevicesList();
}

void DevicesPresenter::OnPressRecycleViewButton(uint8_t index) const
{
    DrawManager::GetInstance().EnableDeviceProfilesView(_devices.at(index).name);
}

std::weak_ptr<std::function<void()>> DevicesPresenter::SubscribeToDevicesNotifications(
    DevicesNotifications devicesNotification, std::function<void()>&& action)
{
    return _devicesNotifications.Subscribe(devicesNotification, std::move(action));
}

void DevicesPresenter::UnsubscribeToDevicesNotifications(DevicesNotifications devicesNotification,
    std::weak_ptr<std::function<void()>>&& action)
{
    _devicesNotifications.Unsubscribe(devicesNotification, std::move(action));
}
