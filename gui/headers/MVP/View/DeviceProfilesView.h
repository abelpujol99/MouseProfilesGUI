#pragma once
#include "BaseView.h"
#include "MVP/Presenter/DeviceProfiles/DeviceProfilesPresenter.h"

#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/RecycleView/RecycleView.h"
#include "UI/Elements/Intermediate/Text/Text.h"

class DeviceProfilesView : public BaseView
{
public:

    DeviceProfilesView(bool isHidden);

    ~DeviceProfilesView() override = default;

    void SetTitle(std::string title);

    void Enable() override;

    void Disable() override;

private:

    void OnScrollUpdate();

    void OnCurrentProfileUpdate();

    void OnProfilesRead();

    std::unique_ptr<DeviceProfilesPresenter> _presenter;

    std::unique_ptr<Text> _title;

    std::unique_ptr<Button> _backButton;

    std::unique_ptr<Text> _currentProfileTitle;

    std::unique_ptr<Text> _currentProfileName;

    std::unique_ptr<Button> _editCurrentProfileButton;

    std::unique_ptr<Button> _unloadCurrentProfileButton;

    RectDrawable* _profileRecycleViewRect;

    std::unique_ptr<RecycleView> _profilesRecycleView;

    std::unique_ptr<Button> _templateProfileButton;

    std::vector<std::unique_ptr<Button>> _profilesButtons;
};
