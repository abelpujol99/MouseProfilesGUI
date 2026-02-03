#pragma once
#include <cstdint>

#include "Drawable.h"

class Text : public Drawable
{
public:

    Text(int positionX, int positionY, const char* text, ImFont* fontFamily, float fontSize, ImColor color);

    void SetColor(ImColor color);

    void SetText(const char* text);

    void SetFontFamily(ImFont* fontFamily);

    void SetFontSize(float fontSize);

    [[nodiscard]] const char* GetText() const;

    [[nodiscard]] float GetFontSize() const;

    void Draw(ImDrawList* drawList) override;

private:

    const char* _text;

    ImFont* _fontFamily;

    float _fontSize;

    ImColor _color;
};
