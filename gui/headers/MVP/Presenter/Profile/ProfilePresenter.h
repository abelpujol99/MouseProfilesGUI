#pragma once

#include "ProfileNotifications.h"
#include "MVP/Model/ServiceModel.h"
#include "Utilities/Notification/NotificationBus.h"

class ProfilePresenter
{
public:

    ProfilePresenter();


    std::weak_ptr<std::function<void()>> SubscribeToProfileNotifications(ProfileNotifications profileNotification, std::function<void()>&& action);
    void UnsubscribeToProfileNotifications(ProfileNotifications profileNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ServiceModel& _serviceModel;

    NotificationBus<ProfileNotifications> _profileNotifications;
};
