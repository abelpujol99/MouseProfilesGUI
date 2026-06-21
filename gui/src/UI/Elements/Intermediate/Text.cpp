#include "UI/Elements/Intermediate/Text/Text.h"

#include "ColorDefines.h"
#include "TextDefines.h"
#include "Factory/Font/FontFactory.h"
#include "UI/Elements/Intermediate/Text/TextVerticalAlignments.h"
#include "UI/Elements/Intermediate/Text/TextHorizontalAlignments.h"
#include "UI/Structs/TextData.h"

#define MAX_ITERATIONS 10

Text::Text(TextData&& textData, bool isHidden) :
        DrawableComponent(isHidden), _text(textData.text),
        _horizontalAlignment(textData.horizontalAlignment), _verticalAlignment(textData.verticalAlignment), _fontFamilyType(textData.fontFamily),
        _fontFamily(FontFactory::GetInstance().GetFontFamily(textData.fontFamily)), _minimumFontSize(textData.minimumFontSize),
        _maximumFontSize(textData.maximumFontSize), _color(textData.color), _currentColor(_color), _padding(textData.padding),
        _fontSize(_minimumFontSize)
{
    TextToWords();

    _spaceWidth = FontFactory::GetInstance().GetTextReferenceWidth(_fontFamilyType, " ");
    _referenceTextHeight = CalculateTextSize(BASE_FONT_SIZE, "a").y;
}

Text::Text(const Text& other) :
    DrawableComponent(true),
    _text(other._text),
    _horizontalAlignment(other._horizontalAlignment),
    _verticalAlignment(other._verticalAlignment),
    _fontFamilyType(other._fontFamilyType),
    _fontFamily(FontFactory::GetInstance().GetFontFamily(_fontFamilyType)),
    _minimumFontSize(other._minimumFontSize),
    _maximumFontSize(other._maximumFontSize),
    _color(other._color),
    _currentColor(other._currentColor),
    _padding(other._padding),
    _fontSize(_minimumFontSize),
    _spaceWidth(other._spaceWidth),
    _referenceTextHeight(other._referenceTextHeight)
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

void Text::EraseFromIndex(size_t fist, size_t count)
{
    _text.erase(fist, count);

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

float Text::GetFontSize() const
{
    return _fontSize;
}

FontFamilyTypes Text::GetFontFamily() const
{
    return _fontFamilyType;
}

void Text::UpdateRelativePosition()
{
    if (_horizontalAlignment == TextHorizontalAlignments::LEFT)
    {
        _getPositionXAction = [&](Line line) {
            return GetParentPosition().x;
        };
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::CENTER)
    {
        _getPositionXAction = [&](Line line) {
            return GetParentPosition().x + GetParentSize().x / 2 - line.width / 2;
        };
    }
    else if (_horizontalAlignment == TextHorizontalAlignments::RIGHT)
    {
        _getPositionXAction = [&](Line line) {
            return GetParentPosition().x + GetParentSize().x - line.width;
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
            return GetParentPosition().y + GetParentSize().y / 2 - _textHeight * _lines.size() / 2;
        };
    }
    else if (_verticalAlignment == TextVerticalAlignments::BOTTOM)
    {
        _getPositionYAction = [&]() {
            return GetParentPosition().y + GetParentSize().y - _textHeight * _lines.size();
        };
    }
}

void Text::UpdateLayout()
{
    TextToWords();

    UpdateMeasures();
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

    CalculateWordsWidth();
}

void Text::CalculateWordsWidth()
{
    for (Word& word : _words)
    {
        word.referenceWidth = FontFactory::GetInstance().GetTextReferenceWidth(_fontFamilyType, word.text);
    }
}

ImVec2 Text::CalculateTextSize(float fontSize, std::string text)
{
    return _fontFamily->CalcTextSizeA(fontSize, FLT_MAX, -1.f, text.c_str());
}

void Text::UpdateMeasures()
{
    UpdateFontSize();

    _lines = CreateLines(_fontSize);

    _textHeight = _referenceTextHeight * (_fontSize / BASE_FONT_SIZE);
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

        if (DoesLayoutFit(mid))
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

bool Text::DoesLayoutFit(float fontSize)
{
    std::vector<Line> tempLines {CreateLines(fontSize)};

    const float lineHeight {_textHeight * (fontSize / BASE_FONT_SIZE)};

    float broadestLine {0};

    for (const auto& line : tempLines)
    {
        if (line.width <= broadestLine)
        {
            continue;
        }

        broadestLine = line.width;
    }

    const float availableHeight {GetParentSize().y - _padding.topPadding - _padding.bottomPadding};

    const float availableWidth {GetParentSize().x - _padding.leftPadding - _padding.rightPassing};

    return broadestLine <= availableWidth && tempLines.size() * lineHeight <= availableHeight;
}

std::vector<Text::Line> Text::CreateLines(float fontSize) const
{
    std::vector<Line> lines;

    const float availableWidth {GetParentSize().x - _padding.leftPadding - _padding.rightPassing};

    std::string currentLine;

    float currentWidth {0};

    float scale (fontSize / BASE_FONT_SIZE);

    const float spaceWidth {_spaceWidth * scale};

    for (const Word& word : _words)
    {
        const float wordWidth {word.referenceWidth * scale};

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
                lines.emplace_back(word.text, wordWidth);
                currentWidth = 0;
                continue;
            }

            lines.emplace_back(currentLine, currentWidth);
            currentLine = word.text;
            currentWidth = wordWidth;
        }
    }

    if (!currentLine.empty())
    {
        lines.emplace_back(currentLine, currentWidth);
    }

    return lines;
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

    UpdateRelativePosition();

    float positionY {_getPositionYAction()};

    for (const auto& line : _lines)
    {
        drawList->AddText(_fontFamily, _fontSize, {_getPositionXAction(line), positionY}, _currentColor,
        line.text.c_str());

        positionY += _textHeight;
    }
}
