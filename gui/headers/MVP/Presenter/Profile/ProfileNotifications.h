#pragma once

enum class ProfileNotifications
{
    TITLE_UPDATE,
    SUB_PROFILE_SCROLL_UPDATE,
    INPUT_SCROLL_UPDATE,
    CODE_REMAPS_UPDATE,
    DETAILS_UPDATE,
    COUNT
};

inline ProfileNotifications& operator++(ProfileNotifications& profileNotification)
{
    profileNotification = static_cast<ProfileNotifications>(static_cast<char>(profileNotification) + 1);

    return profileNotification;
}