#include "../../headers/Managers/GLFWManager.h"

#include <unistd.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"

#define GLFW_EXPOSE_NATIVE_WAYLAND
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "Managers/Input/InputManager.h"
#include "Managers/Input/TypeManager.h"
#include "Managers/Gestures/ClickableManager.h"
#include "Managers/Gestures/ScrollableManager.h"
#include "Managers/MVPManager.h"
#include "Managers/View/DrawManager.h"

GLFWManager* GLFWManager::_windowManagerInstance {nullptr};

GLFWManager::~GLFWManager()
{
    glfwDestroyWindow(_window);
    delete _windowManagerInstance;
}

GLFWManager& GLFWManager::GetInstance()
{
    if (_windowManagerInstance == nullptr)
    {
        _windowManagerInstance = new GLFWManager();
    }

    return *_windowManagerInstance;
}

void GLFWManager::SetInitialSize(int width, int height)
{
    _initialWidth = width;
    _initialHeight = height;

    _sizeObserver.SetValue({_initialWidth, _initialHeight});
}

WindowSize GLFWManager::GetSize() const
{
    return _sizeObserver.GetValue();
}

void GLFWManager::GlfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GLFWManager::Start()
{
    SetupGLFW();

    GrabWaylandSettings();

    SetupImGui();

    IMGUI_CHECKVERSION();
}

void GLFWManager::SetupGLFW()
{
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfwInit())
    {
        std::__throw_runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Tell GLFW to use OpenGL 3.*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Tell GLFW to use OpenGL *.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Tell GLFW to use OpenGL *.* Core Profile

    _window = glfwCreateWindow(_initialWidth, _initialHeight, "Mouse Profile GUI", nullptr, nullptr);

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

void GLFWManager::GrabWaylandSettings()
{
    _waylandSettings.display = glfwGetWaylandDisplay();

    _waylandSettings.registry = wl_display_get_registry(_waylandSettings.display);

    wl_registry_add_listener(_waylandSettings.registry, &_registryListener, &_waylandSettings);

    wl_display_roundtrip(_waylandSettings.display);
    wl_display_roundtrip(_waylandSettings.display);
}

void GLFWManager::SetupImGui() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(_window, true); //Initialize GLFW backend and install callbacks

    const char* glslVersion {"#version 330"}; //GLSL shader version
    ImGui_ImplOpenGL3_Init(glslVersion); //Initialize OpenGl 3 render backend
}

#pragma region Listeners

#include <libevdev/libevdev.h>

#pragma region Keyboard

void GLFWManager::KeyboardKeymap(void* data, wl_keyboard* waylandKeyboard, uint32_t format, int32_t file, uint32_t size)
{
    printf("[keyboard] keymap received (format=%u, size=%u)\n", format, size);
    close(file);
}

void GLFWManager::KeyboardKey(void* data, wl_keyboard* waylandKeyboard, uint32_t serial, uint32_t time, uint32_t key,
    uint32_t state)
{
    const char* name {libevdev_event_code_get_name(EV_KEY, key)};
    printf("[keyboard] %s | %d\n", name, state);
}

void GLFWManager::KeyboardModifiers(void* data, wl_keyboard* waylandKeyboard, uint32_t, uint32_t modifiersReleased,
    uint32_t modifiersLatched, uint32_t modifiersLocked, uint32_t group)
{
    printf("[keyboard] mods: depressed=%u latched=%u locked=%u group=%u\n",
           modifiersReleased, modifiersLatched, modifiersLocked, group);
}

void GLFWManager::KeyboardRepeatInfo(void* data, wl_keyboard* waylandKeyboard, int32_t rate, int32_t delay)
{
    printf("[keyboard] repeat: rate=%d delay=%d\n", rate, delay);
}

#pragma endregion

#pragma region Pointer

void GLFWManager::PointerEnter(void* data, wl_pointer* waylandPointer, uint32_t, wl_surface* waylandSurface,
    wl_fixed_t pointerXPosition, wl_fixed_t pointerYPosition)
{
    printf("[pointer] enter surface at %.2f, %.2f\n",
           wl_fixed_to_double(pointerXPosition), wl_fixed_to_double(pointerYPosition));
}

void GLFWManager::PointerLeave(void* data, wl_pointer* waylandPointer, uint32_t serial, wl_surface* waylandSurface)
{
    printf("[pointer] leave surface\n");
}

