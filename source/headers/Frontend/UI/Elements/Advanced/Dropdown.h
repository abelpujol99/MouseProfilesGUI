#pragma once
#include <memory>

#include "RecycleView.h"
#include "Frontend/UI/Elements/Base/DrawableComponent.h"
#include "Frontend/UI/Elements/Base/RectDrawable.h"
#include "Frontend/UI/Structs/RectangleData.h"

#include "Frontend/Utilities/Concepts/DerivedFromDrawableComponent.h"

template<DerivedFromDrawableComponent TDrawableComponent>
class Dropdown : public DrawableComponent, public DrawableTransform
{
public:

    Dropdown(std::unique_ptr<Button>&& button, std::unique_ptr<RectDrawable>&& recycleViewContainer,
        std::unique_ptr<RecycleView<TDrawableComponent, NotResizableRow>>&& recycleView, bool isHidden);

    ~Dropdown() override = default;

    void AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent);

    void Draw(ImDrawList* drawList) override;

private:

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Button> _button;

    ImVec2 _dropdownWindowSize;

    std::unique_ptr<RectDrawable> _recycleViewContainer;

    std::unique_ptr<RecycleView<TDrawableComponent, NotResizableRow>> _recycleView;

};

template<DerivedFromDrawableComponent TDrawableComponent>
Dropdown<TDrawableComponent>::Dropdown(std::unique_ptr<Button>&& button, std::unique_ptr<RectDrawable>&& recycleViewContainer,
    std::unique_ptr<RecycleView<TDrawableComponent, NotResizableRow>>&& recycleView, bool isHidden) :
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

template<DerivedFromDrawableComponent TDrawableComponent>
void Dropdown<TDrawableComponent>::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    _recycleViewContainer->UpdateAttributes();
}

template<DerivedFromDrawableComponent TDrawableComponent>
void Dropdown<TDrawableComponent>::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    _recycleViewContainer->UpdateAttributes();
}

template<DerivedFromDrawableComponent TDrawableComponent>
void Dropdown<TDrawableComponent>::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    _recycleViewContainer->UpdateAttributes();
}

template<DerivedFromDrawableComponent TDrawableComponent>
void Dropdown<TDrawableComponent>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    _recycleView->AddDrawableComponent(std::move(drawableComponent));
}

template<DerivedFromDrawableComponent TDrawableComponent>
void Dropdown<TDrawableComponent>::Draw(ImDrawList *drawList)
{
    if (IsHidden())
    {
        return;
    }

    _recycleViewContainer->Draw(drawList);

    _button->Draw(drawList);
}
