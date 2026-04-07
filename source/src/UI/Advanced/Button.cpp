#include "UI/Advanced/Button.h"

#include <utility>

Button::Button(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData,
    bool isHidden) :
        RectDrawable(std::move(drawablePosition), isHidden)
{

}

void Button::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }
}
