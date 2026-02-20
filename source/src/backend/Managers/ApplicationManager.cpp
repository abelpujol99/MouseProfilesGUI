#include "backend/Managers/ApplicationManager.h"

#include "backend/Managers/ThreadsManager.h"
#include "backend/Managers/ProfileManager.h"
#include "backend/Managers/VirtualDeviceManager.h"
#include "backend/Listener/EvdevListener.h"
#include "backend/Listener/HidrawListener.h"
#include "backend/Observer/ObserverSingleValue.h"
#include "backend/Profile/FileCodes.h"

#include "Managers/WindowManager.h"

std::unique_ptr<ApplicationManager> ApplicationManager::_applicationManagerInstance = nullptr;

ApplicationManager::ApplicationManager()
{
    _shouldRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldRunObserver->SetValue(true);

    _shouldGUIRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldGUIRunObserver->SetValue(false);

    _scrollWheelModeHidrawPath = "/sys/class/hidraw/hidraw0/device/scroll_mode";
}

ApplicationManager& ApplicationManager::GetInstance()
{
    if (!_applicationManagerInstance)
    {
        _applicationManagerInstance.reset(new ApplicationManager());
    }

    return *_applicationManagerInstance;
}

void ApplicationManager::Start()
{
    ProfileManager::GetInstance().OnChangeApplicationFocus();

    VirtualDeviceManager::GetInstance().CreateListeners();

    ThreadsManager::GetInstance().Start();
}

void ApplicationManager::TurnOnGUI()
{
    _shouldGUIRunObserver->SetValue(true);
}

void ApplicationManager::StartGUI()
{
    WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetSizes(1500, 700);
    windowManager.Start();
    windowManager.Update();
}

std::string ApplicationManager::GetPathToSwitchScrollMode() const
{
    return _scrollWheelModeHidrawPath;
}

std::weak_ptr<std::function<void(bool)>> ApplicationManager::SubscribeToShouldRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldRunObserver->Subscribe(std::move(action));
}

void ApplicationManager::UnsubscribeToShouldRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldRunObserver->Unsubscribe(std::move(action));
}

void ApplicationManager::SwitchShouldRun() const
{
    _shouldRunObserver->SetValue(false);
}

bool ApplicationManager::GetShouldRun() const
{
    return _shouldRunObserver->GetValue();
}

std::weak_ptr<std::function<void(bool)>> ApplicationManager::SubscribeToShouldGUIRunObserver(
    std::function<void(bool)> action) const
{
    return _shouldGUIRunObserver->Subscribe(std::move(action));
}

void ApplicationManager::UnsubscribeToShouldGUIRunObserver(std::weak_ptr<std::function<void(bool)>> action) const
{
    _shouldGUIRunObserver->Unsubscribe(std::move(action));
}

void ApplicationManager::TurnOffGUI()
{
    _shouldGUIRunObserver->SetValue(false);
}