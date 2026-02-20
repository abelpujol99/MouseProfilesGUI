#include "UI/Text/TextBox.h"

#include <iostream>

#include "Factories/DrawableFactory.h"
#include "Factories/Font/FontFactory.h"
#include "Factories/Font/FontFamilyTypes.h"
#include "Factories/ImGui/ImGuiFactory.h"
#include "Managers/Gesture/GestureManager.h"
#include "UI/Text/Text.h"
#include "Utilities/Boundaries.h"

TextBox::TextBox(const ImVec2& parentPosition, float positionX, float positionY, int width, int height,
    float verticalPadding, float horizontalPadding, ImColor color, float rounding, float thickness,
    TextHorizontalAlignments textHorizontalAlignment, TextVerticalAlignments textVerticalAlignment, FontFamilyTypes textFont,
    float fontSize, ImColor textColor, bool isHidden) : RectDrawable(parentPosition, positionX, positionY, isHidden),
    _color(color), _verticalPadding(verticalPadding), _horizontalPadding(horizontalPadding), _rounding(rounding), _thickness(thickness),
    _text(DrawableFactory::CreateText(GetFinalPosition(), 0, 0, "Test", textHorizontalAlignment, textVerticalAlignment,
    FontFactory::GetInstance().GetFontFamily(textFont), fontSize, textColor))
{
    SetSize(width, height);

    _onLeftMouseButtonReleasedWeakAction = GestureManager::GetInstance().SubscribeToMouseButtonReleaseEvent(MouseButtons::LEFT,
        [&](bool value) {
            _hasLeftMouseButtonReleased = value;
    });
}

void TextBox::UpdatePosition()
{
    RectDrawable::UpdatePosition();

    _text->UpdatePosition();
}

void TextBox::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _text->Draw(drawList);

    const ImVec2& finalPosition {GetFinalPosition()};

    drawList->AddRect(finalPosition, _bottomRightPosition, _color, _rounding, 0, _thickness);

    if (_isSelected || !_hasLeftMouseButtonReleased)
    {
        return;
    }

    _hasLeftMouseButtonReleased = false;

    ImVec2 mousePosition {ImGuiFactory::GetMousePosition()};

    _isSelected = Utilities::Boundaries::IsPositionInsideBoundaries(mousePosition, finalPosition, _bottomRightPosition);

    if (!_isSelected)
    {
        return;
    }

    //TODO SUBSCRIBE TEXT
}