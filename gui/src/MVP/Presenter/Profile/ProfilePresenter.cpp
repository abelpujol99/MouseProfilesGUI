#include "MVP/Presenter/Profile/ProfilePresenter.h"

#include <utility>

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

ProfilePresenter::ProfilePresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{
    ProfileNotifications profileNotificationCount {ProfileNotifications::COUNT};

    for (ProfileNotifications i{ProfileNotifications::TITLE_UPDATE}; i != profileNotificationCount; ++i)
    {
        _profileNotifications.AddEntry(i);
    }
}

void ProfilePresenter::Restart()
{
    _subProfileRecycleViewPresenter.Reset();

    _inputRecycleViewPresenter.Reset();

    _profile = _serviceModel.RetrieveProfile(_profileIndex);

    _profile.subProfiles.emplace_back(std::vector<CodeRemap>{});

    _subProfileRecycleViewPresenter.SetListLength(_profile.subProfiles.size());

    _profileNotifications.TriggerNotification(ProfileNotifications::SUB_PROFILE_SCROLL_UPDATE);
}

void ProfilePresenter::SetDeviceName(std::string deviceName)
{
    _deviceName = std::move(deviceName);
}

void ProfilePresenter::SetProfileIndex(uint8_t profileIndex)
{
    _profileIndex = profileIndex;

    _profileNotifications.TriggerNotification(ProfileNotifications::TITLE_UPDATE);
}

std::string ProfilePresenter::GetTitle() const
{
    return {_deviceName + " - " + _serviceModel.RetrieveProfile(_profileIndex).name};
}

void ProfilePresenter::SetSubProfileRecyclerViewHeight(float recyclerViewHeight)
{
    _subProfileRecycleViewPresenter.SetRecyclerViewHeight(recyclerViewHeight);
}

void ProfilePresenter::SetSubProfileViewsPerRow(uint8_t viewsPerRow)
{
    _subProfileRecycleViewPresenter.SetViewsPerRow(viewsPerRow);
}

void ProfilePresenter::SetSubProfileItemHeight(float itemHeight)
{
    _subProfileRecycleViewPresenter.SetItemHeight(itemHeight);
}

void ProfilePresenter::SetSubProfileRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _subProfileRecycleViewPresenter.SetRecycleViewVisibleItemsCount(visibleItemsCount);
}

void ProfilePresenter::SetSubProfileRecyclerViewBufferRows(uint8_t bufferRows)
{
    _subProfileRecycleViewPresenter.SetRecyclerViewBufferRows(bufferRows);
}

void ProfilePresenter::OnSubProfileScroll(float scrollValue)
{
    _subProfileRecycleViewPresenter.OnScroll(scrollValue);

    _profileNotifications.TriggerNotification(ProfileNotifications::SUB_PROFILE_SCROLL_UPDATE);
}

float ProfilePresenter::GetSubProfileCurrentScroll() const
{
    return _subProfileRecycleViewPresenter.GetCurrentScroll();
}

std::vector<ButtonInfo> ProfilePresenter::GetSubProfileVisibleButtons() const
{
    std::vector<uint8_t> visibleItemsIndex {_subProfileRecycleViewPresenter.GetVisibleItemsIndex()};

    size_t visibleItemsIndexCount {visibleItemsIndex.size()};

    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(visibleItemsIndexCount);

    for (size_t i{0}; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        std::string subProfileName {"SubProfile "};

        subProfileName += std::to_string(index);

        buttonsInfo.emplace_back(subProfileName, index);
    }

    return buttonsInfo;
}

bool ProfilePresenter::IsSubProfileFirstItemPresent() const
{
    return _subProfileRecycleViewPresenter.IsFirstItemPresent();
}

bool ProfilePresenter::IsSubProfileLastItemPresent() const
{
    return _subProfileRecycleViewPresenter.IsLastItemPresent();
}

