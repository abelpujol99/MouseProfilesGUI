#include "Managers/Gestures/SelectableManager.h"

#include "Factory/ImGuiFactory.h"
#include "Managers/Input/InputManager.h"
#include "Managers/Input/MouseButton/MouseButtons.h"
#include "UI/Helpers/ISelectable.h"
#include "Utilities/UI/Boundaries.h"

SelectableManager* SelectableManager::_selectableManagerInstance {nullptr};

SelectableManager::SelectableManager() : _currentSelection(nullptr)
{
    _onLeftMouseButtonReleasedWeakAction = InputManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
        [&](bool value) {
            _hasLeftMouseButtonReleased = value;
    });
}

SelectableManager::~SelectableManager() noexcept
{
    delete _selectableManagerInstance;
}

SelectableManager& SelectableManager::GetInstance()
{
    if (_selectableManagerInstance == nullptr)
    {
        _selectableManagerInstance = new SelectableManager();
    }

    return *_selectableManagerInstance;
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