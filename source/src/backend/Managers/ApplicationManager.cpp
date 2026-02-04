#include <ApplicationManager.h>

#include <ThreadsManager.h>
#include <ProfileManager.h>
#include <EvdevListener.h>
#include <HidrawListener.h>
#include <ObserverSingleValue.h>
#include <FileCodes.h>

#include "VirtualDeviceManager.h"

std::unique_ptr<ApplicationManager> ApplicationManager::_applicationManagerInstance = nullptr;

ApplicationManager::ApplicationManager()
{
    _shouldRunObserver = std::make_unique<ObserverSingleValue<bool>>();

    _shouldRunObserver->SetValue(true);

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
    ProfileManager::GetInstance().OnChangeApplicationInFocus();

    VirtualDeviceManager::GetInstance().CreateListeners();

    ThreadsManager::GetInstance().Start();
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