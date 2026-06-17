#include "Managers/View/WindowManager.h"

#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "Managers/GLFWManager.h"

#include "Managers/Input/InputManager.h"
#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

std::unique_ptr<WindowManager> WindowManager::_windowManagerInstance {nullptr};

WindowManager& WindowManager::GetInstance()
{
    if (_windowManagerInstance == nullptr)
    {
        _windowManagerInstance.reset(new WindowManager());
    }

    return *_windowManagerInstance;
}

void WindowManager::SetInitialSize(int width, int height)
{
    _initialWidth = width;
    _initialHeight = height;

    _sizeObserver.SetValue({_initialWidth, _initialHeight});
}

void WindowManager::Start()
{
    _window = GLFWManager::CreateWindow(_initialHeight, _initialHeight, "Mouse Profiles GUI");
}

void WindowManager::Update()
{
    InputManager::GetInstance().Start();

    MVPManager::GetInstance();

    DrawManager& drawManager {DrawManager::GetInstance()};

    while (!glfwWindowShouldClose(_window))
    {
        GLFWManager::PrepareWindow();

        drawManager.DrawElements(ImGui::GetBackgroundDrawList());

        RenderWindow();
    }

    GLFWManager::CleanseWindow(_window);
}

void WindowManager::RenderWindow()
{
    ImGui::Render();

    int displayWidth;
    int displayHeight;

    glfwGetFramebufferSize(_window, &displayWidth, &displayHeight);
    glViewport(0, 0, displayWidth, displayHeight);
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);

    _sizeObserver.SetValue({displayWidth, displayHeight});
}

std::weak_ptr<std::function<void(WindowSize)>> WindowManager::SubscribeToSizeObserver(std::function<void(WindowSize)>&& action)
{
    return _sizeObserver.Subscribe(std::move(action));
}

void WindowManager::UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(WindowSize)>>&& weakAction)
{
    _sizeObserver.Unsubscribe(std::move(weakAction));
}