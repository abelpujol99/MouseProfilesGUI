#pragma once

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

    [[nodiscard]] float GetWidth() const;

    [[nodiscard]] float GetHeight() const;

    void Start();

    void Update();

    void Cleanse() const;

private:

    WindowManager() = default;

    static void GlfwErrorCallback(int error, const char* description);

    void SetupGLFW();

    void SetupImGui() const;

    static WindowManager _windowManagerInstance;

    int _width;
    int _height;

    GLFWwindow* _window;
};