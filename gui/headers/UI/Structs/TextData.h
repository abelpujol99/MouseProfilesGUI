#pragma once

#include "imgui.h"
#include <string>

struct TextPadding
{
public:

    TextPadding(float padding);
    TextPadding(float verticalPadding, float horizontalPadding);
    TextPadding(float topPadding, float bottomPadding, float leftPadding, float rightPadding);

private:

    float topPadding;
    float bottomPadding;
    float leftPadding;
    float rightPassing;
};

inline TextPadding::TextPadding(float padding) : TextPadding(padding, padding)
{}

inline TextPadding::TextPadding(float verticalPadding, float horizontalPadding) :
    TextPadding(verticalPadding, verticalPadding, horizontalPadding, horizontalPadding)
{}

inline TextPadding::TextPadding(float topPadding, float bottomPadding, float leftPadding, float rightPadding) :
    topPadding(topPadding), bottomPadding(bottomPadding), leftPadding(leftPadding), rightPassing(rightPadding)
{}

enum class FontFamilyTypes;
enum class TextHorizontalAlignments;
enum class TextVerticalAlignments;

struct TextData
{
    const std::string& text;
    TextHorizontalAlignments horizontalAlignment;
    TextVerticalAlignments verticalAlignment;
    FontFamilyTypes fontFamily;
    float minimumFontSize;
    float maximumFontSize;
    ImColor color;
    TextPadding textPadding;
};
