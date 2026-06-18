#include "UI/Elements/Intermediate/Text.h"

#include "ColorDefines.h"
#include "Factory/Font/FontFactory.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Structs/TextData.h"

#define MAX_ITERATIONS 10

Text::Text(TextData&& textData, bool isHidden) :
        DrawableComponent(isHidden), _text(textData.text),
        _horizontalAlignment(textData.horizontalAlignment), _verticalAlignment(textData.verticalAlignment),
        _fontFamily(FontFactory::GetInstance().GetFontFamily(textData.fontFamily)), _minimumFontSize(textData.minimumFontSize),
        _maximumFontSize(textData.maximumFontSize), _color(textData.color), _currentColor(_color), _padding(textData.padding),
        _fontSize(_minimumFontSize)
{
    TextToWords();
}

Text::Text(const Text& other) :
    DrawableComponent(true),
    _text(other._text),
    _horizontalAlignment(other._horizontalAlignment),
    _verticalAlignment(other._verticalAlignment),
    _fontFamily(other._fontFamily),
    _minimumFontSize(other._minimumFontSize),
    _maximumFontSize(other._maximumFontSize),
    _color(other._color),
    _currentColor(other._currentColor),
    _padding(other._padding),
    _fontSize(_minimumFontSize)
{
    TextToWords();
}

void Text::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    UpdateMeasures();
}

void Text::OnParentSizeUpdated()
{
    UpdateMeasures();
}

void Text::SetColor(ImColor color)
{
    _color = color;
}

void Text::SetText(const std::string& text)
{
    _text = text;

    UpdateLayout();
}

void Text::AddText(const std::string& text, size_t index)
{
    _text.insert(index, text);

    UpdateLayout();
}

void Text::EraseFromIndexToIndex(size_t fist, size_t last)
{
    _text.erase(fist, last);

    UpdateLayout();
}

void Text::SetFontFamily(ImFont* fontFamily)
{
    _fontFamily = fontFamily;

    UpdateMeasures();
}

void Text::SetMinimumFontSize(float minimumFontSize)
{
    _minimumFontSize = minimumFontSize;

    UpdateMeasures();
}

void Text::SetMaximumFontSize(float maximumFontSize)
{
    _maximumFontSize = maximumFontSize;

    UpdateMeasures();
}

void Text::SetHorizontalAlignment(TextHorizontalAlignments horizontalAlignment)
{
    _horizontalAlignment = horizontalAlignment;

    UpdateRelativePosition();
}

void Text::SetVerticalAlignment(TextVerticalAlignments verticalAlignment)
{
    _verticalAlignment = verticalAlignment;

    UpdateRelativePosition();
}

void Text::SetPadding(TextPadding padding)
{
    _padding = padding;

    UpdateMeasures();
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
            return GetParentPosition().y - _textHeight / 2 + GetParentSize().y / 2;
        };
    }
    else if (_verticalAlignment == TextVerticalAlignments::BOTTOM)
    {
        _getPositionYAction = [&]() {
            return GetParentPosition().y - _textHeight + GetParentSize().y;
        };
    }
}

void Text::UpdateLayout()
{
    TextToWords();

    UpdateMeasures();
}

void Text::UpdateMeasures()
{
    UpdateFontSize();

    BuildLines(_fontSize, _lines);

    _textHeight = CalculateTextHeight(_fontSize);
}

void Text::TextToWords()
{
    _words.clear();

    size_t start {0};

    while (start < _text.size())
    {
        while (start < _text.size() && _text.at(start) == ' ')
        {
            start++;
        }

        if (start == _text.size())
        {
            break;
        }

        size_t end {_text.find(' ', start)};

        if (end == std::string::npos)
        {
            end = _text.size();
        }

        _words.push_back({
            .text = _text.substr(start, end - start)
        });

        start = end + 1;
    }
}

void Text::UpdateFontSize()
{
    float low {_minimumFontSize};
    float high {_maximumFontSize};

    ImVec2 availableSpace {GetParentSize()};

    availableSpace.x -= _padding.leftPadding + _padding.rightPassing;
    availableSpace.y -= _padding.topPadding + _padding.bottomPadding;

    for (int i{0}; i < MAX_ITERATIONS; ++i)
    {
        float mid {(low + high) * 0.5f};

        if (LayoutFits(mid))
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    _fontSize = low;

    UpdateRelativePosition();
}

bool Text::LayoutFits(float fontSize)
{
    std::vector<std::string> tempLines;

    BuildLines(fontSize, tempLines);

    float availableHeight {GetParentSize().y - _padding.topPadding - _padding.bottomPadding};

    const float lineHeight {CalculateTextHeight(fontSize)};

    return tempLines.size() * lineHeight <= availableHeight;
}

ImVec2 Text::CalculateTextSize(float fontSize, std::string text)
{
    return _fontFamily->CalcTextSizeA(fontSize, FLT_MAX, -1.f, text.c_str());
}

float Text::CalculateTextHeight(float fontSize)
{
    return _fontFamily->CalcTextSizeA(fontSize, FLT_MAX, -1.f, "a").y;
}

void Text::BuildLines(float fontSize, std::vector<std::string>& outLines)
{
    outLines.clear();

    const float availableWidth {GetParentSize().x - _padding.leftPadding - _padding.rightPassing};

    std::string currentLine;

    float currentWidth {0};

    const float spaceWidth {CalculateTextSize(fontSize, " ").x};

    for (const Word& word : _words)
    {
        const float wordWidth {CalculateTextSize(fontSize, word.text).x};

        bool isCurrentLineEmpty {currentLine.empty()};

        const float widthToAdd {isCurrentLineEmpty ? wordWidth : wordWidth + spaceWidth};

        if (currentWidth + widthToAdd <= availableWidth)
        {
            if (!isCurrentLineEmpty)
            {
                currentLine += " ";
            }

            currentLine += word.text;
            currentWidth += widthToAdd;
        }
        else
        {
            if (isCurrentLineEmpty)
            {
                outLines.push_back(word.text);
                currentWidth = 0;
                continue;
            }

            outLines.push_back(currentLine);
            currentLine = word.text;
            currentWidth = wordWidth;
        }
    }

    if (!currentLine.empty())
    {
        outLines.push_back(currentLine);
    }
}

std::string Text::GetText() const
{
    return _text;
}

void Text::Enable()
{
    _currentColor = _color;
}

void Text::Disable()
{
    _currentColor = GRAY;
}

std::unique_ptr<Text> Text::Clone() const
{
    return std::make_unique<Text>(*this);
}

void Text::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    float positionY {_getPositionYAction()};

    for (const auto& line : _lines)
    {
        drawList->AddText(_fontFamily, _fontSize, {_getPositionXAction(), positionY}, _currentColor,
        line.c_str());

        positionY += _textHeight;
    }
}
