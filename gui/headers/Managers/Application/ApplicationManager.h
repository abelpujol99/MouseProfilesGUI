#pragma once
#include <memory>
#include <mutex>
#include <thread>

#include "ApplicationNotifications.h"
#include "Notification/NotificationBus.h"

class ApplicationManager
{
public:

    ~ApplicationManager() = default;

    ApplicationManager(const ApplicationManager& other) = delete;
    ApplicationManager& operator=(const ApplicationManager& other) = delete;
    ApplicationManager(ApplicationManager&& other) = delete;
    ApplicationManager& operator=(ApplicationManager&& other) = delete;

    static ApplicationManager& GetInstance();

    static void Start();

    void OnGainFocus();

    void OnLoseFocus();

    std::weak_ptr<std::function<void()>> SubscribeToApplicationNotification(ApplicationNotifications applicationNotification, std::function<void()>&& action);
    void UnsubscribeToApplicationNotification(ApplicationNotifications applicationNotification, std::weak_ptr<std::function<void()>>&& action);

private:

    ApplicationManager();

    static std::unique_ptr<ApplicationManager> _applicationManagerInstance;

    NotificationBus<ApplicationNotifications> _applicationNotification;

    bool _isApplicationRunning {true};
};
