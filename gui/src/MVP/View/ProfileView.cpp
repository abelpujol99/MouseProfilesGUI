#include "MVP/View/ProfileView.h"

#include "AnchorsDefines.h"
#include "PivotDefines.h"
#include "ColorDefines.h"
#include "TextDefines.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "RectangleDefines.h"
#include "Factory/DrawableFactory.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/TextData.h"
#include "Themes/ProfileViewThemeDefines.h"

ProfileView::ProfileView(bool isHidden) : BaseView(isHidden), _presenter(std::make_unique<ProfilePresenter>())
{
    _templateContainerRectangle = DrawableFactory::CreateRectangle<DrawEmptyRectangle>(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER}, false);

    _templateSubProfileEditButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, RED, NO_PADDING}, []() {}, false);

    _templateSubProfileDeleteButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, RED, NO_PADDING}, []() {}, false);

    _templateInputEditButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, RED, NO_PADDING}, []() {}, false);

    _templateInputDeleteButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, RED, NO_PADDING}, []() {}, false);

    _templateSwitchToSubProfileButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, []() {}, false);

#pragma region Top Bar

    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(RectDrawableData{TOP_BAR_RECT_ANCHORS,
        TOP_BAR_RECT_PIVOT,TOP_BAR_RECT_RELATIVE_POSITION, TOP_BAR_RECT_SIZE}, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(RectDrawableData{TITLE_RECT_ANCHORS,
        TITLE_RECT_PIVOT, TITLE_RECT_RELATIVE_POSITION, TITLE_RECT_SIZE}, false)};

    _title = DrawableFactory::CreateText(TextData{"", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, MAIN_TITLE_SIZE, WHITE, NO_PADDING});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> backButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{BACK_BUTTON_RECT_ANCHORS,
        BACK_BUTTON_RECT_PIVOT, BACK_BUTTON_RECT_RELATIVE_POSITION, BACK_BUTTON_RECT_SIZE}, false)};

    _backButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Back", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING},
            [&]()
            {
                _presenter->OnPressBackButton();
            }, false);

    backButtonRect->AddDrawableComponent(_backButton.get());
    topBarRect->AddRectDrawable(std::move(backButtonRect));

#pragma endregion

#pragma region Profile Name

    std::unique_ptr<RectDrawable> profileNameRect {DrawableFactory::CreateRectDrawable(RectDrawableData{PROFILE_NAME_RECT_ANCHORS,
        PROFILE_NAME_RECT_PIVOT, PROFILE_NAME_RECT_RELATIVE_POSITION, PROFILE_NAME_RECT_SIZE}, false)};

    _profileNameTextBox = DrawableFactory::CreateTextBox(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING});

    profileNameRect->AddDrawableComponent(_profileNameTextBox.get());

#pragma endregion

#pragma region Profile Buttons

    std::unique_ptr<RectDrawable> profileButtonsRect {DrawableFactory::CreateRectDrawable(RectDrawableData{PROFILE_BUTTONS_RECT_ANCHORS,
        PROFILE_BUTTONS_RECT_PIVOT, PROFILE_BUTTONS_RECT_RELATIVE_POSITION, PROFILE_NAME_RECT_SIZE}, false)};

    std::unique_ptr<RectDrawable> profileLoadUnloadButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{PROFILE_LOAD_UNLOAD_BUTTON_RECT_ANCHORS,
        PROFILE_LOAD_UNLOAD_BUTTON_RECT_PIVOT, PROFILE_LOAD_UNLOAD_BUTTON_RECT_RELATIVE_POSITION, PROFILE_LOAD_UNLOAD_BUTTON_RECT_SIZE}, false)};

    _profileLoadUnloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Load/Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]() {
            _presenter->OnPressLoadUnloadButton();
        }, false);

    profileLoadUnloadButtonRect->AddDrawableComponent(_profileLoadUnloadButton.get());

    std::unique_ptr<RectDrawable> profileLinkButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{PROFILE_LINK_BUTTON_RECT_ANCHORS,
        PROFILE_LINK_BUTTON_RECT_PIVOT, PROFILE_LINK_BUTTON_RECT_RELATIVE_POSITION, PROFILE_LINK_BUTTON_RECT_SIZE}, false)};

    _profileLinkButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Link", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]() {
            _presenter->OnPressLinkButton();
        }, false);

    profileLinkButtonRect->AddDrawableComponent(_profileLinkButton.get());

    profileButtonsRect->AddRectDrawable(std::move(profileLoadUnloadButtonRect));
    profileButtonsRect->AddRectDrawable(std::move(profileLinkButtonRect));

