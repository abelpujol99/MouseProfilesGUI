#include "MVP/View/Devices/DevicesPresenterRecycleViewActions.h"

DevicesPresenterRecycleViewActions::DevicesPresenterRecycleViewActions(std::function<void(uint8_t)>&& onUpdateRowsCount,
    std::function<void(float)>&& onUpdateSize, std::function<void(float)>&& onScroll) :
        _onUpdateRowsCount(std::move(onUpdateRowsCount)), _onUpdateSize(std::move(onUpdateSize)), _onScroll(std::move(onScroll))
{}

void DevicesPresenterRecycleViewActions::ExecuteOnUpdateRowsCount(uint8_t rowsCount) const
{
    _onUpdateRowsCount(rowsCount);
}

void DevicesPresenterRecycleViewActions::ExecuteOnUpdateSize(float size) const
{
    _onUpdateSize(size);
}

void DevicesPresenterRecycleViewActions::ExecuteOnScroll(float scroll) const
{
    _onScroll(scroll);
}
