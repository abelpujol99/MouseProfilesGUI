#pragma once

#include <memory>
#include <functional>

#include "imgui.h"

class ISelectable;

class SelectableManager
{

public:

    ~SelectableManager() = default;

    SelectableManager(const SelectableManager& other) = delete;
    SelectableManager& operator=(const SelectableManager& other) = delete;
    SelectableManager(SelectableManager&& other) = delete;
    SelectableManager& operator=(SelectableManager&& other) = delete;

    static SelectableManager& GetInstance();

    void OnSelect(const ImVec2& mousePosition);

    void AddSelectable(ISelectable* selectable);

    void RemoveSelectable(ISelectable* selectable);

private:

    SelectableManager() = default;

    static std::unique_ptr<SelectableManager> _selectableManagerInstance;

    std::vector<ISelectable*> _selectables;

    ISelectable* _currentSelection;
};