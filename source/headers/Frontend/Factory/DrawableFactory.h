#pragma once

#include <functional>
#include <memory>

#include "Frontend/UI/Elements/Complex/Canvas.h"
#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/Text/TextBox.h"
#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"
#include "Frontend/UI/Elements/Intermediate/Texture.h"
#include "Frontend/UI/Strategies/TextStrategy/ApplyKey.h"
#include "Frontend/UI/Strategies/TextStrategy/DisplayKey.h"

#include "Frontend/Utilities/Concepts/DerivedFromDrawableComponent.h"
template<DerivedFromDrawableComponent TDrawableComponent>
class RecycleView;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Canvas> CreateScreen(bool isHidden = false);

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

    template<DerivedFromDrawableComponent TDrawableComponent>
    static std::unique_ptr<RecycleView<TDrawableComponent>> CreateRecycleView(RectDrawable* parentDrawable,
        Anchors&& rectDrawablesAnchors, ImVec2&& rectDrawablesPivot, ImVec2&& rectDrawablesSize, uint8_t bufferSlots,
        bool isHidden = false);
};

template<DerivedFromDrawableComponent TDrawableComponent>
std::unique_ptr<RecycleView<TDrawableComponent>> DrawableFactory::CreateRecycleView(RectDrawable* parentDrawable,
    Anchors&& rectDrawablesAnchors, ImVec2&& rectDrawablesPivot, ImVec2&& rectDrawablesSize, uint8_t bufferSlots, bool isHidden)
{
    return std::make_unique<RecycleView<TDrawableComponent>>(parentDrawable, std::move(rectDrawablesAnchors), std::move(rectDrawablesPivot),
        std::move(rectDrawablesSize), bufferSlots, isHidden);
}
