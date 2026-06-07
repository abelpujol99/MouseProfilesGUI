#pragma once

enum class ProfileNotifications
{
    DEVICES_UPDATE,
    SCROLL_UPDATE,
    COUNT
};

inline ProfileNotifications& operator++(ProfileNotifications& profileNotification)
{
    profileNotification = static_cast<ProfileNotifications>(static_cast<char>(profileNotification) + 1);

    return profileNotification;
}