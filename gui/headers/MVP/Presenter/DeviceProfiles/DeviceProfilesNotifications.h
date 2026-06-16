#pragma once

enum class DeviceProfilesNotifications
{
    PROFILES_UPDATE,
    CURRENT_PROFILE_UPDATE,
    SCROLL_UPDATE,
    COUNT
};

inline DeviceProfilesNotifications& operator++(DeviceProfilesNotifications& deviceProfilesNotifications)
{
    deviceProfilesNotifications = static_cast<DeviceProfilesNotifications>(static_cast<char>(deviceProfilesNotifications) + 1);

    return deviceProfilesNotifications;
}