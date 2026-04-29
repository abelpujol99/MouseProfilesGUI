#include "Frontend/Factory/CanvasFactory.h"

#include <filesystem>
#include <iostream>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/Managers/View/WindowManager.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"
#include "Frontend/ColorDefines.h"
#include "Frontend/AnchorsDefines.h"
#include "Frontend/PivotDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/RectangleDefines.h"
#include "Frontend/UI/Elements/Advanced/RecycleView.h"
#include "Frontend/UI/Elements/Advanced/Dropdown.h"

std::unique_ptr<Canvas> CanvasFactory::CreateProfileCanvas(bool isHidden)
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    std::unique_ptr<Canvas> profileScreen {DrawableFactory::CreateCanvas(isHidden)};

#pragma region Device Name

    std::unique_ptr<RectDrawable> deviceNameRect {DrawableFactory::CreateRectDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {0, 10}, {0, 50}, isHidden)};

    std::unique_ptr<Text> deviceNameText {DrawableFactory::CreateText(TextData{"Razer Basilisk V3", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE, WHITE})};

    deviceNameRect->AddDrawableComponent(std::move(deviceNameText));

    profileScreen->AddRectDrawable(std::move(deviceNameRect));

#pragma endregion

#pragma region Profile Name

    std::unique_ptr<RectDrawable> profileNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0.4, 0.1}, {0.6, 0.1}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<TextBox<char, ApplyKey>> profileNameTextBox {DrawableFactory::CreateTextBox(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE})};

    profileNameRect->AddDrawableComponent(std::move(profileNameTextBox));

    profileScreen->AddRectDrawable(std::move(profileNameRect));

#pragma endregion

#pragma region Profile Buttons

    std::unique_ptr<RectDrawable> profileButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.2}, {1, 0.2}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<RectDrawable> profileLoadButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0},{0.3, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<Button> profileLoadButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Load", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, []() {
            std::cout << "Load" << std::endl;
        }, isHidden)};

    profileLoadButtonRect->AddDrawableComponent(std::move(profileLoadButton));

    std::unique_ptr<RectDrawable> profileUnloadButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.4, 0},{0.6, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<Button> profileUnloadButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, []() {
            std::cout << "Unload" << std::endl;
        }, isHidden)};

    profileUnloadButtonRect->AddDrawableComponent(std::move(profileUnloadButton));

    std::unique_ptr<RectDrawable> profileLinkButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.7, 0},{0.9, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<Button> profileLinkButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Link", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, []() {
            std::cout << "Link" << std::endl;
        }, isHidden)};

    profileLinkButtonRect->AddDrawableComponent(std::move(profileLinkButton));

    profileButtonsRect->AddRectDrawable(std::move(profileLoadButtonRect));
    profileButtonsRect->AddRectDrawable(std::move(profileUnloadButtonRect));
    profileButtonsRect->AddRectDrawable(std::move(profileLinkButtonRect));

    profileScreen->AddRectDrawable(std::move(profileButtonsRect));

#pragma endregion

