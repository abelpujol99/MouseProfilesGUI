#pragma once
#include "UI/Elements/Base/DrawableComponent.h"

#include "glad/glad.h"

class Texture : public DrawableComponent
{
public:

    Texture(const char* fileName, bool isHidden = false);

    Texture(const Texture& other);

    ~Texture() override = default;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<Texture> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    GLuint _texture;

    GLuint LoadTexture(const char* fileName);
};
