#include "Frontend/UI/Basic/Text.h"

#include "Frontend/Factory/Font/FontFactory.h"
#include "Frontend/UI/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Structs/TextData.h"

Text::Text(DrawablePosition &&drawablePosition, TextData &&textData, bool isHidden) :
        Drawable(std::move(drawablePosition), isHidden), _text(textData.text),
        _horizontalAlignment(textData.horizontalAlignment), _verticalAlignment(textData.verticalAlignment),
        _fontFamily(FontFactory::GetInstance().GetFontFamily(textData.fontFamily)), _fontSize(textData.fontSize), _color(textData.color)
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
    _text.append(text);
}

void Text::EraseLastChar()
{
    if (_text.empty())
    {
        return;
    }

    _text.pop_back();
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
    else if (_verticalAlignment == TextVerticalAlignments::MIDDLE)
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

    drawList->AddText(_fontFamily, _fontSize, *GetPosition(), _color, _text.c_str());
}