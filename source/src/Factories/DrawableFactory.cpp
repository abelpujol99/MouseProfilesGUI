#include "Factories/DrawableFactory.h"

#include "UI/Basic/Texture.h"
#include "UI/Basic/Rectangle.h"
#include "UI/Basic/Text.h"
#include "UI/Advanced/Text/TextBox.h"
#include "UI/Advanced/Button.h"

std::unique_ptr<Texture> DrawableFactory::CreateTexture(DrawablePosition&& drawablePosition, const char* textureFileName,
    bool isHidden)
{
    return std::make_unique<Texture>(std::move(drawablePosition), textureFileName, isHidden);
}

std::unique_ptr<Rectangle> DrawableFactory::CreateRectangle(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
    bool isHidden)
{
    return std::make_unique<Rectangle>(std::move(drawablePosition), std::move(rectangleData), isHidden);
}

std::unique_ptr<Text> DrawableFactory::CreateText(DrawablePosition&& drawablePosition, TextData&& textData, bool isHidden)
{
    return std::make_unique<Text>(std::move(drawablePosition), std::move(textData), isHidden);
}

std::unique_ptr<TextBox> DrawableFactory::CreateTextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
    TextData&& textData, bool isHidden)
{
    return std::make_unique<TextBox>(std::move(drawablePosition), std::move(rectangleData), std::move(textData), isHidden);
}

std::unique_ptr<Button> DrawableFactory::CreateButton(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
    TextData&& textData, std::function<void()>&& action, bool isHidden)
{
    return std::make_unique<Button>(std::move(drawablePosition), std::move(rectangleData), std::move(textData),
        std::move(action), isHidden);
}