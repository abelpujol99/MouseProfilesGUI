#pragma once
#include <utility>

#include "Utilities/Concepts/DerivedFromBaseProcessDataStrategy.h"
#include "UI/Helpers/ISelectable.h"

#include "UI/Elements/Intermediate/Rectangle.h"
#include "../../Intermediate/Text.h"
#include "Managers/Gestures/SelectableManager.h"
#include "Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"

template<DerivedFromBaseProcessDataStrategy TProcessData>
class TextBox : public DrawableComponent, public ISelectable
{
public:

    TextBox(std::string placeHolder, bool isHidden = false);

    TextBox(const TextBox& other);

    ~TextBox() noexcept override;

    void SetRectangle(std::unique_ptr<Rectangle<DrawEmptyRectangle>> rectangle);

    void SetTextComponent(std::unique_ptr<Text> text);

    void SetIsHidden(bool isHidden) override;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    bool CanBeSelected() override;

    void OnSelect() override;

    void OnUnselect() override;

    void Subscribe() override;

    void Unsubscribe() override;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<TextBox<TProcessData>> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    std::string _placeHolder;

    std::unique_ptr<TProcessData> _processDataStrategy;

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> _rectangle;

    std::unique_ptr<Text> _text;
};

template<DerivedFromBaseProcessDataStrategy TProcessData>
TextBox<TProcessData>::TextBox(std::string placeHolder, bool isHidden) :
        DrawableComponent(isHidden), _placeHolder(std::move(placeHolder)), _processDataStrategy(std::make_unique<TProcessData>())
{}

template<DerivedFromBaseProcessDataStrategy TProcessData>
TextBox<TProcessData>::TextBox(const TextBox& other) :
    DrawableComponent(other.IsHidden()),
    _rectangle(other._rectangle->Clone()),
    _processDataStrategy(std::make_unique<TProcessData>()),
    _text(other._text->Clone())
{}

template<DerivedFromBaseProcessDataStrategy TProcessData>
TextBox<TProcessData>::~TextBox() noexcept
{
    TextBox<TProcessData>::Unsubscribe();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::SetRectangle(std::unique_ptr<Rectangle<DrawEmptyRectangle>> rectangle)
{
    _rectangle = std::move(rectangle);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::SetTextComponent(std::unique_ptr<Text> text)
{
    _text = std::move(text);

    _processDataStrategy->SetText(_text.get());
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    isHidden ? Disable() : Enable();

    _rectangle->SetIsHidden(isHidden);

    _text->SetIsHidden(isHidden);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    BaseDrawable::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _rectangle->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _text->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
ImVec2 TextBox<TProcessData>::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
ImVec2 TextBox<TProcessData>::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
bool TextBox<TProcessData>::CanBeSelected()
{
    return !IsHidden();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::OnSelect()
{
    _processDataStrategy->StartProcessData();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::OnUnselect()
{
    _processDataStrategy->StopProcessData();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::Subscribe()
{
    SelectableManager::GetInstance().AddSelectable(this);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::Unsubscribe()
{
    SelectableManager::GetInstance().RemoveSelectable(this);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::Enable()
{
    Subscribe();

    _rectangle->Enable();

    _text->Enable();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::Disable()
{
    Unsubscribe();

    _rectangle->Disable();

    _text->Disable();
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
std::unique_ptr<TextBox<TProcessData>> TextBox<TProcessData>::Clone() const
{
    return std::make_unique<TextBox<TProcessData>>(*this);
}

template<DerivedFromBaseProcessDataStrategy TProcessData>
void TextBox<TProcessData>::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}
