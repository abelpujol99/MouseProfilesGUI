#pragma once

#include <cstdint>
#include <string>
#include <vector>

class RecycleViewPresenter
{
public:

    void Reset();

    void SetListLength(size_t listLength);

    void SetRecyclerViewHeight(float recyclerViewHeight);

    void SetViewsPerRow(uint8_t viewsPerRow);

    void SetItemHeight(float itemHeight);

    void SetRecycleViewVisibleItemsCount(uint8_t visibleItemsCount);

    void SetRecyclerViewBufferRows(uint8_t bufferRows);

    void OnScroll(float scrollValue);

    [[nodiscard]] float GetCurrentScroll() const;

    [[nodiscard]] std::vector<uint8_t> GetVisibleItemsIndex() const;

    [[nodiscard]] bool IsFirstItemPresent() const;

    [[nodiscard]] bool IsLastItemPresent() const;

private:

    void CalculateMaxScroll();

    void UpdateRecycleViewDataDisplay();

    size_t _listLength {0};

    float _recyclerViewHeight {0};

    uint8_t _viewsPerRow {0};

    float _itemHeight {0};

    uint8_t _visibleItemsCount {0};

    uint8_t _bufferRows {0};

    float _currentScroll {0};

    float _maxScroll {0};

    uint8_t _firstItemToShowIndex {0};
};
