#pragma once
#include "Utilities/Concepts/DerivedFromBaseDrawable.h"

#include <vector>
#include <memory>
#include <map>
#include <cmath>

#include "Factory/DrawableFactory.h"
#include "Managers/Gestures/ScrollableManager.h"
#include "UI/Helpers/IScrollable.h"
#include "Utilities/Math.h"
#include "ColorDefines.h"
#include "RecycleViewActions.h"

#define SCROLL_MULTIPLIER 10

template<DerivedFromBaseDrawable TBaseDrawable>
class RecycleView : public DrawableComponent, public DrawableTransform, public IScrollable
{
public:

    RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
        std::function<void(RectDrawable*)>&& addDefault, std::function<void()> removeLastView,
        RecycleViewActions&& devicesPresenterActions, bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetIsHidden(bool isHidden) override;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void SetCurrentScroll(float currentScroll);

    void SetIsFirstItemPresent(bool isFirstItemPresent);

    void SetIsLastItemPresent(bool isLastItemPresent);

    void Enable() override;

    void Disable() override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    void UpdateResizableDrawablesCount();

    void CreateRow(ImVec2&& lastRowPosition);

    void DeleteLastRow();

    void HandleMove();

    uint8_t _viewsPerRow;

    ImVec2 _marginBetweenViews;

    ImVec2 _rowsSize;

    uint8_t _bufferRows;

    float _widthPerView;

    std::vector<std::unique_ptr<RectDrawable>> _rows;

    std::map<RectDrawable*, std::vector<RectDrawable*>> _views;

    float _currentScroll {0};

    bool _isFirstItemPresent;

    bool _isLastItemPresent;

    std::function<void(RectDrawable*)> _addDefault;

    std::function<void()> _removeLastViewComponents;

    RecycleViewActions _devicesPresenterActions;
};

