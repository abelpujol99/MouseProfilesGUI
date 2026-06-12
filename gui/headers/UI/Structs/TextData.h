#pragma once

#include "imgui.h"
#include <string>

enum class FontFamilyTypes;
enum class TextHorizontalAlignments;
enum class TextVerticalAlignments;

struct TextData
{
    const std::string& text;
    TextHorizontalAlignments horizontalAlignment;
    TextVerticalAlignments verticalAlignment;
    FontFamilyTypes fontFamily;
    float fontSize;
    ImColor color;
};
