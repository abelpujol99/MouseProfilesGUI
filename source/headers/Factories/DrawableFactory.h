#pragma once
#include <memory>

#include "imgui.h"
#include "Font/FontFamilyTypes.h"
#include "UI/Text/TextHorizontalAlignments.h"
#include "UI/Text/TextVerticalAlignments.h"

class Texture;
class Text;
class TextBox;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Texture> CreateTexture(const ImVec2& parentPosition, float positionX, float positionY,
        const char* textureFileName, bool isHidden = false);

    static std::unique_ptr<Text> CreateText(const ImVec2& parentPosition, float positionX, float positionY,
        const char* text, TextHorizontalAlignments horizontalAlignment, TextVerticalAlignments verticalAlignment,
        ImFont* fontFamily, float fontSize, ImColor color, bool isHidden = false);

    static std::unique_ptr<TextBox> CreateTextBox(const ImVec2& parentPosition, float positionX, float positionY,
        int width, int height, float verticalPadding, float horizontalPadding, ImColor textBoxColor, float rounding,
        float thickness, TextHorizontalAlignments textHorizontalAlignment, TextVerticalAlignments textVerticalAlignment,
        FontFamilyTypes textFont, float fontSize, ImColor textColor, bool isHidden = false);
};
