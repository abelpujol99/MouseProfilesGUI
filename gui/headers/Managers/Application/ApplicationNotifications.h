#pragma once

enum class ApplicationNotifications
{
    SHUTDOWN,
    GAIN_FOCUS,
    LOSE_FOCUS,
    COUNT
};

inline ApplicationNotifications& operator++(ApplicationNotifications& applicationNotifications)
{
    applicationNotifications = static_cast<ApplicationNotifications>(static_cast<char>(applicationNotifications) + 1);

    return applicationNotifications;
}