#pragma once
#include <memory>

class Drawable;

class DrawableFactory
{
public:

    static std::unique_ptr<Drawable> CreateTexture(int positionX, int positionY, const char* textureFileName);
};
