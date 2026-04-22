#include "Frontend/Managers/Gestures/ScrollableManager.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Input/InputManager.h"
#include "Frontend/UI/Helpers/IScrollable.h"
#include "Frontend/Utilities/Boundaries.h"

ScrollableManager* ScrollableManager::_scrollableManagerInstance {nullptr};

ScrollableManager::ScrollableManager()
{
    _onMouseScrollWeakAction = InputManager::GetInstance().SubscribeToMouseScroll([&](float scrollValue) {
            _mouseScroll = scrollValue;
        });
}

ScrollableManager::~ScrollableManager() noexcept
{
    delete _scrollableManagerInstance;
}

ScrollableManager& ScrollableManager::GetInstance()
{
    if (_scrollableManagerInstance == nullptr)
    {
        _scrollableManagerInstance = new ScrollableManager();
    }

    return *_scrollableManagerInstance;
}

void ScrollableManager::Update()
{
    if (_mouseScroll == 0.f)
    {
        return;
    }

    ImVec2 mousePosition {ImGuiFactory::GetMousePosition()};

    for (auto scrollable : _scrollables)
    {
        if (!scrollable->CanBeScrolled() ||
            !Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, scrollable->GetParentPosition(),
                scrollable->GetParentBottomRightPosition()))
        {
            continue;
        }

        scrollable->Scroll(_mouseScroll);

        return;
    }

    _mouseScroll = 0.f;
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
