#pragma once

#include "imgui.h"

#include "TimeUsings.h"
#include "Observers/ObserverMap.h"
#include "Observers/ObserverSingleValue.h"

enum class MouseButtons : char;
class BaseMouseButtonState;

class GestureManager
{
public:

    ~GestureManager() = default;

    GestureManager(const GestureManager& other) = delete;
    GestureManager& operator=(const GestureManager& other) = delete;
    GestureManager(GestureManager&& other) = delete;
    GestureManager& operator=(GestureManager&& other) = delete;

    static GestureManager& GetInstance();

    void Update();

    void OnPressButton(MouseButtons mouseButton);
    void OnReleaseButton(MouseButtons mouseButton);

    [[nodiscard]] std::weak_ptr<std::function<void(bool)>> SubscribeToMouseButtonClickEvent(MouseButtons mouseButton,
        std::function<void(bool)>&& action);

    [[nodiscard]] std::weak_ptr<std::function<void(bool)>> SubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton,
        std::function<void(bool)>&& action);

    void UnsubscribeToMouseButtonClickEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction);
    void UnsubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction);

private:

    void ChangeState(MouseButtons mouseButton, std::unique_ptr<BaseMouseButtonState>&& mouseButtonState);

    GestureManager();

    static GestureManager _gestureManagerInstance;

    ObserverSingleValue<ImVec2> _mousePositionObserver;

    std::unique_ptr<BaseMouseButtonState> _mouseButtonState[ImGuiMouseButton_COUNT];

    ObserverMap<MouseButtons, bool> _mouseClickInputObserverMap;
    ObserverMap<MouseButtons, bool> _mouseReleaseInputObserverMap;

    TimePoint _mousePressedTimePoint[ImGuiMouseButton_COUNT];

    ObserverSingleValue<Duration> _mouseButtonsTimePressed[ImGuiMouseButton_COUNT];
};