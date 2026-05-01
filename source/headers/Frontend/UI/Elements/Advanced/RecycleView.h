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

    void MoveContainers(float scrollValue);

    void Draw(ImDrawList* drawList) override;

private:

    void UpdateResizableDrawablesCount();

    void Reset();

    void CalculateMaxScroll();

    void CreateRow(ImVec2&& lastRowPosition);

    void DeleteLastRow();

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    uint8_t _viewsPerRow;

    ImVec2 _marginBetweenViews;

    ImVec2 _rowsSize;

    uint8_t _bufferRows;

    uint8_t _totalRows;

    float _widthPerView;

    std::vector<std::unique_ptr<ResizableDrawable>> _rows;

    std::map<ResizableDrawable*, std::vector<ResizableDrawable*>> _views;

    std::vector<std::unique_ptr<TDrawableComponent>> _drawableComponents;

    std::map<ResizableDrawable*, uint8_t> _viewsComponentIndex;

    std::map<uint8_t, ResizableDrawable*> _componentViewsIndex;

    float _currentScroll {0};

    float _maxScroll{0};

    std::unique_ptr<TRowCreation> _rowCreationStrategy;
};

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize,
    uint8_t bufferRows, bool isHidden) :
        DrawableComponent(isHidden), _viewsPerRow(viewsPerRow), _marginBetweenViews({marginBetweenViews.x / _viewsPerRow, marginBetweenViews.y}),
        _rowsSize(std::move(rowsSize)), _bufferRows(bufferRows * 2),
        _widthPerView(1 / static_cast<float>(_viewsPerRow)), _rowCreationStrategy(std::make_unique<TRowCreation>())
{
    ScrollableManager::GetInstance().AddScrollable(this);

    CreateRow({0, -_rowsSize.y});
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
RecycleView<TDrawableComponent, TRowCreation>::~RecycleView() noexcept
{
    ScrollableManager::GetInstance().RemoveScrollable(this);
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
    MoveContainers(-_currentScroll);

    _currentScroll = 0;

    uint8_t rowsCount {static_cast<uint8_t>(_rows.size())};

    if (_viewsComponentIndex.at(_views.at(_rows.front().get()).front()) == 0)
    {
        //return;
    }

    for (uint8_t i {0}; i < rowsCount; ++i)
    {
        for (uint8_t j {0}; j < _viewsPerRow; ++j)
        {
            ResizableDrawable* view {_views.at(_rows.at(i).get()).at(j)};

            uint8_t& index {_viewsComponentIndex.at(view)};

            if (index >= _drawableComponents.size())
            {
                return;
            }

            view->RemoveDrawableComponent(_drawableComponents.at(index).get());

            index = i * _viewsPerRow + j;

            view->AddDrawableComponent(_drawableComponents.at(index).get());

            _componentViewsIndex.at(index) = _views.at(_rows.at(i).get()).at(j);
        }
    }
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
void RecycleView<TDrawableComponent, TRowCreation>::CreateRow(ImVec2&& lastRowPosition)
{
    std::unique_ptr<ResizableDrawable> row {DrawableFactory::CreateResizableDrawable(ANCHORS_TOP_STRETCH, PIVOT_TOP_CENTER,
        {lastRowPosition.x, lastRowPosition.y + _rowsSize.y}, {_rowsSize.x, _rowsSize.y}, _isHidden)};

    _views.emplace(row.get(), std::vector<ResizableDrawable*>{});

    uint8_t offsetIndex {static_cast<uint8_t>(_viewsPerRow * _rows.size())};

    for (uint8_t i {0}; i < _viewsPerRow; ++i)
    {
        std::unique_ptr<ResizableDrawable> view {DrawableFactory::CreateResizableDrawable(
            Anchors{{i * _widthPerView + _marginBetweenViews.x, _marginBetweenViews.y},
                {(i + 1) * _widthPerView - _marginBetweenViews.x, 1 - _marginBetweenViews.y}}, PIVOT_MIDDLE_CENTER,
                {0, 0}, {0, 0}, false)};

        uint8_t index {static_cast<uint8_t>(i + offsetIndex)};

        _viewsComponentIndex.emplace(view.get(), index);

        _componentViewsIndex.emplace(index + _viewsPerRow * _rows.size(), view.get());

        _views.at(row.get()).push_back(view.get());

        row->AddResizableDrawable(std::move(view));
    }

    row->SetParentTransform(_position.get(), _bottomRightPosition.get(), _size.get());

    _rows.push_back(std::move(row));
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::DeleteLastRow()
{
    _views.erase(_rows.back().get());

    _rows.pop_back();
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
void RecycleView<TDrawableComponent, TRowCreation>::AddDrawableComponent(std::unique_ptr<TDrawableComponent>&& drawableComponent)
{
    uint8_t drawableComponentsSize {static_cast<uint8_t>(_drawableComponents.size())};

    _componentViewsIndex.emplace(drawableComponentsSize, nullptr);

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
}

template<DerivedFromDrawableComponent TDrawableComponent, DerivedFromBaseRowCreationStrategy TRowCreation>
void RecycleView<TDrawableComponent, TRowCreation>::RemoveDrawableComponent(uint8_t index)
{
    uint8_t auxIndex = index;

    ResizableDrawable* resizableDrawable {nullptr};

    do{
        resizableDrawable = _componentViewsIndex.at(auxIndex);

        resizableDrawable->RemoveDrawableComponent(_drawableComponents.at(auxIndex));

        if (_drawableComponents.size() == ++auxIndex)
        {
            break;
        }

        resizableDrawable->AddDrawableComponent(_drawableComponents.at(auxIndex));

    }while(true);

    _drawableComponents.erase(index);

    _componentViewsIndex.erase(_componentViewsIndex.cend());

    CalculateMaxScroll();
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
    uint8_t halfBufferSlots {static_cast<uint8_t>(_bufferRows / 2)};

    float upperLimit {-_rowsSize.y * halfBufferSlots};

    float lowerLimit {_size->y + _rowsSize.y * (halfBufferSlots - 1)};

    float jumpDistance {_rowsSize.y * _rows.size() / _viewsPerRow};

    for (auto&& row : _rows)
    {
        ImVec2 currentRelativePosition {row->GetRelativePosition()};

        float predictedRelativePosition {currentRelativePosition.y + scrollValue};

        if (predictedRelativePosition < upperLimit)
        {
            for (auto&& view : _views.at(row.get()))
            {
                uint8_t& index {_viewsComponentIndex.at(view)};

                int nexIndex {index + static_cast<int>(_rows.size() * _viewsPerRow)};

                if (nexIndex < _drawableComponents.size())
                {
                    predictedRelativePosition += jumpDistance;

                    if (index > NO_INDEX)
                    {
                        view->RemoveDrawableComponent(_drawableComponents.at(index).get());
                    }

                    index = nexIndex;

                    if (index > NO_INDEX)
                    {
                        view->AddDrawableComponent(_drawableComponents.at(index).get());
                    }
                }
            }
        }
        else if (predictedRelativePosition > lowerLimit)
        {
            for (auto&& view : _views.at(row.get()))
            {
                uint8_t& index {_viewsComponentIndex.at(view)};

                int nexIndex {index - static_cast<int>(_rows.size() * _viewsPerRow)};

                if (nexIndex >= 0)
                {
                    predictedRelativePosition -= jumpDistance;

                    if (index > NO_INDEX)
                    {
                        view->RemoveDrawableComponent(_drawableComponents.at(index).get());
                    }

                    index = nexIndex;

                    if (index > NO_INDEX)
                    {
                        view->AddDrawableComponent(_drawableComponents.at(index).get());
                    }
                }
            }
        }

        currentRelativePosition.y = predictedRelativePosition;

        row->SetRelativePosition(std::move(currentRelativePosition));
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
        for (auto&& view : _views.at(row.get()))
        {
            view->Draw(drawList);
        }
    }
}
