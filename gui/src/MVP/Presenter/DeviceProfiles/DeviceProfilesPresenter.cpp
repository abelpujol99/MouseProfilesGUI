#include "MVP/Presenter/DeviceProfiles/DeviceProfilesPresenter.h"

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

DeviceProfilesPresenter::DeviceProfilesPresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{
    DeviceProfilesNotifications devicesNotificationsCount {DeviceProfilesNotifications::COUNT};

    for (DeviceProfilesNotifications i{DeviceProfilesNotifications::PROFILES_UPDATE}; i != devicesNotificationsCount; ++i)
    {
        _deviceProfilesNotifications.AddEntry(i);
    }

    _serviceModel.SubscribeToDeviceProfiles([&](DeviceProfiles deviceProfiles)
    {
        _deviceProfiles = std::move(deviceProfiles.profiles);

        _deviceProfiles.emplace_back("+", false, std::vector<SubProfile>{});

        _recyclerViewPresenter.SetListLength(_deviceProfiles.size());

        _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::CURRENT_PROFILE_UPDATE);
        _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::PROFILES_UPDATE);
    });
}

void DeviceProfilesPresenter::SetDeviceName(std::string deviceName)
{
    if (_deviceName == deviceName)
    {
        return;
    }

    _serviceModel.RetrieveDeviceProfiles(deviceName);

    _deviceName = std::move(deviceName);
}

void DeviceProfilesPresenter::Restart()
{
    _recyclerViewPresenter.Reset();
}

void DeviceProfilesPresenter::SetRecyclerViewHeight(float recyclerViewHeight)
{
    _recyclerViewPresenter.SetRecyclerViewHeight(recyclerViewHeight);
}

void DeviceProfilesPresenter::SetViewsPerRow(uint8_t viewsPerRow)
{
    _recyclerViewPresenter.SetViewsPerRow(viewsPerRow);
}

void DeviceProfilesPresenter::SetItemHeight(float itemHeight)
{
    _recyclerViewPresenter.SetItemHeight(itemHeight);
}

void DeviceProfilesPresenter::SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _recyclerViewPresenter.SetRecycleViewVisibleItemsCount(visibleItemsCount);
}

void DeviceProfilesPresenter::SetRecyclerViewBufferRows(uint8_t bufferRows)
{
    _recyclerViewPresenter.SetRecyclerViewBufferRows(bufferRows);
}

void DeviceProfilesPresenter::OnScroll(float scrollValue)
{
    _recyclerViewPresenter.OnScroll(scrollValue);

    _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::SCROLL_UPDATE);
}

float DeviceProfilesPresenter::GetCurrentScroll() const
{
    return _recyclerViewPresenter.GetCurrentScroll();
}

std::string DeviceProfilesPresenter::GetActiveProfileName() const
{
    if (_currentDeviceProfileIndex != -1)
    {
        return _deviceProfiles.at(_currentDeviceProfileIndex).name;
    }

    return "";
}

std::vector<ButtonInfo> DeviceProfilesPresenter::GetVisibleButtons() const
{
    std::vector<uint8_t> visibleItemsIndex {_recyclerViewPresenter.GetVisibleItemsIndex()};

    size_t visibleItemsIndexCount {visibleItemsIndex.size()};

    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(visibleItemsIndexCount);

    for (size_t i{0}; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        buttonsInfo.emplace_back(_deviceProfiles.at(index).name, index);
    }

    return buttonsInfo;
}

bool DeviceProfilesPresenter::IsFirstItemPresent() const
{
    return _recyclerViewPresenter.IsFirstItemPresent();
}

bool DeviceProfilesPresenter::IsLastItemPresent() const
{
    return _recyclerViewPresenter.IsLastItemPresent();
}

void DeviceProfilesPresenter::OnPressBackButton()
{
    DrawManager::GetInstance().EnableDevicesView();
}

void DeviceProfilesPresenter::OnPressEditButton()
{
    DrawManager::GetInstance().EnableProfileView(_deviceName, _currentDeviceProfileIndex);
}

void DeviceProfilesPresenter::OnPressUnloadButton()
{
    _currentDeviceProfileIndex = {-1};

    _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::CURRENT_PROFILE_UPDATE);
}

void DeviceProfilesPresenter::OnPressRecycleViewButton(uint8_t index)
{
    if (index == _deviceProfiles.size() - 1)
    {
        AddProfile();
        return;
    }

    DrawManager::GetInstance().EnableProfileView(_deviceName, index);
}

void DeviceProfilesPresenter::AddProfile() const
{
    std::string profileName {"Profile "};

    profileName += std::to_string(_deviceProfiles.size());

    Profile profile {profileName, false, std::vector<SubProfile>{}};

    _serviceModel.AddProfile(std::move(profile));
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