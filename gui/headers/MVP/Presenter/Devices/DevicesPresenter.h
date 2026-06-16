#pragma once

#include "MVP/Presenter/Devices/DevicesNotifications.h"
#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/RecycleViewPresenter.h"
#include "Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class DevicesPresenter
{
public:

    DevicesPresenter();

    ~DevicesPresenter() = default;

    void Restart();

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetVisibleButtons() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

    void OnPressReloadButton() const;

    void OnPressRecycleViewButton(uint8_t index) const;

    std::weak_ptr<std::function<void()>> SubscribeToDevicesNotifications(DevicesNotifications devicesNotification, std::function<void()>&& action);
    void UnsubscribeToDevicesNotifications(DevicesNotifications devicesNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ServiceModel& _serviceModel;

    std::vector<DeviceInfo> _devices;

    NotificationBus<DevicesNotifications> _devicesNotifications;

    RecycleViewPresenter _recyclerViewPresenter;
};
