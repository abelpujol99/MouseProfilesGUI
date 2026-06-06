#include "MVP/View/Devices/DevicesView.h"

#include "ColorDefines.h"
#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Factory/DrawableFactory.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "Managers/View/DrawManager.h"
#include "Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"

#define RECYCLE_VIEW_VIEWS_PER_ROW 4
#define RECYCLE_VIEW_BUFFER_ROWS 2
#define RECYCLE_VIEW_HORIZONTAL_MARGIN 0.05
#define RECYCLE_VIEW_VERTICAL_MARGIN 0.05
#define RECYCLE_VIEW_ROW_HEIGHT 150

DevicesView::DevicesView(bool isHidden) : BaseView(isHidden), _readDevices(std::make_unique<ReadLinuxDevices>())
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(Anchors{{0, 0}, {1, 0.15}},
        PIVOT_MIDDLE_CENTER,{0, 0}, {0, 100}, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_STRETCH,
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _title = DrawableFactory::CreateText(TextData{"Devices", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> reloadButtonRect {DrawableFactory::CreateRectDrawable(ANCHORS_MIDDLE_LEFT,
        PIVOT_MIDDLE_LEFT, {50, 0}, {50, 50}, false)};

    _reloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Reload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [&]()
            {
                Reload();
            }, false);

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());
    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

    std::unique_ptr<RectDrawable> recycleViewRect {DrawableFactory::CreateRectDrawable(Anchors{{0.1, 0.15}, {0.9, 1}},
        PIVOT_MIDDLE_CENTER, {0, 0}, {0, 0}, false)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(RECYCLE_VIEW_VIEWS_PER_ROW,
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
                Reload();
            },
            [&](float scrollValue)
            {
                _presenter->OnScroll(scrollValue);
            }
        }, false);

    recycleViewRect->AddDrawableComponent(_devicesRecycleView.get());

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(recycleViewRect));

    _presenter->SetItemHeight(RECYCLE_VIEW_ROW_HEIGHT + RECYCLE_VIEW_VERTICAL_MARGIN * 2);
    _presenter->SetViewsPerRow(RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetRecyclerViewBufferRows(RECYCLE_VIEW_BUFFER_ROWS);

    _actionOnDevicesRead = _presenter->SubscribeToDevicesNotifications(DevicesNotifications::SCROLL_UPDATE, [&](){OnScrollUpdate();});
    _actionOnDevicesRead = _presenter->SubscribeToDevicesNotifications(DevicesNotifications::DEVICES_UPDATE, [&](){OnDevicesRead();});

    _reloadButton->Click();
}

void DevicesView::Enable()
{
    *_mustBeHidden = false;

    _reloadButton->Subscribe();

    _devicesRecycleView->Enable();
}

void DevicesView::Disable()
{
    *_mustBeHidden = true;

    _reloadButton->Unsubscribe();

    _devicesRecycleView->Disable();
}

void DevicesView::OnScrollUpdate()
{
    _devicesRecycleView->SetCurrentScroll(_presenter->GetCurrentScroll());

    _devicesRecycleView->SetIsFirstItemPresent(_presenter->IsFirstItemPresent());

    _devicesRecycleView->SetIsLastItemPresent(_presenter->IsLastItemPresent());

    OnDevicesRead();
}

void DevicesView::OnDevicesRead()
{
    std::vector<ButtonInfo> buttonsInfo {_presenter->GetVisibleButtons()};

    std::vector<Button*> buttons {_devicesRecycleView->GetDrawableComponents()};

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

void DevicesView::Reload() const
{
    _presenter->OnPressReloadButton();
}
