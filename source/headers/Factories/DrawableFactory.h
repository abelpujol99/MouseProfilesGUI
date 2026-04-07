#pragma once

#include <functional>
#include <memory>

class Texture;
class Rectangle;
class Text;
class TextBox;
class Button;
class DrawablePosition;
class RectangleData;
class TextData;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Texture> CreateTexture(DrawablePosition&& drawablePosition, const char* textureFileName,
        bool isHidden = false);

    static std::unique_ptr<Rectangle> CreateRectangle(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        bool isHidden = false);

    static std::unique_ptr<Text> CreateText(DrawablePosition&& drawablePosition, TextData&& textData, bool isHidden = false);

    static std::unique_ptr<TextBox> CreateTextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        TextData&& textData, bool isHidden = false);

    static std::unique_ptr<Button> CreateButton(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        TextData&& textData, std::function<void()>&& action, bool isHidden = false);
};
