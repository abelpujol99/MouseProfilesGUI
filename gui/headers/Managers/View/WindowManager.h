#pragma once

#include "Observer/ObserverSingleValue.h"
#include "Utilities/Structs/WindowSize.h"

struct GLFWwindow;

class WindowManager
{
public:

    ~WindowManager() = default;

    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;
    WindowManager(WindowManager&& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;

    static WindowManager& GetInstance();

    void SetInitialSize(int width, int height);

    void Start();

    void Update();

    std::weak_ptr<std::function<void(WindowSize)>> SubscribeToSizeObserver(std::function<void(WindowSize)>&& action);
    void UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(WindowSize)>>&& weakAction);

private:

    WindowManager() = default;

    void RenderWindow();

    static std::unique_ptr<WindowManager> _windowManagerInstance;

    int _initialWidth;
    int _initialHeight;

    ObserverSingleValue<WindowSize> _sizeObserver;

    GLFWwindow* _window;
};