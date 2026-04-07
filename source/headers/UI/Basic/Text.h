#pragma once
#include "UI/Drawable.h"

#include <string>

#include "UI/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Structs/TextData.h"

class Text : public Drawable
{
public:

    Text(DrawablePosition&& drawablePosition, TextData&& textData, bool isHidden = false);

    ~Text() override = default;

    void SetColor(ImColor color);

    void SetText(const std::string& text);

    void AddText(const std::string& text);

    void SetFontFamily(ImFont* fontFamily);

    void SetFontSize(float fontSize);

    void SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment);

    void SetVerticalAlignment(TextVerticalAlignments verticalAlignment);

    [[nodiscard]] std::string GetText() const;

    [[nodiscard]] float GetFontSize() const;

    [[nodiscard]] ImVec2 GetTextSize() const;

    [[nodiscard]] const ImVec2& GetRelativePosition() const override;

    void Draw(ImDrawList* drawList) override;

private:

    void CalculateTextSize();

    void UpdateTopLeftPosition();

    std::string _text;

    TextHorizontalAlignments _horizontalAlignment;

    TextVerticalAlignments _verticalAlignment;

    ImFont* _fontFamily;

    float _fontSize;

    ImColor _color;

    ImVec2 _currentRelativePosition;

    ImVec2 _size;
};
