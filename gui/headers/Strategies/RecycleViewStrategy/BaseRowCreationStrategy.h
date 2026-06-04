#pragma once
#include <memory>

#include "UI/Elements/Base/RectDrawable.h"

class BaseRowCreationStrategy
{
public:

    virtual ~BaseRowCreationStrategy() = default;

    [[nodiscard]] std::unique_ptr<RectDrawable> CreateRow(ImVec2 lasPosition);
};
