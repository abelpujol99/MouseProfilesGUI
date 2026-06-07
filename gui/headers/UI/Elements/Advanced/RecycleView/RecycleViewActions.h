#pragma once
#include <cstdint>
#include <functional>

class RecycleViewActions
{
public:

    RecycleViewActions(std::function<void(uint8_t)>&& onUpdateRowsCount, std::function<void(float)>&& onUpdateSize,
        std::function<void(float)>&& onScroll);

    void ExecuteOnUpdateRowsCount(uint8_t rowsCount) const;

    void ExecuteOnUpdateSize(float size) const;

    void ExecuteOnScroll(float scroll) const;

private:

    std::function<void(uint8_t)> _onUpdateRowsCount;

    std::function<void(float)> _onUpdateSize;

    std::function<void(float)> _onScroll;
};
