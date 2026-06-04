#pragma once

#include "imgui.h"

#include "Managers/Input/MouseButton/BaseMouseButtonState.h"
#include "Observer/ObserverMap.h"
#include "Observer/ObserverSingleValue.h"
#include "TimeUsings.h"

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

    void ChangeState(MouseButtons mouseButton, std::unique_ptr<BaseMouseButtonState>&& mouseButtonState);

    InputManager();

    static InputManager* _inputManagerInstance;

    std::unique_ptr<BaseMouseButtonState> _mouseButtonState[ImGuiMouseButton_COUNT];

    ObserverMap<MouseButtons, bool> _mouseClickInputObserverMap;
    ObserverMap<MouseButtons, bool> _mouseReleaseInputObserverMap;

    TimePoint _mousePressedTimePoint[ImGuiMouseButton_COUNT];

    ObserverSingleValue<Duration> _mouseButtonsTimePressed[ImGuiMouseButton_COUNT];

    ObserverSingleValue<float> _mouseScrollObserver;
};