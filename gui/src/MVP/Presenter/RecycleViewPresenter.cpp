#include "MVP/Presenter/RecycleViewPresenter.h"

#include <cmath>

#include "Utilities/Math.h"

void RecycleViewPresenter::Reset()
{
    OnScroll(-_currentScroll);
}

void RecycleViewPresenter::SetListLength(size_t listLength)
{
    _listLength = listLength;

    CalculateMaxScroll();
}

void RecycleViewPresenter::SetRecyclerViewHeight(float recyclerViewHeight)
{
    _recyclerViewHeight = recyclerViewHeight;
}

void RecycleViewPresenter::SetViewsPerRow(uint8_t viewsPerRow)
{
    _viewsPerRow = viewsPerRow;
}

void RecycleViewPresenter::SetItemHeight(float itemHeight)
{
    _itemHeight = itemHeight;
}

void RecycleViewPresenter::SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount)
{
    _visibleItemsCount = visibleItemsCount;
}

void RecycleViewPresenter::SetRecyclerViewBufferRows(uint8_t bufferRows)
{
    _bufferRows = bufferRows;
}

void RecycleViewPresenter::CalculateMaxScroll()
{
    _maxScroll = std::ceil(static_cast<float>(_listLength) / static_cast<float>(_viewsPerRow)) * _itemHeight - _recyclerViewHeight;

    if (_maxScroll >= 0)
    {
        return;
    }

    _maxScroll = 0;
}

void RecycleViewPresenter::OnScroll(float scrollValue)
{
    scrollValue = Utilities::Math::Clamp(scrollValue, -_itemHeight, _itemHeight);

    float newScrollValue {_currentScroll + scrollValue};

    if (newScrollValue < 0)
    {
        if (_currentScroll == 0)
        {
            return;
        }

        newScrollValue = 0;
    }
    else if (newScrollValue > _maxScroll)
    {
        if (_currentScroll == _maxScroll)
        {
            return;
        }

        newScrollValue = _maxScroll;
    }

    _currentScroll = newScrollValue;

    UpdateRecycleViewDataDisplay();
}

void RecycleViewPresenter::UpdateRecycleViewDataDisplay()
{
    _firstItemToShowIndex = Utilities::Math::Clamp(
        std::ceil(_currentScroll / _itemHeight) * _viewsPerRow - _bufferRows * _viewsPerRow, 0, _listLength - _visibleItemsCount);
}

float RecycleViewPresenter::GetCurrentScroll() const
{
    return _currentScroll;
}

std::vector<uint8_t> RecycleViewPresenter::GetVisibleItemsIndex() const
{
    std::vector<uint8_t> visibleItemsIndex;

    visibleItemsIndex.reserve(_visibleItemsCount);

    for (uint8_t i{_firstItemToShowIndex}; i < _firstItemToShowIndex + _visibleItemsCount && i < _listLength; ++i)
    {
        visibleItemsIndex.push_back(i);
    }

    return visibleItemsIndex;
}

bool RecycleViewPresenter::IsFirstItemPresent() const
{
    return _firstItemToShowIndex * _viewsPerRow == 0;
}

bool RecycleViewPresenter::IsLastItemPresent() const
{
    return _listLength < _visibleItemsCount || _firstItemToShowIndex + _visibleItemsCount == _listLength;
}