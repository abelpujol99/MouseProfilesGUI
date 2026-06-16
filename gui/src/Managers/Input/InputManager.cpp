#include "Managers/Input/InputManager.h"

#include <unistd.h>
#include <libevdev/libevdev.h>

#include "Factory/ImGuiFactory.h"
#include "Managers/GLFWManager.h"
#include "Managers/Input/MouseButton/MouseButtons.h"
#include "Managers/Input/MouseButton/ReleasedState.h"
#include "Managers/Input/MouseButton/ClickedState.h"

InputManager* InputManager::_inputManagerInstance {nullptr};

InputManager::InputManager()
{
    MouseButtons mouseMaxButtons {MouseButtons::COUNT};

    for (MouseButtons i{MouseButtons::LEFT}; i != mouseMaxButtons; ++i)
    {
        _mouseButtonState[static_cast<int>(i)] = std::make_unique<ReleasedState>(i);

        _mouseClickInputObserverMap.AddEntry(i, [&](bool clicked) {

            if (clicked)
            {
                _mousePressedTimePoint[static_cast<int>(i)] = SystemClock::now();
            }

            return clicked;
        });

        _mouseReleaseInputObserverMap.AddEntry(i, [&](bool released) {

            if (released)
            {
                _mouseButtonsTimePressed->SetValue(SystemClock::now() - _mousePressedTimePoint[static_cast<int>(i)]);
            }

            return released;
        });
    }

    _mouseButtonsTimePressed->SetAction([&](Duration timePressed) {

        return timePressed;
    });
}

InputManager::~InputManager() noexcept
{
    GLFWManager::CleanseInput(_waylandSettings);

    delete _inputManagerInstance;
}

InputManager& InputManager::GetInstance()
{
    if (_inputManagerInstance == nullptr)
    {
        _inputManagerInstance = new InputManager();
    }

    return *_inputManagerInstance;
}

void InputManager::Start()
{
    _waylandSettings = GLFWManager::GetWaylandSettings(&_registryListener);
}

void InputManager::Update()
{
    MouseButtons mouseMaxButtons {MouseButtons::COUNT};

    for (MouseButtons i{MouseButtons::LEFT}; i != mouseMaxButtons; ++i)
    {
        _mouseButtonState[static_cast<int>(i)]->CheckState();
    }

    _mouseScrollObserver.SetValue(ImGuiFactory::GetMouseScroll());
}

void InputManager::OnPressButton(MouseButtons mouseButton)
{
    ChangeState(mouseButton, std::make_unique<ClickedState>(mouseButton));

    _mouseClickInputObserverMap.SetValue(mouseButton, true);
    _mouseReleaseInputObserverMap.SetValue(mouseButton, false);
}

void InputManager::OnReleaseButton(MouseButtons mouseButton)
{
    ChangeState(mouseButton, std::make_unique<ReleasedState>(mouseButton));

    _mouseClickInputObserverMap.SetValue(mouseButton, false);
    _mouseReleaseInputObserverMap.SetValue(mouseButton, true);
}

std::weak_ptr<std::function<void(bool)>> InputManager::SubscribeToMouseButtonClickEvent(MouseButtons mouseButton,
    std::function<void(bool)>&& action)
{
    return _mouseClickInputObserverMap.Subscribe(mouseButton, std::move(action));
}

std::weak_ptr<std::function<void(bool)>> InputManager::SubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton,
    std::function<void(bool)>&& action)
{
    return _mouseReleaseInputObserverMap.Subscribe(mouseButton, std::move(action));
}

void InputManager::UnsubscribeToMouseButtonClickEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction)
{
    _mouseClickInputObserverMap.Unsubscribe(mouseButton, std::move(weakAction));
}

void InputManager::UnsubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction)
{
    _mouseReleaseInputObserverMap.Unsubscribe(mouseButton, std::move(weakAction));
}

std::weak_ptr<std::function<void(float)>> InputManager::SubscribeToMouseScroll(std::function<void(float)>&& action)
{
    return _mouseScrollObserver.Subscribe(action);
}

void InputManager::UnsubscribeToMouseScroll(std::weak_ptr<std::function<void(float)>>&& weakAction)
{
    _mouseScrollObserver.Unsubscribe(weakAction);
}

void InputManager::ChangeState(MouseButtons mouseButton, std::unique_ptr<BaseMouseButtonState>&& mouseButtonState)
{
    _mouseButtonState[static_cast<int>(mouseButton)] = std::move(mouseButtonState);
}

#pragma region Listeners

#pragma region Keyboard

void InputManager::KeyboardKeymap(void* data, wl_keyboard* waylandKeyboard, uint32_t format, int32_t file, uint32_t size)
{
    printf("[keyboard] keymap received (format=%u, size=%u)\n", format, size);
    close(file);
}

void InputManager::KeyboardKey(void* data, wl_keyboard* waylandKeyboard, uint32_t serial, uint32_t time, uint32_t key,
    uint32_t state)
{
    const char* name {libevdev_event_code_get_name(EV_KEY, key)};
    printf("[keyboard] %s | %d\n", name, state);
}

void InputManager::KeyboardModifiers(void* data, wl_keyboard* waylandKeyboard, uint32_t, uint32_t modifiersReleased,
    uint32_t modifiersLatched, uint32_t modifiersLocked, uint32_t group)
{
    printf("[keyboard] mods: depressed=%u latched=%u locked=%u group=%u\n",
           modifiersReleased, modifiersLatched, modifiersLocked, group);
}

void InputManager::KeyboardRepeatInfo(void* data, wl_keyboard* waylandKeyboard, int32_t rate, int32_t delay)
{
    printf("[keyboard] repeat: rate=%d delay=%d\n", rate, delay);
}

#pragma endregion

#pragma region Pointer

void InputManager::PointerEnter(void* data, wl_pointer* waylandPointer, uint32_t, wl_surface* waylandSurface,
    wl_fixed_t pointerXPosition, wl_fixed_t pointerYPosition)
{
    printf("[pointer] enter surface at %.2f, %.2f\n",
           wl_fixed_to_double(pointerXPosition), wl_fixed_to_double(pointerYPosition));
}

void InputManager::PointerLeave(void* data, wl_pointer* waylandPointer, uint32_t serial, wl_surface* waylandSurface)
{
    printf("[pointer] leave surface\n");
}

void InputManager::PointerMotion(void* data, wl_pointer* waylandPointer, uint32_t time, wl_fixed_t pointerXPosition,
    wl_fixed_t pointerYPosition)
{
    printf("[pointer] motion t=%u pos=%.2f,%.2f\n",
           time, wl_fixed_to_double(pointerXPosition), wl_fixed_to_double(pointerYPosition));
}

void InputManager::PointerButton(void* data, wl_pointer* waylandPointer, uint32_t serial, uint32_t time, uint32_t button,
    uint32_t state)
{
    const char* name {libevdev_event_code_get_name(EV_KEY, button)};
    printf("[pointer] %s | %d\n", name, state);
}

void InputManager::PointerAxis(void* data, wl_pointer* waylandPointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
    const char* name {libevdev_event_code_get_name(EV_REL, axis)};
    printf("[pointer] %s | %d\n", name, value);
}

#pragma endregion

#pragma region Seat

void InputManager::SeatCapabilities(void* data, wl_seat* waylandSeat, uint32_t caps)
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

void InputManager::SeatName(void* data, wl_seat* waylandSeat, const char* name)
{
    printf("[seat] name: %s\n", name);
}

#pragma endregion

#pragma region Registry

void InputManager::RegistryGlobal(void* data, wl_registry* waylandRegistry, uint32_t name, const char* interface,
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
