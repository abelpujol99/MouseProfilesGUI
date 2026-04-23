#pragma once
#include "Frontend/Utilities/Concepts/DerivedFromDrawableComponent.h"

#include <vector>
#include <memory>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Managers/Gestures/ScrollableManager.h"
#include "Frontend/UI/Elements/Base/RectDrawable.h"
#include "Frontend/UI/Helpers/IScrollable.h"
#include "Frontend/Utilities/Math.h"

#define SCROLL_MULTIPLIER 10

template<DerivedFromDrawableComponent TDrawableComponent>
class RecycleView : public DrawableComponent, public DrawableTransform, public IScrollable
{
public:

    RecycleView(Anchors&& rectDrawablesAnchors, ImVec2&& rectDrawablesPivot, ImVec2&& rectDrawablesSize,
        uint8_t bufferSlots, bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    void AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent);

    void RemoveDrawableComponent(int index);

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateRectDrawablesCount();

    void AddRectDrawables(int count);

    void RemoveRectDrawables(int count);

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    Anchors _rectDrawablesAnchors;

    ImVec2 _rectDrawablesPivot;

    ImVec2 _rectDrawablesSize;

    uint8_t _bufferSlots;

    std::vector<std::unique_ptr<RectDrawable>> _rectDrawables;

    std::vector<std::unique_ptr<TDrawableComponent>> _drawableComponents;

    float _currentScroll {0};

    float _maxScroll;

};

template<DerivedFromDrawableComponent TDrawableComponent>
RecycleView<TDrawableComponent>::RecycleView(Anchors&& rectDrawablesAnchors, ImVec2&& rectDrawablesPivot,
    ImVec2&& rectDrawablesSize, uint8_t bufferSlots, bool isHidden) :
        DrawableComponent(isHidden), _rectDrawablesAnchors(rectDrawablesAnchors), _rectDrawablesPivot(rectDrawablesPivot),
        _rectDrawablesSize(rectDrawablesSize), _bufferSlots(bufferSlots * 2)
{
    ScrollableManager::GetInstance().AddScrollable(this);
}

template<DerivedFromDrawableComponent TDrawableComponent>
RecycleView<TDrawableComponent>::~RecycleView() noexcept
{
    ScrollableManager::GetInstance().RemoveScrollable(this);
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::UpdateRectDrawablesCount()
{
    float parentSizeY {GetParentSize().y};

    int slots {static_cast<int>(parentSizeY / _rectDrawablesSize.y + 1 + _bufferSlots)};

    int difference {static_cast<int>(slots - _rectDrawables.size())};

    if (difference > 0)
    {
        _rectDrawables.reserve(_rectDrawables.size() + difference);
        AddRectDrawables(difference);
    }
    else if (difference < 0)
    {
        RemoveRectDrawables(difference);
        _rectDrawables.shrink_to_fit();
    }

    _maxScroll = -(_drawableComponents.size() * _rectDrawablesSize.y) + GetParentSize().y;

    if (_maxScroll < 0)
    {
        return;
    }

    _maxScroll = 0;
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::SetParentTransform(ImVec2* parentPositionPointer,
    ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer)
{
    DrawableComponent::SetParentTransform(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer);

    _position.reset(parentPositionPointer);

    _bottomRightPosition.reset(parentBottomRightPositionPointer);

    _size.reset(parentSizePointer);

    UpdateRectDrawablesCount();
}

template<DerivedFromDrawableComponent TDrawableComponent>
ImVec2 RecycleView<TDrawableComponent>::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

template<DerivedFromDrawableComponent TDrawableComponent>
ImVec2 RecycleView<TDrawableComponent>::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::AddRectDrawables(int count)
{
    for (int i {0}; i < count; ++i)
    {
        std::unique_ptr<RectDrawable> rectDrawable {DrawableFactory::CreateRectDrawable({{_rectDrawablesAnchors.min.x, _rectDrawablesAnchors.min.y},
            {_rectDrawablesAnchors.max.x, _rectDrawablesAnchors.max.y}}, {_rectDrawablesPivot.x, _rectDrawablesPivot.y},
            {0, _rectDrawables.size() * _rectDrawablesSize.y}, {_rectDrawablesSize.x, _rectDrawablesSize.y}, false)};

        std::string string {"Input Key"};

        string += static_cast<char>(_rectDrawables.size() + 48);

        rectDrawable->AddDrawableComponent(std::make_unique<Rectangle>(RectangleData{WHITE, 0, 1, false}, false));
        rectDrawable->AddDrawableComponent(std::make_unique<Text>(TextData{string, TextHorizontalAlignments::CENTER,
            TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, 20.f, RED}, false));

        rectDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

        _rectDrawables.push_back(std::move(rectDrawable));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::RemoveRectDrawables(int count)
{
    count = Utilities::Math::Absolute(count);

    for (int i {0}; i < count; ++i)
    {
        _rectDrawables.pop_back();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentPositionUpdated()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentBottomRightPositionUpdated()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentSizeUpdated()
{
    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }

    UpdateRectDrawablesCount();
    std::cout << "Count: " << _rectDrawables.size() << std::endl;
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    _drawableComponents.push_back(std::move(drawableComponent));
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::RemoveDrawableComponent(int index)
{
    _drawableComponents.erase(index);
}

template<DerivedFromDrawableComponent TDrawableComponent>
bool RecycleView<TDrawableComponent>::CanBeScrolled()
{
    return !_isHidden;
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::Scroll(float scrollValue)
{
    scrollValue *= SCROLL_MULTIPLIER;

    _currentScroll += scrollValue;

    if (_currentScroll > 0)
    {
        scrollValue -= _currentScroll;
        _currentScroll = 0;
    }
    else if (_currentScroll < _maxScroll)
    {
        scrollValue += _maxScroll - _currentScroll;
        _currentScroll = _maxScroll;
    }

    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        RectDrawable& rectDrawable {**it};

        ImVec2 currentRelativePosition {rectDrawable.GetRelativePosition()};

        currentRelativePosition.y += scrollValue;

        rectDrawable.SetRelativePosition(std::move(currentRelativePosition));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    auto itEnd {_rectDrawables.cend()};

    for (auto it {_rectDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}
