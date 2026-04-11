#pragma once
#include <forward_list>

#include "Drawable.h"

class Screen : public Drawable
{
public:

    Screen(DrawablePosition&& drawablePosition, bool isHidden);

    ~Screen() override = default;

    void AddDrawable(std::unique_ptr<Drawable>&& drawable);

    void UpdatePosition() override;

    void Draw(ImDrawList* drawList) override;

private:

    std::forward_list<std::unique_ptr<Drawable>> _drawables;
};