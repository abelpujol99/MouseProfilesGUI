#pragma once
#include <functional>
#include <memory>

class IScrollable;

class ScrollableManager
{
public:

    ~ScrollableManager() noexcept;

    ScrollableManager(const ScrollableManager& other) = delete;
    ScrollableManager& operator=(const ScrollableManager& other) = delete;
    ScrollableManager(ScrollableManager&& other) = delete;
    ScrollableManager& operator=(ScrollableManager&& other) = delete;

    static ScrollableManager& GetInstance();

    void Update();

    void AddScrollable(IScrollable* scrollable);

    void RemoveScrollable(IScrollable* scrollable);

private:

    ScrollableManager();

    static ScrollableManager* _scrollableManagerInstance;

    std::weak_ptr<std::function<void(float)>> _onMouseScrollWeakAction;

    float _mouseScroll;

    std::vector<IScrollable*> _scrollables;
};
