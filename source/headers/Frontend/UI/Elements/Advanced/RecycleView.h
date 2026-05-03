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

#define SCROLL_MULTIPLIER 10

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
class RecycleView : public DrawableComponent, public DrawableTransform, public IScrollable
{
public:

    RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
        bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    void AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent);

    void RemoveDrawableComponent(uint8_t index);

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    void UpdateResizableDrawablesCount();

    void Reset();

    void CalculateFirstViewIndexReference();

    void CalculateLastViewIndexReference();

    void CalculateMaxScroll();

    void CreateRow(ImVec2&& lastRowPosition);

    void DeleteLastRow();

    void MoveContainers(float scrollValue);

    void UpdateViewContent(RectDrawable* view, int newIndex);

    void HandleMoveUp(float scrollValue);

    void HandleMoveDown(float scrollValue);

    uint8_t _viewsPerRow;

    ImVec2 _marginBetweenViews;

    ImVec2 _rowsSize;

    uint8_t _bufferRows;

    uint8_t _totalRows;

    float _widthPerView;

    std::vector<std::unique_ptr<RectDrawable>> _rows;

    std::map<RectDrawable*, std::vector<RectDrawable*>> _views;

    std::vector<std::unique_ptr<TDrawableComponent>> _drawableComponents;

    std::map<RectDrawable*, uint8_t> _viewsComponentIndex;

    std::map<uint8_t, RectDrawable*> _componentViewsIndex;

    float _currentScroll {0};

    float _maxScroll{0};

    std::unique_ptr<TRowCreation> _rowCreationStrategy;

    RectDrawable** _firstComponentViewReference {nullptr};
    RectDrawable** _lastComponentViewReference {nullptr};
};

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize,
    uint8_t bufferRows, bool isHidden) :
        DrawableComponent(isHidden), _viewsPerRow(viewsPerRow), _marginBetweenViews({marginBetweenViews.x / _viewsPerRow, marginBetweenViews.y}),
        _rowsSize(std::move(rowsSize)), _bufferRows(bufferRows * 2), _widthPerView(1 / static_cast<float>(_viewsPerRow)),
        _rowCreationStrategy(std::make_unique<TRowCreation>())
{
    ScrollableManager::GetInstance().AddScrollable(this);

    CreateRow({0, -_rowsSize.y});

    for (uint8_t i {1}; i < _bufferRows; ++i)
    {
        CreateRow(_rows.back()->GetRelativePosition());
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::~RecycleView() noexcept
{
    ScrollableManager::GetInstance().RemoveScrollable(this);
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::SetParentTransform(ImVec2* parentPositionPointer,
    ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer)
{
    DrawableComponent::SetParentTransform(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer);

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

    UpdateResizableDrawablesCount();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }

    UpdateResizableDrawablesCount();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    CalculateMaxScroll();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }

    UpdateResizableDrawablesCount();
    std::cout << "Count: " << _rows.size() << std::endl;
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::UpdateResizableDrawablesCount()
{
    float parentSizeY {GetParentSize().y};

    int slots {_bufferRows};

    float availableSlots {std::ceil(parentSizeY / _rowsSize.y)};

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

    Reset();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Reset()
{
    _currentScroll = 0;

    uint8_t rowsCount {static_cast<uint8_t>(_rows.size())};

    for (uint8_t i {0}; i < rowsCount; ++i)
    {
        _rows[i]->SetRelativePosition({0, i * _rowsSize.y});

        for (uint8_t j {0}; j < _viewsPerRow; ++j)
        {
            UpdateViewContent(_views.at(_rows.at(i).get()).at(j), i * _viewsPerRow + j);
        }
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::CalculateFirstViewIndexReference()
{
    int index {0};

    if (!_componentViewsIndex.contains(index))
    {
        _firstComponentViewReference = nullptr;
        return;
    }

    _firstComponentViewReference = &_componentViewsIndex.at(index);
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::CalculateLastViewIndexReference()
{
    int index {_drawableComponents.size() - 1};

    if (!_componentViewsIndex.contains(index))
    {
        _lastComponentViewReference = nullptr;
        return;
    }

    _lastComponentViewReference = &_componentViewsIndex.at(index);
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::CalculateMaxScroll()
{
    _maxScroll = -(std::ceil(static_cast<float>(_drawableComponents.size()) / static_cast<float>(_viewsPerRow)) * _rowsSize.y) + GetParentSize().y;

    if (_maxScroll <= 0)
    {
        return;
    }

    _maxScroll = 0;
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::CreateRow(ImVec2&& lastRowPosition)
{
    std::unique_ptr<RectDrawable> row {DrawableFactory::CreateRectDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {lastRowPosition.x, lastRowPosition.y + _rowsSize.y}, {_rowsSize.x, _rowsSize.y}, false)};

    _views.emplace(row.get(), std::vector<RectDrawable*>{});

    uint8_t offsetIndex {static_cast<uint8_t>(_viewsPerRow * _rows.size())};

    for (uint8_t i {0}; i < _viewsPerRow; ++i)
    {
        std::unique_ptr<RectDrawable> view {DrawableFactory::CreateRectDrawable(
            Anchors{{i * _widthPerView + _marginBetweenViews.x, _marginBetweenViews.y},
                {(i + 1) * _widthPerView - _marginBetweenViews.x, 1 - _marginBetweenViews.y}}, PIVOT_MIDDLE_CENTER,
                {0, 0}, {0, 0}, false)};

        uint8_t index {static_cast<uint8_t>(i + offsetIndex)};

        _viewsComponentIndex.emplace(view.get(), index);

        _views.at(row.get()).push_back(view.get());

        row->AddRectDrawable(std::move(view));
    }

    row->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    row->AddDrawableComponent(new Rectangle(RectangleData{BROWN, 0, 2, false}, false));

    _rows.push_back(std::move(row));
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::DeleteLastRow()
{
    for (auto&& view : _views.at(_rows.back().get()))
    {
        uint8_t index {_viewsComponentIndex.at(view)};

        _viewsComponentIndex.erase(view);

        if (!_componentViewsIndex.contains(index))
        {
            continue;
        }

        _componentViewsIndex.at(index) = nullptr;
    }

    _views.erase(_rows.back().get());

    _rows.pop_back();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    uint8_t drawableComponentsSize {static_cast<uint8_t>(_drawableComponents.size())};

    _componentViewsIndex.emplace(drawableComponentsSize, nullptr);
    drawableComponent->SetIsHidden(true);

    auto itEnd {_viewsComponentIndex.cend()};

    for (auto it{_viewsComponentIndex.begin()}; it != itEnd; ++it)
    {
        auto& pair {*it};

        if (pair.second != drawableComponentsSize)
        {
            continue;
        }

        _componentViewsIndex.at(drawableComponentsSize) = pair.first;

        pair.first->AddDrawableComponent(drawableComponent.get());

        break;
    }

    _drawableComponents.push_back(std::move(drawableComponent));

    CalculateMaxScroll();

    CalculateFirstViewIndexReference();

    CalculateLastViewIndexReference();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::RemoveDrawableComponent(uint8_t index)
{
    uint8_t auxIndex = index;

    RectDrawable* view {nullptr};

    do{
        view = _componentViewsIndex.at(auxIndex);

        view->RemoveDrawableComponent(_drawableComponents.at(auxIndex));

        if (_drawableComponents.size() == ++auxIndex)
        {
            break;
        }

        view->AddDrawableComponent(_drawableComponents.at(auxIndex));

    }while(true);

    _drawableComponents.erase(index);

    _componentViewsIndex.erase(_componentViewsIndex.cend());

    CalculateMaxScroll();

    CalculateFirstViewIndexReference();

    CalculateLastViewIndexReference();
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
bool RecycleView<TDrawableComponent, TRowCreation>::CanBeScrolled()
{
    return !_isHidden;
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Scroll(float scrollValue)
{
    scrollValue *= SCROLL_MULTIPLIER;

    scrollValue = Utilities::Math::Clamp(scrollValue, -_rowsSize.y, _rowsSize.y);

    float newScrollValue {_currentScroll + scrollValue};

    if (newScrollValue > 0)
    {
        if (_currentScroll == 0)
        {
            return;
        }

        scrollValue = -_currentScroll;

        newScrollValue = 0;
    }
    else if (newScrollValue < _maxScroll)
    {
        if (_currentScroll == _maxScroll)
        {
            return;
        }

        scrollValue = _maxScroll - _currentScroll;

        newScrollValue = _maxScroll;
    }

    _currentScroll = newScrollValue;

    MoveContainers(scrollValue);
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::MoveContainers(float scrollValue)
{
    if (scrollValue > 0)
    {
        HandleMoveUp(scrollValue);
        return;
    }

    HandleMoveDown(scrollValue);
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::HandleMoveUp(float scrollValue)
{
    const uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferRows / 2)};

    const float lowerLimit {_size->y + _rowsSize.y * (halfBufferSlots - 1)};

    const size_t rowsCount {_rows.size()};

    const float jumpDistance {_rowsSize.y * rowsCount};

    const int indexJump {static_cast<int>(rowsCount * _viewsPerRow)};

    for (int i {static_cast<int>(rowsCount - 1)}; i >= 0; --i)
    {
        RectDrawable* row {_rows[i].get()};

        ImVec2 currentRelativePosition {row->GetRelativePosition()};

        float predictedRelativePosition {currentRelativePosition.y + scrollValue};

        std::vector<RectDrawable*>& views {_views.at(row)};

        if (predictedRelativePosition > lowerLimit && *_firstComponentViewReference == nullptr)
        {
            uint8_t firstViewIndex {_viewsComponentIndex.at(views.front())};

            if (firstViewIndex - indexJump >= 0)
            {
                predictedRelativePosition -= jumpDistance;
            }

            for (auto&& view : views)
            {
                UpdateViewContent(view, _viewsComponentIndex.at(view) - indexJump);
            }
        }

        currentRelativePosition.y = predictedRelativePosition;

        row->SetRelativePosition(std::move(currentRelativePosition));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::HandleMoveDown(float scrollValue)
{
    const uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferRows / 2)};

    const float upperLimit {-_rowsSize.y * halfBufferSlots};

    const size_t rowsCount {_rows.size()};

    const float jumpDistance {_rowsSize.y * rowsCount};

    const int indexJump {static_cast<int>(rowsCount * _viewsPerRow)};

    for (auto&& row : _rows)
    {
        ImVec2 currentRelativePosition {row->GetRelativePosition()};

        float predictedRelativePosition {currentRelativePosition.y + scrollValue};

        std::vector<RectDrawable*>& views {_views.at(row.get())};

        if (predictedRelativePosition < upperLimit && *_lastComponentViewReference == nullptr)
        {
            uint8_t firstViewIndex {_viewsComponentIndex.at(views.front())};

            if (firstViewIndex + indexJump < _drawableComponents.size())
            {
                predictedRelativePosition += jumpDistance;
            }

            for (auto&& view : views)
            {
                UpdateViewContent(view, _viewsComponentIndex.at(view) + indexJump);
            }
        }

        currentRelativePosition.y = predictedRelativePosition;

        row->SetRelativePosition(std::move(currentRelativePosition));
    }
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::UpdateViewContent(RectDrawable* view, int newIndex)
{
    uint8_t& index {_viewsComponentIndex.at(view)};

    if (index < _drawableComponents.size())
    {
        view->RemoveDrawableComponent(_drawableComponents.at(index).get());
        _componentViewsIndex.at(index) = nullptr;
    }

    index = newIndex;

    if (index < _drawableComponents.size())
    {
        view->AddDrawableComponent(_drawableComponents.at(index).get());
        _componentViewsIndex.at(index) = view;
    }
}


template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::Draw(ImDrawList* drawList)
{
    if (_isHidden)
    {
        return;
    }

    for (auto&& row : _rows)
    {
        row->Draw(drawList);
    }
}