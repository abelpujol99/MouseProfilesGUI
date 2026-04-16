#pragma once

#include <memory>

#include "imgui.h"

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

    void SetSizes(int width, int height);

    [[nodiscard]] ImVec2 GetSize() const;

    [[nodiscard]] float GetDesiredWidth() const;

    [[nodiscard]] float GetDesiredHeight() const;

    void Start();

    void Update();

    void Cleanse() const;

private:

    WindowManager() = default;

    static void GlfwErrorCallback(int error, const char* description);

    void SetupGLFW();

    void SetupImGui() const;

    void RenderWindow() const;

    static WindowManager _windowManagerInstance;

    int _desiredWidth;
    int _desiredHeight;

    GLFWwindow* _window;
};