#include "Frontend/UI/Elements/Complex/Canvas.h"

#include "Frontend/Managers/View/WindowManager.h"

Canvas::Canvas(bool isHidden) :
        BaseDisplay(isHidden)
{
    _onSizeChangeWeakAction = WindowManager::GetInstance().SubscribeToSizeObserver([&](ImVec2 size) {

        if (_size->x == size.x && _size->y == size.y) {
            return;
        }

        *_size = size;

        *_bottomRightPosition = {_size->x, _size->y};
        UpdateRectDrawables();
    });
}

void Canvas::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _rectDrawables.push_front(std::move(rectDrawable));
}

ImVec2 Canvas::GetParentPosition() const
{
    return {0, 0};
}

ImVec2 Canvas::GetParentBottomRightPosition() const
{
    return {GetParentPosition().x + GetParentSize().x, GetParentPosition().y + GetParentSize().y};
}

ImVec2 Canvas::GetParentSize() const
{
    return *_size;
}

void Canvas::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}

void Canvas::UpdateRectDrawables() const
{
    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}