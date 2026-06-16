#pragma once

#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/RecycleViewPresenter.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesNotifications.h"
#include "Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class DeviceProfilesPresenter
{
public:

    DeviceProfilesPresenter();

    ~DeviceProfilesPresenter() = default;

    void SetDeviceName(std::string deviceName);

    void Restart();

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::string GetActiveProfileName() const;

    [[nodiscard]] std::vector<ButtonInfo> GetVisibleButtons() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

    void OnPressBackButton();

    void OnPressEditButton();

    void OnPressUnloadButton();

    void OnPressRecycleViewButton(uint8_t index);

    void AddProfile() const;

    std::weak_ptr<std::function<void()>> SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::function<void()>&& action);
    void UnsubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ServiceModel& _serviceModel;

    std::string _deviceName;

    int _currentDeviceProfileIndex;

    std::vector<Profile> _deviceProfiles;

    NotificationBus<DeviceProfilesNotifications> _deviceProfilesNotifications;

    RecycleViewPresenter _recyclerViewPresenter;
};