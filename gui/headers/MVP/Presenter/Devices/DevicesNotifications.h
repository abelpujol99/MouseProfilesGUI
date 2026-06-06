#pragma once

enum class DevicesNotifications
{
    DEVICES_UPDATE,
    SCROLL_UPDATE,
    COUNT
};

inline DevicesNotifications& operator++(DevicesNotifications& devicesNotification)
{
    devicesNotification = static_cast<DevicesNotifications>(static_cast<char>(devicesNotification) + 1);

    return devicesNotification;
}