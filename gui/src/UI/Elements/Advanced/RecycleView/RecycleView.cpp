#include "UI/Elements/Advanced/RecycleView/RecycleView.h"

#include <cmath>

#include "AnchorsDefines.h"
#include "PivotDefines.h"
#include "Factory/DrawableFactory.h"
#include "Managers/Gestures/ScrollableManager.h"
#include "Utilities/Math.h"

RecycleView::RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
    std::function<void(RectDrawable*)>&& addDefault, std::function<void()> removeLastView,
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

RecycleView::~RecycleView() noexcept
{
    RecycleView::Disable();
}

void RecycleView::SetIsHidden(bool isHidden)
{
    DrawableComponent::SetIsHidden(isHidden);

    isHidden ? Disable() : Enable();

    for (auto&& row : _rows)
    {
        row->SetIsHidden(isHidden);
    }
}

void RecycleView::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    DrawableComponent::SetParentState(parentPositionPointer, parentBottomRightPositionPointer, parentSizePointer, isParentHiddenPointer);

    UpdateResizableDrawablesCount();
}

ImVec2 RecycleView::GetParentPosition() const
{
    return DrawableComponent::GetParentPosition();
}

ImVec2 RecycleView::GetParentBottomRightPosition() const
{
    return DrawableComponent::GetParentBottomRightPosition();
}

void RecycleView::OnParentPositionUpdated()
{
    *_position = GetParentPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

void RecycleView::OnParentBottomRightPositionUpdated()
{
    *_bottomRightPosition = GetParentBottomRightPosition();

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }
}

void RecycleView::OnParentSizeUpdated()
{
    *_size = GetParentSize();

    _devicesPresenterActions.ExecuteOnUpdateSize(_size->y);

    for (auto&& row : _rows)
    {
        row->UpdateAttributes();
    }

    UpdateResizableDrawablesCount();
}

void RecycleView::UpdateResizableDrawablesCount()
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

void RecycleView::CreateRow(ImVec2&& lastRowPosition)
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

void RecycleView::DeleteLastRow()
{
    _views.erase(_rows.back().get());

    _rows.pop_back();

    for (uint8_t i{0}; i < _viewsPerRow; ++i)
    {
        _removeLastViewComponents();
    }
}

void RecycleView::Enable()
{
    ScrollableManager::GetInstance().AddScrollable(this);

    for (auto&& row : _rows)
    {
        row->Enable();
    }
}

void RecycleView::Disable()
{
    ScrollableManager::GetInstance().RemoveScrollable(this);

    for (auto&& row : _rows)
    {
        row->Disable();
    }
}

bool RecycleView::CanBeScrolled()
{
    return !IsHidden();
}

void RecycleView::Scroll(float scrollValue)
{
    scrollValue *= SCROLL_MULTIPLIER;

    _devicesPresenterActions.ExecuteOnScroll(-scrollValue);
}

void RecycleView::SetCurrentScroll(float currentScroll)
{
    _currentScroll = currentScroll;

    HandleMove();
}

void RecycleView::SetIsFirstItemPresent(bool isFirstItemPresent)
{
    _isFirstItemPresent = isFirstItemPresent;
}

void RecycleView::SetIsLastItemPresent(bool isLastItemPresent)
{
    _isLastItemPresent = isLastItemPresent;
}

void RecycleView::HandleMove()
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

void RecycleView::Draw(ImDrawList* drawList)
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