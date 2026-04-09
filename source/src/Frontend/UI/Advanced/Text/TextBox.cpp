#include "Frontend/UI/Advanced/Text/TextBox.h"

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Managers/Input/InputManager.h"
#include "Frontend/Managers/Input/SelectableManager.h"
#include "Frontend/UI/Structs/DrawablePosition.h"
#include "Frontend/UI/Structs/RectangleData.h"
#include "Frontend/UI/Structs/TextData.h"

TextBox::TextBox(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData, bool isHidden) :
        RectDrawable(std::move(drawablePosition), isHidden),
        _rectangle(DrawableFactory::CreateRectangle(DrawablePosition{_finalPosition, 0, 0},
        RectangleData{rectangleData.size, rectangleData.color, rectangleData.rounding, rectangleData.thickness, rectangleData.isFilled})),
        _text(DrawableFactory::CreateText(DrawablePosition{_finalPosition, 0, 0},
        TextData{textData.text, textData.horizontalAlignment, textData.verticalAlignment, textData.fontFamily, textData.fontSize, textData.color}))
{
    SetSize(rectangleData.size);

    SelectableManager::GetInstance().AddSelectable(this);
}

void TextBox::UpdatePosition()
{
    RectDrawable::UpdatePosition();

    _rectangle->UpdatePosition();

    _text->UpdatePosition();
}

bool TextBox::CanBeSelected()
{
    return !_isHidden;
}

const ImVec2& TextBox::GetPosition()
{
    return GetFinalPosition();
}

const ImVec2& TextBox::GetBottomRightPosition()
{
    return _bottomRightPosition;
}

void TextBox::OnSelect()
{
    _onTypingWeakAction = InputManager::GetInstance().SubscribeToCurrentKeyChainObserver([&](KeyChain keyChain) {
        _text->AddText(std::string(ImGui::GetKeyName(keyChain)));
    });
}

void TextBox::OnUnselect()
{
    InputManager::GetInstance().UnsubscribeToCurrentKeyChainObserver(_onTypingWeakAction);
}

void TextBox::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}