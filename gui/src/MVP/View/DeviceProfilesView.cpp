#include "MVP/View/DeviceProfilesView.h"

#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "Managers/View/DrawManager.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"
#include "Themes/DeviceProfilesViewThemeDefines.h"

DeviceProfilesView::DeviceProfilesView(bool isHidden) : BaseView(isHidden), _presenter(std::make_unique<DeviceProfilesPresenter>())
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

#pragma region Current Profile

    std::unique_ptr<RectDrawable> currentProfileRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_RECT_ANCHORS,
        CURRENT_PROFILE_RECT_PIVOT, CURRENT_PROFILE_RECT_RELATIVE_POSITION, CURRENT_PROFILE_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> currentProfileTitleRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_TITLE_RECT_ANCHORS,
        CURRENT_PROFILE_TITLE_RECT_PIVOT, CURRENT_PROFILE_TITLE_RECT_RELATIVE_POSITION, CURRENT_PROFILE_TITLE_RECT_SIZE, false)};

    _currentProfileTitle = DrawableFactory::CreateText(TextData{"Current Profile", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE});

    currentProfileTitleRect->AddDrawableComponent(_currentProfileTitle.get());

    std::unique_ptr<RectDrawable> currentProfileNameRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_NAME_RECT_ANCHORS,
        CURRENT_PROFILE_NAME_RECT_PIVOT, CURRENT_PROFILE_NAME_RECT_RELATIVE_POSITION, CURRENT_PROFILE_NAME_RECT_SIZE, false)};

    _currentProfileName = DrawableFactory::CreateText(TextData{"Name", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, SUB_TITLE_SIZE, WHITE});

    currentProfileNameRect->AddDrawableComponent(_currentProfileName.get());

    std::unique_ptr<RectDrawable> currentProfileButtonsRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_BUTTONS_RECT_ANCHORS,
        CURRENT_PROFILE_BUTTONS_RECT_PIVOT, CURRENT_PROFILE_BUTTONS_RECT_RELATIVE_POSITION, CURRENT_PROFILE_BUTTONS_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> currentProfileEditButtonRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_EDIT_BUTTON_RECT_ANCHORS,
        CURRENT_PROFILE_EDIT_BUTTON_RECT_PIVOT, CURRENT_PROFILE_EDIT_BUTTON_RECT_RELATIVE_POSITION, CURRENT_PROFILE_EDIT_BUTTON_RECT_SIZE, false)};

    _editCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Edit", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE},
        [&]()
        {
            _presenter->OnPressEditButton();
        }, false);

    currentProfileEditButtonRect->AddDrawableComponent(_editCurrentProfileButton.get());

    std::unique_ptr<RectDrawable> currentProfileUnloadButtonRect {DrawableFactory::CreateRectDrawable(CURRENT_PROFILE_UNLOAD_BUTTON_RECT_ANCHORS,
        CURRENT_PROFILE_UNLOAD_BUTTON_RECT_PIVOT, CURRENT_PROFILE_UNLOAD_BUTTON_RECT_RELATIVE_POSITION, CURRENT_PROFILE_UNLOAD_BUTTON_RECT_SIZE, false)};

    _unloadCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE},
        [&]()
        {
            _presenter->OnPressUnloadButton();
        }, false);

    currentProfileUnloadButtonRect->AddDrawableComponent(_unloadCurrentProfileButton.get());

    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileEditButtonRect));
    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileUnloadButtonRect));

    currentProfileRect->AddRectDrawable(std::move(currentProfileTitleRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileNameRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileButtonsRect));

#pragma endregion

