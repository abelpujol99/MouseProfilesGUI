#include "Frontend/UI/Advanced/Button.h"

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Managers/Gesture/GestureManager.h"
#include "Frontend/Managers/Gesture/MouseButton/MouseButtons.h"
#include "Frontend/UI/Structs/DrawablePosition.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

Button::Button(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData,
    std::function<void()>&& action, bool isHidden) :
        RectDrawable(std::move(drawablePosition), isHidden),
        _rectangle(DrawableFactory::CreateRectangle(DrawablePosition{_finalPosition, 0, 0},
        RectangleData{rectangleData.size, rectangleData.color, rectangleData.rounding, rectangleData.thickness, rectangleData.isFilled})),
        _text(DrawableFactory::CreateText(DrawablePosition{_finalPosition, 0, 0},
        TextData{textData.text, textData.horizontalAlignment, textData.verticalAlignment, textData.fontFamily, textData.fontSize, textData.color})),
        _action(action)
{
    _onLeftMouseButtonReleasedWeakAction = GestureManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
            [&](bool value) {
                _hasLeftMouseButtonReleased = value;
        });
}

void Button::UpdatePosition()
{
    RectDrawable::UpdatePosition();

    _rectangle->UpdatePosition();

    _text->UpdatePosition();
}

void Button::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);

    if (!_hasLeftMouseButtonReleased)
    {
        return;
    }

    _hasLeftMouseButtonReleased = false;

    _action();
}