template<DerivedFromBaseDrawable TBaseDrawable>
RecycleView<TBaseDrawable>::RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize,
    uint8_t bufferRows, std::function<void(RectDrawable*)>&& addDefault, std::function<void()> removeLastView,
    RecycleViewActions&& devicesPresenterActions, bool isHidden) :
        DrawableComponent(isHidden), _viewsPerRow(viewsPerRow), _marginBetweenViews({marginBetweenViews.x / _viewsPerRow, marginBetweenViews.y}),
        _rowsSize(std::move(rowsSize)), _bufferRows(bufferRows * 2), _widthPerView(1 / static_cast<float>(_viewsPerRow)),
        _addDefault(std::move(addDefault)), _removeLastViewComponents(std::move(removeLastView)), _devicesPresenterActions(std::move(devicesPresenterActions))
{
    CreateRow({0, -(_rowsSize.y + _marginBetweenViews.y)});

    for (uint8_t i {1}; i < _bufferRows; ++i)
    {
        CreateRow(_rows.back()->GetRelativePosition());
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
RecycleView<TBaseDrawable>::~RecycleView() noexcept
{
    Disable();
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    for (auto&& row : _rows)
    {
        row->SetIsHidden(isHidden);
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::SetParentState(ImVec2* parentPositionPointer,
    ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    UpdateResizableDrawablesCount();
}

template<DerivedFromBaseDrawable TBaseDrawable>
ImVec2 RecycleView<TBaseDrawable>::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

template<DerivedFromBaseDrawable TBaseDrawable>
ImVec2 RecycleView<TBaseDrawable>::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    _devicesPresenterActions.ExecuteOnUpdateSize(_size->y);

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }

    UpdateResizableDrawablesCount();
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::UpdateResizableDrawablesCount()
{
    float parentSizeY {GetParentSize().y};

    int slots {_bufferRows};

    float availableSlots {std::ceil(parentSizeY / _rowsSize.y + _marginBetweenViews.y * 2)};

    if (!std::isnan(availableSlots))
    {
        slots += static_cast<int>(availableSlots);
    }

    int difference {static_cast<int>(slots - _rows.size())};

    if (difference > 0)
    {
        _rows.reserve(_rows.size() + difference);

        for (int i {0}; i < difference; ++i)
        {
            CreateRow(_rows.back()->GetRelativePosition());
        }
    }
    else if (difference < 0)
    {
        difference = Utilities::Math::Absolute(difference);

        for (int i {0}; i < difference; ++i)
        {
            DeleteLastRow();
        }
        _rows.shrink_to_fit();
    }

    _devicesPresenterActions.ExecuteOnUpdateRowsCount(_rows.size() * _viewsPerRow);
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::CreateRow(ImVec2&& lastRowPosition)
{
    std::unique_ptr<RectDrawable> row {DrawableFactory::CreateRectDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {lastRowPosition.x, lastRowPosition.y + _rowsSize.y}, {_rowsSize.x, _rowsSize.y}, false)};

    _views.emplace(row.get(), std::vector<RectDrawable*>{});

    for (uint8_t i {0}; i < _viewsPerRow; ++i)
    {
        std::unique_ptr<RectDrawable> view {DrawableFactory::CreateRectDrawable(
            Anchors{{i * _widthPerView + _marginBetweenViews.x, _marginBetweenViews.y},
                {(i + 1) * _widthPerView - _marginBetweenViews.x, 1 - _marginBetweenViews.y}}, PIVOT_MIDDLE_CENTER,
                {0, 0}, {0, 0}, false)};

        _addDefault(view.get());

        _views.at(row.get()).push_back(view.get());

        row->AddRectDrawable(std::move(view));
    }

    row->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rows.push_back(std::move(row));
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::DeleteLastRow()
{
    _views.erase(_rows.back().get());

    _rows.pop_back();

    for (uint8_t i{0}; i < _viewsPerRow; ++i)
    {
        _removeLastViewComponents();
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::Enable()
{
    ScrollableManager::GetInstance().AddScrollable(this);

    for (auto&& row : _rows)
    {
        row->Enable();
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::Disable()
{
    ScrollableManager::GetInstance().RemoveScrollable(this);

    for (auto&& row : _rows)
    {
        row->Disable();
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
bool RecycleView<TBaseDrawable>::CanBeScrolled()
{
    return !IsHidden();
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::Scroll(float scrollValue)
{
    scrollValue *= SCROLL_MULTIPLIER;

    _devicesPresenterActions.ExecuteOnScroll(-scrollValue);
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::SetCurrentScroll(float currentScroll)
{
    _currentScroll = currentScroll;

    HandleMove();
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::SetIsFirstItemPresent(bool isFirstItemPresent)
{
    _isFirstItemPresent = isFirstItemPresent;
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::SetIsLastItemPresent(bool isLastItemPresent)
{
    _isLastItemPresent = isLastItemPresent;
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::HandleMove()
{
    const uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferRows / 2)};

    const float upperBound {-_rowsSize.y * halfBufferSlots};

    const float lowerBound {_size->y + _rowsSize.y * halfBufferSlots};

    const size_t rowsCount {_rows.size()};

    const float jumpDistance {_rowsSize.y * rowsCount};

    for (size_t i{0}; i < rowsCount; ++i)
    {
        RectDrawable* row {_rows[i].get()};

        float newYPosition {i * _rowsSize.y - _currentScroll};

        if (newYPosition > lowerBound && _isFirstItemPresent)
        {
            row->SetRelativePosition({0, newYPosition});
            continue;
        }

        newYPosition -= upperBound;

        newYPosition = std::fmod(newYPosition, jumpDistance);

        if (newYPosition < 0)
        {
            newYPosition += jumpDistance;
        }

        newYPosition += upperBound;

        row->SetRelativePosition({0, newYPosition});
    }
}

template<DerivedFromBaseDrawable TBaseDrawable>
void RecycleView<TBaseDrawable>::Draw(ImDrawList* drawList)
{
    if (IsHidden())
    {
        return;
    }

    for (auto&& row : _rows)
    {
        row->Draw(drawList);
    }
}