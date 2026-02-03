#pragma once
#include "Drawable.h"

#include "glad/glad.h"

class Texture : public Drawable
{
public:

    Texture(int positionX, int positionY, const char* fileName);

    void Draw(ImDrawList* drawList) override;

private:
    GLuint _texture;

    GLuint LoadTexture(const char* fileName);
};
