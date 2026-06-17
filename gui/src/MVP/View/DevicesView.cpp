#include "MVP/View/DevicesView.h"

#include "AnchorsDefines.h"
#include "PivotDefines.h"
#include "ColorDefines.h"
#include "RectangleDefines.h"
#include "TextDefines.h"
#include "Factory/Font/FontFamilyTypes.h"
#include "Factory/DrawableFactory.h"
#include "UI/Elements/Advanced/Text/TextHorizontalAlignments.h"
#include "UI/Elements/Advanced/Text/TextVerticalAlignments.h"
#include "UI/Structs/TextData.h"
#include "Themes/DevicesViewThemeDefines.h"

DevicesView::DevicesView(bool isHidden) : BaseView(isHidden), _presenter(std::make_unique<DevicesPresenter>())
{
    _templateDeviceButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
        SUB_TITLE_SIZE, WHITE}, [&](){}, false);

#pragma region Top Bar

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

    _reloadButton = DrawableFactory::CreateButton(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER},
        TextData{"Reload", TextHorizontalAlignments::CENTER, TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR,
            SUB_TITLE_SIZE, WHITE},
            [&]()
            {
                _presenter->OnPressReloadButton();
            }, false);

    reloadButtonRect->AddDrawableComponent(_reloadButton.get());
    topBarRect->AddRectDrawable(std::move(reloadButtonRect));

#pragma endregion

#pragma region Devices Recycle View

    std::unique_ptr<RectDrawable> devicesRecycleViewRect {DrawableFactory::CreateRectDrawable(DEVICES_RECYCLE_VIEW_RECT_ANCHORS,
        DEVICES_RECYCLE_VIEW_RECT_PIVOT, DEVICES_RECYCLE_VIEW_RECT_RELATIVE_POSITION, DEVICES_RECYCLE_VIEW_RECT_SIZE, false)};

    _devicesRecycleView = DrawableFactory::CreateRecycleView(DEVICES_RECYCLE_VIEW_VIEWS_PER_ROW,
        DEVICES_RECYCLE_VIEW_PADDINGS, {0, DEVICES_RECYCLE_VIEW_ROW_HEIGHT}, DEVICES_RECYCLE_VIEW_BUFFER_ROWS,
        [&](RectDrawable* view)
        {
            std::unique_ptr<Button> deviceViewButton {_templateDeviceButton->Clone()};

            view->AddDrawableComponent(deviceViewButton.get());

            _devicesButtons.push_back(std::move(deviceViewButton));
        },
        [&]()
        {
            _devicesButtons.pop_back();
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

#pragma endregion

    AddRectDrawable(std::move(topBarRect));
    AddRectDrawable(std::move(devicesRecycleViewRect));

    _presenter->SetItemHeight(DEVICES_RECYCLE_VIEW_ROW_HEIGHT + DEVICES_RECYCLE_VIEW_VERTICAL_PADDING * 2);
    _presenter->SetViewsPerRow(DEVICES_RECYCLE_VIEW_VIEWS_PER_ROW);
    _presenter->SetRecyclerViewBufferRows(DEVICES_RECYCLE_VIEW_BUFFER_ROWS);

    _presenter->SubscribeToDevicesNotifications(DevicesNotifications::SCROLL_UPDATE, [&](){OnScrollUpdate();});
    _presenter->SubscribeToDevicesNotifications(DevicesNotifications::DEVICES_UPDATE, [&](){OnDevicesRead();});
}

void DevicesView::Enable()
{
    *_mustBeHidden = false;

    _reloadButton->Subscribe();

    _devicesRecycleView->Enable();

    _presenter->Restart();
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

    size_t i{0};

    for (; i < buttonsInfo.size(); ++i)
    {
        ButtonInfo& buttonInfo {buttonsInfo.at(i)};

        Button& button {(*_devicesButtons.at(buttonInfo.index % buttonsInfo.size()))};

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
        _devicesButtons.at(i)->SetIsHidden(true);
    }
}