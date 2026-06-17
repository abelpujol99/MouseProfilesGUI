#include "Managers/Input/InputManager.h"

#include <unistd.h>
#include <sys/mman.h>
#include <bits/mman-linux.h>
#include <libevdev/libevdev.h>

#include "KeyDefines.h"
#include "Factory/ImGuiFactory.h"
#include "Managers/GLFWManager.h"
#include "Managers/Application/ApplicationManager.h"
#include "Managers/Gestures/ClickableManager.h"
#include "Managers/Gestures/ScrollableManager.h"
#include "Managers/Gestures/SelectableManager.h"
#include "Utilities/Math.h"

#define XKB_OFFSET 8

std::unique_ptr<InputManager> InputManager::_inputManagerInstance {nullptr};

InputManager::InputManager()
{
    _mouseButtonsTimePressed->SetAction([&](uint32_t timePressed) {

        return timePressed;
    });
}

InputManager::~InputManager() noexcept
{
    GLFWManager::CleanseInput(_waylandContext);
}

InputManager& InputManager::GetInstance()
{
    if (_inputManagerInstance == nullptr)
    {
        _inputManagerInstance.reset(new InputManager());
    }

    return *_inputManagerInstance;
}

void InputManager::Start()
{
    _waylandContext = GLFWManager::GetWaylandContext(&_registryListener);
}

std::weak_ptr<std::function<void(const char*)>> InputManager::SubscribeToKeyPressed(
    std::function<void(const char*)>&& action)
{
    return _keyPressed.Subscribe(std::move(action));
}

void InputManager::UnsubscribeToKeyPressed(std::weak_ptr<std::function<void(const char*)>>&& action)
{
    _keyPressed.Unsubscribe(std::move(action));
}

std::weak_ptr<std::function<void(std::string)>> InputManager::SubscribeToCharPressed(
    std::function<void(std::string)>&& action)
{
    return _charPressed.Subscribe(std::move(action));
}

void InputManager::UnsubscribeToCharPressed(std::weak_ptr<std::function<void(std::string)>>&& action)
{
    _charPressed.Unsubscribe(std::move(action));
}

ImVec2 InputManager::GetMousePosition() const
{
    return _mousePosition;
}

#pragma region Listeners

#pragma region Keyboard

void InputManager::KeyboardKeymap(void* data, wl_keyboard* waylandKeyboard, uint32_t format, int32_t file, uint32_t size)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};
    WaylandContext& context {inputManager->_waylandContext};

    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
    {
        close(file);
        return;
    }

    char* mapString {static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_PRIVATE, file, 0))};

    if (mapString == MAP_FAILED)
    {
        close(file);
        return;
    }

    if (context.xkbContext == nullptr)
    {
        context.xkbContext = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    }
    if (context.xkbState != nullptr)
    {
        xkb_state_unref(context.xkbState);
    }
    if (context.xkbKeymap != nullptr)
    {
        xkb_keymap_unref(context.xkbKeymap);
    }

    context.xkbKeymap = xkb_keymap_new_from_string(context.xkbContext, mapString, XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS);

    context.xkbState = xkb_state_new(context.xkbKeymap);

    munmap(mapString, size);

    close(file);
}

void InputManager::KeyboardKey(void* data, wl_keyboard* waylandKeyboard, uint32_t serial, uint32_t time, uint32_t key,
    uint32_t state)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};
    WaylandContext& context {inputManager->_waylandContext};

    if (context.xkbState == nullptr || state != WL_KEYBOARD_KEY_STATE_PRESSED)
    {
        return;
    }

    //Physical Key
    inputManager->_keyPressed.SendValue(libevdev_event_code_get_name(EV_KEY, key));

    //Char
    uint32_t keyCode {key + XKB_OFFSET};
    xkb_keysym_t sym = xkb_state_key_get_one_sym(context.xkbState, keyCode);

    switch (sym) {
        case XKB_KEY_BackSpace:
            inputManager->_charPressed.SendValue(BACKSPACE);
            return;
        case XKB_KEY_Delete:
            inputManager->_charPressed.SendValue(DELETE);
            return;
        case XKB_KEY_space:
            inputManager->_charPressed.SendValue(SPACE_BAR);
            return;
        case XKB_KEY_Up:
            inputManager->_charPressed.SendValue(UP_ARROW);
            return;
        case XKB_KEY_Left:
            inputManager->_charPressed.SendValue(LEFT_ARROW);
            return;
        case XKB_KEY_Right:
            inputManager->_charPressed.SendValue(RIGHT_ARROW);
            return;
        case XKB_KEY_Down:
            inputManager->_charPressed.SendValue(DOWN_ARROW);
            return;
        case XKB_KEY_Home:
            inputManager->_charPressed.SendValue(HOME);
            return;
        case XKB_KEY_End:
            inputManager->_charPressed.SendValue(END);
            return;
        default:
            break;
    }

    char utf8[8] = {0};
    int length {xkb_state_key_get_utf8(context.xkbState, keyCode, utf8, sizeof(utf8))};

    if (length > 0)
    {
        inputManager->_charPressed.SendValue(utf8);
    }
}

