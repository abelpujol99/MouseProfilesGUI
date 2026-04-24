#include "Frontend/Factory/DrawableFactory.h"

#include "Frontend/Utilities/Anchors.h"

std::unique_ptr<Canvas> DrawableFactory::CreateCanvas(bool isHidden)
{
    return std::make_unique<Canvas>(isHidden);
}

std::unique_ptr<RectDrawable> DrawableFactory::CreateRectDrawable(Anchors&& anchors, ImVec2&& pivot ,ImVec2&& relativePosition,
    ImVec2&& desiredSize, bool isHidden)
{
    return std::make_unique<RectDrawable>(std::move(anchors), std::move(pivot), std::move(relativePosition),
        std::move(desiredSize), isHidden);
}

std::unique_ptr<ResizableDrawable> DrawableFactory::CreateResizableDrawable(Anchors &&anchors, ImVec2 &&pivot,
    ImVec2 &&relativePosition, ImVec2 &&desiredSize, bool isHidden)
{
    return std::make_unique<ResizableDrawable>(std::move(anchors), std::move(pivot), std::move(relativePosition),
        std::move(desiredSize), isHidden);
}

std::unique_ptr<Texture> DrawableFactory::CreateTexture(const char* textureFileName, bool isHidden)
{
    return std::make_unique<Texture>(textureFileName, isHidden);
}

std::unique_ptr<Rectangle> DrawableFactory::CreateRectangle(RectangleData&& rectangleData, bool isHidden)
{
    return std::make_unique<Rectangle>(std::move(rectangleData), isHidden);
}

std::unique_ptr<Text> DrawableFactory::CreateText(TextData&& textData, bool isHidden)
{
    return std::make_unique<Text>(std::move(textData), isHidden);
}

std::unique_ptr<TextBox<char, ApplyKey>> DrawableFactory::CreateTextBox(RectangleData&& rectangleData, TextData&& textData, bool isHidden)
{
    std::unique_ptr<TextBox<char, ApplyKey>> textBox {std::make_unique<TextBox<char, ApplyKey>>(isHidden)};

    textBox->SetRectangle(CreateRectangle(std::move(rectangleData), isHidden));

    textBox->SetText(CreateText(std::move(textData), isHidden));

    return textBox;
}

std::unique_ptr<TextBox<Key, DisplayKey>> DrawableFactory::CreateDisplayTextBox(RectangleData&& rectangleData, TextData&& textData, bool isHidden)
{
    std::unique_ptr<TextBox<Key, DisplayKey>> textBox {std::make_unique<TextBox<Key, DisplayKey>>(isHidden)};

    textBox->SetRectangle(CreateRectangle(std::move(rectangleData), isHidden));

    textBox->SetText(CreateText(std::move(textData), isHidden));

    return textBox;
}

std::unique_ptr<Button> DrawableFactory::CreateButton(RectangleData&& rectangleData, TextData&& textData,
    std::function<void()>&& action, bool isHidden)
{
    std::unique_ptr<Button> button {std::make_unique<Button>(std::move(action), isHidden)};

    button->SetRectangle(CreateRectangle(std::move(rectangleData), isHidden));

    button->SetText(CreateText(std::move(textData), isHidden));

    return button;
}
