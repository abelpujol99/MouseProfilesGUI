#pragma once
#include "Frontend/UI/Elements/Base/DrawableComponent.h"

#include "glad/glad.h"

class Texture : public DrawableComponent
{
public:

    Texture(const char* fileName, bool isHidden = false);

    ~Texture() override = default;

    void Draw(ImDrawList* drawList) override;

private:

    GLuint _texture;

    GLuint LoadTexture(const char* fileName);
};
