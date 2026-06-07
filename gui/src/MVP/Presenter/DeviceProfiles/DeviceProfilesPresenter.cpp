#include "MVP/Presenter/DeviceProfiles/DeviceProfilesPresenter.h"

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesNotifications.h"

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

        CalculateMaxScroll();

        _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::CURRENT_PROFILE_UPDATE);
        _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::PROFILES_UPDATE);
    });
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

void DeviceProfilesPresenter::SetDeviceName(std::string deviceName)
{
    if (_deviceName != deviceName)
    {
        _serviceModel.RetrieveDeviceProfiles(deviceName);
    }

    _deviceName = std::move(deviceName);
}

void DeviceProfilesPresenter::OnPressBackButton()
{
    DrawManager::GetInstance().EnableDevicesView();
}

void DeviceProfilesPresenter::OnPressEditButton()
{
    DrawManager::GetInstance().EnableProfileView(_deviceName, *_currentDeviceProfile);
}

void DeviceProfilesPresenter::OnPressUnloadButton()
{
    _currentDeviceProfile = {nullptr};

    _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::CURRENT_PROFILE_UPDATE);
}

void DeviceProfilesPresenter::CalculateMaxScroll()
{
    _maxScroll = std::ceil(static_cast<float>(_deviceProfiles.size()) / static_cast<float>(_viewsPerRow)) * _itemHeight - _recyclerViewHeight;

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
        std::ceil(_currentScroll / _itemHeight) * _viewsPerRow - _bufferRows * _viewsPerRow, 0, _deviceProfiles.size() - _visibleItemsCount);
}

float DeviceProfilesPresenter::GetCurrentScroll() const
{
    return _currentScroll;
}

std::string DeviceProfilesPresenter::GetActiveProfileName() const
{
    if (_currentDeviceProfile != nullptr)
    {
        return _currentDeviceProfile->name;
    }

    return "";
}

std::vector<ButtonInfo> DeviceProfilesPresenter::GetVisibleButtons() const
{
    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(_visibleItemsCount);

    for (int i{_firstItemToShowIndex}; i < _firstItemToShowIndex + _visibleItemsCount && i < _deviceProfiles.size(); ++i)
    {
        std::string string = "";

        string += std::to_string(i);

        buttonsInfo.emplace_back(_deviceProfiles.at(i).name, i);
    }

    return buttonsInfo;
}

bool DeviceProfilesPresenter::IsFirstItemPresent() const
{
    return _firstItemToShowIndex * _viewsPerRow == 0;
}

bool DeviceProfilesPresenter::IsLastItemPresent() const
{
    return _deviceProfiles.size() < _viewsPerRow || _firstItemToShowIndex + _visibleItemsCount == _deviceProfiles.size();
}

#include <iostream>

void DeviceProfilesPresenter::OnPressRecycleViewButton(uint8_t index)
{
    if (index == _deviceProfiles.size() - 1)
    {
        AddProfile();
        return;
    }

    Profile profile {_deviceProfiles.at(index)};

    std::cout << "Profile Name: " << profile.name << std::endl;

    std::cout << "Is Current Profile: "<< profile.isCurrentProfile << std::endl;

    for (size_t i{0}; i < profile.subProfiles.size(); ++i)
    {
        SubProfile subProfile {profile.subProfiles.at(i)};

        for (size_t j{0}; j < subProfile.codesRemaps.size(); ++j)
        {
            CodeRemap codeRemap {subProfile.codesRemaps.at(j)};

            std::cout << "Code Remap Code: "<< codeRemap.code << std::endl;

            std::cout << "Command Type: "<< static_cast<int>(codeRemap.commandType) << std::endl;

            for (size_t k{0}; k < codeRemap.emitsData.size(); ++k)
            {
                EmitData emitData {codeRemap.emitsData.at(k)};

                std::cout << "Input Device: "<< static_cast<int>(emitData.GetInputDevice()) << std::endl;

                InputEvent inputEvent {emitData.GetInputEvent()};

                std::cout << "Input Code: "<< inputEvent.GetCode() << std::endl;

                std::cout << "Input Type: "<< inputEvent.GetType() << std::endl;

                std::cout << "Input Value: "<< inputEvent.GetValue() << std::endl;
            }

            std::cout << "SubProfile Index: " << static_cast<int>(codeRemap.subProfileIndex) << std::endl;
        }
    }

    DrawManager::GetInstance().EnableProfileView(_deviceName, _deviceProfiles.at(index));
}

void DeviceProfilesPresenter::AddProfile()
{
    std::cout << "Add Profile" << std::endl;

    Profile& lastProfile {_deviceProfiles.back()};

    lastProfile = Profile{};

    std::string profileName {"Profile "};

    profileName += std::to_string(_deviceProfiles.size());

    lastProfile.name = std::move(profileName);

    _deviceProfiles.emplace_back("+", false, std::vector<SubProfile>{});

    _deviceProfilesNotifications.TriggerNotification(DeviceProfilesNotifications::PROFILES_UPDATE);
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