#include "Managers/Input/SelectableManager.h"

#include "Factories/ImGui/ImGuiFactory.h"
#include "Managers/Gesture/GestureManager.h"
#include "Managers/Gesture/MouseButton/MouseButtons.h"
#include "UI/ISelectable.h"
#include "Utilities/Boundaries.h"

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
        if (!selectable->CanBeSelected() || selectable == _currentSelection || !Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, selectable->GetPosition(), selectable->GetBottomRightPosition()))
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