void GLFWManager::PointerMotion(void* data, wl_pointer* waylandPointer, uint32_t time, wl_fixed_t pointerXPosition,
    wl_fixed_t pointerYPosition)
{
    printf("[pointer] motion t=%u pos=%.2f,%.2f\n",
           time, wl_fixed_to_double(pointerXPosition), wl_fixed_to_double(pointerYPosition));
}

void GLFWManager::PointerButton(void* data, wl_pointer* waylandPointer, uint32_t serial, uint32_t time, uint32_t button,
    uint32_t state)
{
    const char* name {libevdev_event_code_get_name(EV_KEY, button)};
    printf("[pointer] %s | %d\n", name, state);
}

void GLFWManager::PointerAxis(void* data, wl_pointer* waylandPointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
    const char* name {libevdev_event_code_get_name(EV_REL, axis)};
    printf("[pointer] %s | %d\n", name, value);
}

#pragma endregion

#pragma region Seat

void GLFWManager::SeatCapabilities(void* data, wl_seat* waylandSeat, uint32_t caps)
{
    WaylandSettings* settings = static_cast<WaylandSettings*>(data);

    bool has_kb  = caps & WL_SEAT_CAPABILITY_KEYBOARD;
    bool has_ptr = caps & WL_SEAT_CAPABILITY_POINTER;

    printf("[seat] capabilities: keyboard=%d pointer=%d\n", has_kb, has_ptr);

    // Keyboard
    if (has_kb && !settings->keyboard)
    {
        settings->keyboard = wl_seat_get_keyboard(waylandSeat);
        wl_keyboard_add_listener(settings->keyboard, &GetInstance()._keyboardListener, nullptr);
    } else if (!has_kb && settings->keyboard)
    {
        wl_keyboard_destroy(settings->keyboard);
        settings->keyboard = nullptr;
    }

    // Pointer
    if (has_ptr && !settings->pointer)
    {
        settings->pointer = wl_seat_get_pointer(waylandSeat);
        wl_pointer_add_listener(settings->pointer, &GetInstance()._pointerListener, nullptr);
    } else if (!has_ptr && settings->pointer)
    {
        wl_pointer_destroy(settings->pointer);
        settings->pointer = nullptr;
    }
}

void GLFWManager::SeatName(void* data, wl_seat* waylandSeat, const char* name)
{
    printf("[seat] name: %s\n", name);
}

#pragma endregion

#pragma region Registry

void GLFWManager::RegistryGlobal(void* data, wl_registry* waylandRegistry, uint32_t name, const char* interface,
    uint32_t version)
{
    WaylandSettings* settings = static_cast<WaylandSettings*>(data);

    if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        settings->seat = static_cast<wl_seat*>(wl_registry_bind(waylandRegistry, name,
            &wl_seat_interface,version < 5 ? version : 5));

        wl_seat_add_listener(settings->seat, &GetInstance()._seatListener, settings);

        printf("[registry] bound wl_seat v%u\n", version < 5 ? version : 5);
    }
}

#pragma endregion

#pragma endregion

void GLFWManager::Update()
{
    InputManager& inputManager {InputManager::GetInstance()};

    TypeManager& typeManager {TypeManager::GetInstance()};

    ClickableManager& clickableManager {ClickableManager::GetInstance()};

    SelectableManager& selectableManager {SelectableManager::GetInstance()};

    ScrollableManager& scrollableManager {ScrollableManager::GetInstance()};

    MVPManager& mvpManager {MVPManager::GetInstance()};

    DrawManager& drawManager {DrawManager::GetInstance()};

    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

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

void GLFWManager::RenderWindow()
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

std::weak_ptr<std::function<void(WindowSize)>> GLFWManager::SubscribeToSizeObserver(std::function<void(WindowSize)> action)
{
    return _sizeObserver.Subscribe(std::move(action));
}

void GLFWManager::UnsubscribeToSizeObserver(std::weak_ptr<std::function<void(WindowSize)>> weakAction)
{
    _sizeObserver.Unsubscribe(weakAction);
}

void GLFWManager::Cleanse() const
{
    if (_waylandSettings.keyboard)
    {
        wl_keyboard_destroy(_waylandSettings.keyboard);
    }
    if (_waylandSettings.pointer)
    {
        wl_pointer_destroy(_waylandSettings.pointer);
    }
    if (_waylandSettings.seat)
    {
        wl_seat_destroy(_waylandSettings.seat);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}