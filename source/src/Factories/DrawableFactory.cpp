#include "Factories/DrawableFactory.h"

#include "UI/Texture.h"
#include "UI/Text.h"

std::unique_ptr<Drawable> DrawableFactory::CreateTexture(int positionX, int positionY, const char* textureFileName)
{
    return std::make_unique<Texture>(positionX, positionY, textureFileName);
}

std::unique_ptr<Drawable> DrawableFactory::CreateText(int positionX, int positionY, const char* text,
    ImFont* fontFamily, float fontSize, ImColor color)
{
    return std::make_unique<Text>(positionX, positionY, text, fontFamily, fontSize, color);
}