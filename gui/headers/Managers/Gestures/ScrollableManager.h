#pragma once
#include <functional>
#include <memory>

#include "imgui.h"

class IScrollable;

class ScrollableManager
{
public:

    ~ScrollableManager() = default;

    ScrollableManager(const ScrollableManager& other) = delete;
    ScrollableManager& operator=(const ScrollableManager& other) = delete;
    ScrollableManager(ScrollableManager&& other) = delete;
    ScrollableManager& operator=(ScrollableManager&& other) = delete;

    static ScrollableManager& GetInstance();

    void OnScroll(const float& scrollValue, const ImVec2& mousePosition) const;

    void AddScrollable(IScrollable* scrollable);

    void RemoveScrollable(IScrollable* scrollable);

private:

    ScrollableManager() = default;

    static std::unique_ptr<ScrollableManager> _scrollableManagerInstance;

    std::vector<IScrollable*> _scrollables;
};
