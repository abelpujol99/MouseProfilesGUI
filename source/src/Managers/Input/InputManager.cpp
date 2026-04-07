#include "Managers/Input/InputManager.h"

#include "Factories/ImGui/ImGuiFactory.h"

InputManager InputManager::_inputManagerInstance{};

InputManager& InputManager::GetInstance()
{
    return _inputManagerInstance;
}

void InputManager::Update()
{
    KeyChain keyChain {ImGuiFactory::GetLastKeyPressed()};

    if (keyChain == ImGuiKey_None)
    {
        return;
    }

    _currentKeyChainObserver.SetValue(keyChain);
}

std::weak_ptr<std::function<void(KeyChain)>> InputManager::SubscribeToCurrentKeyChainObserver(
    std::function<void(KeyChain)>&& action)
{
    return _currentKeyChainObserver.Subscribe(std::move(action));
}


void InputManager::UnsubscribeToCurrentKeyChainObserver(const std::weak_ptr<std::function<void(KeyChain)>>& weakAction)
{
    _currentKeyChainObserver.Unsubscribe(weakAction);
}