#include "Factory/DrawableFactory.h"

#include "AnchorsDefines.h"
#include "PivotDefines.h"
#include "UI/Structs/TextData.h"

std::unique_ptr<RectDrawable> DrawableFactory::CreateRectDrawable(RectDrawableData&& rectDrawableData, bool isHidden)
{
    return std::make_unique<RectDrawable>(std::move(rectDrawableData), isHidden);
}

std::unique_ptr<Texture> DrawableFactory::CreateTexture(const char* textureFileName, bool isHidden)
{
    return std::make_unique<Texture>(textureFileName, isHidden);
}

std::unique_ptr<Text> DrawableFactory::CreateText(TextData&& textData, bool isHidden)
{
    return std::make_unique<Text>(std::move(textData), isHidden);
}

std::unique_ptr<TextBox> DrawableFactory::CreateTextBox(RectangleData&& rectangleData, TextData&& textData, bool isHidden)
{
    std::unique_ptr<TextBox> textBox {std::make_unique<TextBox>(textData.text, isHidden)};

    textBox->SetRectangle(CreateRectangle<DrawEmptyRectangle>(std::move(rectangleData), isHidden));

    textBox->SetTextComponent(CreateText(std::move(textData), isHidden));

    return textBox;
}

std::unique_ptr<Button> DrawableFactory::CreateButton(RectangleData&& rectangleData, TextData&& textData,
    std::function<void()>&& action, bool isHidden)
{
    std::unique_ptr<Button> button {std::make_unique<Button>(std::move(action), isHidden)};

    button->SetRectangle(CreateRectangle<DrawFilledRectangle>(std::move(rectangleData), isHidden));

    button->SetTextComponent(CreateText(std::move(textData), isHidden));

    return button;
}

std::unique_ptr<RecycleView> DrawableFactory::CreateRecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews,
    ImVec2&& rowsSize, uint8_t bufferRows, std::function<void(RectDrawable*)>&& addDefault,
    std::function<void()>&& removeLastViewComponents, RecycleViewActions&& devicesPresenterActions, bool isHidden)
{
    return std::make_unique<RecycleView>(viewsPerRow, std::move(marginBetweenViews), std::move(rowsSize),
        std::move(bufferRows), std::move(addDefault), std::move(removeLastViewComponents), std::move(devicesPresenterActions),
        isHidden);
}

/*std::unique_ptr<Dropdown> DrawableFactory::CreateDropdown(RectangleData&& buttonRectangleData,
    TextData&& buttonTextData, float distanceY, ImVec2&& dropdownWindowsSize, uint8_t viewsPerRow,
    ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows, std::function<void(RectDrawable*)>&& addDefault,
    std::function<void()>&& removeLastViewComponents, RecycleViewActions&& devicesPresenterActions, bool isHidden)
{
    std::unique_ptr<Button> button {CreateButton(std::move(buttonRectangleData), std::move(buttonTextData), [](){}, isHidden)};

    std::unique_ptr<RectDrawable> recycleViewContainer {CreateRectDrawable(ANCHORS_BOTTOM_STRETCH, PIVOT_TOP_CENTER,
        {0, distanceY}, std::move(dropdownWindowsSize), true)};

    std::unique_ptr<RecycleView> recycleView {CreateRecycleView(viewsPerRow, std::move(marginBetweenViews), std::move(rowsSize),
        bufferRows, std::move(addDefault), std::move(removeLastViewComponents), std::move(devicesPresenterActions), isHidden)};

    return std::make_unique<Dropdown>(std::move(button), std::move(recycleViewContainer), std::move(recycleView),
        isHidden);
}*/
