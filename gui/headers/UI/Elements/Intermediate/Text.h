#pragma once
#include "UI/Elements/Base/DrawableComponent.h"

#include <memory>
#include <string>
#include <functional>

#include "UI/Structs/TextData.h"

class Text : public DrawableComponent
{
public:

    Text(TextData&& textData, bool isHidden = false);

    Text(const Text& other);

    ~Text() override = default;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    void SetColor(ImColor color);

    void SetText(const std::string& text);

    void AddText(const std::string& text);

    void EraseLastChar();

    void ErasePreviousChar();

    void SetFontFamily(ImFont* fontFamily);

    void SetFontSize(float fontSize);

    void SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment);

    void SetVerticalAlignment(TextVerticalAlignments verticalAlignment);

    void SetPadding(TextPadding textPadding);

    [[nodiscard]] std::string GetText() const;

    [[nodiscard]] float GetFontSize() const;

    [[nodiscard]] ImVec2 GetTextSize() const;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<Text> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    void CalculateTextSize();

    void UpdateRelativePosition();

    std::string _text;

    TextHorizontalAlignments _horizontalAlignment;

    TextVerticalAlignments _verticalAlignment;

    TextPadding _textPadding;

    ImFont* _fontFamily;

    float _minimumFontSize;

    float _maximumFontSize;

    ImVec2 _textSize;

    ImColor _color;

    ImColor _currentColor;

    std::function<float()> _getPositionXAction;

    std::function<float()> _getPositionYAction;
};