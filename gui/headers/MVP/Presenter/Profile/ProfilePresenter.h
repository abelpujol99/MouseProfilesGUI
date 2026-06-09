#pragma once

#include "ProfileNotifications.h"
#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/RecycleViewPresenter.h"
#include "Utilities/Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class ProfilePresenter
{
public:

    ProfilePresenter();

    void Restart();

    void SetDeviceName(std::string deviceName);

    void SetProfileIndex(uint8_t profileIndex);

    [[nodiscard]] std::string GetTitle() const;

    void SetSubProfileRecyclerViewHeight(float recyclerViewHeight);

    void SetSubProfileViewsPerRow(uint8_t viewsPerRow);

    void SetSubProfileItemHeight(float itemHeight);

    void SetSubProfileRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetSubProfileRecyclerViewBufferRows(uint8_t bufferRows);

    void OnSubProfileScroll(float scrollValue);

    [[nodiscard]] float GetSubProfileCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetSubProfileVisibleButtons() const;

    [[nodiscard]] bool IsSubProfileFirstItemPresent() const;

    [[nodiscard]] bool IsSubProfileLastItemPresent() const;

    void SetInputRecyclerViewHeight(float recyclerViewHeight);

    void SetInputViewsPerRow(uint8_t viewsPerRow);

    void SetInputItemHeight(float itemHeight);

    void SetInputRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetInputRecyclerViewBufferRows(uint8_t bufferRows);

    void OnInputScroll(float scrollValue);

    [[nodiscard]] float GetInputCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetInputVisibleButtons() const;

    [[nodiscard]] bool IsInputFirstItemPresent() const;

    [[nodiscard]] bool IsInputLastItemPresent() const;

    void OnPressBackButton();

    void OnPressLoadUnloadButton();

    void OnPressLinkButton();

    void OnPressSubProfileAddButton();

    void OnPressSubProfileDeleteButton();

    void OnPressInputRecordButton();

    void OnPressInputDeleteButton();

    void OnPressSubProfileRecycleViewButton(uint8_t index);

    void OnPressInputRecycleViewButton(uint8_t index);

    std::weak_ptr<std::function<void()>> SubscribeToProfileNotifications(ProfileNotifications profileNotification, std::function<void()>&& action);
    void UnsubscribeToProfileNotifications(ProfileNotifications profileNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ServiceModel& _serviceModel;

    std::string _deviceName;

    uint8_t _profileIndex;

    Profile _profile;

    SubProfile* _currentSubProfile;

    CodeRemap* _currentCodeRemap;

    NotificationBus<ProfileNotifications> _profileNotifications;

    RecycleViewPresenter _subProfileRecycleViewPresenter;

    RecycleViewPresenter _inputRecycleViewPresenter;
};
