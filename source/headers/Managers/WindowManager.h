#pragma once
#include <memory>

class Texture;
struct ImDrawList;
struct GLFWwindow;

class WindowManager
{
private:

    static std::unique_ptr<WindowManager> _windowManagerInstance;

    int _width;
    int _height;

    GLFWwindow* _window;

    WindowManager() = default;

    static void GlfwErrorCallback(int error, const char* description);

    void SetupGLFW();

    void SetupImGui() const;

    void DrawElements(ImDrawList* drawList) const;

public:

    ~WindowManager();

    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;
    WindowManager(WindowManager&& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;

    static WindowManager& GetInstance();

    void SetSizes(int width, int height);

    void Start();

    void Update();

    void Cleanse() const;
};