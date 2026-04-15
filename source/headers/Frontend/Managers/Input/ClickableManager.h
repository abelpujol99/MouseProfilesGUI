#pragma once
#include <functional>
#include <memory>

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

    void Update();

    void AddClickable(IClickable* clickable);

    void RemoveClickable(IClickable* clickable);

private:

    ClickableManager();

    static ClickableManager _clickableManagerInstance;

    std::weak_ptr<std::function<void(bool)>> _onLeftMouseButtonReleasedWeakAction;

    bool _hasLeftMouseButtonReleased;

    std::vector<IClickable*> _clickables;
};
