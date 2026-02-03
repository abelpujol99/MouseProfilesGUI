#include "UI/Text.h"

Text::Text(int positionX, int positionY, const char *text, ImFont* fontFamily, float fontSize, ImColor color) :
Drawable(positionX, positionY), _text(text), _fontFamily(fontFamily), _fontSize(fontSize), _color(color)
{}

void Text::SetColor(ImColor color)
{
    _color = color;
}

void Text::SetText(const char* text)
{
    _text = text;
}

void Text::SetFontFamily(ImFont* fontFamily)
{
    _fontFamily = fontFamily;
}

void Text::SetFontSize(float fontSize)
{
    _fontSize = fontSize;
}

const char* Text::GetText() const
{
    return _text;
}

float Text::GetFontSize() const
{
    return _fontSize;
}

void Text::Draw(ImDrawList* drawList)
{
    drawList->AddText(_fontFamily, _fontSize, _topLeftPosition, _color, _text);
}
