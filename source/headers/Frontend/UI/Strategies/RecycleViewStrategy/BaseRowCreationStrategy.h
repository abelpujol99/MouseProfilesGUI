#pragma once
#include <memory>

#include "Frontend/UI/Elements/Base/ResizableDrawable.h"

class BaseRowCreationStrategy
{
public:

    virtual ~BaseRowCreationStrategy() = default;

    [[nodiscard]] std::unique_ptr<ResizableDrawable> CreateRow(ImVec2 lasPosition);
};
