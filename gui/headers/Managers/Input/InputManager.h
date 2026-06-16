#pragma once

#include "imgui.h"

#include "Managers/Input/MouseButton/BaseMouseButtonState.h"
#include "Observer/ObserverMap.h"
#include "Observer/ObserverSingleValue.h"
#include "TimeUsings.h"
#include "Utilities/WaylandSettings.h"

enum class MouseButtons : char;

class InputManager
{
public:

    ~InputManager() noexcept;

    InputManager(const InputManager& other) = delete;
    InputManager& operator=(const InputManager& other) = delete;
    InputManager(InputManager&& other) = delete;
    InputManager& operator=(InputManager&& other) = delete;

    static InputManager& GetInstance();

    void Start();

    void Update();

    void OnPressButton(MouseButtons mouseButton);
    void OnReleaseButton(MouseButtons mouseButton);

    [[nodiscard]] std::weak_ptr<std::function<void(bool)>> SubscribeToMouseButtonClickEvent(MouseButtons mouseButton,
        std::function<void(bool)>&& action);

    void UnsubscribeToMouseButtonClickEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction);

    [[nodiscard]] std::weak_ptr<std::function<void(bool)>> SubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton,
        std::function<void(bool)>&& action);

    void UnsubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction);

    [[nodiscard]] std::weak_ptr<std::function<void(float)>> SubscribeToMouseScroll(std::function<void(float)>&& action);

    void UnsubscribeToMouseScroll(std::weak_ptr<std::function<void(float)>>&& weakAction);

private:

    InputManager();

    void ChangeState(MouseButtons mouseButton, std::unique_ptr<BaseMouseButtonState>&& mouseButtonState);

#pragma region Listeners

#pragma region Keyboard

    static void KeyboardKeymap(void* data, wl_keyboard* waylandKeyboard, uint32_t format, int32_t file, uint32_t size);

    static void KeyboardEnter(void* data, wl_keyboard* waylandKeyboard, uint32_t format, wl_surface* waylandSurface, wl_array* size) {};

    static void KeyboardLeave(void* data, wl_keyboard* waylandKeyboard, uint32_t format, wl_surface* waylandSurface) {};

    static void KeyboardKey(void* data, wl_keyboard* waylandKeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);

    static void KeyboardModifiers(void* data, wl_keyboard* waylandKeyboard, uint32_t, uint32_t modifiersReleased, uint32_t modifiersLatched,
        uint32_t modifiersLocked, uint32_t group);

    static void KeyboardRepeatInfo(void* data, wl_keyboard* waylandKeyboard, int32_t rate, int32_t delay);

#pragma endregion

#pragma region Mouse

    static void PointerEnter(void* data, wl_pointer* waylandPointer, uint32_t, wl_surface* waylandSurface,
        wl_fixed_t pointerXPosition, wl_fixed_t pointerYPosition);

    static void PointerLeave(void* data, wl_pointer* waylandPointer, uint32_t serial, wl_surface* waylandSurface);

    static void PointerMotion(void* data, wl_pointer* waylandPointer, uint32_t time, wl_fixed_t pointerXPosition,
        wl_fixed_t pointerYPosition);

    static void PointerButton(void* data, wl_pointer* waylandPointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);

    static void PointerAxis(void* data, wl_pointer* waylandPointer, uint32_t time, uint32_t axis, wl_fixed_t value);

    static void PointerFrame(void* data, wl_pointer* waylandPointer) {};

    static void PointerAxisSource(void* data, wl_pointer* waylandPointer, uint32_t axisSource) {};

    static void PointerAxisStop(void* data, wl_pointer* waylandPointer, uint32_t time, uint32_t axis) {};

    static void PointerAxisDiscrete(void* data, wl_pointer* waylandPointer, uint32_t axis, int32_t discrete) {};

#pragma endregion

#pragma region Seat

    static void SeatCapabilities(void* data, wl_seat* waylandSeat, uint32_t caps);

    static void SeatName(void* data, wl_seat* waylandSeat, const char* name);

#pragma endregion

#pragma region Registry

    static void RegistryGlobal(void* data, wl_registry* waylandRegistry, uint32_t name, const char* interface, uint32_t version);

    static void RegistryGlobalRemove(void* data, wl_registry* waylandRegistry, uint32_t name) {};

#pragma endregion

#pragma endregion

    static InputManager* _inputManagerInstance;

    std::unique_ptr<BaseMouseButtonState> _mouseButtonState[ImGuiMouseButton_COUNT];

    ObserverMap<MouseButtons, bool> _mouseClickInputObserverMap;
    ObserverMap<MouseButtons, bool> _mouseReleaseInputObserverMap;

    TimePoint _mousePressedTimePoint[ImGuiMouseButton_COUNT];

    ObserverSingleValue<Duration> _mouseButtonsTimePressed[ImGuiMouseButton_COUNT];

    ObserverSingleValue<float> _mouseScrollObserver;

    WaylandSettings _waylandSettings;

    const wl_keyboard_listener _keyboardListener = {
        .keymap = KeyboardKeymap,
        .enter = KeyboardEnter,
        .leave = KeyboardLeave,
        .key = KeyboardKey,
        .modifiers = KeyboardModifiers,
        .repeat_info = KeyboardRepeatInfo,
    };

    const wl_pointer_listener _pointerListener = {
        .enter = PointerEnter,
        .leave = PointerLeave,
        .motion = PointerMotion,
        .button = PointerButton,
        .axis = PointerAxis,
        .frame = PointerFrame,
        .axis_source = PointerAxisSource,
        .axis_stop = PointerAxisStop,
        .axis_discrete = PointerAxisDiscrete
    };

    const wl_seat_listener _seatListener = {
        .capabilities = SeatCapabilities,
        .name = SeatName
    };

    const wl_registry_listener _registryListener = {
        .global = RegistryGlobal,
        .global_remove = RegistryGlobalRemove
    };
};