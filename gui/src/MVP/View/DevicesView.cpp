#include "MVP/View/DevicesView.h"

#include "ColorDefines.h"
#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Themes/DevicesViewThemeDefines.h"
#include "Factory/DrawableFactory.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "Managers/View/DrawManager.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"

DevicesView::DevicesView(bool isHidden) : BaseView(isHidden), _presenter(std::make_unique<DevicesPresenter>())
{
    std::unique_ptr<RectDrawable> topBarRect{DrawableFactory::CreateRectDrawable(TOP_BAR_RECT_ANCHORS,
        TOP_BAR_RECT_PIVOT, TOP_BAR_RECT_RELATIVE_POSITION,  TOP_BAR_RECT_SIZE, false)};

    std::unique_ptr<RectDrawable> titleRect {DrawableFactory::CreateRectDrawable(TITLE_RECT_ANCHORS,
        TITLE_RECT_PIVOT, TITLE_RECT_RELATIVE_POSITION, TITLE_RECT_SIZE, false)};

    _title = DrawableFactory::CreateText(TextData{"Devices", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, MAIN_TITLE_SIZE, WHITE});

    titleRect->AddDrawableComponent(_title.get());
    topBarRect->AddRectDrawable(std::move(titleRect));

    std::unique_ptr<RectDrawable> reloadButtonRect {DrawableFactory::CreateRectDrawable(RELOAD_BUTTON_RECT_ANCHORS,
        RELOAD_BUTTON_RECT_PIVOT, RELOAD_BUTTON_RECT_RELATIVE_POSITION, RELOAD_BUTTON_RECT_SIZE, false)};

    _reloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, true},
        TextData{"Reload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [&]()
            {
                _presenter->OnPressReloadButton();
            }, false);

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());
    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

    std::unique_ptr<RectDrawable> devicesRecycleViewRect {DrawableFactory::CreateRectDrawable(DEVICES_RECYCLE_VIEW_RECT_ANCHORS,
        DEVICES_RECYCLE_VIEW_RECT_PIVOT, DEVICES_RECYCLE_VIEW_RECT_RELATIVE_POSITION, DEVICES_RECYCLE_VIEW_RECT_SIZE, false)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView<Button, NotResizableRow>(DEVICES_RECYCLE_VIEW_VIEWS_PER_ROW,
        DEVICES_RECYCLE_VIEW_MARGINS, {0, DEVICES_RECYCLE_VIEW_ROW_HEIGHT}, DEVICES_RECYCLE_VIEW_BUFFER_ROWS,
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
                _presenter->OnPressReloadButton();
            },
            [&](float scrollValue)
            {
                _presenter->OnScroll(scrollValue);
            }
        }, false);

    devicesRecycleViewRect->AddDrawableComponent(_devicesRecycleView.get());

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(devicesRecycleViewRect));

    _presenter->SetItemHeight(DEVICES_RECYCLE_VIEW_ROW_HEIGHT + DEVICES_RECYCLE_VIEW_VERTICAL_MARGIN * 2);
    _presenter->SetViewsPerRow(DEVICES_RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetRecyclerViewBufferRows(DEVICES_RECYCLE_VIEW_BUFFER_ROWS);

    _presenter->SubscribeToDevicesNotifications(DevicesNotifications::SCROLL_UPDATE, [&](){OnScrollUpdate();});
    _presenter->SubscribeToDevicesNotifications(DevicesNotifications::DEVICES_UPDATE, [&](){OnDevicesRead();});
}

void DevicesView::Enable()
{
    *_mustBeHidden = false;

    _reloadButton->Click();

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