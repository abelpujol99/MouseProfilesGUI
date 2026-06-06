#pragma once
#include <cstdint>
#include <vector>

#include "DevicesNotifications.h"
#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/BasePresenter.h"
#include "Utilities/Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class DevicesPresenter : public BasePresenter
{
public:

    DevicesPresenter();

    ~DevicesPresenter() override = default;

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void Refresh() override;

    void OnPressReloadButton() const;

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetVisibleButtons() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

    void OnPressRecycleViewButton(uint8_t index) const;

    std::weak_ptr<std::function<void()>> SubscribeToDevicesNotifications(DevicesNotifications devicesNotification, std::function<void()>&& action);
    void UnsubscribeToDevicesNotifications(DevicesNotifications devicesNotification, std::weak_ptr<std::function<void()>>&& action);

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

    std::vector<DeviceInfo> _devices;

    NotificationBus<DevicesNotifications> _devicesNotifications;
};
