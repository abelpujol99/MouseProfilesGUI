#include "MVP/Presenter/Devices/DevicesPresenter.h"

#include <cmath>
#include <utility>

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"
#include "Utilities/Math.h"

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

        CalculateMaxScroll();

        _devicesNotifications.TriggerNotification(DevicesNotifications::DEVICES_UPDATE);
    });
}

void DevicesPresenter::SetRecyclerViewHeight(float recyclerViewHeight)
{
    _recyclerViewHeight = recyclerViewHeight;
}

void DevicesPresenter::SetViewsPerRow(uint8_t viewsPerRow)
{
    _viewsPerRow = viewsPerRow;
}

void DevicesPresenter::SetItemHeight(float itemHeight)
{
    _itemHeight = itemHeight;
}

void DevicesPresenter::SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _visibleItemsCount = visibleItemsCount;
}

void DevicesPresenter::SetRecyclerViewBufferRows(uint8_t bufferRows)
{
    _bufferRows = bufferRows;
}

void DevicesPresenter::OnPressReloadButton() const
{
    _serviceModel.RefreshDevicesList();
}

void DevicesPresenter::CalculateMaxScroll()
{
    _maxScroll = std::ceil(static_cast<float>(_devices.size()) / static_cast<float>(_viewsPerRow)) * _itemHeight - _recyclerViewHeight;

    if (_maxScroll >= 0)
    {
        return;
    }

    _maxScroll = 0;
}

void DevicesPresenter::OnScroll(float scrollValue)
{
    scrollValue = Utilities::Math::Clamp(scrollValue, -_itemHeight, _itemHeight);

    float newScrollValue {_currentScroll + scrollValue};

    if (newScrollValue < 0)
    {
        if (_currentScroll == 0)
        {
            return;
        }

        newScrollValue = 0;
    }
    else if (newScrollValue > _maxScroll)
    {
        if (_currentScroll == _maxScroll)
        {
            return;
        }

        newScrollValue = _maxScroll;
    }

    _currentScroll = newScrollValue;

    UpdateRecycleViewDataDisplay();

    _devicesNotifications.TriggerNotification(DevicesNotifications::SCROLL_UPDATE);
}

void DevicesPresenter::UpdateRecycleViewDataDisplay()
{
    _firstItemToShowIndex = Utilities::Math::Clamp(
        std::ceil(_currentScroll / _itemHeight) * _viewsPerRow - _bufferRows * _viewsPerRow, 0, _devices.size() - _visibleItemsCount);
}

float DevicesPresenter::GetCurrentScroll() const
{
    return _currentScroll;
}

std::vector<ButtonInfo> DevicesPresenter::GetVisibleButtons() const
{
    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(_visibleItemsCount);

    for (int i{_firstItemToShowIndex}; i < _firstItemToShowIndex + _visibleItemsCount && i < _devices.size(); ++i)
    {
        buttonsInfo.emplace_back(_devices.at(i).name, i);
    }

    return buttonsInfo;
}

bool DevicesPresenter::IsFirstItemPresent() const
{
    return _firstItemToShowIndex * _viewsPerRow == 0;
}

bool DevicesPresenter::IsLastItemPresent() const
{
    return _devices.size() < _viewsPerRow || _firstItemToShowIndex + _visibleItemsCount == _devices.size();
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
