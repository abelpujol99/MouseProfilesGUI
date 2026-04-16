#include "Frontend/UI/Elements/Complex/Screen.h"

#include "Frontend/Managers/View/WindowManager.h"

Screen::Screen(bool isHidden) :
        BaseDisplay(isHidden), _position(std::make_unique<ImVec2>(ImVec2{0, 0})),
        _size(std::make_unique<ImVec2>(ImVec2{1500, 700})), _bottomRightPosition(std::make_unique<ImVec2>())
{
    _onSizeChangeWeakAction = WindowManager::GetInstance().SubscribeToSizeObserver([&](ImVec2 size) {
        *_size = size;
        UpdateRectDrawables();
    });

    *_bottomRightPosition = {_position->x + _size->x, _position->y + _size->y};
}

void Screen::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    rectDrawable->UpdatePosition();

    rectDrawable->UpdateSize();

    rectDrawable->UpdateRectDrawables();

    _rectDrawables.push_front(std::move(rectDrawable));
}

ImVec2 Screen::GetParentPosition() const
{
    return *_position;
}

ImVec2 Screen::GetParentBottomRightPosition() const
{
    return {GetParentPosition().x + GetParentSize().x, GetParentPosition().y + GetParentSize().y};
}

ImVec2 Screen::GetParentSize() const
{
    return *_size;
}

void Screen::Draw(ImDrawList* drawList)
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

void Screen::UpdateRectDrawables() const
{
    const auto itEnd{_rectDrawables.cend()};

    for (auto it{_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();

        (*it)->UpdateSize();

        (*it)->UpdateRectDrawables();
    }
}
