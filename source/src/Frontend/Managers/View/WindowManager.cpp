#include "Frontend/Managers/View/WindowManager.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Input/InputManager.h"
#include "Frontend/Managers/Input/SelectableManager.h"
#include "Frontend/Managers/View/DrawManager.h"
#include "Backend/Managers/ApplicationManager.h"

WindowManager WindowManager::_windowManagerInstance{};

WindowManager::~WindowManager()
{
    glfwDestroyWindow(_window);
}

WindowManager& WindowManager::GetInstance()
{
    return _windowManagerInstance;
}

void WindowManager::SetSizes(int width, int height)
{
    _width = width;
    _height = height;
}

int WindowManager::GetWidth() const
{
    return _width;
}

int WindowManager::GetHeight() const
{
    return _height;
}

void WindowManager::GlfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void WindowManager::Start()
{
    SetupGLFW();

    SetupImGui();

    IMGUI_CHECKVERSION();
}

void WindowManager::SetupGLFW()
{
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfwInit())
    {
        std::__throw_runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Tell GLFW to use OpenGL 3.*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Tell GLFW to use OpenGL *.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Tell GLFW to use OpenGL *.* Core Profile

    _window = glfwCreateWindow(_width, _height, "Mouse Profile GUI", nullptr, nullptr);

    if (!_window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::__throw_runtime_error("Failed to load GLAD");
    }

    glfwSwapInterval(1); //Enable VSync
}

void WindowManager::SetupImGui() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(_window, true); //Initialize GLFW backend and install callbacks

    const char* glslVersion {"#version 330"}; //GLSL shader version
    ImGui_ImplOpenGL3_Init(glslVersion); //Initialize OpenGl 3 render backend
}

void WindowManager::Update()
{
    GestureManager& gestureManager {GestureManager::GetInstance()};

    InputManager& inputManager {InputManager::GetInstance()};

    SelectableManager& selectableManager {SelectableManager::GetInstance()};

    DrawManager& drawManager {DrawManager::GetInstance()};

    drawManager.Start();

    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImDrawList* drawList {ImGui::GetBackgroundDrawList()};

        gestureManager.Update();

        inputManager.Update();

        selectableManager.Update();

        drawManager.DrawElements(drawList);

        ImGui::Render();

        int displayWidth;
        int displayHeight;

        glfwGetFramebufferSize(_window, &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }

    Cleanse();

    ApplicationManager::GetInstance().TurnOffGUI();
}

void WindowManager::Cleanse() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}
