#pragma once
#include "Frontend/UI/RectDrawable.h"
#include "Frontend/UI/ISelectable.h"

#include <memory>
#include <functional>

#include "Frontend/UI/Basic/Rectangle.h"
#include "Frontend/UI/Basic/Text.h"
#include "Frontend/KeyUsings.h"
#include "Frontend/Managers/Input/SelectableManager.h"

#include "Utilities/Concepts/DerivedFromBaseProcessDataStrategy.h"

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
class TextBox : public RectDrawable, public ISelectable
{
public:

    TextBox(DrawablePosition&& drawablePosition, bool isHidden = false);

    ~TextBox() override = default;

    void SetRectangle(std::unique_ptr<Rectangle> rectangle);

    void SetText(std::unique_ptr<Text> text);

    void UpdatePosition() override;

    bool CanBeSelected() override;

    [[nodiscard]] ImVec2* GetPosition() const override;

    const ImVec2& GetBottomRightPosition() override;

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
TextBox<T, TProcessData>::TextBox(DrawablePosition&& drawablePosition, bool isHidden) :
        RectDrawable(std::move(drawablePosition), isHidden), _processDataStrategy(std::make_unique<TProcessData>())
{
    SelectableManager::GetInstance().AddSelectable(this);
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetRectangle(std::unique_ptr<Rectangle> rectangle)
{
    _rectangle = std::move(rectangle);

    SetSize(_rectangle->GetSize());

    _rectangle->SetParentPosition(*GetPosition());
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::SetText(std::unique_ptr<Text> text)
{
    _text = std::move(text);

    _processDataStrategy->SetText(_text.get());

    _text->SetParentPosition(*GetPosition());
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
void TextBox<T, TProcessData>::UpdatePosition()
{
    RectDrawable::UpdatePosition();

    _rectangle->UpdatePosition();

    _text->UpdatePosition();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
bool TextBox<T, TProcessData>::CanBeSelected()
{
    return !_isHidden;
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
ImVec2* TextBox<T, TProcessData>::GetPosition() const
{
    return Drawable::GetPosition();
}

template<typename T, DerivedFromBaseProcessDataStrategy<T> TProcessData>
const ImVec2& TextBox<T, TProcessData>::GetBottomRightPosition()
{
    return _bottomRightPosition;
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