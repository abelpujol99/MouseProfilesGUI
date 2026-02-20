#include "Factories/DrawableFactory.h"

#include "Factories/Font/FontFactory.h"
#include "UI/Texture.h"
#include "UI/Text/Text.h"
#include "UI/Text/TextBox.h"

std::unique_ptr<Texture> DrawableFactory::CreateTexture(const ImVec2& parentPosition, float positionX,
    float positionY, const char* textureFileName, bool isHidden)
{
    return std::make_unique<Texture>(parentPosition, positionX, positionY, textureFileName, isHidden);
}

std::unique_ptr<Text> DrawableFactory::CreateText(const ImVec2& parentPosition, float positionX, float positionY,
    std::string text, TextHorizontalAlignments horizontalAlignment, TextVerticalAlignments verticalAlignment,
    ImFont* fontFamily, float fontSize, ImColor color, bool isHidden)
{
    return std::make_unique<Text>(parentPosition, positionX, positionY, text, horizontalAlignment,
        verticalAlignment, fontFamily, fontSize, color, isHidden);
}

std::unique_ptr<TextBox> DrawableFactory::CreateTextBox(const ImVec2& parentPosition, float positionX, float positionY,
    int width, int height, float verticalPadding, float horizontalPadding, ImColor textBoxColor, float rounding, float thickness,
    TextHorizontalAlignments textHorizontalAlignment, TextVerticalAlignments textVerticalAlignment, FontFamilyTypes textFont,
    float fontSize, ImColor textColor, bool isHidden)
{
    return std::make_unique<TextBox>(parentPosition, positionX, positionY, width, height, verticalPadding,
        horizontalPadding, textBoxColor, rounding, thickness, textHorizontalAlignment, textVerticalAlignment,
        textFont, fontSize, textColor, isHidden);
}
