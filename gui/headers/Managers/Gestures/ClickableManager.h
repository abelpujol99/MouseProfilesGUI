#pragma once
#include <functional>
#include <memory>
#include <set>

#include "imgui.h"

class IClickable;

class ClickableManager
{
public:

    ~ClickableManager() = default;

    ClickableManager(const ClickableManager& other) = delete;
    ClickableManager& operator=(const ClickableManager& other) = delete;
    ClickableManager(ClickableManager&& other) = delete;
    ClickableManager& operator=(ClickableManager&& other) = delete;

    static ClickableManager& GetInstance();

    void OnClick(const ImVec2& mousePosition) const;

    void AddClickable(IClickable* clickable);

    void RemoveClickable(IClickable* clickable);

private:

    ClickableManager() = default;

    static std::unique_ptr<ClickableManager> _clickableManagerInstance;

    std::set<IClickable*> _clickables;
};
