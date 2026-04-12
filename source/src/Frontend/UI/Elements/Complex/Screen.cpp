#include "Frontend/UI/Elements/Complex/Screen.h"

Screen::Screen(ImVec2&& position, ImVec2&& size, bool isHidden) :
        BaseDisplay(isHidden), _position(std::make_unique<ImVec2>(std::move(position))),
        _size(std::make_unique<ImVec2>(std::move(size)))
{}

void Screen::AddRectDrawable(std::unique_ptr<RectDrawable>&& rectDrawable)
{
    rectDrawable->SetParentTransform(_position.get(), _size.get());

    rectDrawable->UpdatePosition();

    rectDrawable->UpdateSize();

    _rectDrawables.push_front(std::move(rectDrawable));
}

ImVec2 Screen::GetPosition() const
{
    return *_position;
}

ImVec2 Screen::GetBottomRightPosition() const
{
    return {GetPosition().x + GetSize().x, GetPosition().y + GetSize().y};
}

ImVec2 Screen::GetSize() const
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
        (*it)->UpdatePosition();
        (*it)->Draw(drawList);
    }
}
