#include "Managers/View/DrawManager.h"

DrawManager* DrawManager::_drawManagerInstance {nullptr};

DrawManager::DrawManager()
{
    _devicesView = std::make_unique<DevicesView>(true);
    _deviceProfilesView = std::make_unique<DeviceProfilesView>(true);
    _profileView = std::make_unique<ProfileView>(true);

    _currentView = _devicesView.get();
    _currentView->Enable();
}

DrawManager::~DrawManager() noexcept
{
    delete _drawManagerInstance;
}

DrawManager& DrawManager::GetInstance()
{
    if (_drawManagerInstance == nullptr)
    {
        _drawManagerInstance = new DrawManager();
    }

    return *_drawManagerInstance;
}

void DrawManager::EnableDevicesView()
{
    _currentView->Disable();
    _currentView = _devicesView.get();
    _currentView->Enable();
}

void DrawManager::EnableDeviceProfilesView(std::string deviceName)
{
    _currentView->Disable();
    _deviceProfilesView->SetTitle(deviceName);
    _currentView = _deviceProfilesView.get();
    _currentView->Enable();
}

void DrawManager::EnableProfileView(std::string deviceName, Profile profile)
{
    _currentView->Disable();
    _currentView = _profileView.get();
    _currentView->Enable();
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    _currentView->Draw(drawList);
}
