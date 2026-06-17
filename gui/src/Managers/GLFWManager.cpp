#include "Managers/GLFWManager.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"

#define GLFW_EXPOSE_NATIVE_WAYLAND
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <cstdio>

void GLFWManager::GlfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

GLFWwindow* GLFWManager::CreateWindow(int width, int height, const char* windowName)
{
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfwInit())
    {
        std::__throw_runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Tell GLFW to use OpenGL 3.*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Tell GLFW to use OpenGL *.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Tell GLFW to use OpenGL *.* Core Profile

    GLFWwindow* window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::__throw_runtime_error("Failed to load GLAD");
    }

    glfwSwapInterval(1); //Enable VSync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true); //Initialize GLFW backend and install callbacks

    const char* glslVersion {"#version 330"}; //GLSL shader version
    ImGui_ImplOpenGL3_Init(glslVersion); //Initialize OpenGl 3 render backend

    return window;
}

WaylandContext GLFWManager::GetWaylandContext(const wl_registry_listener* registryListener)
{
    WaylandContext waylandContext;

    waylandContext.display = glfwGetWaylandDisplay();

    waylandContext.registry = wl_display_get_registry(waylandContext.display);

    wl_registry_add_listener(waylandContext.registry, registryListener, &waylandContext);

    wl_display_roundtrip(waylandContext.display);
    wl_display_roundtrip(waylandContext.display);

    return waylandContext;
}

void GLFWManager::PrepareWindow()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GLFWManager::CleanseWindow(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    window = nullptr;
}

void GLFWManager::CleanseInput(const WaylandContext& waylandContext) noexcept
{
    wl_keyboard_destroy(waylandContext.keyboard);
    wl_pointer_destroy(waylandContext.pointer);
    wl_seat_destroy(waylandContext.seat);
    xkb_state_unref(waylandContext.xkbState);
    xkb_keymap_unref(waylandContext.xkbKeymap);
    xkb_context_unref(waylandContext.xkbContext);
}