#pragma endregion

#pragma region SubProfile

    std::unique_ptr<RectDrawable> subProfileRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_RECT_ANCHORS,
        SUB_PROFILE_RECT_PIVOT, SUB_PROFILE_RECT_RELATIVE_POSITION, SUB_PROFILE_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> subProfileRectangleContainer {_templateContainerRectangle->Clone()};

    subProfileRect->AddDrawableComponent(subProfileRectangleContainer.get());

    subProfileRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(subProfileRectangleContainer));

    std::unique_ptr<RectDrawable> subProfileTitleRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_TITLE_RECT_ANCHORS,
        SUB_PROFILE_TITLE_RECT_PIVOT, SUB_PROFILE_TITLE_RECT_RELATIVE_POSITION, SUB_PROFILE_TITLE_RECT_SIZE}, false)};

    _subProfileTitle = DrawableFactory::CreateText(TextData{"SubProfiles", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, false);

    subProfileTitleRect->AddDrawableComponent(_subProfileTitle.get());

    std::unique_ptr<RectDrawable> subProfileListRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_LIST_RECT_ANCHORS,
        SUB_PROFILE_LIST_RECT_PIVOT, SUB_PROFILE_LIST_RECT_RELATIVE_POSITION, SUB_PROFILE_LIST_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> subProfileListRectangleContainer {_templateContainerRectangle->Clone()};

    subProfileListRect->AddDrawableComponent(subProfileListRectangleContainer.get());

    subProfileListRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(subProfileListRectangleContainer));

    _subProfileRecycleView = DrawableFactory::CreateRecycleView(SUB_PROFILE_RECYCLE_VIEW_VIEWS_PER_ROW,
        SUB_PROFILE_RECYCLE_VIEW_PADDINGS, {0, SUB_PROFILE_RECYCLE_VIEW_ROW_HEIGHT}, SUB_PROFILE_RECYCLE_VIEW_BUFFER_ROWS,
        [&](RectDrawable* view)
        {
            std::unique_ptr<RectDrawable> subProfileEditButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_EDIT_BUTTON_RECT_ANCHORS,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_EDIT_BUTTON_RECT_PIVOT, SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_EDIT_BUTTON_RECT_RELATIVE_POSITION,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_EDIT_BUTTON_RECT_SIZE}, false)};

            std::unique_ptr<Button> subProfileEditButton {_templateSubProfileEditButton->Clone()};

            subProfileEditButtonRect->AddDrawableComponent(subProfileEditButton.get());

            _subProfileEditButtons.push_back(std::move(subProfileEditButton));

            std::unique_ptr<RectDrawable> subProfileDeleteButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_DELETE_BUTTON_RECT_ANCHORS,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_DELETE_BUTTON_RECT_PIVOT, SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_DELETE_BUTTON_RECT_RELATIVE_POSITION,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_SUB_PROFILE_DELETE_BUTTON_RECT_SIZE}, false)};

            std::unique_ptr<Button> subProfileDeleteButton {_templateSubProfileDeleteButton->Clone()};

            subProfileDeleteButtonRect->AddDrawableComponent(subProfileDeleteButton.get());

            _subProfileDeleteButtons.push_back(std::move(subProfileDeleteButton));

            view->AddRectDrawable(std::move(subProfileEditButtonRect));
            view->AddRectDrawable(std::move(subProfileDeleteButtonRect));
        },
        [&]()
        {
            _subProfileEditButtons.pop_back();
            _subProfileDeleteButtons.pop_back();
        },
        {
            [&](uint8_t items)
            {
                _presenter->SetSubProfileRecycleViewVisibleItemsCount(items);
            },
            [&](float size)
            {
                _presenter->SetSubProfileRecyclerViewHeight(size);
            },
            [&](float scrollValue)
            {
                _presenter->OnSubProfileScroll(scrollValue);
            }
        }, false);

    subProfileListRect->AddDrawableComponent(_subProfileRecycleView.get());

    subProfileRect->AddRectDrawable(std::move(subProfileTitleRect));
    subProfileRect->AddRectDrawable(std::move(subProfileListRect));

