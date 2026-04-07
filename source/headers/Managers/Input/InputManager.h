#pragma once

#include "KeyUsings.h"

#include "Observers/ObserverSingleValue.h"

class InputManager
{

public:

    ~InputManager() = default;

    InputManager(const InputManager& other) = delete;
    InputManager& operator=(const InputManager& other) = delete;
    InputManager(InputManager&& other) = delete;
    InputManager& operator=(InputManager&& other) = delete;

    static InputManager& GetInstance();

    void Update();

    std::weak_ptr<std::function<void(KeyChain)>> SubscribeToCurrentKeyChainObserver(std::function<void(KeyChain)>&& action);
    void UnsubscribeToCurrentKeyChainObserver(const std::weak_ptr<std::function<void(KeyChain)>>& weakAction);

private:

    InputManager() = default;

    static InputManager _inputManagerInstance;

    ObserverSingleValue<KeyChain> _currentKeyChainObserver;
};