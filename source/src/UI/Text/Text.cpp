#include "UI/Text/Text.h"

#include <iostream>

Text::Text(const ImVec2& parentPosition, float positionX, float positionY, const std::string& text,
    TextHorizontalAlignments horizontalAlignment, TextVerticalAlignments verticalAlignment, ImFont* fontFamily,
    float fontSize, ImColor color, bool isHidden) : Drawable(parentPosition, positionX, positionY, isHidden),
    _text(text), _horizontalAlignment(horizontalAlignment), _verticalAlignment(verticalAlignment), _fontFamily(fontFamily),
    _fontSize(fontSize), _color(color)
{
    CalculateTextSize();
}

void Text::SetColor(ImColor color)
{
    _color = color;
}

void Text::SetText(const std::string& text)
{
    _text = text;
}

void Text::AddText(const std::string& text)
{

}

void Text::SetFontFamily(ImFont* fontFamily)
{
    _fontFamily = fontFamily;

    CalculateTextSize();
}

void Text::SetFontSize(float fontSize)
{
    _fontSize = fontSize;

    CalculateTextSize();
}

void Text::SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment)
{
    _horizontalAlignment = horizontalAlignment;
}

void Text::SetVerticalAlignment(TextVerticalAlignments verticalAlignment)
{
    _verticalAlignment = verticalAlignment;
}

void Text::CalculateTextSize()
{
    _size = _fontFamily->CalcTextSizeA(_fontSize, FLT_MAX, -1.0f, _text.c_str());

    UpdateTopLeftPosition();
}

void Text::UpdateTopLeftPosition()
{
    if (_horizontalAlignment == TextHorizontalAlignments::LEFT)
    {
        _currentRelativePosition.x = _relativePosition.x;
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::CENTER)
    {
        _currentRelativePosition.x = _relativePosition.x - _size.x / 2;
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::RIGHT)
    {
        _currentRelativePosition.x = _relativePosition.x - _size.x;
    }

    if (_verticalAlignment == TextVerticalAlignments::TOP)
    {
        _currentRelativePosition.y = _relativePosition.y;
    }
    else if (_verticalAlignment == TextVerticalAlignments::CENTER)
    {
        _currentRelativePosition.y = _relativePosition.y - _size.y / 2;
    }
    else if (_verticalAlignment == TextVerticalAlignments::BOTTOM)
    {
        _currentRelativePosition.y = _relativePosition.y - _size.y;
    }
}

std::string Text::GetText() const
{
    return _text;
}

float Text::GetFontSize() const
{
    return _fontSize;
}

ImVec2 Text::GetTextSize() const
{
    return _size;
}

const ImVec2& Text::GetRelativePosition() const
{
    return _currentRelativePosition;
}

void Text::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    drawList->AddText(_fontFamily, _fontSize, GetFinalPosition(), _color, _text.c_str());
}