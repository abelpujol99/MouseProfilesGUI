#include "Frontend/Managers/Input/ClickableManager.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Gesture/MouseButton/MouseButtons.h"
#include "Frontend/Utilities/Boundaries.h"
#include "Frontend/UI/IClickable.h"

ClickableManager ClickableManager::_clickableManagerInstance {};

ClickableManager::ClickableManager()
{
    _onLeftMouseButtonReleasedWeakAction = GestureManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
            [&](bool value) {
                _hasLeftMouseButtonReleased = value;
        });
}

ClickableManager& ClickableManager::GetInstance()
{
    return _clickableManagerInstance;
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