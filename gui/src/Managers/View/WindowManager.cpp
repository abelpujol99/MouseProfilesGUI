#include "Managers/View/WindowManager.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "Managers/GLFWManager.h"

#include "Managers/Input/InputManager.h"
#include "Managers/Input/TypeManager.h"
#include "Managers/Gestures/ClickableManager.h"
#include "Managers/Gestures/ScrollableManager.h"
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
    InputManager& inputManager {InputManager::GetInstance()};

    inputManager.Start();

    TypeManager& typeManager {TypeManager::GetInstance()};

    ClickableManager& clickableManager {ClickableManager::GetInstance()};

    SelectableManager& selectableManager {SelectableManager::GetInstance()};

    ScrollableManager& scrollableManager {ScrollableManager::GetInstance()};

    MVPManager& mvpManager {MVPManager::GetInstance()};

    DrawManager& drawManager {DrawManager::GetInstance()};

    while (!glfwWindowShouldClose(_window))
    {
        GLFWManager::PrepareWindow();

        ImDrawList* drawList {ImGui::GetBackgroundDrawList()};

        inputManager.Update();

        typeManager.Update();

        clickableManager.Update();

        selectableManager.Update();

        scrollableManager.Update();

        drawManager.DrawElements(drawList);

        RenderWindow();
    }

    Cleanse();
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

std::weak_ptr<std::function<void(WindowSize)>> WindowManager::SubscribeToSizeObserver(
    std::function<void(WindowSize)> action)
{
    return _sizeObserver.Subscribe(std::move(action));
}

void WindowManager::UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(WindowSize)>> weakAction)
{
    _sizeObserver.Unsubscribe(weakAction);
}

void WindowManager::Cleanse() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}
