#pragma once

#include <functional>
#include <memory>

#include "Frontend/AnchorsDefines.h"
#include "Frontend/PivotDefines.h"
#include "Frontend/UI/Elements/Complex/Canvas.h"
#include "Frontend/UI/Elements/Advanced/Button.h"
#include "Frontend/UI/Elements/Advanced/Text/TextBox.h"
#include "Frontend/UI/Elements/Base/ResizableDrawable.h"
#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"
#include "Frontend/UI/Elements/Intermediate/Texture.h"
#include "Frontend/UI/Strategies/RecycleViewStrategy/NotResizableRow.h"
#include "Frontend/UI/Strategies/TextStrategy/ApplyKey.h"
#include "Frontend/UI/Strategies/TextStrategy/DisplayKey.h"
#include "Frontend/UI/Structs/TextData.h"

#include "Frontend/Utilities/Concepts/DerivedFromDrawableComponent.h"
#include "Frontend/Utilities/Concepts/DerivedFromBaseRowCreationStrategy.h"

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
class RecycleView;

template<DerivedFromDrawableComponent TDrawableComponent>
class Dropdown;

class DrawableFactory
{
public:

    DrawableFactory() = delete;

    static std::unique_ptr<Canvas> CreateCanvas(bool isHidden = false);

    static std::unique_ptr<RectDrawable> CreateRectDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition,
    ImVec2&& desiredSize, bool isHidden);

    static std::unique_ptr<ResizableDrawable> CreateResizableDrawable(Anchors&& anchors, Pivot&& pivot, ImVec2&& relativePosition,
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
        ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows, bool isHidden = false);

    template<DerivedFromDrawableComponent TDrawableComponent>
    static std::unique_ptr<Dropdown<TDrawableComponent>> CreateDropdown(RectangleData&& buttonRectangleData,
        TextData&& buttonTextData,float distanceY, ImVec2&& dropdownWindowsSize, Anchors&& resizableDrawablesAnchors,
        ImVec2&& resizableDrawablesPivot, ImVec2&& resizableDrawablesSize, uint8_t bufferSlots, bool isHidden);
};

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
std::unique_ptr<RecycleView<TDrawableComponent, TRowCreation>> DrawableFactory::CreateRecycleView(uint8_t viewsPerRow,
    ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows, bool isHidden)
{
    return std::make_unique<RecycleView<TDrawableComponent, TRowCreation>>(viewsPerRow, std::move(marginBetweenViews),
        std::move(rowsSize), bufferRows, isHidden);
}

template<DerivedFromDrawableComponent TDrawableComponent>
std::unique_ptr<Dropdown<TDrawableComponent>> DrawableFactory::CreateDropdown(RectangleData&& buttonRectangleData,
    TextData&& buttonTextData, float distanceY, ImVec2&& dropdownWindowsSize, Anchors&& resizableDrawablesAnchors,
    ImVec2&& resizableDrawablesPivot, ImVec2&& resizableDrawablesSize, uint8_t bufferSlots, bool isHidden)
{
    std::unique_ptr<Button> button {CreateButton(std::move(buttonRectangleData), std::move(buttonTextData), [](){}, isHidden)};

    std::unique_ptr<ResizableDrawable> recycleViewContainer {CreateResizableDrawable(ANCHORS_BOTTOM_STRETCH, PIVOT_TOP_CENTER,
        {0, distanceY}, std::move(dropdownWindowsSize), true)};

    std::unique_ptr<RecycleView<TDrawableComponent, NotResizableRow>> recycleView {CreateRecycleView<TDrawableComponent>(std::move(resizableDrawablesAnchors),
        std::move(resizableDrawablesPivot), std::move(resizableDrawablesSize), bufferSlots, isHidden)};

    return std::make_unique<Dropdown<TDrawableComponent>>(std::move(button), std::move(recycleViewContainer), std::move(recycleView),
        isHidden);
}
