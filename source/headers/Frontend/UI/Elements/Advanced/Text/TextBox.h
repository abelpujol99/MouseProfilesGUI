#pragma once
#include "Frontend/Utilities/Concepts/DerivedFromBaseProcessDataStrategy.h"
#include "Frontend/UI/ISelectable.h"

#include "Frontend/UI/Elements/Intermediate/Rectangle.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"
#include "Frontend/Managers/Input/SelectableManager.h"

#include "Frontend/KeyUsings.h"

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
class TextBox : public DrawableComponent, public ISelectable
{
public:

    TextBox(bool isHidden = false);

    ~TextBox() override = default;

    void SetRectangle(std::unique_ptr<Rectangle> rectangle);

    void SetText(std::unique_ptr<Text> text);

    void SetParentTransform(ImVec2* parentPosition, ImVec2* parentSize) override;

    void SetBottomRightPositionPointer(ImVec2 *bottomRightPositionPointer) override;

    bool CanBeSelected() override;

    void OnSelect() override;

    void OnUnselect() override;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<Rectangle> _rectangle;

    std::unique_ptr<TProcessData> _processDataStrategy;

    std::unique_ptr<Text> _text;

    std::weak_ptr<std::function<void(Key)>> _onTypingWeakAction;
};

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
TextBox<T, TProcessData>::TextBox(bool isHidden) :
        DrawableComponent(isHidden), _processDataStrategy(std::make_unique<TProcessData>())
{
    SelectableManager::GetInstance().AddSelectable(this);
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

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetParentTransform(ImVec2* parentPosition, ImVec2* parentSize)
{
    DrawableComponent::SetParentTransform(parentPosition, parentSize);

    _rectangle->SetParentTransform(parentPosition, parentSize);

    _text->SetParentTransform(parentPosition, parentSize);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetBottomRightPositionPointer(ImVec2* bottomRightPositionPointer)
{
    DrawableComponent::SetBottomRightPositionPointer(bottomRightPositionPointer);

    _rectangle->SetBottomRightPositionPointer(bottomRightPositionPointer);

    _text->SetBottomRightPositionPointer(bottomRightPositionPointer);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
bool TextBox<T, TProcessData>::CanBeSelected()
{
    return !_isHidden;
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

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    _rectangle->Draw(drawList);

    _text->Draw(drawList);
}