#include "Managers/Gestures/SelectableManager.h"

#include "UI/Helpers/ISelectable.h"
#include "Utilities/UI/Boundaries.h"

std::unique_ptr<SelectableManager> SelectableManager::_selectableManagerInstance {nullptr};

SelectableManager& SelectableManager::GetInstance()
{
    if (_selectableManagerInstance == nullptr)
    {
        _selectableManagerInstance.reset(new SelectableManager());
    }

    return *_selectableManagerInstance;
}

void SelectableManager::OnSelect(const ImVec2& mousePosition)
{
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