#pragma once

#include <functional>
#include <memory>

#include "Frontend/UI/Advanced/Button.h"
#include "Frontend/UI/Advanced/Text/TextBox.h"
#include "Frontend/UI/Basic/Rectangle.h"
#include "Frontend/UI/Basic/Text.h"
#include "Frontend/UI/Basic/Texture.h"
#include "Frontend/UI/Strategies/TextStrategy/ApplyKey.h"
#include "Frontend/UI/Strategies/TextStrategy/DisplayKey.h"

struct DrawablePosition;
struct RectangleData;
struct TextData;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Texture> CreateTexture(DrawablePosition&& drawablePosition, const char* textureFileName,
        bool isHidden = false);

    static std::unique_ptr<Rectangle> CreateRectangle(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        bool isHidden = false);

    static std::unique_ptr<Text> CreateText(DrawablePosition&& drawablePosition, TextData&& textData, bool isHidden = false);

    static std::unique_ptr<TextBox<char, ApplyKey>> CreateTextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        TextData&& textData, bool isHidden = false);

    static std::unique_ptr<TextBox<Key, DisplayKey>> CreateDisplayTextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        TextData&& textData, bool isHidden = false);

    static std::unique_ptr<Button> CreateButton(DrawablePosition&& drawablePosition, RectangleData&& rectangleData,
        TextData&& textData, std::function<void()>&& action, bool isHidden = false);
};
