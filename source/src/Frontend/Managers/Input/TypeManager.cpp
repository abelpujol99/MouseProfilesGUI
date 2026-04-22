#include "Frontend/Managers/Input/TypeManager.h"

#include "Frontend/Factory/ImGuiFactory.h"

TypeManager* TypeManager::_typeManagerInstance {nullptr};

TypeManager::~TypeManager() noexcept
{
    delete _typeManagerInstance;
}

TypeManager& TypeManager::GetInstance()
{
    if (_typeManagerInstance == nullptr)
    {
        _typeManagerInstance = new TypeManager();
    }

    return *_typeManagerInstance;
}

void TypeManager::Update()
{
    UpdateLastKeyPressed();

    UpdateLastCharTyped();
}

void TypeManager::UpdateLastKeyPressed()
{
    Key key {ImGuiFactory::GetLastKeyPressed()};

    if (key == ImGuiKey_None)
    {
        return;
    }

    _currentPressedKeyObserver.SetValue(key);
}

void TypeManager::UpdateLastCharTyped()
{
    char character {ImGuiFactory::GetLastCharTyped()};

    if (character == 0)
    {
        return;
    }

    _currentTypedCharObserver.SetValue(character);
}

std::weak_ptr<std::function<void(Key)>> TypeManager::SubscribeToCurrentTypedKeyObserver(
    std::function<void(Key)>&& action)
{
    return _currentPressedKeyObserver.Subscribe(std::move(action));
}

void TypeManager::UnsubscribeToCurrentTypedKeyObserver(const std::weak_ptr<std::function<void(Key)>>& weakAction)
{
    _currentPressedKeyObserver.Unsubscribe(weakAction);
}

std::weak_ptr<std::function<void(char)>> TypeManager::SubscribeToCurrentTypedCharObserver(
    std::function<void(char)>&& action)
{
    return _currentTypedCharObserver.Subscribe(std::move(action));
}

void TypeManager::UnsubscribeToCurrentTypedCharObserver(const std::weak_ptr<std::function<void(char)>>& weakAction)
{
    _currentTypedCharObserver.Unsubscribe(weakAction);
}
