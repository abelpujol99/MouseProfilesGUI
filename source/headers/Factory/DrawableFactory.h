#pragma once
#include <memory>

#include "imgui.h"

class Text;
class Drawable;

class DrawableFactory
{
public:

    static std::unique_ptr<Drawable> CreateTexture(int positionX, int positionY, const char* textureFileName);

    static std::unique_ptr<Drawable> CreateText(int positionX, int positionY, const char* text, ImFont* fontFamily,
        float fontSize, ImColor color);
};
