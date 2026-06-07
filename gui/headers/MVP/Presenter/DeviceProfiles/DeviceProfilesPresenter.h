#pragma once
#include <cstdint>

#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesNotifications.h"
#include "Utilities/Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class DeviceProfilesPresenter
{
public:

    DeviceProfilesPresenter();

    ~DeviceProfilesPresenter() = default;

    void SetDeviceName(std::string deviceName);

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void OnPressBackButton();

    void OnPressEditButton();

    void OnPressUnloadButton();

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::string GetActiveProfileName() const;

    [[nodiscard]] std::vector<ButtonInfo> GetVisibleButtons() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

    void OnPressRecycleViewButton(uint8_t index);

    void AddProfile();

    std::weak_ptr<std::function<void()>> SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::function<void()>&& action);
    void UnsubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    void CalculateMaxScroll();

    void UpdateRecycleViewDataDisplay();

    ServiceModel& _serviceModel;

    std::string _deviceName;

    float _recyclerViewHeight {0};

    uint8_t _viewsPerRow {0};

    float _itemHeight {0};

    uint8_t _visibleItemsCount {0};

    uint8_t _bufferRows {0};

    float _currentScroll {0};

    float _maxScroll {0};

    uint8_t _firstItemToShowIndex {0};

    Profile* _currentDeviceProfile {nullptr};

    std::vector<Profile> _deviceProfiles;

    NotificationBus<DeviceProfilesNotifications> _deviceProfilesNotifications;

};