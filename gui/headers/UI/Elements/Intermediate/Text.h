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

    void OnParentSizeUpdated() override;

    void SetColor(ImColor color);

    void SetText(const std::string& text);

    void AddText(const std::string& text, size_t index);

    void EraseFromIndexToIndex(size_t fist, size_t last);

    void SetFontFamily(ImFont* fontFamily);

    void SetMinimumFontSize(float minimumFontSize);

    void SetMaximumFontSize(float maximumFontSize);

    void SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment);

    void SetVerticalAlignment(TextVerticalAlignments verticalAlignment);

    void SetPadding(TextPadding padding);

    [[nodiscard]] std::string GetText() const;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<Text> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    struct Word
    {
        std::string text;
        float referenceWidth;
    };

    struct Line
    {
        std::string text;
        float width;
    };

    void UpdateRelativePosition();

    void UpdateLayout();

    void UpdateMeasures();

    void TextToWords();

    void CalculateWordsWidth();

    [[nodiscard]] ImVec2 CalculateTextSize(float fontSize, std::string text);

    void UpdateFontSize();

    bool DoesLayoutFit(float fontSize);

    std::vector<Line> CreateLines(float fontSize);

    float _previousParentWidth;

    std::string _text;

    std::vector<Word> _words;

    std::vector<Line> _lines;

    float _spaceWidth;

    float _referenceTextHeight;

    float _textHeight;

    TextHorizontalAlignments _horizontalAlignment;

    TextVerticalAlignments _verticalAlignment;

    TextPadding _padding;

    ImFont* _fontFamily;

    float _minimumFontSize;

    float _maximumFontSize;

    float _fontSize;

    ImVec2 _textSize;

    ImColor _color;

    ImColor _currentColor;

    std::function<float(Line)> _getPositionXAction;

    std::function<float()> _getPositionYAction;
};