#pragma once

#include <functional>
#include <memory>

#include "UI/Elements/Intermediate/Texture.h"
#include "UI/Elements/Advanced/Button.h"
#include "UI/Elements/Advanced/Text/TextBox.h"
#include "UI/Elements/Advanced/RecycleView/RecycleView.h"
#include "UI/Elements/Advanced/RecycleView/RecycleViewActions.h"
#include "UI/Elements/Advanced/Dropdown.h"
#include "Strategies/TextStrategy/ApplyKey.h"
#include "Strategies/TextStrategy/DisplayKey.h"

class DrawableFactory
{
public:

    DrawableFactory() = delete;

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

    static std::unique_ptr<RecycleView> CreateRecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize,
        uint8_t bufferRows, std::function<void(RectDrawable*)>&& addDefault, std::function<void()>&& removeLastViewComponents,
        RecycleViewActions&& devicesPresenterActions, bool isHidden = false);

    static std::unique_ptr<Dropdown> CreateDropdown(RectangleData&& buttonRectangleData,
        TextData&& buttonTextData, float distanceY, ImVec2&& dropdownWindowsSize, uint8_t viewsPerRow, ImVec2&& marginBetweenViews,
        ImVec2&& rowsSize, uint8_t bufferRows, std::function<void(RectDrawable*)>&& addDefault,
        std::function<void()>&& removeLastViewComponents, RecycleViewActions&& devicesPresenterActions, bool isHidden = false);
};
