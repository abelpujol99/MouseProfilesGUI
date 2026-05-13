#pragma once

#include "Frontend/UI/Elements/Complex/DeviceProfilesCanvas.h"
#include "Frontend/UI/Elements/Complex/DevicesCanvas.h"

class DrawManager
{
public:

    ~DrawManager() noexcept;

    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;
    DrawManager(DrawManager&& other) = delete;
    DrawManager& operator=(DrawManager&& other) = delete;

    static DrawManager& GetInstance();

    void EnableDevicesCanvas();

    void EnableDeviceProfilesCanvas(std::string deviceName);

    void DrawElements(ImDrawList* drawList);

private:

    DrawManager();

    static DrawManager* _drawManagerInstance;

    Canvas* _currentCanvas;

    std::unique_ptr<DevicesCanvas> _devicesCanvas;
    std::unique_ptr<DeviceProfilesCanvas> _deviceProfilesCanvas;
};
