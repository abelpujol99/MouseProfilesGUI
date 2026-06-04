#pragma once

#include <functional>
#include <memory>

#include "AnchorsDefines.h"
#include "PivotDefines.h"
#include "UI/Elements/Complex/Canvas.h"
#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/Text/TextBox.h"
#include "UI/Elements/Intermediate/Texture.h"
#include "Strategies/RecycleViewStrategy/NotResizableRow.h"
#include "Strategies/TextStrategy/ApplyKey.h"
#include "Strategies/TextStrategy/DisplayKey.h"

#include "Utilities/Concepts/DerivedFromDrawableComponent.h"
#include "Utilities/Concepts/DerivedFromBaseRowCreationStrategy.h"

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
class RecycleView;

template<DerivedFromDrawableComponent TDrawableComponent>
class Dropdown;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Canvas> CreateDevicesCanvas(bool isHidden = false);

    static std::unique_ptr<RectDrawable> CreateRectDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition,
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

    template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
    static std::unique_ptr<RecycleView<TDrawableComponent, TRowCreation>> CreateRecycleView(uint8_t viewsPerRow,
        ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows, std::function<void(TDrawableComponent&)>&& onEnable,
        std::function<void(TDrawableComponent&)>&& onDisable, bool isHidden = false);

    template<DerivedFromDrawableComponent TDrawableComponent>
    static std::unique_ptr<Dropdown<TDrawableComponent>> CreateDropdown(RectangleData&& buttonRectangleData,
        TextData&& buttonTextData,float distanceY, ImVec2&& dropdownWindowsSize, Anchors&& resizableDrawablesAnchors,
        ImVec2&& resizableDrawablesPivot, ImVec2&& resizableDrawablesSize, uint8_t bufferSlots, bool isHidden);
};


template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
std::unique_ptr<RecycleView<TDrawableComponent, TRowCreation>> DrawableFactory::CreateRecycleView(uint8_t viewsPerRow,
    ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
    std::function<void(TDrawableComponent&)>&& onEnable, std::function<void(TDrawableComponent&)>&& onDisable,
    bool isHidden)
{
    return std::make_unique<RecycleView<TDrawableComponent, TRowCreation>>(viewsPerRow, std::move(marginBetweenViews),
        std::move(rowsSize), std::move(bufferRows), std::move(onEnable), std::move(onDisable), isHidden);
}

template<DerivedFromDrawableComponent TDrawableComponent>
std::unique_ptr<Dropdown<TDrawableComponent>> DrawableFactory::CreateDropdown(RectangleData&& buttonRectangleData,
    TextData&& buttonTextData, float distanceY, ImVec2&& dropdownWindowsSize, Anchors&& resizableDrawablesAnchors,
    ImVec2&& resizableDrawablesPivot, ImVec2&& resizableDrawablesSize, uint8_t bufferSlots, bool isHidden)
{
    std::unique_ptr<Button> button {CreateButton(std::move(buttonRectangleData), std::move(buttonTextData), [](){}, isHidden)};

    std::unique_ptr<RectDrawable> recycleViewContainer {CreateRectDrawable(ANCHORS_BOTTOM_STRETCH, PIVOT_TOP_CENTER,
        {0, distanceY}, std::move(dropdownWindowsSize), true)};

    std::unique_ptr<RecycleView<TDrawableComponent, NotResizableRow>> recycleView {CreateRecycleView<TDrawableComponent>(std::move(resizableDrawablesAnchors),
        std::move(resizableDrawablesPivot), std::move(resizableDrawablesSize), bufferSlots, isHidden)};

    return std::make_unique<Dropdown<TDrawableComponent>>(std::move(button), std::move(recycleViewContainer), std::move(recycleView),
        isHidden);
}