#pragma endregion

#pragma region Input

    std::unique_ptr<RectDrawable> inputRect {DrawableFactory::CreateRectDrawable(RectDrawableData{INPUT_RECT_ANCHORS, INPUT_RECT_PIVOT,
        INPUT_RECT_RELATIVE_POSITION, INPUT_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> inputRectangleContainer {_templateContainerRectangle->Clone()};

    inputRect->AddDrawableComponent(inputRectangleContainer.get());

    inputRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(inputRectangleContainer));

    std::unique_ptr<RectDrawable> inputTitleRect {DrawableFactory::CreateRectDrawable(RectDrawableData{INPUT_TITLE_RECT_ANCHORS,
        INPUT_TITLE_RECT_PIVOT, INPUT_TITLE_RECT_RELATIVE_POSITION, INPUT_TITLE_RECT_SIZE}, false)};

    _inputTitle = DrawableFactory::CreateText(TextData{"Input", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, false);

    inputTitleRect->AddDrawableComponent(_inputTitle.get());

    std::unique_ptr<RectDrawable> inputListRect {DrawableFactory::CreateRectDrawable(RectDrawableData{INPUT_LIST_RECT_ANCHORS,
        INPUT_LIST_RECT_PIVOT, INPUT_LIST_RECT_RELATIVE_POSITION, INPUT_LIST_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> inputListRectangleContainer {_templateContainerRectangle->Clone()};

    inputListRect->AddDrawableComponent(inputListRectangleContainer.get());

    inputListRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(inputListRectangleContainer));

    _inputRecycleView = DrawableFactory::CreateRecycleView(INPUT_RECYCLE_VIEW_VIEWS_PER_ROW,
        INPUT_RECYCLE_VIEW_PADDINGS, {0, INPUT_RECYCLE_VIEW_ROW_HEIGHT}, INPUT_RECYCLE_VIEW_BUFFER_ROWS,
        [&](RectDrawable* view)
        {
            std::unique_ptr<RectDrawable> subProfileEditButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_EDIT_BUTTON_RECT_ANCHORS,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_EDIT_BUTTON_RECT_PIVOT, SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_EDIT_BUTTON_RECT_RELATIVE_POSITION,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_EDIT_BUTTON_RECT_SIZE}, false)};

            std::unique_ptr<Button> subProfileEditButton {_templateInputEditButton->Clone()};

            subProfileEditButtonRect->AddDrawableComponent(subProfileEditButton.get());

            _inputEditButtons.push_back(std::move(subProfileEditButton));

            std::unique_ptr<RectDrawable> subProfileDeleteButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_DELETE_BUTTON_RECT_ANCHORS,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_DELETE_BUTTON_RECT_PIVOT, SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_DELETE_BUTTON_RECT_RELATIVE_POSITION,
                SUB_PROFILE_RECYCLE_VIEW_DEFAULT_INPUT_DELETE_BUTTON_RECT_SIZE}, false)};

            std::unique_ptr<Button> subProfileDeleteButton {_templateInputDeleteButton->Clone()};

            subProfileDeleteButtonRect->AddDrawableComponent(subProfileDeleteButton.get());

            _inputDeleteButtons.push_back(std::move(subProfileDeleteButton));

            view->AddRectDrawable(std::move(subProfileEditButtonRect));
            view->AddRectDrawable(std::move(subProfileDeleteButtonRect));
        },
        [&]()
        {
            _inputEditButtons.pop_back();
            _inputDeleteButtons.pop_back();
        },
        {
            [&](uint8_t items)
            {
                _presenter->SetInputRecycleViewVisibleItemsCount(items);
            },
            [&](float size)
            {
                _presenter->SetInputRecyclerViewHeight(size);
            },
            [&](float scrollValue)
            {
                _presenter->OnInputScroll(scrollValue);
            }
        }, false);

    inputListRect->AddDrawableComponent(_inputRecycleView.get());

    inputRect->AddRectDrawable(std::move(inputTitleRect));
    inputRect->AddRectDrawable(std::move(inputListRect));

