#include "UI/Text/TextBox.h"

#include "Factories/DrawableFactory.h"
#include "Factories/Font/FontFactory.h"
#include "Managers/Input/InputManager.h"
#include "Managers/Input/SelectableManager.h"
#include "UI/Text/Text.h"

TextBox::TextBox(const ImVec2& parentPosition, float positionX, float positionY, int width, int height,
    float verticalPadding, float horizontalPadding, ImColor color, float rounding, float thickness,
    TextHorizontalAlignments textHorizontalAlignment, TextVerticalAlignments textVerticalAlignment, FontFamilyTypes textFont,
    float fontSize, ImColor textColor, bool isHidden) : RectDrawable(parentPosition, positionX, positionY, isHidden),
    _color(color), _verticalPadding(verticalPadding), _horizontalPadding(horizontalPadding), _rounding(rounding), _thickness(thickness),
    _text(DrawableFactory::CreateText(GetFinalPosition(), 0, 0, "", textHorizontalAlignment, textVerticalAlignment,
    FontFactory::GetInstance().GetFontFamily(textFont), fontSize, textColor))
{
    SetSize(width, height);

    SelectableManager::GetInstance().AddSelectable(this);
}

void TextBox::UpdatePosition()
{
    RectDrawable::UpdatePosition();

    _text->UpdatePosition();
}

void TextBox::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _text->Draw(drawList);

    const ImVec2& finalPosition {GetFinalPosition()};

    drawList->AddRect(finalPosition, _bottomRightPosition, _color, _rounding, 0, _thickness);
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