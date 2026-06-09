#include "MVP/View/ProfileView.h"

#include <utility>

#include "ColorDefines.h"
#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Factory/DrawableFactory.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"
#include "Themes/ProfileViewThemeDefines.h"

ProfileView::ProfileView(bool isHidden) : BaseView(isHidden), _presenter(std::make_unique<ProfilePresenter>())
{
#pragma region Top Bar

    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(TOP_BAR_RECT_ANCHORS,
        TOP_BAR_RECT_PIVOT,TOP_BAR_RECT_RELATIVE_POSITION, TOP_BAR_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(TITLE_RECT_ANCHORS,
        TITLE_RECT_PIVOT, TITLE_RECT_RELATIVE_POSITION, TITLE_RECT_SIZE, false)};

    _title = DrawableFactory::CreateText(TextData{"", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> backButtonRect {DrawableFactory::CreateRectDrawable(BACK_BUTTON_RECT_ANCHORS,
        BACK_BUTTON_RECT_PIVOT, BACK_BUTTON_RECT_RELATIVE_POSITION, BACK_BUTTON_RECT_SIZE, false)};

    _backButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Back", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [&]()
            {
                _presenter->OnPressBackButton();
            }, false);

    backButtonRect->AddDrawableComponent(_backButton.get());
    topBarRect->AddRectDrawable(std::move(backButtonRect));

#pragma endregion

#pragma region Profile Name

    std::unique_ptr<RectDrawable> profileNameRect {DrawableFactory::CreateRectDrawable(PROFILE_NAME_RECT_ANCHORS,
        PROFILE_NAME_RECT_PIVOT, PROFILE_NAME_RECT_RELATIVE_POSITION, PROFILE_NAME_RECT_SIZE, false)};

    _profileNameTextBox = DrawableFactory::CreateTextBox(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"", TextHorizontalAlignments::LEFT, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, SUB_TITLE_SIZE, WHITE});

    profileNameRect->AddDrawableComponent(_profileNameTextBox.get());

#pragma endregion

#pragma region Profile Buttons

    std::unique_ptr<RectDrawable> profileButtonsRect {DrawableFactory::CreateRectDrawable(PROFILE_BUTTONS_RECT_ANCHORS,
        PROFILE_BUTTONS_RECT_PIVOT, PROFILE_BUTTONS_RECT_RELATIVE_POSITION, PROFILE_NAME_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> profileLoadUnloadButtonRect {DrawableFactory::CreateRectDrawable(PROFILE_LOAD_UNLOAD_BUTTON_RECT_ANCHORS,
        PROFILE_LOAD_UNLOAD_BUTTON_RECT_PIVOT, PROFILE_LOAD_UNLOAD_BUTTON_RECT_RELATIVE_POSITION, PROFILE_LOAD_UNLOAD_BUTTON_RECT_SIZE, false)};

    _profileLoadUnloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Load/Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, [&]() {
            _presenter->OnPressLoadUnloadButton();
        }, false);

    profileLoadUnloadButtonRect->AddDrawableComponent(_profileLoadUnloadButton.get());

    std::unique_ptr<RectDrawable> profileLinkButtonRect {DrawableFactory::CreateRectDrawable(PROFILE_LINK_BUTTON_RECT_ANCHORS,
        PROFILE_LINK_BUTTON_RECT_PIVOT, PROFILE_LINK_BUTTON_RECT_RELATIVE_POSITION, PROFILE_LINK_BUTTON_RECT_SIZE, false)};

    _profileLinkButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Link", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        TITLE_SIZE, WHITE}, [&]() {
            _presenter->OnPressLinkButton();
        }, false);

    profileLinkButtonRect->AddDrawableComponent(_profileLinkButton.get());

    profileButtonsRect->AddRectDrawable(std::move(profileLoadUnloadButtonRect));
    profileButtonsRect->AddRectDrawable(std::move(profileLinkButtonRect));

#pragma endregion

