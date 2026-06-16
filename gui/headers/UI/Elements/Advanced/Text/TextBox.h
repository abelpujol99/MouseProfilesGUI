#pragma once
#include "Utilities/Concepts/DerivedFromBaseProcessDataStrategy.h"
#include "UI/Helpers/ISelectable.h"

#include "UI/Elements/Intermediate/Rectangle.h"
#include "UI/Elements/Intermediate/Text.h"
#include "Managers/Gestures/SelectableManager.h"

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
class TextBox : public DrawableComponent, public ISelectable
{
public:

    TextBox(bool isHidden = false);

    TextBox(const TextBox& other);

    ~TextBox() noexcept override;

    void SetRectangle(std::unique_ptr<Rectangle> rectangle);

    void SetText(std::unique_ptr<Text> text);

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

    [[nodiscard]] std::unique_ptr<TextBox<T, TProcessData>> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<TProcessData> _processDataStrategy;

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<Text> _text;
};

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
TextBox<T, TProcessData>::TextBox(bool isHidden) :
        DrawableComponent(isHidden), _processDataStrategy(std::make_unique<TProcessData>())
{}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
TextBox<T, TProcessData>::TextBox(const TextBox& other) :
    DrawableComponent(other.IsHidden()),
    _rectangle(other._rectangle->Clone()),
    _processDataStrategy(std::make_unique<TProcessData>()),
    _text(other._text->Clone())
{}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
TextBox<T, TProcessData>::~TextBox() noexcept
{
    TextBox<T, TProcessData>::Unsubscribe();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetRectangle(std::unique_ptr<Rectangle> rectangle)
{
    _rectangle = std::move(rectangle);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetText(std::unique_ptr<Text> text)
{
    _text = std::move(text);

    _processDataStrategy->SetText(_text.get());
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    isHidden ? Disable() : Enable();

    _rectangle->SetIsHidden(isHidden);

    _text->SetIsHidden(isHidden);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    BaseDrawable::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _rectangle->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    _text->SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
ImVec2 TextBox<T, TProcessData>::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
ImVec2 TextBox<T, TProcessData>::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
bool TextBox<T, TProcessData>::CanBeSelected()
{
    return !IsHidden();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::OnSelect()
{
    _processDataStrategy->StartProcessData();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::OnUnselect()
{
    _processDataStrategy->StopProcessData();
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Subscribe()
{
    SelectableManager::GetInstance().AddSelectable(this);
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Unsubscribe()
{
    SelectableManager::GetInstance().RemoveSelectable(this);
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Enable()
{
    Subscribe();

    _rectangle->Enable();

    _text->Enable();
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Disable()
{
    Unsubscribe();

    _rectangle->Disable();

    _text->Disable();
}

template <typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
std::unique_ptr<TextBox<T, TProcessData>> TextBox<T, TProcessData>::Clone() const
{
    return std::make_unique<TextBox<T, TProcessData>>(*this);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}
