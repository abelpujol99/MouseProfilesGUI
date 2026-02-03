#pragma once
#include "Drawable.h"

#include "glad/include/glad/glad.h"

class Texture : public Drawable
{
private:
    GLuint _texture;

    GLuint LoadTexture(const char* fileName);

public:

    Texture(int positionX, int positionY, const char* fileName);

    void Draw(ImDrawList* drawList) override;
};
