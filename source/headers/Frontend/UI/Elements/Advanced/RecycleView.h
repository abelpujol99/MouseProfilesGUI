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

    RecycleView(Anchors&& resizableDrawablesAnchors, ImVec2&& resizableDrawablesPivot, ImVec2&& resizableDrawablesSize,
        uint8_t bufferSlots, bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    void AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent);

    void RemoveDrawableComponent(uint8_t index);

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void MoveContainers(float scrollValue);

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateResizableDrawablesCount();

    void Reset();

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

    std::map<ResizableDrawable*, uint8_t> _resizableDrawableComponentIndex;

    std::map<uint8_t, ResizableDrawable*> _drawableComponentResizableIndex;

    float _currentScroll {0};

    float _maxScroll{0};
};

template<DerivedFromDrawableComponent TDrawableComponent>
RecycleView<TDrawableComponent>::RecycleView(Anchors&& resizableDrawablesAnchors, ImVec2&& resizableDrawablesPivot,
    ImVec2&& resizableDrawablesSize, uint8_t bufferSlots, bool isHidden) :
        DrawableComponent(isHidden), _resizeDrawablesAnchors(resizableDrawablesAnchors), _resizeDrawablesPivot(resizableDrawablesPivot),
        _resizableDrawablesSize(resizableDrawablesSize), _bufferSlots(bufferSlots * 2)
{
    ScrollableManager::GetInstance().AddScrollable(this);

    std::unique_ptr<ResizableDrawable> resizableDrawable {DrawableFactory::CreateResizableDrawable({{_resizeDrawablesAnchors.min.x, _resizeDrawablesAnchors.min.y},
            {_resizeDrawablesAnchors.max.x, _resizeDrawablesAnchors.max.y}}, {_resizeDrawablesPivot.x, _resizeDrawablesPivot.y},
            {0, 0}, {_resizableDrawablesSize.x, _resizableDrawablesSize.y}, false)};

    _resizableDrawableComponentIndex.emplace(resizableDrawable.get(), 0);

    _drawableComponentResizableIndex.emplace(0, resizableDrawable.get());

    resizableDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _resizableDrawables.push_back(std::move(resizableDrawable));
}

template<DerivedFromDrawableComponent TDrawableComponent>
RecycleView<TDrawableComponent>::~RecycleView() noexcept
{
    ScrollableManager::GetInstance().RemoveScrollable(this);
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::UpdateResizableDrawablesCount()
{
    float parentSizeY {GetParentSize().y};

    int slots {_bufferSlots};

    float availableSlots {std::ceil(parentSizeY / _resizableDrawablesSize.y)};

    if (!std::isnan(availableSlots))
    {
        slots += static_cast<int>(availableSlots);
    }

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

    Reset();

    if (_maxScroll <= 0)
    {
        return;
    }

    _maxScroll = 0;
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::Reset()
{
    MoveContainers(-_currentScroll);

    _currentScroll = 0;

    uint8_t resizableDrawablesCount {static_cast<uint8_t>(_resizableDrawables.size())};

    if (_resizableDrawableComponentIndex.at(_resizableDrawables.at(0).get()) == 0)
    {
        return;
    }

    for (uint8_t i {0}; i < resizableDrawablesCount; ++i)
    {
        ResizableDrawable* resizableDrawable {_resizableDrawables.at(i).get()};

        uint8_t& index {_resizableDrawableComponentIndex.at(resizableDrawable)};

        if (index >= _drawableComponents.size())
        {
            continue;
        }

        resizableDrawable->RemoveDrawableComponent(_drawableComponents.at(index).get());

        index = i;

        resizableDrawable->AddDrawableComponent(_drawableComponents.at(index).get());

        _drawableComponentResizableIndex.at(index) = _resizableDrawables.at(index).get();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::SetParentTransform(ImVec2* parentPositionPointer,
    ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer)
{
    DrawableComponent::SetParentTransform(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer);

    UpdateResizableDrawablesCount();
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

        _drawableComponentResizableIndex.emplace(_resizableDrawables.size(), resizableDrawable.get());

        resizableDrawable->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

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

    UpdateResizableDrawablesCount();
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

    UpdateResizableDrawablesCount();
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

    UpdateResizableDrawablesCount();
    std::cout << "Count: " << _resizableDrawables.size() << std::endl;
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    uint8_t drawableComponentsSize {static_cast<uint8_t>(_drawableComponents.size())};

    _drawableComponentResizableIndex.emplace(drawableComponentsSize, nullptr);

    auto itEnd {_resizableDrawableComponentIndex.cend()};

    for (auto it{_resizableDrawableComponentIndex.begin()}; it != itEnd; ++it)
    {
        auto& pair {*it};

        if (pair.second != drawableComponentsSize)
        {
            continue;
        }

        _drawableComponentResizableIndex.at(drawableComponentsSize) = pair.first;

        pair.first->AddDrawableComponent(drawableComponent.get());

        break;
    }

    _drawableComponents.push_back(std::move(drawableComponent));
}

template<DerivedFromDrawableComponent TDrawableComponent>
void RecycleView<TDrawableComponent>::RemoveDrawableComponent(uint8_t index)
{
    uint8_t auxIndex = index;

    ResizableDrawable* resizableDrawable {nullptr};

    do{
        resizableDrawable = _drawableComponentResizableIndex.at(auxIndex);

        resizableDrawable->RemoveDrawableComponent(_drawableComponents.at(auxIndex));

        if (_drawableComponents.size() == ++auxIndex)
        {
            break;
        }

        resizableDrawable->AddDrawableComponent(_drawableComponents.at(auxIndex));

    }while(true);

    _drawableComponents.erase(index);

    _drawableComponentResizableIndex.erase(_drawableComponentResizableIndex.cend());
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

        uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferSlots / 2)};

        float upperLimit {-_resizableDrawablesSize.y * halfBufferSlots};

        float lowerLimit {_size->y + _resizableDrawablesSize.y * (halfBufferSlots - 1)};

        ImVec2 currentRelativePosition {resizeDrawable->GetRelativePosition()};

        float predictedRelativePosition {currentRelativePosition.y + scrollValue};

        float jumpDistance {_resizableDrawablesSize.y * _resizableDrawables.size()};

        if (predictedRelativePosition < upperLimit)
        {
            uint8_t& index {_resizableDrawableComponentIndex.at(resizeDrawable)};

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
            uint8_t& index {_resizableDrawableComponentIndex.at(resizeDrawable)};

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
