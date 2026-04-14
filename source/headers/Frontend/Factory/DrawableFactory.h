#pragma once

#include <functional>
#include <memory>

#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/Text/TextBox.h"
#include "Frontend/UI/Elements/Complex/Screen.h"
#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"
#include "Frontend/UI/Elements/Intermediate/Texture.h"
#include "Frontend/UI/Strategies/TextStrategy/ApplyKey.h"
#include "Frontend/UI/Strategies/TextStrategy/DisplayKey.h"

class Anchors;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Screen> CreateScreen(ImVec2&& position, ImVec2&& size, bool isHidden = false);

    static std::unique_ptr<RectDrawable> CreateRectDrawable(Anchors&& anchors, ImVec2&& pivot ,ImVec2&& relativePosition,
    ImVec2&& desiredSize, bool isHidden);

    static std::unique_ptr<Texture> CreateTexture(const char* textureFileName, bool isHidden = false);

    static std::unique_ptr<Rectangle> CreateRectangle(RectangleData&& rectangleData, bool isHidden = false);

    static std::unique_ptr<Text> CreateText(TextData&& textData, bool isHidden = false);

    static std::unique_ptr<TextBox<char, ApplyKey>> CreateTextBox(RectangleData&& rectangleData, TextData&& textData,
        bool isHidden = false);

    static std::unique_ptr<TextBox<Key, DisplayKey>> CreateDisplayTextBox(RectangleData&& rectangleData, TextData&& textData,
        bool isHidden = false);

    static std::unique_ptr<Button> CreateButton(RectangleData&& rectangleData, TextData&& textData, std::function<void()>&& action,
        bool isHidden = false);
};
