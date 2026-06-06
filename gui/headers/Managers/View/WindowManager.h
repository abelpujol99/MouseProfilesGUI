#pragma once

#include "Utilities/Structs/WindowSize.h"
#include "Observer/ObserverSingleValue.h"

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

    [[nodiscard]] WindowSize GetSize() const;

    void Start();

    void Update();

    std::weak_ptr<std::function<void(WindowSize)>> SubscribeToSizeObserver(std::function<void(WindowSize)> action);

    void UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(WindowSize)>> weakAction);

    void Cleanse() const;

private:

    WindowManager() = default;

    static void GlfwErrorCallback(int error, const char* description);

    void SetupGLFW();

    void SetupImGui() const;

    void RenderWindow();

    static WindowManager* _windowManagerInstance;

    int _initialWidth;
    int _initialHeight;

    ObserverSingleValue<WindowSize> _sizeObserver;

    GLFWwindow* _window;
};