#include "Managers/Gesture/GestureManager.h"

#include "imgui.h"

#include "Factories/ImGui/ImGuiFactory.h"
#include "Managers/Gesture/MouseButton/ClickedState.h"
#include "Managers/Gesture/MouseButton/ReleasedState.h"

GestureManager GestureManager::_gestureManagerInstance{};

GestureManager::GestureManager()
{
    _mousePositionObserver.SetAction([&](ImVec2 vector) {

        return vector;
    });

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

GestureManager& GestureManager::GetInstance()
{
    return _gestureManagerInstance;
}

void GestureManager::Update()
{
    MouseButtons mouseMaxButtons {MouseButtons::COUNT};

    for (MouseButtons i{MouseButtons::LEFT}; i != mouseMaxButtons; ++i)
    {
        _mouseButtonState[static_cast<int>(i)]->CheckState();
    }

    _mousePositionObserver.SetValue(ImGuiFactory::GetMousePosition());
}

void GestureManager::OnPressButton(MouseButtons mouseButton)
{
    ChangeState(mouseButton, std::make_unique<ClickedState>(mouseButton));

    _mouseClickInputObserverMap.SetValue(mouseButton, true);
    _mouseReleaseInputObserverMap.SetValue(mouseButton, false);
}

void GestureManager::OnReleaseButton(MouseButtons mouseButton)
{
    ChangeState(mouseButton, std::make_unique<ReleasedState>(mouseButton));

    _mouseClickInputObserverMap.SetValue(mouseButton, false);
    _mouseReleaseInputObserverMap.SetValue(mouseButton, true);
}

std::weak_ptr<std::function<void(bool)>> GestureManager::SubscribeToMouseButtonClickEvent(MouseButtons mouseButton,
    std::function<void(bool)>&& action)
{
    return _mouseClickInputObserverMap.Subscribe(mouseButton, std::move(action));
}

std::weak_ptr<std::function<void(bool)>> GestureManager::SubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton,
    std::function<void(bool)>&& action)
{
    return _mouseReleaseInputObserverMap.Subscribe(mouseButton, std::move(action));
}

void GestureManager::UnsubscribeToMouseButtonClickEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction)
{
    _mouseClickInputObserverMap.Unsubscribe(mouseButton, std::move(weakAction));
}

void GestureManager::UnsubscribeToMouseButtonReleaseEvent(MouseButtons mouseButton, std::weak_ptr<std::function<void(bool)>>&& weakAction)
{
    _mouseReleaseInputObserverMap.Unsubscribe(mouseButton, std::move(weakAction));
}

void GestureManager::ChangeState(MouseButtons mouseButton, std::unique_ptr<BaseMouseButtonState>&& mouseButtonState)
{
    _mouseButtonState[static_cast<int>(mouseButton)] = std::move(mouseButtonState);
}