#pragma region SubProfile

    std::unique_ptr<RectDrawable> subProfileRect {DrawableFactory::CreateRectDrawable(SUB_PROFILE_RECT_ANCHORS,
        SUB_PROFILE_RECT_PIVOT, SUB_PROFILE_RECT_RELATIVE_POSITION, SUB_PROFILE_RECT_SIZE, false)};

    subProfileRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    std::unique_ptr<RectDrawable> subProfileTitleRect {DrawableFactory::CreateRectDrawable(SUB_PROFILE_TITLE_RECT_ANCHORS,
        SUB_PROFILE_TITLE_RECT_PIVOT, SUB_PROFILE_TITLE_RECT_RELATIVE_POSITION, SUB_PROFILE_TITLE_RECT_SIZE, false)};

    _subProfileTitle = DrawableFactory::CreateText(TextData{"SubProfiles", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, false);

    subProfileTitleRect->AddDrawableComponent(_subProfileTitle.get());

    std::unique_ptr<RectDrawable> subProfileButtonsRect {DrawableFactory::CreateRectDrawable(SUB_PROFILE_BUTTONS_RECT_ANCHORS,
        SUB_PROFILE_BUTTONS_RECT_PIVOT, SUB_PROFILE_BUTTONS_RECT_RELATIVE_POSITION, SUB_PROFILE_BUTTONS_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> subProfileAddButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.05, 0}, {0.45, 0}},
        SUB_PROFILE_ADD_BUTTON_RECT_PIVOT, SUB_PROFILE_ADD_BUTTON_RECT_RELATIVE_POSITION, SUB_PROFILE_ADD_BUTTON_RECT_SIZE, false)};

    _subProfileAddButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Add", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        [&]() {
            _presenter->OnPressSubProfileAddButton();
        }, false);

    subProfileAddButtonRect->AddDrawableComponent(_subProfileAddButton.get());

    std::unique_ptr<RectDrawable> subProfileDeleteButtonRect {DrawableFactory::CreateRectDrawable(SUB_PROFILE_DELETE_BUTTON_RECT_ANCHORS,
        SUB_PROFILE_DELETE_BUTTON_RECT_PIVOT, SUB_PROFILE_DELETE_BUTTON_RECT_RELATIVE_POSITION, SUB_PROFILE_DELETE_BUTTON_RECT_SIZE, false)};

    _subProfileDeleteButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Delete", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        [&]() {
            _presenter->OnPressSubProfileDeleteButton();
        }, false);

    subProfileDeleteButtonRect->AddDrawableComponent(_subProfileDeleteButton.get());

    subProfileButtonsRect->AddRectDrawable(std::move(subProfileAddButtonRect));
    subProfileButtonsRect->AddRectDrawable(std::move(subProfileDeleteButtonRect));

    std::unique_ptr<RectDrawable> subProfileListRect {DrawableFactory::CreateRectDrawable(SUB_PROFILE_LIST_RECT_ANCHORS,
        SUB_PROFILE_LIST_RECT_PIVOT, SUB_PROFILE_LIST_RECT_RELATIVE_POSITION, SUB_PROFILE_LIST_RECT_SIZE, false)};

    subProfileListRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    _subProfileRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(SUB_PROFILE_RECYCLE_VIEW_VIEWS_PER_ROW,
        SUB_PROFILE_RECYCLE_VIEW_PADDINGS, {0, SUB_PROFILE_RECYCLE_VIEW_ROW_HEIGHT}, SUB_PROFILE_RECYCLE_VIEW_BUFFER_ROWS,
        [](Button& button){button.Subscribe();},
        [](Button& button){button.Unsubscribe();},
        []()
        {
            return DrawableFactory::CreateButton(
                RectangleData{PURPLE, NO_ROUNDING, THIN_BORDER, false},
                TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
                TITLE_SIZE, RED}, []() {}, true);
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
    subProfileRect->AddRectDrawable(std::move(subProfileButtonsRect));
    subProfileRect->AddRectDrawable(std::move(subProfileListRect));

#pragma endregion

#pragma region Input

    std::unique_ptr<RectDrawable> inputRect {DrawableFactory::CreateRectDrawable(INPUT_RECT_ANCHORS, INPUT_RECT_PIVOT,
        INPUT_RECT_RELATIVE_POSITION, INPUT_RECT_SIZE, false)};

    inputRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    std::unique_ptr<RectDrawable> inputTitleRect {DrawableFactory::CreateRectDrawable(INPUT_TITLE_RECT_ANCHORS,
        INPUT_TITLE_RECT_PIVOT, INPUT_TITLE_RECT_RELATIVE_POSITION, INPUT_TITLE_RECT_SIZE, false)};

    _inputTitle = DrawableFactory::CreateText(TextData{"Input", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, false);

    inputTitleRect->AddDrawableComponent(_inputTitle.get());

    std::unique_ptr<RectDrawable> inputButtonsRect {DrawableFactory::CreateRectDrawable(INPUT_BUTTONS_RECT_ANCHORS,
        INPUT_BUTTONS_RECT_PIVOT, INPUT_BUTTONS_RECT_RELATIVE_POSITION, INPUT_BUTTONS_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> inputRecordButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.05, 0}, {0.45, 0}},
        INPUT_RECORD_BUTTON_RECT_PIVOT, INPUT_RECORD_BUTTON_RECT_RELATIVE_POSITION, INPUT_RECORD_BUTTON_RECT_SIZE, false)};

    _inputRecordButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Record", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        [&]() {
            _presenter->OnPressInputRecordButton();
        }, false);

    inputRecordButtonRect->AddDrawableComponent(_inputRecordButton.get());

    std::unique_ptr<RectDrawable> inputDeleteButtonRect {DrawableFactory::CreateRectDrawable(INPUT_DELETE_BUTTON_RECT_ANCHORS,
        INPUT_DELETE_BUTTON_RECT_PIVOT, INPUT_DELETE_BUTTON_RECT_RELATIVE_POSITION, INPUT_DELETE_BUTTON_RECT_SIZE, false)};

    _inputDeleteButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false},
        TextData{"Delete", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE},
        [&]() {
            _presenter->OnPressInputDeleteButton();
        }, false);

    inputDeleteButtonRect->AddDrawableComponent(_inputDeleteButton.get());

    inputButtonsRect->AddRectDrawable(std::move(inputRecordButtonRect));
    inputButtonsRect->AddRectDrawable(std::move(inputDeleteButtonRect));

    std::unique_ptr<RectDrawable> inputListRect {DrawableFactory::CreateRectDrawable(INPUT_LIST_RECT_ANCHORS,
        INPUT_LIST_RECT_PIVOT, INPUT_LIST_RECT_RELATIVE_POSITION, INPUT_LIST_RECT_SIZE, false)};

    inputListRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    _inputRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(INPUT_RECYCLE_VIEW_VIEWS_PER_ROW,
        INPUT_RECYCLE_VIEW_PADDINGS, {0, INPUT_RECYCLE_VIEW_ROW_HEIGHT}, INPUT_RECYCLE_VIEW_BUFFER_ROWS,
        [](Button& button){button.Subscribe();},
        [](Button& button){button.Unsubscribe();},
        []()
        {
            return DrawableFactory::CreateButton(
                RectangleData{PURPLE, NO_ROUNDING, THIN_BORDER, false},
                TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
                TITLE_SIZE, RED}, []() {}, true);
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
    inputRect->AddRectDrawable(std::move(inputButtonsRect));
    inputRect->AddRectDrawable(std::move(inputListRect));

#pragma endregion

#pragma region Output

    std::unique_ptr<RectDrawable> outputRect {DrawableFactory::CreateRectDrawable(OUTPUT_RECT_ANCHORS, OUTPUT_RECT_PIVOT,
        OUTPUT_RECT_RELATIVE_POSITION, OUTPUT_RECT_SIZE, false)};

    outputRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    std::unique_ptr<RectDrawable> outputTitleRect {DrawableFactory::CreateRectDrawable(OUTPUT_TITLE_RECT_ANCHORS,
        OUTPUT_TITLE_RECT_PIVOT, OUTPUT_TITLE_RECT_RELATIVE_POSITION, OUTPUT_TITLE_RECT_SIZE, false)};

    _outputTitle = DrawableFactory::CreateText(TextData{"Output", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE}, false);

    outputTitleRect->AddDrawableComponent(_outputTitle.get());

    std::unique_ptr<RectDrawable> outputTypeRect {DrawableFactory::CreateRectDrawable(OUTPUT_TYPE_RECT_ANCHORS,
        OUTPUT_TYPE_RECT_PIVOT, OUTPUT_TYPE_RECT_RELATIVE_POSITION, OUTPUT_TYPE_RECT_SIZE, false)};

    outputTypeRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

    std::unique_ptr<RectDrawable> outputTypeDetailsRect {DrawableFactory::CreateRectDrawable(OUTPUT_TYPE_DETAILS_RECT_ANCHORS,
        OUTPUT_TYPE_DETAILS_RECT_PIVOT, OUTPUT_TYPE_DETAILS_RECT_RELATIVE_POSITION, OUTPUT_TYPE_DETAILS_RECT_SIZE, false)};

    outputTypeDetailsRect->AddDrawableComponent(new Rectangle(RectangleData{WHITE, NO_ROUNDING, THIN_BORDER, false}, false));

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

    _subProfileAddButton->Subscribe();

    _subProfileDeleteButton->Subscribe();

    _subProfileRecycleView->Enable();

    _inputRecordButton->Subscribe();

    _inputDeleteButton->Subscribe();

    _inputRecycleView->Enable();

    _presenter->Restart();
}

