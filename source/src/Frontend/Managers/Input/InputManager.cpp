#include "Frontend/Managers/Input/InputManager.h"

#include "Frontend/Factory/ImGuiFactory.h"

InputManager InputManager::_inputManagerInstance{};

InputManager& InputManager::GetInstance()
{
    return _inputManagerInstance;
}

void InputManager::Update()
{
    UpdateLastKeyPressed();

    UpdateLastCharTyped();
}

void InputManager::UpdateLastKeyPressed()
{
    Key key {ImGuiFactory::GetLastKeyPressed()};

    if (key == ImGuiKey_None)
    {
        return;
    }

    _currentPressedKeyObserver.SetValue(key);
}

void InputManager::UpdateLastCharTyped()
{
    char character {ImGuiFactory::GetLastCharTyped()};

    if (character == 0)
    {
        return;
    }

    _currentTypedCharObserver.SetValue(character);
}

std::weak_ptr<std::function<void(Key)>> InputManager::SubscribeToCurrentTypedKeyObserver(
    std::function<void(Key)>&& action)
{
    return _currentPressedKeyObserver.Subscribe(std::move(action));
}


void InputManager::UnsubscribeToCurrentTypedKeyObserver(const std::weak_ptr<std::function<void(Key)>>& weakAction)
{
    _currentPressedKeyObserver.Unsubscribe(weakAction);
}

std::weak_ptr<std::function<void(char)>> InputManager::SubscribeToCurrentTypedCharObserver(
    std::function<void(char)>&& action)
{
    return _currentTypedCharObserver.Subscribe(std::move(action));
}

void InputManager::UnsubscribeToCurrentTypedCharObserver(const std::weak_ptr<std::function<void(char)>>& weakAction)
{
    _currentTypedCharObserver.Unsubscribe(weakAction);
}
