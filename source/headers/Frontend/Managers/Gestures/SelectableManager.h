#pragma once

#include <memory>
#include <functional>

class ISelectable;

class SelectableManager
{

public:

    ~SelectableManager() noexcept;

    SelectableManager(const SelectableManager& other) = delete;
    SelectableManager& operator=(const SelectableManager& other) = delete;
    SelectableManager(SelectableManager&& other) = delete;
    SelectableManager& operator=(SelectableManager&& other) = delete;

    static SelectableManager& GetInstance();

    void Update();

    void AddSelectable(ISelectable* selectable);

    void RemoveSelectable(ISelectable* selectable);

private:

    SelectableManager();

    static SelectableManager* _selectableManagerInstance;

    std::weak_ptr<std::function<void(bool)>> _onLeftMouseButtonReleasedWeakAction;

    bool _hasLeftMouseButtonReleased;

    std::vector<ISelectable*> _selectables;

    ISelectable* _currentSelection;
};