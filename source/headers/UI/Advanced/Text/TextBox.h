#pragma once
#include "UI/RectDrawable.h"
#include "UI/ISelectable.h"

#include <memory>
#include <functional>

#include "KeyUsings.h"

class Text;
class Rectangle;
class RectangleData;
class TextData;

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