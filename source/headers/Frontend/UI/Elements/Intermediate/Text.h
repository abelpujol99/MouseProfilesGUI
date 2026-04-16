#pragma once
#include "Frontend/UI/Elements/Base/DrawableComponent.h"

#include <string>
#include <functional>

struct TextData;
enum class TextHorizontalAlignments;
enum class TextVerticalAlignments;

class Text : public DrawableComponent
{
public:

    Text(TextData&& textData, bool isHidden = false);

    ~Text() override = default;

    void SetParentAttributes(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize,
        bool* isParentHidden) override;

    void SetColor(ImColor color);

    void SetText(const std::string& text);

    void AddText(const std::string& text);

    void EraseLastChar();

    void SetFontFamily(ImFont* fontFamily);

    void SetFontSize(float fontSize);

    void SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment);

    void SetVerticalAlignment(TextVerticalAlignments verticalAlignment);

    [[nodiscard]] std::string GetText() const;

    [[nodiscard]] float GetFontSize() const;

    [[nodiscard]] ImVec2 GetTextSize() const;

    void Draw(ImDrawList* drawList) override;

private:

    void CalculateTextSize();

    void UpdateRelativePosition();

    std::string _text;

    TextHorizontalAlignments _horizontalAlignment;

    TextVerticalAlignments _verticalAlignment;

    ImFont* _fontFamily;

    float _fontSize;

    ImVec2 _textSize;

    ImColor _color;

    ImVec2 _currentRelativePosition;

    std::function<float()> _getPositionXAction;

    std::function<float()> _getPositionYAction;
};