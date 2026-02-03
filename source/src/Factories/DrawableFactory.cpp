#include "Factories/DrawableFactory.h"

#include "UI/Texture.h"

std::unique_ptr<Drawable> DrawableFactory::CreateTexture(int positionX, int positionY, const char* textureFileName)
{
    return std::make_unique<Texture>(positionX, positionY, textureFileName);
}
