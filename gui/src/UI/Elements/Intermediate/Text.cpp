#include "UI/Elements/Intermediate/Text.h"

#include "ColorDefines.h"
#include "Factory/Font/FontFactory.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Structs/TextData.h"

Text::Text(TextData&& textData, bool isHidden) :
        DrawableComponent(isHidden), _text(textData.text),
        _horizontalAlignment(textData.horizontalAlignment), _verticalAlignment(textData.verticalAlignment),
        _fontFamily(FontFactory::GetInstance().GetFontFamily(textData.fontFamily)), _fontSize(textData.fontSize),
        _color(textData.color), _currentColor(_color)
{}

void Text::SetParentState(ImVec2 *parentPositionPointer, ImVec2 *parentBottomRightPositionPointer,
    ImVec2 *parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    CalculateTextSize();
}

void Text::SetColor(ImColor color)
{
    _color = color;
}

void Text::SetText(const std::string& text)
{
    _text = text;

    CalculateTextSize();
}

void Text::AddText(const std::string& text)
{
    _text.append(text);

    CalculateTextSize();
}

void Text::EraseLastChar()
{
    if (_text.empty())
    {
        return;
    }

    _text.pop_back();

    CalculateTextSize();
}

void Text::ErasePreviousChar()
{
    if (_text.empty())
    {
        return;
    }

    CalculateTextSize();
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

    CalculateTextSize();
}

void Text::SetVerticalAlignment(TextVerticalAlignments verticalAlignment)
{
    _verticalAlignment = verticalAlignment;

    CalculateTextSize();
}

void Text::CalculateTextSize()
{
    _textSize = _fontFamily->CalcTextSizeA(_fontSize, FLT_MAX, -1.0f, _text.c_str());

    UpdateRelativePosition();
}

void Text::UpdateRelativePosition()
{
    if (_horizontalAlignment == TextHorizontalAlignments::LEFT)
    {
        _getPositionXAction = [&]() {
            return GetParentPosition().x;
        };
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::CENTER)
    {
        _getPositionXAction = [&]() {
            return GetParentPosition().x - _textSize.x / 2 + GetParentSize().x / 2;
        };
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::RIGHT)
    {
        _getPositionXAction = [&]() {
            return GetParentPosition().x - _textSize.x + GetParentSize().x;
        };
    }

    if (_verticalAlignment == TextVerticalAlignments::TOP)
    {
        _getPositionYAction = [&]() {
            return GetParentPosition().y;
        };
    }
    else if (_verticalAlignment == TextVerticalAlignments::MIDDLE)
    {
        _getPositionYAction = [&]() {
            return GetParentPosition().y - _textSize.y / 2 + GetParentSize().y / 2;
        };
    }
    else if (_verticalAlignment == TextVerticalAlignments::BOTTOM)
    {
        _getPositionYAction = [&]() {
            return GetParentPosition().y - _textSize.y + GetParentSize().y;
        };
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
    return _textSize;
}

void Text::Enable()
{
    _currentColor = _color;
}

void Text::Disable()
{
    _currentColor = GRAY;
}

void Text::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    drawList->AddText(_fontFamily, _fontSize, {_getPositionXAction(), _getPositionYAction()}, _currentColor, _text.c_str());
}
