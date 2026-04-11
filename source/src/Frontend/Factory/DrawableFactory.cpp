#include "Frontend/Factory/DrawableFactory.h"

#include "Frontend/UI/Structs/DrawablePosition.h"

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

std::unique_ptr<TextBox<char, ApplyKey>> DrawableFactory::CreateTextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
    TextData&& textData, bool isHidden)
{
    std::unique_ptr<TextBox<char, ApplyKey>> textBox {std::make_unique<TextBox<char, ApplyKey>>(std::move(drawablePosition))};

    textBox->SetRectangle(CreateRectangle(DrawablePosition{*textBox->GetPosition(), 0, 0}, std::move(rectangleData), isHidden));

    textBox->SetText(CreateText(DrawablePosition{*textBox->GetPosition(), 0, 0}, std::move(textData), isHidden));

    return textBox;
}

std::unique_ptr<TextBox<Key, DisplayKey>> DrawableFactory::CreateDisplayTextBox(DrawablePosition &&drawablePosition,
    RectangleData&& rectangleData, TextData&& textData, bool isHidden)
{
    std::unique_ptr<TextBox<Key, DisplayKey>> textBox {std::make_unique<TextBox<Key, DisplayKey>>(std::move(drawablePosition))};

    textBox->SetRectangle(CreateRectangle(DrawablePosition{*textBox->GetPosition(), 0, 0}, std::move(rectangleData), isHidden));

    textBox->SetText(CreateText(DrawablePosition{*textBox->GetPosition(), 0, 0}, std::move(textData), isHidden));

    return textBox;
}

std::unique_ptr<Button> DrawableFactory::CreateButton(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
    TextData&& textData, std::function<void()>&& action, bool isHidden)
{
    return std::make_unique<Button>(std::move(drawablePosition), std::move(rectangleData), std::move(textData),
        std::move(action), isHidden);
}

std::unique_ptr<Screen> DrawableFactory::CreateScreen(DrawablePosition &&drawablePosition, bool isHidden)
{
    return std::make_unique<Screen>(std::move(drawablePosition), isHidden);
}
