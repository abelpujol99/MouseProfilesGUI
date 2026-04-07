#pragma once
#include <functional>
#include <memory>

#include "UI/RectDrawable.h"

class Rectangle;
class Text;
class RectangleData;
class TextData;

class Button : public RectDrawable
{

public:

    Button(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData,
        std::function<void()>&& action, bool isHidden);

    ~Button() override = default;

    void UpdatePosition() override;

    void Draw(ImDrawList *drawList) override;

private:

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Text> _text;

    std::weak_ptr<std::function<void(bool)>> _onLeftMouseButtonReleasedWeakAction;

    bool _hasLeftMouseButtonReleased;

    std::function<void()> _action;

};