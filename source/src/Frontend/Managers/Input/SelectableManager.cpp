#include "Frontend/Managers/Input/SelectableManager.h"

#include "Frontend/Factory/ImGuiFactory.h"
#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Gesture/MouseButton/MouseButtons.h"
#include "Frontend/UI/ISelectable.h"
#include "Frontend/Utilities/Boundaries.h"

SelectableManager SelectableManager::_selectableManagerInstance{};

SelectableManager::SelectableManager() : _currentSelection(nullptr)
{
    _onLeftMouseButtonReleasedWeakAction = GestureManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
        [&](bool value) {
            _hasLeftMouseButtonReleased = value;
    });
}

SelectableManager& SelectableManager::GetInstance()
{
    return _selectableManagerInstance;
}

void SelectableManager::Update()
{
    if (!_hasLeftMouseButtonReleased)
    {
        return;
    }

    _hasLeftMouseButtonReleased = false;

    ImVec2 mousePosition {ImGuiFactory::GetMousePosition()};

    for (auto selectable : _selectables)
    {
        if (!selectable->CanBeSelected() ||
            selectable == _currentSelection ||
            !Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, selectable->GetParentPosition(),
                selectable->GetParentBottomRightPosition()))
        {
            continue;
        }

        if (_currentSelection != nullptr)
        {
            _currentSelection->OnUnselect();
        }

        _currentSelection = selectable;

        _currentSelection->OnSelect();

        return;
    }
}

void SelectableManager::AddSelectable(ISelectable* selectable)
{
    _selectables.push_back(selectable);
}

void SelectableManager::RemoveSelectable(ISelectable* selectable)
{
    auto itEnd {_selectables.cend()};

    for (auto it {_selectables.begin()}; it != itEnd; ++it)
    {
        if (*it != selectable)
        {
            continue;
        }

        _selectables.erase(it);
        return;
    }
}