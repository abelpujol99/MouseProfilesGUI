#pragma once

#include "MVP/View/DeviceProfilesView.h"
#include "MVP/View/Devices/DevicesView.h"

class DrawManager
{
public:

    ~DrawManager() noexcept;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void EnableDevicesView();

    void EnableDeviceProfilesView(std::string deviceName);

    void DrawElements(ImDrawList* drawList);

private:

    DrawManager();

    static DrawManager* _drawManagerInstance;

    IView* _currentView;

    std::unique_ptr<DevicesView> _devicesView;
    std::unique_ptr<DeviceProfilesView> _deviceProfilesView;
};
