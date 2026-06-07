#pragma once
#include "BaseView.h"

#include "MVP/Presenter/Profile/ProfilePresenter.h"

class ProfileView : public BaseView
{
public:

    ProfileView(bool isHidden);

    ~ProfileView() override = default;

    void Enable() override;

    void Disable() override;

private:

    std::unique_ptr<ProfilePresenter> _presenter;
};