void ProfileView::Disable()
{
    *_mustBeHidden = true;

    _backButton->Unsubscribe();

    _profileNameTextBox->Unsubscribe();

    _profileLoadUnloadButton->Unsubscribe();

    _profileLinkButton->Unsubscribe();

    _subProfileAddButton->Unsubscribe();

    _subProfileDeleteButton->Unsubscribe();

    _subProfileRecycleView->Disable();

    _inputRecordButton->Unsubscribe();

    _inputDeleteButton->Unsubscribe();

    _inputRecycleView->Disable();
}

void ProfileView::OnTitleUpdate()
{
    _title->SetText(_presenter->GetTitle());
}

void ProfileView::OnSubProfileScrollUpdate()
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetSubProfileVisibleButtons()};

    std::vector<Button*> buttons {_subProfileRecycleView->GetDrawableComponents()};

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        Button& button {(*buttons.at(buttonInfo.index % buttonsInfo.size()))};

        button.SetText(std::move(buttonInfo.text));

        uint8_t index {buttonInfo.index};

        button.SetAction([&, index]()
        {
            _presenter->OnPressSubProfileRecycleViewButton(index);
        });

        button.SetIsHidden(false);
    }

    for (; i < buttonsInfo.size(); ++i)
    {
        buttons.at(i)->SetIsHidden(true);
    }
}

void ProfileView::OnInputScrollUpdate()
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetInputVisibleButtons()};

    std::vector<Button*> buttons {_inputRecycleView->GetDrawableComponents()};

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        Button& button {(*buttons.at(buttonInfo.index % buttonsInfo.size()))};

        button.SetText(std::move(buttonInfo.text));

        uint8_t index {buttonInfo.index};

        button.SetAction([&, index]()
        {
            _presenter->OnPressInputRecycleViewButton(index);
        });

        button.SetIsHidden(false);
    }

    for (; i < buttonsInfo.size(); ++i)
    {
        buttons.at(i)->SetIsHidden(true);
    }

}