void ProfilePresenter::SetInputRecyclerViewHeight(float recyclerViewHeight)
{
    _inputRecycleViewPresenter.SetRecyclerViewHeight(recyclerViewHeight);
}

void ProfilePresenter::SetInputViewsPerRow(uint8_t viewsPerRow)
{
    _inputRecycleViewPresenter.SetViewsPerRow(viewsPerRow);
}

void ProfilePresenter::SetInputItemHeight(float itemHeight)
{
    _inputRecycleViewPresenter.SetItemHeight(itemHeight);
}

void ProfilePresenter::SetInputRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _inputRecycleViewPresenter.SetRecycleViewVisibleItemsCount(visibleItemsCount);
}

void ProfilePresenter::SetInputRecyclerViewBufferRows(uint8_t bufferRows)
{
    _inputRecycleViewPresenter.SetRecyclerViewBufferRows(bufferRows);
}

void ProfilePresenter::OnInputScroll(float scrollValue)
{
    _inputRecycleViewPresenter.OnScroll(scrollValue);

    _profileNotifications.TriggerNotification(ProfileNotifications::INPUT_SCROLL_UPDATE);
}

float ProfilePresenter::GetInputCurrentScroll() const
{
    return _inputRecycleViewPresenter.GetCurrentScroll();
}

std::vector<ButtonInfo> ProfilePresenter::GetInputVisibleButtons() const
{
    std::vector<uint8_t> visibleItemsIndex {_inputRecycleViewPresenter.GetVisibleItemsIndex()};

    size_t visibleItemsIndexCount {visibleItemsIndex.size()};

    std::vector<ButtonInfo> buttonsInfo;

    buttonsInfo.reserve(visibleItemsIndexCount);

    for (size_t i{0}; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        std::string keyName {"Key "};

        keyName += std::to_string(_currentSubProfile->codesRemaps.at(index).code);

        buttonsInfo.emplace_back(keyName, index);
    }

    return buttonsInfo;
}

bool ProfilePresenter::IsInputFirstItemPresent() const
{
    return _inputRecycleViewPresenter.IsFirstItemPresent();
}

bool ProfilePresenter::IsInputLastItemPresent() const
{
    return _inputRecycleViewPresenter.IsLastItemPresent();
}

void ProfilePresenter::OnPressBackButton()
{
    DrawManager::GetInstance().EnableDeviceProfilesView(_deviceName);
}

void ProfilePresenter::OnPressLoadUnloadButton()
{
}

void ProfilePresenter::OnPressLinkButton()
{
}

void ProfilePresenter::OnPressSubProfileAddButton()
{
}

void ProfilePresenter::OnPressSubProfileDeleteButton()
{
}

void ProfilePresenter::OnPressInputRecordButton()
{
}

void ProfilePresenter::OnPressInputDeleteButton()
{
}

void ProfilePresenter::OnPressSubProfileRecycleViewButton(uint8_t index)
{
    _currentSubProfile = &_profile.subProfiles.at(index);

    _inputRecycleViewPresenter.SetListLength(_currentSubProfile->codesRemaps.size());

    _profileNotifications.TriggerNotification(ProfileNotifications::INPUT_SCROLL_UPDATE);
}

void ProfilePresenter::OnPressInputRecycleViewButton(uint8_t index)
{
    _currentCodeRemap = &_currentSubProfile->codesRemaps.at(index);

    _profileNotifications.TriggerNotification(ProfileNotifications::DETAILS_UPDATE);
}

std::weak_ptr<std::function<void()>> ProfilePresenter::SubscribeToProfileNotifications(
    ProfileNotifications profileNotification, std::function<void()>&& action)
{
    return _profileNotifications.Subscribe(profileNotification, std::move(action));
}

void ProfilePresenter::UnsubscribeToProfileNotifications(ProfileNotifications profileNotification,
    std::weak_ptr<std::function<void()>>&& action)
{
    _profileNotifications.Unsubscribe(profileNotification, std::move(action));
}
