#pragma once
#include <cstdint>

#include "TextHorizontalAlignments.h"
#include "TextVerticalAlignments.h"
#include "UI/Drawable.h"

class Text : public Drawable
{
public:

    Text(const ImVec2& parentPosition, float positionX, float positionY, const char* text,
        TextHorizontalAlignments horizontalAlignment, TextVerticalAlignments verticalAlignment, ImFont* fontFamily,
        float fontSize, ImColor color, bool isHidden = false);

    ~Text() override = default;

    void SetColor(ImColor color);

    void SetText(const char* text);

    void SetFontFamily(ImFont* fontFamily);

    void SetFontSize(float fontSize);

    void SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment);

    void SetVerticalAlignment(TextVerticalAlignments verticalAlignment);

    [[nodiscard]] const char* GetText() const;

    [[nodiscard]] float GetFontSize() const;

    [[nodiscard]] ImVec2 GetTextSize() const;

    [[nodiscard]] const ImVec2& GetRelativePosition() const override;

    void Draw(ImDrawList* drawList) override;

private:

    void CalculateTextSize();

    void UpdateTopLeftPosition();


private:
    const char* _text;

    TextHorizontalAlignments _horizontalAlignment;

    TextVerticalAlignments _verticalAlignment;

    ImFont* _fontFamily;

    float _fontSize;

    ImColor _color;

    ImVec2 _currentRelativePosition;

    ImVec2 _size;
};
