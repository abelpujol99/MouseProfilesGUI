#include "MVP/Presenter/Profile/ProfilePresenter.h"

#include "Managers/MVPManager.h"

ProfilePresenter::ProfilePresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{
    ProfileNotifications profileNotificationCount {ProfileNotifications::COUNT};

    for (ProfileNotifications i{ProfileNotifications::DEVICES_UPDATE}; i != profileNotificationCount; ++i)
    {
        _profileNotifications.AddEntry(i);
    }
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
