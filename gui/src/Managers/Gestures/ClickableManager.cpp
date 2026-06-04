#include "Managers/Gestures/ClickableManager.h"

#include "Factory/ImGuiFactory.h"
#include "Managers/Input/InputManager.h"
#include "Managers/Input/MouseButton/MouseButtons.h"
#include "Utilities/Boundaries.h"
#include "UI/Helpers/IClickable.h"

ClickableManager* ClickableManager::_clickableManagerInstance {nullptr};

ClickableManager::ClickableManager()
{
    _onLeftMouseButtonReleasedWeakAction = InputManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
            [&](bool value) {
                _hasLeftMouseButtonReleased = value;
        });
}

ClickableManager::~ClickableManager() noexcept
{
    delete _clickableManagerInstance;
}

ClickableManager& ClickableManager::GetInstance()
{
    if (_clickableManagerInstance == nullptr)
    {
        _clickableManagerInstance = new ClickableManager();
    }

    return *_clickableManagerInstance;
}

void ClickableManager::Update()
{
    if (!_hasLeftMouseButtonReleased)
    {
        return;
    }

    _hasLeftMouseButtonReleased = false;

    ImVec2 mousePosition {ImGuiFactory::GetMousePosition()};

    for (auto clickable : _clickables)
    {
        if (!clickable->CanBeClicked() ||
            !Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, clickable->GetParentPosition(),
                clickable->GetParentBottomRightPosition()))
        {
            continue;
        }

        clickable->Click();

        return;
    }
}

void ClickableManager::AddClickable(IClickable* clickable)
{
    _clickables.push_back(clickable);
}

void ClickableManager::RemoveClickable(IClickable* clickable)
{
    auto itEnd {_clickables.cend()};

    for (auto it {_clickables.begin()}; it != itEnd; ++it)
    {
        if (*it != clickable)
        {
            continue;
        }

        _clickables.erase(it);
        return;
    }
}