#include "UI/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include "imgui.h"

Texture::Texture(int positionX, int positionY, const char* fileName) : Drawable(positionX, positionY)
{
    _texture = LoadTexture(fileName);
}

GLuint Texture::LoadTexture(const char* fileName)
{
    int width;
    int height;
    int channels;

    unsigned char* data {stbi_load(fileName, &width, &height, &channels, 4)};

    if (!data)
    {
        printf("Failed to load image: %s\n", fileName);
        return 0;
    }

    SetSize(width, height);

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
    drawList->AddImage(_texture, _topLeftPosition, _bottomRightPosition);
}