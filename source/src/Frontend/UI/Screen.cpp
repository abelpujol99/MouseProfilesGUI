#include "Frontend/UI/Screen.h"

Screen::Screen(DrawablePosition&& drawablePosition, bool isHidden) :
        Drawable(std::move(drawablePosition), isHidden)
{}

void Screen::AddDrawable(std::unique_ptr<Drawable>&& drawable)
{
    _drawables.push_front(std::move(drawable));
}

void Screen::UpdatePosition()
{
    Drawable::UpdatePosition();

    const auto itEnd{_drawables.cend()};

    for (auto it{_drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdatePosition();
    }
}

void Screen::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    const auto itEnd{_drawables.cend()};

    for (auto it{_drawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}