#pragma region Profile Recycle View

    std::unique_ptr<RectDrawable> profileRecycleViewRect {DrawableFactory::CreateRectDrawable(PROFILE_RECYCLE_VIEW_RECT_ANCHORS_SHRANK,
        PROFILE_RECYCLE_VIEW_RECT_PIVOT, PROFILE_RECYCLE_VIEW_RECT_RELATIVE_POSITION, PROFILE_RECYCLE_VIEW_RECT_SIZE, false)};

    _profileRecycleViewRect = profileRecycleViewRect.get();

    _profilesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(PROFILE_RECYCLE_VIEW_VIEWS_PER_ROW,
        PROFILE_RECYCLE_VIEW_PADDINGS, {0, PROFILE_RECYCLE_VIEW_ROW_HEIGHT}, PROFILE_RECYCLE_VIEW_BUFFER_ROWS,
        [](Button& button){button.Subscribe();},
        [](Button& button){button.Unsubscribe();},
        []()
        {
            return DrawableFactory::CreateButton(
                RectangleData{WHITE, LOW_ROUNDING, THIN_BORDER, false},
                TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
                SUB_TITLE_SIZE, WHITE},
                [&](){}, true);
        },
        {
            [&](uint8_t items)
            {
                _presenter->SetRecycleViewVisibleItemsCount(items);
            },
            [&](float size)
            {
                _presenter->SetRecyclerViewHeight(size);
            },
            [&](float scrollValue)
            {
                _presenter->OnScroll(scrollValue);
            }
        }, false);

    profileRecycleViewRect->AddDrawableComponent(_profilesRecycleView.get());

#pragma endregion

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(currentProfileRect));
    AddRectDrawable(std::move(profileRecycleViewRect));

    _presenter->SetItemHeight(PROFILE_RECYCLE_VIEW_ROW_HEIGHT + PROFILE_RECYCLE_VIEW_VERTICAL_PADDING * 2);
    _presenter->SetViewsPerRow(PROFILE_RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetRecyclerViewBufferRows(PROFILE_RECYCLE_VIEW_BUFFER_ROWS);

    _presenter->SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications::SCROLL_UPDATE, [&](){OnScrollUpdate();});
    _presenter->SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications::PROFILES_UPDATE, [&](){OnProfilesRead();});
    _presenter->SubscribeToDeviceProfilesNotifications(DeviceProfilesNotifications::CURRENT_PROFILE_UPDATE, [&](){OnCurrentProfileUpdate();});
}

void DeviceProfilesView::SetTitle(std::string title)
{
    _title->SetText(title);

    _presenter->SetDeviceName(title);
}

void DeviceProfilesView::Enable()
{
    *_mustBeHidden = false;

    _backButton->Subscribe();

    _editCurrentProfileButton->Subscribe();

    _unloadCurrentProfileButton->Subscribe();

    _profilesRecycleView->Enable();

    _presenter->Restart();
}

void DeviceProfilesView::Disable()
{
    *_mustBeHidden = true;

    _backButton->Unsubscribe();

    _editCurrentProfileButton->Unsubscribe();

    _unloadCurrentProfileButton->Unsubscribe();

    _profilesRecycleView->Disable();
}

void DeviceProfilesView::OnScrollUpdate()
{
    _profilesRecycleView->SetCurrentScroll(_presenter->GetCurrentScroll());

    _profilesRecycleView->SetIsFirstItemPresent(_presenter->IsFirstItemPresent());

    _profilesRecycleView->SetIsLastItemPresent(_presenter->IsLastItemPresent());

    OnProfilesRead();
}

void DeviceProfilesView::OnCurrentProfileUpdate()
{
    std::string currentProfileName {_presenter->GetActiveProfileName()};

    _currentProfileName->SetText(currentProfileName);

    if (currentProfileName.empty())
    {
        _currentProfileTitle->SetIsHidden(true);
        _currentProfileName->SetIsHidden(true);
        _editCurrentProfileButton->SetIsHidden(true);
        _unloadCurrentProfileButton->SetIsHidden(true);
        _profileRecycleViewRect->SetAnchors(PROFILE_RECYCLE_VIEW_RECT_ANCHORS_EXPANDED);
        return;
    }

    _profileRecycleViewRect->SetAnchors(PROFILE_RECYCLE_VIEW_RECT_ANCHORS_SHRANK);
}

void DeviceProfilesView::OnProfilesRead()
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetVisibleButtons()};

    std::vector<Button*> buttons {_profilesRecycleView->GetDrawableComponents()};

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        Button& button {(*buttons.at(buttonInfo.index % buttonsInfo.size()))};

        button.SetText(std::move(buttonInfo.text));

        uint8_t index {buttonInfo.index};

        button.SetAction([&, index]()
        {
            _presenter->OnPressRecycleViewButton(index);
        });

        button.SetIsHidden(false);
    }

    for (; i < buttonsInfo.size(); ++i)
    {
        buttons.at(i)->SetIsHidden(true);
    }
}