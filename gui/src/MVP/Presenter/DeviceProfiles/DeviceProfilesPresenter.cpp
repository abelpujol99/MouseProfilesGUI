#include "MVP/Presenter/DeviceProfiles/DeviceProfilesPresenter.h"

#include "Managers/View/DrawManager.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesNotifications.h"

DeviceProfilesPresenter::DeviceProfilesPresenter() : BasePresenter()
{
    DeviceProfilesNotifications devicesNotificationsCount {DeviceProfilesNotifications::COUNT};

    for (DeviceProfilesNotifications i{DeviceProfilesNotifications::DEVICES_UPDATE}; i != devicesNotificationsCount; ++i)
    {
        _deviceProfilesNotifications.AddEntry(i);
    }
}

void DeviceProfilesPresenter::SetRecyclerViewHeight(float recyclerViewHeight)
{
    _recyclerViewHeight = recyclerViewHeight;
}

void DeviceProfilesPresenter::SetViewsPerRow(uint8_t viewsPerRow)
{
    _viewsPerRow = viewsPerRow;
}

void DeviceProfilesPresenter::SetItemHeight(float itemHeight)
{
    _itemHeight = itemHeight;
}

void DeviceProfilesPresenter::SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _visibleItemsCount = visibleItemsCount;
}

void DeviceProfilesPresenter::SetRecyclerViewBufferRows(uint8_t bufferRows)
{
    _bufferRows = bufferRows;
}

void DeviceProfilesPresenter::Refresh()
{
}

void DeviceProfilesPresenter::OnPressBackButton()
{
    DrawManager::GetInstance().EnableDevicesView();
}

void DeviceProfilesPresenter::CalculateMaxScroll()
{
    _maxScroll = std::ceil(static_cast<float>(_profiles.size()) / static_cast<float>(_viewsPerRow)) * _itemHeight - _recyclerViewHeight;

    if (_maxScroll >= 0)
    {
        return;
    }

    _maxScroll = 0;
}

void DeviceProfilesPresenter::OnScroll(float scrollValue)
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

    _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::SCROLL_UPDATE);
}

void DeviceProfilesPresenter::UpdateRecycleViewDataDisplay()
{
    _firstItemToShowIndex = Utilities::Math::Clamp(
        std::ceil(_currentScroll / _itemHeight) * _viewsPerRow - _bufferRows * _viewsPerRow, 0, _profiles.size() - _visibleItemsCount);
}

float DeviceProfilesPresenter::GetCurrentScroll() const
{
    return _currentScroll;
}

std::vector<ButtonInfo> DeviceProfilesPresenter::GetVisibleButtons() const
{
    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(_visibleItemsCount);

    for (int i{_firstItemToShowIndex}; i < _firstItemToShowIndex + _visibleItemsCount && i < _profiles.size(); ++i)
    {
        buttonsInfo.emplace_back(_profiles.at(i).name, i);
    }

    return buttonsInfo;
}

bool DeviceProfilesPresenter::IsFirstItemPresent() const
{
    return _firstItemToShowIndex * _viewsPerRow == 0;
}

bool DeviceProfilesPresenter::IsLastItemPresent() const
{
    return _profiles.size() < _viewsPerRow || _firstItemToShowIndex + _visibleItemsCount == _profiles.size();
}

void DeviceProfilesPresenter::OnPressRecycleViewButton(uint8_t index) const
{
    //TODO
}

std::weak_ptr<std::function<void()>> DeviceProfilesPresenter::SubscribeToDeviceProfilesNotifications(
    DeviceProfilesNotifications devicesNotification, std::function<void()>&& action)
{
    return _deviceProfilesNotifications.Subscribe(devicesNotification, std::move(action));
}

void DeviceProfilesPresenter::UnsubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification,
    std::weak_ptr<std::function<void()>>&& action)
{
    _deviceProfilesNotifications.Unsubscribe(devicesNotification, std::move(action));
}
