#include "UI/Elements/Advanced/RecycleView/RecycleViewActions.h"

RecycleViewActions::RecycleViewActions(std::function<void(uint8_t)>&& onUpdateRowsCount,
    std::function<void(float)>&& onUpdateSize, std::function<void(float)>&& onScroll) :
        _onUpdateRowsCount(std::move(onUpdateRowsCount)), _onUpdateSize(std::move(onUpdateSize)), _onScroll(std::move(onScroll))
{}

void RecycleViewActions::ExecuteOnUpdateRowsCount(uint8_t rowsCount) const
{
    _onUpdateRowsCount(rowsCount);
}

void RecycleViewActions::ExecuteOnUpdateSize(float size) const
{
    _onUpdateSize(size);
}

void RecycleViewActions::ExecuteOnScroll(float scroll) const
{
    _onScroll(scroll);
}
