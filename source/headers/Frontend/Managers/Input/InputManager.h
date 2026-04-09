#pragma once

#include "Frontend/KeyUsings.h"

#include "Utilities/Observer/ObserverSingleValue.h"

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

    std::weak_ptr<std::function<void(Key)>> SubscribeToCurrentTypedKeyObserver(std::function<void(Key)>&& action);
    void UnsubscribeToCurrentTypedKeyObserver(const std::weak_ptr<std::function<void(Key)>>& weakAction);

    std::weak_ptr<std::function<void(char)>> SubscribeToCurrentTypedCharObserver(std::function<void(char)>&& action);
    void UnsubscribeToCurrentTypedCharObserver(const std::weak_ptr<std::function<void(char)>>& weakAction);

private:

    InputManager() = default;

    void UpdateLastKeyPressed();

    void UpdateLastCharTyped();

    static InputManager _inputManagerInstance;

    ObserverSingleValue<Key> _currentPressedKeyObserver;

    ObserverSingleValue<char> _currentTypedCharObserver;
};