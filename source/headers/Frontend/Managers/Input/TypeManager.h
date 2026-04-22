#pragma once

#include "Frontend/KeyUsings.h"

#include "Utilities/Observer/ObserverSingleValue.h"

class TypeManager
{

public:

    ~TypeManager() noexcept;

    TypeManager(const TypeManager& other) = delete;
    TypeManager& operator=(const TypeManager& other) = delete;
    TypeManager(TypeManager&& other) = delete;
    TypeManager& operator=(TypeManager&& other) = delete;

    static TypeManager& GetInstance();

    void Update();

    std::weak_ptr<std::function<void(Key)>> SubscribeToCurrentTypedKeyObserver(std::function<void(Key)>&& action);
    void UnsubscribeToCurrentTypedKeyObserver(const std::weak_ptr<std::function<void(Key)>>& weakAction);

    std::weak_ptr<std::function<void(char)>> SubscribeToCurrentTypedCharObserver(std::function<void(char)>&& action);
    void UnsubscribeToCurrentTypedCharObserver(const std::weak_ptr<std::function<void(char)>>& weakAction);

private:

    TypeManager() = default;

    void UpdateLastKeyPressed();

    void UpdateLastCharTyped();

    static TypeManager* _typeManagerInstance;

    ObserverSingleValue<Key> _currentPressedKeyObserver;

    ObserverSingleValue<char> _currentTypedCharObserver;
};