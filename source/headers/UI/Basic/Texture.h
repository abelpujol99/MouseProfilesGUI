#pragma once
#include "UI/RectDrawable.h"

#include "glad/glad.h"

class Texture : public RectDrawable
{
public:

    Texture(DrawablePosition&& drawablePosition, const char* fileName, bool isHidden = false);

    ~Texture() override = default;

    void Draw(ImDrawList* drawList) override;

private:

    GLuint _texture;

    GLuint LoadTexture(const char* fileName);
};