#pragma endregion

#pragma region Output

    std::unique_ptr<RectDrawable> outputRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_RECT_ANCHORS, OUTPUT_RECT_PIVOT,
        OUTPUT_RECT_RELATIVE_POSITION, OUTPUT_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> outputRectangleContainer {_templateContainerRectangle->Clone()};

    outputRect->AddDrawableComponent(outputRectangleContainer.get());

    outputRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(outputRectangleContainer));

    std::unique_ptr<RectDrawable> outputTitleRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_TITLE_RECT_ANCHORS,
        OUTPUT_TITLE_RECT_PIVOT, OUTPUT_TITLE_RECT_RELATIVE_POSITION, OUTPUT_TITLE_RECT_SIZE}, false)};

    _outputTitle = DrawableFactory::CreateText(TextData{"Output", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, false);

    outputTitleRect->AddDrawableComponent(_outputTitle.get());

    std::unique_ptr<RectDrawable> outputTypeRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_TYPE_RECT_ANCHORS,
        OUTPUT_TYPE_RECT_PIVOT, OUTPUT_TYPE_RECT_RELATIVE_POSITION, OUTPUT_TYPE_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> outputTypeRectangleContainer {_templateContainerRectangle->Clone()};

    outputTypeRect->AddDrawableComponent(outputTypeRectangleContainer.get());

    outputTypeRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(outputTypeRectangleContainer));

    std::unique_ptr<RectDrawable> emitInputEventCommandButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_EMIT_INPUT_EVENT_COMMAND_BUTTON_RECT_ANCHORS,
        OUTPUT_EMIT_INPUT_EVENT_COMMAND_BUTTON_RECT_PIVOT, OUTPUT_EMIT_INPUT_EVENT_COMMAND_BUTTON_RECT_RELATIVE_POSITION,
        OUTPUT_EMIT_INPUT_EVENT_COMMAND_BUTTON_RECT_SIZE}, false)};

    _emitInputEventCommandButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Emit Input Event", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]()
    {
        _presenter->OnPressEmitInputEventButton();
        _inputTextBox->SetIsHidden(false);
        _inputDisplayTextBox->SetIsHidden(false);
        _switchToSubProfileRecycleView->SetIsHidden(true);
    }, false);

    emitInputEventCommandButtonRect->AddDrawableComponent(_emitInputEventCommandButton.get());

    std::unique_ptr<RectDrawable> macroCommandButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_MACRO_COMMAND_BUTTON_RECT_ANCHORS,
        OUTPUT_MACRO_COMMAND_BUTTON_RECT_PIVOT, OUTPUT_MACRO_COMMAND_BUTTON_RECT_RELATIVE_POSITION, OUTPUT_MACRO_COMMAND_BUTTON_RECT_SIZE},
        false)};

    _macroCommandButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Macro", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]()
    {
        _presenter->OnPressMacroButton();
    }, false);

    macroCommandButtonRect->AddDrawableComponent(_macroCommandButton.get());

    std::unique_ptr<RectDrawable> switchToSubProfileCommandButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_SWITCH_TO_SUB_PROFILE_COMMAND_BUTTON_RECT_ANCHORS,
        OUTPUT_SWITCH_TO_SUB_PROFILE_COMMAND_BUTTON_RECT_PIVOT, OUTPUT_SWITCH_TO_SUB_PROFILE_COMMAND_BUTTON_RECT_RELATIVE_POSITION,
        OUTPUT_SWITCH_TO_SUB_PROFILE_COMMAND_BUTTON_RECT_SIZE}, false)};

    _switchToSubProfileCommandButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Switch to SubProfile", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]()
    {
        _presenter->OnPressSwitchToSubProfileButton();
        _switchToSubProfileRecycleView->SetIsHidden(false);
        _inputTextBox->SetIsHidden(true);
        _inputDisplayTextBox->SetIsHidden(true);
    }, false);

    switchToSubProfileCommandButtonRect->AddDrawableComponent(_switchToSubProfileCommandButton.get());

    std::unique_ptr<RectDrawable> shutdownApplicationCommandButtonRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_SHUTDOWN_APPLICATION_COMMAND_BUTTON_RECT_ANCHORS,
        OUTPUT_SHUTDOWN_APPLICATION_COMMAND_BUTTON_RECT_PIVOT, OUTPUT_SHUTDOWN_APPLICATION_COMMAND_BUTTON_RECT_RELATIVE_POSITION,
        OUTPUT_SHUTDOWN_APPLICATION_COMMAND_BUTTON_RECT_SIZE}, false)};

    _shutdownApplicationCommandButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Shutdown Application", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, [&]()
    {
        _presenter->OnPressShutdownApplicationButton();
    }, false);

    shutdownApplicationCommandButtonRect->AddDrawableComponent(_shutdownApplicationCommandButton.get());

    outputTypeRect->AddRectDrawable(std::move(emitInputEventCommandButtonRect));
    outputTypeRect->AddRectDrawable(std::move(macroCommandButtonRect));
    outputTypeRect->AddRectDrawable(std::move(switchToSubProfileCommandButtonRect));
    outputTypeRect->AddRectDrawable(std::move(shutdownApplicationCommandButtonRect));

    std::unique_ptr<RectDrawable> outputTypeDetailsRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_TYPE_DETAILS_RECT_ANCHORS,
        OUTPUT_TYPE_DETAILS_RECT_PIVOT, OUTPUT_TYPE_DETAILS_RECT_RELATIVE_POSITION, OUTPUT_TYPE_DETAILS_RECT_SIZE}, false)};

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> outputTypeDetailsRectangleContainer {_templateContainerRectangle->Clone()};

    outputTypeDetailsRect->AddDrawableComponent(outputTypeDetailsRectangleContainer.get());

    outputTypeDetailsRectangleContainer->SetIsHidden(false);

    _containerRectangles.push_back(std::move(outputTypeDetailsRectangleContainer));

    std::unique_ptr<RectDrawable> outputTypeDetailsInputTextBoxRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_TYPE_DETAILS_INPUT_TEXT_BOX_RECT_ANCHORS,
        OUTPUT_TYPE_DETAILS_INPUT_TEXT_BOX_RECT_PIVOT, OUTPUT_TYPE_DETAILS_INPUT_TEXT_BOX_RECT_RELATIVE_POSITION,
        OUTPUT_TYPE_DETAILS_INPUT_TEXT_BOX_RECT_SIZE}, false)};

    _inputTextBox = DrawableFactory::CreateTextBox(RectangleData{WHITE, LOW_ROUNDING, THIN_BORDER},
        TextData{"Type input to emit", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE,
        FontFamilyTypes::ROBOTO_REGULAR, TEXT_SIZE, SUB_TITLE_SIZE, WHITE, NO_PADDING}, true);

    outputTypeDetailsInputTextBoxRect->AddDrawableComponent(_inputTextBox.get());

    std::unique_ptr<RectDrawable> outputTypeDetailsInputDisplayTextBoxRect {DrawableFactory::CreateRectDrawable(RectDrawableData{OUTPUT_TYPE_DETAILS_INPUT_DISPLAY_TEXT_BOX_RECT_ANCHORS,
        OUTPUT_TYPE_DETAILS_INPUT_DISPLAY_TEXT_BOX_RECT_PIVOT, OUTPUT_TYPE_DETAILS_INPUT_DISPLAY_TEXT_BOX_RECT_RELATIVE_POSITION,
        OUTPUT_TYPE_DETAILS_INPUT_DISPLAY_TEXT_BOX_RECT_SIZE}, false)};

    _inputDisplayTextBox = DrawableFactory::CreateDisplayTextBox(RectangleData{INPUT_DISPLAY_TEXT_BOX_COLOR, LOW_ROUNDING, THIN_BORDER},
        TextData{"Emit inputs here", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE,
        FontFamilyTypes::ROBOTO_REGULAR, TEXT_SIZE, SUB_TITLE_SIZE, INPUT_DISPLAY_TEXT_BOX_COLOR, NO_PADDING}, true);

    outputTypeDetailsInputDisplayTextBoxRect->AddDrawableComponent(_inputDisplayTextBox.get());

    _switchToSubProfileRecycleView = DrawableFactory::CreateRecycleView(LIST_OF_SUB_PROFILES_RECYCLE_VIEW_VIEWS_PER_ROW,
        LIST_OF_SUB_PROFILES_RECYCLE_VIEW_PADDINGS, {0, LIST_OF_SUB_PROFILES_RECYCLE_VIEW_ROW_HEIGHT}, LIST_OF_SUB_PROFILES_RECYCLE_VIEW_BUFFER_ROWS,
        [&](RectDrawable* view)
        {
            std::unique_ptr<Button> switchToSubProfileButton {_templateSwitchToSubProfileButton->Clone()};

            view->AddDrawableComponent(switchToSubProfileButton.get());

            _switchToSubProfileListButtons.push_back(std::move(switchToSubProfileButton));
        },
        [&]()
        {
            _switchToSubProfileListButtons.pop_back();
        },
        {
            [&](uint8_t items)
            {
                _presenter->SetSwitchToSubProfileRecycleViewVisibleItemsCount(items);
            },
            [&](float size)
            {
                _presenter->SetSwitchToSubProfileRecyclerViewHeight(size);
            },
            [&](float scrollValue)
            {
                _presenter->OnSwitchToSubProfileScroll(scrollValue);
            }
        }, true);

    outputTypeDetailsRect->AddRectDrawable(std::move(outputTypeDetailsInputTextBoxRect));
    outputTypeDetailsRect->AddRectDrawable(std::move(outputTypeDetailsInputDisplayTextBoxRect));
    outputTypeDetailsRect->AddDrawableComponent(_switchToSubProfileRecycleView.get());

    outputRect->AddRectDrawable(std::move(outputTitleRect));
    outputRect->AddRectDrawable(std::move(outputTypeRect));
    outputRect->AddRectDrawable(std::move(outputTypeDetailsRect));

