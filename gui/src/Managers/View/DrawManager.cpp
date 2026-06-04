#include "Managers/View/DrawManager.h"

#include "Factory/CanvasFactory.h"

DrawManager* DrawManager::_drawManagerInstance {nullptr};

DrawManager::DrawManager()
{
    _devicesCanvas = std::make_unique<DevicesCanvas>(true);
    _deviceProfilesCanvas = std::make_unique<DeviceProfilesCanvas>(true);

    _currentCanvas = _devicesCanvas.get();
    _currentCanvas->Enable();
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

void DrawManager::EnableDevicesCanvas()
{
    _currentCanvas->Disable();
    _currentCanvas = _devicesCanvas.get();
    _currentCanvas->Enable();
}

void DrawManager::EnableDeviceProfilesCanvas(std::string deviceName)
{
    _currentCanvas->Disable();
    _deviceProfilesCanvas->SetTitle(deviceName);
    _currentCanvas = _deviceProfilesCanvas.get();
    _currentCanvas->Enable();
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    _currentCanvas->Draw(drawList);
}