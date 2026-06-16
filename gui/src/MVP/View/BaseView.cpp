#include "MVP/View/BaseView.h"

#include "../../../headers/Managers/GLFWManager.h"

BaseView::BaseView(bool isHidden) :
        BaseDisplay(isHidden)
{
    _onSizeChangeWeakAction = GLFWManager::GetInstance().SubscribeToSizeObserver([&](WindowSize size) {

        if (static_cast<int>(_size->x) == size.width && static_cast<int>(_size->y) == size.height) {
            return;
        }

        *_size = {static_cast<float>(size.width), static_cast<float>(size.height)};

        *_bottomRightPosition = {_size->x, _size->y};
        UpdateRectDrawables();
    });
}

void BaseView::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    rectDrawable->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

void BaseView::RemoveRectDrawable(RectDrawable* rectDrawable)
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

ImVec2 BaseView::GetParentPosition() const
{
    return {0, 0};
}

ImVec2 BaseView::GetParentBottomRightPosition() const
{
    return {GetParentPosition().x + GetParentSize().x, GetParentPosition().y + GetParentSize().y};
}

ImVec2 BaseView::GetParentSize() const
{
    return *_size;
}

void BaseView::Draw(ImDrawList* drawList)
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

void BaseView::UpdateRectDrawables() const
{
    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}