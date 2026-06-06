#pragma once
#include <forward_list>
#include <functional>

#include "IView.h"
#include "UI/Elements/Base/RectDrawable.h"
#include "Utilities/Concepts/DerivedFromBasePresenter.h"

#include "Managers/View/WindowManager.h"

template <DerivedFromBasePresenter TPresenter>
class BaseView : public BaseDisplay, public DrawableTransform, public IView
{
public:

    BaseView(bool isHidden);

    ~BaseView() override = default;

    void AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable);

    void RemoveRectDrawable(RectDrawable* rectDrawable);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetParentSize() const override;

    void Draw(ImDrawList* drawList) override;

protected:

    std::unique_ptr<TPresenter> _presenter;

private:

    void UpdateRectDrawables() const;

    std::weak_ptr<std::function<void(WindowSize)>> _onSizeChangeWeakAction;

    std::forward_list<std::unique_ptr<RectDrawable>> _rectDrawables;
};

template <DerivedFromBasePresenter TPresenter>
BaseView<TPresenter>::BaseView(bool isHidden) : BaseDisplay(isHidden), _presenter(std::make_unique<TPresenter>())
{
    _onSizeChangeWeakAction = WindowManager::GetInstance().SubscribeToSizeObserver([&](WindowSize size) {

        if (static_cast<int>(_size->x) == size.width && static_cast<int>(_size->y) == size.height) {
            return;
        }

        *_size = {static_cast<float>(size.width), static_cast<float>(size.height)};

        *_bottomRightPosition = {_size->x, _size->y};
        UpdateRectDrawables();
    });
}

template <DerivedFromBasePresenter TPresenter>
void BaseView<TPresenter>::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    rectDrawable->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

template <DerivedFromBasePresenter TPresenter>
void BaseView<TPresenter>::RemoveRectDrawable(RectDrawable* rectDrawable)
{
    auto itEnd {_rectDrawables.cend()};

    auto itPrevious {_rectDrawables.before_begin()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        if (it->get() != rectDrawable)
        {
            itPrevious = it;
            continue;
        }

        _rectDrawables.erase_after(itPrevious);

        return;
    }
}

template <DerivedFromBasePresenter TPresenter>
ImVec2 BaseView<TPresenter>::GetParentPosition() const
{
    return {0, 0};
}

template <DerivedFromBasePresenter TPresenter>
ImVec2 BaseView<TPresenter>::GetParentBottomRightPosition() const
{
    return {GetParentPosition().x + GetParentSize().x, GetParentPosition().y + GetParentSize().y};
}

template <DerivedFromBasePresenter TPresenter>
ImVec2 BaseView<TPresenter>::GetParentSize() const
{
    return *_size;
}

template <DerivedFromBasePresenter TPresenter>
void BaseView<TPresenter>::Draw(ImDrawList* drawList)
{
    if (*_mustBeHidden)
    {
        return;
    }

    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}

template <DerivedFromBasePresenter TPresenter>
void BaseView<TPresenter>::UpdateRectDrawables() const
{
    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}

