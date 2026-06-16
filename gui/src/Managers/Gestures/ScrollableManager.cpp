#include "Managers/Gestures/ScrollableManager.h"

#include "UI/Helpers/IScrollable.h"
#include "Utilities/UI/Boundaries.h"

std::unique_ptr<ScrollableManager> ScrollableManager::_scrollableManagerInstance {nullptr};

ScrollableManager& ScrollableManager::GetInstance()
{
    if (_scrollableManagerInstance == nullptr)
    {
        _scrollableManagerInstance.reset(new ScrollableManager());
    }

    return *_scrollableManagerInstance;
}

void ScrollableManager::OnScroll(const float& scrollValue, const ImVec2& mousePosition) const
{
    for (auto scrollable : _scrollables)
    {
        if (!scrollable->CanBeScrolled() ||
            !Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, scrollable->GetParentPosition(),
                scrollable->GetParentBottomRightPosition()))
        {
            continue;
        }

        scrollable->Scroll(scrollValue);

        return;
    }
}

void ScrollableManager::AddScrollable(IScrollable* scrollable)
{
    _scrollables.push_back(scrollable);
}

void ScrollableManager::RemoveScrollable(IScrollable* scrollable)
{
    auto itEnd {_scrollables.cend()};

    for (auto it {_scrollables.begin()}; it != itEnd; ++it)
    {
        if (*it != scrollable)
        {
            continue;
        }

        _scrollables.erase(it);
        return;
    }
}
