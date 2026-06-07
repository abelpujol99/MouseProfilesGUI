#pragma once
#include "Utilities/Concepts/DerivedFromDrawableComponent.h"

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
#include "UI/Structs/RectangleData.h"

#define SCROLL_MULTIPLIER 10

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
class RecycleView : public DrawableComponent, public DrawableTransform, public IScrollable
{
public:

    RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
        std::function<void(TDrawableComponent&)>&& onEnable, std::function<void(TDrawableComponent&)>&& onDisable,
        std::function<std::unique_ptr<TDrawableComponent>()>&& createDefault, RecycleViewActions&& devicesPresenterActions,
        bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    void AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent);

    void RemoveLastDrawableComponent();

    [[nodiscard]] std::vector<TDrawableComponent*> GetDrawableComponents() const;

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void SetCurrentScroll(float currentScroll);

    void SetIsFirstItemPresent(bool isFirstItemPresent);

    void SetIsLastItemPresent(bool isLastItemPresent);

    void Enable();

    void Disable();

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

    std::vector<std::unique_ptr<TDrawableComponent>> _drawableComponents;

    float _currentScroll {0};

    bool _isFirstItemPresent;

    bool _isLastItemPresent;

    std::unique_ptr<TRowCreation> _rowCreationStrategy;

    std::function<void(TDrawableComponent&)> _onEnable;

    std::function<void(TDrawableComponent&)> _onDisable;

    std::function<std::unique_ptr<TDrawableComponent>()> _createDefault;

    RecycleViewActions _devicesPresenterActions;
};

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize,
    uint8_t bufferRows, std::function<void(TDrawableComponent&)>&& onEnable, std::function<void(TDrawableComponent&)>&& onDisable,
    std::function<std::unique_ptr<TDrawableComponent>()>&& createDefault, RecycleViewActions&& devicesPresenterActions, bool isHidden) :
        DrawableComponent(isHidden), _viewsPerRow(viewsPerRow), _marginBetweenViews({marginBetweenViews.x / _viewsPerRow, marginBetweenViews.y}),
        _rowsSize(std::move(rowsSize)), _bufferRows(bufferRows * 2), _widthPerView(1 / static_cast<float>(_viewsPerRow)),
        _rowCreationStrategy(std::make_unique<TRowCreation>()), _onEnable(std::move(onEnable)), _onDisable(std::move(onDisable)),
        _createDefault(std::move(createDefault)), _devicesPresenterActions(std::move(devicesPresenterActions))
{
    Enable();

    CreateRow({0, -(_rowsSize.y + _marginBetweenViews.y)});

    for (uint8_t i {1}; i < _bufferRows; ++i)
    {
        CreateRow(_rows.back()->GetRelativePosition());
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::~RecycleView() noexcept
{
    Disable();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::SetParentState(ImVec2* parentPositionPointer,
    ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    UpdateResizableDrawablesCount();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
ImVec2 RecycleView<TDrawableComponent, TRowCreation>::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
ImVec2 RecycleView<TDrawableComponent, TRowCreation>::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    _devicesPresenterActions.ExecuteOnUpdateSize(_size->y);

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }

    UpdateResizableDrawablesCount();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::UpdateResizableDrawablesCount()
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

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::CreateRow(ImVec2&& lastRowPosition)
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

        _views.at(row.get()).push_back(view.get());

        row->AddRectDrawable(std::move(view));
    }

    row->SetParentState(_position.get(), _bottomRightPosition.get(), _size.get(), _mustBeHidden.get());

    _rows.push_back(std::move(row));

    for (uint8_t i {0}; i < _viewsPerRow; ++i)
    {
        AddDrawableComponent(_createDefault());
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::DeleteLastRow()
{
    _views.erase(_rows.back().get());

    _rows.pop_back();

    for (uint8_t i{0}; i < _viewsPerRow; ++i)
    {
        RemoveLastDrawableComponent();
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    {
        uint8_t drawableComponentsCount {static_cast<uint8_t>(_drawableComponents.size())};

        int quotient {drawableComponentsCount / _viewsPerRow};

        int module {drawableComponentsCount % _viewsPerRow};

        _views.at(_rows.at(quotient).get()).at(module)->AddDrawableComponent(drawableComponent.get());
    }

    _drawableComponents.push_back(std::move(drawableComponent));
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::RemoveLastDrawableComponent()
{
    _drawableComponents.pop_back();
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
std::vector<TDrawableComponent*> RecycleView<TDrawableComponent, TRowCreation>::GetDrawableComponents() const
{
    std::vector<TDrawableComponent*> drawableComponents;

    for (auto& drawableComponent : _drawableComponents)
    {
        drawableComponents.push_back(drawableComponent.get());
    }

    return drawableComponents;
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Enable()
{
    ScrollableManager::GetInstance().AddScrollable(this);

    for (auto&& drawableComponent : _drawableComponents)
    {
        _onEnable(*drawableComponent);
    }
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Disable()
{
    ScrollableManager::GetInstance().RemoveScrollable(this);

    for (auto&& drawableComponent : _drawableComponents)
    {
        _onDisable(*drawableComponent);
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
bool RecycleView<TDrawableComponent, TRowCreation>::CanBeScrolled()
{
    return !IsHidden();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Scroll(float scrollValue)
{
    scrollValue *= SCROLL_MULTIPLIER;

    _devicesPresenterActions.ExecuteOnScroll(-scrollValue);
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::SetCurrentScroll(float currentScroll)
{
    _currentScroll = currentScroll;

    HandleMove();
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::SetIsFirstItemPresent(bool isFirstItemPresent)
{
    _isFirstItemPresent = isFirstItemPresent;
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::SetIsLastItemPresent(bool isLastItemPresent)
{
    _isLastItemPresent = isLastItemPresent;
}

template <DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::HandleMove()
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

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Draw(ImDrawList* drawList)
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
