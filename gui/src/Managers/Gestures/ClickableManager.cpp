#include "Managers/Gestures/ClickableManager.h"

#include "Utilities/UI/Boundaries.h"
#include "UI/Helpers/IClickable.h"

std::unique_ptr<ClickableManager> ClickableManager::_clickableManagerInstance {nullptr};

ClickableManager& ClickableManager::GetInstance()
{
    if (_clickableManagerInstance == nullptr)
    {
        _clickableManagerInstance.reset(new ClickableManager());
    }

    return *_clickableManagerInstance;
}

void ClickableManager::OnClick(const ImVec2& mousePosition) const
{
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
    _clickables.emplace(clickable);
}

void ClickableManager::RemoveClickable(IClickable* clickable)
{
    _clickables.erase(clickable);
}