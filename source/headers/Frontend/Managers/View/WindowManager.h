#pragma once

#include "imgui.h"
#include "Utilities/Observer/ObserverSingleValue.h"

struct GLFWwindow;

class WindowManager
{
public:

    ~WindowManager();

    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;
    WindowManager(WindowManager&& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;

    static WindowManager& GetInstance();

    void SetInitialSize(int width, int height);

    void Start();

    void Update();

    std::weak_ptr<std::function<void(ImVec2)>> SubscribeToSizeObserver(std::function<void(ImVec2)> action);

    void UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(ImVec2)>> weakAction);

    void Cleanse() const;

private:

    WindowManager() = default;

    static void GlfwErrorCallback(int error, const char* description);

    void SetupGLFW();

    void SetupImGui() const;

    void RenderWindow();

    static WindowManager _windowManagerInstance;

    int _initialWidth;
    int _initialHeight;

    ObserverSingleValue<ImVec2> _sizeObserver;

    GLFWwindow* _window;
};