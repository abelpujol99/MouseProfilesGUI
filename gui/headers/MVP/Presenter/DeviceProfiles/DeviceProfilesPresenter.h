#pragma once
#include <cstdint>

#include "MVP/Presenter/BasePresenter.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesNotifications.h"
#include "Utilities/Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class DeviceProfilesPresenter : public BasePresenter
{
public:

    DeviceProfilesPresenter();

    ~DeviceProfilesPresenter() override = default;

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void Refresh() override;

    void OnPressBackButton();

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetVisibleButtons() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

    void OnPressRecycleViewButton(uint8_t index) const;

    std::weak_ptr<std::function<void()>> SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::function<void()>&& action);
    void UnsubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications devicesNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    void CalculateMaxScroll();

    void UpdateRecycleViewDataDisplay();

    float _recyclerViewHeight {0};

    uint8_t _viewsPerRow {0};

    float _itemHeight {0};

    uint8_t _visibleItemsCount {0};

    uint8_t _bufferRows {0};

    float _currentScroll {0};

    float _maxScroll {0};

    int _firstItemToShowIndex {0};

    std::vector<DeviceInfo> _profiles;

    NotificationBus<DeviceProfilesNotifications> _deviceProfilesNotifications;

};
