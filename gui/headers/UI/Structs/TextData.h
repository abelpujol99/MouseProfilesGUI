#pragma once

#include <string>
#include "imgui.h"

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
