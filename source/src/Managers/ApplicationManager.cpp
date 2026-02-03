#include "Managers/ApplicationManager.h"

#include "Managers/WindowManager.h"

ApplicationManager ApplicationManager::_applicationMangerInstance{};

ApplicationManager& ApplicationManager::GetInstance()
{
    return _applicationMangerInstance;
}

void ApplicationManager::Start()
{
    WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetSizes(1500, 700);
    windowManager.Start();
    windowManager.Update();
}