#include "MVP/Presenter/Profile/ProfilePresenter.h"

#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

ProfilePresenter::ProfilePresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{
    ProfileNotifications profileNotificationCount {ProfileNotifications::COUNT};

    for (ProfileNotifications i{ProfileNotifications::TITLE_UPDATE}; i != profileNotificationCount; ++i)
    {
        _profileNotifications.AddEntry(i);
    }

    _serviceModel.SubscribeToProfile([&](Profile profile)
    {
        _profile = profile;

        _profile.subProfiles.emplace_back();

        _subProfileRecycleViewPresenter.SetListLength(_profile.subProfiles.size());

        _profileNotifications.TriggerNotification(ProfileNotifications::SUB_PROFILE_SCROLL_UPDATE);
    });

    _serviceModel.SubscribeToProfileName([&](std::string profileName)
    {
        _profile.name = profileName;

        _profileNotifications.TriggerNotification(ProfileNotifications::TITLE_UPDATE);
    });

    _serviceModel.SubscribeToSubProfile([&](SubProfile subProfile)
    {
        _subProfile = subProfile;

        _subProfile.codesRemaps.emplace_back();

        _inputRecycleViewPresenter.SetListLength(_subProfile.codesRemaps.size());

        _profileNotifications.TriggerNotification(ProfileNotifications::INPUT_SCROLL_UPDATE);
    });

    _serviceModel.SubscribeToCodeRemap([&](CodeRemap codeRemap)
    {
        _codeRemap = codeRemap;
    });
}

void ProfilePresenter::SetDeviceName(std::string deviceName)
{
    _deviceName = std::move(deviceName);
}

void ProfilePresenter::SetProfileIndex(uint8_t profileIndex)
{
    _profileIndex = profileIndex;

    _serviceModel.RefreshProfile(profileIndex);
}

void ProfilePresenter::Restart()
{
    _subProfileRecycleViewPresenter.Reset();

    _inputRecycleViewPresenter.Reset();
}

std::string ProfilePresenter::GetTitle() const
{
    return {_deviceName + " - " + _profile.name};
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

    if (visibleItemsIndexCount == 1)
    {
        buttonsInfo.emplace_back("+", 0);
        return buttonsInfo;
    }

    buttonsInfo.reserve(visibleItemsIndexCount);

    bool isLastElementPresent {_subProfileRecycleViewPresenter.IsLastItemPresent()};

    if (isLastElementPresent)
    {
        visibleItemsIndexCount--;
    }

    size_t i{0};

    for (; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        std::string subProfileName {"SubProfile "};

        subProfileName += std::to_string(index);

        buttonsInfo.emplace_back(subProfileName, index);
    }

    if (isLastElementPresent)
    {
        buttonsInfo.emplace_back("+", i);
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

void ProfilePresenter::OnPressSubProfileRecycleViewButton(uint8_t index)
{
    if (index == _profile.subProfiles.size() - 1)
    {
        AddSubProfile();
        return;
    }

    _currentSubProfileIndex = index;

    _serviceModel.RefreshSubProfile(_profileIndex, _currentSubProfileIndex);
}

void ProfilePresenter::OnPressSubProfileDeleteButton(uint8_t index)
{
    //TODO
}

void ProfilePresenter::AddSubProfile() const
{
    SubProfile subProfile {};

    _serviceModel.AddSubProfile(_profileIndex, std::move(subProfile));
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

    if (visibleItemsIndexCount == 1)
    {
        buttonsInfo.emplace_back("+", 0);
        return buttonsInfo;
    }

    buttonsInfo.reserve(visibleItemsIndexCount);

    bool isLastItemPresent {_inputRecycleViewPresenter.IsLastItemPresent()};

    if (isLastItemPresent)
    {
        visibleItemsIndexCount--;
    }

    size_t i{0};

    for (; i < visibleItemsIndexCount; ++i)
    {
        uint8_t index {visibleItemsIndex.at(i)};

        std::string keyName;

        const Code& code {_subProfile.codesRemaps.at(index).code};

        if (code == 0)
        {
            keyName = "Unset";
        }
        else
        {
            keyName = "Key ";

            keyName += std::to_string(_subProfile.codesRemaps.at(index).code);
        }

        buttonsInfo.emplace_back(keyName, index);
    }

    if (isLastItemPresent)
    {
        buttonsInfo.emplace_back("+", i);
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

void ProfilePresenter::OnPressInputRecycleViewButton(uint8_t index)
{
    if (index == _subProfile.codesRemaps.size() - 1)
    {
        AddCodeRemap();
        return;
    }

    _currentCodeRemapIndex = index;

    _profileNotifications.TriggerNotification(ProfileNotifications::DETAILS_UPDATE);
}

void ProfilePresenter::OnPressInputDeleteButton(uint8_t index)
{
    //TODO
}

void ProfilePresenter::AddCodeRemap() const
{
    CodeRemap codeRemap {};

    _serviceModel.AddCodeRemap(_profileIndex, _currentSubProfileIndex, std::move(codeRemap));
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

void ProfilePresenter::OnPressInputRecordButton()
{
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