#pragma region SubProfile

    std::unique_ptr<RectDrawable> subProfileRect {DrawableFactory::CreateRectDrawable(Anchors{{0.4, 0.3}, {0.6, 0.3}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<Dropdown<Button>> subProfilesDropdown {DrawableFactory::CreateDropdown<Button>(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"SubProfiles Dropdown", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        10, {0, 100}, ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER, {0, 50}, 4, isHidden)};

    subProfileRect->AddDrawableComponent(std::move(subProfilesDropdown));

    profileScreen->AddRectDrawable(std::move(subProfileRect));

#pragma endregion

#pragma region Input

    std::unique_ptr<RectDrawable> inputRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {0.5, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RectDrawable> inputTitleRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 70}, isHidden)};

    std::unique_ptr<Text> inputTitle {DrawableFactory::CreateText(TextData{"Input", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, isHidden)};

    inputTitleRect->AddDrawableComponent(std::move(inputTitle));

    std::unique_ptr<RectDrawable> inputButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.2}, {1, 0.2}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RectDrawable> inputRecordButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.05, 0}, {0.45, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<Button> inputRecordButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Record", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        []() {
            std::cout << "Record" << std::endl;
        }, isHidden)};

    inputRecordButtonRect->AddDrawableComponent(std::move(inputRecordButton));

    std::unique_ptr<RectDrawable> inputDeleteButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.55, 0}, {0.95, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<Button> inputDeleteButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Delete", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        []() {
            std::cout << "Delete" << std::endl;
        }, isHidden)};

    inputDeleteButtonRect->AddDrawableComponent(std::move(inputDeleteButton));

    inputButtonsRect->AddRectDrawable(std::move(inputRecordButtonRect));
    inputButtonsRect->AddRectDrawable(std::move(inputDeleteButtonRect));

    std::unique_ptr<RectDrawable> inputListRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RecycleView<Button>> subProfileRecycleView {DrawableFactory::CreateRecycleView<Button>(Anchors{{0, 0}, {1, 0}},
        PIVOT_TOP_CENTER,{0, 50}, 2, false)};

    inputListRect->AddDrawableComponent(std::move(subProfileRecycleView));
    inputListRect->AddDrawableComponent(GetText("Inputs List"));
    inputListRect->AddDrawableComponent(GetRectangle(BROWN));

    inputRect->AddRectDrawable(std::move(inputTitleRect));
    inputRect->AddRectDrawable(std::move(inputButtonsRect));
    inputRect->AddRectDrawable(std::move(inputListRect));
    inputRect->AddDrawableComponent(GetRectangle(RED));

    profileScreen->AddRectDrawable(std::move(inputRect));

#pragma endregion

#pragma region Output

    std::unique_ptr<RectDrawable> outputTitleRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 70}, isHidden)};

    std::unique_ptr<Text> outputTitle {DrawableFactory::CreateText(TextData{"Output", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, isHidden)};

    outputTitleRect->AddDrawableComponent(std::move(outputTitle));

    std::unique_ptr<RectDrawable> outputTypeRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.2}, {0.3, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    outputTypeRect->AddDrawableComponent(GetRectangle(BROWN));
    outputTypeRect->AddDrawableComponent(GetText("Output Types"));

    std::unique_ptr<RectDrawable> outputTypeDetailsRect {DrawableFactory::CreateRectDrawable(Anchors{{0.3, 0.2}, {1, 1}}, PIVOT_MIDDLE_CENTER,
    {0, 0}, {0, 0}, isHidden)};

    outputTypeDetailsRect->AddDrawableComponent(GetRectangle(BROWN));
    outputTypeDetailsRect->AddDrawableComponent(GetText("Output Type Details"));

    std::unique_ptr<RectDrawable> outputRect {DrawableFactory::CreateRectDrawable(Anchors{{0.5, 0.4}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    outputRect->AddRectDrawable(std::move(outputTitleRect));
    outputRect->AddRectDrawable(std::move(outputTypeRect));
    outputRect->AddRectDrawable(std::move(outputTypeDetailsRect));
    outputRect->AddDrawableComponent(GetRectangle(RED));

    profileScreen->AddRectDrawable(std::move(outputRect));

#pragma endregion

    return profileScreen;
}

void CanvasFactory::ShowLinesX(void* rect)
{
    for (float i = 0; i < 10; i += 0.5f)
    {
        std::unique_ptr<Rectangle> rectangle {DrawableFactory::CreateRectangle(RectangleData{PURPLE, 0, 1, false}, false)};

        std::unique_ptr<RectDrawable> rectDrawable {DrawableFactory::CreateRectDrawable({{static_cast<float>(i / 10), 0},
            {static_cast<float>(i / 10), 1}}, PIVOT_MIDDLE_CENTER,
            {0, 0},{0, 100}, false)};

        rectDrawable->AddDrawableComponent(std::move(rectangle));

        static_cast<RectDrawable*>(rect)->AddRectDrawable(std::move(rectDrawable));
    }
}

std::unique_ptr<Rectangle> CanvasFactory::GetRectangle(ImColor color)
{
    return std::make_unique<Rectangle>(RectangleData{color, 0, 1, false}, false);
}

std::unique_ptr<Text> CanvasFactory::GetText(std::string string)
{
    return std::make_unique<Text>(TextData{string, TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE,
        FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, RED}, false);
}
