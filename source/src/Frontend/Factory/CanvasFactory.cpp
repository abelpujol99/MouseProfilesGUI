#include "Frontend/Factory/CanvasFactory.h"

#include <filesystem>
#include <iostream>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Factory/Font/FontFamilyTypes.h"
#include "Frontend/UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "Frontend/UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"
#include "Frontend/ColorDefines.h"
#include "Frontend/TextDefines.h"
#include "Frontend/RectangleDefines.h"
#include "Frontend/UI/Elements/Advanced/RecycleView.h"
#include "Frontend/UI/Elements/Advanced/Dropdown.h"

std::unique_ptr<Canvas> CanvasFactory::CreateDevicesCanvas(bool isHidden)
{
    std::unique_ptr<Canvas> devicesScreen {DrawableFactory::CreateCanvas(isHidden)};

    return devicesScreen;
}

std::unique_ptr<Canvas> CanvasFactory::CreateProfileCanvas(bool isHidden)
{
    std::unique_ptr<Canvas> profileScreen {DrawableFactory::CreateCanvas(isHidden)};

/*#pragma region Device Name

    std::unique_ptr<RectDrawable> deviceNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.1}, {1, 0.1}}, PIVOT_TOP_CENTER,
        {0, 10}, {0, 50}, isHidden)};

    std::unique_ptr<Text> deviceNameText {DrawableFactory::CreateText(TextData{"Razer Basilisk V3", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE, WHITE})};

    deviceNameRect->AddDrawableComponent(std::move(deviceNameText));

    profileScreen->AddRectDrawable(std::move(deviceNameRect));

#pragma endregion

#pragma region Profile Name

    std::unique_ptr<RectDrawable> profileNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0.4, 0.2}, {0.6, 0.2}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<TextBox<char, ApplyKey>> profileNameTextBox {DrawableFactory::CreateTextBox(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE})};

    profileNameRect->AddDrawableComponent(std::move(profileNameTextBox));

    profileScreen->AddRectDrawable(std::move(profileNameRect));

#pragma endregion

#pragma region Profile Buttons

    std::unique_ptr<RectDrawable> profileButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.3}, {1, 0.3}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<RectDrawable> profileLoadUnloadButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.3, 0},{0.45, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<Button> profileLoadUnloadButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Load/Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, []() {
            std::cout << "Load/Unload" << std::endl;
        }, isHidden)};

    profileLoadUnloadButtonRect->AddDrawableComponent(std::move(profileLoadUnloadButton));

    std::unique_ptr<RectDrawable> profileLinkButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.55, 0},{0.7, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<Button> profileLinkButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Link", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, []() {
            std::cout << "Link" << std::endl;
        }, isHidden)};

    profileLinkButtonRect->AddDrawableComponent(std::move(profileLinkButton));

    profileButtonsRect->AddRectDrawable(std::move(profileLoadUnloadButtonRect));
    profileButtonsRect->AddRectDrawable(std::move(profileLinkButtonRect));

    profileScreen->AddRectDrawable(std::move(profileButtonsRect));

#pragma endregion

#pragma region SubProfile

    std::unique_ptr<RectDrawable> subProfileRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {0.2, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RectDrawable> subProfileTitleRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 70}, isHidden)};

    std::unique_ptr<Text> subProfileTitle {DrawableFactory::CreateText(TextData{"SubProfiles", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, isHidden)};

    subProfileTitleRect->AddDrawableComponent(std::move(subProfileTitle));

    std::unique_ptr<RectDrawable> subProfileButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.2}, {1, 0.2}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RectDrawable> subProfileAddButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.05, 0}, {0.45, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<Button> subProfileAddButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Add", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        []() {
            std::cout << "Add" << std::endl;
        }, isHidden)};

    subProfileAddButtonRect->AddDrawableComponent(std::move(subProfileAddButton));

    std::unique_ptr<RectDrawable> subProfileDeleteButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.55, 0}, {0.95, 0}}, PIVOT_TOP_CENTER,
        {0, 0}, {0, 50}, isHidden)};

    std::unique_ptr<Button> subProfileDeleteButton {DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Delete", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        []() {
            std::cout << "Delete" << std::endl;
        }, isHidden)};

    subProfileDeleteButtonRect->AddDrawableComponent(std::move(subProfileDeleteButton));

    subProfileButtonsRect->AddRectDrawable(std::move(subProfileAddButtonRect));
    subProfileButtonsRect->AddRectDrawable(std::move(subProfileDeleteButtonRect));

    std::unique_ptr<RectDrawable> subProfileListRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

    std::unique_ptr<RecycleView<Button, NotResizableRow>> subProfileListRecycleView {DrawableFactory::CreateRecycleView<Button, NotResizableRow>(
        1, {0, 0}, {0, 50}, 2, false)};

    auto recyclePtr {subProfileListRecycleView.get()};

    subProfileListRect->AddDrawableComponent(std::move(subProfileListRecycleView));
    subProfileListRect->AddDrawableComponent(GetText("SubProfiles List"));
    subProfileListRect->AddDrawableComponent(GetRectangle(BROWN));

    for (int i {0}; i < 30; ++i)
    {
        std::string string {"Device "};

        string += std::to_string(i);

        recyclePtr->AddDrawableComponent(DrawableFactory::CreateButton(RectangleData{PURPLE, NO_ROUNDING, THIN_BORDER, false},
            TextData{string, TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
                TITLE_SIZE, RED}, [string]() {
            std::cout << string << std::endl;
        }));
    }

    subProfileRect->AddRectDrawable(std::move(subProfileTitleRect));
    subProfileRect->AddRectDrawable(std::move(subProfileButtonsRect));
    subProfileRect->AddRectDrawable(std::move(subProfileListRect));
    subProfileRect->AddDrawableComponent(GetRectangle(RED));

    profileScreen->AddRectDrawable(std::move(subProfileRect));

#pragma endregion

#pragma region Input

    std::unique_ptr<RectDrawable> inputRect {DrawableFactory::CreateRectDrawable(Anchors{{0.2, 0.4}, {0.5, 1}}, PIVOT_MIDDLE_CENTER,
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

    std::unique_ptr<RecycleView<Button, NotResizableRow>> inputListRecycleView {DrawableFactory::CreateRecycleView<Button, NotResizableRow>(
        1, {0, 0},{0, 50}, 2, false)};

    inputListRect->AddDrawableComponent(std::move(inputListRecycleView));
    inputListRect->AddDrawableComponent(GetText("Inputs List"));
    inputListRect->AddDrawableComponent(GetRectangle(BROWN));

    inputRect->AddRectDrawable(std::move(inputTitleRect));
    inputRect->AddRectDrawable(std::move(inputButtonsRect));
    inputRect->AddRectDrawable(std::move(inputListRect));
    inputRect->AddDrawableComponent(GetRectangle(RED));

    profileScreen->AddRectDrawable(std::move(inputRect));

#pragma endregion

#pragma region Output

    std::unique_ptr<RectDrawable> outputRect {DrawableFactory::CreateRectDrawable(Anchors{{0.5, 0.4}, {1, 1}}, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}, isHidden)};

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

    outputRect->AddRectDrawable(std::move(outputTitleRect));
    outputRect->AddRectDrawable(std::move(outputTypeRect));
    outputRect->AddRectDrawable(std::move(outputTypeDetailsRect));
    outputRect->AddDrawableComponent(GetRectangle(RED));

    profileScreen->AddRectDrawable(std::move(outputRect));

#pragma endregion*/

    return profileScreen;
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
