#include "MVP/View/DeviceProfilesView.h"

#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "Managers/View/DrawManager.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"

#define RECYCLE_VIEW_VIEWS_PER_ROW 4
#define RECYCLE_VIEW_BUFFER_ROWS 2
#define RECYCLE_VIEW_HORIZONTAL_MARGIN 0.1
#define RECYCLE_VIEW_VERTICAL_MARGIN 0.1
#define RECYCLE_VIEW_ROW_HEIGHT 150

DeviceProfilesView::DeviceProfilesView(bool isHidden) : BaseView(isHidden)
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.15}},
        PIVOT_MIDDLE_CENTER,{0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _title = DrawableFactory::CreateText(TextData{"", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> backButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, false)};

    _backButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Back", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [&]()
            {
                _presenter->OnPressBackButton();
            }, false);

    backButtonRect->AddDrawableComponent(_backButton.get());
    topBarRect->AddRectDrawable(std::move(backButtonRect));

    std::unique_ptr<RectDrawable> currentProfileRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.15}, {1, 0.35}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> currentProfileTitleRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.4}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _currentProfileTitle = DrawableFactory::CreateText(TextData{"Current Profile", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, WHITE});

    currentProfileTitleRect->AddDrawableComponent(_currentProfileTitle.get());

    std::unique_ptr<RectDrawable> currentProfileNameRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.4}, {1, 0.7}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _currentProfileName = DrawableFactory::CreateText(TextData{"Name", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, SUB_TITLE_SIZE, WHITE});

    currentProfileNameRect->AddDrawableComponent(_currentProfileName.get());

    std::unique_ptr<RectDrawable> currentProfileButtonsRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.7}, {1, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    std::unique_ptr<RectDrawable> currentProfileEditButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.45, 0.5}, {0.45, 0.5}},
        PIVOT_MIDDLE_RIGHT, {0, 0}, {50, 50}, false)};

    _editCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Edit", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE},
        [&]()
        {
            //TODO NOTIFY TO EDIT
            Edit();
        }, false);

    currentProfileEditButtonRect->AddDrawableComponent(_editCurrentProfileButton.get());

    std::unique_ptr<RectDrawable> currentProfileUnloadButtonRect {DrawableFactory::CreateRectDrawable(Anchors{{0.55, 0.5}, {0.55, 0.5}},
        PIVOT_MIDDLE_LEFT, {0, 0}, {50, 50}, false)};

    _unloadCurrentProfileButton = DrawableFactory::CreateButton(RectangleData{BLUE, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Unload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE},
        [&]()
        {
            //TODO NOTIFY TO UNLOAD
            Unload();
        }, false);

    currentProfileUnloadButtonRect->AddDrawableComponent(_unloadCurrentProfileButton.get());

    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileEditButtonRect));
    currentProfileButtonsRect->AddRectDrawable(std::move(currentProfileUnloadButtonRect));

    currentProfileRect->AddRectDrawable(std::move(currentProfileTitleRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileNameRect));
    currentProfileRect->AddRectDrawable(std::move(currentProfileButtonsRect));

    std::unique_ptr<RectDrawable> profileRecycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0, 0.35}, {1, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _profilesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(RECYCLE_VIEW_VIEWS_PER_ROW,
        {RECYCLE_VIEW_HORIZONTAL_MARGIN, RECYCLE_VIEW_VERTICAL_MARGIN}, {0, RECYCLE_VIEW_ROW_HEIGHT}, RECYCLE_VIEW_BUFFER_ROWS,
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

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(currentProfileRect));
    AddRectDrawable(std::move(profileRecycleViewRect));
}

void DeviceProfilesView::SetTitle(std::string title)
{
    _title->SetText(title);

    /*ApplicationManager& applicationManager {ApplicationManager::GetInstance()};

    applicationManager.SetEditingDeviceProfiles(_title->GetText());

    std::unordered_map<std::string, Profile> deviceProfiles {applicationManager.GetDeviceProfiles(_title->GetText())};

    for (auto [profileName, profile] : deviceProfiles)
    {
        _profilesRecycleView->AddDrawableComponent(DrawableFactory::CreateButton(RectangleData{WHITE, LOW_ROUNDING, THIN_BORDER, false},
            TextData{profileName, TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [profileName, profile]()
            {
                //TODO PASS TO DEVICE PROFILE CANVAS
            }, false));
    }*/
}

void DeviceProfilesView::Enable()
{
    *_mustBeHidden = false;

    _backButton->Subscribe();

    _editCurrentProfileButton->Subscribe();

    _unloadCurrentProfileButton->Subscribe();

    _profilesRecycleView->Enable();
}

void DeviceProfilesView::Disable()
{
    *_mustBeHidden = true;

    _backButton->Unsubscribe();

    _editCurrentProfileButton->Unsubscribe();

    _unloadCurrentProfileButton->Unsubscribe();

    _profilesRecycleView->Disable();
}

void DeviceProfilesView::Back() const
{
    DrawManager::GetInstance().EnableDevicesView();
}

#include <iostream>

void DeviceProfilesView::Edit() const
{
    std::cout << "Edit" << std::endl;
}

void DeviceProfilesView::Unload() const
{
    std::cout << "Unload" << std::endl;
}
