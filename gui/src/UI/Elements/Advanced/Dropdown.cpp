#include "UI/Elements/Advanced/Dropdown.h"

#include "RectangleDefines.h"
#include "Factory/DrawableFactory.h"

Dropdown::Dropdown(std::unique_ptr<Button>&& button, std::unique_ptr<RectDrawable>&& recycleViewContainer,
    std::unique_ptr<RecycleView>&& recycleView, bool isHidden) :
        DrawableComponent(isHidden), _button(std::move(button)), _recycleViewContainer(std::move(recycleViewContainer)),
        _recycleView(std::move(recycleView))
{
    _button->SetAction([&]() {
        _recycleViewContainer->SetIsHidden(false);
    });

    _recycleViewContainer->AddDrawableComponent(_recycleView.get());

    _button->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());
    _recycleViewContainer->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rectangle = DrawableFactory::CreateRectangle(RectangleData{GRAY, LOW_ROUNDING, THIN_BORDER, false}, false);
    _recycleViewContainer->AddDrawableComponent(_rectangle.get());
}

void Dropdown::Enable()
{
    _rectangle->Enable();

    _button->Enable();

    _recycleViewContainer->Enable();

    _recycleView->Enable();
}

void Dropdown::Disable()
{
    _rectangle->Disable();

    _button->Disable();

    _recycleViewContainer->Disable();

    _recycleView->Disable();
}

void Dropdown::OnParentPositionUpdated()
{
    DrawableComponent::OnParentPositionUpdated();

    *_position = GetParentPosition();

    _recycleViewContainer->UpdateAttributes();
}

void Dropdown::OnParentBottomRightPositionUpdated()
{
    DrawableComponent::OnParentBottomRightPositionUpdated();

    *_bottomRightPosition = GetParentBottomRightPosition();

    _recycleViewContainer->UpdateAttributes();
}

void Dropdown::OnParentSizeUpdated()
{
    DrawableComponent::OnParentSizeUpdated();

    *_size = GetParentSize();

    _recycleViewContainer->UpdateAttributes();
}

void Dropdown::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _recycleViewContainer->Draw(drawList);

    _button->Draw(drawList);
}