#pragma endregion

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(profileNameRect));
    AddRectDrawable(std::move(profileButtonsRect));
    AddRectDrawable(std::move(subProfileRect));
    AddRectDrawable(std::move(inputRect));
    AddRectDrawable(std::move(outputRect));

    _presenter->SetSubProfileItemHeight(SUB_PROFILE_RECYCLE_VIEW_ROW_HEIGHT + SUB_PROFILE_RECYCLE_VIEW_VERTICAL_PADDING * 2);
    _presenter->SetSubProfileViewsPerRow(SUB_PROFILE_RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetSubProfileRecyclerViewBufferRows(SUB_PROFILE_RECYCLE_VIEW_BUFFER_ROWS);

    _presenter->SetInputItemHeight(INPUT_RECYCLE_VIEW_ROW_HEIGHT + INPUT_RECYCLE_VIEW_VERTICAL_PADDING * 2);
    _presenter->SetInputViewsPerRow(INPUT_RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetInputRecyclerViewBufferRows(INPUT_RECYCLE_VIEW_BUFFER_ROWS);

    _presenter->SubscribeToProfileNotifications(ProfileNotifications::TITLE_UPDATE, [&](){OnTitleUpdate();});
    _presenter->SubscribeToProfileNotifications(ProfileNotifications::SUB_PROFILE_SCROLL_UPDATE, [&](){OnSubProfileScrollUpdate();});
    _presenter->SubscribeToProfileNotifications(ProfileNotifications::INPUT_SCROLL_UPDATE, [&](){OnInputScrollUpdate();});
}

void ProfileView::SetDeviceName(std::string deviceName)
{
    _presenter->SetDeviceName(std::move(deviceName));
}

void ProfileView::SetProfileIndex(uint8_t profileIndex)
{
    _presenter->SetProfileIndex(profileIndex);
}

void ProfileView::Enable()
{
    *_mustBeHidden = false;

    _backButton->Subscribe();

    _profileNameTextBox->Subscribe();

    _profileLoadUnloadButton->Subscribe();

    _profileLinkButton->Subscribe();

    _subProfileRecycleView->Enable();

    _inputRecycleView->Enable();

    _emitInputEventCommandButton->Enable();

    _macroCommandButton->Enable();

    _switchToSubProfileCommandButton->Enable();

    _shutdownApplicationCommandButton->Enable();

    _presenter->Restart();
}

void ProfileView::Disable()
{
    *_mustBeHidden = true;

    _backButton->Unsubscribe();

    _profileNameTextBox->Unsubscribe();

    _profileLoadUnloadButton->Unsubscribe();

    _profileLinkButton->Unsubscribe();

    _subProfileRecycleView->Disable();

    for (size_t i{0}; i < _subProfileEditButtons.size(); ++i)
    {
        _subProfileEditButtons.at(i)->SetIsHidden(true);
        _subProfileDeleteButtons.at(i)->SetIsHidden(true);
    }

    _inputRecycleView->Disable();

    for (size_t i{0}; i < _inputEditButtons.size(); ++i)
    {
        _inputEditButtons.at(i)->SetIsHidden(true);
        _inputDeleteButtons.at(i)->SetIsHidden(true);
    }

    _emitInputEventCommandButton->Disable();

    _macroCommandButton->Disable();

    _switchToSubProfileCommandButton->Disable();

    _shutdownApplicationCommandButton->Disable();
}

void ProfileView::OnTitleUpdate() const
{
    _title->SetText(_presenter->GetTitle());
}

void ProfileView::OnSubProfileScrollUpdate() const
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetSubProfileVisibleButtons()};

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        uint8_t buttonInfoIndex {buttonInfo.index};

        size_t buttonIndex {buttonInfoIndex % buttonsInfo.size()};

        Button& editButton {*_subProfileEditButtons.at(buttonIndex)};

        editButton.SetText(std::move(buttonInfo.text));

        editButton.SetAction([&, buttonInfoIndex]()
        {
            _presenter->OnPressSubProfileRecycleViewButton(buttonInfoIndex);
        });

        editButton.SetIsHidden(false);

        Button& deleteButton {*_subProfileDeleteButtons.at(buttonIndex)};

        deleteButton.SetAction([&, buttonInfoIndex]()
        {
            _presenter->OnPressSubProfileDeleteButton(buttonInfoIndex);
        });

        _subProfileDeleteButtons.at(i)->SetIsHidden(false);
    }

    for (; i < _subProfileEditButtons.size(); ++i)
    {
        _subProfileEditButtons.at(i)->SetIsHidden(true);
        _subProfileDeleteButtons.at(i)->SetIsHidden(true);
    }
}

void ProfileView::OnInputScrollUpdate() const
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetInputVisibleButtons()};

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        uint8_t buttonInfoIndex {buttonInfo.index};

        size_t buttonIndex {buttonInfoIndex % buttonsInfo.size()};

        Button& editButton {*_inputEditButtons.at(buttonIndex)};

        editButton.SetText(std::move(buttonInfo.text));

        editButton.SetAction([&, buttonInfoIndex]()
        {
            _presenter->OnPressInputRecycleViewButton(buttonInfoIndex);
        });

        editButton.SetIsHidden(false);

        Button& deleteButton {*_inputDeleteButtons.at(buttonIndex)};

        deleteButton.SetAction([&, buttonInfoIndex]()
        {
            _presenter->OnPressInputDeleteButton(buttonInfoIndex);
        });

        deleteButton.SetIsHidden(false);
    }

    for (; i < _inputEditButtons.size(); ++i)
    {
        _inputEditButtons.at(i)->SetIsHidden(true);
        _inputDeleteButtons.at(i)->SetIsHidden(true);
    }
}
