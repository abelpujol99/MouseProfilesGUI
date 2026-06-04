#include "Managers/Input/InputManager.h"

#include "Factory/ImGuiFactory.h"
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
