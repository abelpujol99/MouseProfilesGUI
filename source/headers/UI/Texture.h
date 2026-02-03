#pragma once
#include "RectDrawable.h"

#include "glad/glad.h"

class Texture : public RectDrawable
{
public:

    Texture(const ImVec2& parentPosition, float positionX, float positionY, const char* fileName, bool isHidden = false);

    ~Texture() override = default;

    void Draw(ImDrawList* drawList) override;

private:

    GLuint _texture;

    GLuint LoadTexture(const char* fileName);
};
