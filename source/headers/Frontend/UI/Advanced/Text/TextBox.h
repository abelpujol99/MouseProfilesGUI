#pragma once
#include "Frontend/UI/RectDrawable.h"
#include "Frontend/UI/ISelectable.h"

#include <memory>
#include <functional>

#include "Frontend/UI/Basic/Rectangle.h"
#include "Frontend/UI/Basic/Text.h"
#include "KeyUsings.h"

class TextBox : public RectDrawable, public ISelectable
{
public:

    TextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData, bool isHidden = false);

    ~TextBox() override = default;

    void UpdatePosition() override;

    bool CanBeSelected() override;

    const ImVec2& GetPosition() override;

    const ImVec2& GetBottomRightPosition() override;

    void OnSelect() override;

    void OnUnselect() override;

    void Draw(ImDrawList* drawList) override;


private:

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Text> _text;

    float _verticalPadding;

    float _horizontalPadding;

    std::weak_ptr<std::function<void(KeyChain)>> _onTypingWeakAction;
};