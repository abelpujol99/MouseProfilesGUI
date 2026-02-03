#include "Managers/ApplicationManager.h"

#include "Managers/WindowManager.h"

std::unique_ptr<ApplicationManager> ApplicationManager::_applicationMangerInstance = nullptr;

ApplicationManager& ApplicationManager::GetInstance()
{
    if (!_applicationMangerInstance)
    {
        _applicationMangerInstance.reset(new ApplicationManager());
    }

    return *_applicationMangerInstance;
}

void ApplicationManager::Start()
{
    WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetSizes(1500, 700);
    windowManager.Start();
    windowManager.Update();
}