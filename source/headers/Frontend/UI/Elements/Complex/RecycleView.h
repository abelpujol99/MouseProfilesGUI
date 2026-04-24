#pragma once
#include "Frontend/Utilities/Concepts/DerivedFromDrawableComponent.h"

#include <vector>
#include <memory>
#include <map>
#include <cmath>

#include "Frontend/Factory/DrawableFactory.h"
#include "Frontend/Managers/Gestures/ScrollableManager.h"
#include "Frontend/UI/Helpers/IScrollable.h"
#include "Frontend/Utilities/Math.h"

#define NO_INDEX -1
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

    void MoveContainers(float scrollValue);

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateRectDrawablesCount();

    void AddResizableDrawables(int count);

    void RemoveRectDrawables(int count);

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    Anchors _resizeDrawablesAnchors;

    ImVec2 _resizeDrawablesPivot;

    ImVec2 _resizableDrawablesSize;

    uint8_t _bufferSlots;

    std::vector<std::unique_ptr<ResizableDrawable>> _resizableDrawables;

    std::vector<std::unique_ptr<TDrawableComponent>> _drawableComponents;

    std::map<ResizableDrawable*, int8_t> _resizableDrawableComponentIndex;

    float _currentScroll {0};

    float _maxScroll{0};
};

template<DerivedFromDrawableComponent TDrawableComponent>
RecycleView<TDrawableComponent>::RecycleView(Anchors&& rectDrawablesAnchors, ImVec2&& rectDrawablesPivot,
    ImVec2&& rectDrawablesSize, uint8_t bufferSlots, bool isHidden) :
        DrawableComponent(isHidden), _resizeDrawablesAnchors(rectDrawablesAnchors), _resizeDrawablesPivot(rectDrawablesPivot),
        _resizableDrawablesSize(rectDrawablesSize), _bufferSlots(bufferSlots * 2)
{
    ScrollableManager::GetInstance().AddScrollable(this);

    std::unique_ptr<ResizableDrawable> resizableDrawable {DrawableFactory::CreateResizableDrawable({{_resizeDrawablesAnchors.min.x, _resizeDrawablesAnchors.min.y},
            {_resizeDrawablesAnchors.max.x, _resizeDrawablesAnchors.max.y}}, {_resizeDrawablesPivot.x, _resizeDrawablesPivot.y},
            {0, 0}, {_resizableDrawablesSize.x, _resizableDrawablesSize.y}, false)};

    _resizableDrawableComponentIndex.emplace(resizableDrawable.get(), 0);

    resizableDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    std::unique_ptr<Button> button {DrawableFactory::CreateButton(RectangleData{RED, NO_ROUNDING, THIN_BORDER, false}, TextData{"Input Key 0", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, RED}, []() {
        std::cout << "Input Key 0" << std::endl;
    }, false)};

    AddDrawableComponent(std::move(button));

    std::unique_ptr<Button> button1 {DrawableFactory::CreateButton(RectangleData{RED, NO_ROUNDING, THIN_BORDER, false}, TextData{"Input Key 1", TextHorizontalAlignments::CENTER,
        TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, RED}, []() {
        std::cout << "Input Key 1" << std::endl;
    }, false)};

    AddDrawableComponent(std::move(button1));

    resizableDrawable->AddDrawableComponent(_drawableComponents.at(_resizableDrawableComponentIndex.at(resizableDrawable.get())).get());

    _resizableDrawables.push_back(std::move(resizableDrawable));
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

    int slots {static_cast<int>(std::ceil(parentSizeY / _resizableDrawablesSize.y) + _bufferSlots)};

    int difference {static_cast<int>(slots - _resizableDrawables.size())};

    if (difference > 0)
    {
        _resizableDrawables.reserve(_resizableDrawables.size() + difference);
        AddResizableDrawables(difference);
    }
    else if (difference < 0)
    {
        RemoveRectDrawables(difference);
        _resizableDrawables.shrink_to_fit();
    }

    _maxScroll = -(_drawableComponents.size() * _resizableDrawablesSize.y) + GetParentSize().y;

    if (_maxScroll <= 0)
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
void RecycleView<TDrawableComponent>::AddResizableDrawables(int count)
{
    for (int i {0}; i < count; ++i)
    {
        ImVec2 lastResizableDrawablePosition {_resizableDrawables.back()->GetRelativePosition()};

        std::unique_ptr<ResizableDrawable> resizableDrawable {DrawableFactory::CreateResizableDrawable({{_resizeDrawablesAnchors.min.x, _resizeDrawablesAnchors.min.y},
            {_resizeDrawablesAnchors.max.x, _resizeDrawablesAnchors.max.y}}, {_resizeDrawablesPivot.x, _resizeDrawablesPivot.y},
            {lastResizableDrawablePosition.x, lastResizableDrawablePosition.y + _resizableDrawablesSize.y},
            {_resizableDrawablesSize.x, _resizableDrawablesSize.y}, false)};

        _resizableDrawableComponentIndex.emplace(resizableDrawable.get(), _resizableDrawables.size());

        resizableDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

        for (int i {0}; i < 5; ++i)
        {
            std::string string {"Input Key "};

            string += std::to_string(_drawableComponents.size());

            std::unique_ptr<Button> button {DrawableFactory::CreateButton(RectangleData{RED, NO_ROUNDING, THIN_BORDER, false}, TextData{string, TextHorizontalAlignments::CENTER,
                TextVerticalAlignments::MIDDLE, FontFamilyTypes::ROBOTO_REGULAR, TITLE_SIZE, RED}, [string]() {
                std::cout << string << std::endl;
            }, false)};

            _drawableComponents.push_back(std::move(button));
        }

        resizableDrawable->AddDrawableComponent(_drawableComponents.at(_resizableDrawableComponentIndex.at(resizableDrawable.get())).get());

        _resizableDrawables.push_back(std::move(resizableDrawable));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::RemoveRectDrawables(int count)
{
    count = Utilities::Math::Absolute(count);

    for (int i {0}; i < count; ++i)
    {
        _resizableDrawables.pop_back();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->UpdateAttributes();
    }

    UpdateRectDrawablesCount();
    std::cout << "Count: " << _resizableDrawables.size() << std::endl;
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

    float newScrollValue {_currentScroll + scrollValue};

    if (newScrollValue > 0 || newScrollValue < _maxScroll)
    {
        return;
    }

    _currentScroll = newScrollValue;

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

    MoveContainers(scrollValue);
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::MoveContainers(float scrollValue)
{
    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        ResizableDrawable* resizeDrawable {it->get()};

        ImVec2 currentRelativePosition {resizeDrawable->GetRelativePosition()};

        float predictedRelativePosition {currentRelativePosition.y + scrollValue};

        uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferSlots / 2)};

        float upperLimit {-_resizableDrawablesSize.y * halfBufferSlots};

        float lowerLimit {_size->y + _resizableDrawablesSize.y * (halfBufferSlots - 1)};

        float jumpDistance {_resizableDrawablesSize.y * _resizableDrawables.size()};

        if (predictedRelativePosition < upperLimit)
        {
            int8_t& index {_resizableDrawableComponentIndex.at(resizeDrawable)};

            int nexIndex {index + static_cast<int>(_resizableDrawables.size())};

            if (nexIndex < _drawableComponents.size())
            {
                predictedRelativePosition += jumpDistance;

                if (index > NO_INDEX)
                {
                    resizeDrawable->RemoveDrawableComponent(_drawableComponents.at(index).get());
                }

                index = nexIndex;

                if (index > NO_INDEX)
                {
                    resizeDrawable->AddDrawableComponent(_drawableComponents.at(index).get());
                }
            }
        }
        else if (predictedRelativePosition > lowerLimit)
        {
            int8_t& index {_resizableDrawableComponentIndex.at(resizeDrawable)};

            int newIndex {index - static_cast<int>(_resizableDrawables.size())};

            if (newIndex >= 0)
            {
                predictedRelativePosition -= jumpDistance;

                if (index > NO_INDEX)
                {
                    resizeDrawable->RemoveDrawableComponent(_drawableComponents.at(index).get());
                }

                index = newIndex;

                if (index > NO_INDEX)
                {
                    resizeDrawable->AddDrawableComponent(_drawableComponents.at(index).get());
                }
            }
        }

        currentRelativePosition.y = predictedRelativePosition;

        resizeDrawable->SetRelativePosition(std::move(currentRelativePosition));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    auto itEnd {_resizableDrawables.cend()};

    for (auto it {_resizableDrawables.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}
