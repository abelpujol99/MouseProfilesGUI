#pragma once
#include <memory>

#include "Button.h"
#include "RecycleView/RecycleView.h"
#include "UI/Elements/Base/DrawableComponent.h"
#include "UI/Elements/Base/RectDrawable.h"

class Dropdown : public DrawableComponent, public DrawableTransform
{
public:

    Dropdown(std::unique_ptr<Button>&& button, std::unique_ptr<RectDrawable>&& recycleViewContainer,
        std::unique_ptr<RecycleView>&& recycleView, bool isHidden);

    ~Dropdown() override = default;

    //TODO ADD DRAWABLE

    void Enable() override;

    void Disable() override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

private:
    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Button> _button;

    ImVec2 _dropdownWindowSize;

    std::unique_ptr<RectDrawable> _recycleViewContainer;

    std::unique_ptr<RecycleView> _recycleView;

};