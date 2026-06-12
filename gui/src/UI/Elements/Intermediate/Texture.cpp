#include "UI/Elements/Intermediate/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include <filesystem>

#include "Factory/DrawableFactory.h"

Texture::Texture(const char* fileName, bool isHidden) :
        DrawableComponent(isHidden)
{
    _texture = LoadTexture(fileName);
}

Texture::Texture(const Texture& other) :
    DrawableComponent(true),
    _texture(other._texture)
{}

void Texture::Enable()
{
    //TODO APPLY GRAY FILTER
}

void Texture::Disable()
{
    //TODO REMOVE GRAY FILTER
}

std::unique_ptr<Texture> Texture::Clone() const
{
    return std::make_unique<Texture>(*this);
}

GLuint Texture::LoadTexture(const char* fileName)
{
    int width;
    int height;
    int channels;

    std::filesystem::path resourceDir = RESOURCE_DIR;

    auto path {resourceDir / fileName};

    unsigned char* data {stbi_load(path.c_str(), &width, &height, &channels, 4)};

    if (!data)
    {
        printf("Failed to load image: %s\n", path.c_str());
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}

void Texture::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    drawList->AddImage(_texture, GetParentPosition(), GetParentBottomRightPosition());
}