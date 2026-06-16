#include "Managers/Application/ApplicationManager.h"

#include "TimeUsings.h"
#include "../../../headers/Managers/GLFWManager.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 700

std::unique_ptr<ApplicationManager> ApplicationManager::_applicationManagerInstance {nullptr};

ApplicationManager& ApplicationManager::GetInstance()
{
    if (_applicationManagerInstance == nullptr)
    {
        _applicationManagerInstance.reset(new ApplicationManager());
    }

    return *_applicationManagerInstance;
}

void ApplicationManager::Start() const
{
    GLFWManager& windowManager {GLFWManager::GetInstance()};

    windowManager.SetInitialSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    windowManager.Start();
    windowManager.Update();
}

std::weak_ptr<std::function<void()>> ApplicationManager::SubscribeToApplicationNotification(
    ApplicationNotifications applicationNotification, std::function<void()>&& action)
{
    return _applicationNotification.Subscribe(applicationNotification, std::move(action));
}

void ApplicationManager::UnsubscribeToApplicationNotification(ApplicationNotifications applicationNotification,
    std::weak_ptr<std::function<void()>>&& action)
{
    _applicationNotification.Unsubscribe(applicationNotification, std::move(action));
}
