#pragma once

#include "MVP/Presenter/Profile/ProfileNotifications.h"
#include "MVP/Model/ServiceModel.h"
#include "MVP/Presenter/RecycleViewPresenter.h"
#include "Notification/NotificationBus.h"
#include "Utilities/Structs/ButtonInfo.h"

class ProfilePresenter
{
public:

    ProfilePresenter();

    void SetDeviceName(std::string deviceName);

    void SetProfileIndex(uint8_t profileIndex);

    void Restart();

    [[nodiscard]] std::string GetTitle() const;

#pragma region SubProfile List

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

    void OnPressSubProfileRecycleViewButton(uint8_t index);

    void OnPressSubProfileDeleteButton(uint8_t index);

    void AddSubProfile() const;

#pragma endregion

#pragma region Input List

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

    void OnPressInputRecycleViewButton(uint8_t index);

    void OnPressInputDeleteButton(uint8_t index);

    void AddCodeRemap() const;

#pragma endregion

#pragma region

    void SetSwitchToSubProfileRecyclerViewHeight(float recyclerViewHeight);

    void SetSwitchToSubProfileViewsPerRow(uint8_t viewsPerRow);

    void SetSwitchToSubProfileItemHeight(float itemHeight);

    void SetSwitchToSubProfileRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetSwitchToSubProfileRecyclerViewBufferRows(uint8_t bufferRows);

    void OnSwitchToSubProfileScroll(float scrollValue);

    [[nodiscard]] float GetSwitchToSubProfileCurrentScroll() const;

    [[nodiscard]] std::vector<ButtonInfo> GetSwitchToSubProfileVisibleButtons() const;

    [[nodiscard]] bool IsSwitchToSubProfileFirstItemPresent() const;

    [[nodiscard]] bool IsSwitchToSubProfileLastItemPresent() const;

    void OnPressSwitchToSubProfileRecycleViewButton(uint8_t index);

#pragma endregion

    void OnPressBackButton();

    void OnPressLoadUnloadButton();

    void OnPressLinkButton();

    void OnPressSubProfileAddButton();

    void OnPressInputRecordButton();

    void OnPressEmitInputEventButton();

    void OnPressMacroButton();

    void OnPressSwitchToSubProfileButton();

    void OnPressShutdownApplicationButton();

    std::weak_ptr<std::function<void()>> SubscribeToProfileNotifications(ProfileNotifications profileNotification, std::function<void()>&& action);
    void UnsubscribeToProfileNotifications(ProfileNotifications profileNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ServiceModel& _serviceModel;

    std::string _deviceName;

    uint8_t _profileIndex;

    uint8_t _currentSubProfileIndex;

    uint8_t _currentCodeRemapIndex;

    Profile _profile;

    SubProfile _subProfile;

    CodeRemap _codeRemap;

    NotificationBus<ProfileNotifications> _profileNotifications;

    RecycleViewPresenter _subProfileRecycleViewPresenter;

    RecycleViewPresenter _inputRecycleViewPresenter;

    RecycleViewPresenter _switchToSubProfileRecycleViewPresenter;
};
