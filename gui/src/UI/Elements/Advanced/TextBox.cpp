#include "UI/Elements/Advanced/TextBox.h"

#include "KeyDefines.h"
#include "TextDefines.h"
#include "Factory/DrawableFactory.h"
#include "Factory/Font/FontFactory.h"
#include "Managers/Input/InputManager.h"

TextBox::TextBox(std::string placeHolder, bool isHidden) : DrawableComponent(isHidden), _placeHolder(std::move(placeHolder))
{
    MapSubscriptions();

    CreateTextContainer();
}

TextBox::TextBox(const TextBox& other) :
    DrawableComponent(true),
    _pointerPosition(0),
    _placeHolder(other._placeHolder),
    _rectangle(other._rectangle->Clone()),
    _selectionRectangle(other._selectionRectangle->Clone()),
    _textContainer(other._textContainer->Clone()),
    _text(other._text->Clone())
{
    MapSubscriptions();

    _textContainer->AddDrawableComponent(_text.get());

    CreateTextContainer();
}

void TextBox::MapSubscriptions()
{
    _charPressedActions.emplace(BACKSPACE, [&]()
    {
        if (_selectionCount > 0)
        {
            _charPressedActions.at(DELETE)();
            return;
        }

        const int firstIndex {_pointerPosition - _selectionCount != 0 ? _selectionCount : 1};

        {
            const std::string message {_text->GetText()};

            const float textReferenceWidth {FontFactory::GetInstance().GetTextReferenceWidth(_text->GetFontFamily(), message.substr(firstIndex, _pointerPosition))};

            const float fontSize {_text->GetFontSize()};

            _textWidth -= static_cast<uint16_t>(textReferenceWidth * (fontSize / BASE_FONT_SIZE));

            _pointerPosition = firstIndex;
        }

        _text->EraseFromIndexToIndex(firstIndex, _pointerPosition);
    });
    _charPressedActions.emplace(DELETE, [&]()
    {
        if (_selectionCount < 0)
        {
            _charPressedActions.at(BACKSPACE)();
            return;
        }

        const int lastIndex {_pointerPosition + _selectionCount != 0 ? _selectionCount : 1};

        {
            const std::string message {_text->GetText()};

            const float textReferenceWidth {FontFactory::GetInstance().GetTextReferenceWidth(_text->GetFontFamily(), message.substr(_pointerPosition, lastIndex))};

            const float fontSize {_text->GetFontSize()};

            _textWidth -= static_cast<uint16_t>(textReferenceWidth * (fontSize / BASE_FONT_SIZE));
        }

        _text->EraseFromIndexToIndex(_pointerPosition, lastIndex);
    });
    _charPressedActions.emplace(LEFT_ARROW, [&](){_pointerPosition--;});
    _charPressedActions.emplace(RIGHT_ARROW, [&](){_pointerPosition++;});
    /*_charPressedActions.emplace(HOME, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(END, [&](){_text->EraseLastChar();});*/
    _charPressedActions.emplace(SPACE_BAR, [&](){_text->AddText(" ", _pointerPosition);});
}

void TextBox::CreateTextContainer()
{
    _textContainer = DrawableFactory::CreateRectDrawable(RectDrawableData{ANCHORS_FULL_STRETCH, PIVOT_MIDDLE_CENTER,
        {0, 0}, {0, 0}}, *_mustBeHidden);

    _textContainer->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());
}

TextBox::~TextBox() noexcept
{
    TextBox::Unsubscribe();
}

void TextBox::SetRectangle(std::unique_ptr<Rectangle<DrawEmptyRectangle>>&& rectangle)
{
    _rectangle = std::move(rectangle);
}

void TextBox::SetTextComponent(std::unique_ptr<Text>&& text)
{
    _textContainer->RemoveDrawableComponent(_text.get());

    _text = std::move(text);

    _textContainer->AddDrawableComponent(_text.get());
}

void TextBox::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    isHidden ? Disable() : Enable();

    _rectangle->SetIsHidden(isHidden);

    _textContainer->SetIsHidden(isHidden);
}

void TextBox::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _rectangle->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _textContainer->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);
}

ImVec2 TextBox::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

ImVec2 TextBox::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

bool TextBox::CanBeSelected()
{
    return !IsHidden();
}

void TextBox::OnSelect()
{
    _onTypeCharAction = InputManager::GetInstance().SubscribeToCharPressed([&](std::string character)
    {
        if (_charPressedActions.contains(character))
        {
            _charPressedActions.at(character)();
            return;
        }

        const float textReferenceWidth {FontFactory::GetInstance().GetTextReferenceWidth(_text->GetFontFamily(), character)};

        const float fontSize {_text->GetFontSize()};

        _textWidth += static_cast<uint16_t>(textReferenceWidth * (fontSize / BASE_FONT_SIZE));

        _text->AddText(character, _pointerPosition++);
    });
}

void TextBox::OnUnselect()
{
    InputManager::GetInstance().UnsubscribeToCharPressed(std::move(_onTypeCharAction));
}

void TextBox::Subscribe()
{
    SelectableManager::GetInstance().AddSelectable(this);
}

void TextBox::Unsubscribe()
{
    SelectableManager::GetInstance().RemoveSelectable(this);
}

void TextBox::Enable()
{
    Subscribe();

    _rectangle->Enable();

    _textContainer->Enable();
}

void TextBox::Disable()
{
    Unsubscribe();

    _rectangle->Disable();

    _textContainer->Disable();
}

std::unique_ptr<TextBox> TextBox::Clone() const
{
    return std::make_unique<TextBox>(*this);
}

void TextBox::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _rectangle->Draw(drawList);

    _textContainer->Draw(drawList);
}

void TextBox::EraseSelection(size_t first, size_t last) const
{
    _text->EraseFromIndexToIndex(first, last);
}

void TextBox::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    _textContainer->UpdateAttributes();
}

void TextBox::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    _textContainer->UpdateAttributes();
}

void TextBox::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    _textContainer->UpdateAttributes();
}