void InputManager::KeyboardModifiers(void* data, wl_keyboard* waylandKeyboard, uint32_t, uint32_t modifiersPressed,
    uint32_t modifiersLatched, uint32_t modifiersLocked, uint32_t group)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};
    WaylandContext& context {inputManager->_waylandContext};

    if (context.xkbState == nullptr)
    {
        return;
    }

    xkb_state_update_mask(context.xkbState, modifiersPressed, modifiersLatched, modifiersLocked, 0, 0, group);
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
    ApplicationManager::GetInstance().OnGainFocus();
}

void InputManager::PointerLeave(void* data, wl_pointer* waylandPointer, uint32_t serial, wl_surface* waylandSurface)
{
    ApplicationManager::GetInstance().OnLoseFocus();
}

void InputManager::PointerMotion(void* data, wl_pointer* waylandPointer, uint32_t time, wl_fixed_t pointerXPosition,
    wl_fixed_t pointerYPosition)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};

    inputManager->_mousePosition = {static_cast<float>(wl_fixed_to_double(pointerXPosition)), static_cast<float>(wl_fixed_to_double(pointerYPosition))};
}

void InputManager::PointerButton(void* data, wl_pointer* waylandPointer, uint32_t serial, uint32_t time, uint32_t button,
    uint32_t state)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};

    const char* name {libevdev_event_code_get_name(EV_KEY, button)};

    if (state == 1)
    {
        inputManager->_mousePressedTimePoint[button] = time;
        inputManager->_keyPressed.SendValue(name);
        return;
    }

    inputManager->_mouseButtonsTimePressed->SendValue(time - inputManager->_mousePressedTimePoint[button]);

    ClickableManager::GetInstance().OnClick(inputManager->_mousePosition);
    SelectableManager::GetInstance().OnSelect(inputManager->_mousePosition);
}

void InputManager::PointerAxis(void* data, wl_pointer* waylandPointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
    InputManager* inputManager {static_cast<InputManager*>(data)};

    float valueClamped {Utilities::Math::Clamp<float>(wl_fixed_from_double(value), -1.f, 1.f)};

    const char* name {libevdev_event_code_get_name(EV_REL, axis)};
    printf("[pointer] %s | %d\n", name, value);

    if (axis == 0) //VerticalScroll
    {
        ScrollableManager::GetInstance().OnScroll(valueClamped, inputManager->_mousePosition);
    }
    else //HorizontalScroll
    {
        //inputManager->_mouseScrollObserver.SetValue(valueFixed);
    }
}

#pragma endregion

#pragma region Seat

void InputManager::SeatCapabilities(void* data, wl_seat* waylandSeat, uint32_t caps)
{
    WaylandContext* settings = static_cast<WaylandContext*>(data);

    bool has_kb  = caps & WL_SEAT_CAPABILITY_KEYBOARD;
    bool has_ptr = caps & WL_SEAT_CAPABILITY_POINTER;

    printf("[seat] capabilities: keyboard=%d pointer=%d\n", has_kb, has_ptr);

    // Keyboard
    if (has_kb && !settings->keyboard)
    {
        settings->keyboard = wl_seat_get_keyboard(waylandSeat);
        wl_keyboard_add_listener(settings->keyboard, &GetInstance()._keyboardListener, &GetInstance());
    }
    else if (!has_kb && settings->keyboard)
    {
        wl_keyboard_destroy(settings->keyboard);
        settings->keyboard = nullptr;
    }

    // Pointer
    if (has_ptr && !settings->pointer)
    {
        settings->pointer = wl_seat_get_pointer(waylandSeat);
        wl_pointer_add_listener(settings->pointer, &GetInstance()._pointerListener, &GetInstance());
    }
    else if (!has_ptr && settings->pointer)
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
    WaylandContext* settings = static_cast<WaylandContext*>(data);

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
